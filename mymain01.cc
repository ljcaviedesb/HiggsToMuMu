#include<iostream>
#include "Pythia8/Pythia.h"
#include "TTree.h"
#include "TH1.h"
#include "TVirtualPad.h"
#include "TApplication.h"
#include "TFile.h"

using namespace Pythia8;

int main (int argc, char* arg[]){

  // Create the ROOT application environment. 
  TApplication theApp("muon1", &argc, arg);
  
  Pythia pythia;
  pythia.readString("HiggsSM:gg2h = on");
  //  pythia.readString("HiggsSM:all = on");
  //  pythia.readString("HardQCD:all = on");
  //  pythia.readString("PhaseSpace:pTHatMin = 20.");
  pythia.readString("Beams:eCM = 13000");
  pythia.init();

  //Create file.root
  TFile* outFile = new TFile("muon.root", "RECREATE");

  Event *event = &pythia.event;
  Float_t pT=0, eta=0, phi=0, E=0, m=0, px=0, py=0, pz=0, ET=0;
  Int_t imu = 0, imum = 0, iHiggs = 0;
  
  TTree *T = new TTree("T","ev1 Tree");
  T->Branch("event",&event,"Event");
  T->Branch("pT",&pT);
  T->Branch("eta",&eta);
  T->Branch("phi",&phi);
  T->Branch("E",&E);
  T->Branch("m",&m);


  for (int iEvent = 0; iEvent<10000; ++iEvent){
    if(!pythia.next()) continue;

    for (int i = 0; i<pythia.event.size(); ++i){
      Int_t muon = pythia.event[i].id()==13;
      Int_t muonm = pythia.event[i].id()==-13;
      Int_t bottom = pythia.event[i].id()==5;
      Int_t top = pythia.event[i].id()==6;
      Int_t charm = pythia.event[i].id()==4;
      Int_t gluon = pythia.event[i].id()==21;
      Int_t foton = pythia.event[i].id()==22;
      Int_t Z = pythia.event[i].id()==23;
      Int_t W = pythia.event[i].id()==24;
      Int_t H = pythia.event[i].id()==25;

      /*To make every ROOT file for each Higgs decay change the if for each decay wanted 
	like if (bottom || H){ or if (Z || H){  and also is needed to be change the name 
	of the application and output root file*/
      if (muon || H){

	pT = pythia.event[i].pT();
	px = pythia.event[i].px();
	py = pythia.event[i].py();
	pz = pythia.event[i].pz();
	eta = pythia.event[i].eta();
	phi = pythia.event[i].phi();
	E = pythia.event[i].e();
	ET = pythia.event[i].eT();
	m = pythia.event[i].mCalc();
	
	
     }
    }
    
    T->Fill();

  }

  pythia.stat();
 
  T->Print();
  T->Write();
  outFile->Write();
  delete outFile;
  
  
  return 0;
}
