#ifndef CONFIG_BUILDER
#define CONFIG_BUILDER


std::string N_SAMPLE;
std::string LATEX_SAMPLE;

// The following is for PlotNTrkPt2 only
double LX1;
double LX2;
double TX;

std::string N_SAVE;
std::string F_REF;
std::vector<std::string> F_FAILS;
std::vector<int> N_EVENTS;
std::vector<std::string> LATEX_FAILS;
std::vector<string> N_CASES;
std::vector<string> CASES;
std::vector<int> COLOR;

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

    LX1 = 0.18;
    LX2 = 0.38;
    TX = 0.17;

    stubKiller0Set = 1;
    stubKiller1Set = 0;
    biasRailSet = 0;
  }
  else if(s == 1) {

    N_SAMPLE = "TTbar_noPU_D88";
    LATEX_SAMPLE = "t#bar{t}, no PU, D88";

    LX1 = 0.62;
    LX2 = 0.9;
    TX = 0.7;

    stubKiller0Set = 0;
    stubKiller1Set = 1;
    biasRailSet = 0;
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

  N_EVENTS = {9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};

  LATEX_FAILS = {
    "No dead modules",          // 0
    "Kill L5 + 5% module loss", // 1
    "Kill L1 + 5% module loss", // 2
    "Kill L1 + L2",             // 3
    "Kill L1 + D1",             // 4
    "5% module loss",           // 5
    "1% module loss",           // 6
    "Kill L5 + 1% module loss", // 7
    "Kill L1 + 1% module loss", // 8
    "10% module loss"           // 9
  };

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

  N_EVENTS = {8600, -1, 9000, 8800, 9000, 9000}; // N_EVENTS[1] not used

  LATEX_FAILS = {
    "No inefficiency",            // 0
    "",
    "Bias rail + 1% bad strips",  // 2
    "Bias rail + 5% bad strips",  // 3
    "Bias rail + 10% bad strips", // 4
    "Bias rail"                   // 5
  };

  N_CASES = {
    "ploss"
  };

  CASES = {
    "5_2_3_4"
  };

  COLOR = {-1, 1, 94, 2, 226, 9}; // COLOR[0] not used

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
