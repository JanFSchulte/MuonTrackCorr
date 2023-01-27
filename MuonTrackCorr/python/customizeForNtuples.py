import FWCore.ParameterSet.Config as cms

def customizeForNtuples(process):

    process.Ntuplizer = cms.EDAnalyzer("Ntuplizer",
        # L1MuonPosInputTag = cms.InputTag("simGmtStage2Digis", "imdMuonsEMTFPos", "HLT"),
        # L1MuonNegInputTag = cms.InputTag("simGmtStage2Digis", "imdMuonsEMTFNeg", "HLT"),
        # L1TrackInputTag   = cms.InputTag("TTStubsFromPhase2TrackerDigis", "ClusterAccepted", "HLT"), # or ClusterInclusive ?
        TkMuInputTag        = cms.InputTag("l1tTkMuonsGmt"),
        #TkMuStubInputTag        = cms.InputTag("l1tGMTStubs"),
        L1MuonEMTFInputTag  = cms.InputTag("simEmtfDigis"),
        L1EMTFHitInputTag   = cms.InputTag("simEmtfDigis"),
        L1TrackInputTag     = cms.InputTag("l1tTTTracksFromExtendedTrackletEmulation","Level1TTTracks"),
        L1TrackTruthInputTag  = cms.InputTag("l1tTTTrackAssociatorFromPixelDigisExtended","Level1TTTracks"),
        GenParticleInputTag = cms.InputTag("genParticles"),
        L1BarrelMuonInputTag = cms.InputTag("simBmtfDigis","BMTF"),
        L1OverlapMuonInputTag = cms.InputTag("simOmtfDigis","OMTF"),
        SimTrackInputTag = cms.InputTag("g4SimHits"),
        # for DT Hit associator
        crossingframe = cms.bool(False),
        simtracksTag = cms.InputTag("g4SimHits"),
        simtracksXFTag = cms.InputTag("mix","g4SimHits"),
        #
        DTsimhitsTag = cms.InputTag("g4SimHits","MuonDTHits"),
        DTsimhitsXFTag = cms.InputTag("mix","g4SimHitsMuonDTHits"),
        DTdigiTag = cms.InputTag("simMuonDTDigis"),
        DTdigisimlinkTag = cms.InputTag("simMuonDTDigis"),
        DTrechitTag = cms.InputTag("dt1DRecHits"),
        #
        dumpDT = cms.bool(False),
        links_exist = cms.bool(True),
        associatorByWire = cms.bool(False),
        #
        # for CSC Hit associator
        CSCsimHitsTag = cms.InputTag("g4SimHits","MuonCSCHits"),
        CSCsimHitsXFTag = cms.InputTag("mix","g4SimHitsMuonCSCHits"),
        CSClinksTag = cms.InputTag("simMuonCSCDigis","MuonCSCStripDigiSimLinks"),
        CSCwireLinksTag = cms.InputTag("simMuonCSCDigis","MuonCSCWireDigiSimLinks"),
        #
        # for RPC Hit associator
        RPCsimhitsTag = cms.InputTag("g4SimHits","MuonRPCHits"),
        RPCsimhitsXFTag = cms.InputTag("mix","g4SimHitsMuonRPCHits"),
        RPCdigisimlinkTag = cms.InputTag("simMuonRPCDigis","RPCDigiSimLink"),
        #
        # for GEM Hit associator
        useGEMs = cms.bool(False),
        GEMsimhitsTag = cms.InputTag("g4SimHits","MuonGEMHits"),
        GEMsimhitsXFTag = cms.InputTag("mix","g4SimHitsMuonGEMHits"),
        GEMdigisimlinkTag = cms.InputTag("simMuonGEMDigis","GEM"),

        save_all_L1TTT = cms.bool(True),
        prompt_mu_only = cms.bool(True),
        mu_from_tau_only = cms.bool(False),
        save_tau_3mu = cms.bool(True),
    )

    process.Ntuples = cms.Path(
        process.Ntuplizer
    )
    process.TFileService = cms.Service("TFileService",
          fileName = cms.string("TkMuNtuple.root"),
          closeFileFast = cms.untracked.bool(True)
    )
   
    process.schedule.insert(2, process.Ntuples)

    return process
