#include "RecoTauTag/RecoTau/interface/AntiElectronIDCut2.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include <TMath.h>

AntiElectronIDCut2::AntiElectronIDCut2()
{
  //Default values for the HLT
  TauLeadPFChargedHadrEoP_barrel_min_ = 0.99;
  TauLeadPFChargedHadrEoP_barrel_max_ = 1.01;
  TauHcal3x3OverPLead_barrel_max_ = 0.2;
  TauGammaEtaMom_barrel_max_ = 4.0;
  TauGammaPhiMom_barrel_max_ = 4.0;
  TauGammaEnFrac_barrel_max_ = 0.15;
  TauLeadPFChargedHadrEoP_endcap_min1_ = 0.7;
  TauLeadPFChargedHadrEoP_endcap_max1_ = 1.3;
  TauLeadPFChargedHadrEoP_endcap_min2_ = 0.99;
  TauLeadPFChargedHadrEoP_endcap_max2_ = 1.01;
  TauHcal3x3OverPLead_endcap_max_ = 0.1;
  TauGammaEtaMom_endcap_max_ = 10.0;
  TauGammaPhiMom_endcap_max_ = 10.0;
  TauGammaEnFrac_endcap_max_ = 0.2;

  //default, keep all taus in cracks for HLT 
  keepAllInEcalCrack_ = true;
  rejectAllInEcalCrack_ = false;

  verbosity_ = 0;
}

AntiElectronIDCut2::~AntiElectronIDCut2()
{}

double
AntiElectronIDCut2::Discriminator(Float_t TauPt,
                                  Float_t TauEta,
                                  Float_t TauLeadChargedPFCandPt,
                                  Float_t TauLeadChargedPFCandEtaAtEcalEntrance,
                                  Float_t TauLeadPFChargedHadrEoP,
                                  Float_t TauHcal3x3OverPLead,
				  Float_t TauGammaEtaMom,
				  Float_t TauGammaPhiMom,
				  Float_t TauGammaEnFrac)
{

  // ensure tau has at least one charged object
  if( TauLeadChargedPFCandPt <= 0 )
    {
      return 0.;
    }
  else {
    // Check if track goes to Ecal Crack
    if(isInEcalCrack(TauLeadChargedPFCandEtaAtEcalEntrance))
      {
	if(keepAllInEcalCrack_)
	  return 1.0;
	else if(rejectAllInEcalCrack_)
	  return 0.;
      }
  }
  
  bool decision = false;
  //Apply separate cuts for barrel and endcap
  if(TMath::Abs(TauEta) < 1.479)
    {
      
      //Apply cut for barrel
      if(TauGammaEtaMom > TauGammaEtaMom_barrel_max_)
	decision = true;

      if(TauHcal3x3OverPLead > TauHcal3x3OverPLead_barrel_max_)
	decision = true;

      if(TauLeadPFChargedHadrEoP < TauLeadPFChargedHadrEoP_barrel_min_ ||
	 TauLeadPFChargedHadrEoP > TauLeadPFChargedHadrEoP_barrel_max_) 
	decision = true;
    }
  else {
    
    //Apply cut for endcap
    if(TauGammaEtaMom > TauGammaEtaMom_endcap_max_)
      decision = true;

    //This cut is for both offline and HLT. For offline, use cut 0.99-1.01, 
    //For HLT use cut 0.7-1.3
    if(TauLeadPFChargedHadrEoP < TauLeadPFChargedHadrEoP_endcap_min1_ ||
         TauLeadPFChargedHadrEoP > TauLeadPFChargedHadrEoP_endcap_max1_) 
      decision = true;

    //This cut is only for HLT. For HLT, use cut like 0.99-1.01 & H3x3/P>0.1
    //For offline, keep the values same as above : 0.99-1.01 & H3x3/P>0, otherwise it may select events in a wrong way. 
    if((TauLeadPFChargedHadrEoP < TauLeadPFChargedHadrEoP_endcap_min2_ || 
	 TauLeadPFChargedHadrEoP > TauLeadPFChargedHadrEoP_endcap_max2_) &&
       TauHcal3x3OverPLead > TauHcal3x3OverPLead_endcap_max_)
      decision = true;
  }

  return (decision ? 1. : 0.);
}  

double
AntiElectronIDCut2::Discriminator(Float_t TauPt,
				  Float_t TauEta,
				  Float_t TauLeadChargedPFCandPt,
				  Float_t TauLeadChargedPFCandEtaAtEcalEntrance,
				  Float_t TauLeadPFChargedHadrEoP,
				  Float_t TauHcal3x3OverPLead,
				  const std::vector<Float_t>& GammasdEta,
				  const std::vector<Float_t>& GammasdPhi,
				  const std::vector<Float_t>& GammasPt
				  )
{
  double sumPt  = 0.;
  double dEta   = 0.;
  double dEta2  = 0.;
  double dPhi   = 0.;
  double dPhi2  = 0.;
  double sumPt2 = 0.;
  for ( unsigned int i = 0 ; i < GammasPt.size() ; ++i ) {
    double pt_i  = GammasPt[i];
    double phi_i = GammasdPhi[i];
    if ( GammasdPhi[i] > TMath::Pi() ) phi_i = GammasdPhi[i] - 2*TMath::Pi();
    else if ( GammasdPhi[i] < -TMath::Pi() ) phi_i = GammasdPhi[i] + 2*TMath::Pi();
    double eta_i = GammasdEta[i];
    sumPt  +=  pt_i;
    sumPt2 += (pt_i*pt_i);
    dEta   += (pt_i*eta_i);
    dEta2  += (pt_i*eta_i*eta_i);
    dPhi   += (pt_i*phi_i);
    dPhi2  += (pt_i*phi_i*phi_i);
  }

  Float_t TauGammaEnFrac = sumPt/TauPt;

  if ( sumPt > 0. ) {
    dEta  /= sumPt;
    dPhi  /= sumPt;
    dEta2 /= sumPt;
    dPhi2 /= sumPt;
  }

  Float_t TauGammaEtaMom = TMath::Sqrt(dEta2)*TMath::Sqrt(TauGammaEnFrac)*TauPt;
  Float_t TauGammaPhiMom = TMath::Sqrt(dPhi2)*TMath::Sqrt(TauGammaEnFrac)*TauPt;

  return Discriminator(TauPt,
                       TauEta,
                       TauLeadChargedPFCandPt,
                       TauLeadChargedPFCandEtaAtEcalEntrance,
                       TauLeadPFChargedHadrEoP,
                       TauHcal3x3OverPLead,
                       TauGammaEtaMom,
                       TauGammaPhiMom,
		       TauGammaEnFrac
		       );
}

double
AntiElectronIDCut2::Discriminator(const reco::PFTau& thePFTau)
{
  float TauLeadChargedPFCandEtaAtEcalEntrance = -99.;
  float TauLeadChargedPFCandPt = -99.;
  const std::vector<reco::PFCandidatePtr>& signalPFCands = thePFTau.signalPFCands();
  for ( std::vector<reco::PFCandidatePtr>::const_iterator pfCandidate = signalPFCands.begin();
	pfCandidate != signalPFCands.end(); ++pfCandidate ) {
    const reco::Track* track = 0;
    if ( (*pfCandidate)->trackRef().isNonnull() ) track = (*pfCandidate)->trackRef().get();
    else if ( (*pfCandidate)->muonRef().isNonnull() && (*pfCandidate)->muonRef()->innerTrack().isNonnull()  ) track = (*pfCandidate)->muonRef()->innerTrack().get();
    else if ( (*pfCandidate)->muonRef().isNonnull() && (*pfCandidate)->muonRef()->globalTrack().isNonnull() ) track = (*pfCandidate)->muonRef()->globalTrack().get();
    else if ( (*pfCandidate)->muonRef().isNonnull() && (*pfCandidate)->muonRef()->outerTrack().isNonnull()  ) track = (*pfCandidate)->muonRef()->outerTrack().get();
    else if ( (*pfCandidate)->gsfTrackRef().isNonnull() ) track = (*pfCandidate)->gsfTrackRef().get();
    if ( track ) {
      if ( track->pt() > TauLeadChargedPFCandPt ) {
	TauLeadChargedPFCandEtaAtEcalEntrance = (*pfCandidate)->positionAtECALEntrance().eta();
	TauLeadChargedPFCandPt = track->pt();
      }
    }
  }
  
  Float_t TauPt = thePFTau.pt();
  Float_t TauEta = thePFTau.eta();
  //Float_t TauLeadPFChargedHadrHoP = 0.;
  Float_t TauLeadPFChargedHadrEoP = 0.;
  if ( thePFTau.leadPFChargedHadrCand()->p() > 0. ) {
    //TauLeadPFChargedHadrHoP = thePFTau.leadPFChargedHadrCand()->hcalEnergy()/thePFTau.leadPFChargedHadrCand()->p();
    TauLeadPFChargedHadrEoP = thePFTau.leadPFChargedHadrCand()->ecalEnergy()/thePFTau.leadPFChargedHadrCand()->p();
  }

  std::vector<Float_t> GammasdEta;
  std::vector<Float_t> GammasdPhi;
  std::vector<Float_t> GammasPt;
  for ( unsigned i = 0 ; i < thePFTau.signalPFGammaCands().size(); ++i ) {
    reco::PFCandidatePtr gamma = thePFTau.signalPFGammaCands().at(i);
    if ( thePFTau.leadPFChargedHadrCand().isNonnull() ) {
      GammasdEta.push_back(gamma->eta() - thePFTau.leadPFChargedHadrCand()->eta());
      GammasdPhi.push_back(gamma->phi() - thePFTau.leadPFChargedHadrCand()->phi());
    } else {
      GammasdEta.push_back(gamma->eta() - thePFTau.eta());
      GammasdPhi.push_back(gamma->phi() - thePFTau.phi());
    }
    GammasPt.push_back(gamma->pt());
  }

  Float_t TauHcal3x3OverPLead = thePFTau.hcal3x3OverPLead();

  return Discriminator(TauPt,
		       TauEta,
		       TauLeadChargedPFCandPt,
		       TauLeadChargedPFCandEtaAtEcalEntrance,
		       TauLeadPFChargedHadrEoP,
		       TauHcal3x3OverPLead,
		       GammasdEta,
		       GammasdPhi,
                       GammasPt
		       );
}

void 
AntiElectronIDCut2::SetBarrelCutValues(Float_t TauLeadPFChargedHadrEoP_min,
				       Float_t TauLeadPFChargedHadrEoP_max,
				       Float_t TauHcal3x3OverPLead_max,
				       Float_t TauGammaEtaMom_max,
				       Float_t TauGammaPhiMom_max,
				       Float_t TauGammaEnFrac_max
				       )
{
  TauLeadPFChargedHadrEoP_barrel_min_ = TauLeadPFChargedHadrEoP_min;
  TauLeadPFChargedHadrEoP_barrel_max_ = TauLeadPFChargedHadrEoP_max;
  TauHcal3x3OverPLead_barrel_max_ = TauHcal3x3OverPLead_max;
  TauGammaEtaMom_barrel_max_ = TauHcal3x3OverPLead_max;
  TauGammaPhiMom_barrel_max_ = TauGammaEtaMom_max;
  TauGammaEnFrac_barrel_max_ = TauGammaEnFrac_max;
}

void 
AntiElectronIDCut2::SetEndcapCutValues(Float_t TauLeadPFChargedHadrEoP_min_1,
				       Float_t TauLeadPFChargedHadrEoP_max_1,
				       Float_t TauLeadPFChargedHadrEoP_min_2,
				       Float_t TauLeadPFChargedHadrEoP_max_2,
				       Float_t TauHcal3x3OverPLead_max,
				       Float_t TauGammaEtaMom_max,
				       Float_t TauGammaPhiMom_max,
				       Float_t TauGammaEnFrac_max
				       )
{
  TauLeadPFChargedHadrEoP_endcap_min1_ = TauLeadPFChargedHadrEoP_min_1;
  TauLeadPFChargedHadrEoP_endcap_max1_ = TauLeadPFChargedHadrEoP_max_1;
  TauLeadPFChargedHadrEoP_endcap_min2_ = TauLeadPFChargedHadrEoP_min_2;
  TauLeadPFChargedHadrEoP_endcap_max2_ = TauLeadPFChargedHadrEoP_max_2;
  TauHcal3x3OverPLead_endcap_max_ = TauHcal3x3OverPLead_max;
  TauGammaEtaMom_endcap_max_ = TauGammaEtaMom_max;
  TauGammaPhiMom_endcap_max_ = TauGammaPhiMom_max;
  TauGammaEnFrac_endcap_max_ = TauGammaEnFrac_max;
}

bool
AntiElectronIDCut2::isInEcalCrack(double eta) const
{
  eta = fabs(eta);
  return (eta < 0.018 ||
          (eta>0.423 && eta<0.461) ||
          (eta>0.770 && eta<0.806) ||
          (eta>1.127 && eta<1.163) ||
          (eta>1.460 && eta<1.558));
}

