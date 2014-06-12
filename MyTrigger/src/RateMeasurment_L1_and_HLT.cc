// -*- C++ -*-
//
// Package:    RateMeasurment_L1_and_HLT
// Class:      RateMeasurment_L1_and_HLT
// 
/**\class RateMeasurment_L1_and_HLT RateMeasurment_L1_and_HLT.cc TauTrigger2014/RateMeasurment_L1_and_HLT/src/RateMeasurment_L1_and_HLT.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
 */
//
// Original Author:  local user
//         Created:  Thu Jan 16 15:23:21 CET 2014
// $Id$
//
//


// system include files
#include <memory>
#include "TMath.h" //M_PI is in TMath
//#include "DataFormats/Math/interface/deltaPhi.h"
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
//for trigger results
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
//HLT
#include "DataFormats/HLTReco/interface/TriggerEvent.h"


#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "L1Trigger/UCT2015/interface/UCTCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "TH1.h"

//
// class declaration
//

class RateMeasurment_L1_and_HLT : public edm::EDAnalyzer {
public:
    explicit RateMeasurment_L1_and_HLT(const edm::ParameterSet&);
    ~RateMeasurment_L1_and_HLT();
private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    TH1D * Histo_RateReduction;
    TH1D * Mass_BeforAntiEle;
    TH1D * Mass_AfterAntiEle;
    edm::InputTag srcTriggerResults_;
    edm::InputTag srcGenParticle_;
    edm::InputTag L1TauSource_;
    edm::InputTag L1JetSource_;
    edm::InputTag L1MuSource_;
    edm::InputTag srcHLTCaloTowers_;
    edm::InputTag srcL1UpgradeTaus_;
    edm::InputTag srcL1UpgradeIsoTaus_;

    // ----------member data ---------------------------
};

RateMeasurment_L1_and_HLT::RateMeasurment_L1_and_HLT(const edm::ParameterSet& iConfig) {
    using namespace edm;
    edm::Service<TFileService> fs;
    Histo_RateReduction = fs->make<TH1D > ("Histo_RateReduction", "Histo_RateReduction", 10, 0, 10);
    Mass_BeforAntiEle = fs->make<TH1D > ("Mass_BeforAntiMu", "Mass_BeforAntiMu", 200, 0, 200);
    Mass_AfterAntiEle = fs->make<TH1D > ("Mass_AfterAntiMu", "Mass_AfterAntiMu", 200, 0, 200);

    srcTriggerResults_ = iConfig.getParameter<edm::InputTag > ("srcTriggerResults");
    srcGenParticle_ = iConfig.getParameter<edm::InputTag > ("srcGenParticle");
    L1MuSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Mus");
    L1TauSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Taus");
    L1JetSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Jets");
    srcHLTCaloTowers_ = iConfig.getParameter<edm::InputTag > ("srcHLTCaloTowers");
    srcL1UpgradeTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeTaus");
    srcL1UpgradeIsoTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeIsoTaus");




}

RateMeasurment_L1_and_HLT::~RateMeasurment_L1_and_HLT() {
}


//
// member functions
//

float deltaPhi_(float a, float b) {
    float result = a - b;
    while (result > M_PI) result -= 2 * M_PI;
    while (result <= -M_PI) result += 2 * M_PI;
    return fabs(result);
}

float dR(float l1eta, float l1phi, float l2eta, float l2phi) {
    float deta = l1eta - l2eta;
    float dphi = deltaPhi_(l1phi, l2phi);
    return sqrt(deta * deta + dphi * dphi);
}

float doInVarMass(float eta_, float phi_, float itauE, float itaupx, float itaupy, float itaupz, const edm::Event& iEvent) {
    using reco::RecoChargedCandidate;
    using namespace std;
    using namespace reco;
    using namespace edm;
    Handle < std::vector < reco::RecoChargedCandidate >> HLTMuonHandle;
    iEvent.getByLabel("isolatedOnlineMuons", HLTMuonHandle);
    float mass_ = 0;
    for (vector<reco::RecoChargedCandidate>::const_iterator imu = HLTMuonHandle->begin(); imu != HLTMuonHandle->end(); imu++) {
        if (imu->pt() > 17 && fabs(imu->eta()) < 2.4 && dR(imu->eta(), imu->phi(), eta_, phi_) > 0.4) {
            mass_ = sqrt(TMath::Power(imu->energy() + itauE, 2) - TMath::Power(imu->px() + itaupx, 2) - TMath::Power(imu->py() + itaupy, 2) - TMath::Power(imu->pz() + itaupz, 2));
        }
    }
    return mass_;
}

bool hasOverLap(float eta_, float phi_, const edm::Event& iEvent) {
    using reco::Muon;
    using reco::MuonCollection;
    using reco::RecoChargedCandidate;
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;

    Handle < std::vector < reco::RecoChargedCandidate >> HLTMuonHandle;
    iEvent.getByLabel("isolatedOnlineMuons", HLTMuonHandle);
    const std::vector<reco::RecoChargedCandidate> & muons = *(HLTMuonHandle.product());
    std::vector<reco::RecoChargedCandidate>::const_iterator imu = muons.begin();
    std::vector<reco::RecoChargedCandidate>::const_iterator jmu = muons.end();

    //&&&&&&&&&&&&&&&&&
    // Here apply the same logic as MuTau  --> Use Break
    //&&&&&&&&&&&&&&&&&
    bool dR05 = 0;
    for (; imu != jmu; ++imu) {
        if (imu->pt() > 17 && fabs(imu->eta()) < 2.1) dR05 = (dR(imu->eta(), imu->phi(), eta_, phi_) > 0.4 ? 1 : 0);
    }

    return dR05;
}

//bool matchToOfflinMuTaus(int isoOption, float eta_, float phi_, const edm::Event& iEvent) {
//    using namespace std;
//    using namespace reco;
//    using namespace edm;
//    using namespace pat;
//
//
//    Handle<pat::TauCollection> pftausHandle;
//    iEvent.getByLabel("selectedTaus", pftausHandle);
//    const TauCollection &pftau = *(pftausHandle.product());
//    pat::TauCollection::const_iterator ipftau = pftau.begin();
//    pat::TauCollection::const_iterator jpftau = pftau.end();
//
//    bool dR05 = 0;
//    for (; ipftau != jpftau; ++ipftau) {
//        if (isoOption == 3 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonLoose3") > 0.5) {
//            if (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5) {
//                return 1;
//                dR05 = 1;
//                break;
//            } else
//                dR05 = 0;
//        }
//
//    }
//
//    return dR05;
//
//}


// ------------ method called for each event  ------------

void
RateMeasurment_L1_and_HLT::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using reco::Muon;
    using reco::MuonCollection;
    using reco::RecoChargedCandidate;
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;

    edm::Handle<TriggerResults> triggerResults;
    iEvent.getByLabel(srcTriggerResults_, triggerResults);

    Handle < vector < l1extra::L1MuonParticle >> HLTMuonHandle;
    iEvent.getByLabel(L1MuSource_, HLTMuonHandle);

    edm::Handle < edm::SortedCollection<CaloTower, edm::StrictWeakOrdering<CaloTower> >> CaloTowerHandle;
    iEvent.getByLabel(srcHLTCaloTowers_, CaloTowerHandle);

    Handle < vector < l1extra::L1JetParticle >> tausHandle;
    iEvent.getByLabel(L1TauSource_, tausHandle);

    Handle < vector < l1extra::L1JetParticle >> jetsHandle;
    iEvent.getByLabel(L1JetSource_, jetsHandle);

    Handle < vector < UCTCandidate >> tausUpgradeHandle;
    iEvent.getByLabel(srcL1UpgradeTaus_, tausUpgradeHandle);

    Handle < vector < UCTCandidate >> tausUpgradeIsoHandle;
    iEvent.getByLabel(srcL1UpgradeIsoTaus_, tausUpgradeIsoHandle);

    Handle<pat::TauCollection> pftausHandle;
    iEvent.getByLabel("selectedTaus", pftausHandle);

    Handle<pat::TauCollection> tausHandle;
    iEvent.getByLabel("selectedHltPatTausNP", tausHandle); //Close to Legacy in 53X

    Handle<pat::TauCollection> tausHandleNew;
    iEvent.getByLabel("selectedHltPatTausPxl2NP", tausHandleNew); //New One

    Handle < std::vector < reco::RecoChargedCandidate >> HLTMuonHandle;
    iEvent.getByLabel("isolatedOnlineMuons", HLTMuonHandle);


//    if (triggerResults.isValid()) {
//        int ntrigs = triggerResults->size();
//        TriggerNames const &triggerNames = iEvent.triggerNames(*triggerResults);
//        cout << "ntrigs size = " << ntrigs << "\n";
//        for (int itrig = 0; itrig < ntrigs; itrig++) {
//            string name = triggerNames.triggerName(itrig);
//            bool result = triggerResults->accept(itrig);
//            //            size_t foundEl = name.find(eleTrigger);
//            //            size_t foundMu = name.find(muTrigger);
//            //            if (filterTriggerResults && (foundEl != string::npos || foundMu != string::npos))
//            //                (m->HLT)[name] = result;
//            //            else if (!filterTriggerResults)
//            //                (m->HLT)[name] = result;
//
//            //
//            //            if (name == "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2") {
//            //                m->HLT_DiElectron = result;
//            //                // cout << "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2" << endl;
//            //            }
//            //            if (name == "HLT_DoubleMu7_v1") {
//            //                m->HLT_DiMuon = result;
//            //                // cout << "HLT_DoubleMu7_v1" << endl;
//            //            }
//
//            size_t foundMu = name.find("IsoMu17_eta2p1_LooseIsoPFTau20");
//
//            //            Histo_RateReduction->Fill(1);
//            if (foundMu != string::npos) {
//                //                cout << name << " = " << result << endl;
//                if (result == 1) Histo_RateReduction->Fill(2);
//            }
//        }//for itrig
//    }//if triggerResults valid

    bool PassedL1Mu16Tau20 = false;
    int step1 = 0;
    int step2 = 0;
    int step3 = 0;
    int step4 = 0;
    //####################################################################################################
    //    Measuring the L1 Rate
    //####################################################################################################
    for (vector<l1extra::L1MuonParticle>::const_iterator mu = HLTMuonHandle->begin(); mu != HLTMuonHandle->end(); mu++) {
        if (mu->pt() > 16 && fabs(mu->eta()) < 2.2) {
            step1++;

            //******************************************************
            float maxValPt_ucttau = 0;
            for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
                if (matchToMuon(ucttau->eta(), ucttau->phi(), iEvent)) {
                    if (ucttau->pt() > maxValPt_ucttau) maxValPt_ucttau = ucttau->pt();
                }
            }
            rate_UCTCandidate->Fill(maxValPt_ucttau);
            if (maxValPt_ucttau > 20) {
                step2++;
                PassedL1Mu16Tau20 = true;
            }

            //******************************************************
            //            float maxValPt_uctIsotau = 0;
            //            for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {
            //                if (matchToMuon(uctIsotau->eta(), uctIsotau->phi(), iEvent)) {
            //                    if (uctIsotau->pt() > maxValPt_uctIsotau) maxValPt_uctIsotau = uctIsotau->pt();
            //                }
            //            }
            //            rate_UCTCandidateIso->Fill(maxValPt_uctIsotau);
            //******************************************************
            break; // Just once for an event with L1Mu16ER
        }
    }
    //####################################################################################################
    //    Measuring the HLT Rate
    //####################################################################################################
    if (PassedL1Mu16Tau20) {
        for (vector<reco::RecoChargedCandidate>::const_iterator imu = HLTMuonHandle->begin(); imu != HLTMuonHandle->end(); imu++) {

            if (imu->pt() > 16 && fabs(imu->eta()) < 2.1) {
                step3++;
                break; // Just once for an event with L1Mu16ER

                //******************************************************
                //  Making Loop over Taus
                //******************************************************
                for (pat::TauCollection::const_iterator itau = tausHandleNew->begin(); itau != tausHandleNew->end(); itau++) {

                    bool ptCut = itau->pt() > 20 && fabs(itau->eta()) < 2.3;
                    bool hasOverlapMu = hasOverLap(itau->eta(), itau->phi(), iEvent);
                    bool discByDecayModeFinding = (itau->tauID("decayModeFinding") > 0.5 ? true : false);
                    bool discByIsolation5hits = (itau->tauID("byTrkIsolation5hits") < 3.0 ? true : false);
                    bool discByMuLoose = (itau->tauID("againstMuonLoose") > 0.5 ? true : false);

                    if (ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation5hits && discByMuLoose) {
                        step4++;
                    }
                }
            }
        }
    }

    Histo_RateReduction->Fill(0);
    if (step1 > 0) {
        Histo_RateReduction->Fill(1);
    }
    if (step2 > 0) {
        Histo_RateReduction->Fill(2);
    }
    if (step3 > 0) {
        Histo_RateReduction->Fill(3);
    }
    if (step4 > 0) {
        Histo_RateReduction->Fill(4);
    }
}



//define this as a plug-in
DEFINE_FWK_MODULE(RateMeasurment_L1_and_HLT);

