#ifndef _HTAUTAU_METRECOILCORRECTION_H_
#define _HTAUTAU_METRECOILCORRECTION_H_

#include "AnalysisTool/DataForm.h"
#include "RecoilCorrector.hh"
#include "TLorentzVector.h"
#include "Math/VectorUtil.h"

class MEtRecoilCorrection
{
 public:
  MEtRecoilCorrection(GenParticle boson);
  ~MEtRecoilCorrection(){ delete corrector_;};

  TLorentzVector RecoilCorrectedMET(TLorentzVector pfMet_, LorentzVector lepLeg1_, LorentzVector lepLeg2_, GenParticle boson, int nJets_);

 private:
  RecoilCorrector *corrector_;
};


MEtRecoilCorrection::MEtRecoilCorrection(GenParticle boson)
{
  if(boson.PDGId() == 23) {
    corrector_ = new RecoilCorrector("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_zmm53XRR_2012_njet.root");
    corrector_->addMCFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_zmm53XRR_2012_njet.root");
    corrector_->addDataFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_datamm53XRR_2012_njet.root");
  }
  else if(TMath::Abs(boson.PDGId()) == 24) {
    corrector_ = new RecoilCorrector("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_wjets53X_20pv_njet.root");
    corrector_->addMCFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_zmm53XRR_2012_njet.root");
    corrector_->addDataFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_datamm53XRR_2012_njet.root");
  }
  else if(boson.PDGId() == 25 || boson.PDGId() == 35 || boson.PDGId() == 36) {
    corrector_ = new RecoilCorrector("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_higgs53X_20pv_njet.root");
    corrector_->addMCFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_zmm53XRR_2012_njet.root");
    corrector_->addDataFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_datamm53XRR_2012_njet.root");
  }
  else
    corrector_ = 0;
}


TLorentzVector MEtRecoilCorrection::RecoilCorrectedMET(TLorentzVector pfMet_, LorentzVector lepLeg1_, LorentzVector lepLeg2_, GenParticle boson, int nJets_)
{
  double newPfMetPt_ = pfMet_.Pt(); 
  double newPfMetPhi_ = pfMet_.Phi();
  
  double u1 = 0; double u2 = 0;
  LorentzVector genVP4_(0, 0, 0, 0);
  LorentzVector genVisLeg1_(0, 0, 0, 0);
  LorentzVector genVisLeg2_(0, 0, 0, 0);
  LorentzVector finalLepLeg1_(0, 0, 0, 0);
  LorentzVector finalLepLeg2_(0, 0, 0, 0);
  LorentzVector diLepton_(0, 0, 0, 0);
  vector<GenParticle> daughters;
  
  // case -I   
  if( boson.PDGId() == 23 || boson.PDGId() == 25 || boson.PDGId() == 35 || boson.PDGId() == 36 ) { 
    
    for(unsigned int i = 0; i < boson.NumDaughters(); ++i) {
      const GenParticle daughter = boson.GetDaughter(i);
      if(TMath::Abs(daughter.PDGId()) == 15){
	daughters.push_back(daughter);
      }
    }
    
    for(size_t i = 0; i < daughters.size(); i++) {
      if(daughters[i].PDGId() == -15) { //for tau-
	genVisLeg1_ = daughters[i].P4();
	for(int j = 0; j < daughters[i].NumDaughters(); ++j){
	  const GenParticle daughter2 = daughters[i].GetDaughter(j);
	  int daughter2Id = daughter2.PDGId();
	  int daughter2Status = daughter2.Status();
	  
	  if((fabs(daughter2Id)==12 || fabs(daughter2Id)==14 || fabs(daughter2Id)==16) && daughter2Status==1 )
	    genVisLeg1_ -= daughter2.P4();
	}
      }
      
      if(daughters[i].PDGId() == 15){ //for tau+
	genVisLeg2_ = daughters[i].P4();
	for(int j = 0; j < daughters[i].NumDaughters(); ++j){
	  const GenParticle daughter2 = daughters[i].GetDaughter(j);
	  int daughter2Id = daughter2.PDGId();
	  int daughter2Status = daughter2.Status();
	  
	  if((fabs(daughter2Id)==12 || fabs(daughter2Id)==14 || fabs(daughter2Id)==16) && daughter2Status==1 )
	    genVisLeg2_ -= daughter2.P4();
	}
      }
    }
  
    // finalLeg1, finalLeg2  
    if(genVisLeg1_.Pt() > 0) {
      if(ROOT::Math::VectorUtil::DeltaR(genVisLeg1_, lepLeg1_) < 0.3)
	finalLepLeg1_ = lepLeg1_;
      else if(ROOT::Math::VectorUtil::DeltaR(genVisLeg1_, lepLeg2_) < 0.3)
	finalLepLeg1_ = lepLeg2_;
      else
	finalLepLeg1_ = genVisLeg1_;
    }
    
    if(genVisLeg2_.Pt() > 0) {
      if(ROOT::Math::VectorUtil::DeltaR(genVisLeg2_, lepLeg1_) < 0.3)
	finalLepLeg2_ = lepLeg1_;
      else if(ROOT::Math::VectorUtil::DeltaR(genVisLeg2_, lepLeg2_) < 0.3)
	finalLepLeg2_ = lepLeg2_;
      else
	finalLepLeg2_ = genVisLeg2_;
    }

    if(finalLepLeg1_.Pt() > 0 && finalLepLeg2_.Pt() > 0) 
      diLepton_ = finalLepLeg1_ + finalLepLeg2_;
    else diLepton_ = lepLeg1_ + lepLeg2_;
  }
  

  // case -II   
if( TMath::Abs(boson.PDGId()) == 24) {
    for(unsigned int i = 0; i < boson.NumDaughters(); ++i) {
      const GenParticle daughter = boson.GetDaughter(i);
      if( ( TMath::Abs(daughter.PDGId()) == 11 || TMath::Abs(daughter.PDGId()) ==  13 || TMath::Abs(daughter.PDGId()) ==  15 ) && daughter.Status() == 1)
	daughters.push_back(daughter);
    }
    
    for (size_t i = 0; i < daughters.size(); i++) {
      //subcase-I
      if (TMath::Abs(daughters[i].PDGId()) == 15) { //for tau
	genVisLeg1_ = daughters[i].P4();
	
	for(int j = 0; j < daughters[i].NumDaughters(); ++j){
	  const GenParticle daughter2 = daughters[i].GetDaughter(j);
	  int daughter2Id = daughter2.PDGId();
	  int daughter2Status = daughter2.Status();
	  if((fabs(daughter2Id)==12 || fabs(daughter2Id)==14 || fabs(daughter2Id)==16) && daughter2Status==1 )
	    genVisLeg1_ -= daughter2.P4();
	}
      }
      //subcase-II
      else if(TMath::Abs(daughters[i].PDGId()) == 11 || TMath::Abs(daughters[i].PDGId()) == 13 ) { //for ele, mu
	genVisLeg1_ = daughters[i].P4();
      }
    } 

    // finalLeg1
    if(genVisLeg1_.Pt() > 0){
      if(ROOT::Math::VectorUtil::DeltaR(genVisLeg1_, lepLeg1_) < 0.3)
	finalLepLeg1_ = lepLeg1_;
      else if(ROOT::Math::VectorUtil::DeltaR(genVisLeg1_, lepLeg2_) < 0.3) 
	finalLepLeg1_ = lepLeg2_;
      else
	finalLepLeg1_ = genVisLeg1_;
    }
    
    if(finalLepLeg1_.Pt() > 0) 
      diLepton_ = finalLepLeg1_;
    else diLepton_ = lepLeg1_;
  }// if( boson.PDGId() == 24);  
  

  // TypeI Correction
  TLorentzVector corMET_;
  corrector_->CorrectType1(newPfMetPt_,newPfMetPhi_,genVP4_.Pt() ,genVP4_.Phi(), diLepton_.Pt(),diLepton_.Phi(), u1, u2 , 0 , 0, TMath::Min(nJets_,2) );
  corMET_.SetPtEtaPhiM(newPfMetPt_, 0, newPfMetPhi_, 0);
 
  return corMET_;
}

#endif // _HTAUTAU

