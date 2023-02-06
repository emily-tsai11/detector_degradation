#include "../include/ConfigBuilder.hh"
#include "../include/SmallText.hh"
#include "../include/Style.hh"


void PlotEffEta() {

  if(!configHasRun) gROOT->ProcessLine(".x ConfigBuilder.cc");

  std::string f_name;

  SetPlotStyle();

  TFile* f_ref = TFile::Open(F_REF.c_str());

  TH1F* h_ref = f_ref->Get<TH1F>("eff_eta");
  h_ref->SetMinimum(0.0);
  h_ref->SetMaximum(1.1);
  h_ref->SetMarkerSize(MARKER_SIZE);
  h_ref->SetMarkerStyle(20);

  for(int s = 0; s < F_FAILS.size(); s++) {

    if(F_FAILS[s].length() == 0) continue;

    TFile* f = TFile::Open(F_FAILS[s].c_str());

    TH1F* h = f->Get<TH1F>("eff_eta");
    h->SetMinimum(0.0);
    h->SetMaximum(1.1);
    h->SetMarkerSize(MARKER_SIZE);
    h->SetMarkerStyle(21);
    h->SetMarkerColor(COLOR[s]);
    h->SetLineColor(COLOR[s]);

    TCanvas c;

    h_ref->Draw("p");
    h->Draw("p,same");

    TLegend* l = new TLegend(0.6, 0.4, 0.85, 0.55);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "pl");
    l->AddEntry(h, LATEX_FAILS[s].c_str(), "pl");

    l->Draw();

    c.SetRightMargin(0.09);
    c.SetLeftMargin(0.15);
    c.SetBottomMargin(0.15);

    MySmallText(0.2, 0.5, 1, LATEX_SAMPLE);

    f_name = "../plots/" + N_SAMPLE + "_eff_eta_" + N_SAVE + std::to_string(s) + ".pdf";

    gPad->SetGridy();
    c.SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;
  }

  for(int i = 0; i < CASES.size(); i++) {

    TCanvas c;

    TLegend* l = new TLegend(0.6, 0.25, 0.85, 0.55);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h_ref->Draw("p");

    l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "pl");

    for(auto& s : CASES[i].second) {

      TFile* f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("eff_eta");
      h->SetMinimum(0.0);
      h->SetMaximum(1.1);
      h->SetMarkerSize(MARKER_SIZE);
      h->SetMarkerStyle(21);
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      h->Draw("p,same");

      l->AddEntry(h, LATEX_FAILS[s].c_str(), "pl");
    }

    l->Draw();

    c.SetRightMargin(0.09);
    c.SetLeftMargin(0.15);
    c.SetBottomMargin(0.15);

    MySmallText(0.2, 0.5, 1, LATEX_SAMPLE);

    f_name = "../plots/" + N_SAMPLE + "_eff_eta_" + CASES[i].first + ".pdf";

    gPad->SetGridy();
    c.SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;
  }
}
