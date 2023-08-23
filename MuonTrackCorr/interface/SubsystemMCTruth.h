#ifndef MuonTrackCorr_MuonTrackCorr_SubsystemMCTruth_h
#define MuonTrackCorr_MuonTrackCorr_SubsystemMCTruth_h

#include <cassert>
#include <cstdint>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include "Geometry/GEMGeometry/interface/ME0Geometry.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "SimDataFormats/TrackerDigiSimLink/interface/StripDigiSimLink.h"
#include "SimDataFormats/RPCDigiSimLink/interface/RPCDigiSimLink.h"
#include "SimDataFormats/GEMDigiSimLink/interface/GEMDigiSimLink.h"
#include "SimDataFormats/GEMDigiSimLink/interface/ME0DigiSimLink.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"

// Forward declarations
namespace l1t::phase2 {
    class EMTFHit;
}  // namespace l1t


        class SubsystemMCTruth {
            public:
                // Typedefs
                typedef l1t::phase2::EMTFHit                EMTFHit;
                typedef edm::DetSetVector<StripDigiSimLink> StripDigiSimLinks;
                typedef edm::DetSetVector<StripDigiSimLink> WireDigiSimLinks;
                typedef edm::DetSetVector<RPCDigiSimLink>   RPCDigiSimLinks;
                typedef edm::DetSetVector<GEMDigiSimLink>   GEMDigiSimLinks;
                typedef edm::DetSetVector<ME0DigiSimLink>   ME0DigiSimLinks;
                typedef std::pair<EncodedEventId, uint32_t> sim_hit_id_t;

                SubsystemMCTruth(const edm::ParameterSet&, edm::ConsumesCollector&&);

                ~SubsystemMCTruth();

                // Fetch event data
                void update(const edm::Event&, const edm::EventSetup&);

                // Find the matching tracking particle and return its index
                std::pair<int, int> findTrackingParticlesFromEMTFHit(const EMTFHit&) const;
                int findTrackingParticleFromSimHit(const PSimHit&) const;

            private:
                int findTrackingParticleCSCStrip(const EMTFHit&) const;
                int findTrackingParticleCSCWire(const EMTFHit&) const;
                int findTrackingParticleRPC(const EMTFHit&) const;
                int findTrackingParticleGEM(const EMTFHit&) const;
                int findTrackingParticleME0(const EMTFHit&) const;
                int findBestMatch(
                        const std::map<sim_hit_id_t, float>&
                ) const;

                // Enables
                bool csc_enable_;
                bool rpc_enable_;
                bool gem_enable_;
                bool me0_enable_;

                // Tokens
                edm::EDGetTokenT<TrackingParticleCollection> trk_part_token_;
                edm::EDGetTokenT<StripDigiSimLinks>          csc_strip_sim_links_token_;
                edm::EDGetTokenT<WireDigiSimLinks>           csc_wire_sim_links_token_;
                edm::EDGetTokenT<RPCDigiSimLinks>            rpc_digi_sim_links_token_;
                edm::EDGetTokenT<GEMDigiSimLinks>            gem_digi_sim_links_token_;
                edm::EDGetTokenT<ME0DigiSimLinks>            me0_digi_sim_links_token_;

                // SimLinks
                std::map<sim_hit_id_t, int> trk_part_links_;
                const StripDigiSimLinks*    csc_strip_sim_links_;
                const WireDigiSimLinks*     csc_wire_sim_links_;
                const RPCDigiSimLinks*      rpc_digi_sim_links_;
                const GEMDigiSimLinks*      gem_digi_sim_links_;
                const ME0DigiSimLinks*      me0_digi_sim_links_;
        };


#endif  // MuonTrackCorr_MuonTrackCorr_SubsystemMCTruth_h not defined
