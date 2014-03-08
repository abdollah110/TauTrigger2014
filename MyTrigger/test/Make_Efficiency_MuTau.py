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

    commul=TH1F(str(num), "", 100, 0, 100)
    for ii in range(1,100):
        commul.SetBinContent(ii + 1, (num.Integral(ii, 100)*1.0) / denum.GetEntries());

    commul.SetMinimum(0.0)
    commul.SetMaximum(1.2)
    commul.SetMarkerSize(marSize);
    commul.SetMarkerStyle(marStyle);
    commul.SetMarkerColor(marColor);
    commul.GetXaxis().SetTitle("Offline #tau_{pT} [GeV]")
    commul.GetYaxis().SetTitle("ROC Efficiency")

    return commul


#File = TFile("eff_Results_v3.root", "OPEN")
##File = TFile("eff_Results_Fixed1_Z_Zprime.root", "OPEN")
#Denum = File.Get("demo/offLineTauEff")
#Num_l1extra = File.Get("demo/l1extraParticlesEff")
#Num_RelaxedTau = File.Get("demo/RelaxedTauUnpackedEff")
#Num_IsolatedTau = File.Get("demo/IsolatedTauUnpackedEff")
#l1extra = doRatio(Num_l1extra, Denum, 1.2, 24, 2)
#RelaxedTau = doRatio(Num_RelaxedTau, Denum, 1.2, 21, 3)
#IsolatedTau = doRatio(Num_IsolatedTau, Denum, 1.2, 25, 1)

#FileFixed = TFile("eff_Results_Fixed1.root", "OPEN")
#FileFixed = TFile("eff_Results_Fixed1_Z_Zprime.root", "OPEN")


FileFixed = TFile("eff_Results_Fixed1.root", "OPEN")

DenumEff = FileFixed.Get("demo/offLineTauEff")
Num_l1extraEff = FileFixed.Get("demo/l1extraParticlesEff")
Num_RelaxedTauEff = FileFixed.Get("demo/RelaxedTauUnpackedEff")
Num_IsolatedTauEff = FileFixed.Get("demo/IsolatedTauUnpackedEff")

DenumROC = FileFixed.Get("demo/offLineTauROC")
Num_l1extraROC = FileFixed.Get("demo/l1extraParticlesROC")
Num_RelaxedTauROC = FileFixed.Get("demo/RelaxedTauUnpackedROC")
Num_IsolatedTauROC = FileFixed.Get("demo/IsolatedTauUnpackedROC")
Num_RelaxedTauROC4x4 = FileFixed.Get("demo/RelaxedTauUnpackedROC4x4")
Num_IsolatedTauROC4x4 = FileFixed.Get("demo/IsolatedTauUnpackedROC4x4")




l1extraEff = doRatio(Num_l1extraEff, DenumEff, 1.2, 23, 2)
RelaxedTauEff = doRatio(Num_RelaxedTauEff, DenumEff, 1.2, 21, 3)
IsolatedTauEff = doRatio(Num_IsolatedTauEff, DenumEff, 1.2, 24, 4)

l1extraROC = doCommulative(Num_l1extraROC, DenumROC, 1.2, 23, 2)
RelaxedTauROC = doCommulative(Num_RelaxedTauROC, DenumROC, 1.2, 21, 3)
IsolatedTauROC = doCommulative(Num_IsolatedTauROC, DenumROC, 1.2, 24, 4)
RelaxedTau4x4ROC = doCommulative(Num_RelaxedTauROC4x4, DenumROC, 1.2, 21, 3)
IsolatedTau4x4ROC = doCommulative(Num_IsolatedTauROC4x4, DenumROC, 1.2, 24, 4)


#for bn in range(1,50):
#    print bn, DenumFixed.GetBinContent(bn)-Num_l1extraFixed.GetBinContent(bn), DenumFixed.GetBinContent(bn)-Num_RelaxedTauFixed.GetBinContent(bn),DenumFixed.GetBinContent(bn)-Num_IsolatedTauFixed.GetBinContent(bn)

l1extraEff.Draw("PAE")
RelaxedTauEff.Draw("Psame")
IsolatedTauEff.Draw("Psame")


legend_ = TLegend(0.60, 0.78, 0.9, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(l1extraFixed, "l1extra(Fixed)", "lp")
legend_.AddEntry(RelaxedTauFixed, "UCTTau(Fixed)", "lp")
legend_.AddEntry(IsolatedTauFixed, "IsoUCTTau(Fixed)", "lp")
legend_.Draw()



canvas.SaveAs("ChannelNameFixed2.pdf")



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



canvas.SaveAs("ChannelNameROC2.pdf")
