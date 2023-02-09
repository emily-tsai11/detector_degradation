#include "../include/Config.hh"
#include "../include/ConfigBuilder.hh"
#include "../include/PlotHelperFunctions.hh"


void plot_resVsEta_z0_interval();


void PlotResVsEtaZ0Interval(int sample = SAMPLE) {

  if(sample == 0 || sample == -1) {
    if(!stubKiller0Set) ConfigBuilder(0);
    plot_resVsEta_z0_interval();
  }

  if(sample == 1 || sample == -1) {
    if(!stubKiller1Set) ConfigBuilder(1);
    plot_resVsEta_z0_interval();
  }

  if(sample == 2 || sample == -1) {
    if(!biasRailSet) ConfigBuilder(2);
    plot_resVsEta_z0_interval();
  }
}


void plot_resVsEta_z0_interval() {

  SetPlotStyle();

  TFile* f_ref = TFile::Open(F_REF.c_str());

  TH1F* h_ref_68 = f_ref->Get<TH1F>("resVsEta_z0_68");
  h_ref_68->GetXaxis()->SetRangeUser(0.0, 2.4);
  h_ref_68->SetMinimum(0.0);
  h_ref_68->SetMaximum(2.0);
  h_ref_68->SetMarkerStyle(20);

  TH1F* h_ref_90 = f_ref->Get<TH1F>("resVsEta_z0_90");
  h_ref_90->GetXaxis()->SetRangeUser(0.0, 2.4);
  h_ref_90->SetMinimum(0.0);
  h_ref_90->SetMaximum(2.0);
  h_ref_90->SetMarkerStyle(24);

  for(int s = 0; s < F_FAILS.size(); s++) {

    if(F_FAILS[s].length() == 0) continue;

    TFile* f = TFile::Open(F_FAILS[s].c_str());

    TH1F* h_68 = f->Get<TH1F>("resVsEta_z0_68");
    h_68->GetXaxis()->SetRangeUser(0.0, 2.4);
    h_68->SetMinimum(0.0);
    h_68->SetMaximum(2.0);
    h_68->SetMarkerStyle(21);
    h_68->SetMarkerColor(COLOR[s]);
    h_68->SetLineColor(COLOR[s]);

    TH1F* h_90 = f->Get<TH1F>("resVsEta_z0_90");
    h_90->GetXaxis()->SetRangeUser(0.0, 2.4);
    h_90->SetMinimum(0.0);
    h_90->SetMaximum(2.0);
    h_90->SetMarkerStyle(25);
    h_90->SetMarkerColor(COLOR[s]);
    h_90->SetLineColor(COLOR[s]);

    TCanvas c;

    h_ref_68->Draw("p");
    h_ref_90->Draw("p,same");
    h_68->Draw("p,same");
    h_90->Draw("p,same");

    TLegend* l1 = new TLegend(0.2, 0.65, 0.5, 0.85);
    l1->SetFillStyle(0);
    l1->SetBorderSize(0);
    l1->SetTextSize(0.04);
    l1->SetTextFont(42);

    l1->AddEntry(h_ref_68, LATEX_FAILS[0].c_str(), "pl");
    l1->AddEntry(h_68, LATEX_FAILS[s].c_str(), "pl");

    l1->Draw();

    TLegend* l2 = new TLegend(0.65, 0.65, 0.9, 0.85);
    l2->SetFillStyle(0);
    l2->SetBorderSize(0);
    l2->SetTextSize(0.04);
    l2->SetTextFont(42);

    l2->AddEntry(h_ref_68, "68%", "p");
    l2->AddEntry(h_ref_90, "90%", "p");

    l2->Draw();

    c.SetRightMargin(0.09);
    c.SetLeftMargin(0.15);
    c.SetBottomMargin(0.15);

    MySmallText(0.2, 0.55, 1, LATEX_SAMPLE);

    std::string f_name = "../plots/" + N_SAMPLE + "_resVsEta_z0_interval_" + N_SAVE + std::to_string(s) + ".pdf";
    c.SaveAs(f_name.c_str());

    delete l1;
    delete l2;

    f->Close();
  }
}
