# MuonTrackCorr

## Install instructions

From the [PhaseII L1 twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TPhase2Instructions), modified with Osvaldo's PR for the EMTF emulator 

```
cmsrel cmsrel CMSSW_13_3_0_pre3
cd cmsrel CMSSW_13_3_0_pre3/src
cmsenv
git cms-init
git cms-merge-topic -u 43766
# get model files for the EMTF emulator
git clone git clone https://github.com/JanFSchulte/Tau3MuEventGeneration
cp -r Tau3MuEventGeneration/models/data L1Trigger/L1TMuonEndCapPhase2/
# and finally this code
git clone https://github.com/JanFSchulte/MuonTrackCorr.git
scram b -j 8

```

## Run the Ntuplizer

```
cd MuonTrackCorr/MuonTrackCorr/test/
cmsRun ananlyze.py
```

## Submit crab jobs to ntuplize samples

Adjust input dataset and related names in MuonTrackCorr/MuonTrackCorr/test/crab_cfg.py, then do:

```
voms-proxy-init -voms cms
cd MuonTrackCorr/MuonTrackCorr/test/
crab submit crab_cfg.py
```
