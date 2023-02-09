#ifndef CONFIG_BUILDER
#define CONFIG_BUILDER


std::string N_SAMPLE;
std::string LATEX_SAMPLE;
std::vector<std::string> F_FAILS;
std::vector<std::string> LATEX_FAILS;
std::vector<int> N_EVENTS;
std::vector<string> N_CASES;
std::vector<string> CASES;
std::vector<int> COLOR;
std::string N_SAVE;


// PlotNTrkPt2
double NTRK_PT2_LX1;
double NTRK_PT2_LX2;
double NTRK_PT2_LMEANX1;
double NTRK_PT2_LMEANX2;
double NTRK_PT2_MAX_ZOOM;

// PlotNTrkPt2
double NTRK_PT3_MAX_ZOOM;

// Plot track quality variables
double TRK_CHI2_MAX;
double TRK_CHI2DOF_MAX;
double TRK_CHI2RPHI_MAX;
double TRK_CHI2RPHIDOF_MAX;
double TRK_CHI2RZ_MAX;
double TRK_CHI2RZDOF_MAX;
double TRK_BENDCHI2_MAX;


// PlotEffEta
double EFF_ETA_MIN = 0.65;
double EFF_ETA_MAX = 1.05;

// PlotEffPt
double EFF_PT_MIN = 0.45;
double EFF_PT_MAX = 1.05;

// PlotEffD0
double EFF_D0_MIN = 0.0;
double EFF_D0_MAX = 1.1;

// PlotEffZ0
double EFF_Z0_MIN = 0.0;
double EFF_Z0_MAX = 1.1;

// PlotEffPhi
double EFF_PHI_MIN = 0.45;
double EFF_PHI_MAX = 1.05;

// Efficiency ratio plots
double RATIO_MIN = 0.6;
double RATIO_MAX = 1.2;

// Efficiency plot legend
double EFF_LX1 = 0.58;
double EFF_LY1 = 0.02;
double EFF_LX2 = 0.83;
double EFF_LY2 = 0.32;

// Efficiency plot small text
double EFF_TX = 0.8;
double EFF_TY = 0.96;

// Track quality plot legend
double TRK_LX1 = 0.55;
double TRK_LY1 = 0.65;
double TRK_LX2 = 0.9;
double TRK_LY2 = 0.9;

// Small text
double TX = 0.75;
double TY = 0.95;


bool stubKiller0Set = 0;
bool stubKiller1Set = 0;
bool biasRailSet = 0;


void ClearConfig();
void DefineStubKillerConstants(int s);
void DefineBiasRailConstants();
void GetCases();


void ConfigBuilder(int sample) {

  ClearConfig();

  if(sample == 0 || sample == 1) DefineStubKillerConstants(sample);
  else if(sample == 2) DefineBiasRailConstants();
}


void ClearConfig() {

  F_FAILS.clear();
  N_EVENTS.clear();
  LATEX_FAILS.clear();
  N_CASES.clear();
  CASES.clear();
  COLOR.clear();
}


void DefineStubKillerConstants(int s) {

  if(s == 0) {

    N_SAMPLE = "TTbar_PU200_D88";
    LATEX_SAMPLE = "t#bar{t}, PU 200, D88";

    NTRK_PT2_LX1 = 0.17;
    NTRK_PT2_LX2 = 0.3;
    NTRK_PT2_LMEANX1 = 0.15;
    NTRK_PT2_LMEANX2 = 0.35;
    NTRK_PT2_MAX_ZOOM = -1;

    NTRK_PT3_MAX_ZOOM = -1;

    TRK_CHI2_MAX = 180000;
    TRK_CHI2DOF_MAX = 260000;
    TRK_CHI2RPHI_MAX = 400000;
    TRK_CHI2RPHIDOF_MAX = 520000;
    TRK_CHI2RZ_MAX = 330000;
    TRK_CHI2RZDOF_MAX = 470000;
    TRK_BENDCHI2_MAX = 290000;

    stubKiller0Set = 1;
    stubKiller1Set = 0;
    biasRailSet = 0;
  }
  else if(s == 1) {

    N_SAMPLE = "TTbar_noPU_D88";
    LATEX_SAMPLE = "t#bar{t}, no PU, D88";

    NTRK_PT2_LX1 = 0.62;
    NTRK_PT2_LX2 = 0.9;
    NTRK_PT2_LMEANX1 = 0.75;
    NTRK_PT2_LMEANX2 = 0.95;
    NTRK_PT2_MAX_ZOOM = 100;

    NTRK_PT3_MAX_ZOOM = 80;

    TRK_CHI2_MAX = 26000;
    TRK_CHI2DOF_MAX = 37000;
    TRK_CHI2RPHI_MAX = 48000;
    TRK_CHI2RPHIDOF_MAX = 65000;
    TRK_CHI2RZ_MAX = 54000;
    TRK_CHI2RZDOF_MAX = 78000;
    TRK_BENDCHI2_MAX = 52000;

    stubKiller0Set = 0;
    stubKiller1Set = 1;
    biasRailSet = 0;
  }

  F_FAILS = {
    "../results/" + N_SAMPLE + "_f0e9000/output_" + N_SAMPLE + ".root",
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

  N_EVENTS = {9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};

  N_CASES = {
    "1loss",
    "5loss",
    "killL1",
    "killL5",
    "ploss"
  };
  CASES = {
    "6_8_7",
    "5_2_1",
    "8_2_3_4",
    "7_1",
    "6_5_9"
  };

  COLOR = {1, 9, 15, 8, 63, 2, 94, 6, 221, 226};

  N_SAVE = "f";
}


void DefineBiasRailConstants() {

  N_SAMPLE = "TRK2026D88PU200MB2";
  LATEX_SAMPLE = "t#bar{t}, PU 200, D88";

  F_FAILS = { // F_FAILS[1] not used
    "../results/" + N_SAMPLE + "-v1_f0e8600/output_" + N_SAMPLE + "-v1.root",
    "",
    "../results/" + N_SAMPLE + "-v2_f0e9000/output_" + N_SAMPLE + "-v2.root",
    "../results/" + N_SAMPLE + "-v3_f0e8800/output_" + N_SAMPLE + "-v3.root",
    "../results/" + N_SAMPLE + "-v4_f0e9000/output_" + N_SAMPLE + "-v4.root",
    "../results/" + N_SAMPLE + "-v5_f0e9000/output_" + N_SAMPLE + "-v5.root"
  };
  LATEX_FAILS = {
    "No inefficiency",      // 0
    "",
    "Bias rail + 1% loss",  // 2
    "Bias rail + 5% loss",  // 3
    "Bias rail + 10% loss", // 4
    "Bias rail"             // 5
  };

  N_EVENTS = {8600, -1, 9000, 8800, 9000, 9000}; // N_EVENTS[1] not used

  N_CASES = {
    "ploss"
  };
  CASES = {
    "5_2_3_4"
  };

  COLOR = {-1, 1, 94, 2, 226, 9}; // COLOR[0] not used

  N_SAVE = "v";

  NTRK_PT2_LX1 = 0.17;
  NTRK_PT2_LX2 = 0.3;
  NTRK_PT2_LMEANX1 = 0.15;
  NTRK_PT2_LMEANX2 = 0.35;
  NTRK_PT2_MAX_ZOOM = -1;

  NTRK_PT3_MAX_ZOOM = -1;

  TRK_CHI2_MAX = 175000;
  TRK_CHI2DOF_MAX = 250000;
  TRK_CHI2RPHI_MAX = 380000;
  TRK_CHI2RPHIDOF_MAX = 500000;
  TRK_CHI2RZ_MAX = 320000;
  TRK_CHI2RZDOF_MAX = 470000;
  TRK_BENDCHI2_MAX = 280000;

  stubKiller0Set = 0;
  stubKiller1Set = 0;
  biasRailSet = 1;
}


void GetCases(std::string& s, std::vector<int>& cases) {

  std::string delimiter = "_";
  std::string token;
  int pos = 0;
  while((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    cases.push_back(stoi(token));
    s.erase(0, pos + delimiter.length());
  }
  cases.push_back(stoi(s));
}


#endif
