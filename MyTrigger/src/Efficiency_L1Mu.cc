// -*- C++ -*-
//
// Package:    Efficiency_L1Mu
// Class:      Efficiency_L1Mu
//
/**\class Efficiency_L1Mu Efficiency_L1Mu.cc TauTrigger2014/Efficiency_L1Mu/src/Efficiency_L1Mu.cc

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
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "L1Trigger/UCT2015/interface/UCTCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "TH1.h"
#include "../interface/MyTools.h"

//
// class declaration
//

class Efficiency_L1Mu : public edm::EDAnalyzer {
public:
    explicit Efficiency_L1Mu(const edm::ParameterSet&);
    ~Efficiency_L1Mu();
    MyTools t;

    //    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual bool matchToGenTau(float ieta, float iphi, const edm::Event& iEvent, const edm::EventSetup& iSetup);
    virtual bool matchToOfflineTausEff(const edm::Event& iEvent);

    TH1D *demohisto;
    TH1D *l1extraParticles;
    TH1D *RelaxedTauUnpacked;
    TH1D *IsolatedTauUnpacked;
    TH1D *l1extraParticles_Denum;
    TH1D *RelaxedTauUnpacked_Denum;
    TH1D *IsolatedTauUnpacked_Denum;
    TH1D *offLineTau;
    TH1D *eff_num_L1Tau;
    TH1D *eff_denum_L1Tau;


    edm::InputTag srcGenParticle_;
    edm::InputTag L1TauSource_;
    edm::InputTag L1MuSource_;
    edm::InputTag srcHLTCaloTowers_;
    edm::InputTag srcL1UpgradeTaus_;
    edm::InputTag srcL1UpgradeIsoTaus_;


    map<string, TH1F*>* myMap1__;

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

Efficiency_L1Mu::Efficiency_L1Mu(const edm::ParameterSet& iConfig) {
    //now do what ever initialization is needed
    using namespace edm;
    edm::Service<TFileService> fs;
    myMap1__ = new std::map<std::string, TH1F*>();

    demohisto = fs->make<TH1D > ("demo", "demo", 50, 0, 50);
    l1extraParticles = fs->make<TH1D > ("l1extraParticles", "", 50, 0, 100);
    RelaxedTauUnpacked = fs->make<TH1D > ("RelaxedTauUnpacked", "", 50, 0, 100);
    IsolatedTauUnpacked = fs->make<TH1D > ("IsolatedTauUnpacked", "", 50, 0, 100);
    l1extraParticles_Denum = fs->make<TH1D > ("l1extraParticles_Denum", "", 50, 0, 100);
    RelaxedTauUnpacked_Denum = fs->make<TH1D > ("RelaxedTauUnpacked_Denum", "", 50, 0, 100);
    IsolatedTauUnpacked_Denum = fs->make<TH1D > ("IsolatedTauUnpacked_Denum", "", 50, 0, 100);
    offLineTau = fs->make<TH1D > ("offLineTau", "", 50, 0, 100);
    eff_num_L1Tau = fs->make<TH1D > ("eff_num_L1Tau", "", 50, 0, 100);
    eff_denum_L1Tau = fs->make<TH1D > ("eff_denum_L1Tau", "", 50, 0, 100);



    srcGenParticle_ = iConfig.getParameter<edm::InputTag > ("srcGenParticle");
    L1MuSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Mus");
    L1TauSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Taus");
    srcHLTCaloTowers_ = iConfig.getParameter<edm::InputTag > ("srcHLTCaloTowers");
    srcL1UpgradeTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeTaus");
    srcL1UpgradeIsoTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeIsoTaus");
}

Efficiency_L1Mu::~Efficiency_L1Mu() {

    map<string, TH1F*>::const_iterator iMap1 = myMap1__->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1__->end();

    //    for (; iMap1 != jMap1; ++iMap1)
    //        t.nplot1(iMap1->first)->Write();

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

bool Efficiency_L1Mu::matchToGenTau(float ieta, float iphi, const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;
    using reco::GenParticle;


    Handle < reco::GenParticleCollection> genTausHandle;
    iEvent.getByLabel(srcGenParticle_, genTausHandle);


    bool dR03 = false;
    for (reco::GenParticleCollection::const_iterator genPar = genTausHandle->begin(); genPar != genTausHandle->end(); genPar++) {
        if (abs(genPar->pdgId()) == 15 && t.dR2(genPar->eta(), genPar->phi(), ieta, iphi) < 0.3)
            dR03 = true;
    }
    return dR03;
}

bool Efficiency_L1Mu::matchToOfflineTausEff(const edm::Event& iEvent) {
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;


    Handle<pat::TauCollection> pftausHandle;
    iEvent.getByLabel("selectedTaus", pftausHandle);
    const TauCollection &pftau = *(pftausHandle.product());
    pat::TauCollection::const_iterator ipftau = pftau.begin();
    pat::TauCollection::const_iterator jpftau = pftau.end();


    bool thereIsAGoodTau = false;
    for (; ipftau != jpftau; ++ipftau) {
        if (ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits") > 0.5 && ipftau->tauID("againstMuonTight") > 0.5 && ipftau->tauID("againstElectronLoose") > 0.5)
            thereIsAGoodTau = true;
    }
    return thereIsAGoodTau;
}




// ------------ method called for each event  ------------

void
Efficiency_L1Mu::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using reco::Muon;
    using reco::MuonCollection;
    using reco::RecoChargedCandidate;
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;






    Handle < vector < l1extra::L1MuonParticle >> muonsHandle;
    iEvent.getByLabel(L1MuSource_, muonsHandle);

    edm::Handle < edm::SortedCollection<CaloTower, edm::StrictWeakOrdering<CaloTower> >> CaloTowerHandle;
    iEvent.getByLabel(srcHLTCaloTowers_, CaloTowerHandle);

    Handle < vector < l1extra::L1JetParticle >> tausHandle;
    iEvent.getByLabel(L1TauSource_, tausHandle);

    Handle < vector < UCTCandidate >> tausUpgradeHandle;
    iEvent.getByLabel(srcL1UpgradeTaus_, tausUpgradeHandle);

    Handle < vector < UCTCandidate >> tausUpgradeIsoHandle;
    iEvent.getByLabel(srcL1UpgradeIsoTaus_, tausUpgradeIsoHandle);

    int step1 = 0;
    for (vector<l1extra::L1MuonParticle>::const_iterator mu = muonsHandle->begin(); mu != muonsHandle->end(); mu++) {
        step1++;
        //        cout << step1 << "   Mu Pt is   " << mu->pt() << "   Mu eta is   " << mu->eta() << "   Mu Phi is   " << mu->phi() << endl;
        float isolation02 = 0;
        float isolation03 = 0;
        float isolation04 = 0;
        for (SortedCollection < CaloTower, edm::StrictWeakOrdering < CaloTower >> ::const_iterator tower = CaloTowerHandle->begin(); tower != CaloTowerHandle->end(); tower++) {
            if (t.dR2(tower->eta(), tower->phi(), mu->eta(), mu->phi()) < 0.2) isolation02 += tower->pt();
            if (t.dR2(tower->eta(), tower->phi(), mu->eta(), mu->phi()) < 0.3) isolation03 += tower->pt();
            if (t.dR2(tower->eta(), tower->phi(), mu->eta(), mu->phi()) < 0.4) isolation04 += tower->pt();

        }
        //        cout << "isolation02   " << isolation02 << endl;
        //        cout << "isolation03   " << isolation03 << endl;
        //        cout << "isolation04   " << isolation04 << endl;

    }

    Handle<pat::TauCollection> pftausHandle;
    iEvent.getByLabel("selectedTaus", pftausHandle);
    const TauCollection &pftau = *(pftausHandle.product());
    pat::TauCollection::const_iterator ipftau = pftau.begin();
    pat::TauCollection::const_iterator jpftau = pftau.end();


    ////////////////////////////////////////////////////////////////////////////////
    //  For efficiency measurement
    ////////////////////////////////////////////////////////////////////////////////
    //    bool thereIsAGoodTau = false;
    for (; ipftau != jpftau; ++ipftau) {
        if (ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits") > 0.5 && ipftau->tauID("againstMuonTight") > 0.5 && ipftau->tauID("againstElectronLoose") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent, iSetup)) {
            //            thereIsAGoodTau = true;
            offLineTau->Fill(ipftau->pt());

            for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {
                if (matchToGenTau(tau->eta(), tau->phi(), iEvent, iSetup)) {
                    l1extraParticles->Fill(ipftau->pt());
                    //                    t.plotFill("XXXXX", 10, 100, 0, 100, 1);
                }
            }


            for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
                if (matchToGenTau(ucttau->eta(), ucttau->phi(), iEvent, iSetup))
                    RelaxedTauUnpacked->Fill(ipftau->pt());
            }

            for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {
                if (matchToGenTau(uctIsotau->eta(), uctIsotau->phi(), iEvent, iSetup))
                    IsolatedTauUnpacked->Fill(ipftau->pt());
            }

        }

    }



    ////////////////////////////////////////////////////////////////////////////////
    //  For efficiency turn On curve
    ////////////////////////////////////////////////////////////////////////////////
    for (; ipftau != jpftau; ++ipftau) {
        if (ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits") > 0.5 && ipftau->tauID("againstMuonTight") > 0.5 && ipftau->tauID("againstElectronLoose") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent, iSetup)) {
            for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {
                for (int ii = 0; ii < 100; ii++) {
                    if (tau->pt() > ii) eff_denum_L1Tau->Fill(ii);
                    if (tau->pt() > ii && dR2(tau->eta(), tau->phi(), ipftau->eta(), ipftau->phi())) eff_num_L1Tau->Fill(ii);
                }
            }
        }
    }
    //    for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
    //        rate_UCTCandidate->Fill(ii);
    //        if (ucttau->pt() > ii)
    //                rate_after_UCTCandidate->Fill(ii);
    //        }
    //
    //    for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {
    //        rate_UCTCandidateIso->Fill(ii);
    //        if (uctIsotau->pt() > ii)
    //                rate_after_UCTCandidateIso->Fill(ii);
    //        }


}









//define this as a plug-in
DEFINE_FWK_MODULE(Efficiency_L1Mu);
