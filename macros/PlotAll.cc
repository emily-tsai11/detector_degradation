void PlotAll() {

  gROOT->ProcessLine(".x ConfigBuilder.cc");
  gROOT->ProcessLine(".x PlotEffEta.cc");
  gROOT->ProcessLine(".x PlotNTrkPt2.cc");
  gROOT->ProcessLine(".x PlotNTrkPt3.cc");
  gROOT->ProcessLine(".x PlotResVsEtaZ0Interval.cc");

}
