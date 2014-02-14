import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames=cms.untracked.vstring(
                            'file:/tmp/abdollah/patTuple_L1Mu12_9_1_7Cz.root'


                            )
                            )

process.isolatedOnlineMuons = cms.EDProducer(
                                             "ChargedCandidateFromTrigRefConverter",
                                             triggerFilterMuonsSrc=cms.InputTag("hltL3crIsoL1sMu14erORMu16erL1f0L2f14QL3f17QL3crIsoRhoFiltered0p15")
                                             )
process.demo = cms.EDAnalyzer('L1MuTrigger'
                              #rhoCenNeutralTight=cms.InputTag("kt6PFJetsCentralNeutralTight", "rho")
                              )

process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string('Results1.root')
                                   )

process.p = cms.Path(process.isolatedOnlineMuons * process.demo)
