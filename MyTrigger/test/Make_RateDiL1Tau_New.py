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
#    t.DrawLatex(0.6, .52, "PU40bx25")
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
    Hist.GetXaxis().SetRangeUser(0,100)
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
def doCommulativeRate(num, marStyle, marColor, type):
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
    AddCostumMarker(commul, 0.001, 1.2, 1.1, marStyle, marColor, "L1 #tau_{pT} [GeV]", type)
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

FileRootEff = TFile("efficiency_diTau_v5.root", "OPEN")
FileRootRate = TFile("rate_diTau_v5.root", "OPEN")
#FileRootRate = TFile("TOTAL.root", "OPEN")



DenumEff = FileRootEff.Get("demo/offLineTauEff")
DenumROC = FileRootEff.Get("demo/offLineTauROC")

Num_l1extraEff = FileRootEff.Get("demo/Eff2D_Num_l1extraParticles")
Num_IsolatedTauEff_4x4 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTau")
Num_RelaxedTauEff_4x4 = FileRootEff.Get("demo/Eff2D_Num_RelaxedTau")

L1JetParticle = FileRootRate.Get("demo/rate_L1JetParticle");
UCTCandidate4x4 = FileRootRate.Get("demo/rate_UCTCandidate4x4");
UCTCandidateIso4x4 = FileRootRate.Get("demo/rate_UCTCandidateIso4x4");


offLineTauROC = FileRootRate.Get("demo/offLineTauROC");
l1extraParticlesROC = FileRootRate.Get("demo/l1extraParticlesROC");
RelaxedTauROC = FileRootRate.Get("demo/RelaxedTauROC");
RelaxedTauROC4x4 = FileRootRate.Get("demo/RelaxedTauROC4x4");
IsolatedTauROC = FileRootRate.Get("demo/IsolatedTauROC");
IsolatedTauROC4x4 = FileRootRate.Get("demo/IsolatedTauROC4x4");

offLineTauEff = FileRootRate.Get("demo/offLineTauEff");
l1extraParticlesEff = FileRootRate.Get("demo/l1extraParticlesEff");
RelaxedTauEff = FileRootRate.Get("demo/RelaxedTauEff");
IsolatedTauEff = FileRootRate.Get("demo/IsolatedTauEff");

rate_L1JetParticle  = FileRootRate.Get("demo/rate_L1JetParticle");
rate_UCTTauNoIsoNoEta = FileRootRate.Get("demo/rate_UCTTauNoIsoNoEta");
rate_UCTTauNoIso = FileRootRate.Get("demo/rate_UCTTauNoIso");
rate_UCTTauIsoNoEta = FileRootRate.Get("demo/rate_UCTTauIsoNoEta");
rate_UCTTauIso = FileRootRate.Get("demo/rate_UCTTauIso");
rate_UCTTauIso1p0 = FileRootRate.Get("demo/rate_UCTTauIso1p0");
rate_UCTTauIso0p5 = FileRootRate.Get("demo/rate_UCTTauIso0p5");
rate_UCTTauIso0p3 = FileRootRate.Get("demo/rate_UCTTauIso0p3");
rate_UCTTauIso0p25 = FileRootRate.Get("demo/rate_UCTTauIso0p25");
rate_UCTTauIso0p2 = FileRootRate.Get("demo/rate_UCTTauIso0p2");
rate_UCTTauIso0p1 = FileRootRate.Get("demo/rate_UCTTauIso0p1");

Eff2D_Num_l1extraParticles = FileRootEff.Get("demo/Eff2D_Num_l1extraParticles");
Eff2D_Num_RelaxedTau = FileRootEff.Get("demo/Eff2D_Num_RelaxedTau");
Eff2D_Num_IsolatedTauNoEta = FileRootEff.Get("demo/Eff2D_Num_IsolatedTauNoEta");
Eff2D_Num_IsolatedTau = FileRootEff.Get("demo/Eff2D_Num_IsolatedTau");
Eff2D_Num_IsolatedTau1p0 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTau1p0");
Eff2D_Num_IsolatedTau0p5 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTau0p5");
Eff2D_Num_IsolatedTau0p3 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTau0p3");
Eff2D_Num_IsolatedTau0p25 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTau0p25");
Eff2D_Num_IsolatedTau0p2 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTau0p2");
Eff2D_Num_IsolatedTau0p1 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTau0p1");







#
#IsolatedTauEff10_4x4 = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 20, 21, 2)
#IsolatedTauEff15_4x4 = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 25, 22, 3)
#IsolatedTauEff20_4x4 = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 30, 23, 4)
#IsolatedTauEff25_4x4 = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 35, 24, 6)
#IsolatedTauEff10_4x4.Draw("PAE")
#IsolatedTauEff15_4x4.Draw("Psame")
#IsolatedTauEff20_4x4.Draw("Psame")
#IsolatedTauEff25_4x4.Draw("Psame")
#legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
#legend_.SetFillColor(0)
#legend_.SetBorderSize(0)
#legend_.SetTextSize(.03)
#legend_.AddEntry(IsolatedTauEff10_4x4, "UCTIsoTau 20GeV", "lp")
#legend_.AddEntry(IsolatedTauEff15_4x4, "UCTIsoTau 25GeV", "lp")
#legend_.AddEntry(IsolatedTauEff20_4x4, "UCTIsoTau 30GeV", "lp")
#legend_.AddEntry(IsolatedTauEff25_4x4, "UCTIsoTau 35GeV", "lp")
#legend_.Draw()
#AddCostumText(candidate)
#canvas.SaveAs("PlotTau/out_" + candidate + "TauEfficiencyUCTTau4x4DifferentL1Pt.pdf")



#
#l1extraEff = doRatio2D(Num_l1extraEff, DenumEff, 25, 21, 2)
#RelaxedTauEff = doRatio2D(Num_RelaxedTauEff_4x4, DenumEff, 25, 22, 3)
#IsolatedTauEff = doRatio2D(Num_IsolatedTauEff_4x4, DenumEff, 25, 23, 4)
#l1extraEff.Draw("PAE")
#RelaxedTauEff.Draw("Psame")
#IsolatedTauEff.Draw("Psame")
#legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
#legend_.SetFillColor(0)
#legend_.SetBorderSize(0)
#legend_.SetTextSize(.03)
#legend_.AddEntry(l1extraEff, "L1tau or jet", "lp")
#legend_.AddEntry(RelaxedTauEff, "UCTTau", "lp")
#legend_.AddEntry(IsolatedTauEff, "UCTIsoTau", "lp")
#legend_.Draw()
#AddCostumText(candidate)
#canvas.SaveAs("PlotTau/out_" + candidate + "TauEfficiencyDifferentL1Algo.pdf")

#
ptL1 = [1,40,70]
for iipt in ptL1:
    l1extraROC = doCommulative2D(iipt, Num_l1extraEff, DenumROC, 19, 1, "Efficiency")
#    RelaxedTau4x4ROC = doCommulative2D(iipt, Num_RelaxedTauEff_4x4, DenumROC, 24, 6, "Efficiency")
#    IsolatedTau4x4ROC = doCommulative2D(iipt, Num_IsolatedTauEff_4x4, DenumROC, 25, 2, "Efficiency")
#    Eff2D_Num_IsolatedTauNoEta_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTauNoEta, DenumROC, 20, 3, "Efficiency")
#    Eff2D_Num_IsolatedTau_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTau, DenumROC, 21, 4, "Efficiency")
    Eff2D_Num_IsolatedTau1p0_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTau1p0, DenumROC, 22, 5, "Efficiency")
    Eff2D_Num_IsolatedTau0p5_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTau0p5, DenumROC, 23, 6, "Efficiency")
    Eff2D_Num_IsolatedTau0p3_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTau0p3, DenumROC, 24, 7, "Efficiency")
    Eff2D_Num_IsolatedTau0p25_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTau0p25, DenumROC, 34, 8, "Efficiency")
    Eff2D_Num_IsolatedTau0p2_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTau0p2, DenumROC, 17, 9, "Efficiency")
    Eff2D_Num_IsolatedTau0p1_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTau0p1, DenumROC, 18, 11, "Efficiency")


    l1extraROC.Draw("P")
#    RelaxedTau4x4ROC.Draw("Psame")
#    IsolatedTau4x4ROC.Draw("Psame")
#    Eff2D_Num_IsolatedTauNoEta_.Draw("Psame")
#    Eff2D_Num_IsolatedTau_.Draw("Psame")
    Eff2D_Num_IsolatedTau1p0_.Draw("Psame")
    Eff2D_Num_IsolatedTau0p5_.Draw("Psame")
    Eff2D_Num_IsolatedTau0p3_.Draw("Psame")
    Eff2D_Num_IsolatedTau0p25_.Draw("Psame")
    Eff2D_Num_IsolatedTau0p2_.Draw("Psame")
    Eff2D_Num_IsolatedTau0p1_.Draw("Psame")

    legend_ = TLegend(0.70, 0.58, 0.85, 0.9)
    legend_.SetFillColor(0)
    legend_.SetBorderSize(0)
    legend_.SetTextSize(.03)
    legend_.AddEntry(l1extraROC, "L1tau or jet", "lp")
#    legend_.AddEntry(RelaxedTau4x4ROC, "UCTTau4x4", "lp")
#    legend_.AddEntry(IsolatedTau4x4ROC, "UCTIsoTau4x4", "lp")
#    Eff2D_Num_IsolatedTauNoEta_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTauNoEta, DenumROC, 20, 3, "Efficiency")
#    Eff2D_Num_IsolatedTau_ = doCommulative2D(iipt,Eff2D_Num_IsolatedTau, DenumROC, 21, 4, "Efficiency")
    legend_.AddEntry(Eff2D_Num_IsolatedTau1p0_, "1p0", "lp")
    legend_.AddEntry(Eff2D_Num_IsolatedTau0p5_, "0p5", "lp")
    legend_.AddEntry(Eff2D_Num_IsolatedTau0p3_, "0p3", "lp")
    legend_.AddEntry(Eff2D_Num_IsolatedTau0p25_, "0p25", "lp")
    legend_.AddEntry(Eff2D_Num_IsolatedTau0p2_, "0p2", "lp")
    legend_.AddEntry(Eff2D_Num_IsolatedTau0p1_, "0p1", "lp")

    
    legend_.Draw()
    AddCostumText2(candidate,iipt)
    canvas.SaveAs("PlotTau/out_" + candidate + "TauEfficiencyCumulative2D" + str(iipt) + ".pdf")





#L1JetParticleCum = doCommulativeRate(L1JetParticle, L1JetParticle, 21, 2, "L1 Rate")
rate_L1JetParticle_ = doCommulativeRate(rate_L1JetParticle, 24, 6, "L1 Rate Reduction")
rate_UCTTauNoIsoNoEta_ = doCommulativeRate(rate_UCTTauNoIsoNoEta, 25, 7, "L1 Rate Reduction")
rate_UCTTauNoIso_ = doCommulativeRate(rate_UCTTauNoIso, 20, 1, "L1 Rate Reduction")
rate_UCTTauIsoNoEta_ = doCommulativeRate(rate_UCTTauIsoNoEta, 32, 2, "L1 Rate Reduction")
rate_UCTTauIso_ = doCommulativeRate(rate_UCTTauIso, 22, 3, "L1 Rate Reduction")
rate_UCTTauIso1p0_ = doCommulativeRate(rate_UCTTauIso1p0, 33, 4, "L1 Rate Reduction")
rate_UCTTauIso0p5_ = doCommulativeRate(rate_UCTTauIso0p5, 26, 5, "L1 Rate Reduction")
rate_UCTTauIso0p3_ = doCommulativeRate(rate_UCTTauIso0p3, 27, 9, "L1 Rate Reduction")
rate_UCTTauIso0p25_ = doCommulativeRate(rate_UCTTauIso0p25, 27, 8, "L1 Rate Reduction")
rate_UCTTauIso0p2_ = doCommulativeRate(rate_UCTTauIso0p2, 29, 13, "L1 Rate Reduction")
rate_UCTTauIso0p1_ = doCommulativeRate(rate_UCTTauIso0p1, 30, 11, "L1 Rate Reduction")

#L1JetParticleCum.Draw("P")
rate_L1JetParticle_.Draw("P")
#rate_UCTTauNoIsoNoEta_.Draw("Psame")
#rate_UCTTauNoIso_.Draw("Psame")
#rate_UCTTauIsoNoEta_.Draw("Psame")
#rate_UCTTauIso_.Draw("Psame")
rate_UCTTauIso1p0_.Draw("Psame")
rate_UCTTauIso0p5_.Draw("Psame")
rate_UCTTauIso0p3_.Draw("Psame")
rate_UCTTauIso0p25_.Draw("Psame")
rate_UCTTauIso0p2_.Draw("Psame")
rate_UCTTauIso0p1_.Draw("Psame")
legend_ = TLegend(0.50, 0.58, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
#legend_.AddEntry(L1JetParticleCum, "L1Tau or Jet", "lp")
legend_.AddEntry(rate_L1JetParticle_, "L1tau || Jet", "lp")
#legend_.AddEntry(rate_UCTTauNoIsoNoEta_, "NoIsoNoEta", "lp")
#legend_.AddEntry(rate_UCTTauNoIso_, "NoIso", "lp")
#legend_.AddEntry(rate_UCTTauIsoNoEta_," IsoNoEta", "lp")
#legend_.AddEntry(rate_UCTTauIso_," Iso default ", "lp")
legend_.AddEntry(rate_UCTTauIso1p0_," Iso1p0", "lp")
legend_.AddEntry(rate_UCTTauIso0p5_," Iso0p5", "lp")
legend_.AddEntry(rate_UCTTauIso0p3_," Iso0p3", "lp")
legend_.AddEntry(rate_UCTTauIso0p25_," Iso0p25", "lp")
legend_.AddEntry(rate_UCTTauIso0p2_," Iso0p2", "lp")
legend_.AddEntry(rate_UCTTauIso0p1_," Iso0p1", "lp")
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




