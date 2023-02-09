#include "../include/Config.hh"
#include "../include/ConfigBuilder.hh"
#include "../include/PlotHelperFunctions.hh"


void plot_eff_phi();


void PlotEffPhi(int sample = SAMPLE) {

  if(sample == 0 || sample == -1) {
    if(!stubKiller0Set) ConfigBuilder(0);
    plot_eff_phi();
  }

  if(sample == 1 || sample == -1) {
    if(!stubKiller1Set) ConfigBuilder(1);
    plot_eff_phi();
  }

  if(sample == 2 || sample == -1) {
    if(!biasRailSet) ConfigBuilder(2);
    plot_eff_phi();
  }
}


void plot_eff_phi() {

  std::string f_name;

  SetPlotStyle();

  TFile* f_ref = TFile::Open(F_FAILS[0].c_str());

  TH1F* h_ref = f_ref->Get<TH1F>("eff_phi");
  h_ref->SetMinimum(EFF_PHI_MIN);
  h_ref->SetMaximum(EFF_PHI_MAX);

  for(int i = 0; i < N_CASES.size(); i++) {

    TCanvas* c = new TCanvas("c", "c", 800, 600);

    TPad* p_eff = new TPad("p_eff", "p_eff", 0.0, 0.3, 1.0, 1.0);
    p_eff->SetBottomMargin(0.0);
    p_eff->Draw();

    TLegend* l = new TLegend(0.2, EFF_LY1, 0.45, EFF_LY2);
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
    std::vector<int> cases;
    GetCases(CASES[i], cases);
    for(auto& s : cases) {

      f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("eff_phi");
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      // Sumw2 already calculated
      TH1F* h_ratio = (TH1F*) h->Clone();
      h_ratio->Divide(h_ref);
      h_ratio->SetMinimum(0.5);
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
    f_name = "../plots/" + N_SAMPLE + "_eff_phi_" + N_CASES[i] + ".pdf";
    c->SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;
    delete c;

    f->Close();
  }

  if(DO_DETAILED_PLOTS) {

    for(int s = 1; s < F_FAILS.size(); s++) {

      if(F_FAILS[s].length() == 0) continue;

      TFile* f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("eff_phi");
      h->SetMinimum(EFF_PHI_MIN);
      h->SetMaximum(EFF_PHI_MAX);
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      // Sumw2 already calculated
      TH1F* h_ratio = (TH1F*) h->Clone();
      h_ratio->Divide(h_ref);
      h_ratio->SetMinimum(0.5);
      h_ratio->SetMaximum(RATIO_MAX);
      h_ratio->GetXaxis()->SetTitleSize(0.12);
      h_ratio->GetXaxis()->SetTitleOffset(1.0);
      h_ratio->GetXaxis()->SetLabelSize(0.12);
      h_ratio->GetYaxis()->SetNdivisions(404);
      h_ratio->GetYaxis()->SetTitle("Ratio");
      h_ratio->GetYaxis()->SetTitleSize(0.12);
      h_ratio->GetYaxis()->SetTitleOffset(0.61);
      h_ratio->GetYaxis()->SetLabelSize(0.12);

      TCanvas* c = new TCanvas("c", "c", 800, 600);

      TPad* p_eff = new TPad("p_eff", "p_eff", 0.0, 0.3, 1.0, 1.0);
      p_eff->SetBottomMargin(0.0);
      p_eff->Draw();

      TLegend* l = new TLegend(0.2, EFF_LY1, 0.45, EFF_LY2);
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
      h->Draw("p,same");
      l->AddEntry(h, LATEX_FAILS[s].c_str(), "pl");
      c->cd();

      p_ratio->cd();
      h_ratio->Draw("ep");
      c->cd();

      p_eff->cd();
      l->Draw();
      MySmallText(EFF_TX, EFF_TY, 1, LATEX_SAMPLE);
      c->cd();

      gPad->SetGridy();
      f_name = "../plots/" + N_SAMPLE + "_eff_phi_" + N_SAVE + std::to_string(s) + ".pdf";
      c->SaveAs(f_name.c_str());
      gPad->SetGridy(0);

      delete l;
      delete c;

      f->Close();
    }
  }

  f_ref->Close();
}
