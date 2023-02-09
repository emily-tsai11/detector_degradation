## Detector Degradation Studies for the L1 Track Trigger

Simple plotting scripts for CMS outer tracker detector degradation studies. Ntuples are generated on lxplus, then moved here for analysis. 

### To Run
```
cd macros/
root -l -b <macro name>.cc
```
Note: you may run into an issue opening too many root files with PlotAll.cc

---

### Fail Scenarios
- 0: No dead modules
- 6: 1% random module loss throughout tracker
- 5: 5% random module loss throughout tracker
- 9: 10% random module less throughout tracker
- 8: Kill layer 1 in one quadrant + 1% random module loss
- 2: Kill layer 1 in one quadrant + 5% random module loss
- 3: Kill layer 1 + layer 2, both in same quadrant
- 4: Kill layer 1 + disk 1, both in same quadrant
- 7: Kill layer 5 in one quadrant + 1% random module loss
- 1: Kill layer 5 in one quadrant + 5% random module loss

### Samples
- /RelValTTbar_14TeV/CMSSW_12_6_0_pre4-125X_mcRun4_realistic_v2_2026D88noPU-v1/GEN-SIM-DIGI-RAW
- /RelValTTbar_14TeV/CMSSW_12_6_0_pre4-PU_125X_mcRun4_realistic_v2_2026D88PU200-v1/GEN-SIM-DIGI-RAW

---

### Inefficiency Scenarios
- v1: No inefficiency
- v5: PS-p bias rail inefficiency
- v2: PS-p bias rail inefficiency + 1% bad strips in PS-s and 2S sensors
- v3: PS-p bias rail inefficiency + 5% bad strips in PS-s and 2S sensors
- v4: PS-p bias rail inefficiency + 10% bad strips in PS-s and 2S sensors

### Samples
- /RelValTTbar_14TeV/CMSSW_12_4_0_pre3-PU_123X_mcRun4_realistic_v11_TRK2026D88PU200MB2-v1/GEN-SIM-DIGI-RAW
- /RelValTTbar_14TeV/CMSSW_12_4_0_pre3-PU_123X_mcRun4_realistic_v11_TRK2026D88PU200MB2-v2/GEN-SIM-DIGI-RAW
- /RelValTTbar_14TeV/CMSSW_12_4_0_pre3-PU_123X_mcRun4_realistic_v11_TRK2026D88PU200MB2-v3/GEN-SIM-DIGI-RAW
- /RelValTTbar_14TeV/CMSSW_12_4_0_pre3-PU_123X_mcRun4_realistic_v11_TRK2026D88PU200MB2-v4/GEN-SIM-DIGI-RAW
- /RelValTTbar_14TeV/CMSSW_12_4_0_pre3-PU_123X_mcRun4_realistic_v11_TRK2026D88PU200MB2-v5/GEN-SIM-DIGI-RAW
