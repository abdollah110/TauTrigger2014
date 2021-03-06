import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

#process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames=cms.untracked.vstring(
                            #$        'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_10_1_EwT.root'
'file:/tmp/abdollah/patTuples_EleEle_1.root',
'file:/tmp/abdollah/patTuples_EleEle_2.root',
'file:/tmp/abdollah/patTuples_EleEle_3.root'

                            )
                            )

#process.isolatedOnlineMuons = cms.EDProducer(
#                                             "ChargedCandidateFromTrigRefConverter",
#                                             triggerFilterMuonsSrc=cms.InputTag("hltL3crIsoL1sMu14erORMu16erL1f0L2f14QL3f17QL3crIsoRhoFiltered0p15")
#)
process.isolatedOnlineElectrons = cms.EDProducer(
                                                 "ElectronCandidateFromTrigRefConverter",
                                                 triggerFilterElectronsSrc=cms.InputTag("hltEle22WP90RhoTrackIsoFilter")
                                                 )
process.demo = cms.EDAnalyzer(
                                "RateMeasurment_L1_and_HLT_Ele",
                              srcTriggerResults=cms.InputTag("TriggerResults", "", "HLT"),
                              srcGenParticle=cms.InputTag("genParticles"),
                              srcL1IsoElectron=cms.InputTag("l1extraParticles","Isolated"),
                              srcL1NonIsoElectron=cms.InputTag("l1extraParticles","NonIsolated"),
                              srcL1Mus=cms.InputTag("l1extraParticles"),
                              srcL1Taus=cms.InputTag("l1extraParticles", "Tau"),
                              srcL1Jets=cms.InputTag("l1extraParticles", "Central"),
                              srcHLTCaloTowers=cms.InputTag('hltTowerMakerForPF'),
                              srcL1UpgradeTaus=cms.InputTag('UCT2015Producer', 'RelaxedTauUnpacked'),
                              srcL1UpgradeIsoTaus=cms.InputTag('UCT2015Producer', 'IsolatedTauUnpacked') #taus below 60 GeV will have isolation applied
                              )

process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string('rate_HLTplusL1.root')
                                   )

process.p = cms.Path(process.isolatedOnlineElectrons * process.demo)
#process.p = cms.Path(process.isolatedOnlineMuons * process.demo)
