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
#include "TH1.h"
#include "makeHisto.h"

//
// class declaration
//

class Efficiency_L1Mu : public edm::EDAnalyzer {
public:
    explicit Efficiency_L1Mu(const edm::ParameterSet&);
    ~Efficiency_L1Mu();

    //    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);


    TH1D *demohisto;


    edm::InputTag srcGenParticle_;
    edm::InputTag L1TauSource_;
    edm::InputTag L1MuSource_;
    edm::InputTag srcHLTCaloTowers_;
    edm::InputTag srcL1UpgradeTaus_;
    edm::InputTag srcL1UpgradeIsoTaus_;

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
    myMap1 = new std::map<std::string, TH1F*>();

    demohisto = fs->make<TH1D > ("demo", "demo", 50, 0, 50);



    srcGenParticle_ = iConfig.getParameter<edm::InputTag > ("srcGenParticle");
    L1MuSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Mus");
    L1TauSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Taus");
    srcHLTCaloTowers_ = iConfig.getParameter<edm::InputTag > ("srcHLTCaloTowers");
    srcL1UpgradeTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeTaus");
    srcL1UpgradeIsoTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeIsoTaus");
}

Efficiency_L1Mu::~Efficiency_L1Mu() {

    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();

    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

bool matchToGenTau(float ieta, float iphi, const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;
    using reco::GenParticle;


    Handle < reco::GenParticleCollection> genTausHandle;
    iEvent.getByLabel("srcGenParticle_", genTausHandle);


    bool dR05 = false;
    for (reco::GenParticleCollection::const_iterator genPar = genTausHandle->begin(); genPar != genTausHandle->end(); genPar++) {
        if (genPar->pdgId() == 15 && dR2(genPar->eta(), genPar->phi(), ieta, iphi) < 0.5)
            dR05 = true;
    }
    return dR05;
}

bool matchToOfflineTausEff(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
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
        if (matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent, iSetup) && ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits") > 0.5 && ipftau->tauID("againstMuonTight") > 0.5 && ipftau->tauID("againstElectronLoose") > 0.5)
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
        cout << step1 << "   Mu Pt is   " << mu->pt() << "   Mu eta is   " << mu->eta() << "   Mu Phi is   " << mu->phi() << endl;
        float isolation02 = 0;
        float isolation03 = 0;
        float isolation04 = 0;
        for (SortedCollection < CaloTower, edm::StrictWeakOrdering < CaloTower >> ::const_iterator tower = CaloTowerHandle->begin(); tower != CaloTowerHandle->end(); tower++) {
            if (dR2(tower->eta(), tower->phi(), mu->eta(), mu->phi()) < 0.2) isolation02 += tower->pt();
            if (dR2(tower->eta(), tower->phi(), mu->eta(), mu->phi()) < 0.3) isolation03 += tower->pt();
            if (dR2(tower->eta(), tower->phi(), mu->eta(), mu->phi()) < 0.4) isolation04 += tower->pt();

        }
        cout << "isolation02   " << isolation02 << endl;
        cout << "isolation03   " << isolation03 << endl;
        cout << "isolation04   " << isolation04 << endl;


        bool PassTau = false;
        for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {

            if (tau->pt() > 20) PassTau = true;


        }

        bool PassuctTau = false;
        for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {

            if (ucttau->pt() > 20) PassuctTau = true;
        }
        bool PassuctIsoTau = false;
        for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {

            if (uctIsotau->pt() > 20) PassuctIsoTau = true;
        }




    }
    //    Histo_Denumerator->Fill(step1);
    plotFill("XXX", 6, 10, 0, 10);





}



//define this as a plug-in
DEFINE_FWK_MODULE(Efficiency_L1Mu);
