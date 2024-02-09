# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step1 --conditions 125X_mcRun4_realistic_v2 -n 2 --era Phase2C17I13M9 --eventcontent FEVTDEBUGHLT -s RAW2DIGI,L1TrackTrigger,L1 --datatier GEN-SIM-DIGI-RAW-MINIAOD --fileout file:test.root --customise SLHCUpgradeSimulations/Configuration/aging.customise_aging_1000,Configuration/DataProcessing/Utils.addMonitoring,L1Trigger/Configuration/customisePhase2.addHcalTriggerPrimitives,L1Trigger/Configuration/customisePhase2FEVTDEBUGHLT.customisePhase2FEVTDEBUGHLT,L1Trigger/Configuration/customisePhase2TTNoMC.customisePhase2TTNoMC --geometry Extended2026D88 --nThreads 8 --filein /store/mc/Phase2Fall22DRMiniAOD/TT_TuneCP5_14TeV-powheg-pythia8/GEN-SIM-DIGI-RAW-MINIAOD/PU200_125X_mcRun4_realistic_v2_ext1-v1/30000/000c5e5f-78f7-44ee-95fe-7b2f2c2e2312.root --mc
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Phase2C17I13M9_cff import Phase2C17I13M9

process = cms.Process('L1',Phase2C17I13M9)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2026D88Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2026D88_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedHLLHC14TeV_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.L1TrackTrigger_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet),
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring( (
#      '/store/mc/Phase2Fall22DRMiniAOD/TT_TuneCP5_14TeV-powheg-pythia8/GEN-SIM-DIGI-RAW-MINIAOD/PU200_125X_mcRun4_realistic_v2_ext1-v1/30000/000c5e5f-78f7-44ee-95fe-7b2f2c2e2312.root'
        #'file:/depot/cms/users/schul105/Tau3Mu/production/CMSSW_12_5_2_patch1/src/DsTau3Mu-GEN-SIM-DIGI-RAW.root'
        'file:../../../Tau3Mu_GEN-SIM-DIGI-RAW_PU0.root'
    #    '/store/user/jschulte/DSTau3Mu_pCut1_14TeV_Pythia8/Phase2Fall22DRMiniAOD-PU200_125X_mcRun4_realistic_v2_GEN-SIM-DIGI-RAW-v2/240115_165556/0000/DsTau3Mu-GEN-SIM-DIGI-RAW_PUValid_10.root'
     ) ),
    secondaryFileNames = cms.untracked.vstring(),
                           # skipEvents=cms.untracked.uint32(58)
)

process.options = cms.untracked.PSet(
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
    accelerators = cms.untracked.vstring('*'),
    allowUnscheduled = cms.obsolete.untracked.bool,
    canDeleteEarly = cms.untracked.vstring(),
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True),
    dumpOptions = cms.untracked.bool(False),
    emptyRunLumiMode = cms.obsolete.untracked.string,
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(
            allowAnyLabel_=cms.required.untracked.uint32
        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(1)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    makeTriggerResults = cms.obsolete.untracked.bool,
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(1),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(1),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('EMTFTools/ParticleGuns/python/SingleMuon_PosEnd_2GeV_cfi.py nevts:1000'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('FEVTDEBUGHLT'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('reprocess.root'),
    # outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    outputCommands = cms.untracked.vstring( "keep *_*_*_*"),
    splitLevel = cms.untracked.int32(0)
)


# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '131X_mcRun4_realistic_v5', '')

process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1TrackTrigger_step = cms.Path(process.L1TrackTrigger)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

process.Ntuplizer = cms.EDAnalyzer("Ntuplizer",
    TkMuInputTag        = cms.InputTag("l1tTkMuonsGmt"),
    MuStubInputTag        = cms.InputTag("l1tTkStubsGmt"),
    L1MuonEMTFInputTag  = cms.InputTag("simEmtfDigisPhase2"),
    L1EMTFHitInputTag   = cms.InputTag("simEmtfDigisPhase2"),
    L1TrackInputTag = cms.InputTag('l1tTTTracksFromTrackletEmulation', 'Level1TTTracks'),
    L1TrackTruthInputTag = cms.InputTag('TTTrackAssociatorFromPixelDigis', 'Level1TTTracks'),

    GenParticleInputTag = cms.InputTag("genParticles"),
    L1BarrelMuonInputTag = cms.InputTag("simBmtfDigis","BMTF"),
    L1OverlapMuonInputTag = cms.InputTag("simOmtfDigis","OMTF"),
    SimTrackInputTag = cms.InputTag("g4SimHits"),
   
    save_all_L1TTT = cms.bool(True),
    prompt_mu_only = cms.bool(False),
    mu_from_tau_only = cms.bool(True),
    save_tau_3mu = cms.bool(True),
    CSCSimHitEnabled = cms.bool(True),
    RPCSimHitEnabled = cms.bool(True),
    GEMSimHitEnabled = cms.bool(True),
    ME0SimHitEnabled = cms.bool(False),
    TrkPartTag = cms.InputTag('mix', 'MergedTrackTruth'),
    CSCStripSimLinksTag = cms.InputTag('simMuonCSCDigis', 'MuonCSCStripDigiSimLinks'),
    CSCWireSimLinksTag  = cms.InputTag('simMuonCSCDigis', 'MuonCSCWireDigiSimLinks'),
    RPCDigiSimLinksTag  = cms.InputTag('simMuonRPCDigis', 'RPCDigiSimLink'),
    GEMDigiSimLinksTag  = cms.InputTag('simMuonGEMDigis', 'GEM'),
    ME0DigiSimLinksTag  = cms.InputTag('simMuonME0Digis', 'ME0'),    
)

process.Ntuples = cms.Path(
    process.Ntuplizer
)

outputFileName = "TkMuNtuple.root"
process.TFileService = cms.Service('TFileService',
    fileName = cms.string(outputFileName)
)



# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1TrackTrigger_step,process.L1simulation_step,process.endjob_step,process.Ntuples)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
#process.options.numberOfThreads = 8
# process.options.numberOfStreams = 0

# customisation of the process.

# Automatic addition of the customisation function from SimGeneral.MixingModule.customiseStoredTPConfig
from SimGeneral.MixingModule.customiseStoredTPConfig import higherPtTP

#call to customisation function higherPtTP imported from SimGeneral.MixingModule.customiseStoredTPConfig
process = higherPtTP(process)

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.aging
from SLHCUpgradeSimulations.Configuration.aging import customise_aging_1000

#call to customisation function customise_aging_1000 imported from SLHCUpgradeSimulations.Configuration.aging
process = customise_aging_1000(process)

# Automatic addition of the customisation function from L1Trigger.Configuration.customisePhase2TTOn110
from L1Trigger.Configuration.customisePhase2TTOn110 import customisePhase2TTOn110

#call to customisation function customisePhase2TTOn110 imported from L1Trigger.Configuration.customisePhase2TTOn110
process = customisePhase2TTOn110(process)

# Automatic addition of the customisation function from L1Trigger.L1TMuonEndCapPhase2.config
from L1Trigger.L1TMuonEndCapPhase2.config import customise_mc

#call to customisation function customise_mc imported from L1Trigger.L1TMuonEndCapPhase2.config
process = customise_mc(process)

process.gemRecHits.gemDigiLabel = 'simMuonGEMDigis'
# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
