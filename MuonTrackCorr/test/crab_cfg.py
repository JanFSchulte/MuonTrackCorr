import sys


from CRABClient.UserUtilities import config

config = config()

config.JobType.pluginName   = 'Analysis'
config.JobType.outputFiles  = ['TkMuNtuple_eras_muonly_wtkmus.root']
config.Data.splitting       = 'EventAwareLumiBased'
config.Data.unitsPerJob       = '2000'

config.section_("Site")
config.Site.blacklist = ['T2_US_Caltech','T2_US_Florida','T2_US_MIT','T2_US_Nebraska','T2_US_Vanderbilt','T2_US_Wisconsin']
config.Site.whitelist = ['T2_US_Purdue']
config.Site.storageSite = 'T2_US_Purdue'
# this is needed in order to prevent jobs overflowing to blacklisted sites

config.General.workArea   = "DSTau3Mu_pCut1_part3"
config.Data.outLFNDirBase = '/store/user/jschulte/Tau3MuNtuples/DSTau3Mu_pCut1_part3_offlineAOD'
config.Data.useParent = True

config.JobType.psetName    = 'analyze_MTD_MC_AOD.py'
config.General.requestName = "DSTau3Mu_pCut1_part3_offlineAOD"
#config.Data.inputDataset = '/DSTau3Mu_pCut1_14TeV_Pythia8/jschulte-PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2_GEN-SIM-DIGI-RAW`-v1-0b09b1d51eb1b176460746cc4e457a22/USER'
config.Data.inputDataset = '/DSTau3Mu_pCut1_14TeV_Pythia8/jschulte-PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2_AODSIM_part3-v1-29a4743688bcbc5edaf8475987a7a405/USER'
config.Data.inputDBS = 'phys03'
config.Data.outputDatasetTag   = "DSTau3Mu_pCut1_part3_offlineAOD"

config.section_("Debug")
config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']

