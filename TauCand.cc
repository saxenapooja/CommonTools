
#include "AnalysisTool/DataForm.h"
#include "Common/TauCand.h"
#include "Common/TauWP.h"

static TLorentzVector correct(const TLorentzVector& p4, double corr)
{
	const double px = p4.Px() * corr;
	const double py = p4.Py() * corr;
	const double pz = p4.Pz() * corr;
	const double M = p4.M();
	return TLorentzVector(px, py, pz, TMath::Sqrt(M*M+px*px+py*py+pz*pz));
}

TauCand::TauCand(const TauWP& wp, const Tau& tau, double sf):
	trigObj(tau), Charge(tau.Charge()), NewEMFraction(tau.NewEMFraction()), NumTracks(tau.NumTracks()),
	Dxy(tau.Dxy()), Dz(tau.Dz()),
	IsoNeutralsPt(tau.IsoNeutralsPt()), IsoChargedPt(tau.IsoChargedPt()), IsoGammaPt(tau.IsoGammaPt()), Iso3Hits(tau.Iso3Hits()), TrackIso(0.0f),
	decayModeFinding(tau.TauDiscriminator("decayModeFinding") == 1),
	decayModeFindingOldDMs(tau.TauDiscriminator("decayModeFindingOldDMs") == 1),
	decayModeFindingNewDMs(tau.TauDiscriminator("decayModeFindingNewDMs") == 1),
	byLooseCombinedIsolationDeltaBetaCorr3Hits(tau.TauDiscriminator("byLooseCombinedIsolationDeltaBetaCorr3Hits") == 1),
	byMediumCombinedIsolationDeltaBetaCorr3Hits(tau.TauDiscriminator("byMediumCombinedIsolationDeltaBetaCorr3Hits") == 1),
	byTightCombinedIsolationDeltaBetaCorr3Hits(tau.TauDiscriminator("byTightCombinedIsolationDeltaBetaCorr3Hits") == 1),
	byLooseIsolationMVA3oldDMwLT(tau.TauDiscriminator("byLooseIsolationMVA3oldDMwLT") == 1),
	byMediumIsolationMVA3oldDMwLT(tau.TauDiscriminator("byMediumIsolationMVA3oldDMwLT") == 1),
	byTightIsolationMVA3oldDMwLT(tau.TauDiscriminator("byTightIsolationMVA3oldDMwLT") == 1),
	byVTightIsolationMVA3oldDMwLT(tau.TauDiscriminator("byVTightIsolationMVA3oldDMwLT") == 1),
	againstElectronLoose(tau.TauDiscriminator("againstElectronLoose") == 1),
	againstElectronMedium(tau.TauDiscriminator("againstElectronMedium") == 1),
	againstElectronTight(tau.TauDiscriminator("againstElectronTight") == 1),
	againstElectronLooseMVA5(tau.TauDiscriminator("againstElectronLooseMVA5") == 1),
	againstElectronMediumMVA5(tau.TauDiscriminator("againstElectronMediumMVA5") == 1),
	againstElectronTightMVA5(tau.TauDiscriminator("againstElectronTightMVA5") == 1),
	againstMuonLoose(tau.TauDiscriminator("againstMuonLoose") == 1),
	againstMuonMedium(tau.TauDiscriminator("againstMuonMedium") == 1),
	againstMuonTight(tau.TauDiscriminator("againstMuonTight") == 1),
	againstMuonLoose3(tau.TauDiscriminator("againstMuonLoose3") == 1),
	againstMuonTight3(tau.TauDiscriminator("againstMuonTight3") == 1),
	againstMuonLooseMVA(tau.TauDiscriminator("againstMuonLooseMVA") == 1),
	againstMuonMediumMVA(tau.TauDiscriminator("againstMuonMediumMVA") == 1),
	againstMuonTightMVA(tau.TauDiscriminator("againstMuonTightMVA") == 1),
	corr(sf), p4(correct(tau, corr)),
	leadpfchargedhadrcandpt(tau.leadpfchargedhadrcandpt()),
	leadpfchargedhadrcandp4(tau.leadpfchargedhadrcandp4()),
	PFChargedHadrCands_size(tau.signalPFChargedHadrCands_size()),
	PFGammaCands_size(tau.signalPFGammaCands_size()),
	L1trigger_match(tau.TauL1trigger_match())
{
}


TauCand::TauCand(const Tau& tau, double sf):
	trigObj(tau), Charge(tau.Charge()), NewEMFraction(tau.NewEMFraction()), NumTracks(tau.NumTracks()),
	Dxy(tau.Dxy()), Dz(tau.Dz()),
	IsoNeutralsPt(tau.IsoNeutralsPt()), IsoChargedPt(tau.IsoChargedPt()), IsoGammaPt(tau.IsoGammaPt()), Iso3Hits(tau.Iso3Hits()), TrackIso(0.0f),
	decayModeFinding(tau.TauDiscriminator("decayModeFinding") == 1),
	decayModeFindingOldDMs(tau.TauDiscriminator("decayModeFindingOldDMs") == 1),
        decayModeFindingNewDMs(tau.TauDiscriminator("decayModeFindingNewDMs") == 1),
        byLooseCombinedIsolationDeltaBetaCorr3Hits(tau.TauDiscriminator("byLooseCombinedIsolationDeltaBetaCorr3Hits") == 1),
        byMediumCombinedIsolationDeltaBetaCorr3Hits(tau.TauDiscriminator("byMediumCombinedIsolationDeltaBetaCorr3Hits") == 1),
        byTightCombinedIsolationDeltaBetaCorr3Hits(tau.TauDiscriminator("byTightCombinedIsolationDeltaBetaCorr3Hits") == 1),
        byLooseIsolationMVA3oldDMwLT(tau.TauDiscriminator("byLooseIsolationMVA3oldDMwLT") == 1),
        byMediumIsolationMVA3oldDMwLT(tau.TauDiscriminator("byMediumIsolationMVA3oldDMwLT") == 1),
        byTightIsolationMVA3oldDMwLT(tau.TauDiscriminator("byTightIsolationMVA3oldDMwLT") == 1),
        byVTightIsolationMVA3oldDMwLT(tau.TauDiscriminator("byVTightIsolationMVA3oldDMwLT") == 1),
        againstElectronLoose(tau.TauDiscriminator("againstElectronLoose") == 1),
        againstElectronMedium(tau.TauDiscriminator("againstElectronMedium") == 1),
        againstElectronTight(tau.TauDiscriminator("againstElectronTight") == 1),
        againstElectronLooseMVA5(tau.TauDiscriminator("againstElectronLooseMVA5") == 1),
        againstElectronMediumMVA5(tau.TauDiscriminator("againstElectronMediumMVA5") == 1),
        againstElectronTightMVA5(tau.TauDiscriminator("againstElectronTightMVA5") == 1),
        againstMuonLoose(tau.TauDiscriminator("againstMuonLoose") == 1),
        againstMuonMedium(tau.TauDiscriminator("againstMuonMedium") == 1),
        againstMuonTight(tau.TauDiscriminator("againstMuonTight") == 1),
        againstMuonLoose3(tau.TauDiscriminator("againstMuonLoose3") == 1),
        againstMuonTight3(tau.TauDiscriminator("againstMuonTight3") == 1),
	againstMuonLooseMVA(tau.TauDiscriminator("againstMuonLooseMVA") == 1),
        againstMuonMediumMVA(tau.TauDiscriminator("againstMuonMediumMVA") == 1),
        againstMuonTightMVA(tau.TauDiscriminator("againstMuonTightMVA") == 1),
	corr(sf), p4(correct(tau, corr)),
	leadpfchargedhadrcandpt(tau.leadpfchargedhadrcandpt()),
	leadpfchargedhadrcandp4(tau.leadpfchargedhadrcandp4()),
	L1trigger_match(tau.TauL1trigger_match())
{
}
