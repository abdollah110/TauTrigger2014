import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))

process.source = cms.Source( "PoolSource",
    fileNames = cms.untracked.vstring(
        'file:file.root',
    ),
    secondaryFileNames = cms.untracked.vstring(
    ),
    inputCommands = cms.untracked.vstring(
        'keep *'
    )
)

execfile("files.py")

process.demo = cms.EDAnalyzer('Etau_rate'
                              )
process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string('eTau.root')
                                   )
process.p = cms.Path(process.demo)
