void PlotAll() {

  gROOT->ProcessLine(".x ConfigBuilder.cc");
  gROOT->ProcessLine(".x PlotEffEta.cc");
  gROOT->ProcessLine(".x PlotEffPt.cc");
  gROOT->ProcessLine(".x PlotEffd0.cc");
  gROOT->ProcessLine(".x PlotNTrkPt2.cc");
  gROOT->ProcessLine(".x PlotNTrkPt3.cc");
  gROOT->ProcessLine(".x PlotResVsEtaZ0Interval.cc");

  if(DO_DETAILED_PLOTS) {
    gROOT->ProcessLine(".x PlotEffz0.cc");
    gROOT->ProcessLine(".x PlotEffPhi.cc");
  }

}
