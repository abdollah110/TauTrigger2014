import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(20000))

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames=cms.untracked.vstring(
#                            'file:/tmp/abdollah/patTuple_L1Mu12_9_1_7Cz.root'
                            'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_9_1_7Cz.root',
#/eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_9_1_7Cz.root


'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_10_1_Icr.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_11_1_RT4.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_12_1_Ki7.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_13_1_TgF.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_14_1_Jp3.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_15_1_dn7.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_16_1_Ofd.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_17_1_WMT.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_18_1_Z8n.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_19_1_IZL.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_1_1_I4W.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_20_1_vbz.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_21_1_1Pd.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_22_1_NM9.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_23_1_qET.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_24_1_UFb.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_25_1_yt3.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_26_1_Sba.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_27_1_p05.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_28_1_kNu.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_29_1_G0P.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_2_1_ay0.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_30_1_6j1.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_31_1_hjg.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_32_1_hld.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_33_1_I23.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_34_1_nK8.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_35_1_ldh.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_36_1_2Na.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_37_1_73M.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_38_1_7IU.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_39_1_RL4.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_3_1_rC5.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_40_1_E9z.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_41_1_vf6.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_42_1_wBV.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_43_1_t5B.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_44_1_Lyu.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_45_1_vC0.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_46_1_I25.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_47_1_96i.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_48_1_y9n.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_49_1_4xr.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_4_1_JQp.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_50_1_ujQ.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_51_1_OOh.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_52_1_O3O.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_53_1_dv1.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_54_1_B1j.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_55_1_nbz.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_56_1_hsv.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_57_1_YD0.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_58_1_6zT.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_59_1_Mtr.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_5_1_IxZ.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_60_1_1YC.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_61_1_FN9.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_62_1_Y20.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_63_1_Q9L.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_64_1_GOy.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_65_1_fyr.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_66_1_iDP.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_67_1_8C2.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_68_1_ZQe.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_69_1_y1A.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_6_1_Nf2.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_70_1_9j2.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_71_1_T3n.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_72_1_nnM.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_73_1_Ita.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_74_1_bPR.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_75_1_JyK.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_76_1_Uz0.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_77_1_zca.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_78_1_o4Z.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_79_1_k3R.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_7_1_svC.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_80_1_I7H.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_81_1_DgW.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_82_1_08v.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_83_1_imy.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_84_1_gLj.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_85_1_dwP.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_86_1_910.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_87_1_CdZ.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_88_1_Ce6.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_8_1_oKq.root',
'root://eoscms//eos/cms/store/user/abdollah/TauTrigger2014/CommissioningSkimmedL1Mu12-PatTuples/patTuple_L1Mu12_9_1_7Cz.root',


                            )
                            )

#process.isolatedOnlineMuons = cms.EDProducer(
#                                             "ChargedCandidateFromTrigRefConverter",
#                                             triggerFilterMuonsSrc=cms.InputTag("hltL3crIsoL1sMu14erORMu16erL1f0L2f14QL3f17QL3crIsoRhoFiltered0p15")
#                                             )
process.demo = cms.EDAnalyzer('L1MuTrigger',
                              #rhoCenNeutralTight=cms.InputTag("kt6PFJetsCentralNeutralTight", "rho")
                              srcL1Mus=cms.InputTag("l1extraParticles"),
                              srcL1Taus=cms.InputTag("l1extraParticles", "Tau"),
                              srcHLTCaloTowers = cms.InputTag('hltTowerMakerForPF'),
                              srcL1UpgradeTaus = cms.InputTag('UCT2015Producer', 'RelaxedTauUnpacked'),
                              srcL1UpgradeIsoTaus = cms.InputTag('UCT2015Producer', 'IsolatedTauUnpacked')
                              )

process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string('Results1.root')
                                   )

process.p = cms.Path(process.demo)
#process.p = cms.Path(process.isolatedOnlineMuons * process.demo)
