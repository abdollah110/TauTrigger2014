// -*- C++ -*-
//
// Package:    RateMeasurment_L1_and_HLT_Ele
// Class:      RateMeasurment_L1_and_HLT_Ele
// 
/**\class RateMeasurment_L1_and_HLT_Ele RateMeasurment_L1_and_HLT_Ele.cc TauTrigger2014/RateMeasurment_L1_and_HLT_Ele/src/RateMeasurment_L1_and_HLT_Ele.cc

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
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
//for trigger results
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
//HLT
#include "DataFormats/HLTReco/interface/TriggerEvent.h"


#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "L1Trigger/UCT2015/interface/UCTCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "../interface/MyTools.h"

#include "TH1.h"

//
// class declaration
//

class RateMeasurment_L1_and_HLT_Ele : public edm::EDAnalyzer {
public:
    explicit RateMeasurment_L1_and_HLT_Ele(const edm::ParameterSet&);
    ~RateMeasurment_L1_and_HLT_Ele();
    MyTools tool;
private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual bool hasNoOverLapETau(float, float, const edm::Event&);
    virtual bool matchToElectron(float, float, const edm::Event&);
    TH1D * Histo_RateReduction;
    TH1D * Mass_BeforAntiEle;
    TH1D * Mass_AfterAntiEle;
    edm::InputTag srcTriggerResults_;
    edm::InputTag srcGenParticle_;
    edm::InputTag srcL1IsoElectron_;
    edm::InputTag srcL1NonIsoElectron_;
    edm::InputTag L1TauSource_;
    edm::InputTag L1JetSource_;
    edm::InputTag L1MuSource_;
    edm::InputTag srcHLTCaloTowers_;
    edm::InputTag srcL1UpgradeTaus_;
    edm::InputTag srcL1UpgradeIsoTaus_;

    // ----------member data ---------------------------
};

RateMeasurment_L1_and_HLT_Ele::RateMeasurment_L1_and_HLT_Ele(const edm::ParameterSet& iConfig) {
    using namespace edm;
    edm::Service<TFileService> fs;
    Histo_RateReduction = fs->make<TH1D > ("Histo_RateReduction", "Histo_RateReduction", 10, 0, 10);
    Mass_BeforAntiEle = fs->make<TH1D > ("Mass_BeforAntiMu", "Mass_BeforAntiMu", 200, 0, 200);
    Mass_AfterAntiEle = fs->make<TH1D > ("Mass_AfterAntiMu", "Mass_AfterAntiMu", 200, 0, 200);

    srcTriggerResults_ = iConfig.getParameter<edm::InputTag > ("srcTriggerResults");
    srcGenParticle_ = iConfig.getParameter<edm::InputTag > ("srcGenParticle");
    srcL1IsoElectron_ = iConfig.getParameter<edm::InputTag > ("srcL1IsoElectron");
    srcL1NonIsoElectron_ = iConfig.getParameter<edm::InputTag > ("srcL1NonIsoElectron");
    L1MuSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Mus");
    L1TauSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Taus");
    L1JetSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Jets");
    srcHLTCaloTowers_ = iConfig.getParameter<edm::InputTag > ("srcHLTCaloTowers");
    srcL1UpgradeTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeTaus");
    srcL1UpgradeIsoTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeIsoTaus");




}

RateMeasurment_L1_and_HLT_Ele::~RateMeasurment_L1_and_HLT_Ele() {
}


//
// member functions
//

bool RateMeasurment_L1_and_HLT_Ele::hasNoOverLapETau(float eta_, float phi_, const edm::Event& iEvent) {
    using reco::Electron;
    using namespace std;
    using namespace reco;
    using namespace edm;

    //    iEvent.getByLabel("hltPixelMatchElectronsL1Seeded", electronHandle);
    Handle < std::vector < reco::Electron >> electronHandle;
    iEvent.getByLabel("isolatedOnlineElectrons", electronHandle);
    const std::vector<reco::Electron> & elestrons = *(electronHandle.product());
    std::vector<reco::Electron>::const_iterator iele = elestrons.begin();
    std::vector<reco::Electron>::const_iterator jele = elestrons.end();

    bool OneNonOverLappedElectronExist = false;
    for (; iele != jele; ++iele) {
        if (iele->pt() > 22 && fabs(iele->eta()) < 2.5 && tool.dR2(iele->eta(), iele->phi(), eta_, phi_) > 0.4) {
            OneNonOverLappedElectronExist = true;
            break;
        }
    }
    return OneNonOverLappedElectronExist;
}

bool RateMeasurment_L1_and_HLT_Ele::matchToElectron(float ieta, float iphi, const edm::Event& iEvent) {
    using namespace std;
    using namespace edm;

    Handle < vector < l1extra::L1EmParticle >> IsoElectronHandle;
    iEvent.getByLabel(srcL1IsoElectron_, IsoElectronHandle);

    Handle < vector < l1extra::L1EmParticle >> NonIsoElectronHandle;
    iEvent.getByLabel(srcL1NonIsoElectron_, NonIsoElectronHandle);


    bool dR03Iso = false;
    bool dR03NonIso = false;
    for (vector<l1extra::L1EmParticle>::const_iterator isoele = IsoElectronHandle->begin(); isoele != IsoElectronHandle->end(); isoele++) {
        if (isoele->pt() > 12 && tool.dR2(isoele->eta(), isoele->phi(), ieta, iphi) < 0.3) {
            dR03Iso = true;
            //            break;
        }
    }
    for (vector<l1extra::L1EmParticle>::const_iterator isoNele = NonIsoElectronHandle->begin(); isoNele != NonIsoElectronHandle->end(); isoNele++) {
        if (isoNele->pt() > 12 && tool.dR2(isoNele->eta(), isoNele->phi(), ieta, iphi) < 0.3) {
            dR03NonIso = true;
            //            break;
        }
    }
    return (!(dR03Iso || dR03NonIso));

}

void RateMeasurment_L1_and_HLT_Ele::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using reco::Muon;
    using reco::MuonCollection;
    using reco::RecoChargedCandidate;
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;

    edm::Handle<TriggerResults> triggerResults;
    iEvent.getByLabel(srcTriggerResults_, triggerResults);

    Handle < vector < l1extra::L1MuonParticle >> L1MuonHandle;
    iEvent.getByLabel(L1MuSource_, L1MuonHandle);

    edm::Handle < edm::SortedCollection<CaloTower, edm::StrictWeakOrdering<CaloTower> >> CaloTowerHandle;
    iEvent.getByLabel(srcHLTCaloTowers_, CaloTowerHandle);

    //    Handle < vector < l1extra::L1JetParticle >> tausHandle;
    //    iEvent.getByLabel(L1TauSource_, tausHandle);

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

    Handle < std::vector < reco::Electron >> HLTelectronHandle;
    iEvent.getByLabel("isolatedOnlineElectrons", HLTelectronHandle);


    Handle < vector < l1extra::L1EmParticle >> IsoElectronHandle;
    iEvent.getByLabel(srcL1IsoElectron_, IsoElectronHandle);

    Handle < vector < l1extra::L1EmParticle >> NonIsoElectronHandle;
    iEvent.getByLabel(srcL1NonIsoElectron_, NonIsoElectronHandle);



    bool PassedL1Ele18Tau20 = false;
    int step1 = 0;
    int step2 = 0;
    int step3 = 0;
    int step4 = 0;
    //####################################################################################################
    //    Measuring the L1 Rate
    //####################################################################################################

    for (vector<l1extra::L1EmParticle>::const_iterator isoele = IsoElectronHandle->begin(); isoele != IsoElectronHandle->end(); isoele++) {
        if (isoele->pt() > 18 && fabs(isoele->eta()) < 2.2) {
            step1++;
            cout << "1  ___  This event passed L1Mu" << endl;

            //******************************************************
            float maxValPt_ucttau = 0;
            for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
                if (matchToElectron(ucttau->eta(), ucttau->phi(), iEvent)) {
                    if (ucttau->pt() > maxValPt_ucttau) maxValPt_ucttau = ucttau->pt();
                }
            }
            //            rate_UCTCandidate->Fill(maxValPt_ucttau);
            if (maxValPt_ucttau > 20) {
                step2++;
                PassedL1Ele18Tau20 = true;
                cout << "2  ___  This event passed L1Tau" << endl;
            }

            //******************************************************
            //            float maxValPt_uctIsotau = 0;
            //            for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {
            //                if (matchToElectron(uctIsotau->eta(), uctIsotau->phi(), iEvent)) {
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
    if (PassedL1Ele18Tau20) {

        for (vector<reco::Electron>::const_iterator iele = HLTelectronHandle->begin(); iele != HLTelectronHandle->end(); iele++) {
            if (iele->pt() > 22 && fabs(iele->eta()) < 2.5) step1++;

            break; // Just once for an event with L1Mu16ER
            cout << "3  ___  This event passed HLT MU" << endl;
            step3++;

            //******************************************************
            //  Making Loop over Taus
            //******************************************************
            for (pat::TauCollection::const_iterator itau = tausHandleNew->begin(); itau != tausHandleNew->end(); itau++) {

                bool ptCut = itau->pt() > 20 && fabs(itau->eta()) < 2.3;
                bool hasNoOverLapETau_ = hasNoOverLapETau(itau->eta(), itau->phi(), iEvent);
                bool discByDecayModeFinding = (itau->tauID("decayModeFinding") > 0.5 ? true : false);
                bool discByIsolation5hits = (itau->tauID("byTrkIsolation5hits") < 3.0 ? true : false);
                //                bool discByMuLoose = (itau->tauID("againstMuonLoose") > 0.5 ? true : false);

                if (ptCut && hasNoOverLapETau_ && discByDecayModeFinding && discByIsolation5hits) {
                    cout << "4  ___  This event passed HLT Tau" << endl;
                    step4++;
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
    for (pat::TauCollection::const_iterator itau = tausHandleNew->begin(); itau != tausHandleNew->end(); itau++) {

        bool ptCut = itau->pt() > 20 && fabs(itau->eta()) < 2.3;
        bool hasNoOverLapETau_ = hasNoOverLapETau(itau->eta(), itau->phi(), iEvent);
        bool discByDecayModeFinding = (itau->tauID("decayModeFinding") > 0.5 ? true : false);
        bool discByIsolation5hits = (itau->tauID("byTrkIsolation5hits") < 3.0 ? true : false);

        cout << "Tau is existing " << ptCut << hasNoOverLapETau_ << discByDecayModeFinding << discByIsolation5hits << endl;
    }
}




//define this as a plug-in
DEFINE_FWK_MODULE(RateMeasurment_L1_and_HLT_Ele);

