import FWCore.ParameterSet.Config as cms
from RecoTauTag.RecoTau.TauDiscriminatorTools import requireLeadTrack

pfRecoTauDiscriminationAgainstElectron = cms.EDProducer("PFRecoTauDiscriminationAgainstElectron2",

    # tau collection to discriminate
    PFTauProducer = cms.InputTag('pfRecoTauProducer'),

    # Require leading pion ensures that:
    #  1) these is at least one track above threshold (0.5 GeV) in the signal cone
    #  2) a track OR a pi-zero in the signal cone has pT > 5 GeV
    #Prediscriminants = requireLeadTrack,

    keepTausInEcalCrack = cms.bool(False), 
    rejectTausInEcalCrack = cms.bool(False),

    LeadPFChargedHadrEoP_barrel_min = cms.double(0.99),
    LeadPFChargedHadrEoP_barrel_max = cms.double(1.01),
    Hcal3x3OverPLead_barrel_max = cms.double(0.2),
    GammaEtaMom_barrel_max = cms.double(0.4),
    GammaPhiMom_barrel_max = cms.double(0.4),
    GammaEnFrac_barrel_max = cms.double(0.15),
    LeadPFChargedHadrEoP_endcap_min1 = cms.double(0.7),
    LeadPFChargedHadrEoP_endcap_max1 = cms.double(1.3),
    LeadPFChargedHadrEoP_endcap_min2 = cms.double(0.99),
    LeadPFChargedHadrEoP_endcap_max2 = cms.double(1.01),
    Hcal3x3OverPLead_endcap_max = cms.double(0.1),
    GammaEtaMom_endcap_max = cms.double(10.0),
    GammaPhiMom_endcap_max = cms.double(10.0),
    GammaEnFrac_endcap_max = cms.double(0.2),
)


