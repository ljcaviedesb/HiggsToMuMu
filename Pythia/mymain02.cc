#include <iostream>
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC3.h"

using namespace Pythia8;

int main (){

  // Interface for conversion from Pythia8::Event to HepMC event
  HepMC3::Pythia8ToHepMC3 topHepMC;
  //Specify file where HepMC events will be stored
  HepMC3::WriterAscii ascii_io("hepmchiggs2mumu.hepmc");

  // Generate Process
  Pythia pythia;
  pythia.readString("Beams:eCM = 13000");     // sqrt(s) = 13TeV
  pythia.readString("HiggsSM:gg2h = on");     // Higgs production by gg fusion
  pythia.readString("25:onMode = 1");         // Disallow Higgs decay
  pythia.readString("25:onIfAll = 13 -13");   // Allow only H -> µµ
  pythia.init();

  // Start processes
  for (int iEvent = 0;iEvent<100 ; ++iEvent){
    if(!pythia.next()) continue;

    for (int i1 = 0; i1<pythia.event.size(); ++i1){
      int imuon;
      ++imuon;
    }// End loop for muon selection
    for (int i2 = 0; i2<pythia.event.size(); ++i2){
      int imuonm;
      ++imuonm;
    }// End loop for anti-muon selection
    // Construct new empty HepMC event and fill it.
    // Deful units GeV
    HepMC3::GenEvent hepmcevt;
    topHepMC.fill_next_event( pythia, &hepmcevt );

    // Write the HepMC event to file
    ascii_io.write_event(hepmcevt);
  
  }// End event loop

  pythia.stat();
 
  return 0;
}
