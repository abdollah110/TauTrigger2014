import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames=cms.untracked.vstring(
                            #                            'file:/tmp/abdollah/patTuple_L1Mu12_9_1_7Cz.root'
                            #                            'file:/tmp/abdollah/mcpatTuple_10_1_VXl.root'
                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_19_1_788.root',

                            )
                            )

#process.isolatedOnlineMuons = cms.EDProducer(
#                                             "ChargedCandidateFromTrigRefConverter",
#                                             triggerFilterMuonsSrc=cms.InputTag("hltL3crIsoL1sMu14erORMu16erL1f0L2f14QL3f17QL3crIsoRhoFiltered0p15")
#                                             )
process.demo = cms.EDAnalyzer('Efficiency_L1Mu',
                              #rhoCenNeutralTight=cms.InputTag("kt6PFJetsCentralNeutralTight", "rho")
                              srcGenParticle=cms.InputTag("genParticles"),
                              srcL1Mus=cms.InputTag("l1extraParticles"),
                              srcL1Taus=cms.InputTag("l1extraParticles", "Tau"),
                              srcHLTCaloTowers=cms.InputTag('hltTowerMakerForPF'),
                              srcL1UpgradeTaus=cms.InputTag('UCT2015Producer', 'RelaxedTauUnpacked'),
                              srcL1UpgradeIsoTaus=cms.InputTag('UCT2015Producer', 'IsolatedTauUnpacked') #taus below 60 GeV will have isolation applied
                              )

process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string('eff_Results.root')
                                   )

process.p = cms.Path(process.demo)
#process.p = cms.Path(process.isolatedOnlineMuons * process.demo)
