#include <algorithm>
#include <iostream>

#include "DataFormats/L1TMuonPhase2/interface/EMTFHit.h"

#include "MuonTrackCorr/MuonTrackCorr/interface/SubsystemMCTruth.h"


SubsystemMCTruth::SubsystemMCTruth(
        const edm::ParameterSet& pset, 
        edm::ConsumesCollector&& consumes_collector
) {
    // Get Subsystem Enables
    csc_enable_ = pset.getParameter<bool>("CSCSimHitEnabled");
    rpc_enable_ = pset.getParameter<bool>("RPCSimHitEnabled");
    gem_enable_ = pset.getParameter<bool>("GEMSimHitEnabled");
    me0_enable_ = pset.getParameter<bool>("ME0SimHitEnabled");

    // Get Tokens 
    trk_part_token_  = consumes_collector.consumes<TrackingParticleCollection>(
            pset.getParameter<edm::InputTag>("TrkPartTag")  
    );
    csc_strip_sim_links_token_ = consumes_collector.consumes<StripDigiSimLinks>(
            pset.getParameter<edm::InputTag>("CSCStripSimLinksTag")
    );
    csc_wire_sim_links_token_ = consumes_collector.consumes<WireDigiSimLinks>(
            pset.getParameter<edm::InputTag>("CSCWireSimLinksTag")
    );
    rpc_digi_sim_links_token_ = consumes_collector.consumes<RPCDigiSimLinks>(
            pset.getParameter<edm::InputTag>("RPCDigiSimLinksTag")
    );
    gem_digi_sim_links_token_ = consumes_collector.consumes<GEMDigiSimLinks>(
            pset.getParameter<edm::InputTag>("GEMDigiSimLinksTag")
    );
    me0_digi_sim_links_token_ = consumes_collector.consumes<ME0DigiSimLinks>(
            pset.getParameter<edm::InputTag>("ME0DigiSimLinksTag")
    );

    // Init Pointers
    csc_strip_sim_links_ = nullptr;
    csc_wire_sim_links_  = nullptr;
    rpc_digi_sim_links_  = nullptr;
    gem_digi_sim_links_  = nullptr;
    me0_digi_sim_links_  = nullptr;
}

SubsystemMCTruth::~SubsystemMCTruth() {
    // Do Nothing
}

void SubsystemMCTruth::update(
        const edm::Event& evt, 
        const edm::EventSetup& evt_setup
) {
    // Short-Circuit
    if (evt.isRealData()) {
        return;
    }

    // Load
    auto csc_strip_sim_links_handle = evt.getHandle(csc_strip_sim_links_token_);
    auto csc_wire_sim_links_handle  = evt.getHandle(csc_wire_sim_links_token_);
    auto rpc_digi_sim_links_handle  = evt.getHandle(rpc_digi_sim_links_token_);
    auto gem_digi_sim_links_handle  = evt.getHandle(gem_digi_sim_links_token_);
    auto me0_digi_sim_links_handle  = evt.getHandle(me0_digi_sim_links_token_);

    if (csc_enable_) {
        csc_strip_sim_links_ = csc_strip_sim_links_handle.product();
        csc_wire_sim_links_  = csc_wire_sim_links_handle.product();
    }

    if (rpc_enable_){
        rpc_digi_sim_links_  = rpc_digi_sim_links_handle.product();
    }
    
    if (gem_enable_) {
        gem_digi_sim_links_  = gem_digi_sim_links_handle.product();
    }

    if (me0_enable_) {
        me0_digi_sim_links_  = me0_digi_sim_links_handle.product();
    }

    // Build Track Particle Links
    auto trk_part_col_handle = evt.getHandle(trk_part_token_);
    auto trk_part_col        = trk_part_col_handle.product();

    trk_part_links_.clear();

    unsigned int trk_part_id = 0;

    for (const auto& trk_part : (*trk_part_col)) {        

        for (const auto& sim_trk : trk_part.g4Tracks()) {
            const auto& evt_id     = sim_trk.eventId();
            const auto& sim_trk_id = sim_trk.trackId();

            sim_hit_id_t match_id(evt_id, sim_trk_id);

            //trk_part_links_[match_id] = trk_part.pdgId();
            trk_part_links_[match_id] = trk_part_id;
        }

        trk_part_id++;
    }
}

int SubsystemMCTruth::findTrackingParticleFromSimHit(
        const PSimHit& sim_hit
) const {
    int tp_id = -1;  // index of the tp
                  
    auto evt_id     = sim_hit.eventId();
    auto sim_trk_id = sim_hit.trackId();

    sim_hit_id_t match_id(evt_id, sim_trk_id);
    auto found = trk_part_links_.find(match_id);
    
    if (found != trk_part_links_.end()) {
        tp_id = found->second;
    }

    return tp_id;
}

std::pair<int, int> SubsystemMCTruth::findTrackingParticlesFromEMTFHit(
        const EMTFHit& hit
) const {
    int sim_tp1 = -1;
    int sim_tp2 = -1;

    if (hit.subsystem() == L1TMuon::kCSC) {
        sim_tp1 = findTrackingParticleCSCStrip(hit);
        sim_tp2 = findTrackingParticleCSCWire(hit);
    } else if (hit.subsystem() == L1TMuon::kRPC) {
        sim_tp1 = findTrackingParticleRPC(hit);
        sim_tp2 = -1;
    } else if (hit.subsystem() == L1TMuon::kGEM) {
        sim_tp1 = findTrackingParticleGEM(hit);
        sim_tp2 = -1;
    } else if (hit.subsystem() == L1TMuon::kME0) {
        sim_tp1 = findTrackingParticleME0(hit);
        sim_tp2 = -1;
    }

    return std::make_pair(sim_tp1, sim_tp2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Subsystems
/////////////////////////////////////////////////////////////////////////////////////////////////
int SubsystemMCTruth::findTrackingParticleCSCStrip(const EMTFHit& hit) const {
    // Short-Circuit: Sim Links not found
    if (csc_strip_sim_links_ == nullptr) {
        return -1;
    }

    // Convert hit info
    // Different convention used in CSC StripDigiSimLink (fullstrip)
    int hit_strip = (hit.strip() - 1) / 2 + 1;  

    // Check all 6 CSC layers
    std::map<sim_hit_id_t, float> matches;

    for (unsigned layer = 0; layer < 6; ++layer) {
        const CSCDetId hit_det_id(hit.rawDetId());
        const CSCDetId sim_link_det_id(hit_det_id.endcap(), hit_det_id.station(), hit.ring(), hit_det_id.chamber(), layer + 1);  // correct layer

        const auto csc_strip_layer_links_it = csc_strip_sim_links_->find(sim_link_det_id);

        if (csc_strip_layer_links_it == csc_strip_sim_links_->end()) {
            continue;
        }

        // Loop Sim links
        for (const auto& link : (*csc_strip_layer_links_it)) {
            const auto& evt_id     = link.eventId();
            const auto& sim_trk_id = link.SimTrackId();

            const auto& channel  = link.channel();
            const auto& fraction = link.fraction();

            // Allow delta of +/-3
            int delta = std::abs(hit_strip - static_cast<int>(channel));

            if (delta > 3) {
                continue; 
            }

            // Sim Hit Match 
            sim_hit_id_t match_id(evt_id, sim_trk_id);

            if (matches.find(match_id) == matches.end()) {
                matches[match_id] = 0.;
            }

            matches[match_id] += fraction;
        }
    }

    return findBestMatch(matches);
}

int SubsystemMCTruth::findTrackingParticleCSCWire(const EMTFHit& hit) const {
    // Short-Circuit: Sim Links not found
    if (csc_wire_sim_links_ == nullptr) {
        return -1;
    }

    // Convert hit info
    // Different convention used in CSC StripDigiSimLink
    int hit_wire = (hit.wire1() + 100) + 1; 

    // Check all 6 CSC layers
    std::map<sim_hit_id_t, float> matches;

    for (unsigned layer = 0; layer < 6; ++layer) {
        const CSCDetId hit_det_id(hit.rawDetId());
        const CSCDetId sim_link_det_id(hit_det_id.endcap(), hit_det_id.station(), hit.ring(), hit_det_id.chamber(), layer + 1);  // correct layer

        const auto csc_wire_layer_links_it = csc_wire_sim_links_->find(sim_link_det_id);

        if (csc_wire_layer_links_it == csc_wire_sim_links_->end()) {
            continue;
        }

        for (const auto& link : (*csc_wire_layer_links_it)) {
            const auto& evt_id     = link.eventId();
            const auto& sim_trk_id = link.SimTrackId();

            const auto& channel  = link.channel();
            const auto& fraction = link.fraction();

            // Allow delta of +/-4
            int delta = std::abs(hit_wire - static_cast<int>(channel));

            if (delta > 4) {
                continue;
            }

            // Sim Hit Match 
            sim_hit_id_t match_id(evt_id, sim_trk_id);

            if (matches.find(match_id) == matches.end())
                matches[match_id] = 0.;

            matches[match_id] += fraction;
        }
    }

    return findBestMatch(matches);
}

int SubsystemMCTruth::findTrackingParticleRPC(const EMTFHit& hit) const {
    // Short-Circuit: Sim Links not found
    if (rpc_digi_sim_links_ == nullptr) {
        return -1;
    }

    // Check all strips in the RPC cluster
    std::map<sim_hit_id_t, float> matches;

    const RPCDetId det_id(hit.rawDetId());
    int hit_strip_lo = hit.stripLo();
    int hit_strip_hi = hit.stripHi();
    int hit_bx       = hit.bx();

    // Jia Fu: temporary fix
    for (const auto& digi_sim_link : (*rpc_digi_sim_links_)) { // Loop digi sim links
        for (const auto& link : digi_sim_link) { // Loop layer sim links in digi
            const auto det_unit_id = link.getDetUnitId();
            const auto sim_strip   = link.getStrip();
            const auto sim_bx      = link.getBx();

            const auto& evt_id     = link.getEventId();
            const auto& sim_trk_id = link.getTrackId();

            if (det_unit_id != det_id.rawId()) {
                continue;
            }

            for (int hit_strip = hit_strip_lo; hit_strip < hit_strip_hi + 1; ++hit_strip) { // Loop over strips
                // Allow delta of +/-1
                int delta_bx = std::abs(hit_bx    - static_cast<int>(sim_bx));
                int delta    = std::abs(hit_strip - static_cast<int>(sim_strip));

                if ((delta_bx > 1) || (delta > 1)) {
                    continue;
                }

                // Sim Hit Match 
                sim_hit_id_t match_id(evt_id, sim_trk_id);

                if (matches.find(match_id) == matches.end()) {
                    matches[match_id] = 0.;
                }

                matches[match_id] += 1.0;

                //// Debug
                //std::cout << "Dump RPCDigiSimLink - strip " << linkItr->getStrip() << " hit_bx " << linkItr->getBx()
                //          << " entry " << linkItr->getEntryPoint() << " p4 " << linkItr->getMomentumAtEntry()
                //          << " tof " << linkItr->getTimeOfFlight() << " eloss " << linkItr->getEnergyLoss()
                //          << " pdg " << linkItr->getParticleType() << " process " << linkItr->getProcessType()
                //          << " trackId " << linkItr->getTrackId() << " eventId " << linkItr->getEventId().bunchCrossing()
                //          << ", " << linkItr->getEventId().event() << std::endl;
            }
        }
    }

    return findBestMatch(matches);
}

int SubsystemMCTruth::findTrackingParticleGEM(const EMTFHit& hit) const {
    // Short-Circuit: Sim Links not found
    if (gem_digi_sim_links_ == nullptr) {
        return -1;
    }

    // Check both GEM layers
    // Check all strips in the GEM cluster
    std::map<sim_hit_id_t, float> matches;

    int hit_strip_lo = hit.stripLo();
    int hit_strip_hi = hit.stripHi();
    int hit_bx = hit.bx();

    for (unsigned layer = 0; layer < 2; ++layer) {
        const GEMDetId hit_det_id(hit.rawDetId());
        const GEMDetId sim_link_det_id(hit_det_id.region(), hit_det_id.ring(), hit_det_id.station(), layer + 1, hit_det_id.chamber(), hit_det_id.roll());

        const auto gem_layer_links_it = gem_digi_sim_links_->find(sim_link_det_id);

        if (gem_layer_links_it == gem_digi_sim_links_->end()) {
            continue;
        }

        for (const auto& link : (*gem_layer_links_it)) { // Loop layer sim links in digi
            unsigned int sim_strip = link.getStrip();
            unsigned int sim_bx    = link.getBx();

            const auto& evt_id     = link.getEventId();
            const auto& sim_trk_id = link.getTrackId();

            // Maybe different for GE1/1 vs GE2/1?
            unsigned int sim_pad = (hit.station() == 1) ? ((sim_strip + 1) / 2) : ((sim_strip + 1) / 2);

            for (int hit_strip = hit_strip_lo; hit_strip < hit_strip_hi + 1; ++hit_strip) {
                // Allow delta of +/-3
                int delta_bx = std::abs(hit_bx - static_cast<int>(sim_bx));
                int delta = std::abs(hit_strip - static_cast<int>(sim_pad));

                if ((delta_bx > 1) || (delta > 3)) {
                    continue;
                }

                // Sim Hit Match 
                sim_hit_id_t match_id(evt_id, sim_trk_id);

                if (matches.find(match_id) == matches.end()) {
                    matches[match_id] = 0.;
                }

                matches[match_id] += 1.0;

                //// Debug
                //std::cout << "Dump GEMDigiSimLink - strip " << linkItr->getStrip() << " hit_bx " << linkItr->getBx()
                //          << " entry " << linkItr->getEntryPoint() << " p4 " << linkItr->getMomentumAtEntry()
                //          << " tof " << linkItr->getTimeOfFlight() << " eloss " << linkItr->getEnergyLoss()
                //          << " pdg " << linkItr->getParticleType() << " process " << linkItr->getProcessType()
                //          << " trackId " << linkItr->getTrackId() << " eventId " << linkItr->getEventId().bunchCrossing()
                //          << ", " << linkItr->getEventId().event() << std::endl;
            }
        }
    }

    return findBestMatch(matches);
}

int SubsystemMCTruth::findTrackingParticleME0(const EMTFHit& hit) const {
    // Short-Circuit: Sim Links not found
    if (me0_digi_sim_links_ == nullptr) {
        return -1;
    }

    // Check all 6 ME0 layers.
    std::map<sim_hit_id_t, float> matches;

    int hit_strip = (hit.strip() >> 1);
    int hit_roll = (hit.wire1() >> 1) + 1;
    int hit_bx = hit.bx();

    for (unsigned layer = 0; layer < 6; ++layer) {
        // Check neighbor rolls
        unsigned roll_first = (hit_roll == 1) ? hit_roll : hit_roll - 1;
        unsigned roll_last = (hit_roll == 8) ? hit_roll : hit_roll + 1;

        for (unsigned roll = roll_first; roll <= roll_last; ++roll) {
            ME0DetId hit_det_id(hit.rawDetId());
            ME0DetId sim_link_det_id(hit_det_id.region(), layer + 1, hit_det_id.chamber(), roll);

            const auto me0_layer_links_it = me0_digi_sim_links_->find(sim_link_det_id);

            if (me0_layer_links_it == me0_digi_sim_links_->end()) {
                continue;
            }

            for (const auto& link : (*me0_layer_links_it)) { // Loop layer sim links in digi
                unsigned int sim_strip = link.getStrip();
                unsigned int sim_bx    = link.getBx();

                const auto& evt_id     = link.getEventId();
                const auto& sim_trk_id = link.getTrackId();

                // Allow delta of +/-3
                int delta_bx = std::abs(hit_bx - static_cast<int>(sim_bx));
                int delta    = std::abs(hit_strip - static_cast<int>(sim_strip));

                if ((delta_bx > 1) || (delta > 3)) {
                    continue;
                }

                // Sim Hit Match 
                sim_hit_id_t match_id(evt_id, sim_trk_id);

                if (matches.find(match_id) == matches.end()) {
                    matches[match_id] = 0.;
                }

                matches[match_id] += 1.0;
            }
        }
    }

    return findBestMatch(matches);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Utils
/////////////////////////////////////////////////////////////////////////////////////////////////
int SubsystemMCTruth::findBestMatch(
        const std::map<sim_hit_id_t, float>& matches
) const {
    // Find the matched TP with the highest weight
    int best_tp_id = -1; // index of the tp
    float best_weight = 0.;

    for (const auto& [match_id, match_weight] : matches) {
        auto found = trk_part_links_.find(match_id);

        if (found == trk_part_links_.end()) {
            continue;
        }

        const auto& tp_id = found->second;

        if (best_weight < match_weight) {
            best_weight = match_weight;
            best_tp_id = tp_id;
        }
    }

    return best_tp_id;
}

