SUFFIX_TAG="ntuplesnew"

echo "... preparing the submission (tar and copy of CMSSW)"
python submitOnTier3.py --xrdcp-tar-only  --tar-suffix $SUFFIX_TAG
echo ".. done, launching"


#THE NEW GENERATED SAMPLES by Jan
#python submitOnTier3.py --filelist filelist/Ds_to_Tau3Mu_pythia8_PU0_nocut_Sep2022.txt  --tag Ds_to_Tau3Mu_pythia8_PU0_nocut_Sep2022_${SUFFIX_TAG}  --save-tau-3mu --all-gen-mu --only-mu-from-tau  --njobs 100 --no-tar --no-xrdcp-tar --tar-suffix $SUFFIX_TAG --cmsRunCfg 'analyze_MTD_MC.py'
#python submitOnTier3.py --filelist filelist/TauGun_Tau3Mu_pythia8_PU0_nocut_Sep2022.txt  --tag TauGun_Tau3Mu_pythia8_PU0_nocut_Sep2022_${SUFFIX_TAG}  --save-tau-3mu --all-gen-mu --only-mu-from-tau  --njobs 100 --no-tar --no-xrdcp-tar --tar-suffix $SUFFIX_TAG --cmsRunCfg 'analyze_MTD_MC.py'
python submitOnTier3.py --filelist filelist/Ds_to_Tau3Mu_pythia8_PU200_cut1_Sep2022.txt  --tag Ds_to_Tau3Mu_pythia8_PU200_cut1_Sep2022_${SUFFIX_TAG}  --save-tau-3mu --all-gen-mu --only-mu-from-tau  --njobs 400 --no-tar --no-xrdcp-tar --tar-suffix $SUFFIX_TAG --cmsRunCfg 'analyze_MTD_MC.py'