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




def doRatio(num, denum, marSize, marStyle, marColor):
    bins = array('d', [20, 26, 32, 40, 50, 70, 100])
    num_R = num.Rebin(len(bins)-1, "Hinm", bins)
    denum_R = denum.Rebin(len(bins)-1, "Hin", bins)
    ratio = ROOT.TGraphAsymmErrors(num_R, denum_R, "")
    ratio.SetMinimum(0.0)
    ratio.SetMaximum(1.2)
    ratio.SetMarkerSize(marSize);
    ratio.SetMarkerStyle(marStyle);
    ratio.SetMarkerColor(marColor);
    ratio.SetLineColor(marColor);
    ratio.SetLineWidth(2);
    ratio.GetXaxis().SetTitle("#tau_{pT} [GeV]")
    ratio.GetYaxis().SetTitle("Efficiency")
    return ratio


def doCommulative(num, denum, marSize, marStyle, marColor):
    commul = TH1F(str(num), "", 100, 0, 100)
    for ii in range(1, 100):
        commul.SetBinContent(ii + 1, (num.Integral(ii, 100) * 1.0) / denum.GetEntries());
    commul.SetMinimum(0.001)
    commul.SetMaximum(1.2)
    commul.SetMarkerSize(marSize);
    commul.SetMarkerStyle(marStyle);
    commul.SetMarkerColor(marColor);
    commul.GetXaxis().SetTitle("Offline #tau_{pT} [GeV]")
    commul.GetYaxis().SetTitle("ROC Efficiency")
    return commul

FileRootEff = TFile("muTau_L1Mu_efficiency.root", "OPEN")

DenumEff = FileRootEff.Get("demo/offLineTauEff")
Num_l1extraEff = FileRootEff.Get("demo/l1extraParticlesEff")
Num_RelaxedTauEff = FileRootEff.Get("demo/RelaxedTauUnpackedEff")
Num_IsolatedTauEff = FileRootEff.Get("demo/IsolatedTauUnpackedEff")
l1extraEff = doRatio(Num_l1extraEff, DenumEff, 1.2, 23, 2)
RelaxedTauEff = doRatio(Num_RelaxedTauEff, DenumEff, 1.2, 21, 3)
IsolatedTauEff = doRatio(Num_IsolatedTauEff, DenumEff, 1.2, 24, 4)
l1extraEff.Draw("PAE")
RelaxedTauEff.Draw("Psame")
IsolatedTauEff.Draw("Psame")
legend_ = TLegend(0.60, 0.78, 0.9, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(l1extraEff, "l1extra", "lp")
legend_.AddEntry(RelaxedTauEff, "UCTTau", "lp")
legend_.AddEntry(IsolatedTauEff, "IsoUCTTau", "lp")
legend_.Draw()
canvas.SaveAs("MuTauEfficiency.pdf")



DenumROC = FileRootEff.Get("demo/offLineTauROC")
Num_l1extraROC = FileRootEff.Get("demo/l1extraParticlesROC")
Num_RelaxedTauROC = FileRootEff.Get("demo/RelaxedTauUnpackedROC")
Num_IsolatedTauROC = FileRootEff.Get("demo/IsolatedTauUnpackedROC")
Num_RelaxedTauROC4x4 = FileRootEff.Get("demo/RelaxedTauUnpackedROC4x4")
Num_IsolatedTauROC4x4 = FileRootEff.Get("demo/IsolatedTauUnpackedROC4x4")
l1extraROC = doCommulative(Num_l1extraROC, DenumROC, 1.2, 21, 2)
RelaxedTauROC = doCommulative(Num_RelaxedTauROC, DenumROC, 1.2, 22, 3)
IsolatedTauROC = doCommulative(Num_IsolatedTauROC, DenumROC, 1.2, 23, 4)
RelaxedTau4x4ROC = doCommulative(Num_RelaxedTauROC4x4, DenumROC, 1.2, 24, 6)
IsolatedTau4x4ROC = doCommulative(Num_IsolatedTauROC4x4, DenumROC, 1.2, 25, 7)
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
canvas.SaveAs("MuTauROC.pdf")



FileRootRate = TFile("muTau_L1Mu_rate.root", "OPEN")
L1JetParticle = FileRootRate.Get("demo/rate_L1JetParticle");
UCTCandidate = FileRootRate.Get("demo/rate_UCTCandidate");
UCTCandidateIso = FileRootRate.Get("demo/rate_UCTCandidateIso");
L1JetParticleCum = doCommulative(L1JetParticle, L1JetParticle, 1.2, 21, 2)
UCTCandidateCum = doCommulative(UCTCandidate, UCTCandidate, 1.2, 22, 3)
UCTCandidateIsoCum = doCommulative(UCTCandidateIso, UCTCandidateIso, 1.2, 23, 4)
L1JetParticleCum.Draw("P")
UCTCandidateCum.Draw("Psame")
UCTCandidateIsoCum.Draw("Psame")
#RelaxedTau4x4ROC.Draw("Psame")
#IsolatedTau4x4ROC.Draw("Psame")
legend_ = TLegend(0.60, 0.78, 0.9, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(L1JetParticleCum, "L1JetParticle", "lp")
legend_.AddEntry(UCTCandidateCum, "UCTCandidate", "lp")
legend_.AddEntry(UCTCandidateIsoCum, "UCTCandidateIso", "lp")
#legend_.AddEntry(RelaxedTau4x4ROC, "UCTTau4x4", "lp")
#legend_.AddEntry(IsolatedTau4x4ROC, "IsoUCTTau4x4", "lp")
canvas.SetLogy()
legend_.Draw()
canvas.SaveAs("MuTauRateCum.pdf")
