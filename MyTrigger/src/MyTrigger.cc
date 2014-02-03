// -*- C++ -*-
//
// Package:    MyTrigger
// Class:      MyTrigger
// 
/**\class MyTrigger MyTrigger.cc TauTrigger2014/MyTrigger/src/MyTrigger.cc

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
#include "TH1.h"

//
// class declaration
//

class MyTrigger : public edm::EDAnalyzer {
public:
    explicit MyTrigger(const edm::ParameterSet&);
    ~MyTrigger();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob();
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    virtual void beginRun(edm::Run const&, edm::EventSetup const&);
    virtual void endRun(edm::Run const&, edm::EventSetup const&);
    virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
    virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

    TH1D *demohisto;
    TH1D *demohisto_17;
    TH1D * Histo_tauPt;
    TH1D * Histo_tauPt_20;
    TH1D * Histo_Denumerator;
    TH1D * Histo_DenumeratorSV;
    TH1D * Histo_Step1;
    TH1D * Histo_Step2;
    TH1D * Histo_Step3;
    TH1D * Histo_StepSV1;
    TH1D * Histo_StepSV2;
    TH1D * Histo_StepSV3;
    TH1D * Pt_Step1;
    TH1D * Eta_Step1;
    TH1D * Pt_Step2;
    TH1D * Eta_Step2;
    TH1D * Pt_Step3;
    TH1D * Eta_Step3;

    TH1D * Pt_StepSV1;
    TH1D * Eta_StepSV1;
    TH1D * Pt_StepSV2;
    TH1D * Eta_StepSV2;
    TH1D * Pt_StepSV3;
    TH1D * Eta_StepSV3;

    // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

MyTrigger::MyTrigger(const edm::ParameterSet& iConfig) {
    //now do what ever initialization is needed
    using namespace edm;
    edm::Service<TFileService> fs;
    demohisto = fs->make<TH1D > ("MuPt", "MuPt", 50, 0, 250);
    demohisto_17 = fs->make<TH1D > ("MuPt_17", "MuPt_17", 50, 0, 250);
    Histo_tauPt = fs->make<TH1D > ("TauPt", "TauPt", 50, 0, 250);
    Histo_tauPt_20 = fs->make<TH1D > ("TauPt_20", "TauPt_20", 50, 0, 250);
    Histo_Denumerator = fs->make<TH1D > ("TriggerRate", "TriggerRate", 10, 0, 10);
    Histo_DenumeratorSV = fs->make<TH1D > ("TriggerRateStdVtx", "TriggerRateStdVtx", 10, 0, 10);
    Histo_Step1 = fs->make<TH1D > ("Step1-Multiplicity", "Step1-Multiplicity", 10, 0, 10);
    Histo_Step2 = fs->make<TH1D > ("Step2-Multiplicity", "Step2-Multiplicity", 10, 0, 10);
    Histo_Step3 = fs->make<TH1D > ("Step3-Multiplicity", "Step3-Multiplicity", 10, 0, 10);
    Histo_StepSV1 = fs->make<TH1D > ("StepSV1-Multiplicity", "StepSV1-Multiplicity", 10, 0, 10);
    Histo_StepSV2 = fs->make<TH1D > ("StepSV2-Multiplicity", "StepSV2-Multiplicity", 10, 0, 10);
    Histo_StepSV3 = fs->make<TH1D > ("StepSV3-Multiplicity", "StepSV3-Multiplicity", 10, 0, 10);
    Pt_StepSV1 = fs->make<TH1D > ("Pt_StepSV1", "Pt_StepSV1", 40, 0, 200);
    Eta_StepSV1 = fs->make<TH1D > ("Eta_StepSV1", "Eta_StepSV1", 50, -2.5, 2.5);
    Pt_StepSV2 = fs->make<TH1D > ("Pt_StepSV2", "Pt_StepSV2", 40, 0, 200);
    Eta_StepSV2 = fs->make<TH1D > ("Eta_StepSV2", "Eta_StepSV2", 50, -2.5, 2.5);
    Pt_StepSV3 = fs->make<TH1D > ("Pt_StepSV3", "Pt_StepSV3", 40, 0, 200);
    Eta_StepSV3 = fs->make<TH1D > ("Eta_StepSV3", "Eta_StepSV3", 50, -2.5, 2.5);
    Pt_Step1 = fs->make<TH1D > ("Pt_Step1", "Pt_Step1", 40, 0, 200);
    Eta_Step1 = fs->make<TH1D > ("Eta_Step1", "Eta_Step1", 50, -2.5, 2.5);
    Pt_Step2 = fs->make<TH1D > ("Pt_Step2", "Pt_Step2", 40, 0, 200);
    Eta_Step2 = fs->make<TH1D > ("Eta_Step2", "Eta_Step2", 50, -2.5, 2.5);
    Pt_Step3 = fs->make<TH1D > ("Pt_Step3", "Pt_Step3", 40, 0, 200);
    Eta_Step3 = fs->make<TH1D > ("Eta_Step3", "Eta_Step3", 50, -2.5, 2.5);
}

MyTrigger::~MyTrigger() {

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

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

bool hasOverLap(float eta_, float phi_, const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using pat::Muon;
    using pat::MuonCollection;
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;

    Handle<pat::MuonCollection> muonsHandle;
    iEvent.getByLabel("selectedMuons", muonsHandle);
    const MuonCollection & muons = *(muonsHandle.product());
    pat::MuonCollection::const_iterator imu = muons.begin();
    pat::MuonCollection::const_iterator jmu = muons.end();

    //const Provenance& prov = iEvent.getProvenance(muonsHandle.TauHLT());
    //const float& procName = prov.isolations_;
    int ipfmu = 0;
    bool dR05 = 0;
    for (; imu != jmu; ++imu, ipfmu++) {
        if (imu->pt() > 17 && fabs(imu->eta()) < 2.1 && imu->userFloat("PFRelIsoDB04v2") < 0.15) dR05 = (dR(imu->eta(), imu->phi(), eta_, phi_) > 0.5 ? 1 : 0);

    }

    return dR05;
}

bool matchToOfflineTaus(int isoOption, float eta_, float phi_, const edm::Event& iEvent, const edm::EventSetup& iSetup) {
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
        if (isoOption == 1 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
        if (isoOption == 2 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
        if (isoOption == 3 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonLoose2") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
        if (isoOption == 4 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonMedium2") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
        if (isoOption == 5 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonTight2") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);
        if (isoOption == 6 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("againstMuonLoose2") > 0.5) dR05 = (dR(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5 ? 1 : 0);

    }

    return dR05;

}


// ------------ method called for each event  ------------

void
MyTrigger::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using pat::Muon;
    using pat::MuonCollection;
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;



    //******************************************************
    //  REquring at least 1 muon in the event
    //******************************************************
    Handle<pat::MuonCollection> muonsHandle;
    iEvent.getByLabel("selectedMuons", muonsHandle);
    const MuonCollection & muons = *(muonsHandle.product());
    pat::MuonCollection::const_iterator imu = muons.begin();
    pat::MuonCollection::const_iterator jmu = muons.end();

    int ipfmu = 0;
    for (; imu != jmu; ++imu) {
        if (imu->pt() > 17 && fabs(imu->eta()) < 2.1 && imu->userFloat("PFRelIsoDB04v2") < 0.15) ipfmu++;
    }

    //******************************************************
    //  Making Loop over Taus
    //******************************************************


    Handle<pat::TauCollection> tausHandle;
    iEvent.getByLabel("selectedHltPatTaus", tausHandle);
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

        bool ptCut = itau->pt() > 20;
        bool muTauPair = ipfmu > 0;
        bool hasOverlapMu = hasOverLap(itau->eta(), itau->phi(), iEvent, iSetup);
        bool discByDecayModeFinding = (itau->tauID("decayModeFinding") > 0.5 ? true : false);
        bool discByIsolation = (itau->tauID("byIsolation") > 0.5 ? true : false);
        bool discByMuLoose = (itau->tauID("byMuonLoose") > 0.5 ? true : false);

        if (muTauPair && ptCut && hasOverlapMu) {
            step1++;
            Pt_Step1->Fill(itau->pt());
            Eta_Step1->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding) {
            step2++;
            Pt_Step2->Fill(itau->pt());
            Eta_Step2->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation) {
            step3++;
            Pt_Step3->Fill(itau->pt());
            Eta_Step3->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && matchToOfflineTaus(1, itau->eta(), itau->phi(), iEvent, iSetup)) {
            step4++;
            //            Pt_Step3->Fill(itau->pt());
            //            Eta_Step3->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && matchToOfflineTaus(2, itau->eta(), itau->phi(), iEvent, iSetup)) {
            step5++;
            //            Pt_Step3->Fill(itau->pt());
            //            Eta_Step3->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && matchToOfflineTaus(3, itau->eta(), itau->phi(), iEvent, iSetup)) {
            step6++;
            //            Pt_Step3->Fill(itau->pt());
            //            Eta_Step3->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && matchToOfflineTaus(4, itau->eta(), itau->phi(), iEvent, iSetup)) {
            step7++;
            //            Pt_Step3->Fill(itau->pt());
            //            Eta_Step3->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && matchToOfflineTaus(5, itau->eta(), itau->phi(), iEvent, iSetup)) {
            step8++;
            //            Pt_Step3->Fill(itau->pt());
            //            Eta_Step3->Fill(itau->eta());
        }
        if (muTauPair && ptCut && hasOverlapMu && discByDecayModeFinding && discByIsolation && matchToOfflineTaus(6, itau->eta(), itau->phi(), iEvent, iSetup)) {
            step9++;
            //            Pt_Step3->Fill(itau->pt());
            //            Eta_Step3->Fill(itau->eta());
        }


    }

    Histo_Denumerator->Fill(0);
    if (step1 > 0) {
        Histo_Denumerator->Fill(1);
        Histo_Step1->Fill(step1);
    }
    if (step2 > 0) {
        Histo_Denumerator->Fill(2);
        Histo_Step2->Fill(step2);
    }
    if (step3 > 0) {
        Histo_Denumerator->Fill(3);
        Histo_Step3->Fill(step3);
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






    Handle<pat::TauCollection> tausHandleSV;
    iEvent.getByLabel("selectedHltPatTausStdVtx", tausHandleSV);
    const TauCollection &tauSV = *(tausHandleSV.product());
    pat::TauCollection::const_iterator itauSV = tauSV.begin();
    pat::TauCollection::const_iterator jtauSV = tauSV.end();




    int stepSV1 = 0;
    int stepSV2 = 0;
    int stepSV3 = 0;
    int stepSV4 = 0;
    int stepSV5 = 0;
    int stepSV6 = 0;
    int stepSV7 = 0;
    int stepSV8 = 0;
    for (; itauSV != jtauSV; ++itauSV) {

        bool ptCutSV = itauSV->pt() > 20;
        bool muTauPairSV = ipfmu > 0;
        bool hasOverlapMuSV = hasOverLap(itauSV->eta(), itauSV->phi(), iEvent, iSetup);
        bool discByDecayModeFindingSV = itauSV->tauID("decayModeFinding") > 0.5 ? true : false;
        bool discByIsolationSV = itauSV->tauID("byIsolation") > 0.5 ? true : false;

        if (muTauPairSV && ptCutSV && hasOverlapMuSV) {
            stepSV1++;
            Pt_StepSV1->Fill(itauSV->pt());
            Eta_StepSV1->Fill(itauSV->eta());
        }
        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV) {
            stepSV2++;
            Pt_StepSV2->Fill(itauSV->pt());
            Eta_StepSV2->Fill(itauSV->eta());
        }
        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV) {
            stepSV3++;
            Pt_StepSV3->Fill(itauSV->pt());
            Eta_StepSV3->Fill(itauSV->eta());
        }
        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(1, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
            stepSV4++;
            //            Pt_StepSV4->Fill(itauSV->pt());
            //            Eta_StepSV3->Fill(itauSV->eta());
        }
        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(2, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
            stepSV5++;
            //            Pt_StepSV4->Fill(itauSV->pt());
            //            Eta_StepSV3->Fill(itauSV->eta());
        }
        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(3, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
            stepSV6++;
            //            Pt_StepSV4->Fill(itauSV->pt());
            //            Eta_StepSV3->Fill(itauSV->eta());
        }
        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(4, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
            stepSV7++;
            //            Pt_StepSV4->Fill(itauSV->pt());
            //            Eta_StepSV3->Fill(itauSV->eta());
        }
        if (muTauPairSV && ptCutSV && hasOverlapMuSV && discByDecayModeFindingSV && discByIsolationSV && matchToOfflineTaus(5, itauSV->eta(), itauSV->phi(), iEvent, iSetup)) {
            stepSV8++;
            //            Pt_StepSV4->Fill(itauSV->pt());
            //            Eta_StepSV3->Fill(itauSV->eta());
        }
    }
    Histo_DenumeratorSV->Fill(0);
    if (stepSV1 > 0) {
        Histo_DenumeratorSV->Fill(1);
        Histo_StepSV1->Fill(stepSV1);
    }
    if (stepSV2 > 0) {
        Histo_DenumeratorSV->Fill(2);
        Histo_StepSV2->Fill(stepSV2);
    }
    if (stepSV3 > 0) {
        Histo_DenumeratorSV->Fill(3);
        Histo_StepSV3->Fill(stepSV3);
    }
    if (stepSV4 > 0) {
        Histo_DenumeratorSV->Fill(4);
        //        Histo_StepSV3->Fill(stepSV3);
    }
    if (stepSV5 > 0) {
        Histo_DenumeratorSV->Fill(5);
        //        Histo_StepSV3->Fill(stepSV3);
    }
    if (stepSV6 > 0) {
        Histo_DenumeratorSV->Fill(6);
        //        Histo_StepSV3->Fill(stepSV3);
    }
    if (stepSV7 > 0) {
        Histo_DenumeratorSV->Fill(7);
        //        Histo_StepSV3->Fill(stepSV3);
    }
    if (stepSV8 > 0) {
        Histo_DenumeratorSV->Fill(8);
        //        Histo_StepSV3->Fill(stepSV3);
    }




    /*
        Handle<pat::TauCollection> tausHandle;
        iEvent.getByLabel("selectedHltPatTausStdVtx", tausHandle);
        const TauCollection &tau = *(tausHandle.product());
        pat::TauCollection::const_iterator itau = tau.begin();
        pat::TauCollection::const_iterator jtau = tau.end();

     */



}


// ------------ method called once each job just before starting event loop  ------------

void
MyTrigger::beginJob() {
}

// ------------ method called once each job just after ending the event loop  ------------

void
MyTrigger::endJob() {
}

// ------------ method called when starting to processes a run  ------------

void
MyTrigger::beginRun(edm::Run const&, edm::EventSetup const&) {
}

// ------------ method called when ending the processing of a run  ------------

void
MyTrigger::endRun(edm::Run const&, edm::EventSetup const&) {
}

// ------------ method called when starting to processes a luminosity block  ------------

void
MyTrigger::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
}

// ------------ method called when ending the processing of a luminosity block  ------------

void
MyTrigger::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------

void
MyTrigger::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyTrigger);
