#include "../include/Constants.hh"
#include "../include/SmallText.hh"
#include "../include/Config.hh"
#include "../include/Style.hh"


void PlotResVsEtaZ0Interval() {

  SetPlotStyle();

  std::string sample = SAMPLES[SAMPLE];

  std::string f0_name = "../results/" + sample + "_f0e9000/output_" + sample + ".root";
  TFile* f0 = TFile::Open(f0_name.c_str());

  TH1F* h0_68 = f0->Get<TH1F>("resVsEta_z0_68");
  h0_68->GetXaxis()->SetRangeUser(0.0, 2.4);
  h0_68->SetMinimum(0.0);
  h0_68->SetMaximum(2.0);
  h0_68->SetMarkerSize(MARKER_SIZE);
  h0_68->SetMarkerStyle(20);

  TH1F* h0_90 = f0->Get<TH1F>("resVsEta_z0_90");
  h0_90->GetXaxis()->SetRangeUser(0.0, 2.4);
  h0_90->SetMinimum(0.0);
  h0_90->SetMaximum(2.0);
  h0_90->SetMarkerSize(MARKER_SIZE);
  h0_90->SetMarkerStyle(24);

  for(int s = 1; s <= N_FAIL_SCENARIOS; s++) {

    std::string f_name = "../results/" + sample + "_f" + std::to_string(s) + "e9000/output_" + sample + ".root";
    TFile* f = TFile::Open(f_name.c_str());

    TH1F* h_68 = f->Get<TH1F>("resVsEta_z0_68");
    h_68->GetXaxis()->SetRangeUser(0.0, 2.4);
    h_68->SetMinimum(0.0);
    h_68->SetMaximum(2.0);
    h_68->SetMarkerSize(MARKER_SIZE);
    h_68->SetMarkerStyle(21);
    h_68->SetMarkerColor(COLOR[s]);
    h_68->SetLineColor(COLOR[s]);

    TH1F* h_90 = f->Get<TH1F>("resVsEta_z0_90");
    h_90->GetXaxis()->SetRangeUser(0.0, 2.4);
    h_90->SetMinimum(0.0);
    h_90->SetMaximum(2.0);
    h_90->SetMarkerSize(MARKER_SIZE);
    h_90->SetMarkerStyle(25);
    h_90->SetMarkerColor(COLOR[s]);
    h_90->SetLineColor(COLOR[s]);

    TCanvas c;

    h0_68->Draw("p");
    h0_90->Draw("p,same");
    h_68->Draw("p,same");
    h_90->Draw("p,same");

    TLegend* l1 = new TLegend(0.2, 0.65, 0.5, 0.85);
    l1->SetFillStyle(0);
    l1->SetBorderSize(0);
    l1->SetTextSize(0.04);
    l1->SetTextFont(42);

    l1->AddEntry(h0_68, FAIL_SCENARIOS[0].c_str(), "pl");
    l1->AddEntry(h_68, FAIL_SCENARIOS[s].c_str(), "pl");

    l1->Draw();

    TLegend* l2 = new TLegend(0.5, 0.65, 0.75, 0.85);
    l2->SetFillStyle(0);
    l2->SetBorderSize(0);
    l2->SetTextSize(0.04);
    l2->SetTextFont(42);

    l2->AddEntry(h0_68, "68%", "p");
    l2->AddEntry(h0_90, "90%", "p");

    l2->Draw();

    c.SetRightMargin(0.09);
    c.SetLeftMargin(0.15);
    c.SetBottomMargin(0.15);

    MySmallText(0.2, 0.55, 1, SAMPLE_LATEX[SAMPLE]);

    f_name = "../plots/" + sample + "_resVsEta_z0_interval_f" + std::to_string(s) + ".pdf";
    c.SaveAs(f_name.c_str());

    delete l1;
    delete l2;
  }
}
