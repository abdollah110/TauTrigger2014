// -*- C++ -*-
//
// Package:    HLTMu_Rate
// Class:      HLTMu_Rate
// 
/**\class HLTMu_Rate HLTMu_Rate.cc TauTrigger2014/HLTMu_Rate/src/HLTMu_Rate.cc

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
#include "TH1.h"

//
// class declaration
//

class HLTMu_Rate : public edm::EDAnalyzer {
public:
    explicit HLTMu_Rate(const edm::ParameterSet&);
    ~HLTMu_Rate();
private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    TH1D * Histo_RateReduction;
    TH1D * Mass_BeforAntiEle;
    TH1D * Mass_AfterAntiEle;
    edm::InputTag srcTriggerResults_;

    // ----------member data ---------------------------
};

HLTMu_Rate::HLTMu_Rate(const edm::ParameterSet& iConfig) {
    using namespace edm;
    edm::Service<TFileService> fs;
    Histo_RateReduction = fs->make<TH1D > ("Histo_RateReduction", "Histo_RateReduction", 10, 0, 10);
    Mass_BeforAntiEle = fs->make<TH1D > ("Mass_BeforAntiMu", "Mass_BeforAntiMu", 200, 0, 200);
    Mass_AfterAntiEle = fs->make<TH1D > ("Mass_AfterAntiMu", "Mass_AfterAntiMu", 200, 0, 200);

    srcTriggerResults_ = iConfig.getParameter<edm::InputTag > ("srcTriggerResults");
}

HLTMu_Rate::~HLTMu_Rate() {
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
    Handle < std::vector < reco::RecoChargedCandidate >> muonsHandle;
    iEvent.getByLabel("isolatedOnlineMuons", muonsHandle);
    float mass_ = 0;
    for (vector<reco::RecoChargedCandidate>::const_iterator imu = muonsHandle->begin(); imu != muonsHandle->end(); imu++) {
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

    //    Handle<pat::MuonCollection> muonsHandle;
    //    iEvent.getByLabel("selectedMuons", muonsHandle);
    Handle < std::vector < reco::RecoChargedCandidate >> muonsHandle;
    //    iEvent.getByLabel("hltMuons", muonsHandle);
    iEvent.getByLabel("isolatedOnlineMuons", muonsHandle);
    const std::vector<reco::RecoChargedCandidate> & muons = *(muonsHandle.product());
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

bool matchToOfflinMuTaus(int isoOption, float eta_, float phi_, const edm::Event& iEvent) {
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;


    Handle<pat::TauCollection> pftausHandle;
    iEvent.getByLabel("selectedTaus", pftausHandle);
    const TauCollection &pftau = *(pftausHandle.product());
    pat::TauCollection::const_iterator ipftau = pftau.begin();
    pat::TauCollection::const_iterator jpftau = pftau.end();

    bool dR05 = 0;
    for (; ipftau != jpftau; ++ipftau) {
        if (isoOption == 3 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonLoose3") > 0.5) {
            if (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5) {
                return 1;
                dR05 = 1;
                break;
            } else
                dR05 = 0;
        }

    }

    return dR05;

}


// ------------ method called for each event  ------------

void
HLTMu_Rate::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using reco::Muon;
    using reco::MuonCollection;
    using reco::RecoChargedCandidate;
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;

    edm::Handle<TriggerResults> triggerResults;
    iEvent.getByLabel(srcTriggerResults_, triggerResults);

    int ntrigs = triggerResults->size();
    TriggerNames const &triggerNames = iEvent.triggerNames(*triggerResults);
    for (int itrig = 0; itrig < ntrigs; itrig++) {
        string name = triggerNames.triggerName(itrig);
        bool result = triggerResults->accept(itrig);
        (m->HLT)[name] = result;


        if (name == "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2")
            cout << name << " = "result << endl;
    }//for itrig



    //******************************************************
    //  REquring at least 1 muon in the event
    //******************************************************
    Handle < std::vector < reco::RecoChargedCandidate >> muonsHandle;
    iEvent.getByLabel("isolatedOnlineMuons", muonsHandle);
    const std::vector<reco::RecoChargedCandidate> & muons = *(muonsHandle.product());
    std::vector<reco::RecoChargedCandidate>::const_iterator imu = muons.begin();
    std::vector<reco::RecoChargedCandidate>::const_iterator jmu = muons.end();

    int ipfmu = 0;
    for (; imu != jmu; ++imu) {
        if (imu->pt() > 17 && fabs(imu->eta()) < 2.1) ipfmu++;
    }

    //******************************************************
    //  Making Loop over Taus
    //******************************************************
    Handle<pat::TauCollection> tausHandle;
    //    iEvent.getByLabel("selectedHltPatTaus", tausHandle);
    //    iEvent.getByLabel("selectedHltPatTausPxl2NP", tausHandle);
    //    iEvent.getByLabel("selectedHltPatTausPxl2R18NInfNP", tausHandle); //Legacy
    iEvent.getByLabel("selectedHltPatTausNP", tausHandle); //Close to Legacy in 53X
    const TauCollection &tau = *(tausHandle.product());
    pat::TauCollection::const_iterator itau = tau.begin();
    pat::TauCollection::const_iterator jtau = tau.end();




    int step1 = 0;
    int step2 = 0;
    int step3 = 0;
    int step4 = 0;
    int step5 = 0;
    int step6 = 0;


    for (; itau != jtau; ++itau) {

        bool ptCut = itau->pt() > 20 && fabs(itau->eta()) < 2.3;
        //        bool muTauPair = ipfmu > 0;
        bool muTauPair = 1 > 0;
        bool hasOverlapMu = hasOverLap(itau->eta(), itau->phi(), iEvent);
        bool discByDecayModeFinding = (itau->tauID("decayModeFinding") > 0.5 ? true : false);
        bool discByIsolation = (itau->tauID("byIsolation") > 0.5 ? true : false);
        //        bool discByIsolation = (itau->tauID("byTrkIsolation") < 3.0 ? true : false);
        bool discByIsolation5hits = (itau->tauID("byTrkIsolation5hits") < 3.0 ? true : false);
        bool discByMuLoose = (itau->tauID("againstMuonLoose") > 0.5 ? true : false);
        float InvarMass_Mass_MuTau = doInVarMass(itau->eta(), itau->phi(), itau->energy(), itau->px(), itau->py(), itau->pz(), iEvent);

        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding) {
            step1++;
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation) {
            step2++;
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation5hits) {
            step3++;
            Mass_BeforAntiEle->Fill(InvarMass_Mass_MuTau);

        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation5hits && discByMuLoose) {
            step4++;
            Mass_AfterAntiEle->Fill(InvarMass_Mass_MuTau);
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation5hits && discByMuLoose && matchToOfflinMuTaus(3, itau->eta(), itau->phi(), iEvent)) {
            step5++;
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
    if (step5 > 0) {
        Histo_RateReduction->Fill(5);
    }
    if (step6 > 0) {
        Histo_RateReduction->Fill(6);
    }

}



//define this as a plug-in
DEFINE_FWK_MODULE(HLTMu_Rate);



