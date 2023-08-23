#include <algorithm>
#include <iostream>

#include "MuonTrackCorr/MuonTrackCorr/interface/GenParticleDescendentFinder.h"


GenParticleDescendentFinder::GenParticleDescendentFinder(
        const edm::ParameterSet& pset, 
        edm::ConsumesCollector& consumes_collector
) {
    // Get Tokens 
    gen_part_token_  = consumes_collector.consumes<reco::GenParticleCollection>(
            pset.getParameter<edm::InputTag>("GenPartTag")  
    );
}

GenParticleDescendentFinder::~GenParticleDescendentFinder() {
    // Do Nothing
}

void GenParticleDescendentFinder::update(const edm::Event& evt, const edm::EventSetup& evt_setup) {
    // Get Gen Particles
    auto gen_part_col_handle = evt.getHandle(gen_part_token_);
    gen_part_col_            = gen_part_col_handle.product();

    // Descend
    bool keep_or_drop_all = false;
    bool keep_or_drop = true;
    
    flags_.clear();
    flags_.resize(gen_part_col_->size(), keep_or_drop_all);

    key_t primary_index = 0;
    
    for (const auto& gen_part : (*gen_part_col_)) {
        // Flag W/Z/H descendents
        int pdg_id = std::abs(gen_part.pdgId());

        if ((pdg_id == 23) or (pdg_id == 24) or (pdg_id == 25) or (pdg_id == 37)) {
            std::vector<key_t> visited;

            flags_.at(primary_index) = keep_or_drop;

            recursiveFlagDaughters(primary_index, keep_or_drop, visited);
        }

        // Increase Primary Index
        ++primary_index;
    }
}

void GenParticleDescendentFinder::recursiveFlagDaughters(
        key_t mother_index,
        const bool& keep_or_drop,
        std::vector<key_t>& visited
) {
    const auto& daughters = (*gen_part_col_)[mother_index].daughterRefVector();

    for (const auto& daughter : daughters) {
        auto daughter_index = daughter.key();

        // Short-Circuit: Make sure the daughter index hasn't already been added.
        if (std::find(visited.begin(), visited.end(), daughter_index) != visited.end()) {
            continue;
        }

        visited.push_back(daughter_index);

        // Short-Circuit: Avoid infinite recursion if the daughters are set to "this" particle.
        if (mother_index == daughter_index) {
            continue;
        }

        flags_.at(daughter_index) = keep_or_drop;
        recursiveFlagDaughters(daughter_index, keep_or_drop, visited);
    }
}

bool GenParticleDescendentFinder::isImportant(key_t index) const {
    return flags_.at(index); 
}
