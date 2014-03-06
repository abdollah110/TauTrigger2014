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
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
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
    virtual bool matchToOfflineTaus(int isoOption, float eta_, float phi_, const edm::Event& iEvent);
    virtual bool matchToOfflineTausForEleVeto(float eta_, float phi_, const edm::Event& iEvent);


    TH1D * Histo_Rate;
    // ----------member data ---------------------------
};

Etau_rate::Etau_rate(const edm::ParameterSet& iConfig) {
    using namespace edm;
    edm::Service<TFileService> fs;
    Histo_Rate = fs->make<TH1D > ("TriggerRate", "TriggerRate", 10, 0, 10);
}

Etau_rate::~Etau_rate() {
}

bool Etau_rate::hasOverLap(float eta_, float phi_, const edm::Event& iEvent) {
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

    bool dR05 = 1;
    for (; iele != jele; ++iele) {
        if (iele->pt() > 22 && fabs(iele->eta()) < 2.5) dR05 = (tool.dR2(iele->eta(), iele->phi(), eta_, phi_) < 0.4 ? 0 : 1);
    }
    return dR05;
}

bool Etau_rate::matchToOfflineTaus(int isoOption, float eta_, float phi_, const edm::Event& iEvent) {
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;


    Handle<pat::TauCollection> pftausHandle;
    iEvent.getByLabel("selectedTaus", pftausHandle);
    const TauCollection &pftau = *(pftausHandle.product());
    pat::TauCollection::const_iterator ipftau = pftau.begin();
    pat::TauCollection::const_iterator jpftau = pftau.end();


    bool hasMatched = false;
    for (; ipftau != jpftau; ++ipftau) {
        if (isoOption == 1 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("againstElectronLooseMVA5") > 0.5 && tool.dR2(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5) {
            hasMatched = true;
            break;
        }
        if (isoOption == 2 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && tool.dR2(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5) {
            hasMatched = true;
            break;
        }
        if (isoOption == 3 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstElectronLooseMVA5") > 0.5 && tool.dR2(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5) {
            hasMatched = true;
            break;
        }
    }
    return hasMatched;
    //
    //    int hasMatched = 0;
    //    for (; ipftau != jpftau; ++ipftau) {
    //        if (isoOption == 1 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("againstElectronLooseMVA5") > 0.5 && tool.dR2(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5) hasMatched++;
    //        if (isoOption == 2 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && tool.dR2(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5) hasMatched++;
    //        if (isoOption == 3 && ipftau->pt() > 20 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstElectronLooseMVA5") > 0.5 && tool.dR2(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.5) hasMatched++;
    //    }
    //
    //    if (hasMatched > 0)
    //        return true;
    //    else
    //        return false;
}

bool Etau_rate::matchToOfflineTausForEleVeto(float eta_, float phi_, const edm::Event& iEvent) {
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;


    Handle<pat::TauCollection> pftausHandle;
    iEvent.getByLabel("selectedTaus", pftausHandle);
    const TauCollection &pftau = *(pftausHandle.product());
    pat::TauCollection::const_iterator ipftau = pftau.begin();
    pat::TauCollection::const_iterator jpftau = pftau.end();


    int numMatched = 0;
    int numMatchedEleVeto = 0;
    for (; ipftau != jpftau; ++ipftau) {
        if (tool.dR2(ipftau->eta(), ipftau->phi(), eta_, phi_) < 0.4) {
            numMatched++;
            if (ipftau->tauID("againstElectronLooseMVA5") > 0.5) numMatchedEleVeto++;
        }
    }
    if (numMatchedEleVeto > 0 || numMatched < 1)
        return true;
    else
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
    //  REquring at least 1 HLT Electron in the event
    //******************************************************
    Handle < std::vector < reco::Electron >> electronHandle;
    iEvent.getByLabel("isolatedOnlineElectrons", electronHandle);
    const std::vector<reco::Electron> & elestrons = *(electronHandle.product());
    std::vector<reco::Electron>::const_iterator iele = elestrons.begin();
    std::vector<reco::Electron>::const_iterator jele = elestrons.end();

    int ipfele = 0;
    for (; iele != jele; ++iele) {
        if (iele->pt() > 22 && fabs(iele->eta()) < 2.5) ipfele++;
    }

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
        bool EleTauPair = ipfele > 0;
        bool hasOverlapEle = hasOverLap(itau->eta(), itau->phi(), iEvent);
        bool discByDecayModeFinding = (itau->tauID("decayModeFinding") > 0.5 ? true : false);
        bool discByIsolation5hits = (itau->tauID("byTrkIsolation5hits") < 3.0 ? true : false);
        bool discByEleLoose = matchToOfflineTausForEleVeto(itau->eta(), itau->phi(), iEvent);
        //        bool discByIsolation = (itau->tauID("byIsolation") > 0.5 ? true : false);
        //        bool discByIsolation = (itau->tauID("byTrkIsolation") < 3.0 ? true : false);

        if (EleTauPair && ptCut && hasOverlapEle) step1++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding) step2++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByEleLoose) step3++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits)step4++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits && discByEleLoose) step5++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits && discByEleLoose && matchToOfflineTaus(1, itau->eta(), itau->phi(), iEvent)) step6++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits && discByEleLoose && matchToOfflineTaus(2, itau->eta(), itau->phi(), iEvent)) step7++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits && discByEleLoose && matchToOfflineTaus(3, itau->eta(), itau->phi(), iEvent)) step8++;
    } // end of loop over taus

    Histo_Rate->Fill(0);
    if (step1 > 0) Histo_Rate->Fill(1);
    if (step2 > 0) Histo_Rate->Fill(2);
    if (step3 > 0) Histo_Rate->Fill(3);
    if (step4 > 0) Histo_Rate->Fill(4);
    if (step5 > 0) Histo_Rate->Fill(5);
    if (step6 > 0) Histo_Rate->Fill(6);
    if (step7 > 0) Histo_Rate->Fill(7);
    if (step8 > 0) Histo_Rate->Fill(8);
    if (step9 > 0) Histo_Rate->Fill(9);
    //        cout << iEvent.id().run() << ":" << iEvent.id().luminosityBlock() << ":" << iEvent.id().event() << "\n";

}// end of Analyze



//define this as a plug-in
DEFINE_FWK_MODULE(Etau_rate);
