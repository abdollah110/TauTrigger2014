// -*- C++ -*-
//
// Package:    Etau_rate
// Class:      Etau_rate
// 
/**\class Etau_rate Etau_rate.cc TauTrigger2014/Etau_rate/src/Etau_rate.cc

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
#include "../interface/MyTools.h"

//
// class declaration
//

class Etau_rate : public edm::EDAnalyzer {
public:
    explicit Etau_rate(const edm::ParameterSet&);
    ~Etau_rate();
    MyTools tool;

private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual bool hasOverLap(float eta_, float phi_, const edm::Event& iEvent);


    TH1D *demohisto;
    TH1D *demohisto_17;
    TH1D * Histo_tauPt;
    TH1D * Histo_tauPt_20;
    TH1D * Histo_Denumerator;
    TH1D * Histo_DenumeratorSV;
    // ----------member data ---------------------------
};

Etau_rate::Etau_rate(const edm::ParameterSet& iConfig) {
    using namespace edm;
    edm::Service<TFileService> fs;
    demohisto = fs->make<TH1D > ("MuPt", "MuPt", 50, 0, 250);
    demohisto_17 = fs->make<TH1D > ("MuPt_17", "MuPt_17", 50, 0, 250);
    Histo_tauPt = fs->make<TH1D > ("TauPt", "TauPt", 50, 0, 250);
    Histo_tauPt_20 = fs->make<TH1D > ("TauPt_20", "TauPt_20", 50, 0, 250);
    Histo_Denumerator = fs->make<TH1D > ("TriggerRate", "TriggerRate", 10, 0, 10);
    Histo_DenumeratorSV = fs->make<TH1D > ("TriggerRateStdVtx", "TriggerRateStdVtx", 10, 0, 10);
}

Etau_rate::~Etau_rate() {
}

bool Etau_rate::hasOverLap(float eta_, float phi_, const edm::Event& iEvent) {
    using reco::Muon;
    using reco::MuonCollection;
    using reco::RecoChargedCandidate;
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;

    //    Handle<pat::MuonCollection> electronHandle;
    //    iEvent.getByLabel("selectedMuons", electronHandle);
    Handle < std::vector < reco::RecoChargedCandidate >> electronHandle;
    //    iEvent.getByLabel("hltMuons", electronHandle);
    iEvent.getByLabel("isolatedOnlineElectrons", electronHandle);
    const std::vector<reco::RecoChargedCandidate> & muons = *(electronHandle.product());
    std::vector<reco::RecoChargedCandidate>::const_iterator imu = muons.begin();
    std::vector<reco::RecoChargedCandidate>::const_iterator jmu = muons.end();
    //    //    Handle<pat::MuonCollection> electronHandle;
    //    //    iEvent.getByLabel("selectedMuons", electronHandle);
    //    Handle<reco::MuonCollection> electronHandle;
    //    //    iEvent.getByLabel("hltMuons", electronHandle);
    //    iEvent.getByLabel("hltL3MuonCandidates", electronHandle);
    //    const MuonCollection & muons = *(electronHandle.product());
    //    reco::MuonCollection::const_iterator imu = muons.begin();
    //    reco::MuonCollection::const_iterator jmu = muons.end();

    //const Provenance& prov = iEvent.getProvenance(electronHandle.TauHLT());
    //const float& procName = prov.isolations_;

    bool dR05 = 0;
    //    cout<<imu->userFloat("PFRelIsoDB0ChargedCandidateFromTrigRefConverter
    for (; imu != jmu; ++imu) {
        //        if (imu->pt() > 17 && fabs(imu->eta()) < 2.1 && imu->userFloat("PFRelIsoDB04v2") < 0.15) dR05 = (dR(imu->eta(), imu->phi(), eta_, phi_) > 0.5 ? 1 : 0);
        if (imu->pt() > 17 && fabs(imu->eta()) < 2.1) dR05 = (tool.dR2(imu->eta(), imu->phi(), eta_, phi_) > 0.4 ? 1 : 0);
        //        if (imu->pt() > 17 && fabs(imu->eta()) < 2.1) dR05 = (dR(imu->eta(), imu->phi(), eta_, phi_) > 0.3 ? 1 : 0);

        //    }

    }
    return dR05;
}

bool matchToOfflineTaus(int isoOption, float eta_, float phi_, const edm::Event& iEvent) {
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
    //    for (; ipftau != jpftau; ++ipftau) {
    //        if (isoOption == 1 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr") > 0.5) dR05 = (t.dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
    //        if (isoOption == 2 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
    //        if (isoOption == 3 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonLoose3") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
    //        if (isoOption == 4 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonMedium3") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
    //        if (isoOption == 5 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonTight3") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
    //        if (isoOption == 6 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("againstMuonLoose3") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
    //
    //    }

    return false;
}


// ------------ method called for each event  ------------

void
Etau_rate::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
//    using reco::Muon;
//    using reco::MuonCollection;
    using reco::RecoChargedCandidate;
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;



    //******************************************************
    //  REquring at least 1 muon in the event
    //******************************************************
    Handle < std::vector < reco::RecoChargedCandidate >> electronHandle;
    iEvent.getByLabel("isolatedOnlineElectrons", electronHandle);
    const std::vector<reco::RecoChargedCandidate> & elestrons = *(electronHandle.product());
    std::vector<reco::RecoChargedCandidate>::const_iterator iele = elestrons.begin();
    std::vector<reco::RecoChargedCandidate>::const_iterator jele = elestrons.end();

    int ipfele = 0;
    for (; iele != jele; ++iele) {
        if (iele->pt() > 17 && fabs(iele->eta()) < 2.1) ipfele++;
    }
    //
    //    //******************************************************
    //    //  REquring at least 1 muon in the event
    //    //******************************************************
    //    //    Handle<pat::MuonCollection> electronHandle;
    //    //    iEvent.getByLabel("selectedMuons", electronHandle);
    //    Handle<reco::recoRecoChargedCandidates> electronHandle;
    //    //    iEvent.getByLabel("hltMuons", electronHandle);
    //    iEvent.getByLabel("hltL3MuonCandidates", electronHandle);
    //    const MuonCollection & muons = *(electronHandle.product());
    //    reco::MuonCollection::const_iterator imu = muons.begin();
    //    reco::MuonCollection::const_iterator jmu = muons.end();
    //
    //    int ipfmu = 0;
    //    for (; imu != jmu; ++imu) {
    //        //        if (imu->pt() > 17 && fabs(imu->eta()) < 2.1 && imu->userFloat("PFRelIsoDB04v2") < 0.15) ipfmu++;
    //        if (imu->pt() > 17 && fabs(imu->eta()) < 2.1) ipfmu++;
    //    }

    //******************************************************
    //  Making Loop over Taus
    //******************************************************


    Handle<pat::TauCollection> tausHandle;
    //    iEvent.getByLabel("selectedHltPatTaus", tausHandle);
    iEvent.getByLabel("selectedHltPatTausPxl2NP", tausHandle);
    const TauCollection &tau = *(tausHandle.product());
    pat::TauCollection::const_iterator itau = tau.begin();
    pat::TauCollection::const_iterator jtau = tau.end();




    int step1 = 0;
    int step2 = 0;
    int step3 = 0;
    int step4 = 0;
    int step5 = 0;
    int step6 = 0;
    int step7 = 0;
    int step8 = 0;
    int step9 = 0;


    for (; itau != jtau; ++itau) {

        bool ptCut = itau->pt() > 20 && fabs(itau->eta()) < 2.3;
        //        bool muTauPair = ipfmu > 0;
        bool muTauPair = 1 > 0;
        bool hasOverlapMu = hasOverLap(itau->eta(), itau->phi(), iEvent);
        bool discByDecayModeFinding = (itau->tauID("decayModeFinding") > 0.5 ? true : false);
        //        bool discByIsolation = (itau->tauID("byIsolation") > 0.5 ? true : false);
        bool discByIsolation = (itau->tauID("byTrkIsolation") < 3.0 ? true : false);
        bool discByIsolation5hits = (itau->tauID("byTrkIsolation5hits") < 3.0 ? true : false);
        bool discByMuLoose = (itau->tauID("againstMuonLoose") > 0.5 ? true : false);

        if (muTauPair && ptCut && hasOverlapMu) {
            step1++;
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding) {
            step2++;
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByMuLoose) {
            step3++;
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByMuLoose && discByIsolation) {
            step4++;
            //            Pt_Step4->Fill(itau->pt());
            //            Eta_Step4->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByMuLoose && discByIsolation5hits) {
            step5++;
            //            Pt_Step4->Fill(itau->pt());
            //            Eta_Step4->Fill(itau->eta());
        }
        //        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && matchToOfflineTaus(1, itau->eta(), itau->phi(), iEvent, iSetup)) {
        //            step4++;
        //            //            Pt_Step3->Fill(itau->pt());
        //            //            Eta_Step3->Fill(itau->eta());
        //        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && discByMuLoose && matchToOfflineTaus(6, itau->eta(), itau->phi(), iEvent)) {
            step6++;
            //            Pt_Step3->Fill(itau->pt());
            //            Eta_Step3->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && discByMuLoose && matchToOfflineTaus(2, itau->eta(), itau->phi(), iEvent)) {
            step7++;
            //            Pt_Step3->Fill(itau->pt());
            //            Eta_Step3->Fill(itau->eta());
        }
        //        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && discByMuLoose && matchToOfflineTaus(4, itau->eta(), itau->phi(), iEvent, iSetup)) {
        //            step7++;
        //            //            Pt_Step3->Fill(itau->pt());
        //            //            Eta_Step3->Fill(itau->eta());
        //        }
        ////        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && discByMuLoose && matchToOfflineTaus(5, itau->eta(), itau->phi(), iEvent, iSetup)) {
        //            step8++;
        //            //            Pt_Step3->Fill(itau->pt());
        //            //            Eta_Step3->Fill(itau->eta());
        //        }
        //        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && discByMuLoose && matchToOfflineTaus(6, itau->eta(), itau->phi(), iEvent, iSetup)) {
        //            step9++;
        //            //            Pt_Step3->Fill(itau->pt());
        //            //            Eta_Step3->Fill(itau->eta());
        //        }


    }

    Histo_Denumerator->Fill(0);
    if (step1 > 0) {
        Histo_Denumerator->Fill(1);
//        Histo_Step1->Fill(step1);
    }
    if (step2 > 0) {
        Histo_Denumerator->Fill(2);
//        Histo_Step2->Fill(step2);
    }
    if (step3 > 0) {
        Histo_Denumerator->Fill(3);
//        Histo_Step3->Fill(step3);
    }
    if (step4 > 0) {
        Histo_Denumerator->Fill(4);
        //        Histo_Step4->Fill(step4);
    }
    if (step5 > 0) {
        Histo_Denumerator->Fill(5);
        //        Histo_Step4->Fill(step4);
    }
    if (step6 > 0) {
        Histo_Denumerator->Fill(6);
        //        Histo_Step4->Fill(step4);
    }
    if (step7 > 0) {
        Histo_Denumerator->Fill(7);
        //        Histo_Step4->Fill(step4);
    }
    if (step8 > 0) {
        Histo_Denumerator->Fill(8);
        //        Histo_Step4->Fill(step4);
    }
    if (step9 > 0) {
        Histo_Denumerator->Fill(9);
        //        Histo_Step4->Fill(step4);
    }





    //
    //    Handle<pat::TauCollection> tausHandleSV;
    //    iEvent.getByLabel("selectedHltPatTausStdVtx", tausHandleSV);
    //    const TauCollection &tauSV = *(tausHandleSV.product());
    //    pat::TauCollection::const_iterator itauSV = tauSV.begin();
    //    pat::TauCollection::const_iterator jtauSV = tauSV.end();
    //
    //
    //
    //
    //    int stepSV1 = 0;
    //    int stepSV2 = 0;
    //    int stepSV3 = 0;
    //    int stepSV4 = 0;
    //    int stepSV5 = 0;
    //    int stepSV6 = 0;
    //    int stepSV7 = 0;
    //    int stepSV8 = 0;
    //    for (; itauSV != jtauSV; ++itauSV) {
    //
    //        bool ptCutSV = itauSV->pt() > 20;
    //        bool muTauPairSV = ipfmu > 0;
    //        bool hasOverlapMuSV = hasOverLap(itauSV->eta(), itauSV->phi(), iEvent, iSetup);
    //        bool discByDecayModeFindingSV = itauSV->tauID("decayModeFinding") > 0.5 ? true : false;
    //        bool discByIsolationSV = itauSV->tauID("byIsolation") > 0.5 ? true : false;
    //
    //        if (muTauPairSV && ptCutSV && hasOverlapMuSV) {
    //            stepSV1++;
    //            Pt_StepSV1->Fill(itauSV->pt());
    //            Eta_StepSV1->Fill(itauSV->eta());
    //        }
    //        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV) {
    //            stepSV2++;
    //            Pt_StepSV2->Fill(itauSV->pt());
    //            Eta_StepSV2->Fill(itauSV->eta());
    //        }
    //        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV) {
    //            stepSV3++;
    //            Pt_StepSV3->Fill(itauSV->pt());
    //            Eta_StepSV3->Fill(itauSV->eta());
    //        }
    //        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(1, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
    //            stepSV4++;
    //            //            Pt_StepSV4->Fill(itauSV->pt());
    //            //            Eta_StepSV3->Fill(itauSV->eta());
    //        }
    //        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(2, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
    //            stepSV5++;
    //            //            Pt_StepSV4->Fill(itauSV->pt());
    //            //            Eta_StepSV3->Fill(itauSV->eta());
    //        }
    //        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(3, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
    //            stepSV6++;
    //            //            Pt_StepSV4->Fill(itauSV->pt());
    //            //            Eta_StepSV3->Fill(itauSV->eta());
    //        }
    //        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(4, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
    //            stepSV7++;
    //            //            Pt_StepSV4->Fill(itauSV->pt());
    //            //            Eta_StepSV3->Fill(itauSV->eta());
    //        }
    //        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(5, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
    //            stepSV8++;
    //            //            Pt_StepSV4->Fill(itauSV->pt());
    //            //            Eta_StepSV3->Fill(itauSV->eta());
    //        }
    //    }
    //    Histo_DenumeratorSV->Fill(0);
    //    if (stepSV1 > 0) {
    //        Histo_DenumeratorSV->Fill(1);
    //        Histo_StepSV1->Fill(stepSV1);
    //    }
    //    if (stepSV2 > 0) {
    //        Histo_DenumeratorSV->Fill(2);
    //        Histo_StepSV2->Fill(stepSV2);
    //    }
    //    if (stepSV3 > 0) {
    //        Histo_DenumeratorSV->Fill(3);
    //        Histo_StepSV3->Fill(stepSV3);
    //    }
    //    if (stepSV4 > 0) {
    //        Histo_DenumeratorSV->Fill(4);
    //        //        Histo_StepSV3->Fill(stepSV3);
    //    }
    //    if (stepSV5 > 0) {
    //        Histo_DenumeratorSV->Fill(5);
    //        //        Histo_StepSV3->Fill(stepSV3);
    //    }
    //    if (stepSV6 > 0) {
    //        Histo_DenumeratorSV->Fill(6);
    //        //        Histo_StepSV3->Fill(stepSV3);
    //    }
    //    if (stepSV7 > 0) {
    //        Histo_DenumeratorSV->Fill(7);
    //        //        Histo_StepSV3->Fill(stepSV3);
    //    }
    //    if (stepSV8 > 0) {
    //        Histo_DenumeratorSV->Fill(8);
    //        //        Histo_StepSV3->Fill(stepSV3);
    //    }




    /*
        Handle<pat::TauCollection> tausHandle;
        iEvent.getByLabel("selectedHltPatTausStdVtx", tausHandle);
        const TauCollection &tau = *(tausHandle.product());
        pat::TauCollection::const_iterator itau = tau.begin();
        pat::TauCollection::const_iterator jtau = tau.end();

     */



}



//define this as a plug-in
DEFINE_FWK_MODULE(Etau_rate);