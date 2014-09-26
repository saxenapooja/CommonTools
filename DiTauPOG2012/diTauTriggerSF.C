//source:: https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorkingSummer2013#diTau_trigger 
//http://anayak.web.cern.ch/anayak/HToTauTau/TriggerTest/DiTau_FitResults/SyncSelection/NewTauID_NewTES/

// old ID
Double_t Eff_HLT_2012ISOPARKED_Tau_OLDID_DATA(double pt, double eta)
{
  return ( 0.919649 * 0.5 * (TMath::Erf((pt - 43.1776)/2./0.758213 /sqrt(pt)) + 1.) );
}

Double_t Eff_HLT_2012ISOPARKED_Tau_OLDID_MC(double pt, double eta)
{
  double data_plateau = 0.826969 ;
  if (pt < 140.)   return ( 0.880128 * 0.5 * (TMath::Erf((pt-41.8055)/2./0.800499  /sqrt(pt))+1.) ) ; // only one eta bin
  else if (pt>400) return data_plateau / 2.03467;
  else if (pt>300) return data_plateau / 1.31593;
  else if (pt>250) return data_plateau / 1.25698;
  else if (pt>200) return data_plateau / 1.18941;
  else if (pt>180) return data_plateau / 1.17448;
  else if (pt>160) return data_plateau / 1.0964 ;
  else return data_plateau / 1.09279;
}


// New ID
Double_t Eff_HLT_2012ISOPARKED_Tau_NEWID_DATA(double pt, double eta)
{
  return ( 0.876313 * 0.5 * (TMath::Erf((pt - 42.8216)/2./0.754887 /sqrt(pt)) + 1.) );
}

Double_t Eff_HLT_2012ISOPARKED_Tau_NEWID_MC(double pt, double eta)
{
  double data_plateau = 0.826969 ;
  if (pt < 140.)   return ( 0.861041 * 0.5 * (TMath::Erf((pt- 41.5791)/2./0.768280  /sqrt(pt))+1.) ) ; // only one eta bin
  else if (pt>400) return data_plateau / 2.03467;
  else if (pt>300) return data_plateau / 1.31593;
  else if (pt>250) return data_plateau / 1.25698;
  else if (pt>200) return data_plateau / 1.18941;
  else if (pt>180) return data_plateau / 1.17448;
  else if (pt>160) return data_plateau / 1.0964 ;
  else return data_plateau / 1.09279;
}


