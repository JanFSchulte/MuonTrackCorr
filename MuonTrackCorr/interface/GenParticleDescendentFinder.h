#ifndef MuonTrackCorr_MuonTrackCorr_GenParticleDescendentFinder_h
#define MuonTrackCorr_MuonTrackCorr_GenParticleDescendentFinder_h

#include <cassert>
#include <vector>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"


    class GenParticleDescendentFinder {
        public:
            typedef reco::GenParticleRefVector::key_type key_t;  // should be unsigned int

            GenParticleDescendentFinder(const edm::ParameterSet&, edm::ConsumesCollector&);

            ~GenParticleDescendentFinder();

            void update(const edm::Event&, const edm::EventSetup&);

            // Check if GenParticle (given by its index) descends from W/Z/H
            bool isImportant(key_t index) const;

        private:
            // Tokens
            edm::EDGetTokenT<reco::GenParticleCollection> gen_part_token_;
            const reco::GenParticleCollection*            gen_part_col_;

            void recursiveFlagDaughters(
                    key_t, const bool&, std::vector<key_t>&
            );

            std::vector<bool> flags_;
    };


#endif  // MuonTrackCorr_MuonTrackCorr_GenParticleDescendentFinder_h not defined
