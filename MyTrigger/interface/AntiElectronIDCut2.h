//--------------------------------------------------------------------------------------------------
// AntiElectronIDCut2
//
// Helper Class for applying simple cut based anti-electron discrimination
//
// Authors: A Nayak
//--------------------------------------------------------------------------------------------------

#ifndef RECOTAUTAG_RECOTAU_AntiElectronIDCut2_H
#define RECOTAUTAG_RECOTAU_AntiElectronIDCut2_H

#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Math/interface/deltaR.h"

#include <vector>

class AntiElectronIDCut2 
{
  public:

    AntiElectronIDCut2();
    ~AntiElectronIDCut2(); 

    double Discriminator(Float_t TauPt,
                         Float_t TauEta,
                         Float_t TauLeadChargedPFCandPt,
                         Float_t TauLeadChargedPFCandEtaAtEcalEntrance,
                         Float_t TauLeadPFChargedHadrEoP,
                         Float_t TauHcal3x3OverPLead,
                         Float_t TauGammaEtaMom,
                         Float_t TauGammaPhiMom,
                         Float_t TauGammaEnFrac
			 );

    double Discriminator(Float_t TauPt,
			 Float_t TauEta,
			 Float_t TauLeadChargedPFCandPt,
			 Float_t TauLeadChargedPFCandEtaAtEcalEntrance,
			 Float_t TauLeadPFChargedHadrEoP,
			 Float_t TauHcal3x3OverPLead,
			 const std::vector<Float_t>& GammasdEta,
			 const std::vector<Float_t>& GammasdPhi,
			 const std::vector<Float_t>& GammasPt
			 );

    double Discriminator(const reco::PFTau& thePFTau);

    void SetBarrelCutValues(Float_t TauLeadPFChargedHadrEoP_min,
			    Float_t TauLeadPFChargedHadrEoP_max,
			    Float_t TauHcal3x3OverPLead_max,
			    Float_t TauGammaEtaMom_max,
			    Float_t TauGammaPhiMom_max,
			    Float_t TauGammaEnFrac_max
			    );

    void SetEndcapCutValues(Float_t TauLeadPFChargedHadrEoP_min_1,
                            Float_t TauLeadPFChargedHadrEoP_max_1,
			    Float_t TauLeadPFChargedHadrEoP_min_2,
                            Float_t TauLeadPFChargedHadrEoP_max_2,
                            Float_t TauHcal3x3OverPLead_max,
                            Float_t TauGammaEtaMom_max,
                            Float_t TauGammaPhiMom_max,
                            Float_t TauGammaEnFrac_max
                            );
    void ApplyCut_EcalCrack(bool keepAll_, bool rejectAll_){
      keepAllInEcalCrack_ = keepAll_;
      rejectAllInEcalCrack_ = rejectAll_;
    };
      
 private:

    bool isInEcalCrack(double eta) const; 
    
    float TauLeadPFChargedHadrEoP_barrel_min_;
    float TauLeadPFChargedHadrEoP_barrel_max_;
    float TauHcal3x3OverPLead_barrel_max_;
    float TauGammaEtaMom_barrel_max_;
    float TauGammaPhiMom_barrel_max_;
    float TauGammaEnFrac_barrel_max_;
    float TauLeadPFChargedHadrEoP_endcap_min1_;
    float TauLeadPFChargedHadrEoP_endcap_max1_;
    float TauLeadPFChargedHadrEoP_endcap_min2_;
    float TauLeadPFChargedHadrEoP_endcap_max2_;
    float TauHcal3x3OverPLead_endcap_max_;
    float TauGammaEtaMom_endcap_max_;
    float TauGammaPhiMom_endcap_max_;
    float TauGammaEnFrac_endcap_max_;

    bool keepAllInEcalCrack_;
    bool rejectAllInEcalCrack_;
    
    int verbosity_;
};

#endif
