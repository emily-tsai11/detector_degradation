#include "../include/Constants.hh"
#include "../include/SmallText.hh"
#include "../include/Config.hh"
#include "../include/Style.hh"


void PlotEffEta() {

  SetPlotStyle();

  std::string sample = SAMPLES[SAMPLE];

  std::string f0_name = "../results/" + sample + "_f0e9000/output_" + sample + ".root";
  TFile* f0 = TFile::Open(f0_name.c_str());

  TH1F* h0 = f0->Get<TH1F>("eff_eta");
  h0->SetMinimum(0.0);
  h0->SetMaximum(1.1);
  h0->SetMarkerSize(MARKER_SIZE);
  h0->SetMarkerStyle(20);

  for(auto& s : {1, 2, 3, 4, 5, 6, 7, 8}) {

    std::string f_name = "../results/" + sample + "_f" + std::to_string(s) + "e9000/output_" + sample + ".root";
    TFile* f = TFile::Open(f_name.c_str());

    TH1F* h = f->Get<TH1F>("eff_eta");
    h->SetMinimum(0.0);
    h->SetMaximum(1.1);
    h->SetMarkerSize(MARKER_SIZE);
    h->SetMarkerStyle(21);
    h->SetMarkerColor(COLOR[s]);
    h->SetLineColor(COLOR[s]);

    TCanvas c;

    h0->Draw("p");
    h->Draw("p,same");

    TLegend* l = new TLegend(0.6, 0.4, 0.85, 0.55);
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

    MySmallText(0.2, 0.5, 1, SAMPLE_LATEX[SAMPLE]);

    f_name = "../plots/" + sample + "_eff_eta_f" + std::to_string(s) + ".pdf";

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

    h0->Draw("p");

    l->AddEntry(h0, FAIL_SCENARIOS[0].c_str(), "pl");

    for(auto& s : CASES[i].second) {

      std::string f_name = "../results/" + sample + "_f" + std::to_string(s) + "e9000/output_" + sample + ".root";
      TFile* f = TFile::Open(f_name.c_str());

      TH1F* h = f->Get<TH1F>("eff_eta");
      h->SetMinimum(0.0);
      h->SetMaximum(1.1);
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

    MySmallText(0.2, 0.5, 1, SAMPLE_LATEX[SAMPLE]);

    std::string f_name = "../plots/" + sample + "_eff_eta_" + CASES[i].first + ".pdf";

    gPad->SetGridy();
    c.SaveAs(f_name.c_str());
    gPad->SetGridy(0);

    delete l;
  }
}
