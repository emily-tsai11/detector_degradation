#include "../include/Constants.hh"
#include "../include/SmallText.hh"
#include "../include/Config.hh"
#include "../include/Style.hh"


void PlotNTrkPt2() {

  SetPlotStyle();

  std::string sample = SAMPLES[SAMPLE];

  std::string f0_name = "../results/" + sample + "_f0e9000/output_" + sample + ".root";
  TFile* f0 = TFile::Open(f0_name.c_str());

  TH1F* h0 = f0->Get<TH1F>("ntrk_pt2");
  h0->GetXaxis()->SetRangeUser(0.0, 300.0);
  h0->Scale(1.0 / 9000.0);
  h0->GetYaxis()->SetTitle("Fraction of events");
  h0->SetMarkerSize(MARKER_SIZE);
  h0->SetMarkerStyle(20);

  for(int s = 1; s <= N_FAIL_SCENARIOS; s++) {

    std::string f_name = "../results/" + sample + "_f" + std::to_string(s) + "e9000/output_" + sample + ".root";
    TFile* f = TFile::Open(f_name.c_str());

    TH1F* h = f->Get<TH1F>("ntrk_pt2");
    h->Scale(1.0 / 9000.0);
    h->GetYaxis()->SetTitle("Fraction of events");
    h->SetMarkerSize(MARKER_SIZE);
    h->SetMarkerStyle(21);
    h->SetMarkerColor(COLOR[s]);
    h->SetLineColor(COLOR[s]);

    TCanvas c;

    h0->Draw("p");
    h->Draw("p,same");

    TLegend* l = new TLegend(
      SAMPLE == 1 ? 0.62 : 0.18,
      0.68,
      SAMPLE == 1 ? 0.9 : 0.38,
      0.9);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    l->AddEntry(h0, FAIL_SCENARIOS[0].c_str(), "pl");
    l->AddEntry(h, FAIL_SCENARIOS[s].c_str(), "pl");

    l->Draw();

    c.SetRightMargin(0.09);
    c.SetLeftMargin(0.15);
    c.SetBottomMargin(0.15);

    MySmallText(
      SAMPLE == 1 ? 0.7 : 0.18,
      0.55, 1, SAMPLE_LATEX[SAMPLE]);

    f_name = "../plots/" + sample + "_ntrk_pt2_f" + std::to_string(s);

    gPad->SetLogy();
    c.SaveAs((f_name + "_log.pdf").c_str());
    gPad->SetLogy(0);

    if(DO_DETAILED_PLOTS)
    {
      gPad->SetGridy();
      c.SaveAs((f_name + ".pdf").c_str());
      gPad->SetGridy(0);

      // zoomed plots
      h0->GetXaxis()->SetRangeUser(0.0, 150.0);

      gPad->SetGridy();
      c.SaveAs((f_name + "_z.pdf").c_str());
      gPad->SetGridy(0);

      gPad->SetLogy();
      c.SaveAs((f_name + "_z_log.pdf").c_str());
      gPad->SetLogy(0);

      h0->GetXaxis()->SetRangeUser(0.0, 300.0);
    }

    delete l;
  }

  for(int i = 0; i < CASES.size(); i++) {

    TCanvas c;

    TLegend* l = new TLegend(
      SAMPLE == 1 ? 0.62 : 0.18,
      0.68,
      SAMPLE == 1 ? 0.9 : 0.38,
      0.9);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h0->Draw("p");

    l->AddEntry(h0, FAIL_SCENARIOS[0].c_str(), "pl");

    for(auto& s : CASES[i].second) {

      std::string f_name = "../results/" + sample + "_f" + std::to_string(s) + "e9000/output_" + sample + ".root";
      TFile* f = TFile::Open(f_name.c_str());

      TH1F* h = f->Get<TH1F>("ntrk_pt2");
      h->Scale(1.0 / 9000.0);
      h->GetYaxis()->SetTitle("Fraction of events");
      h->SetMarkerSize(MARKER_SIZE);
      h->SetMarkerStyle(21);
      h->SetMarkerColor(COLOR[s]);
      h->SetLineColor(COLOR[s]);

      h->Draw("p,same");

      l->AddEntry(h, FAIL_SCENARIOS[s].c_str(), "pl");
    }

    l->Draw();

    c.SetRightMargin(0.09);
    c.SetLeftMargin(0.15);
    c.SetBottomMargin(0.15);

    MySmallText(
      SAMPLE == 1 ? 0.7 : 0.18,
      0.55, 1, SAMPLE_LATEX[SAMPLE]);

    std::string f_name = "../plots/" + sample + "_ntrk_pt2_" + CASES[i].first;

    gPad->SetLogy();
    c.SaveAs((f_name + "_log.pdf").c_str());
    gPad->SetLogy(0);

    if(DO_DETAILED_PLOTS)
    {
      gPad->SetGridy();
      c.SaveAs((f_name + ".pdf").c_str());
      gPad->SetGridy(0);

      // zoomed plots
      h0->GetXaxis()->SetRangeUser(0.0, 150.0);

      gPad->SetGridy();
      c.SaveAs((f_name + "_z.pdf").c_str());
      gPad->SetGridy(0);

      gPad->SetLogy();
      c.SaveAs((f_name + "_z_log.pdf").c_str());
      gPad->SetLogy(0);

      h0->GetXaxis()->SetRangeUser(0.0, 300.0);
    }

    delete l;
  }
}
