#include "../include/ConfigBuilder.hh"
#include "../include/SmallText.hh"
#include "../include/Style.hh"


void PlotNTrkPt3() {

  if(!configHasRun) gROOT->ProcessLine(".x ConfigBuilder.cc");

  std::string f_name;

  SetPlotStyle();

  TFile* f_ref = TFile::Open(F_REF.c_str());

  TH1F* h_ref = f_ref->Get<TH1F>("ntrk_pt3");
  // h_ref->GetXaxis()->SetRangeUser(0.0, 300.0);
  h_ref->Scale(1.0 / 9000.0);
  h_ref->GetYaxis()->SetTitle("Fraction of events");
  h_ref->SetMarkerSize(MARKER_SIZE);
  h_ref->SetMarkerStyle(20);

  for(int s = 0; s < F_FAILS.size(); s++) {

    if(F_FAILS[s].length() == 0) continue;

    TFile* f = TFile::Open(F_FAILS[s].c_str());

    TH1F* h = f->Get<TH1F>("ntrk_pt3");
    h->Scale(1.0 / 9000.0);
    h->GetYaxis()->SetTitle("Fraction of events");
    h->SetMarkerSize(MARKER_SIZE);
    h->SetMarkerStyle(21);
    h->SetMarkerColor(COLOR[s]);
    h->SetLineColor(COLOR[s]);

    TCanvas c;

    h_ref->Draw("p");
    h->Draw("p,same");

    TLegend* l = new TLegend(0.62, 0.68, 0.9, 0.9);
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

    MySmallText(0.7, 0.55, 1, LATEX_SAMPLE);

    f_name = "../plots/" + N_SAMPLE + "_ntrk_pt3_" + N_SAVE + std::to_string(s);

    gPad->SetLogy();
    c.SaveAs((f_name + "_log.pdf").c_str());
    gPad->SetLogy(0);

    if(DO_DETAILED_PLOTS)
    {
      gPad->SetGridy();
      c.SaveAs((f_name + ".pdf").c_str());
      gPad->SetGridy(0);

      // zoomed plots
      h_ref->GetXaxis()->SetRangeUser(0.0, 150.0);

      gPad->SetGridy();
      c.SaveAs((f_name + "_z.pdf").c_str());
      gPad->SetGridy(0);

      gPad->SetLogy();
      c.SaveAs((f_name + "_z_log.pdf").c_str());
      gPad->SetLogy(0);

      h_ref->GetXaxis()->SetRangeUser(0.0, 300.0);
    }

    delete l;
  }

  for(int i = 0; i < CASES.size(); i++) {

    TCanvas c;

    TLegend* l = new TLegend(0.62, 0.68, 0.9, 0.9);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h_ref->Draw("p");

    l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "pl");

    for(auto& s : CASES[i].second) {

      TFile* f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("ntrk_pt3");
      h->Scale(1.0 / 9000.0);
      h->GetYaxis()->SetTitle("Fraction of events");
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

    MySmallText(0.7, 0.55, 1, LATEX_SAMPLE);

    f_name = "../plots/" + N_SAMPLE + "_ntrk_pt3_" + CASES[i].first;

    gPad->SetLogy();
    c.SaveAs((f_name + "_log.pdf").c_str());
    gPad->SetLogy(0);

    if(DO_DETAILED_PLOTS)
    {
      gPad->SetGridy();
      c.SaveAs((f_name + ".pdf").c_str());
      gPad->SetGridy(0);

      // zoomed plots
      h_ref->GetXaxis()->SetRangeUser(0.0, 150.0);

      gPad->SetGridy();
      c.SaveAs((f_name + "_z.pdf").c_str());
      gPad->SetGridy(0);

      gPad->SetLogy();
      c.SaveAs((f_name + "_z_log.pdf").c_str());
      gPad->SetLogy(0);

      h_ref->GetXaxis()->SetRangeUser(0.0, 300.0);
    }

    delete l;
  }
}
