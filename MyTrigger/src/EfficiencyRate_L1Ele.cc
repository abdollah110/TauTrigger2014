// -*- C++ -*-
//
// Package:    EfficiencyRate_L1Ele
// Class:      EfficiencyRate_L1Ele
//
/**\class EfficiencyRate_L1Ele EfficiencyRate_L1Ele.cc TauTrigger2014/EfficiencyRate_L1Ele/src/EfficiencyRate_L1Ele.cc

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

class EfficiencyRate_L1Ele : public edm::EDAnalyzer {
public:
    explicit EfficiencyRate_L1Ele(const edm::ParameterSet&);
    ~EfficiencyRate_L1Ele();
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
    TH1D * rate_UCTCandidateIso4x4;
    TH1D * rate_UCTCandidate4x4;

    TH2D * Eff2D_Num_l1extraParticles;
    TH2D * Eff2D_Num_RelaxedTauUnpacked;
    TH2D * Eff2D_Num_RelaxedTauUnpacked4x4;
    TH2D * Eff2D_Num_IsolatedTauUnpacked;
    TH2D * Eff2D_Num_IsolatedTauUnpacked4x4;

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

EfficiencyRate_L1Ele::EfficiencyRate_L1Ele(const edm::ParameterSet& iConfig) {
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
    rate_UCTCandidateIso4x4 = fs->make<TH1D > ("rate_UCTCandidateIso4x4", "", 100, 0, 100);
    rate_UCTCandidate4x4 = fs->make<TH1D > ("rate_UCTCandidate4x4", "", 100, 0, 100);

    Eff2D_Num_l1extraParticles = fs->make<TH2D > ("Eff2D_Num_l1extraParticles", "", 100, 0, 100, 100, 0, 100);
    Eff2D_Num_RelaxedTauUnpacked = fs->make<TH2D > ("Eff2D_Num_RelaxedTauUnpacked", "", 100, 0, 100, 100, 0, 100);
    Eff2D_Num_RelaxedTauUnpacked4x4 = fs->make<TH2D > ("Eff2D_Num_RelaxedTauUnpacked4x4", "", 100, 0, 100, 100, 0, 100);
    Eff2D_Num_IsolatedTauUnpacked = fs->make<TH2D > ("Eff2D_Num_IsolatedTauUnpacked", "", 100, 0, 100, 100, 0, 100);
    Eff2D_Num_IsolatedTauUnpacked4x4 = fs->make<TH2D > ("Eff2D_Num_IsolatedTauUnpacked4x4", "", 100, 0, 100, 100, 0, 100);


    srcGenParticle_ = iConfig.getParameter<edm::InputTag > ("srcGenParticle");
    L1MuSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Mus");
    L1TauSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Taus");
    L1JetSource_ = iConfig.getParameter<edm::InputTag > ("srcL1Jets");
    srcHLTCaloTowers_ = iConfig.getParameter<edm::InputTag > ("srcHLTCaloTowers");
    srcL1UpgradeTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeTaus");
    srcL1UpgradeIsoTaus_ = iConfig.getParameter<edm::InputTag > ("srcL1UpgradeIsoTaus");
    srcIsData_ = iConfig.getParameter<bool>("srcIsData");
}

EfficiencyRate_L1Ele::~EfficiencyRate_L1Ele() {

    //    map<string, TH1F*>::const_iterator iMap1 = myMap1__->begin();
    //    map<string, TH1F*>::const_iterator jMap1 = myMap1__->end();


    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

bool EfficiencyRate_L1Ele::matchToGenTau(float ieta, float iphi, const edm::Event& iEvent) {
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

void EfficiencyRate_L1Ele::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
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
    if (!srcIsData_) {
        for (pat::TauCollection::const_iterator ipftau = pftausHandle->begin(); ipftau != pftausHandle->end(); ipftau++) {
            if (ipftau->pt() > 20 && fabs(ipftau->eta()) < 2.3 && ipftau->tauID("decayModeFinding") > 0.5 && ipftau->tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits") > 0.5 && ipftau->tauID("againstMuonTight") > 0.5 && matchToGenTau(ipftau->eta(), ipftau->phi(), iEvent)) {
                offLineTauEff->Fill(ipftau->pt());
                offLineTauROC->Fill(ipftau->pt());
                // ############################## OLD tau HLT Algorithm
                bool hasPassedL1Tau = false;
                float ValuePtTau = 0;
                float ValuePtJet = 0;
                for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {
                    if (matchToGenTau(tau->eta(), tau->phi(), iEvent)) {
                        hasPassedL1Tau = true;
                        l1extraParticlesEff->Fill(ipftau->pt());
                        l1extraParticlesROC->Fill(tau->pt());
                        ValuePtTau = tau->pt();
                        break;
                    }
                }
                if (!hasPassedL1Tau) { // Here we add OR between L1Tau and L1Jet
                    for (vector<l1extra::L1JetParticle>::const_iterator jet = jetsHandle->begin(); jet != jetsHandle->end(); jet++) {
                        if (matchToGenTau(jet->eta(), jet->phi(), iEvent)) {
                            l1extraParticlesEff->Fill(ipftau->pt());
                            l1extraParticlesROC->Fill(jet->pt() - 20);
                            ValuePtJet = jet->pt() - 20;
                            break;
                        }
                    }
                }
                if (ValuePtTau || ValuePtJet) (ValuePtTau > (ValuePtJet) ? Eff2D_Num_l1extraParticles->Fill(ipftau->pt(), ValuePtTau) : Eff2D_Num_l1extraParticles->Fill(ipftau->pt(), ValuePtJet));
                // ############################## NEW tau HLT Algorithm UST2015
                for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
                    if (matchToGenTau(ucttau->eta(), ucttau->phi(), iEvent)) {
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
    ////////////////////////////////////////////////////////////////////////////////
    //  For rate measurement
    ////////////////////////////////////////////////////////////////////////////////
    } else {

        float maxValPt_tau = 0;
        float maxValPt_jet = 0;
        for (vector<l1extra::L1JetParticle>::const_iterator tau = tausHandle->begin(); tau != tausHandle->end(); tau++) {
            if (tau->pt() > maxValPt_tau) maxValPt_tau = tau->pt();
        }
        for (vector<l1extra::L1JetParticle>::const_iterator jet = jetsHandle->begin(); jet != jetsHandle->end(); jet++) {
            if (jet->pt() > maxValPt_jet) maxValPt_jet = jet->pt();
        }
        (maxValPt_tau > (maxValPt_jet - 20) ? rate_L1JetParticle->Fill(maxValPt_tau) : rate_L1JetParticle->Fill(maxValPt_jet - 20));

        //########################################################
        float maxValPt_ucttau = 0;
        float maxValPt_ucttau4x4 = 0;
        for (vector<UCTCandidate>::const_iterator ucttau = tausUpgradeHandle->begin(); ucttau != tausUpgradeHandle->end(); ucttau++) {
            if (ucttau->pt() > maxValPt_ucttau) maxValPt_ucttau = ucttau->pt();
            if (ucttau->getFloat("associatedRegionEt", -4) > maxValPt_ucttau4x4) maxValPt_ucttau4x4 = ucttau->getFloat("associatedRegionEt", -4);

        }
        rate_UCTCandidate->Fill(maxValPt_ucttau);
        rate_UCTCandidate4x4->Fill(maxValPt_ucttau4x4);

        //########################################################
        float maxValPt_uctIsotau = 0;
        float maxValPt_uctIsotau4x4 = 0;
        for (vector<UCTCandidate>::const_iterator uctIsotau = tausUpgradeIsoHandle->begin(); uctIsotau != tausUpgradeIsoHandle->end(); uctIsotau++) {
            if (uctIsotau->pt() > maxValPt_uctIsotau) maxValPt_uctIsotau = uctIsotau->pt();
            if (uctIsotau->getFloat("associatedRegionEt", -4) > maxValPt_uctIsotau4x4) maxValPt_uctIsotau4x4 = uctIsotau->getFloat("associatedRegionEt", -4);

        }
        rate_UCTCandidateIso->Fill(maxValPt_uctIsotau);
        rate_UCTCandidateIso4x4->Fill(maxValPt_uctIsotau4x4);
    } // end loop over rate

}

//define this as a plug-in
DEFINE_FWK_MODULE(EfficiencyRate_L1Ele);
