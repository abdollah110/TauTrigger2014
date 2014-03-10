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
#include "TLorentzVector.h"

//
// class declaration
//

class Efficiency_L1Mu : public edm::EDAnalyzer {
public:
    explicit Efficiency_L1Mu(const edm::ParameterSet&);
    ~Efficiency_L1Mu();
    MyTools tool;

    //    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual bool matchToGenTau(float ieta, float iphi, const edm::Event&);
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

    edm::InputTag srcGenParticle_;
    edm::InputTag L1TauSource_;
    edm::InputTag L1JetSource_;
    edm::InputTag L1MuSource_;
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

Efficiency_L1Mu::Efficiency_L1Mu(const edm::ParameterSet& iConfig) {
    //now do what ever initialization is needed
    using namespace edm;
    edm::Service<TFileService> fs;
    myMap1__ = new std::map<std::string, TH1F*>();


    offLineTauROC = fs->make<TH1D > ("offLineTauROC", "", 100, 0, 100);
    l1extraParticlesROC = fs->make<TH1D > ("l1extraParticlesROC", "", 100, 0, 100);
    RelaxedTauUnpackedROC = fs->make<TH1D > ("RelaxedTauUnpackedROC", "", 100, 0, 100);
    RelaxedTauUnpackedROC4x4 = fs->make<TH1D > ("RelaxedTauUnpackedROC4x4", "", 100, 0, 100);
    IsolatedTauUnpackedROC = fs->make<TH1D > ("IsolatedTauUnpackedROC", "", 100, 0, 100);
    IsolatedTauUnpackedROC4x4 = fs->make<TH1D > ("IsolatedTauUnpackedROC4x4", "", 100, 0, 100);

    offLineTauEff = fs->make<TH1D > ("offLineTauEff", "", 100, 0, 100);
    l1extraParticlesEff = fs->make<TH1D > ("l1extraParticlesEff", "", 100, 0, 100);
    RelaxedTauUnpackedEff = fs->make<TH1D > ("RelaxedTauUnpackedEff", "", 100, 0, 100);
    IsolatedTauUnpackedEff = fs->make<TH1D > ("IsolatedTauUnpackedEff", "", 100, 0, 100);

    rate_L1JetParticle = fs->make<TH1D > ("rate_L1JetParticle", "", 100, 0, 100);
    rate_UCTCandidateIso = fs->make<TH1D > ("rate_UCTCandidateIso", "", 100, 0, 100);
    rate_UCTCandidate = fs->make<TH1D > ("rate_UCTCandidate", "", 100, 0, 100);


    srcGenParticle_ = iConfig.getParameter<edm::InputTag > ("srcGenParticle");
    L1MuSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Mus");
    L1TauSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Taus");
    L1JetSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Jets");
    srcHLTCaloTowers_ = iConfig.getParameter<edm::InputTag > ("srcHLTCaloTowers");
    srcL1UpgradeTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeTaus");
    srcL1UpgradeIsoTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeIsoTaus");
    srcIsData_ = iConfig.getParameter<bool>("srcIsData");
}

Efficiency_L1Mu::~Efficiency_L1Mu() {

    //    map<string, TH1F*>::const_iterator iMap1 = myMap1__->begin();
    //    map<string, TH1F*>::const_iterator jMap1 = myMap1__->end();


    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

bool Efficiency_L1Mu::matchToGenTau(float ieta, float iphi, const edm::Event& iEvent) {
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

//std::vector<reco::Candidate::LorentzVector> Efficiency_L1Mu::getUCTCandidateP4s(const vector < UCTCandidate >& uctCandidates, int mode) {
//    std::vector<reco::Candidate::LorentzVector> uctCandidateP4s;
//    for (vector < UCTCandidate >::const_iterator uctCandidate = uctCandidates.begin();
//            uctCandidate != uctCandidates.end(); ++uctCandidate) {
////        if (mode == k2x1) uctCandidateP4s.push_back(uctCandidate->p4());
////        else if (mode == k4x4) uctCandidateP4s.push_back(getScaledP4(uctCandidate->p4(), uctCandidate->getFloat("associatedRegionEt", -4), uctCandidate->et()));
////        else if (mode == k12x12) uctCandidateP4s.push_back(getScaledP4(uctCandidate->p4(), uctCandidate->getFloat("associatedJetPt", -4), uctCandidate->et()));
//        else assert(0);
//    }
//    return uctCandidateP4s;
//}
// ------------ method called for each event  ------------

void
Efficiency_L1Mu::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
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



    // Different for Muon Isolation
    //    for (vector<l1extra::L1MuonParticle>::const_iterator mu = muonsHandle->begin(); mu != muonsHandle->end(); mu++) {
    //        float isolation02 = 0;
    //        float isolation03 = 0;
    //        float isolation04 = 0;
    //        for (SortedCollection < CaloTower, edm::StrictWeakOrdering < CaloTower >> ::const_iterator tower = CaloTowerHandle->begin(); tower != CaloTowerHandle->end(); tower++) {
    //            if (tool.dR2(tower->eta(), tower->phi(), mu->eta(), mu->phi()) < 0.2) isolation02 += tower->pt();
    //            if (tool.dR2(tower->eta(), tower->phi(), mu->eta(), mu->phi()) < 0.3) isolation03 += tower->pt();
    //            if (tool.dR2(tower->eta(), tower->phi(), mu->eta(), mu->phi()) < 0.4) isolation04 += tower->pt();
    //
    //        }
    //    }


    ////////////////////////////////////////////////////////////////////////////////
    //  For efficiency measurement
    ////////////////////////////////////////////////////////////////////////////////
    if (srcIsData_) {
        for (pat::TauCollection::const_iterator ipftau = pftausHandle->begin(); ipftau != pftausHandle->end(); ipftau++) {
            if (ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits") > 0.5 && ipftau->tauID("againstMuonTight") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent)) {
                offLineTauEff->Fill(ipftau->pt());
                offLineTauROC->Fill(ipftau->pt());
                // ############################## OLD tau HLT Algorithm
                bool hasPassedL1Tau = false;
                for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {
                    if (matchToGenTau(tau->eta(), tau->phi(), iEvent)) {
                        hasPassedL1Tau = true;
                        l1extraParticlesEff->Fill(ipftau->pt());
                        l1extraParticlesROC->Fill(tau->pt());
                        break;
                    }
                }
                if (!hasPassedL1Tau) { // Here we add OR between L1Tau and L1Jet
                    for (vector<l1extra::L1JetParticle>::const_iterator jet = jetsHandle->begin(); jet != jetsHandle->end(); jet++) {
                        if (matchToGenTau(jet->eta(), jet->phi(), iEvent)) {
                            l1extraParticlesEff->Fill(ipftau->pt());
                            l1extraParticlesROC->Fill(jet->pt());
                            break;
                        }
                    }
                }
                // ############################## NEW tau HLT Algorithm UST2015
                for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
                    //                cout << "2x1=" << ucttau->et() << "   4x4=" << ucttau->getFloat("associatedRegionEt", -4) << "   12x12= " << ucttau->getFloat("associatedJetPt", -4) << endl;
                    if (matchToGenTau(ucttau->eta(), ucttau->phi(), iEvent)) {
                        RelaxedTauUnpackedEff->Fill(ipftau->pt());
                        RelaxedTauUnpackedROC->Fill(ucttau->pt());
                        RelaxedTauUnpackedROC4x4->Fill(ucttau->getFloat("associatedRegionEt", -4));
                        break;

                    }
                }
                for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {
                    if (matchToGenTau(uctIsotau->eta(), uctIsotau->phi(), iEvent)) {
                        IsolatedTauUnpackedEff->Fill(ipftau->pt());
                        IsolatedTauUnpackedROC->Fill(uctIsotau->pt());
                        IsolatedTauUnpackedROC4x4->Fill(uctIsotau->getFloat("associatedRegionEt", -4));
                        break;
                    }
                }

            }// if there is denumerator

        }//loop over OfflineTau
    } else {

        float maxValPt_tau = 0;
        for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {
            if (tau->pt() > maxValPt_tau) {
                maxValPt_tau = tau->pt();
            }
        }
        rate_L1JetParticle->Fill(maxValPt_tau);

        //########################################################
        float maxValPt_ucttau = 0;
        for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
            if (ucttau->pt() > maxValPt_ucttau) {
                maxValPt_ucttau = ucttau->pt();
            }
        }
        rate_UCTCandidate->Fill(maxValPt_ucttau);

        //########################################################
        float maxValPt_uctIsotau = 0;
        for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {
            if (uctIsotau->pt() > maxValPt_uctIsotau) {
                maxValPt_uctIsotau = uctIsotau->pt();
            }
        }
        rate_UCTCandidateIso->Fill(maxValPt_uctIsotau);
    } // end loop over rate

}

//define this as a plug-in
DEFINE_FWK_MODULE(Efficiency_L1Mu);
