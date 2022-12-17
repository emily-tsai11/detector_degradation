// -----------------------------------------------------------------------------
// ROOT script for making tracking performance plots using the ntuples produced
// by L1TrackNtupleMaker.cc for detector degradation studies
//
// e.g. do: root -l DetectorDegradationPlot.C
//
// By Emily Tsai, November 2022
// -----------------------------------------------------------------------------


const int COLOR[] = {1, 9, 2, 8, 63, 15, 94, 6, 221};
const int MARKER[] = {20, 22, 24, 21, 25};
const double MARKER_SIZE = 1.0;

const std::string SAMPLE[] = {
  "TTbar_PU200_D76", // 0
  "TTbar_noPU_D76"   // 1
};
const std::string QUADRANT[] = {
  "phi.0.pi2_z.-1000.0", // 0
  "phi.0.pi2_z.0.1000"   // 1
};

const std::string SAMPLE_P[] = {
  "t#bar{t}, PU 200, D76", // 0
  "t#bar{t}, no PU, D76",  // 1
};
const std::string QUADRANT_P[] = {
  "#phi (0 #rightarrow #pi/2), z (-1000 #rightarrow 0)", // 0
  "#phi (0 #rightarrow #pi/2), z (0 #rightarrow 1000)",  // 1
};
const std::string SCENARIO_P[] = {
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

// FORMAT: sample_quadrant_failScenario


bool debug = 0;


// map for storing histograms
std::map<std::string, TH1F*> h;


void copyHistEntries(TH1F* h_ret, TH1F* h_copy, int n_bins);
void readHistograms(int s, int q, vector<int> scenarios, int n, bool truncation);
void makeResidualIntervalPlot(int s, int q, vector<int> scenarios, std::string name, std::string type);
void makeMultiPlot(int s, int q, vector<int> scenarios, std::string name, std::string type, bool plot_log, bool truncation);
void setPlotStyle();
void mySmallText(Double_t x, Double_t y, Color_t color, std::string text);


// -----------------------------------------------------------------------------
// Main script
// -----------------------------------------------------------------------------

void DetectorDegradationPlot() {

  gROOT->SetBatch();
  gErrorIgnoreLevel = kWarning;

  setPlotStyle();

  // read in histograms and set attributes
  readHistograms(0, 0, {0, 1, 2, 3, 4, 5, 6, 7, 8}, 9000, true);
  readHistograms(0, 0, {0, 6}, 9000, false); // not truncated
  readHistograms(0, 1, {2, 5, 6, 8}, 9000, true);
  readHistograms(1, 0, {0, 1, 2, 3, 4, 5, 6, 7, 8}, 9000, true);
  readHistograms(1, 0, {0, 6}, 9000, false); // not truncated

  // make eta efficiency plots
  for(auto &is : {1, 2, 3, 4, 5, 6, 7, 8})
    makeMultiPlot(0, 0, {0, is}, "eff_eta", "f0" + std::to_string(is), false, true);
  for(auto &is : {6})
    makeMultiPlot(0, 0, {0, is}, "eff_eta", "f0" + std::to_string(is), false, false);
  for(auto &is : {1, 2, 3, 4, 5, 6, 7, 8})
    makeMultiPlot(1, 0, {0, is}, "eff_eta", "f0" + std::to_string(is), false, true);
  for(auto &is : {6})
    makeMultiPlot(1, 0, {0, is}, "eff_eta", "f0" + std::to_string(is), false, false);

  // TTBar PU200
  // make zoomed eta efficiency plots for failure scenario 6, with truncation
  {
    TCanvas c;

    TLegend* l = new TLegend(0.45, 0.2, 0.75, 0.4);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h["eff_eta_0_0_6"]->SetLineColor(221);
    h["eff_eta_0_0_6"]->SetMarkerColor(221);

    h["eff_eta_0_0_0"]->SetMinimum(0.84);
    h["eff_eta_0_0_0"]->SetMaximum(1.0);

    h["eff_eta_0_0_6"]->SetMinimum(0.84);
    h["eff_eta_0_0_6"]->SetMaximum(1.0);

    h["eff_eta_0_0_0"]->Draw("p");
    h["eff_eta_0_0_6"]->Draw("p,same");

    l->AddEntry(h["eff_eta_0_0_0"], SCENARIO_P[0].c_str(), "pl");
    l->AddEntry(h["eff_eta_0_0_6"], SCENARIO_P[6].c_str(), "pl");

    l->Draw();

    mySmallText(0.2, 0.28, 1, "Truncated");

    std::string f_name = "plots/" + SAMPLE[0] + "/" + QUADRANT[0] + "/eff_eta_f06_zoom.pdf";
    gPad->SetGridy();
    c.SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;

    h["eff_eta_0_0_0"]->SetMinimum(0.0);
    h["eff_eta_0_0_0"]->SetMaximum(1.1);

    h["eff_eta_0_0_6"]->SetMinimum(0.0);
    h["eff_eta_0_0_6"]->SetMaximum(1.1);
  }
  // make zoomed eta efficiency plots for failure scenario 6, without truncation
  {
    TCanvas c;

    TLegend* l = new TLegend(0.45, 0.2, 0.75, 0.4);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h["eff_eta_0_0_6_noTrunc"]->SetLineColor(221);
    h["eff_eta_0_0_6_noTrunc"]->SetMarkerColor(221);

    h["eff_eta_0_0_0_noTrunc"]->SetMinimum(0.84);
    h["eff_eta_0_0_0_noTrunc"]->SetMaximum(1.0);

    h["eff_eta_0_0_6_noTrunc"]->SetMinimum(0.84);
    h["eff_eta_0_0_6_noTrunc"]->SetMaximum(1.0);

    h["eff_eta_0_0_0_noTrunc"]->Draw("p");
    h["eff_eta_0_0_6_noTrunc"]->Draw("p,same");

    l->AddEntry(h["eff_eta_0_0_0_noTrunc"], SCENARIO_P[0].c_str(), "pl");
    l->AddEntry(h["eff_eta_0_0_6_noTrunc"], SCENARIO_P[6].c_str(), "pl");

    l->Draw();

    mySmallText(0.2, 0.28, 1, "Not truncated");

    std::string f_name = "plots/" + SAMPLE[1] + "/" + QUADRANT[0] + "/eff_eta_f06_noTrunc_zoom.pdf";
    gPad->SetGridy();
    c.SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;

    h["eff_eta_0_0_0_noTrunc"]->SetMinimum(0.0);
    h["eff_eta_0_0_0_noTrunc"]->SetMaximum(1.1);

    h["eff_eta_0_0_6_noTrunc"]->SetMinimum(0.0);
    h["eff_eta_0_0_6_noTrunc"]->SetMaximum(1.1);
  }

  // TTBar noPU
  // make zoomed eta efficiency plots for failure scenario 6, with truncation
  {
    TCanvas c;

    TLegend* l = new TLegend(0.45, 0.2, 0.75, 0.4);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h["eff_eta_1_0_6"]->SetLineColor(221);
    h["eff_eta_1_0_6"]->SetMarkerColor(221);

    h["eff_eta_1_0_0"]->SetMinimum(0.84);
    h["eff_eta_1_0_0"]->SetMaximum(1.0);

    h["eff_eta_1_0_6"]->SetMinimum(0.84);
    h["eff_eta_1_0_6"]->SetMaximum(1.0);

    h["eff_eta_1_0_0"]->Draw("p");
    h["eff_eta_1_0_6"]->Draw("p,same");

    l->AddEntry(h["eff_eta_1_0_0"], SCENARIO_P[0].c_str(), "pl");
    l->AddEntry(h["eff_eta_1_0_6"], SCENARIO_P[6].c_str(), "pl");

    l->Draw();

    mySmallText(0.2, 0.28, 1, "Truncated");

    std::string f_name = "plots/" + SAMPLE[1] + "/" + QUADRANT[0] + "/eff_eta_f06_zoom.pdf";
    gPad->SetGridy();
    c.SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;

    h["eff_eta_1_0_0"]->SetMinimum(0.0);
    h["eff_eta_1_0_0"]->SetMaximum(1.1);

    h["eff_eta_1_0_6"]->SetMinimum(0.0);
    h["eff_eta_1_0_6"]->SetMaximum(1.1);
  }
  // make zoomed eta efficiency plots for failure scenario 6, without truncation
  {
    TCanvas c;

    TLegend* l = new TLegend(0.45, 0.2, 0.75, 0.4);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h["eff_eta_0_0_6_noTrunc"]->SetLineColor(221);
    h["eff_eta_0_0_6_noTrunc"]->SetMarkerColor(221);

    h["eff_eta_0_0_0_noTrunc"]->SetMinimum(0.84);
    h["eff_eta_0_0_0_noTrunc"]->SetMaximum(1.0);

    h["eff_eta_0_0_6_noTrunc"]->SetMinimum(0.84);
    h["eff_eta_0_0_6_noTrunc"]->SetMaximum(1.0);

    h["eff_eta_0_0_0_noTrunc"]->Draw("p");
    h["eff_eta_0_0_6_noTrunc"]->Draw("p,same");

    l->AddEntry(h["eff_eta_0_0_0_noTrunc"], SCENARIO_P[0].c_str(), "pl");
    l->AddEntry(h["eff_eta_0_0_6_noTrunc"], SCENARIO_P[6].c_str(), "pl");

    l->Draw();

    mySmallText(0.2, 0.28, 1, "Not truncated");

    std::string f_name = "plots/" + SAMPLE[0] + "/" + QUADRANT[0] + "/eff_eta_f06_noTrunc_zoom.pdf";
    gPad->SetGridy();
    c.SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;

    h["eff_eta_0_0_0_noTrunc"]->SetMinimum(0.0);
    h["eff_eta_0_0_0_noTrunc"]->SetMaximum(1.1);

    h["eff_eta_0_0_6_noTrunc"]->SetMinimum(0.0);
    h["eff_eta_0_0_6_noTrunc"]->SetMaximum(1.1);
  }

  // make # of tracks with pT > 3 GeV plots
  for(auto &is : {1, 2, 3, 4, 5, 6, 7, 8})
    makeMultiPlot(0, 0, {0, is}, "ntrk_pt3", "f0" + std::to_string(is), true, true);
  for(auto &is : {1, 2, 3, 4, 5, 6, 7, 8})
    makeMultiPlot(1, 0, {0, is}, "ntrk_pt3", "f0" + std::to_string(is), true, true);

  // make z0 residual vs. eta interval plots
  for(auto &is : {1, 2, 3, 4, 5, 6, 7, 8})
    makeResidualIntervalPlot(0, 0, {0, is}, "resVsEta_z0", "f0" + std::to_string(is));
  for(auto &is : {1, 2, 3, 4, 5, 6, 7, 8})
    makeResidualIntervalPlot(1, 0, {0, is}, "resVsEta_z0", "f0" + std::to_string(is));

  // make 1% loss plots
  makeMultiPlot(0, 0, {0, 6, 7, 8}, "eff_eta", "1loss", false, true);
  makeMultiPlot(0, 0, {0, 6, 7, 8}, "ntrk_pt3", "1loss", true, true);

  makeMultiPlot(1, 0, {0, 6, 7, 8}, "eff_eta", "1loss", false, true);
  makeMultiPlot(1, 0, {0, 6, 7, 8}, "ntrk_pt3", "1loss", true, true);

  // make 5% loss plots
  makeMultiPlot(0, 0, {0, 5, 1, 2}, "eff_eta", "5loss", false, true);
  makeMultiPlot(0, 0, {0, 5, 1, 2}, "ntrk_pt3", "5loss", true, true);

  makeMultiPlot(1, 0, {0, 5, 1, 2}, "eff_eta", "5loss", false, true);
  makeMultiPlot(1, 0, {0, 5, 1, 2}, "ntrk_pt3", "5loss", true, true);

  // make kill L1 plots
  makeMultiPlot(0, 0, {0, 3, 4, 8, 2}, "eff_eta", "killL1", false, true);
  makeMultiPlot(0, 0, {0, 3, 4, 8, 2}, "ntrk_pt3", "killL1", true, true);

  makeMultiPlot(1, 0, {0, 3, 4, 8, 2}, "eff_eta", "killL1", false, true);
  makeMultiPlot(1, 0, {0, 3, 4, 8, 2}, "ntrk_pt3", "killL1", true, true);

  // make kill L5 plots
  makeMultiPlot(0, 0, {0, 7, 1}, "eff_eta", "killL5", false, true);
  makeMultiPlot(0, 0, {0, 7, 1}, "ntrk_pt3", "killL5", true, true);

  makeMultiPlot(1, 0, {0, 7, 1}, "eff_eta", "killL5", false, true);
  makeMultiPlot(1, 0, {0, 7, 1}, "ntrk_pt3", "killL5", true, true);

  // make eta efficiency plot for different quadrants
  for(auto& is : {2, 5, 6, 8})
  {
    std::string ss = std::to_string(is);

    TCanvas c;

    TLegend* l = new TLegend(0.5, 0.25, 0.85, 0.55);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h["eff_eta_0_1_" + ss]->SetLineColor(63);
    h["eff_eta_0_1_" + ss]->SetMarkerColor(63);

    h["eff_eta_0_0_0"]->Draw("p");
    h["eff_eta_0_0_" + ss]->Draw("p,same");
    h["eff_eta_0_1_" + ss]->Draw("p,same");

    l->AddEntry(h["eff_eta_0_0_0"], SCENARIO_P[0].c_str(), "pl");
    l->AddEntry(h["eff_eta_0_0_" + ss], QUADRANT_P[0].c_str(), "pl");
    l->AddEntry(h["eff_eta_0_1_" + ss], QUADRANT_P[1].c_str(), "pl");

    l->Draw();

    mySmallText(0.2, 0.5, 1, SAMPLE_P[0]);
    mySmallText(0.2, 0.4, 1, SCENARIO_P[is]);

    std::string f_name = "plots/" + SAMPLE[0] + "/eff_eta_q01_f0" + ss + ".pdf";
    gPad->SetGridy();
    c.SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;
  }

  // look at track eta disributions for 1% loss
  for(auto match : {"match_", ""}) {
    for(auto& trunc : {"", "_noTrunc"}) {
      for(auto& is : {0, 1}) { // iterate through samples, not scenarios

        std::string ss = std::to_string(is);
        std::string h_name;

        TCanvas c;

        TLegend* l = new TLegend(0.5, 0.25, 0.85, 0.55);
        l->SetFillStyle(0);
        l->SetBorderSize(0);
        l->SetTextSize(0.04);
        l->SetTextFont(42);

        h_name = match + std::string("tp_eta_") + ss + "_0_0" + trunc;
        TH1F* h_f0 = new TH1F(h_name.c_str(), ";Tracking particle #eta; Tracking particles / 0.1", 50, -2.5, 2.5);
        copyHistEntries(h_f0, h[h_name], 50);

        h_name = match + std::string("tp_eta_") + ss + "_0_6" + trunc;
        TH1F* h_f6 = new TH1F(h_name.c_str(), ";Tracking particle #eta; Tracking particles / 0.1", 50, -2.5, 2.5);
        copyHistEntries(h_f6, h[h_name], 50);
        h_f6->SetLineColor(4);
        h_f6->SetMarkerColor(4);

        h_f0->Draw("p");
        h_f6->Draw("p,same");

        l->AddEntry(h_f0, SCENARIO_P[0].c_str(), "pl");
        l->AddEntry(h_f6, SCENARIO_P[6].c_str(), "pl");
        
        l->Draw();

        std::string f_name = "plots/" + SAMPLE[is] + "/" + QUADRANT[0] + "/" + match + "tp_eta_f06" + trunc + ".pdf";
        gPad->SetGridy();
        c.SaveAs(f_name.c_str());
        gPad->SetGridy(0);

        delete l;
      }
    }
  }
}

// -----------------------------------------------------------------------------


void copyHistEntries(TH1F* h_ret, TH1F* h_copy, int n_bins) {

  for(int i = 1; i <= n_bins; i++) {
    h_ret->SetBinContent(i, h_copy->GetBinContent(i));
    h_ret->SetBinError(i, h_copy->GetBinError(i));
  }
}


void readHistograms(int s, int q, vector<int> scenarios, int n, bool truncation) {

  std::string h_name, f_name;
  std::string suffix = "_" + std::to_string(s) + "_" + std::to_string(q) + "_";

  for(auto &is : scenarios) {

    f_name = "results";
    f_name += "/" + SAMPLE[s];
    f_name += "/" + QUADRANT[q];
    f_name += "/f" + std::to_string(is) + "_e" + std::to_string(n);
    if(!truncation) f_name += "_noTrunc";
    f_name += "/output_" + SAMPLE[s] + ".root";

    TFile* f = TFile::Open(f_name.c_str());

    h_name = "eff_eta" + suffix + std::to_string(is);
    if(!truncation) h_name += "_noTrunc";
    h[h_name] = f->Get<TH1F>("eff_eta");
    h[h_name]->SetMinimum(0.0);
    h[h_name]->SetMaximum(1.1);
    h[h_name]->SetLineColor(COLOR[is]);
    h[h_name]->SetMarkerStyle(is == 0 ? MARKER[0] : MARKER[1]);
    h[h_name]->SetMarkerSize(MARKER_SIZE);
    h[h_name]->SetMarkerColor(COLOR[is]);

    h_name = "ntrk_pt3" + suffix + std::to_string(is);
    if(!truncation) h_name += "_noTrunc";
    h[h_name] = f->Get<TH1F>("ntrk_pt3");
    h[h_name]->Scale(1.0 / n);
    h[h_name]->GetYaxis()->SetTitle("Fraction of events");
    h[h_name]->SetLineColor(COLOR[is]);
    h[h_name]->SetMarkerStyle(s == 0 ? MARKER[0] : MARKER[1]);
    h[h_name]->SetMarkerSize(MARKER_SIZE);
    h[h_name]->SetMarkerColor(COLOR[is]);

    h_name = "resVsEta_z0_68" + suffix + std::to_string(is);
    if(!truncation) h_name += "_noTrunc";
    h[h_name] = f->Get<TH1F>("resVsEta_z0_68");
    h[h_name]->GetXaxis()->SetRangeUser(0.0, 2.4);
    h[h_name]->SetMinimum(0.0);
    h[h_name]->SetMaximum(2.0);
    h[h_name]->SetLineColor(COLOR[is]);
    h[h_name]->SetMarkerStyle(s == 0 ? MARKER[0] : MARKER[3]);
    h[h_name]->SetMarkerSize(MARKER_SIZE);
    h[h_name]->SetMarkerColor(COLOR[is]);

    h_name = "resVsEta_z0_90" + suffix + std::to_string(is);
    if(!truncation) h_name += "_noTrunc";
    h[h_name] = f->Get<TH1F>("resVsEta_z0_90");
    h[h_name]->GetXaxis()->SetRangeUser(0.0, 2.4);
    h[h_name]->SetMinimum(0.0);
    h[h_name]->SetMaximum(2.0);
    h[h_name]->SetLineColor(COLOR[is]);
    h[h_name]->SetMarkerStyle(s == 0 ? MARKER[2] : MARKER[4]);
    h[h_name]->SetMarkerSize(MARKER_SIZE);
    h[h_name]->SetMarkerColor(COLOR[is]);

    h_name = "match_tp_eta" + suffix + std::to_string(is);
    if(!truncation) h_name += "_noTrunc";
    h[h_name] = f->Get<TH1F>("match_tp_eta");
    if(h[h_name]) {
      h[h_name]->SetMinimum(0.0);
      h[h_name]->SetMaximum(1.1);
      h[h_name]->SetLineColor(COLOR[is]);
      h[h_name]->SetMarkerStyle(is == 0 ? MARKER[0] : MARKER[1]);
      h[h_name]->SetMarkerSize(MARKER_SIZE);
      h[h_name]->SetMarkerColor(COLOR[is]);
    }
    else {
      if(debug)
        std::cout << f_name << " does not contain match_tp_eta histogram." << std::endl;
    }

    h_name = "tp_eta" + suffix + std::to_string(is);
    if(!truncation) h_name += "_noTrunc";
    h[h_name] = f->Get<TH1F>("tp_eta");
    if(h[h_name]) {
      h[h_name]->SetMinimum(0.0);
      h[h_name]->SetMaximum(1.1);
      h[h_name]->SetLineColor(COLOR[is]);
      h[h_name]->SetMarkerStyle(is == 0 ? MARKER[0] : MARKER[1]);
      h[h_name]->SetMarkerSize(MARKER_SIZE);
      h[h_name]->SetMarkerColor(COLOR[is]);
    }
    else {
      if(debug)
        std::cout << f_name << " does not contain tp_eta histogram." << std::endl;
    }
  }
}


void makeResidualIntervalPlot(int s, int q, vector<int> scenarios, std::string name, std::string type) {

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

  std::string suffix = "_" + std::to_string(s) + "_" + std::to_string(q) + "_";
  bool drawn = false;
  for(auto &is : scenarios) {
    std::string h68 = name + "_68" + suffix + std::to_string(is);
    std::string h90 = name + "_90" + suffix + std::to_string(is);
    h[h68]->Draw("p,same");
    h[h90]->Draw("p,same");
    l1->AddEntry(h[h68], SCENARIO_P[is].c_str(), "pl");
    if(!drawn) {
      l2->AddEntry(h[h68], "68%", "p");
      l2->AddEntry(h[h90], "90%", "p");
      drawn = true;
    }
  }

  l1->Draw();
  l2->Draw();

  std::string f_name = "plots/" + SAMPLE[s] + "/" + QUADRANT[q] + "/" + name + "_interval_" + type + ".pdf";
  c.SaveAs(f_name.c_str());

  delete l1;
  delete l2;
}


void makeMultiPlot(int s, int q, vector<int> scenarios, std::string name, std::string type, bool plot_log, bool truncation) {

  TCanvas c;

  TLegend* l = new TLegend(0.6, 0.25, 0.85, 0.55);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetTextSize(0.04);
  l->SetTextFont(42);

  std::string suffix = "_" + std::to_string(s) + "_" + std::to_string(q) + "_";
  for(auto &is : scenarios) {
    std::string h_name = name + suffix + std::to_string(is);
    if(!truncation) h_name += "_noTrunc";
    h[h_name]->Draw("p,same");
    l->AddEntry(h[h_name], SCENARIO_P[is].c_str(), "pl");
  }

  l->Draw();

  std::string f_name = "plots/" + SAMPLE[s] + "/" + QUADRANT[q] + "/" + name + "_" + type;
  if(!truncation) f_name += "_noTrunc";
  gPad->SetGridy();
  c.SaveAs((f_name + ".pdf").c_str());
  gPad->SetGridy(0);

  if(plot_log) {
    gPad->SetLogy();
    c.SaveAs((f_name + "_log.pdf").c_str());
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


void mySmallText(Double_t x, Double_t y, Color_t color, std::string text) {

  Double_t tsize = 0.044;
  TLatex l;
  l.SetTextSize(tsize);
  l.SetNDC();
  l.SetTextColor(color);
  l.DrawLatex(x, y, text.c_str());
}
