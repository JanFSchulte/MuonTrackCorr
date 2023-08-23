# MuonTrackCorr

## Install instructions

From the [PhaseII L1 twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TPhase2Instructions)

```
cmsrel CMSSW_12_5_2_patch1
cd CMSSW_12_5_2_patch1/src
cmsenv
git cms-init
git cms-checkout-topic -u cms-l1t-offline:phase2-l1t-integration-1252patch1
scram b -j 8

git cms-addpkg  L1Trigger/TrackTrigger
git cms-addpkg SimTracker/TrackTriggerAssociation

#latest EMTF++ data formats from development repositories
git clone https://gitlab.com/rice-acosta-group/emtfpp/l1triggerl1muonendcapphase2 L1Trigger/L1TMuonEndCapPhase2/
rm -r DataFormats/L1TMuonPhase2
git clone https://gitlab.com/rice-acosta-group/emtfpp/dataformatsl1tmuonphase2 DataFormats/L1TMuonPhase2

# and finally this code
git clone https://github.com/JanFSchulte/MuonTrackCorr.git

scram b -j8
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
