#include "../include/Config.hh"


void PlotAll() {

  gROOT->ProcessLine(".x PlotEffEta.cc");
  gROOT->ProcessLine(".x PlotEffPt.cc");
  gROOT->ProcessLine(".x PlotEffD0.cc");
  gROOT->ProcessLine(".x PlotNTrkPt2.cc");
  gROOT->ProcessLine(".x PlotNTrkPt3.cc");
  gROOT->ProcessLine(".x PlotResVsEtaZ0Interval.cc");

  if(DO_DETAILED_PLOTS) {
    gROOT->ProcessLine(".x PlotEffZ0.cc");
    gROOT->ProcessLine(".x PlotEffPhi.cc");
  }

  if(DO_QUALITY_PLOTS) {
    gROOT->ProcessLine(".x PlotTrkChi2.cc");
    gROOT->ProcessLine(".x PlotTrkChi2DOF.cc");
    gROOT->ProcessLine(".x PlotTrkChi2RPhi.cc");
    gROOT->ProcessLine(".x PlotTrkChi2RPhiDOF.cc");
    gROOT->ProcessLine(".x PlotTrkChi2RZ.cc");
    gROOT->ProcessLine(".x PlotTrkChi2RZDOF.cc");
    gROOT->ProcessLine(".x PlotTrkBendChi2.cc");
  }
}
