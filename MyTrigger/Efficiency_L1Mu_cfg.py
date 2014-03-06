import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames=cms.untracked.vstring(
                            #                            'file:/tmp/abdollah/patTuple_L1Mu12_9_1_7Cz.root'
                            #                            'file:/tmp/abdollah/mcpatTuple_10_1_VXl.root',

                            ###### New V4 ZTautau  (Fixed issue)
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_10_1_iJD.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_11_1_Wqu.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_12_1_xLg.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_13_1_e6q.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_14_1_kP1.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_15_1_A5g.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_16_1_v4J.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_18_1_hIR.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_19_1_goh.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_1_1_R0z.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_20_1_1z2.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_2_1_2kM.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_4_1_2V6.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_5_1_UYD.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_6_1_FEn.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_7_1_Psz.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_8_1_z6J.root',
                            'root://eoscms//eos/cms//store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZTauTau_AllPixVtx_firstPixelVtx_sorted2power_threshold10gev/patTuple_9_1_xVB.root',

#                            ###### New V4 ZPrimeTautau  (Fixed issue)
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_10_1_hps.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_11_1_QJn.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_12_1_qUJ.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_13_1_S87.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_14_1_N6F.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_15_1_y08.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_16_1_9P8.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_17_1_kkd.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_18_1_dbl.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_1_1_GGK.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_2_1_UBF.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_3_1_yLc.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_4_1_V3O.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_5_1_ZUW.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_6_1_eBO.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_7_1_c3j.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_8_1_ZMp.root',
#                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/mt/fixedUCT2015/ZPrimeTauTau_firstPixelVtx_sorted2power_threshold10gev/patTuple_9_1_2oj.root',


                            #
                            #
                            #
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_10_1_jgn.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_11_1_n65.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_12_1_sRZ.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_13_1_Dza.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_14_1_NxH.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_15_1_14u.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_16_1_xKC.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_17_1_cYk.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_18_1_L45.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_19_1_5U3.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_1_1_oCK.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_20_1_NGV.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_2_1_vpU.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_3_1_Eg3.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_4_1_QZ9.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_5_1_J6z.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_6_1_1H6.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_7_1_G3G.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_8_1_JBZ.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/4feb/ZTauTau_first2PixelVtx/patTuple_9_1_07C.root',
                            #
                            #                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_10_1_VXl.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_11_1_YPV.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_12_1_zN9.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_13_1_PIu.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_14_1_L9f.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_15_1_3GA.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_16_1_zSJ.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_17_1_BUz.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_18_1_2BA.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_19_1_788.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_1_1_eeX.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_20_1_KR0.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_2_1_LsX.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_3_1_xMx.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_4_1_jou.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_5_1_xhE.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_6_1_AIB.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_7_1_fLA.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_8_1_ehq.root',
                            #                            'root://eoscms//eos/cms/store/cmst3/user/manzoni/TauPOG/11feb/ZTauTau_first4PixelVtx_sorted4power/patTuple_9_1_UZ5.root'

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
                                   fileName=cms.string('eff_Results_Fixed1.root')
                                   )

process.p = cms.Path(process.demo)
#process.p = cms.Path(process.isolatedOnlineMuons * process.demo)
