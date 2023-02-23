#include "../include/Config.hh"
#include "../include/ConfigBuilder.hh"
#include "../include/PlotHelperFunctions.hh"


void check_tp_denom();
void make_eff_eta_plots();
void make_eff_pt_plots();


void AlgoTpDenom(int sample = SAMPLE) {

  // if(sample == 0 || sample == -1) {
  //   if(!stubKiller0Set) ConfigBuilder(0);
  //   check_tp_denom();
  // }

  // if(sample == 1 || sample == -1) {
  //   if(!stubKiller1Set) ConfigBuilder(1);
  //   check_tp_denom();
  // }

  if(sample == 2 || sample == -1) {
    if(!biasRail2Set) ConfigBuilder(2);
    check_tp_denom();
    // make_eff_eta_plots();
    // make_eff_pt_plots();
  }

  // if(sample == 3 || sample == -1) {
  //   if(!biasRail3Set) ConfigBuilder(3);
  //   check_tp_denom();
  // }
}


void check_tp_denom() {

  SetPlotStyle();

  char txt[500];

  std::cout << std::endl;

  TFile* f_noTPStubCut1 = TFile::Open("../results/TRK2026D88PU200MB2_noTPStubCut-v1_f0e8600/output_TRK2026D88PU200MB2_noTPStubCut-v1.root");
  TH1F* h_noTPStubCut1 = f_noTPStubCut1->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(no stub cut)/event = %.1f", h_noTPStubCut1->GetSum());
  std::cout << "reference file             : " << txt << std::endl;

  TFile* f_noTPStubCut5 = TFile::Open("../results/TRK2026D88PU200MB2_noTPStubCut-v5_f0e9000/output_TRK2026D88PU200MB2_noTPStubCut-v5.root");
  TH1F* h_noTPStubCut5 = f_noTPStubCut5->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(no stub cut)/event = %.1f", h_noTPStubCut5->GetSum());
  std::cout << "bias rail                  : " << txt << std::endl;

  TFile* f_noTPStubCut2 = TFile::Open("../results/TRK2026D88PU200MB2_noTPStubCut-v2_f0e9000/output_TRK2026D88PU200MB2_noTPStubCut-v2.root");
  TH1F* h_noTPStubCut2 = f_noTPStubCut2->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(no stub cut)/event = %.1f", h_noTPStubCut2->GetSum());
  std::cout << "bias rail + 1% bad strips  : " << txt << std::endl;

  TFile* f_noTPStubCut3 = TFile::Open("../results/TRK2026D88PU200MB2_noTPStubCut-v3_f0e8800/output_TRK2026D88PU200MB2_noTPStubCut-v3.root");
  TH1F* h_noTPStubCut3 = f_noTPStubCut3->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(no stub cut)/event = %.1f", h_noTPStubCut3->GetSum());
  std::cout << "bias rail + 5% bad strips  : " << txt << std::endl;

  TFile* f_noTPStubCut4 = TFile::Open("../results/TRK2026D88PU200MB2_noTPStubCut-v4_f0e9000/output_TRK2026D88PU200MB2_noTPStubCut-v4.root");
  TH1F* h_noTPStubCut4 = f_noTPStubCut4->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(no stub cut)/event = %.1f", h_noTPStubCut4->GetSum());
  std::cout << "bias rail + 10% bad strips : " << txt << std::endl;

  std::cout << std::endl;

  TFile* f1 = TFile::Open("../results/TRK2026D88PU200MB2-v1_f0e8600/output_TRK2026D88PU200MB2-v1.root");
  TH1F* h1 = f1->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(#geq 4 stubs in #geq 4 layers)/event = %.1f", h1->GetSum());
  std::cout << "reference file             : " << txt << std::endl;

  TFile* f5 = TFile::Open("../results/TRK2026D88PU200MB2-v5_f0e9000/output_TRK2026D88PU200MB2-v5.root");
  TH1F* h5 = f5->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(#geq 4 stubs in #geq 4 layers)/event = %.1f", h5->GetSum());
  std::cout << "bias rail                  : " << txt << std::endl;

  TFile* f2 = TFile::Open("../results/TRK2026D88PU200MB2-v2_f0e9000/output_TRK2026D88PU200MB2-v2.root");
  TH1F* h2 = f2->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(#geq 4 stubs in #geq 4 layers)/event = %.1f", h2->GetSum());
  std::cout << "bias rail + 1% bad strips  : " << txt << std::endl;

  TFile* f3 = TFile::Open("../results/TRK2026D88PU200MB2-v3_f0e8800/output_TRK2026D88PU200MB2-v3.root");
  TH1F* h3 = f3->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(#geq 4 stubs in #geq 4 layers)/event = %.1f", h3->GetSum());
  std::cout << "bias rail + 5% bad strips  : " << txt << std::endl;

  TFile* f4 = TFile::Open("../results/TRK2026D88PU200MB2-v4_f0e9000/output_TRK2026D88PU200MB2-v4.root");
  TH1F* h4 = f4->Get<TH1F>("tp_vspt");
  snprintf(txt, 500, "# TPs(#geq 4 stubs in #geq 4 layers)/event = %.1f", h4->GetSum());
  std::cout << "bias rail + 10% bad strips : " << txt << std::endl;

  std::cout << std::endl;

  // TCanvas* c_match_tp_eta = new TCanvas("c_match_tp_eta", "c_match_tp_eta", 800, 600);
  // 
  // TLegend* l = new TLegend(0.4, 0.2, 0.6, 0.5);
  // l->SetFillStyle(0);
  // l->SetBorderSize(0);
  // l->SetTextSize(0.04);
  // l->SetTextFont(42);
  // 
  // TH1F* h_match_tp_eta_v1 = f->Get<TH1F>("match_tp_eta");
  // h_match_tp_eta_v1->Draw("p");
  // l->AddEntry(h_match_tp_eta_v1, LATEX_FAILS[0].c_str(), "pl");
  // 
  // TFile* f5 = TFile::Open("../results/TRK2026D88PU200MB2-v5_f0e9000/output_TRK2026D88PU200MB2-v5.root");
  // TH1F* h_match_tp_eta_v5 = f5->Get<TH1F>("match_tp_eta");
  // h_match_tp_eta_v5->Draw("p,same");
  // h_match_tp_eta_v5->SetMarkerColor(COLOR[5]);
  // h_match_tp_eta_v5->SetLineColor(COLOR[5]);
  // l->AddEntry(h_match_tp_eta_v5, LATEX_FAILS[5].c_str(), "pl");
  // 
  // TFile* f2 = TFile::Open("../results/TRK2026D88PU200MB2-v2_f0e9000/output_TRK2026D88PU200MB2-v2.root");
  // TH1F* h_match_tp_eta_v2 = f2->Get<TH1F>("match_tp_eta");
  // h_match_tp_eta_v2->Draw("p,same");
  // h_match_tp_eta_v2->SetMarkerColor(COLOR[2]);
  // h_match_tp_eta_v2->SetLineColor(COLOR[2]);
  // l->AddEntry(h_match_tp_eta_v2, LATEX_FAILS[2].c_str(), "pl");
  // 
  // TFile* f3 = TFile::Open("../results/TRK2026D88PU200MB2-v3_f0e8800/output_TRK2026D88PU200MB2-v3.root");
  // TH1F* h_match_tp_eta_v3 = f3->Get<TH1F>("match_tp_eta");
  // h_match_tp_eta_v3->Draw("p,same");
  // h_match_tp_eta_v3->SetMarkerColor(COLOR[3]);
  // h_match_tp_eta_v3->SetLineColor(COLOR[3]);
  // l->AddEntry(h_match_tp_eta_v3, LATEX_FAILS[3].c_str(), "pl");
  // 
  // TFile* f4 = TFile::Open("../results/TRK2026D88PU200MB2-v4_f0e9000/output_TRK2026D88PU200MB2-v4.root");
  // TH1F* h_match_tp_eta_v4 = f4->Get<TH1F>("match_tp_eta");
  // h_match_tp_eta_v4->Draw("p,same");
  // h_match_tp_eta_v4->SetMarkerColor(COLOR[4]);
  // h_match_tp_eta_v4->SetLineColor(COLOR[4]);
  // l->AddEntry(h_match_tp_eta_v4, LATEX_FAILS[4].c_str(), "pl");
  // 
  // l->Draw();
  // 
  // gPad->SetGridy();
  // c_match_tp_eta->SaveAs("../plots/TRK2026D88PU200MB2_match_tp_eta_ploss.pdf");
  // gPad->SetGridy(0);
  // 
  // delete l;
}


void make_eff_eta_plots() {

  std::string f_name;

  SetPlotStyle();

  TFile* f_ref = TFile::Open("../results/TRK2026D88PU200MB2_noTPStubCut-v1_f0e8600/output_TRK2026D88PU200MB2_noTPStubCut-v1.root");
  TH1F* h_tp_eta = f_ref->Get<TH1F>("tp_eta");

  // calculate efficiency
  TFile* f_ref_num = TFile::Open("../results/TRK2026D88PU200MB2-v1_f0e8600/output_TRK2026D88PU200MB2-v1.root");
  TH1F* h_match_tp_eta = f_ref_num->Get<TH1F>("match_tp_eta");
  TH1F* h_ref = (TH1F*) h_match_tp_eta->Clone();
  h_ref->SetName("eff_eta");
  h_ref->GetYaxis()->SetTitle("Efficiency");
  h_ref->Divide(h_match_tp_eta, h_tp_eta, 1.0, 1.0, "B");
  h_ref->SetMinimum(EFF_ETA_MIN);
  h_ref->SetMaximum(EFF_ETA_MAX);

  std::string f2_name = "../results/TRK2026D88PU200MB2_noTPStubCut-v2_f0e9000/output_TRK2026D88PU200MB2_noTPStubCut-v2.root";
  std::string f3_name = "../results/TRK2026D88PU200MB2_noTPStubCut-v3_f0e8800/output_TRK2026D88PU200MB2_noTPStubCut-v3.root";
  std::string f4_name = "../results/TRK2026D88PU200MB2_noTPStubCut-v4_f0e9000/output_TRK2026D88PU200MB2_noTPStubCut-v4.root";
  std::string f5_name = "../results/TRK2026D88PU200MB2_noTPStubCut-v5_f0e9000/output_TRK2026D88PU200MB2_noTPStubCut-v5.root";

  for(int i = 0; i < N_CASES.size(); i++) {

    TCanvas* c = new TCanvas("c", "c", 800, 600);

    TPad* p_eff = new TPad("p_eff", "p_eff", 0.0, 0.3, 1.0, 1.0);
    p_eff->SetBottomMargin(0.0);
    p_eff->Draw();

    TLegend* l = new TLegend(EFF_LX1, EFF_LY1, EFF_LX2, EFF_LY2);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.05);
    l->SetTextFont(42);

    TPad* p_ratio = new TPad("p_ratio", "p_ratio", 0.0, 0.0, 1.0, 0.3);
    p_ratio->SetBottomMargin(0.3);
    p_ratio->SetTopMargin(0.0);
    p_ratio->Draw();

    p_eff->cd();
    h_ref->Draw("p");
    l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "pl");
    c->cd();

    TFile* f;
    TFile* f_num;
    std::vector<int> cases;
    GetCases(CASES[i], cases);
    for(auto& s : cases) {

      if(s == 2) f = TFile::Open(f2_name.c_str());
      if(s == 3) f = TFile::Open(f3_name.c_str());
      if(s == 4) f = TFile::Open(f4_name.c_str());
      if(s == 5) f = TFile::Open(f5_name.c_str());

      f_num = TFile::Open(F_FAILS[s].c_str());

      // calculate efficiency
      TH1F* h_tp_eta_ = f->Get<TH1F>("tp_eta");
      TH1F* h_match_tp_eta_ = f_num->Get<TH1F>("match_tp_eta");
      TH1F* h = (TH1F*) h_match_tp_eta_->Clone();
      h->SetName("eff_eta");
      h->GetYaxis()->SetTitle("Efficiency");
      h->Divide(h_match_tp_eta_, h_tp_eta_, 1.0, 1.0, "B");
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      // Sumw2 already calculated
      TH1F* h_ratio = (TH1F*) h->Clone();
      h_ratio->Divide(h_ref);
      h_ratio->SetMinimum(RATIO_MIN);
      h_ratio->SetMaximum(RATIO_MAX);
      h_ratio->GetXaxis()->SetTitleSize(0.12);
      h_ratio->GetXaxis()->SetTitleOffset(1.0);
      h_ratio->GetXaxis()->SetLabelSize(0.12);
      h_ratio->GetYaxis()->SetNdivisions(404);
      h_ratio->GetYaxis()->SetTitle("Ratio");
      h_ratio->GetYaxis()->SetTitleSize(0.12);
      h_ratio->GetYaxis()->SetTitleOffset(0.61);
      h_ratio->GetYaxis()->SetLabelSize(0.12);

      p_eff->cd();
      h->Draw("p,same");
      l->AddEntry(h, LATEX_FAILS[s].c_str(), "pl");
      c->cd();

      p_ratio->cd();
      h_ratio->Draw("ep,same");
      c->cd();
    }

    p_eff->cd();
    l->Draw();
    MySmallText(EFF_TX, EFF_TY, 1, LATEX_SAMPLE);
    c->cd();

    gPad->SetGridy();
    f_name = "../plots/" + N_SAMPLE + "_eff_eta_" + N_CASES[i] + "_adj.pdf";
    c->SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;
    delete c;

    f->Close();
  }
}


void make_eff_pt_plots() {

  std::string f_name;

  SetPlotStyle();

  TFile* f_ref = TFile::Open("../results/TRK2026D88PU200MB2_noTPStubCut-v1_f0e8600/output_TRK2026D88PU200MB2_noTPStubCut-v1.root");
  TH1F* h_tp_pt = f_ref->Get<TH1F>("tp_pt");

  // calculate efficiency
  TFile* f_ref_num = TFile::Open("../results/TRK2026D88PU200MB2-v1_f0e8600/output_TRK2026D88PU200MB2-v1.root");
  TH1F* h_match_tp_pt = f_ref_num->Get<TH1F>("match_tp_pt");
  TH1F* h_ref = (TH1F*) h_match_tp_pt->Clone();
  h_ref->SetName("eff_pt");
  h_ref->GetYaxis()->SetTitle("Efficiency");
  h_ref->Divide(h_match_tp_pt, h_tp_pt, 1.0, 1.0, "B");
  h_ref->SetMinimum(EFF_PT_MIN);
  h_ref->SetMaximum(EFF_PT_MAX);

  std::string f2_name = "../results/TRK2026D88PU200MB2_noTPStubCut-v2_f0e9000/output_TRK2026D88PU200MB2_noTPStubCut-v2.root";
  std::string f3_name = "../results/TRK2026D88PU200MB2_noTPStubCut-v3_f0e8800/output_TRK2026D88PU200MB2_noTPStubCut-v3.root";
  std::string f4_name = "../results/TRK2026D88PU200MB2_noTPStubCut-v4_f0e9000/output_TRK2026D88PU200MB2_noTPStubCut-v4.root";
  std::string f5_name = "../results/TRK2026D88PU200MB2_noTPStubCut-v5_f0e9000/output_TRK2026D88PU200MB2_noTPStubCut-v5.root";

  for(int i = 0; i < N_CASES.size(); i++) {

    TCanvas* c = new TCanvas("c", "c", 800, 600);

    TPad* p_eff = new TPad("p_eff", "p_eff", 0.0, 0.3, 1.0, 1.0);
    p_eff->SetBottomMargin(0.0);
    p_eff->Draw();

    TLegend* l = new TLegend(EFF_LX1, EFF_LY1, EFF_LX2, EFF_LY2);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.05);
    l->SetTextFont(42);

    TPad* p_ratio = new TPad("p_ratio", "p_ratio", 0.0, 0.0, 1.0, 0.3);
    p_ratio->SetBottomMargin(0.3);
    p_ratio->SetTopMargin(0.0);
    p_ratio->Draw();

    p_eff->cd();
    h_ref->Draw("p");
    l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "pl");
    c->cd();

    TFile* f;
    TFile* f_num;
    std::vector<int> cases;
    GetCases(CASES[i], cases);
    for(auto& s : cases) {

      std::cout << s << std::endl;

      if(s == 2) f = TFile::Open(f2_name.c_str());
      if(s == 3) f = TFile::Open(f3_name.c_str());
      if(s == 4) f = TFile::Open(f4_name.c_str());
      if(s == 5) f = TFile::Open(f5_name.c_str());

      f_num = TFile::Open(F_FAILS[s].c_str());

      // calculate efficiency
      TH1F* h_tp_pt_ = f->Get<TH1F>("tp_pt");
      TH1F* h_match_tp_pt_ = f_num->Get<TH1F>("match_tp_pt");
      TH1F* h = (TH1F*) h_match_tp_pt_->Clone();
      h->SetName("eff_pt");
      h->GetYaxis()->SetTitle("Efficiency");
      h->Divide(h_match_tp_pt_, h_tp_pt_, 1.0, 1.0, "B");
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      // Sumw2 already calculated
      TH1F* h_ratio = (TH1F*) h->Clone();
      h_ratio->Divide(h_ref);
      h_ratio->SetMinimum(RATIO_MIN);
      h_ratio->SetMaximum(RATIO_MAX);
      h_ratio->GetXaxis()->SetTitleSize(0.12);
      h_ratio->GetXaxis()->SetTitleOffset(1.0);
      h_ratio->GetXaxis()->SetLabelSize(0.12);
      h_ratio->GetYaxis()->SetNdivisions(404);
      h_ratio->GetYaxis()->SetTitle("Ratio");
      h_ratio->GetYaxis()->SetTitleSize(0.12);
      h_ratio->GetYaxis()->SetTitleOffset(0.61);
      h_ratio->GetYaxis()->SetLabelSize(0.12);

      p_eff->cd();
      h->Draw("p,same");
      l->AddEntry(h, LATEX_FAILS[s].c_str(), "pl");
      c->cd();

      p_ratio->cd();
      h_ratio->Draw("ep,same");
      c->cd();
    }

    p_eff->cd();
    l->Draw();
    MySmallText(EFF_TX, EFF_TY, 1, LATEX_SAMPLE);
    c->cd();

    gPad->SetGridy();
    f_name = "../plots/" + N_SAMPLE + "_eff_pt_" + N_CASES[i] + "_adj.pdf";
    c->SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;
    delete c;

    f->Close();
  }
}