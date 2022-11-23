// -----------------------------------------------------------------------------
// ROOT script for making tracking performance plots using the ntuples produced
// by L1TrackNtupleMaker.cc for detector degradation studies
//
// e.g. do: root -l DetectorDegradationPlot.C
//
// By Emily Tsai, November 2022
// -----------------------------------------------------------------------------


const int N_SCENARIOS = 8;
const int COLOR[] = {1, 4/*, 2, 8, 13, 9, 94, 6, 7*/};
const int MARKER[] = {20, 24, 21, 25};
const std::string SCENARIO[] = {
  "No dead modules",      // 0
  "Kill L5 + 5% loss",    // 1
  "Kill L1 + 5% loss",    // 2
  "Kill L1 + L2",         // 3
  "Kill L5 + D1",         // 4
  "5% loss",              // 5
  "1% loss",              // 6
  "Kill L5 + 1% loss",    // 7
  "Kill L1 + 1% loss"     // 8
};


void makePlot2(TH1F* h1, TH1F* h2, std::string l1, std::string l2, std::string f);
void makeNTrkPtPlot(TH1F* h1, TH1F* h2, std::string l1, std::string l2, std::string f);
void makeResidualIntervalPlot(TH1F* h1_68, TH1F* h1_90, TH1F* h2_68, TH1F* h2_90,
  std::string str_l1, std::string str_l2, std::string f);
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
  std::map<std::string, TH1F*> h;
  std::string h_name;

  for(int n = 0; n <= N_SCENARIOS; n++) {

    std::string f_name = "fail_scenario_" + std::to_string(n) + "_e100/output_TTbar_PU200_D76.root";
    TFile* f = TFile::Open(f_name.c_str());

    h_name = "eff_eta_" + std::to_string(n);
    h[h_name] = f->Get<TH1F>("eff_eta");
    h[h_name]->SetMinimum(0.0);
    h[h_name]->SetMaximum(1.1);
    h[h_name]->SetMarkerStyle(n == 0 ? 20 : 21);
    h[h_name]->SetMarkerColor(n == 0 ? COLOR[0] : COLOR[1]);

    h_name = "ntrk_pt3_" + std::to_string(n);
    h[h_name] = f->Get<TH1F>("ntrk_pt3");
    h[h_name]->SetMarkerStyle(n == 0 ? 20 : 21);
    h[h_name]->SetMarkerColor(n == 0 ? COLOR[0] : COLOR[1]);

    h_name = "resVsEta_z0_68_" + std::to_string(n);
    h[h_name] = f->Get<TH1F>("resVsEta_z0_68");
    h[h_name]->SetMinimum(0.0);
    h[h_name]->SetMaximum(2.0);
    h[h_name]->SetMarkerStyle(n == 0 ? MARKER[0] : MARKER[2]);
    h[h_name]->SetMarkerColor(n == 0 ? COLOR[0] : COLOR[1]);

    h_name = "resVsEta_z0_90_" + std::to_string(n);
    h[h_name] = f->Get<TH1F>("resVsEta_z0_90");
    h[h_name]->SetMinimum(0.0);
    h[h_name]->SetMaximum(2.0);
    h[h_name]->SetMarkerStyle(n == 0 ? MARKER[1] : MARKER[3]);
    h[h_name]->SetMarkerColor(n == 0 ? COLOR[0] : COLOR[1]);
  }

  // make eta efficiency plots
  for(int n = 1; n <= N_SCENARIOS; n++) {

    std::string str_n = std::to_string(n);
    makePlot2(
      h["eff_eta_0"], h["eff_eta_" + str_n],
      SCENARIO[0], SCENARIO[n], "eff_eta_0" + str_n);
  }

  // make # of tracks with pT > 3 GeV plots
  for(int n = 1; n <= N_SCENARIOS; n++) {

    std::string str_n = std::to_string(n);
    makeNTrkPtPlot(
      h["ntrk_pt3_0"], h["ntrk_pt3_" + str_n],
      SCENARIO[0], SCENARIO[n], "ntrk_pt3_0" + str_n);
  }

  // make z0 residual vs. eta interval plots
  for(int n = 1; n <= N_SCENARIOS; n++) {

    std::string str_n = std::to_string(n);
    makeResidualIntervalPlot(
      h["resVsEta_z0_68_0"], h["resVsEta_z0_90_0"],
      h["resVsEta_z0_68_" + str_n], h["resVsEta_z0_90_" + str_n],
      SCENARIO[0], SCENARIO[n], "resVsEta_z0_interval_0" + str_n);
  }
}

// -----------------------------------------------------------------------------


void makePlot2(TH1F* h1, TH1F* h2, std::string l1, std::string l2, std::string f) {

  TCanvas c;

  h1->Draw("p");
  h2->Draw("p,same");

  TLegend* l = new TLegend(0.6, 0.25, 0.85, 0.55);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetTextSize(0.04);
  l->AddEntry(h1, l1.c_str(), "pl");
  l->AddEntry(h2, l2.c_str(), "pl");
  l->SetTextFont(42);
  l->Draw();

  std::string f_name = "plots/" + f + ".pdf";
  c.SaveAs(f_name.c_str());

  delete l;
}


void makeNTrkPtPlot(TH1F* h1, TH1F* h2, std::string l1, std::string l2, std::string f) {

  TCanvas c;

  h1->Draw("p");
  h2->Draw("p,same");

  TLegend* l = new TLegend(0.6, 0.25, 0.85, 0.55);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetTextSize(0.04);
  l->AddEntry(h1, l1.c_str(), "pl");
  l->AddEntry(h2, l2.c_str(), "pl");
  l->SetTextFont(42);
  l->Draw();

  std::string f_name = "plots/" + f + ".pdf";
  c.SaveAs(f_name.c_str());

  gPad->SetLogy();
  f_name = "plots/" + f + "_log.pdf";
  c.SaveAs(f_name.c_str());
  gPad->SetLogy(0);

  delete l;
}


void makeResidualIntervalPlot(TH1F* h1_68, TH1F* h1_90, TH1F* h2_68, TH1F* h2_90,
  std::string str_l1, std::string str_l2, std::string f) {

  TCanvas c;

  h1_68->Draw("p");
  h1_90->Draw("p,same");
  h2_68->Draw("p,same");
  h2_90->Draw("p,same");

  h1_68->GetXaxis()->SetRangeUser(0.0, 2.4);
  h1_90->GetXaxis()->SetRangeUser(0.0, 2.4);
  h2_68->GetXaxis()->SetRangeUser(0.0, 2.4);
  h2_90->GetXaxis()->SetRangeUser(0.0, 2.4);

  TLegend* l1 = new TLegend(0.55, 0.55, 0.8, 0.85);
  l1->SetFillStyle(0);
  l1->SetBorderSize(0);
  l1->SetTextSize(0.04);
  l1->AddEntry(h1_68, str_l1.c_str(), "pl");
  l1->AddEntry(h2_68, str_l2.c_str(), "pl");
  l1->SetTextFont(42);
  l1->Draw();

  TLegend* l2 = new TLegend(0.3, 0.55, 0.4, 0.85);
  l2->SetFillStyle(0);
  l2->SetBorderSize(0);
  l2->SetTextSize(0.04);
  l2->AddEntry(h1_90, "90%", "p");
  l2->AddEntry(h1_68, "68%", "p");
  l2->SetTextFont(42);
  l2->Draw();

  std::string f_name = "plots/" + f + ".pdf";
  c.SaveAs(f_name.c_str());

  delete l1;
  delete l2;
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
