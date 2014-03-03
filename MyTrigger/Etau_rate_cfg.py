import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))

execfile("source_etau.py")

process.demo = cms.EDAnalyzer('Etau_rate'
                              )
process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string('eTau.root')
                                   )
process.p = cms.Path(process.demo)
