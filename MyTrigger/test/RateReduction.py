#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="abdollahmohammadi"
__date__ ="$Mar 31, 2014 10:38:42 AM$"

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
#canvas.SetGridx(10)
#canvas.SetGridy(10)




FileRootEff = TFile("hltMu_Rate.root", "OPEN")
HistoRate = FileRootEff.Get("demo/Histo_RateReduction")
HistoRate.GetXaxis().SetBinLabel(1, "TotalEvents")
HistoRate.GetXaxis().SetBinLabel(2, "MuTauPair")
HistoRate.GetXaxis().SetBinLabel(3, "DMF")
HistoRate.GetXaxis().SetBinLabel(4, "Isolation")
HistoRate.GetXaxis().SetBinLabel(5, "NewIsolation")
HistoRate.GetXaxis().SetBinLabel(6, "MuVeto")
HistoRate.GetXaxis().SetBinLabel(7, "Match Offline")
HistoRate.SetMarkerSize(2)
HistoRate.Draw("text")
canvas.SaveAs("MuRateReduction.pdf")
canvas.SaveAs("MuRateReduction.root")
