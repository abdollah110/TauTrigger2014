// -*- C++ -*-
//
// Package:    EfficiencyRate_L1Tau4x8
// Class:      EfficiencyRate_L1Tau4x8
//
/**\class EfficiencyRate_L1Tau4x8 EfficiencyRate_L1Tau4x8.cc TauTrigger2014/EfficiencyRate_L1Tau4x8/src/EfficiencyRate_L1Tau4x8.cc

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
#include "TLorentzVector.h"
#include <vector>
//
// class declaration
//

class EfficiencyRate_L1Tau4x8 : public edm::EDAnalyzer {
public:
    explicit EfficiencyRate_L1Tau4x8(const edm::ParameterSet&);
    ~EfficiencyRate_L1Tau4x8();
    MyTools tool;

    //    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual bool matchToGenTau(float ieta, float iphi, const edm::Event&);
    //    virtual bool matchToElectron(float ieta, float iphi, const edm::Event&);
    //    virtual std::vector<reco::Candidate::LorentzVector> getUCTCandidateP4s(const vector < UCTCandidate >& , int );

    TH1D *offLineTauROC;
    TH1D *l1extraParticlesROC;
    TH1D *RelaxedTauROC;
    TH1D *RelaxedTauROC4x4;
    TH1D *IsolatedTauROC;
    TH1D *IsolatedTauROC4x4;

    TH1D *offLineTauEff;
    TH1D *l1extraParticlesEff;
    TH1D *RelaxedTauEff;
    TH1D *IsolatedTauEff;

    TH1D * rate_L1JetParticle;
    TH1D * rate_UCTTauNoIsoNoEta;
    TH1D * rate_UCTTauNoIso;
    TH1D * rate_UCTTauIsoNoEta;
    TH1D * rate_UCTTauIso;
    TH1D * rate_UCTTauIso1p0;
    TH1D * rate_UCTTauIso0p5;
    TH1D * rate_UCTTauIso0p3;
    TH1D * rate_UCTTauIso0p25;
    TH1D * rate_UCTTauIso0p2;
    TH1D * rate_UCTTauIso0p1;



    TH1D * tauPT;

    TH2D * Eff2D_Num_l1extraParticles;
    TH2D * Eff2D_Num_RelaxedTau;
    TH2D * Eff2D_Num_IsolatedTauNoEta;
    TH2D * Eff2D_Num_IsolatedTau;
    TH2D * Eff2D_Num_IsolatedTau1p0;
    TH2D * Eff2D_Num_IsolatedTau0p5;
    TH2D * Eff2D_Num_IsolatedTau0p3;
    TH2D * Eff2D_Num_IsolatedTau0p25;
    TH2D * Eff2D_Num_IsolatedTau0p2;
    TH2D * Eff2D_Num_IsolatedTau0p1;

    edm::InputTag srcGenParticle_;
    edm::InputTag L1TauSource_;
    edm::InputTag L1JetSource_;
    edm::InputTag L1MuSource_;
    edm::InputTag srcL1IsoElectron_;
    edm::InputTag srcL1NonIsoElectron_;
    edm::InputTag srcHLTCaloTowers_;
    edm::InputTag srcL1UpgradeTaus_;
    edm::InputTag srcL1UpgradeIsoTaus_;
    edm::InputTag srcL1UpgradeTaus4x8_;
    edm::InputTag srcL1UpgradeIsoTaus4x8_;
    bool srcIsData_;


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

EfficiencyRate_L1Tau4x8::EfficiencyRate_L1Tau4x8(const edm::ParameterSet& iConfig) {
    //now do what ever initialization is needed
    using namespace edm;
    edm::Service<TFileService> fs;
    myMap1__ = new std::map<std::string, TH1F*>();


    offLineTauROC = fs->make<TH1D > ("offLineTauROC", "", 200, 0, 200);
    l1extraParticlesROC = fs->make<TH1D > ("l1extraParticlesROC", "", 200, 0, 200);
    RelaxedTauROC = fs->make<TH1D > ("RelaxedTauROC", "", 200, 0, 200);
    RelaxedTauROC4x4 = fs->make<TH1D > ("RelaxedTauROC4x4", "", 200, 0, 200);
    IsolatedTauROC = fs->make<TH1D > ("IsolatedTauROC", "", 200, 0, 200);
    IsolatedTauROC4x4 = fs->make<TH1D > ("IsolatedTauROC4x4", "", 200, 0, 200);

    offLineTauEff = fs->make<TH1D > ("offLineTauEff", "", 200, 0, 200);
    l1extraParticlesEff = fs->make<TH1D > ("l1extraParticlesEff", "", 200, 0, 200);
    RelaxedTauEff = fs->make<TH1D > ("RelaxedTauEff", "", 200, 0, 200);
    IsolatedTauEff = fs->make<TH1D > ("IsolatedTauEff", "", 200, 0, 200);

    rate_L1JetParticle = fs->make<TH1D > ("rate_L1JetParticle", "", 200, 0, 200);
    rate_UCTTauNoIsoNoEta = fs->make<TH1D > ("rate_UCTTauNoIsoNoEta", "", 200, 0, 200);
    rate_UCTTauNoIso = fs->make<TH1D > ("rate_UCTTauNoIso", "", 200, 0, 200);
    rate_UCTTauIsoNoEta = fs->make<TH1D > ("rate_UCTTauIsoNoEta", "", 200, 0, 200);
    rate_UCTTauIso = fs->make<TH1D > ("rate_UCTTauIso", "", 200, 0, 200);
    rate_UCTTauIso1p0 = fs->make<TH1D > ("rate_UCTTauIso1p0", "", 200, 0, 200);
    rate_UCTTauIso0p5 = fs->make<TH1D > ("rate_UCTTauIso0p5", "", 200, 0, 200);
    rate_UCTTauIso0p3 = fs->make<TH1D > ("rate_UCTTauIso0p3", "", 200, 0, 200);
    rate_UCTTauIso0p25 = fs->make<TH1D > ("rate_UCTTauIso0p25", "", 200, 0, 200);
    rate_UCTTauIso0p2 = fs->make<TH1D > ("rate_UCTTauIso0p2", "", 200, 0, 200);
    rate_UCTTauIso0p1 = fs->make<TH1D > ("rate_UCTTauIso0p1", "", 200, 0, 200);

    Eff2D_Num_l1extraParticles = fs->make<TH2D > ("Eff2D_Num_l1extraParticles", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_RelaxedTau = fs->make<TH2D > ("Eff2D_Num_RelaxedTau", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTauNoEta = fs->make<TH2D > ("Eff2D_Num_IsolatedTauNoEta", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTau = fs->make<TH2D > ("Eff2D_Num_IsolatedTau", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTau1p0 = fs->make<TH2D > ("Eff2D_Num_IsolatedTau1p0", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTau0p5 = fs->make<TH2D > ("Eff2D_Num_IsolatedTau0p5", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTau0p3 = fs->make<TH2D > ("Eff2D_Num_IsolatedTau0p3", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTau0p25 = fs->make<TH2D > ("Eff2D_Num_IsolatedTau0p25", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTau0p2 = fs->make<TH2D > ("Eff2D_Num_IsolatedTau0p2", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTau0p1 = fs->make<TH2D > ("Eff2D_Num_IsolatedTau0p1", "", 200, 0, 200, 200, 0, 200);

    tauPT = fs->make<TH1D > ("tauPT", "", 2, 0, 2);

    srcGenParticle_ = iConfig.getParameter<edm::InputTag > ("srcGenParticle");
    L1MuSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Mus");
    srcL1IsoElectron_ = iConfig.getParameter<edm::InputTag > ("srcL1IsoElectron");
    srcL1NonIsoElectron_ = iConfig.getParameter<edm::InputTag > ("srcL1NonIsoElectron");
    L1TauSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Taus");
    L1JetSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Jets");
    srcHLTCaloTowers_ = iConfig.getParameter<edm::InputTag > ("srcHLTCaloTowers");
    srcL1UpgradeTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeTaus");
    srcL1UpgradeIsoTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeIsoTaus");
    srcL1UpgradeTaus4x8_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeTaus4x8");
    srcL1UpgradeIsoTaus4x8_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeIsoTaus4x8");
    srcIsData_ = iConfig.getParameter<bool>("srcIsData");
}

EfficiencyRate_L1Tau4x8::~EfficiencyRate_L1Tau4x8() {

    //    map<string, TH1F*>::const_iterator iMap1 = myMap1__->begin();
    //    map<string, TH1F*>::const_iterator jMap1 = myMap1__->end();


    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}

bool EfficiencyRate_L1Tau4x8::matchToGenTau(float ieta, float iphi, const edm::Event& iEvent) {
    using namespace std;
    using namespace reco;
    using namespace edm;
    using namespace pat;
    using reco::GenParticle;


    Handle < reco::GenParticleCollection> genTausHandle;
    iEvent.getByLabel(srcGenParticle_, genTausHandle);


    bool dR03 = false;
    for (reco::GenParticleCollection::const_iterator genPar = genTausHandle->begin(); genPar != genTausHandle->end(); genPar++) {
        if (genPar->mother() != NULL && abs(genPar->mother()->pdgId()) == 15 && abs(genPar->pdgId()) != 15 && abs(genPar->pdgId()) != 11 && abs(genPar->pdgId()) != 13 && abs(genPar->pdgId()) != 12 && abs(genPar->pdgId()) != 14 && abs(genPar->pdgId()) != 16 && tool.dR2(genPar->eta(), genPar->phi(), ieta, iphi) < 0.3) {
            dR03 = true;
            break;
        }
    }
    return dR03;
}

struct SortObject_MaxPt {

    bool operator ()(float a, float b) const {
        return (a > b);
    }
};

void EfficiencyRate_L1Tau4x8::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {




    using reco::Muon;
    using reco::MuonCollection;
    using reco::RecoChargedCandidate;
    //    using reco::UCTCandidateCollection;
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

    Handle < vector < l1extra::L1JetParticle >> jetsHandle;
    iEvent.getByLabel(L1JetSource_, jetsHandle);

    Handle < vector < UCTCandidate >> tausUpgradeHandle;
    iEvent.getByLabel(srcL1UpgradeTaus4x8_, tausUpgradeHandle);

    Handle < vector < UCTCandidate >> tausUpgradeIsoHandle;
    iEvent.getByLabel(srcL1UpgradeIsoTaus4x8_, tausUpgradeIsoHandle);

    Handle<pat::TauCollection> pftausHandle;
    iEvent.getByLabel("selectedTaus", pftausHandle);


    Handle < vector < l1extra::L1EmParticle >> IsoElectronHandle;
    iEvent.getByLabel(srcL1IsoElectron_, IsoElectronHandle);

    Handle < vector < l1extra::L1EmParticle >> NonIsoElectronHandle;
    iEvent.getByLabel(srcL1NonIsoElectron_, NonIsoElectronHandle);

    //For L1 Extra
    vector<float> vectL1Extra;
    vectL1Extra.clear();

    //For UCT No Iso
    vector<float> UCTTauNOEtaNoIso;
    UCTTauNOEtaNoIso.clear();
    vector<float> UCTTauNoIso;
    UCTTauNoIso.clear();

    //For UCT Iso
    vector<float> UCTTauNoEtaIso;
    UCTTauNoEtaIso.clear();
    vector<float> UCTTauIso;
    UCTTauIso.clear();
    vector<float> UCTTauIso1p0;
    UCTTauIso1p0.clear();
    vector<float> UCTTauIso0p5;
    UCTTauIso0p5.clear();
    vector<float> UCTTauIso0p3;
    UCTTauIso0p3.clear();
    vector<float> UCTTauIso0p25;
    UCTTauIso0p25.clear();
    vector<float> UCTTauIso0p2;
    UCTTauIso0p2.clear();
    vector<float> UCTTauIso0p1;
    UCTTauIso0p1.clear();


    ////////////////////////////////////////////////////////////////////////////////
    //  For efficiency measurement
    ////////////////////////////////////////////////////////////////////////////////
    if (!srcIsData_) {
        int numGoodRecoTau = 1;
        //        for (pat::TauCollection::const_iterator ipftau = pftausHandle->begin(); ipftau != pftausHandle->end(); ipftau++) {
        //            //            if (ipftau->pt() > 45 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonLoose") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent)) {
        //            //            tauPT->Fill(ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr"));
        //            if (ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent)) {
        //                numGoodRecoTau++;
        //            }
        //        }
        //        if (numGoodRecoTau > 1) {
        if (numGoodRecoTau > 0) { //for debugging
            for (pat::TauCollection::const_iterator ipftau = pftausHandle->begin(); ipftau != pftausHandle->end(); ipftau++) {
                //                if (ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonLoose") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent)) {
                if (ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent)) {
                    //                    cout << "decayMode() is " << ipftau->decayMode() << endl;
                    offLineTauEff->Fill(ipftau->pt());
                    offLineTauROC->Fill(ipftau->pt());
                    // ############################## OLD tau HLT Algorithm
                    float ValuePtTau = 0;
                    float ValuePtJet = 0;
                    for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {
                        if (tool.dR2(ipftau->eta(), ipftau->phi(), tau->eta(), tau->phi()) < 0.3) {
                            l1extraParticlesEff->Fill(ipftau->pt());
                            l1extraParticlesROC->Fill(tau->pt());
                            ValuePtTau = tau->pt();
                            //                            break;
                        }
                    }
                    for (vector<l1extra::L1JetParticle>::const_iterator jet = jetsHandle->begin(); jet != jetsHandle->end(); jet++) {
                        if (tool.dR2(ipftau->eta(), ipftau->phi(), jet->eta(), jet->phi()) < 0.3) {
                            l1extraParticlesEff->Fill(ipftau->pt());
                            l1extraParticlesROC->Fill(jet->pt() - 20);
                            ValuePtJet = jet->pt() - 20;
                            //                            break;
                        }
                    }
                    if (ValuePtTau || ValuePtJet) {
                        if (ValuePtTau > ValuePtJet) {
                            Eff2D_Num_l1extraParticles->Fill(ipftau->pt(), ValuePtTau);
                        } else {
                            Eff2D_Num_l1extraParticles->Fill(ipftau->pt(), ValuePtJet);
                        }

                    }
                    // ############################## NEW tau HLT Algorithm UCT2015
                    for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
                        if (tool.dR2(ipftau->eta(), ipftau->phi(), ucttau->eta(), ucttau->phi()) < 0.3) {
                            RelaxedTauEff->Fill(ipftau->pt());
                            RelaxedTauROC->Fill(ucttau->pt());
                            cout << "tau Veto bit for ucttau is = " << ucttau->getInt("associated4x4Tau", -4) << endl;
                            Eff2D_Num_RelaxedTau->Fill(ipftau->pt(), ucttau->pt());
                            //                            break;

                        }
                    }
                    for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {
                        if (tool.dR2(ipftau->eta(), ipftau->phi(), uctIsotau->eta(), uctIsotau->phi()) < 0.3) {
                            float jetEt = uctIsotau->getFloat("associatedJetPt", -4);
                            float tauEt = uctIsotau->getFloat("associatedRegionEt", -4);
                            cout << "tau Veto bit for uctIsotau is = " << uctIsotau->getInt("associated4x4Tau", -4) << endl;
                            float tauIso = (jetEt - tauEt) / tauEt;
                            IsolatedTauEff->Fill(ipftau->pt());
                            IsolatedTauROC->Fill(uctIsotau->pt());
                            Eff2D_Num_IsolatedTauNoEta->Fill(ipftau->pt(), uctIsotau->pt());
                            if (fabs(uctIsotau->eta()) < 2.17) Eff2D_Num_IsolatedTau->Fill(ipftau->pt(), uctIsotau->pt());
                            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 1.0) Eff2D_Num_IsolatedTau1p0->Fill(ipftau->pt(), uctIsotau->pt());
                            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.5) Eff2D_Num_IsolatedTau0p5->Fill(ipftau->pt(), uctIsotau->pt());
                            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.3) Eff2D_Num_IsolatedTau0p3->Fill(ipftau->pt(), uctIsotau->pt());
                            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.25) Eff2D_Num_IsolatedTau0p25->Fill(ipftau->pt(), uctIsotau->pt());
                            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.2) Eff2D_Num_IsolatedTau0p2->Fill(ipftau->pt(), uctIsotau->pt());
                            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.1) Eff2D_Num_IsolatedTau0p1->Fill(ipftau->pt(), uctIsotau->pt());
                            //                            break;
                        }
                    }

                }// if there is denumerator

            }//loop over OfflineTau
        }// IF there exists 2 goodRecoTau
        ////////////////////////////////////////////////////////////////////////////////
        //  For rate measurement
        ////////////////////////////////////////////////////////////////////////////////
    } else {

        for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {
            vectL1Extra.push_back(tau->pt());
        }
        for (vector<l1extra::L1JetParticle>::const_iterator jet = jetsHandle->begin(); jet != jetsHandle->end(); jet++) {
            vectL1Extra.push_back(jet->pt() - 20);
        }

        if (vectL1Extra.size() > 1) {
            sort(vectL1Extra.begin(), vectL1Extra.end(), SortObject_MaxPt());
            rate_L1JetParticle->Fill(vectL1Extra[1]);
        }

        //########################################################
        for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {

            UCTTauNOEtaNoIso.push_back(ucttau->pt());
            if (fabs(ucttau->eta()) < 2.17) UCTTauNoIso.push_back(ucttau->pt());
        }

        if (UCTTauNOEtaNoIso.size() > 1) {
            sort(UCTTauNOEtaNoIso.begin(), UCTTauNOEtaNoIso.end(), SortObject_MaxPt());
            rate_UCTTauNoIsoNoEta->Fill(UCTTauNOEtaNoIso[1]);
        }

        if (UCTTauNoIso.size() > 1) {
            sort(UCTTauNoIso.begin(), UCTTauNoIso.end(), SortObject_MaxPt());
            rate_UCTTauNoIso->Fill(UCTTauNoIso[1]);
        }
        //########################################################
        for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {

            float jetEt = uctIsotau->getFloat("associatedJetPt", -4);
            float tauEt = uctIsotau->getFloat("associatedRegionEt", -4);
            float tauIso = (jetEt - tauEt) / tauEt;

            UCTTauNoEtaIso.push_back(uctIsotau->pt());
            if (fabs(uctIsotau->eta()) < 2.17) UCTTauIso.push_back(uctIsotau->pt());
            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 1.0) UCTTauIso1p0.push_back(uctIsotau->pt());
            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.5) UCTTauIso0p5.push_back(uctIsotau->pt());
            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.3) UCTTauIso0p3.push_back(uctIsotau->pt());
            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.25) UCTTauIso0p25.push_back(uctIsotau->pt());
            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.2) UCTTauIso0p2.push_back(uctIsotau->pt());
            if (fabs(uctIsotau->eta()) < 2.17 && tauIso < 0.1) UCTTauIso0p1.push_back(uctIsotau->pt());

        }

        if (UCTTauNoEtaIso.size() > 1) {
            sort(UCTTauNoEtaIso.begin(), UCTTauNoEtaIso.end(), SortObject_MaxPt());
            rate_UCTTauIsoNoEta->Fill(UCTTauNoEtaIso[1]);
        }
        if (UCTTauIso.size() > 1) {
            sort(UCTTauIso.begin(), UCTTauIso.end(), SortObject_MaxPt());
            rate_UCTTauIso->Fill(UCTTauIso[1]);
        }
        if (UCTTauIso1p0.size() > 1) {
            sort(UCTTauIso1p0.begin(), UCTTauIso1p0.end(), SortObject_MaxPt());
            rate_UCTTauIso1p0->Fill(UCTTauIso1p0[1]);
        }
        if (UCTTauIso0p5.size() > 1) {
            sort(UCTTauIso0p5.begin(), UCTTauIso0p5.end(), SortObject_MaxPt());
            rate_UCTTauIso0p5->Fill(UCTTauIso0p5[1]);
        }
        if (UCTTauIso0p3.size() > 1) {
            sort(UCTTauIso0p3.begin(), UCTTauIso0p3.end(), SortObject_MaxPt());
            rate_UCTTauIso0p3->Fill(UCTTauIso0p3[1]);
        }
        if (UCTTauIso0p25.size() > 1) {
            sort(UCTTauIso0p25.begin(), UCTTauIso0p25.end(), SortObject_MaxPt());
            rate_UCTTauIso0p25->Fill(UCTTauIso0p25[1]);
        }
        if (UCTTauIso0p2.size() > 1) {
            sort(UCTTauIso0p2.begin(), UCTTauIso0p2.end(), SortObject_MaxPt());
            rate_UCTTauIso0p2->Fill(UCTTauIso0p2[1]);
        }

        if (UCTTauIso0p1.size() > 1) {
            sort(UCTTauIso0p1.begin(), UCTTauIso0p1.end(), SortObject_MaxPt());
            rate_UCTTauIso0p1->Fill(UCTTauIso0p1[1]);
        }
    } // end loop over rate

}

//define this as a plug-in
DEFINE_FWK_MODULE(EfficiencyRate_L1Tau4x8);
