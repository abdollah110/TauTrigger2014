import FWCore.ParameterSet.Config as cms

is50ns = False
type = 'All' # possible setting 'All' 'Mu' 'EG' 'DiTau' 
verbose = True

process = cms.Process("Skim")

## Source
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
'file:/afs/cern.ch/work/a/abdollah/Run2012A_DoubleMu_AOD_13Jul2012-v1_F87222D4-D6CF-E111-B6ED-0026189438BC.root'
),
    secondaryFileNames = cms.untracked.vstring()
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
if is50ns:
    process.GlobalTag.globaltag = cms.string( 'POSTLS162_V1::All' )
else:
    process.GlobalTag.globaltag = cms.string( 'POSTLS162_V2::All' )
    

process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

## selectors and counters
# EG
process.goodL1NonIsoEGs = cms.EDFilter(
    #"CandViewSelector",
    "L1EmParticleSelector",
    src = cms.InputTag("l1extraParticles:NonIsolated"),
    cut = cms.string("pt > 12 && abs(eta)<2.172"),
    filter = cms.bool(False)
)
process.goodL1NonIsoEGCounter = cms.EDFilter(
    "CandViewCountFilter",
    src = cms.InputTag("goodL1NonIsoEGs"),
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(12345),
)
process.goodL1IsoEGs = cms.EDFilter(
    #"CandViewSelector",
    "L1EmParticleSelector",
    src = cms.InputTag("l1extraParticles:Isolated"),
    cut = cms.string("pt > 12 && abs(eta)<2.172"),
    filter = cms.bool(False)
)
process.goodL1IsoEGCounter = cms.EDFilter(
    "CandViewCountFilter",
    src = cms.InputTag("goodL1IsoEGs"),
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(12345),
)
# Muons
process.goodL1Muons = cms.EDFilter(
    #"CandViewSelector",
    "L1MuonParticleSelector",
    src = cms.InputTag("l1extraParticles"),
    cut = cms.string("pt > 12 && abs(eta)<2.1"),
    filter = cms.bool(False)
)
process.goodL1MuonCounter = cms.EDFilter(
    "CandViewCountFilter",
    src = cms.InputTag("goodL1Muons"),
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(12345),
)
# Taus
process.goodL1UCT2015Taus = cms.EDFilter(
    "CandViewSelector",
    src = cms.InputTag("UCT2015Producer:RelaxedTauUnpacked"),
    cut = cms.string("pt > 12 && abs(eta)<3"),
    filter = cms.bool(False)
)
process.goodL1UCT2015TauCounter = cms.EDFilter(
    "CandViewCountFilter",
    src = cms.InputTag("goodL1UCT2015Taus"),
    minNumber = cms.uint32(2),
    maxNumber = cms.uint32(12345),
)


## Run it
if type == 'All' or type == 'Mu':
    process.pMu = cms.Path(
        process.goodL1Muons +
        process.goodL1MuonCounter
    )
if type == 'All' or type == 'EG':
    process.pNonIsoEG = cms.Path(
        process.goodL1NonIsoEGs +
        process.goodL1NonIsoEGCounter
    )
    process.pIsoEG = cms.Path(
        process.goodL1IsoEGs +
        process.goodL1IsoEGCounter
    )
if type == 'All' or type == 'DiTau':
    process.load("uct2015_MC_cff")
    process.pDiTau = cms.Path(
        process.uct2015Sequence +
        process.goodL1UCT2015Taus +
        process.goodL1UCT2015TauCounter
    )

## Output Module
process.out = cms.OutputModule(
    "PoolOutputModule",
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring() ),
    fileName = cms.untracked.string('skimOutput.root'),
    outputCommands = cms.untracked.vstring(
        'drop *', 
        'keep *',
        'drop *_*_*_Skim', 
    )
)
if type == 'All' or type == 'Mu':
    process.out.SelectEvents.SelectEvents.append('pMu')
if type == 'All' or type == 'EG':
    process.out.SelectEvents.SelectEvents.append('pNonIsoEG')
    process.out.SelectEvents.SelectEvents.append('pIsoEG')
if type == 'All' or type == 'DiTau':
    process.out.SelectEvents.SelectEvents.append('pDiTau')

process.outpath = cms.EndPath(
    process.out
)

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
## Options and Output Report
if verbose:
    process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
    process.MessageLogger.cerr.FwkReport.reportEvery = 100

##
print "type: ",type
print "Global Tag: ", process.GlobalTag.globaltag
