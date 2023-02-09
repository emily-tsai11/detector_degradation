#include "../include/Config.hh"
#include "../include/ConfigBuilder.hh"
#include "../include/PlotHelperFunctions.hh"


void plot_trk_chi2rphi_dof();


void PlotTrkChi2RPhiDOF(int sample = SAMPLE) {

  if(sample == 0 || sample == -1) {
    if(!stubKiller0Set) ConfigBuilder(0);
    plot_trk_chi2rphi_dof();
  }

  if(sample == 1 || sample == -1) {
    if(!stubKiller1Set) ConfigBuilder(1);
    plot_trk_chi2rphi_dof();
  }

  if(sample == 2 || sample == -1) {
    if(!biasRailSet) ConfigBuilder(2);
    plot_trk_chi2rphi_dof();
  }
}


void plot_trk_chi2rphi_dof() {

  std::string f_name;

  SetPlotStyle();

  TFile* f_ref = TFile::Open(F_REF.c_str());

  TH1F* h_ref = f_ref->Get<TH1F>("trk_chi2rphi_dof");
  h_ref->SetMarkerSize(0.0);

  for(int i = 0; i < N_CASES.size(); i++) {

    TCanvas c;

    TLegend* l = new TLegend(0.62, 0.68, 0.9, 0.9);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "l");

    TFile* f;
    std::vector<int> cases;
    GetCases(CASES[i], cases);
    for(auto& s : cases) {

      f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("trk_chi2rphi_dof");
      h->SetMarkerSize(0.0);
      h->SetLineColor(COLOR[s]);
      h->GetXaxis()->SetRangeUser(0.0, 2.2);
      h->GetXaxis()->SetTitle("L1 Track #chi^{2}_{r-#phi} / D.O.F.");
      h->GetYaxis()->SetTitle("# L1 Tracks / 0.2");

      h->Draw("hist,e,same");

      l->AddEntry(h, LATEX_FAILS[s].c_str(), "l");
    }

    h_ref->Draw("hist,e,same");

    l->Draw();

    c.SetRightMargin(0.09);
    c.SetLeftMargin(0.15);
    c.SetTopMargin(0.06);
    c.SetBottomMargin(0.15);

    MySmallText(0.7, 0.55, 1, LATEX_SAMPLE);

    f_name = "../plots/" + N_SAMPLE + "_trk_chi2rphi_dof_" + N_CASES[i] + ".pdf";
    c.SaveAs(f_name.c_str());

    delete l;

    f->Close();
  }

  if(DO_DETAILED_PLOTS) {

    h_ref->GetXaxis()->SetRangeUser(0.0, 2.2);
    h_ref->GetXaxis()->SetTitle("L1 Track #chi^{2}_{r-#phi} / D.O.F.");
    h_ref->GetYaxis()->SetTitle("# L1 Tracks / 0.2");

    for(int s = 0; s < F_FAILS.size(); s++) {

      if(F_FAILS[s].length() == 0) continue;

      TFile* f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("trk_chi2rphi_dof");
      h->SetMarkerSize(0.0);
      h->SetLineColor(COLOR[s]);

      TCanvas c;

      h_ref->Draw("hist,e");
      h->Draw("hist,e,same");

      TLegend* l = new TLegend(0.62, 0.68, 0.9, 0.9);
      l->SetFillStyle(0);
      l->SetBorderSize(0);
      l->SetTextSize(0.04);
      l->SetTextFont(42);

      l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "l");
      l->AddEntry(h, LATEX_FAILS[s].c_str(), "l");

      l->Draw();

      c.SetRightMargin(0.09);
      c.SetLeftMargin(0.15);
      c.SetTopMargin(0.06);
      c.SetBottomMargin(0.15);

      MySmallText(0.7, 0.55, 1, LATEX_SAMPLE);

      f_name = "../plots/" + N_SAMPLE + "_trk_chi2rphi_dof_" + N_SAVE + std::to_string(s) + ".pdf";
      c.SaveAs(f_name.c_str());

      delete l;

      f->Close();
    }
  }

  f_ref->Close();
}
