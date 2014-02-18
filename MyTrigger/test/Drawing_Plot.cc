//#include <TLatex.h>
//#include <TGraph.h>
//
//#include "TROOT.h"
//#include "TFile.h"
//#include "TTree.h"
//#include "TBrowser.h"
//#include "TH1.h"
//#include "TH2.h"
//#include "TRandom.h"
//#include "iostream.h"
//#include "TCanvas.h"
//#include "math.h"
//#include "TGaxis.h"
//#include "TLegend.h"
//#include "TInterpreter.h"
//#include "TCanvas.h"
//#include "TSystem.h"
//#include "TFile.h"
//#include "TH2.h"
//#include "TNtuple.h"
//#include "TPaveLabel.h"
//#include "TPaveText.h"
//#include "TFrame.h"
//#include "TSystem.h"
//#include "TInterpreter.h"
//
//void M_FR(int WP, std::string type, std::string files, std::string num, std::string denum) {
//    cout << "############################################################" << endl;
//    cout << "\n\n   It is Precossing -->  " << num << "  over  " << denum << endl;
//    TFile *inputFile = new TFile(files.c_str());
//
//    //    TH1D *Numerator = (TH1D*) inputFile->Get("demo/RelaxedTauUnpacked");
//    //    TH1D *Numerator = (TH1D*) inputFile->Get("demo/IsolatedTauUnpacked");
//
//    //    TH1D *Denumerator = (TH1D*) inputFile->Get("demo/RelaxedTauUnpacked");
//
//    TH1D *Numerator = (TH1D*) inputFile->Get("demo/l1extraParticles");
//    TH1D *Denumerator = (TH1D*) inputFile->Get("demo/offLineTau");
//    TH1D *Num_rebin = (TH1D*) Numerator->Rebin(1);
//    TH1D *Denum_rebin = (TH1D*) Denumerator->Rebin(1);
//    TGraphAsymmErrors * TGraph_FR = new TGraphAsymmErrors(Num_rebin, Denum_rebin);
//
//    TH1D *Numerator2 = (TH1D*) inputFile->Get("demo/IsolatedTauUnpacked");
//    TH1D *Denumerator2 = (TH1D*) inputFile->Get("demo/offLineTau");
//    TH1D *Num_rebin2 = (TH1D*) Numerator2->Rebin(1);
//    TH1D *Denum_rebin2 = (TH1D*) Denumerator2->Rebin(1);
//    TGraphAsymmErrors * TGraph_FR2 = new TGraphAsymmErrors(Num_rebin2, Denum_rebin2);
//
//
//    //        Denumerator->Draw();
//    //        Numerator->Draw("same");
//    //TGraph_FR->Draw();
//    //############
//    TCanvas* canvas = new TCanvas("canvas", "", 700, 500);
//    //    canvas->SetLogy();
//    canvas->SetTitle("");
//    TGraph_FR->GetYaxis()->SetRangeUser(.001, 1.5);
//    TGraph_FR->GetYaxis()->SetTitle("Efficiency");
//    TGraph_FR->GetXaxis()->SetRangeUser(0, 100);
//    TGraph_FR->GetXaxis()->SetTitle("Pt^{off} [GeV]");
//    //    TGraph_FR->GetName();
//    //    TGraph_FR->SetTitle("");
//    TGraph_FR->SetMarkerSize(1.2);
//    TGraph_FR->SetMarkerStyle(20);
//    TGraph_FR->SetMarkerColor(2);
//    TGraph_FR->Draw("PAE");
//    TGraph_FR2->SetMarkerSize(1.2);
//    TGraph_FR2->SetMarkerStyle(24);
//    TGraph_FR2->SetMarkerColor(3);
//    TGraph_FR2->Draw("samePE");
//
//    std::string outNaming =   "Efficiency1.pdf";
//
//
//
//    TLegend *l = new TLegend(0.3, 0.70, 0.8, 0.85, NULL, "brNDC");
//    l->SetBorderSize(0);
//    l->SetFillColor(0);
//    l->SetTextSize(.04);
//    l->AddEntry(TGraph_FR, "L1Tau[l1extraParticles]", "lpr");
//    l->AddEntry(TGraph_FR2, "L1UpgradeTau[IsolatedTauUnpacked]", "lpr");
//    l->Draw();
//
//    //
//    //    TLatex t = TLatex();
//    //    t.SetNDC();
//    //    t.SetTextFont(62);
//    //    t.SetTextAlign(12);
//    //    t.SetTextSize(0.045);
//    //    //    t.DrawLatex(0.1, .92, "CMS Preliminary 2012");
//    //    //    t.DrawLatex(0.5, .92, "#sqrt{s} = 8 TeV, L = 19.7 fb^{-1}");
//    //    std::string lepName;
//    //
//    //    t.DrawLatex(0.3, .75, lepName.c_str());
//    //    t.DrawLatex(0.3, .85, lepName.c_str());
//    ////    t.DrawLatex(0.3, .85, num.c_str());
//    //    t.DrawLatex(0.5, .80, num.c_str());
//    canvas->SaveAs(outNaming.c_str());
//    //############
//
//
//}
//
//void Drawing_Plot() {
//
//    TFile *FR_File = new TFile("FitValues_FR.root", "RECREATE");
//    M_FR(1, "Exp3Par", "eff_Results.root", "RelaxedTauUnpacked", "offLineTau");
//
//    FR_File->Write();
//    FR_File->Close();
//}
//
