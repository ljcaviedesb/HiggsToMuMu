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
  TApplication theApp("muon", &argc, arg);
  
  Pythia pythia;
  pythia.readString("Beams:eCM = 13000");     // sqrt(s)=13TeV
  pythia.readString("HiggsSM:gg2h = on");     // Higgs production by gg fusion
  pythia.readString("25:onMode = 1");         // Disallow Higgs decay
  pythia.readString("25:onIfAll = 13 -13");   // Allow only H -> µµ  
  pythia.init();

  //Create file.root
  TFile* outFile = new TFile("muon.root", "RECREATE");
  // Declare variables
  Event *event = &pythia.event;
  Float_t pT=0, eta=0, phi=0, E=0, m=0, px=0, py=0, pz=0, ET=0;
   Float_t pTm=0, etam=0, phim=0, Em=0, mm=0, pxm=0, pym=0, pzm=0, ETm=0;
  Float_t invmass=0, tp=0, tpx=0, tpy=0, tpz=0, tpT=0, tE=0, tET=0;
  
  // Create Tree and branches of the tree
  TTree *T = new TTree("T","ev1 Tree");
  T->Branch("event",&event,"Event");
  T->Branch("tpT",&pT);
  T->Branch("eta",&eta);
  T->Branch("etam",&etam);
  T->Branch("phi",&phi);
  T->Branch("phim",&phim);
  T->Branch("tE",&E);
  T->Branch("invmass",&mass);
  T->Branch("tp", &tp);

  // Start process
  for (int iEvent = 0; iEvent<10000; ++iEvent){ // 10 000 events
    if(!pythia.next()) continue;                // jump to the next event
    // Select muons
    for (int i1 = 0; i1 < pythia.event.size(); ++i1){
      Int_t imuon=0;                            // Create iterator
      if ( pythia.event[i1].id()==13){
	imuon = i1;
	pT = pythia.event[i].pT();
	px = pythia.event[i].px();
	py = pythia.event[i].py();
	pz = pythia.event[i].pz();
	eta = pythia.event[i].eta();
	phi = pythia.event[i].phi();
	E = pythia.event[i].e();
	ET = pythia.event[i].eT();
	m = pythia.event[i].mCalc();	
      }// close muon selection
    }// close muon loop
    // Select anti-muons
    for ( int i1 = 0; i2 < pythia.event.size(); ++i2){
      Int_t imuonm = 0;
      if (pythia.event[i2].id()==-13){
	imuonm = i2;
	pTm = pythia.event[i].pT();
	pxm = pythia.event[i].px();
	pym = pythia.event[i].py();
	pzm = pythia.event[i].pz();
	etam = pythia.event[i].eta();
	phim = pythia.event[i].phi();
	Em = pythia.event[i].e();
	ETm = pythia.event[i].eT();
	mm = pythia.event[i].mCalc();
      }// close anit-muons selection
    }// close anti-muon loop

    tpx = px + pxm;
    tpy = py + pym;
    tpz = pz + pzm;
    tp  = sqrt(pow2(tpx) + pow2(tpy) + pow2(tpz));
    tpT = sqrt(pow2(tpx) + pow2(tpy) );
    tE  = E + Em;
    tET = ET + ETm;
    invmass = sqrt(pow2(tE) - pow2(tp) );

	
    T->Fill();
  }

  pythia.stat();
 
  T->Print();
  T->Write();
  outFile->Write();
  delete outFile;
  
  
  return 0;
}
