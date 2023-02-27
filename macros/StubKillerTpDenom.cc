#include "../include/Config.hh"
#include "../include/ConfigBuilder.hh"
#include "../include/PlotHelperFunctions.hh"


void check_tp_denom();


void StubKillerTpDenom(int sample = SAMPLE) {

  if(sample == 0 || sample == -1) {
    if(!stubKiller0Set) ConfigBuilder(0);
    std::cout << "Sample = TTbar_PU200_D88" << std::endl;
    check_tp_denom();
  } else if(sample == 1 || sample == -1) {
    if(!stubKiller1Set) ConfigBuilder(1);
    std::cout << "Sample = TTbar_noPU_D88" << std::endl;
    check_tp_denom();
  } else {
    std::cout << "Invalid sample! Exiting." << std::endl;
  }
}


void check_tp_denom() {

  char txt[500];

  std::cout << std::endl;

  for(int s = 0; s < F_FAILS.size(); s++) {

    if(F_FAILS[s].length() == 0) continue;
    TFile* f = TFile::Open(F_FAILS[s].c_str());
    TH1F* h = f->Get<TH1F>("tp_vspt");
    snprintf(txt, 500, "# TPs(#geq 4 stubs in #geq 4 layers)/event = %.8f", h->GetSum());
    std::cout << LATEX_FAILS[s] << " : " << txt << std::endl;
  }
