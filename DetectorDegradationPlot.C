// -----------------------------------------------------------------------------
// ROOT script for making tracking performance plots using the ntuples produced
// by L1TrackNtupleMaker.cc for detector degradation studies
//
// e.g. do: root -l DetectorDegradationPlot.C
//
// By Emily Tsai, November 2022
// -----------------------------------------------------------------------------


const int N_EVENTS = 9000;
const int N_SCENARIOS = 8;
const int COLOR[] = {1, 9, 2, 8, 63, 15, 94, 6, 221};
const int MARKER[] = {20, 22, 24, 21, 25};
const double MARKER_SIZE = 1.0;
const std::string SCENARIO[] = {
  "No dead modules",      // 0
  "Kill L5 + 5% loss",    // 1
  "Kill L1 + 5% loss",    // 2
  "Kill L1 + L2",         // 3
  "Kill L1 + D1",         // 4
  "5% loss",              // 5
  "1% loss",              // 6
  "Kill L5 + 1% loss",    // 7
  "Kill L1 + 1% loss"     // 8
};

// map for storing histograms
std::map<std::string, TH1F*> h;


void makeResidualIntervalPlot(vector<int> scenarios, std::string name, std::string type);
void makeCombPlot(vector<int> scenarios, std::string name, std::string type, bool plot_log);
void setPlotStyle();
// void MySmallText(Double_t x, Double_t y, Color_t color, char* text);


// -----------------------------------------------------------------------------
// Main script
// -----------------------------------------------------------------------------

void DetectorDegradationPlot() {

  gROOT->SetBatch();
  gErrorIgnoreLevel = kWarning;

  setPlotStyle();

  // read in histograms and set attributes
  std::string h_name, f_name;
  for(int n = 0; n <= N_SCENARIOS; n++) {

    f_name = "results/fail_scenario_" + std::to_string(n) + "_e" + std::to_string(N_EVENTS) + "/output_TTbar_PU200_D76.root";
    TFile* f = TFile::Open(f_name.c_str());

    h_name = "eff_eta_" + std::to_string(n);
    h[h_name] = f->Get<TH1F>("eff_eta");
    h[h_name]->SetMinimum(0.0);
    h[h_name]->SetMaximum(1.1);
    h[h_name]->SetLineColor(COLOR[n]);
    h[h_name]->SetMarkerStyle(n == 0 ? MARKER[0] : MARKER[1]);
    h[h_name]->SetMarkerSize(MARKER_SIZE);
    h[h_name]->SetMarkerColor(COLOR[n]);

    h_name = "ntrk_pt3_" + std::to_string(n);
    h[h_name] = f->Get<TH1F>("ntrk_pt3");
    h[h_name]->Scale(1.0 / N_EVENTS);
    h[h_name]->GetYaxis()->SetTitle("Fraction of events");
    h[h_name]->SetLineColor(COLOR[n]);
    h[h_name]->SetMarkerStyle(n == 0 ? MARKER[0] : MARKER[1]);
    h[h_name]->SetMarkerSize(MARKER_SIZE);
    h[h_name]->SetMarkerColor(COLOR[n]);

    h_name = "resVsEta_z0_68_" + std::to_string(n);
    h[h_name] = f->Get<TH1F>("resVsEta_z0_68");
    h[h_name]->GetXaxis()->SetRangeUser(0.0, 2.4);
    h[h_name]->SetMinimum(0.0);
    h[h_name]->SetMaximum(2.0);
    h[h_name]->SetLineColor(COLOR[n]);
    h[h_name]->SetMarkerStyle(n == 0 ? MARKER[0] : MARKER[3]);
    h[h_name]->SetMarkerSize(MARKER_SIZE);
    h[h_name]->SetMarkerColor(COLOR[n]);

    h_name = "resVsEta_z0_90_" + std::to_string(n);
    h[h_name] = f->Get<TH1F>("resVsEta_z0_90");
    h[h_name]->GetXaxis()->SetRangeUser(0.0, 2.4);
    h[h_name]->SetMinimum(0.0);
    h[h_name]->SetMaximum(2.0);
    h[h_name]->SetLineColor(COLOR[n]);
    h[h_name]->SetMarkerStyle(n == 0 ? MARKER[2] : MARKER[4]);
    h[h_name]->SetMarkerSize(MARKER_SIZE);
    h[h_name]->SetMarkerColor(COLOR[n]);
  }

  // make eta efficiency plots
  for(int n = 1; n <= N_SCENARIOS; n++)
    makeCombPlot((vector<int>) {0, n}, "eff_eta", "0" + std::to_string(n), false);

  // make # of tracks with pT > 3 GeV plots
  for(int n = 1; n <= N_SCENARIOS; n++)
    makeCombPlot((vector<int>) {0, n}, "ntrk_pt3", "0" + std::to_string(n), true);

  // make z0 residual vs. eta interval plots
  for(int n = 1; n <= N_SCENARIOS; n++)
    makeResidualIntervalPlot((vector<int>) {0, n}, "resVsEta", "z0");

  // make 1% loss plots
  makeCombPlot((vector<int>) {0, 6, 7, 8}, "eff_eta", "1loss", false);
  makeCombPlot((vector<int>) {0, 6, 7, 8}, "ntrk_pt3", "1loss", true);

  // make 5% loss plots
  makeCombPlot((vector<int>) {0, 5, 1, 2}, "eff_eta", "5loss", false);
  makeCombPlot((vector<int>) {0, 5, 1, 2}, "ntrk_pt3", "5loss", true);

  // make kill L1 plots
  makeCombPlot((vector<int>) {0, 3, 4, 8, 2}, "eff_eta", "killL1", false);
  makeCombPlot((vector<int>) {0, 3, 4, 8, 2}, "ntrk_pt3", "killL1", true);

  // make kill L5 plots
  makeCombPlot((vector<int>) {0, 7, 1}, "eff_eta", "killL5", false);
  makeCombPlot((vector<int>) {0, 7, 1}, "ntrk_pt3", "killL5", true);
}

// -----------------------------------------------------------------------------


void makeResidualIntervalPlot(vector<int> scenarios, std::string name, std::string type) {

  TCanvas c;

  TLegend* l1 = new TLegend(0.55, 0.55, 0.8, 0.85);
  l1->SetFillStyle(0);
  l1->SetBorderSize(0);
  l1->SetTextSize(0.04);
  l1->SetTextFont(42);

  TLegend* l2 = new TLegend(0.3, 0.55, 0.4, 0.85);
  l2->SetFillStyle(0);
  l2->SetBorderSize(0);
  l2->SetTextSize(0.04);
  l2->SetTextFont(42);

  int n_scenarios = scenarios.size();
  for(int s = 0; s < n_scenarios; s++) {
    int is = scenarios[s];
    std::string ss = std::to_string(is);
    std::string h68 = name + "_" + type + "_68_" + ss;
    std::string h90 = name + "_" + type + "_90_" + ss;
    h[h68]->Draw("p,same");
    h[h90]->Draw("p,same");
    l1->AddEntry(h[h68], SCENARIO[is].c_str(), "pl");
    if(s == 0) {
      l2->AddEntry(h[h68], "68%", "p");
      l2->AddEntry(h[h90], "90%", "p");
    }
  }

  l1->Draw();
  l2->Draw();

  std::string f_name = "comb_plots/" + type + "_" + name + "_interval_";
  for(int s = 0; s < n_scenarios; s++) f_name += std::to_string(scenarios[s]);
  f_name += ".pdf";
  c.SaveAs(f_name.c_str());

  delete l1;
  delete l2;
}


void makeCombPlot(vector<int> scenarios, std::string name, std::string type, bool plot_log) {

  TCanvas c;

  TLegend* l = new TLegend(0.6, 0.25, 0.85, 0.55);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetTextSize(0.04);
  l->SetTextFont(42);

  int n_scenarios = scenarios.size();
  for(int s = 0; s < n_scenarios; s++) {
    int is = scenarios[s];
    std::string ss = std::to_string(is);
    std::string hname = name + "_" + ss;
    h[hname]->Draw("p,same");
    l->AddEntry(h[hname], SCENARIO[is].c_str(), "pl");
  }

  l->Draw();

  std::string f_name = "comb_plots/" + name + "_" + type + ".pdf";
  gPad->SetGridy();
  c.SaveAs(f_name.c_str());
  gPad->SetGridy(0);

  if(plot_log) {
    f_name = "comb_plots/" + name + "_" + type + "_log.pdf";
    gPad->SetLogy();
    c.SaveAs(f_name.c_str());
    gPad->SetLogy(0);
  }

  delete l;
}


// from ATLAS plot style macro
void setPlotStyle() {

  // use plain black on white colors
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetHistLineColor(1);

  gStyle->SetPalette(1);

  // set the paper & margin sizes
  gStyle->SetPaperSize(20, 26);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  gStyle->SetTitleXOffset(1.4);
  gStyle->SetTitleYOffset(1.4);

  // use large fonts
  gStyle->SetTextFont(42);
  gStyle->SetTextSize(0.05);
  gStyle->SetLabelFont(42, "x");
  gStyle->SetTitleFont(42, "x");
  gStyle->SetLabelFont(42, "y");
  gStyle->SetTitleFont(42, "y");
  gStyle->SetLabelFont(42, "z");
  gStyle->SetTitleFont(42, "z");
  gStyle->SetLabelSize(0.05, "x");
  gStyle->SetTitleSize(0.05, "x");
  gStyle->SetLabelSize(0.05, "y");
  gStyle->SetTitleSize(0.05, "y");
  gStyle->SetLabelSize(0.05, "z");
  gStyle->SetTitleSize(0.05, "z");

  // use bold lines and markers
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1.2);
  gStyle->SetHistLineWidth(2.0);
  gStyle->SetLineStyleString(2, "[12 12]");

  // get rid of error bar caps
  gStyle->SetEndErrorSize(0.0);

  // do not display any of the standard histogram decorations
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
}


// void MySmallText(Double_t x, Double_t y, Color_t color, char* text) {
//
//   Double_t tsize = 0.044;
//   TLatex l;
//   l.SetTextSize(tsize);
//   l.SetNDC();
//   l.SetTextColor(color);
//   l.DrawLatex(x, y, text);
// }
