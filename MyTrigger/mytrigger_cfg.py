import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames=cms.untracked.vstring(
                            #$        'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_10_1_EwT.root'



                            'file:/tmp/abdollah/patTuple_10_1_GbK.root',
                            'file:/tmp/abdollah/patTuple_11_1_agD.root',
                            'file:/tmp/abdollah/patTuple_12_1_ooX.root',
                            'file:/tmp/abdollah/patTuple_13_1_3Fd.root',
                            'file:/tmp/abdollah/patTuple_14_1_pKM.root',
                            'file:/tmp/abdollah/patTuple_15_1_EyL.root',
                            'file:/tmp/abdollah/patTuple_17_1_cTP.root',
                            'file:/tmp/abdollah/patTuple_19_1_vJU.root',
                            'file:/tmp/abdollah/patTuple_1_1_FSH.root',
                            'file:/tmp/abdollah/patTuple_20_1_1Ts.root',
                            'file:/tmp/abdollah/patTuple_21_1_fUF.root',
                            'file:/tmp/abdollah/patTuple_22_1_s3l.root',
                            'file:/tmp/abdollah/patTuple_23_1_pfR.root',
                            'file:/tmp/abdollah/patTuple_24_1_rsH.root',
                            'file:/tmp/abdollah/patTuple_25_1_0qn.root',
                            'file:/tmp/abdollah/patTuple_26_1_B5L.root',
                            'file:/tmp/abdollah/patTuple_27_1_hIV.root',
                            'file:/tmp/abdollah/patTuple_28_1_PqW.root',
                            'file:/tmp/abdollah/patTuple_2_1_sul.root',
                            'file:/tmp/abdollah/patTuple_3_1_8dl.root',
                            'file:/tmp/abdollah/patTuple_4_1_b7M.root',
                            'file:/tmp/abdollah/patTuple_5_1_0ZU.root',
                            'file:/tmp/abdollah/patTuple_6_1_uIE.root',
                            'file:/tmp/abdollah/patTuple_7_1_RMK.root',
                            'file:/tmp/abdollah/patTuple_8_1_84N.root',
                            'file:/tmp/abdollah/patTuple_9_1_Grb.root',



                            #'file:/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple_v2/a04681733824dfbb43487c8123b4b0f2/patTuple_7_1_RMK.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_10_1_EwT.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_11_1_ECf.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_1_1_EY9.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_12_1_VYt.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_13_1_MHe.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_14_1_KXl.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_15_1_MtS.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_16_1_BXF.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_17_1_m79.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_18_1_5lq.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_19_1_0vz.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_20_1_HN6.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_21_1_3Y5.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_2_1_Kyd.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_22_1_XCd.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_23_1_j9r.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_24_1_mAv.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_25_1_vl0.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_26_1_vk0.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_27_1_Lie.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_28_1_0ni.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_3_1_q7Z.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_4_1_oB4.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_5_1_80G.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_6_1_te1.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_7_1_haZ.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_8_1_YLO.root',
                            #'file:/user_mnt/user/abdollah/SingleMu/SingleMu-SkimmedHLTMu17-Run2012D-22Jan2013-v1-RAWAOD-PatTuple/6d4df2e925a381a14364673d1f4bb5f0/patTuple_9_1_qgu.root'
        

                            )
                            )

process.demo = cms.EDAnalyzer('MyTrigger'
                              #rhoCenNeutralTight=cms.InputTag("kt6PFJetsCentralNeutralTight", "rho")
                              )

process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string('Results1.root')
                                   )

process.p = cms.Path(process.demo)
