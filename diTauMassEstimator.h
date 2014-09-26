#ifndef _HTAUTAUANALYSIS_diTauMassEstimator_H_
#define _HTAUTAUANALYSIS_diTauMassEstimator_H_

#include "AnalysisTool/DataForm.h"
#include "Common/Config.h"
#include "TauAnalysis/CandidateTools/interface/NSVfitStandaloneAlgorithm.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "TMatrixD.h"
#include <vector>

class diTauMassEstimator
{
public:
  diTauMassEstimator();
  ~diTauMassEstimator(){};
  
  double ComputeDiTauMass(LorentzVector leg1, LorentzVector leg2, LorentzVector met, TMatrixD cov);
};

#endif 

diTauMassEstimator::diTauMassEstimator()
{

}

double diTauMassEstimator::ComputeDiTauMass(LorentzVector leg1, LorentzVector leg2, LorentzVector met, TMatrixD cov)
{
  std::vector<NSVfitStandalone::MeasuredTauLepton> measuredTauLeptons; 
  NSVfitStandalone::Vector measuredMET( met.px(), met.py(), 0); 
  measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(NSVfitStandalone::kHadDecay, leg1)); 
  measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(NSVfitStandalone::kHadDecay, leg2)); 
  NSVfitStandaloneAlgorithm algo(measuredTauLeptons, measuredMET, cov, 0); 
  algo.addLogM(false); 
  //algo.integrateMarkovChain(); 
  algo.integrateVEGAS(); 
  double diTauNSVfitMass_ = algo.getMass();

  return diTauNSVfitMass_;
}
