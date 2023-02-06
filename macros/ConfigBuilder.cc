#include "../include/ConfigBuilder.hh"


void ConfigBuilder() {

  if(SAMPLE == 0 || SAMPLE == 1) DefineStubKillerConstants();
  else if(SAMPLE == 2) DefineBiasRailConstants();

  configHasRun = true;
}


void DefineStubKillerConstants() {

  if(SAMPLE == 0) {
    N_SAMPLE = "TTbar_PU200_D88";
    LATEX_SAMPLE = "t#bar{t}, PU 200, D88";

    LX1 = 0.18;
    LX2 = 0.38;
    TX = 0.17;
  }
  else if(SAMPLE == 1) {
    N_SAMPLE = "TTbar_noPU_D88";
    LATEX_SAMPLE = "t#bar{t}, no PU, D88";

    LX1 = 0.62;
    LX2 = 0.9;
    TX = 0.7;
  }

  N_SAVE = "f";

  F_REF = "../results/" + N_SAMPLE + "_f0e9000/output_" + N_SAMPLE + ".root";

  F_FAILS = {
    "",
    "../results/" + N_SAMPLE + "_f1e9000/output_" + N_SAMPLE + ".root",
    "../results/" + N_SAMPLE + "_f2e9000/output_" + N_SAMPLE + ".root",
    "../results/" + N_SAMPLE + "_f3e9000/output_" + N_SAMPLE + ".root",
    "../results/" + N_SAMPLE + "_f4e9000/output_" + N_SAMPLE + ".root",
    "../results/" + N_SAMPLE + "_f5e9000/output_" + N_SAMPLE + ".root",
    "../results/" + N_SAMPLE + "_f6e9000/output_" + N_SAMPLE + ".root",
    "../results/" + N_SAMPLE + "_f7e9000/output_" + N_SAMPLE + ".root",
    "../results/" + N_SAMPLE + "_f8e9000/output_" + N_SAMPLE + ".root",
    "../results/" + N_SAMPLE + "_f9e9000/output_" + N_SAMPLE + ".root"
  };

  LATEX_FAILS = {
    "No dead modules",   // 0
    "Kill L5 + 5% loss", // 1
    "Kill L1 + 5% loss", // 2
    "Kill L1 + L2",      // 3
    "Kill L1 + D1",      // 4
    "5% loss",           // 5
    "1% loss",           // 6
    "Kill L5 + 1% loss", // 7
    "Kill L1 + 1% loss", // 8
    "10% loss"           // 9
  };

  CASES = {
    {"1loss", {6, 8, 7}},
    {"5loss", {5, 2, 1}},
    {"killL1", {8, 2, 3, 4}},
    {"killL5", {7, 1}},
    {"ploss", {6, 5, 9}}
  };

  COLOR = {1, 9, 2, 8, 63, 15, 94, 6, 221, 226};
}


void DefineBiasRailConstants() {

  N_SAMPLE = "TRK2026D88PU200MB2";

  LATEX_SAMPLE = "t#bar{t}, PU 200, D88";

  LX1 = 0.18;
  LX2 = 0.38;
  TX = 0.17;

  N_SAVE = "v";

  F_REF = "../results/" + N_SAMPLE + "-v1_f0e8600/output_" + N_SAMPLE + "-v1.root";

  F_FAILS = {
    "",
    "",
    "../results/" + N_SAMPLE + "-v2_f0e9000/output_" + N_SAMPLE + "-v2.root",
    "../results/" + N_SAMPLE + "-v3_f0e8800/output_" + N_SAMPLE + "-v3.root",
    "../results/" + N_SAMPLE + "-v4_f0e9000/output_" + N_SAMPLE + "-v4.root",
    "../results/" + N_SAMPLE + "-v5_f0e9000/output_" + N_SAMPLE + "-v5.root"
  };

  LATEX_FAILS = {
    "No inefficiency", // 0
    "",
    "biasRail1pc",     // 2
    "biasRail5pc",     // 3
    "biasRail10pc",    // 4
    "biasRail"         // 5
  };

  CASES = {
    {"ploss", {5, 2, 3, 4}}
  };

  COLOR = {-1, 1, 94, 15, 226, 9};
}
