#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.
####################################################################
####################################################################
# To Run the code just do ./Make_EfficiencyRate.py  (Mu  or  Ele)
####################################################################
####################################################################

__author__ = "abdollahmohammadi"
__date__ = "$Mar 6, 2014 12:15:11 PM$"


from array import array
import math
import sys

import ROOT
from ROOT import Double
from ROOT import TAxis
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TGraph
from ROOT import TGraphAsymmErrors
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TLatex
from ROOT import TLegend
from ROOT import TNtuple
from ROOT import TProfile
from ROOT import gBenchmark
from ROOT import gROOT
from ROOT import gRandom
from ROOT import gStyle
from ROOT import gSystem

canvas = TCanvas("canvas", "", 600, 600)
gStyle.SetOptStat(0);
gStyle.SetOptTitle(0);
canvas.SetFillColor(0)
canvas.SetTitle("")
canvas.SetName("CMS Preliminary")
canvas.SetBorderMode(0)
canvas.SetBorderSize(2)
canvas.SetFrameBorderMode(0)
canvas.SetFrameLineWidth(2)
canvas.SetFrameBorderMode(0)
canvas.SetGridx(10)
canvas.SetGridy(10)

print 'Number of arguments:', len(sys.argv), 'arguments.'
candidate = str(sys.argv[1])
print "candidate is == ", candidate
if not (candidate == "Mu" or candidate == "Ele"or candidate == "Tau"):
    raise "please select either -Mu- or -Ele-"
     


def AddCostumText(candidate):
    t = TLatex()
    t.SetNDC()
    t.SetTextFont(62)
    t.SetTextAlign(12)
    t.SetTextSize(0.025)
    t.DrawLatex(0.1, .92, "CMS Preliminary")
    t.DrawLatex(0.7, .92, "di-tau Channel")
    t.SetTextSize(0.060)
    t.DrawLatex(0.6, .52, "PU40bx25")
    t.SetTextColor(2)
    return 0
def AddCostumText2(candidate,CutOffLine):
    t = TLatex()
    t.SetNDC()
    t.SetTextFont(62)
    t.SetTextAlign(12)
    t.SetTextSize(0.025)
    t.DrawLatex(0.1, .92, "CMS Preliminary")
    t.DrawLatex(0.7, .92, "di-tau Channel")
    t.SetTextSize(0.060)
    t.DrawLatex(0.6, .52, "PU40bx25")
    t.SetTextSize(0.040)
    t.DrawLatex(0.5, .42, "OfflineTau= "+str(CutOffLine) + "GeV")
    t.SetTextColor(2)
    return 0

def AddCostumMarker(Hist, Min, Max, size, marStyle, marColor, XTitke, YTitle):
    Hist.SetMinimum(Min)
    Hist.SetMaximum(Max)
    Hist.SetMarkerSize(size);
    Hist.SetMarkerStyle(marStyle);
    Hist.SetMarkerColor(marColor);
    Hist.GetXaxis().SetTitle(XTitke)
    Hist.GetYaxis().SetTitle(YTitle)
    return 0

    
    
def doRatio2D(num, denum, cut, marStyle, marColor):
    OneDNum = TH1F("NewNum", "", 200, 0, 200)
    for ii in range(0, 200):
        ValDenum = 0
        ValNum = 0
        for jj in range(cut, 200):
            ValNum = ValNum + num.GetBinContent(ii, jj)
#            print ii, jj, ValNum
        OneDNum.SetBinContent(ii, ValNum)
#    bins = array('d', [20, 25, 30, 35, 40, 45, 50, 55, 60,65,70, 80,200])
    bins = array('d', [20, 23,26, 29, 32,35, 39, 43, 47, 51, 55,60,65,70,78, 80,90,100,120,140,170,200])
    num_R = OneDNum.Rebin(len(bins)-1, "Hinm", bins)
    denum_R = denum.Rebin(len(bins)-1, "Hin", bins)
    ratio = ROOT.TGraphAsymmErrors(num_R, denum_R, "")
    AddCostumMarker(ratio, 0.0, 1.2, 1.2, marStyle, marColor, "offLine #tau_{pT} [GeV]", "Efficiency")
    ratio.SetLineColor(marColor)
    ratio.SetLineWidth(2)
    return ratio

def doCommulative(num, denum, marStyle, marColor, type):
    commul = TH1F(str(num), "", 200, 0, 200)
    for ii in range(1, 200):
        commul.SetBinContent(ii + 1, (num.Integral(ii, 200) * 1.0) / denum.GetEntries());
    AddCostumMarker(commul, 0.00001, 1.2, 1.2, marStyle, marColor, "L1 #tau_{pT} [GeV]", type)
    return commul
def doCommulativeRate(num, denum, marStyle, marColor, type):
    commul = TH1F(str(num), "", 200, 0, 200)
    commul.SetBinContent(1,1)  # first bin should be set to 1 ==> means that if you do not cut on L1 rate is 1
    for ii in range(2, 200):
        commul.SetBinContent(ii , (num.Integral(ii, 200) * 1.0) / 40000000.);
    AddCostumMarker(commul, 0.000001, 1.2, 1.2, marStyle, marColor, "L1 #tau_{pT} [GeV]", type)
    return commul

def doCommulative2D(cut, num, denum, marStyle, marColor, type):
    commul = TH1F(str(num) + str(cut), "", 200, 0, 200)
    for ii in range(1, 200):
        commul.SetBinContent(ii + 1, (num.Integral(cut, 201, ii, 201) * 1.0) / denum.Integral(cut, 201));
#        print "binNum=", ii, "Integral"
    AddCostumMarker(commul, 0.001, 1.2, 1.2, marStyle, marColor, "L1 #tau_{pT} [GeV]", type)
    return commul

def doROCCurve(cut, num1, denum1, num2, denum2, marStyle, marColor):
    rocCurve = TH2F(str(num1) + str(cut), "", 120, 0, 1.2, 120, 0, 1.2)
    for ii in range(1, 100):
        if (ii % 10 == 0): print ii, "\t"
        for jj in range (1, 100):
            for kk in range (1, 100):
                if (math.floor((num1.Integral(ii, 101) * 1.0) * 101 / denum1.Integral(cut, 101)) == jj and math.floor((((num2.Integral(ii, 101) * 1.0) / 40000.)) * 101) == kk):
#                if (math.floor((num1.Integral(ii, 101) * 1.0) * 101 / denum1.Integral(cut, 101)) == jj and math.floor((1 - ((num2.Integral(ii, 101) * 1.0) / 40000.)) * 101) == kk):
                    rocCurve.SetBinContent(jj + 1, kk + 1, 10)
    AddCostumMarker(rocCurve, 0.00000001, 1.2, 1.2, marStyle, marColor, "Efficiency", "RateReduction/1000")
    return rocCurve

def doProject2DX(cut, num):
    projectedHist = TH1F(str(num), "", 200, 0, 200)
    for ii in range(1, 200):
        Val = 0
        for jj in range(cut, 200):
            Val = Val + num.GetBinContent(jj, ii)
        projectedHist.SetBinContent(ii, Val)
    return projectedHist

def doScalingTH1(TH1, scale, marStyle, marColor):
    scaleHist = TH1F("scale"+str(TH1), "", 200, 0, 200)
    scaleHist.SetBinContent(1,1)  # first bin should be set to 1 ==> means that if you do not cut on L1 rate is 1
    for jj in range(2, 200):
#        print jj, TH1.GetBinContent(jj)
        Val =  TH1.GetBinContent(jj+1)
        scaleHist.SetBinContent(jj, Val)
    AddCostumMarker(scaleHist, 0.0000001, 1.2, 1.1, marStyle, marColor,  "L1 #tau_{pT} (second tau) [GeV]", "Rate Reduction")
    return scaleHist
    
            

##########################################################################################################
##########################################################################################################
######                                                                                              ######
##########################################################################################################
##########################################################################################################

FileRootEff = TFile("DiTau_L1Tau_efficiency.root", "OPEN")
FileRootRate = TFile("DiTau_L1Tau_rate.root", "OPEN")
#FileRootRate = TFile("TOTAL.root", "OPEN")

DenumEff = FileRootEff.Get("demo/offLineTauEff")
DenumROC = FileRootEff.Get("demo/offLineTauROC")

Num_l1extraEff = FileRootEff.Get("demo/Eff2D_Num_l1extraParticles")
Num_IsolatedTauEff_4x4 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTauUnpacked4x4")
Num_RelaxedTauEff_4x4 = FileRootEff.Get("demo/Eff2D_Num_RelaxedTauUnpacked")

L1JetParticle = FileRootRate.Get("demo/rate_L1JetParticle");
UCTCandidate4x4 = FileRootRate.Get("demo/rate_UCTCandidate4x4");
UCTCandidateIso4x4 = FileRootRate.Get("demo/rate_UCTCandidateIso4x4");



IsolatedTauEff10_4x4 = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 20, 21, 2)
IsolatedTauEff15_4x4 = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 25, 22, 3)
IsolatedTauEff20_4x4 = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 30, 23, 4)
IsolatedTauEff25_4x4 = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 35, 24, 6)
IsolatedTauEff10_4x4.Draw("PAE")
IsolatedTauEff15_4x4.Draw("Psame")
IsolatedTauEff20_4x4.Draw("Psame")
IsolatedTauEff25_4x4.Draw("Psame")
legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(IsolatedTauEff10_4x4, "UCTIsoTau 20GeV", "lp")
legend_.AddEntry(IsolatedTauEff15_4x4, "UCTIsoTau 25GeV", "lp")
legend_.AddEntry(IsolatedTauEff20_4x4, "UCTIsoTau 30GeV", "lp")
legend_.AddEntry(IsolatedTauEff25_4x4, "UCTIsoTau 35GeV", "lp")
legend_.Draw()
AddCostumText(candidate)
canvas.SaveAs("PlotTau/out_" + candidate + "TauEfficiencyUCTTau4x4DifferentL1Pt.pdf")




l1extraEff = doRatio2D(Num_l1extraEff, DenumEff, 25, 21, 2)
RelaxedTauEff = doRatio2D(Num_RelaxedTauEff_4x4, DenumEff, 25, 22, 3)
IsolatedTauEff = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 25, 23, 4)
l1extraEff.Draw("PAE")
RelaxedTauEff.Draw("Psame")
IsolatedTauEff.Draw("Psame")
legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(l1extraEff, "L1tau or jet", "lp")
legend_.AddEntry(RelaxedTauEff, "UCTTau", "lp")
legend_.AddEntry(IsolatedTauEff, "UCTIsoTau", "lp")
legend_.Draw()
AddCostumText(candidate)
canvas.SaveAs("PlotTau/out_" + candidate + "TauEfficiencyDifferentL1Algo.pdf")


ptL1 = [20,30,40,50]
for iipt in ptL1:
    l1extraROC = doCommulative2D(iipt, Num_l1extraEff, DenumROC, 21, 2, "Efficiency")
    RelaxedTau4x4ROC = doCommulative2D(iipt, Num_RelaxedTauEff_4x4, DenumROC, 24, 6, "Efficiency")
    IsolatedTau4x4ROC = doCommulative2D(iipt, Num_IsolatedTauEff_4x4, DenumROC, 25, 7, "Efficiency")
    l1extraROC.Draw("P")
    RelaxedTau4x4ROC.Draw("Psame")
    IsolatedTau4x4ROC.Draw("Psame")
    legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
    legend_.SetFillColor(0)
    legend_.SetBorderSize(0)
    legend_.SetTextSize(.03)
    legend_.AddEntry(l1extraROC, "L1tau or jet", "lp")
    legend_.AddEntry(RelaxedTau4x4ROC, "UCTTau4x4", "lp")
    legend_.AddEntry(IsolatedTau4x4ROC, "UCTIsoTau4x4", "lp")
    legend_.Draw()
    AddCostumText2(candidate,iipt)
    canvas.SaveAs("PlotTau/out_" + candidate + "TauEfficiencyCumulative2D" + str(iipt) + ".pdf")





#L1JetParticleCum = doCommulativeRate(L1JetParticle, L1JetParticle, 21, 2, "L1 Rate")
UCTCandidateCum4x4 = doCommulativeRate(UCTCandidate4x4, UCTCandidate4x4, 24, 6, "L1 Rate Reduction")
UCTCandidateIsoCum4x4 = doCommulativeRate(UCTCandidateIso4x4, UCTCandidateIso4x4, 25, 7, "L1 Rate Reduction")

#L1JetParticleCum.Draw("P")
UCTCandidateCum4x4.Draw("P")
UCTCandidateIsoCum4x4.Draw("Psame")
legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
#legend_.AddEntry(L1JetParticleCum, "L1Tau or Jet", "lp")
legend_.AddEntry(UCTCandidateCum4x4, "UCTTau4x4", "lp")
legend_.AddEntry(UCTCandidateIsoCum4x4, "UCTIsoTau4x4", "lp")
canvas.SetLogy()
legend_.Draw()
AddCostumText(candidate)
canvas.SaveAs("PlotTau/out_" + candidate + "TauRateCumulative.pdf")





#print "rate Tau  20= ", UCTCandidate4x4.Integral(20,200)/1000
#print "rate Tau  25= ", UCTCandidate4x4.Integral(25,200)/1000
#print "rate Tau  30= ", UCTCandidate.Integral(30,200)/1000
#print "rate Tau  20= ", UCTCandidateIso.Integral(20,200)/1000
#print "rate Tau  25= ", UCTCandidateIso.Integral(25,200)/1000
#print "rate Tau  30= ", UCTCandidateIso.Integral(30,200)/1000
##
#ptL1 = [20,30,40]
#for iipt in ptL1:
##    L1JetParticleROC = doROCCurve(iipt, doProject2DX(iipt, Num_l1extraEff), DenumROC, L1JetParticle, L1JetParticle, 21, 2)
#    UCTCandidateROC4x4 = doROCCurve(iipt, doProject2DX(iipt, Num_RelaxedTauEff_4x4), DenumROC, UCTCandidate4x4, UCTCandidate4x4, 24, 6)
#    UCTCandidateIsoROC4x4 = doROCCurve(iipt, doProject2DX(iipt, Num_IsolatedTauEff_4x4), DenumROC, UCTCandidateIso4x4, UCTCandidateIso4x4, 25, 7)
##    L1JetParticleROC.Draw("P")
#    UCTCandidateROC4x4.Draw("P")
#    UCTCandidateIsoROC4x4.Draw("Psame")
#    legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
#    legend_.SetFillColor(0)
#    legend_.SetBorderSize(0)
#    legend_.SetTextSize(.03)
##    legend_.AddEntry(L1JetParticleROC, "L1Tau or Jet", "lp")
#    legend_.AddEntry(UCTCandidateROC4x4, "UCTTau4x4", "lp")
#    legend_.AddEntry(UCTCandidateIsoROC4x4, "UCTIsoTau4x4", "lp")
#    canvas.SetLogy()
#    legend_.Draw()
#    AddCostumText(candidate)
#    canvas.SaveAs("PlotTau/out_" + candidate + "TauROC" + str(iipt) + ".pdf")
##
#
#






ResponseL1ExtraJet_0Res= FileRootEff.Get("demo/ResponseL1ExtraJet_0")
ResponseL1ExtraTau_0Res= FileRootEff.Get("demo/ResponseL1ExtraTau_0")
ResponseRelaxedTau_0Res= FileRootEff.Get("demo/ResponseRelaxedTau_0")
ResponseRelaxedIsoTau_0Res= FileRootEff.Get("demo/ResponseRelaxedIsoTau_0")
ResponseRelaxedTau_0_40GeVRes= FileRootEff.Get("demo/ResponseRelaxedTau_0_40GeV")
ResponseRelaxedIsoTau_0_40GeVRes= FileRootEff.Get("demo/ResponseRelaxedIsoTau_0_40GeV")
ResponseL1ExtraJet_1Res= FileRootEff.Get("demo/ResponseL1ExtraJet_1")
ResponseL1ExtraTau_1Res= FileRootEff.Get("demo/ResponseL1ExtraTau_1")
ResponseRelaxedTau_1Res= FileRootEff.Get("demo/ResponseRelaxedTau_1")
ResponseRelaxedIsoTau_1Res= FileRootEff.Get("demo/ResponseRelaxedIsoTau_1")
ResponseRelaxedTau_1_40GeVRes= FileRootEff.Get("demo/ResponseRelaxedTau_1_40GeV")
ResponseRelaxedIsoTau_1_40GeVRes= FileRootEff.Get("demo/ResponseRelaxedIsoTau_1_40GeV")
ResponseL1ExtraJet_10Res= FileRootEff.Get("demo/ResponseL1ExtraJet_10")
ResponseL1ExtraTau_10Res= FileRootEff.Get("demo/ResponseL1ExtraTau_10")
ResponseRelaxedTau_10Res= FileRootEff.Get("demo/ResponseRelaxedTau_10")
ResponseRelaxedIsoTau_10Res= FileRootEff.Get("demo/ResponseRelaxedIsoTau_10")
ResponseRelaxedTau_10_40GeVRes= FileRootEff.Get("demo/ResponseRelaxedTau_10_40GeV")
ResponseRelaxedIsoTau_10_40GeVRes= FileRootEff.Get("demo/ResponseRelaxedIsoTau_10_40GeV")



def doDrawPlots(A,B,C,D, Maxi):
    AddCostumMarker(A, 0, Maxi, 1.2, 20, 2, "Response", "Unit")
    A.GetXaxis().SetRangeUser(0,4)
    A.Draw("P")
    AddCostumMarker(B, 0, Maxi, 1.2, 29, 3, "Response", "Unit")
    B.Draw("Psame")
    AddCostumMarker(C, 0, Maxi, 1.2, 33, 4, "Response", "Unit")
    C.Draw("Psame")
    AddCostumMarker(D, 0, Maxi, 1.2, 25, 1, "Response", "Unit")
    D.Draw("Psame")
    AddCostumText(candidate)

def doDrawPlots2(A,B, Maxi):
    AddCostumMarker(A, 0, Maxi, 1.2, 20, 2, "Response", "Unit")
    A.GetXaxis().SetRangeUser(0,4)
    A.Draw("P")
    AddCostumMarker(B, 0, Maxi, 1.2, 29, 3, "Response", "Unit")
    B.Draw("Psame")
    AddCostumText(candidate)
    
    
#legend_ = TLegend(0.50, 100, 0.85, 200)
doDrawPlots(ResponseL1ExtraJet_0Res,ResponseL1ExtraTau_0Res,ResponseRelaxedTau_0Res,ResponseRelaxedIsoTau_0Res, 300)
legend_ = TLegend(0.30, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(ResponseL1ExtraJet_0Res, "L1ExtraJet_1prong0pizero", "lp")
legend_.AddEntry(ResponseL1ExtraTau_0Res, "L1ExtraTau_1prong0pizero", "lp")
legend_.AddEntry(ResponseRelaxedTau_0Res, "UCTRelaxedTau_1prong0pizero", "lp")
legend_.AddEntry(ResponseRelaxedIsoTau_0Res, "UCTIsoTau_1prong0pizero", "lp")
legend_.Draw()
canvas.SetLogy(0)
canvas.SaveAs("PlotTau/Resposne_1prong0pizero.pdf")

doDrawPlots(ResponseL1ExtraJet_1Res,ResponseL1ExtraTau_1Res,ResponseRelaxedTau_1Res,ResponseRelaxedIsoTau_1Res, 700)
legend_ = TLegend(0.30, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(ResponseL1ExtraJet_1Res, "L1ExtraJet_1prong1pizero", "lp")
legend_.AddEntry(ResponseL1ExtraTau_1Res, "L1ExtraTau_1prong1pizero", "lp")
legend_.AddEntry(ResponseRelaxedTau_1Res, "UCTRelaxedTau_1prong1pizero", "lp")
legend_.AddEntry(ResponseRelaxedIsoTau_1Res, "UCTIsoTau_1prong1pizero", "lp")
legend_.Draw()
canvas.SetLogy(0)
canvas.SaveAs("PlotTau/Resposne_1prong1pizero.pdf")

doDrawPlots(ResponseL1ExtraJet_10Res,ResponseL1ExtraTau_10Res,ResponseRelaxedTau_10Res,ResponseRelaxedIsoTau_10Res, 300)
legend_ = TLegend(0.30, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(ResponseL1ExtraJet_10Res, "L1ExtraJet_3prongso", "lp")
legend_.AddEntry(ResponseL1ExtraTau_10Res, "L1ExtraTau_3prongso", "lp")
legend_.AddEntry(ResponseRelaxedTau_10Res, "UCTRelaxedTau_3prongso", "lp")
legend_.AddEntry(ResponseRelaxedIsoTau_10Res, "UCTIsoTau_3prongso", "lp")
legend_.Draw()
canvas.SetLogy(0)
canvas.SaveAs("PlotTau/Resposne_3prongso.pdf")


doDrawPlots(ResponseRelaxedTau_10Res,ResponseRelaxedIsoTau_10Res,ResponseRelaxedTau_10_40GeVRes,ResponseRelaxedIsoTau_10_40GeVRes, 300)
legend_ = TLegend(0.30, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(ResponseRelaxedTau_10_40GeVRes, "UCTRelaxedTau_3prongso_40GeV", "lp")
legend_.AddEntry(ResponseRelaxedIsoTau_10_40GeVRes, "UCTIsoTau_3prongso_40GeV", "lp")
legend_.AddEntry(ResponseRelaxedTau_10Res, "UCTRelaxedTau_3prongso_20GeV", "lp")
legend_.AddEntry(ResponseRelaxedIsoTau_10Res, "UCTIsoTau_3prongso_20GeV", "lp")
legend_.Draw()
canvas.SetLogy(0)
canvas.SaveAs("PlotTau/Resposne_3prongso40_20.pdf")



doDrawPlots(ResponseRelaxedTau_0Res,ResponseRelaxedIsoTau_0Res,ResponseRelaxedTau_0_40GeVRes,ResponseRelaxedIsoTau_0_40GeVRes, 300)
legend_ = TLegend(0.30, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(ResponseRelaxedTau_0_40GeVRes, "UCTRelaxedTau_1prong0pizero_40GeV", "lp")
legend_.AddEntry(ResponseRelaxedIsoTau_0_40GeVRes, "UCTIsoTau_1prong0pizero_40GeV", "lp")
legend_.AddEntry(ResponseRelaxedTau_0Res, "UCTRelaxedTau_1prong0pizero_20GeV", "lp")
legend_.AddEntry(ResponseRelaxedIsoTau_0Res, "UCTIsoTau_1prong0pizero_20GeV", "lp")
legend_.Draw()
canvas.SetLogy(0)
canvas.SaveAs("PlotTau/Resposne_1prong0pizero40_20.pdf")


doDrawPlots(ResponseRelaxedTau_1Res,ResponseRelaxedIsoTau_1Res,ResponseRelaxedTau_1_40GeVRes,ResponseRelaxedIsoTau_1_40GeVRes, 700)
legend_ = TLegend(0.30, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(ResponseRelaxedTau_1_40GeVRes, "UCTRelaxedTau_1prong1pizero_40GeV", "lp")
legend_.AddEntry(ResponseRelaxedIsoTau_1_40GeVRes, "UCTIsoTau_1prong1pizero_40GeV", "lp")
legend_.AddEntry(ResponseRelaxedTau_1Res, "UCTRelaxedTau_1prong1pizero_20GeV", "lp")
legend_.AddEntry(ResponseRelaxedIsoTau_1Res, "UCTIsoTau_1prong1pizero_20GeV", "lp")
legend_.Draw()
canvas.SetLogy(0)
canvas.SaveAs("PlotTau/Resposne_1prong1pizero40_20.pdf")




