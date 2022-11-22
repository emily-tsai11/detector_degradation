// -----------------------------------------------------------------------------
// ROOT script for making tracking performance plots using the ntuples produced
// by L1TrackNtupleMaker.cc for detector degradation studies
//
// e.g. do: root -l DetectorDegradationPlot.C
//
// By Emily Tsai, November 2022
// -----------------------------------------------------------------------------
//
// Fail Scenarios:
//
// Scenario 0: No dead modules
// Scenario 1: Kill layer 5 in one quadrant +5 % random module loss
// Scenario 2: Kill layer 1 in one quadrant +5 % random module loss
// Scenario 3: Kill layer 1 + layer 2, both in same quadrant
// Scenario 4: Kill layer 1 and disk 1, both in same quadrant
// Scenario 5: 5% random module loss throughout tracker
// Scenario 6: 1% random module loss throughout tracker
// Scenario 7: Kill layer 5 in one quadrant +1 % random module loss
// Scenario 8: Kill layer 1 in one quadrant +1 % random module loss
//
// -----------------------------------------------------------------------------


// const int N_SCENARIOS = 8;
const int N_SCENARIOS = 5;
const int COLORS[] = {1, 4, 2, 8, 13, 9, 94};
const int MARKER[] = {20, 21, 24, 25};

void SetPlotStyle();
void mySmallText(Double_t x, Double_t y, Color_t color, char* text);


// -----------------------------------------------------------------------------
// Main script
// -----------------------------------------------------------------------------

void DetectorDegradationPlot() {
  gROOT->SetBatch();
  gErrorIgnoreLevel = kWarning;

  SetPlotStyle();

  // read in histograms and set attributes
  std::map<std::string, TH1F*> h;
  for(unsigned int n = 0; n <= N_SCENARIOS; n++) {
    std::string f_name = "fail_scenario_" + std::to_string(n) + "_e100/output_TTbar_PU200_D76.root";
    TFile* f = TFile::Open(f_name.c_str());

    std::string h_name = std::to_string(n) + "_";

    h[h_name + "eff_eta"] = f->Get<TH1F>("eff_eta");
    h[h_name + "eff_eta"]->SetMinimum(0.0);
    h[h_name + "eff_eta"]->SetMaximum(1.1);
    h[h_name + "eff_eta"]->SetMarkerStyle((n == 0) ? 20 : 22);
    h[h_name + "eff_eta"]->SetMarkerColor(COLORS[n]);

    h[h_name + "ntrk_pt3"] = f->Get<TH1F>("ntrk_pt3");
    // TODO

    h[h_name + "resVsEta_z0_68"] = f->Get<TH1F>("resVsEta_z0_68");
    h[h_name + "resVsEta_z0_68"]->SetMinimum(0.0);
    h[h_name + "resVsEta_z0_68"]->SetMaximum(2.0);
    h[h_name + "resVsEta_z0_68"]->SetMarkerStyle((n == 0) ? MARKER[0] : MARKER[2]);
    h[h_name + "resVsEta_z0_68"]->SetMarkerColor((n == 0) ? COLOR[0] : COLOR[1]);

    h[h_name + "resVsEta_z0_90"] = f->Get<TH1F>("resVsEta_z0_90");
    h[h_name + "resVsEta_z0_90"]->SetMinimum(0.0);
    h[h_name + "resVsEta_z0_90"]->SetMaximum(2.0);
    h[h_name + "resVsEta_z0_90"]->SetMarkerStyle((n == 0) ? MARKER[1] : MARKER[3]);
    h[h_name + "resVsEta_z0_90"]->SetMarkerColor((n == 0) ? COLOR[0] : COLOR[1]);
  }

  TFile* f0 = TFile::Open("fail_scenario_0_e100/output_TTbar_PU200_D76.root");
  TH1F* f0_eff_eta = f0->Get<TH1F>("eff_eta");
  TH1F* f0_ntrk_pt3 = f0->Get<TH1F>("ntrk_pt3");
  TH1F* f0_resVsEta_z0_68 = f0->Get<TH1F>("resVsEta_z0_68");
  TH1F* f0_resVsEta_z0_90 = f0->Get<TH1F>("resVsEta_z0_90");

  TFile* f1 = TFile::Open("fail_scenario_1_e100/output_TTbar_PU200_D76.root");
  TH1F* f1_eff_eta = f1->Get<TH1F>("eff_eta");
  TH1F* f1_ntrk_pt3 = f1->Get<TH1F>("ntrk_pt3");
  TH1F* f1_resVsEta_z0_68 = f1->Get<TH1F>("resVsEta_z0_68");
  TH1F* f1_resVsEta_z0_90 = f1->Get<TH1F>("resVsEta_z0_90");

  TFile* f2 = TFile::Open("fail_scenario_2_e100/output_TTbar_PU200_D76.root");
  TH1F* f2_eff_eta = f2->Get<TH1F>("eff_eta");
  TH1F* f2_ntrk_pt3 = f2->Get<TH1F>("ntrk_pt3");
  TH1F* f2_resVsEta_z0_68 = f2->Get<TH1F>("resVsEta_z0_68");
  TH1F* f2_resVsEta_z0_90 = f2->Get<TH1F>("resVsEta_z0_90");

  TFile* f3 = TFile::Open("fail_scenario_3_e100/output_TTbar_PU200_D76.root");
  TH1F* f3_eff_eta = f3->Get<TH1F>("eff_eta");
  TH1F* f3_ntrk_pt3 = f3->Get<TH1F>("ntrk_pt3");
  TH1F* f3_resVsEta_z0_68 = f3->Get<TH1F>("resVsEta_z0_68");
  TH1F* f3_resVsEta_z0_90 = f3->Get<TH1F>("resVsEta_z0_90");

  TFile* f4 = TFile::Open("fail_scenario_4_e100/output_TTbar_PU200_D76.root");
  TH1F* f4_eff_eta = f4->Get<TH1F>("eff_eta");
  TH1F* f4_ntrk_pt3 = f4->Get<TH1F>("ntrk_pt3");
  TH1F* f4_resVsEta_z0_68 = f4->Get<TH1F>("resVsEta_z0_68");
  TH1F* f4_resVsEta_z0_90 = f4->Get<TH1F>("resVsEta_z0_90");

  TFile* f5 = TFile::Open("fail_scenario_5_e100/output_TTbar_PU200_D76.root");
  TH1F* f5_eff_eta = f5->Get<TH1F>("eff_eta");
  TH1F* f5_ntrk_pt3 = f5->Get<TH1F>("ntrk_pt3");
  TH1F* f5_resVsEta_z0_68 = f5->Get<TH1F>("resVsEta_z0_68");
  TH1F* f5_resVsEta_z0_90 = f5->Get<TH1F>("resVsEta_z0_90");

  // make plots

  TCanvas c;
  double minY;
  double maxY;
  int shape;

  minY = 0.0;
  maxY = 1.1;
  shape = 22;

  f0_eff_eta->SetMinimum(minY);
  f1_eff_eta->SetMinimum(minY);
  f2_eff_eta->SetMinimum(minY);
  f3_eff_eta->SetMinimum(minY);
  f4_eff_eta->SetMinimum(minY);
  f5_eff_eta->SetMinimum(minY);

  f0_eff_eta->SetMaximum(maxY);
  f1_eff_eta->SetMaximum(maxY);
  f2_eff_eta->SetMaximum(maxY);
  f3_eff_eta->SetMaximum(maxY);
  f4_eff_eta->SetMaximum(maxY);
  f5_eff_eta->SetMaximum(maxY);

  f0_eff_eta->SetMarkerStyle(20);
  f1_eff_eta->SetMarkerStyle(shape);
  f2_eff_eta->SetMarkerStyle(shape);
  f3_eff_eta->SetMarkerStyle(shape);
  f4_eff_eta->SetMarkerStyle(shape);
  f5_eff_eta->SetMarkerStyle(shape);

  f1_eff_eta->SetMarkerColor(4);
  f2_eff_eta->SetMarkerColor(2);
  f3_eff_eta->SetMarkerColor(8);
  f4_eff_eta->SetMarkerColor(13);
  f5_eff_eta->SetMarkerColor(9);

  // make eta efficiency plots

  {
    f0_eff_eta->Draw("P");

    TLegend* l = new TLegend(0.6, 0.25, 0.85, 0.55);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->AddEntry(f0_eff_eta, "No dead modules", "p");
    l->SetTextFont(42);
    l->Draw();

    c.SaveAs("plots/f0_eff_eta.pdf");

    delete l;
  }

  {
    f0_eff_eta->Draw("P");
    f1_eff_eta->Draw("P,same");

    TLegend* l = new TLegend(0.6, 0.25, 0.85, 0.55);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->AddEntry(f0_eff_eta, "No dead modules", "p");
    l->AddEntry(f1_eff_eta, "Kill L5 + 5% loss", "p");
    l->SetTextFont(42);
    l->Draw();

    c.SaveAs("plots/f0f1_eff_eta.pdf");

    delete l;
  }

  {
    f0_eff_eta->Draw("P");
    f1_eff_eta->Draw("P,same");
    f2_eff_eta->Draw("P,same");
    f3_eff_eta->Draw("P,same");
    f4_eff_eta->Draw("P,same");
    f5_eff_eta->Draw("P,same");

    TLegend* l = new TLegend(0.6, 0.25, 0.85, 0.55);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->AddEntry(f0_eff_eta, "No dead modules", "p");
    l->AddEntry(f1_eff_eta, "Kill L5 + 5% loss", "p");
    l->AddEntry(f2_eff_eta, "Kill L1 + 5% loss", "p");
    l->AddEntry(f3_eff_eta, "Kill L1 + L2", "p");
    l->AddEntry(f4_eff_eta, "Kill L5 + D1", "p");
    l->AddEntry(f5_eff_eta, "5% loss", "p");
    l->SetTextFont(42);
    l->Draw();

    c.SaveAs("plots/fAll_eff_eta.pdf");

    delete l;
  }

  // make residual plots

  minY = 0.0;
  maxY = 2.0;

  f0_resVsEta_z0_68->SetMinimum(minY);
  f0_resVsEta_z0_90->SetMinimum(minY);
  f1_resVsEta_z0_68->SetMinimum(minY);
  f1_resVsEta_z0_90->SetMinimum(minY);

  f0_resVsEta_z0_68->SetMaximum(maxY);
  f0_resVsEta_z0_90->SetMaximum(maxY);
  f1_resVsEta_z0_68->SetMaximum(maxY);
  f1_resVsEta_z0_90->SetMaximum(maxY);

  f0_resVsEta_z0_68->SetMarkerStyle(20);
  f0_resVsEta_z0_90->SetMarkerStyle(21);
  f1_resVsEta_z0_68->SetMarkerStyle(24);
  f1_resVsEta_z0_90->SetMarkerStyle(25);

  f1_resVsEta_z0_68->SetMarkerColor(4);
  f1_resVsEta_z0_90->SetMarkerColor(4);

  {
    f0_resVsEta_z0_68->Draw("p");
    f0_resVsEta_z0_90->Draw("p,same");
    f1_resVsEta_z0_68->Draw("p,same");
    f1_resVsEta_z0_90->Draw("p,same");

    TLegend* l1 = new TLegend(0.55, 0.55, 0.8, 0.85);
    l1->SetFillStyle(0);
    l1->SetBorderSize(0);
    l1->SetTextSize(0.04);
    l1->AddEntry(f0_resVsEta_z0_68, "No dead modules", "p");
    l1->AddEntry(f1_resVsEta_z0_68, "Kill L5 + 5% loss", "p");
    l1->SetTextFont(42);
    l1->Draw();

    TLegend* l2 = new TLegend(0.3, 0.55, 0.4, 0.85);
    l2->SetFillStyle(0);
    l2->SetBorderSize(0);
    l2->SetTextSize(0.04);
    l2->AddEntry(f0_resVsEta_z0_68, "68%", "p");
    l2->AddEntry(f0_resVsEta_z0_90, "90%", "p");
    l2->SetTextFont(42);
    l2->Draw();

    c.SaveAs("plots/f0f1_resVsEta_z0_interval.pdf");

    delete l1;
    delete l2;
  }

  std::cout << "good work" << std::endl;
}

// -----------------------------------------------------------------------------


void SetPlotStyle() {
  // from ATLAS plot style macro

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


void mySmallText(Double_t x, Double_t y, Color_t color, char* text) {
  Double_t tsize = 0.044;
  TLatex l;
  l.SetTextSize(tsize);
  l.SetNDC();
  l.SetTextColor(color);
  l.DrawLatex(x, y, text);
}
