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



File = TFile("eff_Results_v3.root", "OPEN")
#File = TFile("eff_Results_Fixed1_Z_Zprime.root", "OPEN")
Denum = File.Get("demo/offLineTauEff")
Num_l1extra = File.Get("demo/l1extraParticlesEff")
Num_RelaxedTau = File.Get("demo/RelaxedTauUnpackedEff")
Num_IsolatedTau = File.Get("demo/IsolatedTauUnpackedEff")

#FileFixed = TFile("eff_Results_Fixed1.root", "OPEN")
FileFixed = TFile("eff_Results_Fixed1_Z_Zprime.root", "OPEN")
DenumFixed = FileFixed.Get("demo/offLineTauEff")
Num_l1extraFixed = FileFixed.Get("demo/l1extraParticlesEff")
Num_RelaxedTauFixed = FileFixed.Get("demo/RelaxedTauUnpackedEff")
Num_IsolatedTauFixed = FileFixed.Get("demo/IsolatedTauUnpackedEff")



l1extra = doRatio(Num_l1extra, Denum, 1.2, 24, 2)
RelaxedTau = doRatio(Num_RelaxedTau, Denum, 1.2, 21, 3)
IsolatedTau = doRatio(Num_IsolatedTau, Denum, 1.2, 25, 1)

l1extraFixed = doRatio(Num_l1extraFixed, DenumFixed, 1.2, 23, 2)
RelaxedTauFixed = doRatio(Num_RelaxedTauFixed, DenumFixed, 1.2, 21, 3)
IsolatedTauFixed = doRatio(Num_IsolatedTauFixed, DenumFixed, 1.2, 24, 2)

l1extra.Draw("PAE")
l1extraFixed.Draw("Psame")


for bn in range(1,50):
    print bn, DenumFixed.GetBinContent(bn)-Num_IsolatedTauFixed.GetBinContent(bn)

#RelaxedTau.Draw("PAEsame")
#IsolatedTau.Draw("Psame")


#IsolatedTau.Draw("PAE")
#IsolatedTauFixed.Draw("Psame")

legend_ = TLegend(0.60, 0.78, 0.9, 0.9)
legend_.SetFillColor(0)
legend_.SetBorderSize(0)
legend_.SetTextSize(.03)
legend_.AddEntry(IsolatedTauFixed, "IsoUCTTau(Fixed)", "lp")
legend_.AddEntry(IsolatedTau, "IsoUCTTau(old)", "lp")
legend_.Draw()



canvas.SaveAs("ChannelNameFixed2.pdf")
