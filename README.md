# MuonTrackCorr

## Install instructions
From the [PhaseII L1 twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TPhase2Instructions)
```
# get phase-2 L1trigger code
cmsrel CMSSW_10_6_1_patch2
cd CMSSW_10_6_1_patch2/src/
cmsenv
git cms-init
git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline phase2-l1t-integration-CMSSW_10_6_1_patch2
git cms-merge-topic -u cms-l1t-offline:l1t-phase2-v2.37.2
git cms-addpkg L1Trigger/L1TCommon

# and finally the ntuplizer code
git clone https://github.com/cms-p2l1trigger-tau3mu/MuonTrackCorr.git
# compile code
scram b -j 4
```