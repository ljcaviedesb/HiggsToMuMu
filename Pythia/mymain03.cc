#include <iostream>
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC3.h"

using namespace Pythia8;

int main (){

  // Interface for conversion from Pythia8::Event to HepMC event
  HepMC3::Pythia8ToHepMC3 topHepMC;
  
  //Specify file where HepMC events will be stored
  HepMC3::WriterAscii ascii_io("try1.hepmc");

  // Number of listed events.
  int nPrintLHA  = 1;
  int nPrintRest = 0;
  int nAbort     = 10;
  // Generate Process
  Pythia pythia;
  pythia.readString("Beams:eCM = 13000");     // sqrt(s) = 13TeV
  pythia.readString("HiggsSM:gg2h = on");     // Higgs production by gg fusion
  pythia.readString("25:onMode = 1");         // Disallow Higgs decay
  pythia.readString("25:onIfAll = 13 -13");   // Allow only H -> µµ

  //pythia.readString("Next:numberShowLHA = 0"); 
  //pythia.readString("Next:numberShowInfo = 0"); 
  //pythia.readString("Next:numberShowProcess = 0"); 
  //pythia.readString("Next:numberShowEvent = 0");
   
  // Initialize Les Haouces Event File run
  pythia.readString("Beams:frameType = 4");
  pythia.readString("Beams:LHEF = unweighted_events.lhe");
  pythia.init();

  // Set counters
  int iPrintLHA  = 0;
  int iPrintRest = 0;
  int iAbort     = 0;
  int iFile      = 1;

  // Start processes
  for (int iEvent = 0;iEvent < 100 ; ++iEvent){
    if(!pythia.next()) {
      if (pythia.info.atEndOfFile()){
	if (iFile ==1 ) {
	  pythia.readString("Beams:LHEF = unweighted_events.lhe");
	  pythia.init();
	  ++iFile;
	  continue;
	} else break;
      }

      // First few failures write as "acceptable" errors, then quit.
      if (++iAbort < nAbort) continue;
      break;
    }
    // List first few Les Houches and other events
    if (pythia.info.isLHA() && iPrintLHA < nPrintLHA){
      pythia.LHAeventList();
      pythia.info.list();
      pythia.process.list();
      pythia.event.list();
      ++iPrintLHA;
      } else if (!pythia.info.isLHA() && iPrintRest < nPrintRest) {
      pythia.info.list();
      pythia.process.list();
      pythia.event.list();
      ++iPrintRest;
    }

    // Default units GeV
    HepMC3::GenEvent hepmcevt;
    topHepMC.fill_next_event( pythia, &hepmcevt );

    // Write the HepMC event to file
    //ascii_io.write_event(hepmcevt);
  }// End event loop

  pythia.stat();
 
  return 0;
}
