import sys


from CRABClient.UserUtilities import config

config = config()

config.JobType.pluginName   = 'Analysis'
config.JobType.outputFiles  = ['TkMuNtuple.root']
config.Data.splitting       = 'EventAwareLumiBased'
config.Data.unitsPerJob       = '2000'

config.section_("Site")
#config.Site.blacklist = ['T2_US_Caltech','T2_US_Florida','T2_US_MIT','T2_US_Nebraska','T2_US_Vanderbilt','T2_US_Wisconsin']
#config.Site.whitelist = ['T2_US_Purdue']
config.Site.storageSite = 'T2_US_Purdue'
# this is needed in order to prevent jobs overflowing to blacklisted sites

config.General.workArea   = "Tau3Mu_PU200"
config.Data.outLFNDirBase = '/store/user/jschulte/Tau3MuNtuples125X/Tau3Mu_PU200/'
config.Data.useParent = True

config.JobType.psetName    = 'analyze.py'
config.General.requestName = "Tau3Mu_PU200"
#config.Data.inputDataset = '/DSTau3Mu_pCut1_14TeV_Pythia8/jschulte-PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2_GEN-SIM-DIGI-RAW`-v1-0b09b1d51eb1b176460746cc4e457a22/USER'
config.Data.inputDataset = '/DsToTauTo3Mu_TuneCP5_14TeV-pythia8/Phase2Fall22DRMiniAOD-PU200_125X_mcRun4_realistic_v2-v1/GEN-SIM-DIGI-RAW-MINIAOD'
#For privately produced samples, uncomment next line
#config.Data.inputDBS = 'phys03'

config.section_("Debug")
config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']

