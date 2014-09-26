#include "Common/TauWP.h"
#include <cassert>
#include <stdexcept>

TauWP::Isolation string_to_isolation(const std::string& str)
{
  if(str == "loose_3hits")       return TauWP::ISO_LOOSE_3HITS;
  else if(str == "loose_mva3oldDMwLT")  return TauWP::ISO_LOOSE_MVA3oldDMwLT;
  else if(str == "medium_3hits") return TauWP::ISO_MEDIUM_3HITS;
  else if(str == "medium_mva3oldDMwLT")  return TauWP::ISO_MEDIUM_MVA3oldDMwLT;
  else if(str == "tight_3hits")  return TauWP::ISO_TIGHT_3HITS;
  else if(str == "tight_mva3oldDMwLT")  return TauWP::ISO_TIGHT_MVA3oldDMwLT;
  else if(str == "vtight_mva3oldDMwLT")  return TauWP::ISO_VTIGHT_MVA3oldDMwLT;
  else throw std::runtime_error("No such tau isolation working point: " + str);
}

TauWP::AntiE string_to_antie(const std::string& str)
{
  if(str == "loose")            return TauWP::ANTIE_LOOSE;
  else if(str == "loose_mva5")  return TauWP::ANTIE_LOOSE_MVA5;
  else if(str == "medium")      return TauWP::ANTIE_MEDIUM;
  else if(str == "medium_mva5") return TauWP::ANTIE_MEDIUM_MVA5;
  else if(str == "tight")       return TauWP::ANTIE_TIGHT;
  else if(str == "tight_mva5")  return TauWP::ANTIE_TIGHT_MVA5;
  else throw std::runtime_error("No such electron rejection working point: " + str);
}

TauWP::AntiMu string_to_antimu(const std::string& str)
{
  if(str == "loose")           return TauWP::ANTIMU_LOOSE;
  else if(str == "loose_mva")  return TauWP::ANTIMU_LOOSE_MVA;
  else if(str == "medium")     return TauWP::ANTIMU_MEDIUM;
  else if(str == "medium_mva") return TauWP::ANTIMU_MEDIUM_MVA;
  else if(str == "tight")      return TauWP::ANTIMU_TIGHT;
  else if(str == "tight_mva")  return TauWP::ANTIMU_TIGHT_MVA;
  else throw std::runtime_error("No such muon rejection working point: " + str);
}

const bool TauCand::*get_isolation_flag(TauWP::Isolation isolation)
{
  switch(isolation)
  {
  case TauWP::ISO_LOOSE_3HITS:         return &TauCand::byLooseCombinedIsolationDeltaBetaCorr3Hits;
  case TauWP::ISO_LOOSE_MVA3oldDMwLT:  return &TauCand::byLooseIsolationMVA3oldDMwLT;
  case TauWP::ISO_MEDIUM_3HITS:        return &TauCand::byMediumCombinedIsolationDeltaBetaCorr3Hits;
  case TauWP::ISO_MEDIUM_MVA3oldDMwLT: return &TauCand::byMediumIsolationMVA3oldDMwLT; 
  case TauWP::ISO_TIGHT_3HITS:         return &TauCand::byTightCombinedIsolationDeltaBetaCorr3Hits;
  case TauWP::ISO_TIGHT_MVA3oldDMwLT:  return &TauCand::byTightIsolationMVA3oldDMwLT;
  case TauWP::ISO_VTIGHT_MVA3oldDMwLT: return &TauCand::byVTightIsolationMVA3oldDMwLT;
  default: assert(false);       return NULL;
  }
}

const bool TauCand::*get_antie_flag(TauWP::AntiE antie)
{
  switch(antie)
    {
    case TauWP::ANTIE_LOOSE: return &TauCand::againstElectronLoose;
    case TauWP::ANTIE_LOOSE_MVA5: return &TauCand::againstElectronLooseMVA5;
    case TauWP::ANTIE_MEDIUM: return &TauCand::againstElectronMedium;
    case TauWP::ANTIE_MEDIUM_MVA5: return &TauCand::againstElectronMediumMVA5;
    case TauWP::ANTIE_TIGHT: return &TauCand::againstElectronTight;
    case TauWP::ANTIE_TIGHT_MVA5: return &TauCand::againstElectronTightMVA5;
    default: assert(false); return NULL;
    }
}

const bool TauCand::*get_antimu_flag(TauWP::AntiMu antimu)
{
  switch(antimu)
    {
    case TauWP::ANTIMU_LOOSE:      return &TauCand::againstMuonLoose;
    case TauWP::ANTIMU_LOOSE_MVA:  return &TauCand::againstMuonLooseMVA;
    case TauWP::ANTIMU_MEDIUM:     return &TauCand::againstMuonMedium;
    case TauWP::ANTIMU_MEDIUM_MVA: return &TauCand::againstMuonMediumMVA;
    case TauWP::ANTIMU_TIGHT:      return &TauCand::againstMuonTight;
    case TauWP::ANTIMU_TIGHT_MVA:  return &TauCand::againstMuonTightMVA;
    default: assert(false); return NULL;
    }
}

TauWP::TauWP(const Config& cfg,  const char* prefix,  const char* defaultIsolation,    const char* defaultAntiE,   const char* defaultAntiMu):
  ISOLATION(string_to_isolation(cfg.get<std::string>(std::string(prefix) + "_isolation", defaultIsolation))),
  ANTIE(string_to_antie(cfg.get<std::string>(std::string(prefix) + "_antie", defaultAntiE))),
  ANTIMU(string_to_antimu(cfg.get<std::string>(std::string(prefix) + "_antimu", defaultAntiMu))),
  ISOLATION_FLAG(get_isolation_flag(ISOLATION)),
  ANTIE_FLAG(get_antie_flag(ANTIE)),
  ANTIMU_FLAG(get_antimu_flag(ANTIMU))
{
}

// TauWP::TauWP(const Config& cfg,  const char* prefix,  const char* defaultIsolation):
//   ISOLATION(string_to_isolation(cfg.get<std::string>(std::string(prefix) + "_isolation", defaultIsolation))),
//   ISOLATION_FLAG(get_isolation_flag(ISOLATION))
// {
// }



const char* TauWP::isolation_hr_name() const
{
  switch(ISOLATION)
    {
    case ISO_LOOSE_3HITS:         return "Loose3Hits";
    case ISO_LOOSE_MVA3oldDMwLT:  return "LooseMVA3oldDMwLT";
    case ISO_MEDIUM_3HITS:        return "Medium3Hits";
    case ISO_MEDIUM_MVA3oldDMwLT: return "MediumMVA3oldDMwLT";
    case ISO_TIGHT_3HITS:         return "Tight3Hits";
    case ISO_TIGHT_MVA3oldDMwLT:  return "TightMVA3oldDMwLT";
    case ISO_VTIGHT_MVA3oldDMwLT: return "VTightMVA3oldDMwLT";
    default: assert(false); return "";
    }
}

const char* TauWP::antie_hr_name() const
{
  switch(ANTIE)
    {
    case ANTIE_LOOSE:       return "Loose";
    case ANTIE_LOOSE_MVA5:  return "LooseMVA5";
    case ANTIE_MEDIUM:      return "Medium";
    case ANTIE_MEDIUM_MVA5: return "MediumMVA5";
    case ANTIE_TIGHT:       return "Tight";
    case ANTIE_TIGHT_MVA5:  return "TightMVA5";
    default: assert(false); return "";
    }
}

const char* TauWP::antimu_hr_name() const
{
  switch(ANTIMU)
    {
    case ANTIMU_LOOSE:      return "Loose";
    case ANTIMU_LOOSE_MVA:  return "LooseMVA";
    case ANTIMU_MEDIUM:     return "Medium";
    case ANTIMU_MEDIUM_MVA: return "MediumMVA";
    case ANTIMU_TIGHT:      return "Tight";
    case ANTIMU_TIGHT_MVA:  return "TightMVA";
  }
}

const char* TauWP::isolation_frfunc_name() const
{
  switch(ISOLATION)
    {
    case ISO_LOOSE_3HITS:         return "combinedIsolationLoose3Hits";
    case ISO_LOOSE_MVA3oldDMwLT:  return "looseIsolationMVA3oldDMwLT";
    case ISO_MEDIUM_3HITS:        return "combinedIsolationMedium3Hits";
    case ISO_MEDIUM_MVA3oldDMwLT: return "mediumIsolationMVA3oldDMwLT";
    case ISO_TIGHT_3HITS:         return "combinedIsolationTight3Hits";
    case ISO_TIGHT_MVA3oldDMwLT:  return "tightIsolationMVA3oldDMwLT";
    case ISO_VTIGHT_MVA3oldDMwLT: return "vtightIsolationMVA3oldDMwLT";
    default: assert(false); return "";
    }
}

const char* TauWP::antie_frfunc_name() const
{
  switch(ANTIMU)
    {
    case ANTIMU_LOOSE:
      switch(ANTIE)
	{
	case ANTIE_LOOSE: return "electronLoose_muonLoose";
	case ANTIE_LOOSE_MVA5: return "electronLooseMVA5_muonLoose";
	case ANTIE_MEDIUM: return "electronMedium_muonLoose";
	case ANTIE_MEDIUM_MVA5: return "electronMediumMVA5_muonLoose";
	case ANTIE_TIGHT: return "electronTight_muonLoose";
	case ANTIE_TIGHT_MVA5: return "electronTightMVA5_muonLoose";
	default: assert(false); return "";
	}
      break;
    case ANTIMU_LOOSE_MVA:
      switch(ANTIE)
        {
        case ANTIE_LOOSE: return "electronLoose_muonLooseMVA";
        case ANTIE_LOOSE_MVA5: return "electronLooseMVA5_muonLooseMVA";
        case ANTIE_MEDIUM: return "electronMedium_muonLooseMVA";
        case ANTIE_MEDIUM_MVA5: return "electronMediumMVA5_muonLooseMVA";
        case ANTIE_TIGHT: return "electronTight_muonLooseMVA";
        case ANTIE_TIGHT_MVA5: return "electronTightMVA5_muonLooseMVA";
        default: assert(false); return "";
        }
      break;
    case ANTIMU_MEDIUM:
      switch(ANTIE)
	{
	case ANTIE_LOOSE: return "electronLoose_muonMedium";
	case ANTIE_LOOSE_MVA5: return "electronLooseMVA5_muonMedium";
	case ANTIE_MEDIUM: return "electronMedium_muonMedium";
	case ANTIE_MEDIUM_MVA5: return "electronMediumMVA5_muonMedium";
	case ANTIE_TIGHT: return "electronTight_muonMedium";
	case ANTIE_TIGHT_MVA5: return "electronTightMVA5_muonMedium";
	default: assert(false); return "";
	}
      break;
    case ANTIMU_MEDIUM_MVA:
      switch(ANTIE)
        {
        case ANTIE_LOOSE: return "electronLoose_muonMediumMVA";
        case ANTIE_LOOSE_MVA5: return "electronLooseMVA5_muonMediumMVA";
        case ANTIE_MEDIUM: return "electronMedium_muonMediumMVA";
        case ANTIE_MEDIUM_MVA5: return "electronMediumMVA5_muonMediumMVA";
        case ANTIE_TIGHT: return "electronTight_muonMediumMVA";
        case ANTIE_TIGHT_MVA5: return "electronTightMVA5_muonMediumMVA";
        default: assert(false); return "";
        }
      break;
    case ANTIMU_TIGHT:
      switch(ANTIE)
	{
	case ANTIE_LOOSE: return "electronLoose_muonTight";
	case ANTIE_LOOSE_MVA5: return "electronLooseMVA5_muonTight";
	case ANTIE_MEDIUM: return "electronMedium_muonTight";
	case ANTIE_MEDIUM_MVA5: return "electronMediumMVA5_muonTight";
	case ANTIE_TIGHT: return "electronTight_muonTight";
	case ANTIE_TIGHT_MVA5: return "electronTightMVA5_muonTight";
	default: assert(false); return "";
	}
      break;
    case ANTIMU_TIGHT_MVA:
      switch(ANTIE)
        {
        case ANTIE_LOOSE: return "electronLoose_muonTightMVA";
        case ANTIE_LOOSE_MVA5: return "electronLooseMVA5_muonTightMVA";
        case ANTIE_MEDIUM: return "electronMedium_muonTightMVA";
        case ANTIE_MEDIUM_MVA5: return "electronMediumMVA5_muonTightMVA";
        case ANTIE_TIGHT: return "electronTight_muonTightMVA";
        case ANTIE_TIGHT_MVA5: return "electronTightMVA5_muonTightMVA";
        default: assert(false); return "";
	}
      break;
    }
}
