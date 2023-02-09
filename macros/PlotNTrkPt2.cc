#include "../include/Config.hh"
#include "../include/ConfigBuilder.hh"
#include "../include/PlotHelperFunctions.hh"


void plot_ntrk_pt2();


void PlotNTrkPt2(int sample = SAMPLE) {

  if(sample == 0 || sample == -1) {
    if(!stubKiller0Set) ConfigBuilder(0);
    plot_ntrk_pt2();
  }

  if(sample == 1 || sample == -1) {
    if(!stubKiller1Set) ConfigBuilder(1);
    plot_ntrk_pt2();
  }

  if(sample == 2 || sample == -1) {
    if(!biasRailSet) ConfigBuilder(2);
    plot_ntrk_pt2();
  }
}


void plot_ntrk_pt2() {

  std::string f_name;

  SetPlotStyle();

  TFile* f_ref = TFile::Open(F_REF.c_str());

  TH1F* h_ref = f_ref->Get<TH1F>("ntrk_pt2");
  h_ref->GetXaxis()->SetRangeUser(0.0, 320.0);
  h_ref->Scale(1.0 / N_EVENTS[0]);
  h_ref->GetYaxis()->SetTitle("Fraction of events");
  h_ref->SetMarkerSize(0.5);
  h_ref->SetMarkerStyle(20);

  for(int i = 0; i < N_CASES.size(); i++) {

    TCanvas c;

    TLegend* l = new TLegend(LX1, 0.68, LX2, 0.9);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h_ref->Draw("p");

    l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "pl");

    TFile* f;
    std::vector<int> cases;
    GetCases(CASES[i], cases);
    for(auto& s : cases) {

      f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("ntrk_pt2");
      h->Scale(1.0 / N_EVENTS[s]);
      h->GetYaxis()->SetTitle("Fraction of events");
      h->SetMarkerSize(0.5);
      h->SetMarkerStyle(20);
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      h->Draw("p,same");

      l->AddEntry(h, LATEX_FAILS[s].c_str(), "pl");
    }

    l->Draw();

    c.SetRightMargin(0.09);
    c.SetLeftMargin(0.15);
    c.SetBottomMargin(0.15);

    MySmallText(TX, 0.55, 1, LATEX_SAMPLE);

    f_name = "../plots/" + N_SAMPLE + "_ntrk_pt2_" + N_CASES[i];

    gPad->SetLogy();
    c.SaveAs((f_name + "_log.pdf").c_str());
    gPad->SetLogy(0);

    if(DO_EXTRA_DETAILED_PLOTS)
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

      h_ref->GetXaxis()->SetRangeUser(0.0, 320.0);
    }

    delete l;

    f->Close();
  }

  if(DO_DETAILED_PLOTS) {

    for(int s = 0; s < F_FAILS.size(); s++) {

      if(F_FAILS[s].length() == 0) continue;

      TFile* f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("ntrk_pt2");
      h->Scale(1.0 / N_EVENTS[s]);
      h->GetYaxis()->SetTitle("Fraction of events");
      h->SetMarkerSize(0.5);
      h->SetMarkerStyle(20);
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      TCanvas c;

      h_ref->Draw("p");
      h->Draw("p,same");

      TLegend* l = new TLegend(LX1, 0.68, LX2, 0.9);
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

      MySmallText(TX, 0.55, 1, LATEX_SAMPLE);

      f_name = "../plots/" + N_SAMPLE + "_ntrk_pt2_" + N_SAVE + std::to_string(s);

      gPad->SetLogy();
      c.SaveAs((f_name + "_log.pdf").c_str());
      gPad->SetLogy(0);

      if(DO_EXTRA_DETAILED_PLOTS)
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

        h_ref->GetXaxis()->SetRangeUser(0.0, 320.0);
      }

      delete l;

      f->Close();
    }
  }

  f_ref->Close();
}
