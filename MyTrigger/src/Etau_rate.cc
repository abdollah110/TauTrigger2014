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
    virtual bool hasNoOverLapETau(float eta_, float phi_, const edm::Event& iEvent);
    virtual bool matchToOfflineTaus(int isoOption, float eta_, float phi_, const edm::Event& iEvent);
    virtual bool matchToOfflineTausForEleVeto(float eta_, float phi_, const edm::Event& iEvent);


    TH1D * Histo_Rate;
    TH2D * Histo_2DRateAniEle;
    std::vector<float> GammasdEta_;
    std::vector<float> GammasdPhi_;
    std::vector<float> GammasPt_;
    // ----------member data ---------------------------
};

Etau_rate::Etau_rate(const edm::ParameterSet& iConfig) {
    using namespace edm;
    edm::Service<TFileService> fs;
    Histo_Rate = fs->make<TH1D > ("TriggerRate", "TriggerRate", 10, 0, 10);
    Histo_2DRateAniEle = fs->make<TH2D > ("TriggerRate2D", "TriggerRate2D", 5, 0, 5, 10, 0, 10);
}

Etau_rate::~Etau_rate() {
}

bool Etau_rate::hasNoOverLapETau(float eta_, float phi_, const edm::Event& iEvent) {
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

    bool HasNoOverLap = true;
    for (; iele != jele; ++iele) {
        if (iele->pt() > 15 && fabs(iele->eta()) < 2.5 && tool.dR2(iele->eta(), iele->phi(), eta_, phi_) < 0.4) {
            HasNoOverLap = false;
            break;
        }
    }
    return HasNoOverLap;
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
    bool AntiEle[4][8];
    memset(AntiEle, 0, 4 * 8 * sizeof (bool));



    //    cout << "Here os the size of tau in the events=   " << tau.size() << endl;
    for (; itau != jtau; ++itau) {


        //        E_lead / P :
        float Tau_HadrEoP_ = 0;
        if (itau->leadPFChargedHadrCand().isNonnull()) {
            Tau_HadrEoP_ = itau->leadPFChargedHadrCand()->ecalEnergy() / itau->leadPFChargedHadrCand()->p();
        }
        //        cout << "Tau_HadrEoP_= " << Tau_HadrEoP_ << "\n";
        //        H_3x3 / P :
        float Tau_hcal3x3OverPLead_ = itau->hcal3x3OverPLead();
        //        cout << "Tau_hcal3x3OverPLead_= " << Tau_hcal3x3OverPLead_ << "\n";

        //        EgammaFraction, Photon Eta Momenta and Phi Momenta are calculated as follows :

        GammasdEta_.clear();
        GammasdPhi_.clear();
        GammasPt_.clear();
        const std::vector<reco::PFCandidatePtr>& signalPFGammaCands = itau->signalPFGammaCands();
        //        cout << "signalPFGammaCands->size()= " << signalPFGammaCands.size() << endl;
        for (std::vector<reco::PFCandidatePtr>::const_iterator pfGamma = signalPFGammaCands.begin();
                pfGamma != signalPFGammaCands.end(); ++pfGamma) {
            if (itau->leadPFChargedHadrCand().isNonnull()) {
                GammasdEta_.push_back((*pfGamma)->eta() - itau->leadPFChargedHadrCand()->eta());
                GammasdPhi_.push_back((*pfGamma)->phi() - itau->leadPFChargedHadrCand()->phi());
            } else {
                GammasdEta_.push_back((*pfGamma)->eta() - itau->eta());
                GammasdPhi_.push_back((*pfGamma)->phi() - itau->phi());
            }
            GammasPt_.push_back((*pfGamma)->pt());
        }
        float sumPt = 0.;
        float dEta = 0.;
        float dEta2 = 0.;
        float dPhi = 0.;
        float dPhi2 = 0.;
        float sumPt2 = 0.;

        //        cout << "sizez pt, eta, phi =" << GammasPt_.size() << "\t";
        //        cout << GammasdEta_.size() << "\t";
        //        cout << GammasdPhi_.size() << "\n";

        size_t numPFGammas = GammasPt_.size();
        assert(GammasdEta_.size() == numPFGammas);
        assert(GammasdPhi_.size() == numPFGammas);
        for (size_t idxPFGamma = 0; idxPFGamma < numPFGammas; ++idxPFGamma) {
            float pt = GammasPt_[idxPFGamma];
            float dPhi = GammasdPhi_[idxPFGamma];
            if (dPhi > TMath::Pi()) dPhi -= 2. * TMath::Pi();
            else if (dPhi < -TMath::Pi()) dPhi += 2. * TMath::Pi();
            float dEta = GammasdEta_[idxPFGamma];
            sumPt += pt;
            sumPt2 += (pt * pt);
            dEta += (pt * dEta);
            dEta2 += (pt * dEta * dEta);
            dPhi += (pt * dPhi);
            dPhi2 += (pt * dPhi * dPhi);
        }

        float gammadPt = sumPt / itau->pt();

        if (sumPt > 0.) {
            dEta /= sumPt;
            dPhi /= sumPt;
            dEta2 /= sumPt;
            dPhi2 /= sumPt;
        }

        float Tau_GammaEtaMom_ = TMath::Sqrt(dEta2) * TMath::Sqrt(gammadPt) * itau->pt();
        float Tau_GammaPhiMom_ = TMath::Sqrt(dPhi2) * TMath::Sqrt(gammadPt) * itau->pt();
        float Tau_GammaEnFrac_ = gammadPt;

        //   I remove electrons / Taus from ecal cracks :

        float EtaLTrk = (itau->leadPFChargedHadrCand().isNonnull() ? itau->leadPFChargedHadrCand()->eta() : itau->eta());
        bool EtaLTrk_Barrel = TMath::Abs(EtaLTrk) < 1.460;
        bool EtaLTrk_EndCap = TMath::Abs(EtaLTrk) > 1.558;
        bool TauInCracks = (TMath::Abs(EtaLTrk) < 0.018 || (TMath::Abs(EtaLTrk) > 0.423 && TMath::Abs(EtaLTrk) < 0.461) || (TMath::Abs(EtaLTrk) > 0.770 && TMath::Abs(EtaLTrk) < 0.806) || (TMath::Abs(EtaLTrk) > 1.127 && TMath::Abs(EtaLTrk) < 1.163) || (TMath::Abs(EtaLTrk) > 1.460 && TMath::Abs(EtaLTrk) < 1.558));
        //****************  Barrel
        bool Barrel_1 = EtaLTrk_Barrel && (Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01 || Tau_hcal3x3OverPLead_ > 0.2);
        //        Tau Eff. : 0.936, Elec. Eff. : 0.069
        bool Barrel_2 = EtaLTrk_Barrel && ((Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01 || Tau_hcal3x3OverPLead_ > 0.2 || Tau_GammaEnFrac_ > 0.15));
        //        Tau Eff. : 0.98, Elec. Eff. : 0.113
        bool Barrel_3 = EtaLTrk_Barrel && ((Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01 || Tau_hcal3x3OverPLead_ > 0.2 || Tau_GammaEtaMom_ > 4.0));
        //        Tau Eff. : 0.966, Elec. Eff. : 0.11
        bool Barrel_4 = EtaLTrk_Barrel && ((Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01 || Tau_hcal3x3OverPLead_ > 0.2 || Tau_GammaPhiMom_ > 4.0));
        //        Tau Eff. : 0.97, Elec. Eff. : 0.126

        //****************  EndCap
        bool EndCap_1 = EtaLTrk_EndCap && (Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01);
        //Tau Eff. : 0.954, Elec. Eff. : 0.22
        bool EndCap_2 = EtaLTrk_EndCap && ((Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01) && (Tau_HadrEoP_ < 0.7 || Tau_HadrEoP_ > 1.3 || Tau_hcal3x3OverPLead_ > 0.1));
        //        Tau Eff. : 0.944, Elec. Eff. : 0.18
        bool EndCap_3 = EtaLTrk_EndCap && (Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01 || Tau_GammaEnFrac_ > 0.2);
        //        Tau Eff. : 0.969, Elec. Eff. : 0.25
        bool EndCap_4 = EtaLTrk_EndCap && (((Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01) && (Tau_HadrEoP_ < 0.7 || Tau_HadrEoP_ > 1.3 || Tau_hcal3x3OverPLead_ > 0.1)) || Tau_GammaEnFrac_ > 0.2);
        //Tau Eff. : 0.965, Elec. Eff. : 0.24
        bool EndCap_5 = EtaLTrk_EndCap && (Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01 || Tau_GammaEtaMom_ > 10.0);
        //Tau Eff. : 0.961, Elec. Eff. : 0.233
        bool EndCap_6 = EtaLTrk_EndCap && (((Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01) && (Tau_HadrEoP_ < 0.7 || Tau_HadrEoP_ > 1.3 || Tau_hcal3x3OverPLead_ > 0.1)) || Tau_GammaEtaMom_ > 10.0);
        //Tau Eff. : 0.955, Elec. Eff. : 0.198
        bool EndCap_7 = EtaLTrk_EndCap && (Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01 || Tau_GammaPhiMom_ > 10.0);
        //Tau Eff. : 0.965, Elec. Eff. : 0.246
        bool EndCap_8 = EtaLTrk_EndCap && (((Tau_HadrEoP_ < 0.99 || Tau_HadrEoP_ > 1.01) && (Tau_HadrEoP_ < 0.7 || Tau_HadrEoP_ > 1.3 || Tau_hcal3x3OverPLead_ > 0.1)) || Tau_GammaPhiMom_ > 10.0);
        //Tau Eff. : 0.959, Elec. Eff. : 0.216

        bool BB[4] = {Barrel_1, Barrel_2, Barrel_3, Barrel_4};
        bool EE[8] = {EndCap_1, EndCap_2, EndCap_3, EndCap_4, EndCap_5, EndCap_6, EndCap_7, EndCap_8};


        //        //****************  Barrel
        //        Elead / P < 0.99 OR Elead / P > 1.01 || H3x3 / P > 0.2;
        //        //        Tau Eff. : 0.936, Elec. Eff. : 0.069
        //        (Elead / P < 0.99 OR Elead / P > 1.01 OR H3x3 / P > 0.2 OR EgF > 0.15);
        //        //        Tau Eff. : 0.98, Elec. Eff. : 0.113
        //        (Elead / P < 0.99 OR Elead / P > 1.01 OR H3x3 / P > 0.2 OR ghmom > 4.0);
        //        //        Tau Eff. : 0.966, Elec. Eff. : 0.11
        //        (Elead / P < 0.99 OR Elead / P > 1.01 OR H3x3 / P > 0.2 OR gfmom > 4.0);
        //        //        Tau Eff. : 0.97, Elec. Eff. : 0.126
        //
        //        //****************  EndCap
        //        E / P < 0.99 OR E / P > 1.01;
        //        //Tau Eff. : 0.954, Elec. Eff. : 0.22
        //        (Elead / P < 0.99 OR Elead / P > 1.01) AND(Elead / P < 0.7 OR Elead / P > 1.3 OR H3x3 / P > 0.1);
        //        //        Tau Eff. : 0.944, Elec. Eff. : 0.18
        //        Elead / P < 0.99 OR Elead / P > 1.01 OR EgF > 0.2;
        //        //        Tau Eff. : 0.969, Elec. Eff. : 0.25
        //        ((Elead / P < 0.99 OR Elead / P > 1.01) AND(Elead / P < 0.7 OR Elead / P > 1.3 OR H3x3 / P > 0.1)) OR EgF > 0.2;
        //        //Tau Eff. : 0.965, Elec. Eff. : 0.24
        //        Elead / P < 0.99 OR Elead / P > 1.01 OR ghmom > 10.0;
        //        //Tau Eff. : 0.961, Elec. Eff. : 0.233
        //        ((Elead / P < 0.99 OR Elead / P > 1.01) AND(Elead / P < 0.7 OR Elead / P > 1.3 OR H3x3 / P > 0.1)) OR ghmom > 10.0;
        //        //Tau Eff. : 0.955, Elec. Eff. : 0.198
        //        Elead / P < 0.99 OR Elead / P > 1.01 OR gfmom > 5.0;
        //        //Tau Eff. : 0.965, Elec. Eff. : 0.246
        //        ((Elead / P < 0.99 OR Elead / P > 1.01) AND(Elead / P < 0.7 OR Elead / P > 1.3 OR H3x3 / P > 0.1)) OR gfmom > 10.0;
        //        //Tau Eff. : 0.959, Elec. Eff. : 0.216
        //
        //

        bool ptCut = itau->pt() > 20 && fabs(itau->eta()) < 2.3;
        bool EleTauPair = ipfele > 0;
        bool hasOverlapEle = hasNoOverLapETau(itau->eta(), itau->phi(), iEvent);
        bool discByDecayModeFinding = (itau->tauID("decayModeFinding") > 0.5 ? true : false);
        bool discByIsolation5hits = (itau->tauID("byTrkIsolation5hits") < 3.0 ? true : false);
        //        bool discByEleLoose = matchToOfflineTausForEleVeto(itau->eta(), itau->phi(), iEvent);
        bool discByEleLoose = 1;
        //        bool discByIsolation = (itau->tauID("byIsolation") > 0.5 ? true : false);
        //        bool discByIsolation = (itau->tauID("byTrkIsolation") < 3.0 ? true : false);



        if (EleTauPair && ptCut && hasOverlapEle) step1++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding) step2++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByEleLoose) step3++;
        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits) {
            step4++;
            for (int ii = 0; ii < 4; ii++) {
                for (int jj = 0; jj < 8; jj++) {
                    if (BB[ii] || EE[jj]) AntiEle[ii][jj]++;
                    if (TauInCracks) AntiEle[ii][jj]++;
                }
            }
        }


        //        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits && discByEleLoose) step5++;
        //        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits && discByEleLoose && matchToOfflineTaus(1, itau->eta(), itau->phi(), iEvent)) step6++;
        //        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits && discByEleLoose && matchToOfflineTaus(2, itau->eta(), itau->phi(), iEvent)) step7++;
        //        if (EleTauPair && ptCut && hasOverlapEle && discByDecayModeFinding && discByIsolation5hits && discByEleLoose && matchToOfflineTaus(3, itau->eta(), itau->phi(), iEvent)) step8++;
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

    for (int ii = 0; ii < 4; ii++) {
        for (int jj = 0; jj < 8; jj++) {
            if (AntiEle[ii][jj] > 0) Histo_2DRateAniEle->Fill(ii , jj );
        }
    }

    //        cout << iEvent.id().run() << ":" << iEvent.id().luminosityBlock() << ":" << iEvent.id().event() << "\n";

}// end of Analyze



//define this as a plug-in
DEFINE_FWK_MODULE(Etau_rate);
