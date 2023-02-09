#include "../include/Config.hh"
#include "../include/ConfigBuilder.hh"
#include "../include/PlotHelperFunctions.hh"


void plot_ntrk_pt3();


void PlotNTrkPt3(int sample = SAMPLE) {

  if(sample == 0 || sample == -1) {
    if(!stubKiller0Set) ConfigBuilder(0);
    plot_ntrk_pt3();
  }

  if(sample == 1 || sample == -1) {
    if(!stubKiller1Set) ConfigBuilder(1);
    plot_ntrk_pt3();
  }

  if(sample == 2 || sample == -1) {
    if(!biasRailSet) ConfigBuilder(2);
    plot_ntrk_pt3();
  }
}


void plot_ntrk_pt3() {

  std::string f_name;
  char text[500];

  SetPlotStyle();

  TFile* f_ref = TFile::Open(F_FAILS[0].c_str());

  TH1F* h_ref = f_ref->Get<TH1F>("ntrk_pt3");
  h_ref->GetXaxis()->SetRangeUser(0.0, 130.0);
  h_ref->Scale(1.0 / N_EVENTS[0]);
  h_ref->GetYaxis()->SetTitle("Fraction of events");
  h_ref->SetMarkerSize(0.5);
  h_ref->SetMarkerStyle(20);

  for(int i = 0; i < N_CASES.size(); i++) {

    TCanvas c;

    TLegend* l = new TLegend(0.65, 0.72, 0.84, 0.93);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    TLegend* l_mean = new TLegend(0.8, 0.45, 0.95, 0.7);
    l_mean->SetFillStyle(0);
    l_mean->SetBorderSize(0);
    l_mean->SetTextSize(0.04);
    l_mean->SetTextFont(42);

    h_ref->Draw("p");

    l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "pl");
    snprintf(text, 500, "Means");
    l_mean->AddEntry((TObject*) 0, text, "");
    snprintf(text, 500, "%.2f", h_ref->GetMean());
    l_mean->AddEntry((TObject*) 0, text, "");

    TFile* f;
    std::vector<int> cases;
    GetCases(CASES[i], cases);
    for(auto& s : cases) {

      f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("ntrk_pt3");
      h->Scale(1.0 / N_EVENTS[s]);
      h->GetYaxis()->SetTitle("Fraction of events");
      h->SetMarkerSize(0.5);
      h->SetMarkerStyle(20);
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      h->Draw("p,same");

      l->AddEntry(h, LATEX_FAILS[s].c_str(), "pl");
      snprintf(text, 500, "%.2f", h->GetMean());
      TLegendEntry* l_entry = l_mean->AddEntry((TObject*) 0, text, "");
      l_entry->SetTextColor(COLOR[s]);
    }

    l->Draw();
    l_mean->Draw();

    c.SetLeftMargin(0.15);
    c.SetTopMargin(0.06);
    c.SetBottomMargin(0.15);

    MySmallText(TX, TY, 1, LATEX_SAMPLE);

    gPad->SetLogy();
    f_name = "../plots/" + N_SAMPLE + "_ntrk_pt3_" + N_CASES[i];
    c.SaveAs((f_name + "_log.pdf").c_str());

    if(NTRK_PT3_MAX_ZOOM > 0.0) {
      h_ref->GetXaxis()->SetRangeUser(0.0, NTRK_PT3_MAX_ZOOM);
      c.SaveAs((f_name + "_z_log.pdf").c_str());
      h_ref->GetXaxis()->SetRangeUser(0.0, 130.0);
    }
    gPad->SetLogy(0);

    delete l;
    delete l_mean;

    f->Close();
  }

  if(DO_DETAILED_PLOTS) {

    for(int s = 1; s < F_FAILS.size(); s++) {

      if(F_FAILS[s].length() == 0) continue;

      TFile* f = TFile::Open(F_FAILS[s].c_str());

      TH1F* h = f->Get<TH1F>("ntrk_pt3");
      h->Scale(1.0 / N_EVENTS[s]);
      h->GetYaxis()->SetTitle("Fraction of events");
      h->SetMarkerSize(0.5);
      h->SetMarkerStyle(20);
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      TCanvas c;

      h_ref->Draw("p");
      h->Draw("p,same");

      TLegend* l = new TLegend(0.65, 0.72, 0.84, 0.93);
      l->SetFillStyle(0);
      l->SetBorderSize(0);
      l->SetTextSize(0.04);
      l->SetTextFont(42);

      TLegend* l_mean = new TLegend(0.8, 0.45, 0.95, 0.7);
      l_mean->SetFillStyle(0);
      l_mean->SetBorderSize(0);
      l_mean->SetTextSize(0.04);
      l_mean->SetTextFont(42);

      l->AddEntry(h_ref, LATEX_FAILS[0].c_str(), "pl");
      snprintf(text, 500, "Means");
      l_mean->AddEntry((TObject*) 0, text, "");
      snprintf(text, 500, "%.2f", h_ref->GetMean());
      l_mean->AddEntry((TObject*) 0, text, "");

      l->AddEntry(h, LATEX_FAILS[s].c_str(), "pl");
      snprintf(text, 500, "%.2f", h->GetMean());
      TLegendEntry* l_entry = l_mean->AddEntry((TObject*) 0, text, "");
      l_entry->SetTextColor(COLOR[s]);

      l->Draw();
      l_mean->Draw();

      c.SetLeftMargin(0.15);
      c.SetTopMargin(0.06);
      c.SetBottomMargin(0.15);

      MySmallText(TX, TY, 1, LATEX_SAMPLE);

      gPad->SetLogy();
      f_name = "../plots/" + N_SAMPLE + "_ntrk_pt3_" + N_SAVE + std::to_string(s);
      c.SaveAs((f_name + "_log.pdf").c_str());

      if(NTRK_PT3_MAX_ZOOM > 0.0) {
        h_ref->GetXaxis()->SetRangeUser(0.0, NTRK_PT3_MAX_ZOOM);
        c.SaveAs((f_name + "_z_log.pdf").c_str());
        h_ref->GetXaxis()->SetRangeUser(0.0, 130.0);
      }
      gPad->SetLogy(0);

      delete l;
      delete l_mean;

      f->Close();
    }
  }

  f_ref->Close();
}
