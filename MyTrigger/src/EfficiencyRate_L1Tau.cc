// -*- C++ -*-
//
// Package:    EfficiencyRate_L1Tau
// Class:      EfficiencyRate_L1Tau
//
/**\class EfficiencyRate_L1Tau EfficiencyRate_L1Tau.cc TauTrigger2014/EfficiencyRate_L1Tau/src/EfficiencyRate_L1Tau.cc

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

class EfficiencyRate_L1Tau : public edm::EDAnalyzer {
public:
    explicit EfficiencyRate_L1Tau(const edm::ParameterSet&);
    ~EfficiencyRate_L1Tau();
    MyTools tool;

    //    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual bool matchToGenTau(float ieta, float iphi, const edm::Event&);
    //    virtual bool matchToElectron(float ieta, float iphi, const edm::Event&);
    //    virtual std::vector<reco::Candidate::LorentzVector> getUCTCandidateP4s(const vector < UCTCandidate >& , int );

    TH1D *offLineTauROC;
    TH1D *l1extraParticlesROC;
    TH1D *RelaxedTauUnpackedROC;
    TH1D *RelaxedTauUnpackedROC4x4;
    TH1D *IsolatedTauUnpackedROC;
    TH1D *IsolatedTauUnpackedROC4x4;

    TH1D *offLineTauEff;
    TH1D *l1extraParticlesEff;
    TH1D *RelaxedTauUnpackedEff;
    TH1D *IsolatedTauUnpackedEff;

    TH1D * rate_L1JetParticle;
    TH1D * rate_UCTCandidateIso;
    TH1D * rate_UCTCandidate;
    TH1D * rate_UCTCandidateIso4x4;
    TH1D * rate_UCTCandidate4x4;

    TH1D * ResponseL1ExtraJet_0;
    TH1D * ResponseL1ExtraTau_0;
    TH1D * ResponseRelaxedTau_0;
    TH1D * ResponseRelaxedIsoTau_0;
    TH1D * ResponseRelaxedTau_0_40GeV;
    TH1D * ResponseRelaxedIsoTau_0_40GeV;
    TH1D * ResponseL1ExtraJet_1;
    TH1D * ResponseL1ExtraTau_1;
    TH1D * ResponseRelaxedTau_1;
    TH1D * ResponseRelaxedIsoTau_1;
    TH1D * ResponseRelaxedTau_1_40GeV;
    TH1D * ResponseRelaxedIsoTau_1_40GeV;
    TH1D * ResponseL1ExtraJet_10;
    TH1D * ResponseL1ExtraTau_10;
    TH1D * ResponseRelaxedTau_10;
    TH1D * ResponseRelaxedIsoTau_10;
    TH1D * ResponseRelaxedTau_10_40GeV;
    TH1D * ResponseRelaxedIsoTau_10_40GeV;

    TH1D * tauPT;

    TH2D * Eff2D_Num_l1extraParticles;
    TH2D * Eff2D_Num_RelaxedTauUnpacked;
    TH2D * Eff2D_Num_RelaxedTauUnpacked4x4;
    TH2D * Eff2D_Num_IsolatedTauUnpacked;
    TH2D * Eff2D_Num_IsolatedTauUnpacked4x4;

    edm::InputTag srcGenParticle_;
    edm::InputTag L1TauSource_;
    edm::InputTag L1JetSource_;
    edm::InputTag L1MuSource_;
    edm::InputTag srcL1IsoElectron_;
    edm::InputTag srcL1NonIsoElectron_;
    edm::InputTag srcHLTCaloTowers_;
    edm::InputTag srcL1UpgradeTaus_;
    edm::InputTag srcL1UpgradeIsoTaus_;
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

EfficiencyRate_L1Tau::EfficiencyRate_L1Tau(const edm::ParameterSet& iConfig) {
    //now do what ever initialization is needed
    using namespace edm;
    edm::Service<TFileService> fs;
    myMap1__ = new std::map<std::string, TH1F*>();


    offLineTauROC = fs->make<TH1D > ("offLineTauROC", "", 200, 0, 200);
    l1extraParticlesROC = fs->make<TH1D > ("l1extraParticlesROC", "", 200, 0, 200);
    RelaxedTauUnpackedROC = fs->make<TH1D > ("RelaxedTauUnpackedROC", "", 200, 0, 200);
    RelaxedTauUnpackedROC4x4 = fs->make<TH1D > ("RelaxedTauUnpackedROC4x4", "", 200, 0, 200);
    IsolatedTauUnpackedROC = fs->make<TH1D > ("IsolatedTauUnpackedROC", "", 200, 0, 200);
    IsolatedTauUnpackedROC4x4 = fs->make<TH1D > ("IsolatedTauUnpackedROC4x4", "", 200, 0, 200);

    offLineTauEff = fs->make<TH1D > ("offLineTauEff", "", 200, 0, 200);
    l1extraParticlesEff = fs->make<TH1D > ("l1extraParticlesEff", "", 200, 0, 200);
    RelaxedTauUnpackedEff = fs->make<TH1D > ("RelaxedTauUnpackedEff", "", 200, 0, 200);
    IsolatedTauUnpackedEff = fs->make<TH1D > ("IsolatedTauUnpackedEff", "", 200, 0, 200);

    rate_L1JetParticle = fs->make<TH1D > ("rate_L1JetParticle", "", 200, 0, 200);
    rate_UCTCandidateIso = fs->make<TH1D > ("rate_UCTCandidateIso", "", 200, 0, 200);
    rate_UCTCandidate = fs->make<TH1D > ("rate_UCTCandidate", "", 200, 0, 200);
    rate_UCTCandidateIso4x4 = fs->make<TH1D > ("rate_UCTCandidateIso4x4", "", 200, 0, 200);
    rate_UCTCandidate4x4 = fs->make<TH1D > ("rate_UCTCandidate4x4", "", 200, 0, 200);

    ResponseL1ExtraJet_0 = fs->make<TH1D > ("ResponseL1ExtraJet_0", "", 200, 0, 10);
    ResponseL1ExtraTau_0 = fs->make<TH1D > ("ResponseL1ExtraTau_0", "", 200, 0, 10);
    ResponseRelaxedTau_0 = fs->make<TH1D > ("ResponseRelaxedTau_0", "", 200, 0, 10);
    ResponseRelaxedIsoTau_0 = fs->make<TH1D > ("ResponseRelaxedIsoTau_0", "", 200, 0, 10);
    ResponseRelaxedTau_0_40GeV = fs->make<TH1D > ("ResponseRelaxedTau_0_40GeV", "", 200, 0, 10);
    ResponseRelaxedIsoTau_0_40GeV = fs->make<TH1D > ("ResponseRelaxedIsoTau_0_40GeV", "", 200, 0, 10);
    ResponseL1ExtraJet_1 = fs->make<TH1D > ("ResponseL1ExtraJet_1", "", 200, 0, 10);
    ResponseL1ExtraTau_1 = fs->make<TH1D > ("ResponseL1ExtraTau_1", "", 200, 0, 10);
    ResponseRelaxedTau_1 = fs->make<TH1D > ("ResponseRelaxedTau_1", "", 200, 0, 10);
    ResponseRelaxedIsoTau_1 = fs->make<TH1D > ("ResponseRelaxedIsoTau_1", "", 200, 0, 10);
    ResponseRelaxedTau_1_40GeV = fs->make<TH1D > ("ResponseRelaxedTau_1_40GeV", "", 200, 0, 10);
    ResponseRelaxedIsoTau_1_40GeV = fs->make<TH1D > ("ResponseRelaxedIsoTau_1_40GeV", "", 200, 0, 10);
    ResponseL1ExtraJet_10 = fs->make<TH1D > ("ResponseL1ExtraJet_10", "", 200, 0, 10);
    ResponseL1ExtraTau_10 = fs->make<TH1D > ("ResponseL1ExtraTau_10", "", 200, 0, 10);
    ResponseRelaxedTau_10 = fs->make<TH1D > ("ResponseRelaxedTau_10", "", 200, 0, 10);
    ResponseRelaxedIsoTau_10 = fs->make<TH1D > ("ResponseRelaxedIsoTau_10", "", 200, 0, 10);
    ResponseRelaxedTau_10_40GeV = fs->make<TH1D > ("ResponseRelaxedTau_10_40GeV", "", 200, 0, 10);
    ResponseRelaxedIsoTau_10_40GeV = fs->make<TH1D > ("ResponseRelaxedIsoTau_10_40GeV", "", 200, 0, 10);

    Eff2D_Num_l1extraParticles = fs->make<TH2D > ("Eff2D_Num_l1extraParticles", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_RelaxedTauUnpacked = fs->make<TH2D > ("Eff2D_Num_RelaxedTauUnpacked", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_RelaxedTauUnpacked4x4 = fs->make<TH2D > ("Eff2D_Num_RelaxedTauUnpacked4x4", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTauUnpacked = fs->make<TH2D > ("Eff2D_Num_IsolatedTauUnpacked", "", 200, 0, 200, 200, 0, 200);
    Eff2D_Num_IsolatedTauUnpacked4x4 = fs->make<TH2D > ("Eff2D_Num_IsolatedTauUnpacked4x4", "", 200, 0, 200, 200, 0, 200);

    //    tauPT = fs->make<TH1D > ("tauPT", "", 200, 0, 200);
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
    srcIsData_ = iConfig.getParameter<bool>("srcIsData");
}

EfficiencyRate_L1Tau::~EfficiencyRate_L1Tau() {

    //    map<string, TH1F*>::const_iterator iMap1 = myMap1__->begin();
    //    map<string, TH1F*>::const_iterator jMap1 = myMap1__->end();


    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

//bool EfficiencyRate_L1Tau::matchToElectron(float ieta, float iphi, const edm::Event& iEvent) {
//    using namespace std;
//    using namespace edm;
//
//    Handle < vector < l1extra::L1EmParticle >> IsoElectronHandle;
//    iEvent.getByLabel(srcL1IsoElectron_, IsoElectronHandle);
//
//    Handle < vector < l1extra::L1EmParticle >> NonIsoElectronHandle;
//    iEvent.getByLabel(srcL1NonIsoElectron_, NonIsoElectronHandle);
//
//
//    bool dR03Iso = false;
//    bool dR03NonIso = false;
//    int numEle = 0;
//    for (vector<l1extra::L1EmParticle>::const_iterator isoele = IsoElectronHandle->begin(); isoele != IsoElectronHandle->end(); isoele++) {
//        if (isoele->pt() > 12 && tool.dR2(isoele->eta(), isoele->phi(), ieta, iphi) < 0.3) {
//            dR03Iso = true;
//            numEle++;
//            //            break;
//        }
//    }
//    for (vector<l1extra::L1EmParticle>::const_iterator isoNele = NonIsoElectronHandle->begin(); isoNele != NonIsoElectronHandle->end(); isoNele++) {
//        if (isoNele->pt() > 12 && tool.dR2(isoNele->eta(), isoNele->phi(), ieta, iphi) < 0.3) {
//            dR03NonIso = true;
//            numEle++;
//            //            break;
//        }
//    }
//    NumEle->Fill(numEle);
//    return (!(dR03Iso || dR03NonIso));
//
//}

bool EfficiencyRate_L1Tau::matchToGenTau(float ieta, float iphi, const edm::Event& iEvent) {
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

void EfficiencyRate_L1Tau::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {




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
    iEvent.getByLabel(srcL1UpgradeTaus_, tausUpgradeHandle);

    Handle < vector < UCTCandidate >> tausUpgradeIsoHandle;
    iEvent.getByLabel(srcL1UpgradeIsoTaus_, tausUpgradeIsoHandle);

    Handle<pat::TauCollection> pftausHandle;
    iEvent.getByLabel("selectedTaus", pftausHandle);


    Handle < vector < l1extra::L1EmParticle >> IsoElectronHandle;
    iEvent.getByLabel(srcL1IsoElectron_, IsoElectronHandle);

    Handle < vector < l1extra::L1EmParticle >> NonIsoElectronHandle;
    iEvent.getByLabel(srcL1NonIsoElectron_, NonIsoElectronHandle);

    vector<float> vectL1Extra;
    vectL1Extra.clear();


    ////////////////////////////////////////////////////////////////////////////////
    //  For efficiency measurement
    ////////////////////////////////////////////////////////////////////////////////
    if (!srcIsData_) {
        int numGoodRecoTau = 0;
        for (pat::TauCollection::const_iterator ipftau = pftausHandle->begin(); ipftau != pftausHandle->end(); ipftau++) {
            //            if (ipftau->pt() > 45 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && ipftau->tauID("againstMuonLoose") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent)) {
            //            tauPT->Fill(ipftau->tauID("byLooseCombinedIsolationDeltaBetaCorr"));
            if (ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent)) {
                numGoodRecoTau++;
            }
        }
        if (numGoodRecoTau > 1) {
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
                        if (matchToGenTau(tau->eta(), tau->phi(), iEvent)) {
                            l1extraParticlesEff->Fill(ipftau->pt());
                            l1extraParticlesROC->Fill(tau->pt());
                            ValuePtTau = tau->pt();
                            break;
                        }
                    }
                    for (vector<l1extra::L1JetParticle>::const_iterator jet = jetsHandle->begin(); jet != jetsHandle->end(); jet++) {
                        if (matchToGenTau(jet->eta(), jet->phi(), iEvent)) {
                            l1extraParticlesEff->Fill(ipftau->pt());
                            l1extraParticlesROC->Fill(jet->pt() - 20);
                            ValuePtJet = jet->pt() - 20;
                            break;
                        }
                    }
                    if (ValuePtTau || ValuePtJet) {
                        if (ValuePtTau > ValuePtJet) {
                            Eff2D_Num_l1extraParticles->Fill(ipftau->pt(), ValuePtTau);
                            if (ipftau->decayMode() == 0) ResponseL1ExtraTau_0->Fill(ValuePtTau / ipftau->pt());
                            if (ipftau->decayMode() == 1) ResponseL1ExtraTau_1->Fill(ValuePtTau / ipftau->pt());
                            if (ipftau->decayMode() == 10) ResponseL1ExtraTau_10->Fill(ValuePtTau / ipftau->pt());
                        } else {
                            Eff2D_Num_l1extraParticles->Fill(ipftau->pt(), ValuePtJet);
                            if (ipftau->decayMode() == 0) ResponseL1ExtraJet_0->Fill(ValuePtJet / ipftau->pt());
                            if (ipftau->decayMode() == 1) ResponseL1ExtraJet_1->Fill(ValuePtJet / ipftau->pt());
                            if (ipftau->decayMode() == 10) ResponseL1ExtraJet_10->Fill(ValuePtJet / ipftau->pt());
                        }

                    }
                    // ############################## NEW tau HLT Algorithm UST2015
                    for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
                        if (matchToGenTau(ucttau->eta(), ucttau->phi(), iEvent)) {
                            if (ipftau->decayMode() == 0) ResponseRelaxedTau_0->Fill(ucttau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 1) ResponseRelaxedTau_1->Fill(ucttau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 10) ResponseRelaxedTau_10->Fill(ucttau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 0 && ipftau->pt() > 40) ResponseRelaxedTau_0_40GeV->Fill(ucttau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 1 && ipftau->pt() > 40) ResponseRelaxedTau_1_40GeV->Fill(ucttau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 10 && ipftau->pt() > 40) ResponseRelaxedTau_10_40GeV->Fill(ucttau->pt() / ipftau->pt());
                            RelaxedTauUnpackedEff->Fill(ipftau->pt());
                            RelaxedTauUnpackedROC->Fill(ucttau->pt());
                            RelaxedTauUnpackedROC4x4->Fill(ucttau->getFloat("associatedRegionEt", -4));
                            Eff2D_Num_RelaxedTauUnpacked->Fill(ipftau->pt(), ucttau->pt());
                            Eff2D_Num_RelaxedTauUnpacked4x4->Fill(ipftau->pt(), ucttau->getFloat("associatedRegionEt", -4));
                            break;

                        }
                    }
                    for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {
                        if (matchToGenTau(uctIsotau->eta(), uctIsotau->phi(), iEvent)) {
                            if (ipftau->decayMode() == 0) ResponseRelaxedIsoTau_0->Fill(uctIsotau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 1) ResponseRelaxedIsoTau_1->Fill(uctIsotau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 10) ResponseRelaxedIsoTau_10->Fill(uctIsotau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 0 && ipftau->pt() > 40) ResponseRelaxedIsoTau_0_40GeV->Fill(uctIsotau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 1 && ipftau->pt() > 40) ResponseRelaxedIsoTau_1_40GeV->Fill(uctIsotau->pt() / ipftau->pt());
                            if (ipftau->decayMode() == 10 && ipftau->pt() > 40) ResponseRelaxedIsoTau_10_40GeV->Fill(uctIsotau->pt() / ipftau->pt());
                            IsolatedTauUnpackedEff->Fill(ipftau->pt());
                            IsolatedTauUnpackedROC->Fill(uctIsotau->pt());
                            IsolatedTauUnpackedROC4x4->Fill(uctIsotau->getFloat("associatedRegionEt", -4));
                            Eff2D_Num_IsolatedTauUnpacked->Fill(ipftau->pt(), uctIsotau->pt());
                            Eff2D_Num_IsolatedTauUnpacked4x4->Fill(ipftau->pt(), uctIsotau->getFloat("associatedRegionEt", -4));
                            break;
                        }
                    }

                }// if there is denumerator

            }//loop over OfflineTau
        }// IF there exists 2 goodRecoTau
        ////////////////////////////////////////////////////////////////////////////////
        //  For rate measurement
        ////////////////////////////////////////////////////////////////////////////////
    } else {

        float maxValPt_tau = 0;
        float maxValPt_jet = 0;
        for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {
            if (matchToGenTau(tau->eta(), tau->phi(), iEvent)) {
                maxValPt_tau = tau->pt();
                cout << "tau->pt()=" << tau->pt() << endl;
                vectL1Extra.push_back(maxValPt_tau);
            }
        }
        for (vector<l1extra::L1JetParticle>::const_iterator jet = jetsHandle->begin(); jet != jetsHandle->end(); jet++) {
            if (matchToGenTau(jet->eta(), jet->phi(), iEvent)) {
                maxValPt_jet = jet->pt();
                vectL1Extra.push_back(maxValPt_jet - 20);
            }
        }

        if (vectL1Extra.size() > 1) {
            sort(vectL1Extra.begin(), vectL1Extra.end(), SortObject_MaxPt());
            cout << "First= " << vectL1Extra[0] << "   second= " << vectL1Extra[1] << endl;
            rate_L1JetParticle->Fill(vectL1Extra[1]);
        }
        //        (maxValPt_tau > (maxValPt_jet - 20) ? rate_L1JetParticle->Fill(maxValPt_tau) : rate_L1JetParticle->Fill(maxValPt_jet - 20));


        //########################################################
        float maxValPt_ucttau = 0;
        float maxValPt_ucttau4x4 = 0;
        int l1taucount = 0;
        for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++, l1taucount++) {
            //            if (matchToElectron(ucttau->eta(), ucttau->phi(), iEvent)) {
            //           maxValPt_ucttau = ucttau->pt();
            //                maxValPt_ucttau4x4 = ucttau->getFloat("associatedRegionEt", -4);
            if (l1taucount == 2) {
                maxValPt_ucttau = ucttau->pt();
                maxValPt_ucttau4x4 = ucttau->getFloat("associatedRegionEt", -4);
            }
            //            if (ucttau->pt() > maxValPt_ucttau) maxValPt_ucttau = ucttau->pt();
            //            if (ucttau->getFloat("associatedRegionEt", -4) > maxValPt_ucttau4x4) maxValPt_ucttau4x4 = ucttau->getFloat("associatedRegionEt", -4);
            //            }

            //                        if (l1taucount > 1 && ucttau->pt()  > 20)cout << "l1taucount.size()= " << ucttau->pt() << endl;
            //            cout << "l1taucount.size()= " << ucttau->getFloat("associatedRegionEt", -4) << endl;
            //            cout << "l1taucount.size()= " << ucttau->pt() << endl;
        }
        rate_UCTCandidate->Fill(maxValPt_ucttau);
        rate_UCTCandidate4x4->Fill(maxValPt_ucttau4x4);

        //########################################################
        float maxValPt_uctIsotau = 0;
        float maxValPt_uctIsotau4x4 = 0;
        int l1Isotaucount = 0;
        for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++, l1Isotaucount++) {
            //            if (matchToElectron(uctIsotau->eta(), uctIsotau->phi(), iEvent)) {
            if (l1Isotaucount == 2) {
                maxValPt_uctIsotau = uctIsotau->pt();
                maxValPt_uctIsotau4x4 = uctIsotau->getFloat("associatedRegionEt", -4);
            }
            //            if (uctIsotau->pt() > maxValPt_uctIsotau) maxValPt_uctIsotau = uctIsotau->pt();
            //            if (uctIsotau->getFloat("associatedRegionEt", -4) > maxValPt_uctIsotau4x4) maxValPt_uctIsotau4x4 = uctIsotau->getFloat("associatedRegionEt", -4);
            //            }
        }
        rate_UCTCandidateIso->Fill(maxValPt_uctIsotau);
        rate_UCTCandidateIso4x4->Fill(maxValPt_uctIsotau4x4);
    } // end loop over rate

}

//define this as a plug-in
DEFINE_FWK_MODULE(EfficiencyRate_L1Tau);
