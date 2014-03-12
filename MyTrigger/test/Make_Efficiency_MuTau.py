#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__ = "abdollahmohammadi"
__date__ = "$Mar 6, 2014 12:15:11 PM$"


from array import array
import math

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
canvas.SetName("")
canvas.SetBorderMode(0)
canvas.SetBorderSize(2)
canvas.SetFrameBorderMode(0)
canvas.SetFrameLineWidth(2)
canvas.SetFrameBorderMode(0)
canvas.SetGridx(10)
canvas.SetGridy(10)




def doRatio2D(num, denum, cut, marStyle, marColor):
    OneDNum = TH1F("NewNum", "", 100, 0, 100)
#    OneDDenum = TH1F("NewDenum", "", 100, 0, 100)
    for ii in range(1, 100):
        ValDenum = 0
        ValNum = 0
        for jj in range(cut, 100):
            ValNum = ValNum + num.GetBinContent(ii, jj)
        OneDNum.SetBinContent(ii, ValNum)
#        for jj in range(0, 100):
#            ValDenum = ValDenum + denum.GetBinContent(ii, jj)
#        OneDDenum.SetBinContent(ii, ValDenum)
#        OneDNum.Fill(ii, ValNum)
#        OneDDenum.Fill(ii, ValDenum)
#        print ii, ValNum, ValDenum
    bins = array('d', [20, 25, 30, 35, 40, 45, 50, 55, 70, 100])
    num_R = OneDNum.Rebin(len(bins)-1, "Hinm", bins)
    denum_R = denum.Rebin(len(bins)-1, "Hin", bins)
    ratio = ROOT.TGraphAsymmErrors(num_R, denum_R, "")
    ratio.SetMinimum(0.0)
    ratio.SetMaximum(1.2)
    ratio.SetMarkerSize(1.2);
    ratio.SetMarkerStyle(marStyle);
    ratio.SetMarkerColor(marColor);
    ratio.SetLineColor(marColor);
    ratio.SetLineWidth(2);
    ratio.GetXaxis().SetTitle("offLine #tau_{pT} [GeV]")
    ratio.GetYaxis().SetTitle("Efficiency")
    return ratio

#def doRatio(num, denum, marStyle, marColor):
#    bins = array('d', [20, 25, 30, 35, 40, 45, 50, 55, 70, 100])
#    num_R = num.Rebin(len(bins)-1, "Hinm", bins)
#    denum_R = denum.Rebin(len(bins)-1, "Hin", bins)
#    ratio = ROOT.TGraphAsymmErrors(num_R, denum_R, "")
#    ratio.SetMinimum(0.0)
#    ratio.SetMaximum(1.2)
#    ratio.SetMarkerSize(1.2);
#    ratio.SetMarkerStyle(marStyle);
#    ratio.SetMarkerColor(marColor);
#    ratio.SetLineColor(marColor);
#    ratio.SetLineWidth(2);
#    ratio.GetXaxis().SetTitle("#tau_{pT} [GeV]")
#    ratio.GetYaxis().SetTitle("Efficiency")
#    return ratio


def doCommulative(num, denum, marStyle, marColor,type):
    commul = TH1F(str(num), "", 100, 0, 100)
    for ii in range(1, 100):
        commul.SetBinContent(ii + 1, (num.Integral(ii, 100) * 1.0) / denum.GetEntries());
    commul.SetMinimum(0.001)
    commul.SetMaximum(1.2)
    commul.SetMarkerSize(1.2);
    commul.SetMarkerStyle(marStyle);
    commul.SetMarkerColor(marColor);
    commul.GetXaxis().SetTitle("L1 #tau_{pT} [GeV]")
    commul.GetYaxis().SetTitle(type)
    return commul

def doROCCurve(num1, denum1, num2, denum2, marStyle, marColor):
    rocCurve = TH2F(str(num1), "", 120, 0, 1.2, 120, 0, 1.2)
    for ii in range(1, 100):
        for jj in range (1, 100):
            for kk in range (1, 100):
                if (math.floor((num1.Integral(ii, 100) * 1.0) * 100 / denum1.GetEntries()) == jj and math.floor((1 - ((num2.Integral(ii, 100) * 1.0) / denum2.GetEntries())) * 100) == kk):
                    rocCurve.SetBinContent(jj + 1, kk + 1, 10);
    rocCurve.SetMinimum(0.001)
    rocCurve.SetMaximum(2)
    rocCurve.SetMarkerSize(1.1);
    rocCurve.SetMarkerStyle(marStyle);
    rocCurve.SetMarkerColor(marColor);
    rocCurve.GetXaxis().SetTitle("Efficiency")
    rocCurve.GetYaxis().SetTitle("1-Rate")
    return rocCurve



#FileRootEff = TFile("muTau_L1Mu_efficiency.root", "OPEN")
#DenumEff = FileRootEff.Get("demo/offLineTauEff")
#Num_l1extraEff = FileRootEff.Get("demo/l1extraParticlesEff")
#Num_RelaxedTauEff = FileRootEff.Get("demo/RelaxedTauUnpackedEff")
#Num_IsolatedTauEff = FileRootEff.Get("demo/IsolatedTauUnpackedEff")
#l1extraEff = doRatio(Num_l1extraEff, DenumEff, 23, 2)
#RelaxedTauEff = doRatio(Num_RelaxedTauEff, DenumEff, 21, 3)
#IsolatedTauEff = doRatio(Num_IsolatedTauEff, DenumEff, 24, 4)
#l1extraEff.Draw("PAE")
#RelaxedTauEff.Draw("Psame")
#IsolatedTauEff.Draw("Psame")
#legend_ = TLegend(0.60, 0.78, 0.9, 0.9)
#legend_.SetFillColor(0)
#legend_.SetBorderSize(0)
#legend_.SetTextSize(.03)
#legend_.AddEntry(l1extraEff, "l1extra", "lp")
#legend_.AddEntry(RelaxedTauEff, "UCTTau", "lp")
#legend_.AddEntry(IsolatedTauEff, "IsoUCTTau", "lp")
#legend_.Draw()
#canvas.SaveAs("MuTauEfficiency.pdf")

FileRootEff = TFile("muTau_L1Mu_efficiency.root", "OPEN")
DenumEff = FileRootEff.Get("demo/offLineTauEff")
Num_l1extraEff = FileRootEff.Get("demo/Eff2D_Num_l1extraParticles")
Num_RelaxedTauEff = FileRootEff.Get("demo/Eff2D_Num_RelaxedTauUnpacked")
Num_IsolatedTauEff = FileRootEff.Get("demo/Eff2D_Num_IsolatedTauUnpacked")
RelaxedTauEff10 = doRatio2D(Num_RelaxedTauEff, DenumEff, 10, 21, 2)
RelaxedTauEff15 = doRatio2D(Num_RelaxedTauEff, DenumEff, 15, 22, 3)
RelaxedTauEff20 = doRatio2D(Num_RelaxedTauEff, DenumEff, 20, 23, 4)
RelaxedTauEff25 = doRatio2D(Num_RelaxedTauEff, DenumEff, 25, 24, 6)
RelaxedTauEff10.Draw("PAE")
RelaxedTauEff15.Draw("Psame")
RelaxedTauEff20.Draw("Psame")
RelaxedTauEff25.Draw("Psame")
legend_ = TLegend(0.60, 0.78, 0.9, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(RelaxedTauEff10, "UCTTauL1 10GeV", "lp")
legend_.AddEntry(RelaxedTauEff15, "UCTTauL1 15GeV", "lp")
legend_.AddEntry(RelaxedTauEff20, "UCTTauL1 20GeV", "lp")
legend_.AddEntry(RelaxedTauEff25, "UCTTauL1 25GeV", "lp")
legend_.Draw()
canvas.SaveAs("MuTauEfficiency2D.pdf")

FileRootEff = TFile("muTau_L1Mu_efficiency.root", "OPEN")
DenumEff = FileRootEff.Get("demo/offLineTauEff")
Num_l1extraEff = FileRootEff.Get("demo/Eff2D_Num_l1extraParticles")
Num_RelaxedTauEff = FileRootEff.Get("demo/Eff2D_Num_RelaxedTauUnpacked")
Num_IsolatedTauEff = FileRootEff.Get("demo/Eff2D_Num_IsolatedTauUnpacked")
l1extraEff = doRatio2D(Num_l1extraEff, DenumEff, 15, 21, 2)
RelaxedTauEff = doRatio2D(Num_RelaxedTauEff, DenumEff, 15, 22, 3)
IsolatedTauEff = doRatio2D(Num_IsolatedTauEff, DenumEff, 15, 23, 4)
l1extraEff.Draw("PAE")
RelaxedTauEff.Draw("Psame")
IsolatedTauEff.Draw("Psame")
legend_ = TLegend(0.60, 0.78, 0.9, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(l1extraEff, "L1tau or jet", "lp")
legend_.AddEntry(RelaxedTauEff, "UCTTau", "lp")
legend_.AddEntry(IsolatedTauEff, "UCTIsoTau", "lp")
legend_.Draw()
canvas.SaveAs("MuTauEfficiencyDifferentAlgo2D.pdf")


FileRootEff = TFile("muTau_L1Mu_efficiency.root", "OPEN")
DenumROC = FileRootEff.Get("demo/offLineTauROC")
Num_l1extraROC = FileRootEff.Get("demo/l1extraParticlesROC")
Num_RelaxedTauROC = FileRootEff.Get("demo/RelaxedTauUnpackedROC")
Num_IsolatedTauROC = FileRootEff.Get("demo/IsolatedTauUnpackedROC")
Num_RelaxedTauROC4x4 = FileRootEff.Get("demo/RelaxedTauUnpackedROC4x4")
Num_IsolatedTauROC4x4 = FileRootEff.Get("demo/IsolatedTauUnpackedROC4x4")
l1extraROC = doCommulative(Num_l1extraROC, DenumROC, 21, 2, "Efficiency")
RelaxedTauROC = doCommulative(Num_RelaxedTauROC, DenumROC, 22, 3, "Efficiency")
IsolatedTauROC = doCommulative(Num_IsolatedTauROC, DenumROC, 23, 4, "Efficiency")
RelaxedTau4x4ROC = doCommulative(Num_RelaxedTauROC4x4, DenumROC, 24, 6, "Efficiency")
IsolatedTau4x4ROC = doCommulative(Num_IsolatedTauROC4x4, DenumROC, 25, 7, "Efficiency")
l1extraROC.Draw("P")
RelaxedTauROC.Draw("Psame")
IsolatedTauROC.Draw("Psame")
RelaxedTau4x4ROC.Draw("Psame")
IsolatedTau4x4ROC.Draw("Psame")
legend_ = TLegend(0.60, 0.78, 0.9, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(l1extraROC, "L1tau or jet", "lp")
legend_.AddEntry(RelaxedTauROC, "UCTTau2x1", "lp")
legend_.AddEntry(IsolatedTauROC, "IsoUCTTau2x1", "lp")
legend_.AddEntry(RelaxedTau4x4ROC, "UCTTau4x4", "lp")
legend_.AddEntry(IsolatedTau4x4ROC, "IsoUCTTau4x4", "lp")
legend_.Draw()
canvas.SaveAs("MuTauEfficiencyCum.pdf")



FileRootRate = TFile("muTau_L1Mu_rate.root", "OPEN")
L1JetParticle = FileRootRate.Get("demo/rate_L1JetParticle");
UCTCandidate = FileRootRate.Get("demo/rate_UCTCandidate");
UCTCandidateIso = FileRootRate.Get("demo/rate_UCTCandidateIso");
UCTCandidate4x4 = FileRootRate.Get("demo/rate_UCTCandidate4x4");
UCTCandidateIso4x4 = FileRootRate.Get("demo/rate_UCTCandidateIso4x4");
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
legend_ = TLegend(0.60, 0.78, 0.9, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(L1JetParticleCum, "L1JetParticle", "lp")
legend_.AddEntry(UCTCandidateCum, "UCTCandidate", "lp")
legend_.AddEntry(UCTCandidateIsoCum, "UCTCandidateIso", "lp")
legend_.AddEntry(UCTCandidateCum4x4, "UCTCandidate4x4", "lp")
legend_.AddEntry(UCTCandidateIsoCum4x4, "UCTCandidateIso4x4", "lp")
canvas.SetLogy()
legend_.Draw()
canvas.SaveAs("MuTauRateCum.pdf")




L1JetParticleROC = doROCCurve(Num_l1extraROC, DenumROC, L1JetParticle, L1JetParticle, 21, 2)
UCTCandidateROC = doROCCurve(Num_RelaxedTauROC, DenumROC, UCTCandidate, UCTCandidate, 22, 3)
UCTCandidateIsoROC = doROCCurve(Num_IsolatedTauROC, DenumROC, UCTCandidateIso, UCTCandidateIso, 23, 4)
L1JetParticleROC.Draw("P")
UCTCandidateROC.Draw("Psame")
UCTCandidateIsoROC.Draw("Psame")
#UCTCandidateCum4x4.Draw("Psame")
#UCTCandidateIsoCum4x4.Draw("Psame")
legend_ = TLegend(0.50, 0.78, 0.9, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(L1JetParticleROC, "L1JetParticleROC", "lp")
legend_.AddEntry(UCTCandidateROC, "UCTCandidateROC", "lp")
legend_.AddEntry(UCTCandidateIsoROC, "UCTCandidateIsoROC", "lp")
#legend_.AddEntry(UCTCandidateCum4x4, "UCTCandidate4x4", "lp")
#legend_.AddEntry(UCTCandidateIsoCum4x4, "UCTCandidateIso4x4", "lp")
canvas.SetLogy(0)
legend_.Draw()
canvas.SaveAs("MuTauROC.pdf")
