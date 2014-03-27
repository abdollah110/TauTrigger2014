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
if not (candidate == "Mu" or candidate == "Ele"):
    raise "please select either -Mu- or -Ele-"
     


def AddCostumText():
    t = TLatex()
    t.SetNDC()
    t.SetTextFont(62)
    t.SetTextAlign(12)
    t.SetTextSize(0.025)
    t.DrawLatex(0.1, .92, "CMS Preliminary")
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
    OneDNum = TH1F("NewNum", "", 100, 0, 100)
    for ii in range(1, 100):
        ValDenum = 0
        ValNum = 0
        for jj in range(cut, 100):
            ValNum = ValNum + num.GetBinContent(ii, jj)
        OneDNum.SetBinContent(ii, ValNum)
    bins = array('d', [20, 25, 30, 35, 40, 45, 50, 55, 70, 100])
    num_R = OneDNum.Rebin(len(bins)-1, "Hinm", bins)
    denum_R = denum.Rebin(len(bins)-1, "Hin", bins)
    ratio = ROOT.TGraphAsymmErrors(num_R, denum_R, "")
    AddCostumMarker(ratio, 0.0, 1.2, 1.2, marStyle, marColor, "offLine #tau_{pT} [GeV]", "Efficiency")
    ratio.SetLineColor(marColor)
    ratio.SetLineWidth(2)
    return ratio

def doCommulative(num, denum, marStyle, marColor, type):
    commul = TH1F(str(num), "", 100, 0, 100)
    for ii in range(1, 100):
        commul.SetBinContent(ii + 1, (num.Integral(ii, 100) * 1.0) / denum.GetEntries());
    AddCostumMarker(commul, 0.001, 1.2, 1.2, marStyle, marColor, "L1 #tau_{pT} [GeV]", type)
    return commul

def doCommulative2D(cut, num, denum, marStyle, marColor, type):
    commul = TH1F(str(num) + str(cut), "", 100, 0, 100)
    for ii in range(1, 100):
        commul.SetBinContent(ii + 1, (num.Integral(cut, 100, ii, 100) * 1.0) / denum.Integral(cut, 100));
    AddCostumMarker(commul, 0.001, 1.2, 1.2, marStyle, marColor, "L1 #tau_{pT} [GeV]", type)
    return commul

def doROCCurve(cut, num1, denum1, num2, denum2, marStyle, marColor):
    rocCurve = TH2F(str(num1) + str(cut), "", 120, 0, 1.2, 120, 0, 1.2)
    for ii in range(1, 100):
        if (ii % 10 == 0): print ii, "\t"
        for jj in range (1, 100):
            for kk in range (1, 100):
                if (math.floor((num1.Integral(ii, 100) * 1.0) * 100 / denum1.Integral(cut, 100)) == jj and math.floor((1 - ((num2.Integral(ii, 100) * 1.0) / denum2.GetEntries())) * 100) == kk):
                    rocCurve.SetBinContent(jj + 1, kk + 1, 10)
    AddCostumMarker(rocCurve, 0.001, 1.2, 1.2, marStyle, marColor, "Efficiency", "1-Rate")
    return rocCurve

def doProject2DX(cut, num):
    projectedHist = TH1F(str(num), "", 100, 0, 100)
    for ii in range(1, 100):
        Val = 0
        for jj in range(cut, 100):
            Val = Val + num.GetBinContent(jj, ii)
        projectedHist.SetBinContent(ii, Val)
    return projectedHist
            

##########################################################################################################
##########################################################################################################
######                                                                                              ######
##########################################################################################################
##########################################################################################################

FileRootEff = TFile(candidate + "Tau_L1" + candidate + "_efficiency_40.root", "OPEN")
FileRootRate = TFile(candidate + "Tau_L1" + candidate + "_rate.root", "OPEN")

DenumEff = FileRootEff.Get("demo/offLineTauEff")
DenumROC = FileRootEff.Get("demo/offLineTauROC")

Num_l1extraEff = FileRootEff.Get("demo/Eff2D_Num_l1extraParticles")
Num_IsolatedTauEff_2x1 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTauUnpacked")
Num_IsolatedTauEff_4x4 = FileRootEff.Get("demo/Eff2D_Num_IsolatedTauUnpacked4x4")
Num_RelaxedTauEff_2x1 = FileRootEff.Get("demo/Eff2D_Num_RelaxedTauUnpacked")
Num_RelaxedTauEff_4x4 = FileRootEff.Get("demo/Eff2D_Num_RelaxedTauUnpacked4x4")

L1JetParticle = FileRootRate.Get("demo/rate_L1JetParticle");
UCTCandidate = FileRootRate.Get("demo/rate_UCTCandidate");
UCTCandidateIso = FileRootRate.Get("demo/rate_UCTCandidateIso");
UCTCandidate4x4 = FileRootRate.Get("demo/rate_UCTCandidate4x4");
UCTCandidateIso4x4 = FileRootRate.Get("demo/rate_UCTCandidateIso4x4");


#Num_RelaxedTauROC2D = FileRootEff.Get("demo/Eff2D_Num_RelaxedTauUnpacked")
#Num_RelaxedTauEff = FileRootEff.Get("demo/Eff2D_Num_RelaxedTauUnpacked")
#Num_RelaxedTauROC4x42D = FileRootEff.Get("demo/Eff2D_Num_RelaxedTauUnpacked4x4")
#Num_l1extraROC = FileRootEff.Get("demo/Eff2D_Num_l1extraParticles")
#Num_IsolatedTauROC2D = FileRootEff.Get("demo/Eff2D_Num_IsolatedTauUnpacked")


RelaxedTauEff10_2x1 = doRatio2D(Num_RelaxedTauEff_2x1, DenumEff, 10, 21, 2)
RelaxedTauEff15_2x1 = doRatio2D(Num_RelaxedTauEff_2x1, DenumEff, 15, 22, 3)
RelaxedTauEff20_2x1 = doRatio2D(Num_RelaxedTauEff_2x1, DenumEff, 20, 23, 4)
RelaxedTauEff25_2x1 = doRatio2D(Num_RelaxedTauEff_2x1, DenumEff, 25, 24, 6)
RelaxedTauEff10_2x1.Draw("PAE")
RelaxedTauEff15_2x1.Draw("Psame")
RelaxedTauEff20_2x1.Draw("Psame")
RelaxedTauEff25_2x1.Draw("Psame")
legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(RelaxedTauEff10_2x1, "UCTTau2x1 10GeV", "lp")
legend_.AddEntry(RelaxedTauEff15_2x1, "UCTTau2x1 15GeV", "lp")
legend_.AddEntry(RelaxedTauEff20_2x1, "UCTTau2x1 20GeV", "lp")
legend_.AddEntry(RelaxedTauEff25_2x1, "UCTTau2x1 25GeV", "lp")
legend_.Draw()
AddCostumText()
canvas.SaveAs("Plot/out_" + candidate + "TauEfficiencyUCTTau2x1DifferentL1Pt.pdf")


RelaxedTauEff10_4x4 = doRatio2D(Num_RelaxedTauEff_4x4, DenumEff, 10, 21, 2)
RelaxedTauEff15_4x4 = doRatio2D(Num_RelaxedTauEff_4x4, DenumEff, 15, 22, 3)
RelaxedTauEff20_4x4 = doRatio2D(Num_RelaxedTauEff_4x4, DenumEff, 20, 23, 4)
RelaxedTauEff25_4x4 = doRatio2D(Num_RelaxedTauEff_4x4, DenumEff, 25, 24, 6)
RelaxedTauEff10_4x4.Draw("PAE")
RelaxedTauEff15_4x4.Draw("Psame")
RelaxedTauEff20_4x4.Draw("Psame")
RelaxedTauEff25_4x4.Draw("Psame")
legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(RelaxedTauEff10_4x4, "UCTTau4x4 10GeV", "lp")
legend_.AddEntry(RelaxedTauEff15_4x4, "UCTTau4x4 15GeV", "lp")
legend_.AddEntry(RelaxedTauEff20_4x4, "UCTTau4x4 20GeV", "lp")
legend_.AddEntry(RelaxedTauEff25_4x4, "UCTTau4x4 25GeV", "lp")
legend_.Draw()
AddCostumText()
canvas.SaveAs("Plot/out_" + candidate + "TauEfficiencyUCTTau4x4DifferentL1Pt.pdf")




l1extraEff = doRatio2D(Num_l1extraEff, DenumEff, 15, 21, 2)
RelaxedTauEff = doRatio2D(Num_RelaxedTauEff_2x1, DenumEff, 15, 22, 3)
IsolatedTauEff = doRatio2D(Num_IsolatedTauEff_2x1, DenumEff, 15, 23, 4)
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
AddCostumText()
canvas.SaveAs("Plot/out_" + candidate + "TauEfficiencyDifferentL1Algo.pdf")


ptL1 = [20, 40]
for iipt in ptL1:
    l1extraROC = doCommulative2D(iipt, Num_l1extraEff, DenumROC, 21, 2, "Efficiency")
    RelaxedTauROC = doCommulative2D(iipt, Num_RelaxedTauEff_2x1, DenumROC, 22, 3, "Efficiency")
    IsolatedTauROC = doCommulative2D(iipt, Num_IsolatedTauEff_2x1, DenumROC, 23, 4, "Efficiency")
    RelaxedTau4x4ROC = doCommulative2D(iipt, Num_RelaxedTauEff_4x4, DenumROC, 24, 6, "Efficiency")
    IsolatedTau4x4ROC = doCommulative2D(iipt, Num_IsolatedTauEff_4x4, DenumROC, 25, 7, "Efficiency")
    l1extraROC.Draw("P")
    RelaxedTauROC.Draw("Psame")
    IsolatedTauROC.Draw("Psame")
    RelaxedTau4x4ROC.Draw("Psame")
    IsolatedTau4x4ROC.Draw("Psame")
    legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
    legend_.SetFillColor(0)
    legend_.SetBorderSize(0)
    legend_.SetTextSize(.03)
    legend_.AddEntry(l1extraROC, "L1tau or jet", "lp")
    legend_.AddEntry(RelaxedTauROC, "UCTTau2x1", "lp")
    legend_.AddEntry(IsolatedTauROC, "UCTIsoTau2x1", "lp")
    legend_.AddEntry(RelaxedTau4x4ROC, "UCTTau4x4", "lp")
    legend_.AddEntry(IsolatedTau4x4ROC, "UCTIsoTau4x4", "lp")
    legend_.Draw()
    AddCostumText()
    canvas.SaveAs("Plot/out_" + candidate + "TauEfficiencyCumulative2D" + str(iipt) + ".pdf")





L1JetParticleCum = doCommulative(L1JetParticle, L1JetParticle, 21, 2, "L1 Rate")
UCTCandidateCum = doCommulative(UCTCandidate, UCTCandidate, 22, 3, "L1 Rate")
UCTCandidateIsoCum = doCommulative(UCTCandidateIso, UCTCandidateIso, 23, 4, "L1 Rate")
UCTCandidateCum4x4 = doCommulative(UCTCandidate4x4, UCTCandidate4x4, 24, 6, "L1 Rate")
UCTCandidateIsoCum4x4 = doCommulative(UCTCandidateIso4x4, UCTCandidateIso4x4, 25, 7, "L1 Rate")
L1JetParticleCum.Draw("P")
UCTCandidateCum.Draw("Psame")
UCTCandidateIsoCum.Draw("Psame")
UCTCandidateCum4x4.Draw("Psame")
UCTCandidateIsoCum4x4.Draw("Psame")
legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(L1JetParticleCum, "L1Tau or Jet", "lp")
legend_.AddEntry(UCTCandidateCum, "UCTTau2x1", "lp")
legend_.AddEntry(UCTCandidateIsoCum, "UCTIsoTau2x1", "lp")
legend_.AddEntry(UCTCandidateCum4x4, "UCTTau4x4", "lp")
legend_.AddEntry(UCTCandidateIsoCum4x4, "UCTIsoTau4x4", "lp")
canvas.SetLogy()
legend_.Draw()
AddCostumText()
canvas.SaveAs("Plot/out_" + candidate + "TauRateCumulative.pdf")


#ptL1 = [20, 60]
#for iipt in ptL1:
#    L1JetParticleROC = doROCCurve(iipt, doProject2DX(iipt, Num_l1extraEff), DenumROC, L1JetParticle, L1JetParticle, 21, 2)
#    UCTCandidateROC = doROCCurve(iipt, doProject2DX(iipt, Num_RelaxedTauEff_2x1), DenumROC, UCTCandidate, UCTCandidate, 22, 3)
#    UCTCandidateIsoROC = doROCCurve(iipt, doProject2DX(iipt, Num_IsolatedTauEff_2x1), DenumROC, UCTCandidateIso, UCTCandidateIso, 23, 4)
#    UCTCandidateROC4x4 = doROCCurve(iipt, doProject2DX(iipt, Num_RelaxedTauEff_4x4), DenumROC, UCTCandidate4x4, UCTCandidate4x4, 24, 6)
#    UCTCandidateIsoROC4x4 = doROCCurve(iipt, doProject2DX(iipt, Num_IsolatedTauEff_4x4), DenumROC, UCTCandidateIso4x4, UCTCandidateIso4x4, 25, 7)
#    L1JetParticleROC.Draw("P")
#    UCTCandidateROC.Draw("Psame")
#    UCTCandidateIsoROC.Draw("Psame")
#    UCTCandidateROC4x4.Draw("Psame")
#    UCTCandidateIsoROC4x4.Draw("Psame")
#    legend_ = TLegend(0.50, 0.78, 0.85, 0.9)
#    legend_.SetFillColor(0)
#    legend_.SetBorderSize(0)
#    legend_.SetTextSize(.03)
#    legend_.AddEntry(L1JetParticleROC, "L1Tau or Jet", "lp")
#    legend_.AddEntry(UCTCandidateROC, "UCTTau2x1", "lp")
#    legend_.AddEntry(UCTCandidateIsoROC, "UCTIsoTau2x1", "lp")
#    legend_.AddEntry(UCTCandidateROC4x4, "UCTTau4x4", "lp")
#    legend_.AddEntry(UCTCandidateIsoROC4x4, "UCTIsoTau4x4", "lp")
#    canvas.SetLogy(0)
#    legend_.Draw()
#    AddCostumText()
#    canvas.SaveAs("Plot/out_" + candidate + "TauROC" + str(iipt) + ".pdf")
#


