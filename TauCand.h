#ifndef _WHANALYSIS_TAUCAND_H_
#define _WHANALYSIS_TAUCAND_H_

#include "AnalysisTool/DataForm.h"
#include "Common/Config.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

class TauCand
{
public:
  TauCand(const class TauWP& wp, const Tau& tau, double sf);
  TauCand(const Tau& tau, double sf);

  float Pt()  const { return p4.Pt();  }
  float Eta() const { return p4.Eta(); }
  float Phi() const { return p4.Phi(); }
  float E()   const { return p4.E();   }

  TriggerObject trigObj;

  // These are not const so that they can be used with a std::vector<>.
  // You should only use const TauCands, though.
  int Charge;
  float NewEMFraction;
  unsigned int NumTracks;
  float Dxy;
  float Dz;

  int PFChargedHadrCands_size;
  int PFGammaCands_size;

  float IsoNeutralsPt;
  float IsoChargedPt;
  float IsoGammaPt;
  float Iso3Hits;
  float TrackIso;
  float leadpfchargedhadrcandpt;
  LorentzVector leadpfchargedhadrcandp4;

  bool L1trigger_match;
  bool decayModeFinding;
  bool decayModeFindingOldDMs;
  bool decayModeFindingNewDMs;

  bool byLooseCombinedIsolationDeltaBetaCorr3Hits;
  bool byMediumCombinedIsolationDeltaBetaCorr3Hits;
  bool byTightCombinedIsolationDeltaBetaCorr3Hits;
  bool byLooseIsolationMVA3oldDMwLT;
  bool byMediumIsolationMVA3oldDMwLT;
  bool byTightIsolationMVA3oldDMwLT;
  bool byVTightIsolationMVA3oldDMwLT;

  /*
  bool byLooseCombinedIsolationDeltaBetaCorr;
  bool byMediumCombinedIsolationDeltaBetaCorr;
  bool byTightCombinedIsolationDeltaBetaCorr;

  bool againstElectronLooseMVA3;
  bool againstElectronMediumMVA3;
  bool againstElectronTightMVA3;
  */

  bool againstElectronLoose;
  bool againstElectronMedium;
  bool againstElectronTight;
  bool againstElectronLooseMVA5;
  bool againstElectronMediumMVA5;
  bool againstElectronTightMVA5;

  bool againstMuonLoose;
  bool againstMuonMedium;
  bool againstMuonTight;
  bool againstMuonLoose3;
  bool againstMuonTight3;
  bool againstMuonLooseMVA;
  bool againstMuonMediumMVA;
  bool againstMuonTightMVA;

  double corr;
  TLorentzVector p4;

};

#endif // _WHANALYSIS_TAUCAND_H_
