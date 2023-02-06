#ifndef CONFIG_BUILDER
#define CONFIG_BUILDER


#include "../include/Constants.hh"
#include "../include/Config.hh"


bool configHasRun = false;

std::string N_SAMPLE;
std::string LATEX_SAMPLE;

// The following is for PlotNTrkPt2 only
double LX1;
double LX2;
double TX;

std::string N_SAVE;
std::string F_REF;
std::vector<std::string> F_FAILS;
std::vector<std::string> LATEX_FAILS;
std::vector<std::pair<std::string, std::vector<int>>> CASES;
std::vector<int> COLOR;


void DefineStubKillerConstants();
void DefineBiasRailConstants();


#endif
