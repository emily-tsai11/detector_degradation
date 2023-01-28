void PlotAll() {

  gROOT->ProcessLine(".x PlotEffEta.cc");
  gROOT->ProcessLine(".x PlotNTrkPt3.cc");
  gROOT->ProcessLine(".x PlotResVsEtaZ0Interval.cc");

}
