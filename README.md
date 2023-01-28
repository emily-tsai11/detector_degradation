## Detector Degradation Studies for the L1 Track Trigger

Simple plotting scripts for CMS detector degradation studies. Ntuples are generated on lxplus, then moved here for analysis. 

### To Run
```
cd macros/
root -l -b <macro name>.cc
```

### Fail Scenarios
- 0: No dead modules
- 1: Kill layer 5 in one quadrant + 5% random module loss
- 2: Kill layer 1 in one quadrant + 5% random module loss
- 3: Kill layer 1 + layer 2, both in same quadrant
- 4: Kill layer 1 and disk 1, both in same quadrant
- 5: 5% random module loss throughout tracker
- 6: 1% random module loss throughout tracker
- 7: Kill layer 5 in one quadrant + 1% random module loss
- 8: Kill layer 1 in one quadrant + 1% random module loss

### Samples
- /RelValTTbar_14TeV/CMSSW_12_6_0_pre4-125X_mcRun4_realistic_v2_2026D88noPU-v1/GEN-SIM-DIGI-RAW
- /RelValTTbar_14TeV/CMSSW_12_6_0_pre4-PU_125X_mcRun4_realistic_v2_2026D88PU200-v1/GEN-SIM-DIGI-RAW
