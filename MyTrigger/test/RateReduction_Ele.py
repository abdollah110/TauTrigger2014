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
from ROOT import TH1D
from ROOT import TH2D
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




FileRootEff = TFile("eTau.root", "OPEN")
HistoRate = FileRootEff.Get("demo/TriggerRate2D")

HistoRate.GetXaxis().SetBinLabel(1, "Barrel_1")
HistoRate.GetXaxis().SetBinLabel(2, "Barrel_2")
HistoRate.GetXaxis().SetBinLabel(3, "Barrel_3")
HistoRate.GetXaxis().SetBinLabel(4, "Barrel_4")
HistoRate.GetYaxis().SetBinLabel(1, "EndCap_1")
HistoRate.GetYaxis().SetBinLabel(2, "EndCap_2")
HistoRate.GetYaxis().SetBinLabel(3, "EndCap_3")
HistoRate.GetYaxis().SetBinLabel(4, "EndCap_4")
HistoRate.GetYaxis().SetBinLabel(5, "EndCap_5")
HistoRate.GetYaxis().SetBinLabel(6, "EndCap_6")
HistoRate.GetYaxis().SetBinLabel(7, "EndCap_7")
HistoRate.GetYaxis().SetBinLabel(8, "EndCap_8")


#HistoRate.SetMaximum(60000)
#HistoRate.SetMarkerSize(1.7)
HistoRate.Scale(1/7768.)
HistoRate.Draw("text")
canvas.SaveAs("EleRateReduction.pdf")
