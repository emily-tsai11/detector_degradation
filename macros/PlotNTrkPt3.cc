#include "../include/Constants.hh"
#include "../include/Style.hh"

void PlotNTrkPt3() {

  SetPlotStyle();

  std::string sample = SAMPLES[0];

  std::string f0_name = "../results/" + sample + "_f0e9000/output_" + sample + ".root";
  TFile* f0 = TFile::Open(f0_name.c_str());

  TH1F* h0 = f0->Get<TH1F>("ntrk_pt3");
  h0->Scale(1.0 / 9000.0);
  h0->GetYaxis()->SetTitle("Fraction of events");
  h0->SetMarkerSize(MARKER_SIZE);
  h0->SetMarkerStyle(20);

  for(auto& s : {1, 2, 3, 4, 5, 6, 7, 8}) {

    std::string f_name = "../results/" + sample + "_f" + std::to_string(s) + "e9000/output_" + sample + ".root";
    TFile* f = TFile::Open(f_name.c_str());

    TH1F* h = f->Get<TH1F>("ntrk_pt3");
    h->Scale(1.0 / 9000.0);
    h->GetYaxis()->SetTitle("Fraction of events");
    h->SetMarkerSize(MARKER_SIZE);
    h->SetMarkerStyle(21);
    h->SetMarkerColor(COLOR[s]);
    h->SetLineColor(COLOR[s]);

    TCanvas c;

    h0->Draw("p");
    h->Draw("p,same");

    TLegend* l = new TLegend(0.6, 0.65, 0.85, 0.9);
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

    f_name = "../plots/" + sample + "_ntrk_pt3_f" + std::to_string(s);

    gPad->SetGridy();
    c.SaveAs((f_name + ".pdf").c_str());
    gPad->SetGridy(0);

    gPad->SetLogy();
    c.SaveAs((f_name + "_log.pdf").c_str());
    gPad->SetLogy(0);

    // zoomed plots
    h0->GetXaxis()->SetRangeUser(0.0, 150.0);

    gPad->SetGridy();
    c.SaveAs((f_name + "_z.pdf").c_str());
    gPad->SetGridy(0);

    gPad->SetLogy();
    c.SaveAs((f_name + "_z_log.pdf").c_str());
    gPad->SetLogy(0);

    h0->GetXaxis()->SetRangeUser(0.0, 300.0);

    delete l;

  }

  for(int i = 0; i < CASES.size(); i++) {

    TCanvas c;

    TLegend* l = new TLegend(0.6, 0.65, 0.85, 0.9);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(42);

    h0->Draw("p");

    l->AddEntry(h0, FAIL_SCENARIOS[0].c_str(), "pl");

    for(auto& s : CASES[i].second) {

      std::string f_name = "../results/" + sample + "_f" + std::to_string(s) + "e9000/output_" + sample + ".root";
      TFile* f = TFile::Open(f_name.c_str());

      TH1F* h = f->Get<TH1F>("ntrk_pt3");
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

    std::string f_name = "../plots/" + sample + "_ntrk_pt3_" + CASES[i].first;

    gPad->SetGridy();
    c.SaveAs((f_name + ".pdf").c_str());
    gPad->SetGridy(0);

    gPad->SetLogy();
    c.SaveAs((f_name + "_log.pdf").c_str());
    gPad->SetLogy(0);

    // zoomed plots
    h0->GetXaxis()->SetRangeUser(0.0, 150.0);

    gPad->SetGridy();
    c.SaveAs((f_name + "_z.pdf").c_str());
    gPad->SetGridy(0);

    gPad->SetLogy();
    c.SaveAs((f_name + "_z_log.pdf").c_str());
    gPad->SetLogy(0);

    h0->GetXaxis()->SetRangeUser(0.0, 300.0);

    delete l;
  }

}
