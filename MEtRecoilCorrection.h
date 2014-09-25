#ifndef _HTAUTAU_METRECOILCORRECTION_H_
#define _HTAUTAU_METRECOILCORRECTION_H_

//#include "AnalysisTool/DataForm.h"
#include "RecoilCorrector.hh"
#include "TLorentzVector.h"
#include "Math/VectorUtil.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

class MEtRecoilCorrection
{
 public:
  MEtRecoilCorrection(std::string sampleName_);
  ~MEtRecoilCorrection(){ delete corrector_;};

  TLorentzVector RecoilCorrectedMET(TLorentzVector pfMet_, LorentzVector lepLeg1_, LorentzVector lepLeg2_,  LorentzVector genVisLeg1_, LorentzVector genVisLeg2_, int nJets_, std::string sampleName_);

 private:
  RecoilCorrector *corrector_;
};


MEtRecoilCorrection::MEtRecoilCorrection(std::string sampleName_)
{
  if(sampleName_.find("ZJET") != std::string::npos){
    corrector_ = new RecoilCorrector("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_zmm53XRR_2012_njet.root");
    corrector_->addMCFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_zmm53XRR_2012_njet.root");
    corrector_->addDataFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_datamm53XRR_2012_njet.root");
  }
  else if(sampleName_.find("WJET") != std::string::npos){
    corrector_ = new RecoilCorrector("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_wjets53X_20pv_njet.root");
    corrector_->addMCFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_zmm53XRR_2012_njet.root");
    corrector_->addDataFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_datamm53XRR_2012_njet.root");
  }
  else if(sampleName_.find("HIGGS") != std::string::npos){
    corrector_ = new RecoilCorrector("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_higgs53X_20pv_njet.root");
    corrector_->addMCFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_zmm53XRR_2012_njet.root");
    corrector_->addDataFile("/nfs/dust/cms/user/pooja/scratch/plot-macro/RecoilCorrector_v7/recoilfits/recoilfit_datamm53XRR_2012_njet.root");
  }
  else{
    corrector_ = 0;
  }
}


TLorentzVector MEtRecoilCorrection::RecoilCorrectedMET(TLorentzVector pfMet_, LorentzVector lepLeg1_, LorentzVector lepLeg2_,  
						       LorentzVector genVisLeg1_, LorentzVector genVisLeg2_, int nJets_, std::string sampleName_)
{
  double newPfMetPt_ = pfMet_.Pt(); 
  double newPfMetPhi_ = pfMet_.Phi();
  
  double u1 = 0; double u2 = 0;
  LorentzVector genVP4_(0, 0, 0, 0);
  
  // case -I   
  if( sampleName_.find("ZJET") != std::string::npos ){

/*     // loop over allgenparticles */
/*     vector<GenParticle> daughters; */
/*     for(unsigned int i = 0 ; i < NumAllGenParticles() ; i++) */
/*       { */
/* 	GenParticle Gen = AllGenParticles(i); */
/* 	if(Gen.Status() != 3) continue; */
/* 	if(TMath::Abs(Gen.PDGId()) == 23){ */
/* 	  genVP4_ = Gen.P4(); */
/* 	  for(unsigned int i = 0; i < Gen.NumDaughters(); ++i) */
/* 	    { */
/* 	      const GenParticle daughter = Gen.GetDaughter(i); */
/* 	      if(TMath::Abs(daughter.PDGId()) == 15){ */
/* 		daughters.push_back(daughter); */
/* 	      } */
/* 	    } */
/* 	} */
/*       } */
/*   } */

/*   LorentzVector genVisLeg1_(0, 0, 0, 0); */
/*   LorentzVector genVisLeg2_(0, 0, 0, 0); */
/*   for(size_t i = 0; i < daughters.size(); i++){ */
/*     if(daughters[i].PDGId() == -15){ //for tau- */
/*       genVisLeg1_ = daughters[i].P4(); */
/*       for(int j = 0; j < daughters[i].NumDaughters(); ++j){ */
/* 	const GenParticle daughter2 = daughters[i].GetDaughter(j); */
/* 	int daughter2Id = daughter2.PDGId(); */
/* 	int daughter2Status = daughter2.Status(); */
	
/* 	if((fabs(daughter2Id)==12 || fabs(daughter2Id)==14 || fabs(daughter2Id)==16) && daughter2Status==1 )  */
/* 	  genVisLeg1_ -= daughter2.P4(); */
/* 	} */
/*     } */
/*     if(daughters[i].PDGId() == 15){ //for tau+ */
/*       genVisLeg2_ = daughters[i].P4(); */
/*       for(int j = 0; j < daughters[i].NumDaughters(); ++j){ */
/* 	const GenParticle daughter2 = daughters[i].GetDaughter(j); */
/* 	int daughter2Id = daughter2.PDGId(); */
/* 	int daughter2Status = daughter2.Status(); */
	
/* 	if((fabs(daughter2Id)==12 || fabs(daughter2Id)==14 || fabs(daughter2Id)==16) && daughter2Status==1 ) */
/* 	  genVisLeg2_ -= daughter2.P4(); */
/*       }  */
/*     } */
/*   } */
  

    LorentzVector finalLepLeg1_(0, 0, 0, 0);
    LorentzVector finalLepLeg2_(0, 0, 0, 0);
    
    if(genVisLeg1_.Pt() > 0){
      if(ROOT::Math::VectorUtil::DeltaR(genVisLeg1_, lepLeg1_) < 0.3)
	finalLepLeg1_ = lepLeg1_;
      else if(ROOT::Math::VectorUtil::DeltaR(genVisLeg1_, lepLeg2_) < 0.3)
	finalLepLeg1_ = lepLeg2_;
      else
	finalLepLeg1_ = genVisLeg1_;
    }
    
    if(ROOT::Math::VectorUtil::DeltaR(genVisLeg2_, lepLeg1_) < 0.3)
      finalLepLeg2_ = lepLeg1_;
    else if(ROOT::Math::VectorUtil::DeltaR(genVisLeg2_, lepLeg2_) < 0.3)
      finalLepLeg2_ = lepLeg2_;
    else
      finalLepLeg2_ = genVisLeg2_;
    
    LorentzVector diLepton_(0, 0, 0, 0);
    if(finalLepLeg1_.Pt() > 0 && finalLepLeg2_.Pt() > 0) diLepton_ = finalLepLeg1_ + finalLepLeg2_;
    else diLepton_ = lepLeg1_ + lepLeg2_;
    
    corrector_->CorrectType1(newPfMetPt_,newPfMetPhi_,genVP4_.Pt() ,genVP4_.Phi(), diLepton_.Pt(),diLepton_.Phi(), u1, u2 , 0 , 0, TMath::Min(nJets_,2) );

    TLorentzVector corMET_;
    corMET_.SetPtEtaPhiM(newPfMetPt_, 0, newPfMetPhi_, 0);
    return corMET_;
  }
}

#endif // _HTAUTAU

