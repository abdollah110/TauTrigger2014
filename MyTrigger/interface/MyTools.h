/* 
 * File:   MyTools.h
 * Author: abdollahmohammadi
 *
 * Created on February 18, 2014, 10:06 AM
 */

#ifndef MYTOOLS_H
#define	MYTOOLS_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TMath.h" //M_PI is in TMath
#include "TRandom3.h"
using namespace std;

class MyTools {
public:
    explicit MyTools(); // need to include the constrcutor in the class definition
    TH1F* nplot1(std::string name);
    TH2F* nplot2(std::string name);
    void plotFill(std::string name, float x, int nx, float nxmin, float nxmax, double weight = 1);
    void plotFill(std::string name, float x, float y, int nx, float nxmin, float nxmax, int ny, float nymin, float nymax, double weight = 1);
    float deltaPhi_2(float a, float b);
    float dR2(float l1eta, float l1phi, float l2eta, float l2phi);
    map<string, TH1F*>* myMap1;
    map<string, TH2F*>* myMap2;
};



#endif	/* MYTOOLS_H */

