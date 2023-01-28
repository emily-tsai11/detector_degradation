#ifndef CONSTANTS
#define CONSTANTS

const std::string SAMPLES[] = {
  "TTbar_PU200_D88",
  "TTbar_noPU_D88"
};

const std::string SAMPLE_LATEX[] = {
  "t#bar{t}, PU 200, D88",
  "t#bar{t}, no PU, D88",
};

const std::string FAIL_SCENARIOS[] = {
  "No dead modules",   // 0
  "Kill L5 + 5% loss", // 1
  "Kill L1 + 5% loss", // 2
  "Kill L1 + L2",      // 3
  "Kill L1 + D1",      // 4
  "5% loss",           // 5
  "1% loss",           // 6
  "Kill L5 + 1% loss", // 7
  "Kill L1 + 1% loss"  // 8
};

const int COLOR[] = {1, 9, 2, 8, 63, 15, 94, 6, 221};
const double MARKER_SIZE = 1.0;

std::vector< std::pair<std::string, std::vector<int>> > CASES = {
  {"1loss", {6, 8, 7}},
  {"5loss", {5, 2, 1}},
  {"killL1", {8, 2, 3, 4}},
  {"killL5", {7, 1}}
};

#endif
