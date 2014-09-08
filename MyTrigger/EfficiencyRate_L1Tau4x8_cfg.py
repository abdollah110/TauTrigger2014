import FWCore.ParameterSet.Config as cms


#isDoingRate = False
isDoingRate = True

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))


process.source = cms.Source("PoolSource",
                            fileNames=cms.untracked.vstring(
                            'file:file.root',
                            ),
                            secondaryFileNames=cms.untracked.vstring(
                            ),
                            inputCommands=cms.untracked.vstring(
                            'keep *'
                            )
                            )


if isDoingRate:
    execfile("_Files_DiTau_rate.py")
else:
    execfile("_Files_DiTau_eff.py")


#process.isolatedOnlineMuons = cms.EDProducer(
#                                             "ChargedCandidateFromTrigRefConverter",
#                                             triggerFilterMuonsSrc=cms.InputTag("hltL3crIsoL1sMu14erORMu16erL1f0L2f14QL3f17QL3crIsoRhoFiltered0p15")
#                                             )



process.demo = cms.EDAnalyzer('EfficiencyRate_L1Tau',
                              #rhoCenNeutralTight=cms.InputTag("kt6PFJetsCentralNeutralTight", "rho")
                              srcIsData=cms.bool(isDoingRate),
                              srcGenParticle=cms.InputTag("genParticles"),
                              srcL1IsoElectron=cms.InputTag("l1extraParticles","Isolated"),
                              srcL1NonIsoElectron=cms.InputTag("l1extraParticles","NonIsolated"),
                              srcL1Mus=cms.InputTag("l1extraParticles"),
                              srcL1Taus=cms.InputTag("l1extraParticles", "Tau"),
                              srcL1Jets=cms.InputTag("l1extraParticles", "Central"),
                              srcHLTCaloTowers=cms.InputTag('hltTowerMakerForPF'),
                              srcL1UpgradeTaus=cms.InputTag('UCT2015Producer', 'RelaxedTauUnpacked'),
                              srcL1UpgradeIsoTaus=cms.InputTag('UCT2015Producer', 'IsolatedTauUnpacked'), #taus below 60 GeV will have isolation applied
                              srcL1UpgradeTaus4x8=cms.InputTag('UCT2015Producer', 'RelaxedTauUnpacked'),
                              srcL1UpgradeIsoTaus4x8=cms.InputTag('UCT2015Producer', 'IsolatedTauUnpacked') #taus below 60 GeV will have isolation applied
                              )

if isDoingRate:
    process.TFileService = cms.Service("TFileService",
                                       fileName=cms.string('DiTau_L1Tau_rate.root')
                                       )
else:
    process.TFileService = cms.Service("TFileService",
                                       fileName=cms.string('DiTau_L1Tau_efficiency.root')
                                       )

process.p = cms.Path(process.demo)
#process.p = cms.Path(process.isolatedOnlineMuons * process.demo)
