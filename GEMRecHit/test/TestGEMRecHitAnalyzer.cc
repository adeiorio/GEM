// -*- C++ -*-
//
// Package:    TestGEMRecHitAnalyzer
// Class:      TestGEMRecHitAnalyzer
// 
/**\class TestGEMRecHitAnalyzer TestGEMRecHitAnalyzer.cc MyAnalyzers/TestGEMRecHitAnalyzer/src/TestGEMRecHitAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Piet Verwilligen,161 R-006,+41227676292,
//         Created:  Wed Oct 24 17:28:30 CEST 2012
//
//


// system include files
#include <memory>
#include <fstream>
#include <sys/time.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

// root include files
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TDirectoryFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <DataFormats/GeometryVector/interface/GlobalVector.h>
#include <DataFormats/GEMRecHit/interface/GEMRecHit.h>
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include <DataFormats/GEMDigi/interface/GEMDigiCollection.h>
#include "DataFormats/Provenance/interface/Timestamp.h"
#include <DataFormats/MuonDetId/interface/GEMDetId.h>
#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include <Geometry/GEMGeometry/interface/GEMEtaPartition.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/GEMGeometry/interface/GEMGeometry.h>
#include <Geometry/DTGeometry/interface/DTGeometry.h>
#include <Geometry/CSCGeometry/interface/CSCGeometry.h>
#include <Geometry/CSCGeometry/interface/CSCLayer.h>
#include <Geometry/CommonTopologies/interface/RectangularStripTopology.h>
#include <Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h>
//#include <DataFormats/GEMDigi/interface/GEMDigiCollection.h>
//#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
//#include <Geometry/CommonDetUnit/interface/GeomDet.h>
//#include <Geometry/Records/interface/MuonGeometryRecord.h>

//
// class declaration
//

class TestGEMRecHitAnalyzer : public edm::EDAnalyzer {
   public:
      explicit TestGEMRecHitAnalyzer(const edm::ParameterSet&);
      ~TestGEMRecHitAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
  // ----------member data ---------------------------
  edm::ESHandle<GEMGeometry> gemGeom;
  edm::ESHandle<CSCGeometry> cscGeom;
  edm::EDGetTokenT<GEMRecHitCollection> GEMRecHit_Token;
  //  edm::EDGetTokenT<standAloneMuonRecHitCollection> standAloneMuonRecHits_Token;
  edm::EDGetTokenT<CSCSegmentCollection> cscSegments_Token;

  //
  // constants, enums and typedefs
  //
  TTree * RecHitAna;
  //  int gemsize = 500;
  double gemregion[300], gemring[300], gemstation[300], gemlayer[300], gemglobalx[300], gemglobaly[300], gemglobalz[300], gemglobalr[300], gemetapart[300], gemchamber[300], gembunchx[300], gemclustsize[300], gemfirstcluststrip[300];
  double cscregion[300], cscring[300], cscstation[300], nRecHitsCSCSeg[300], cscSegAngle[300], cscSegXo[300], cscSegYo[300], cscSegZo[300], cscSegXi[300], cscSegYi[300], cscSegZi[300];
  std::map<CSCDetId,int> CSCSegmentsCounter;
  int ngems=0, ncscs=0;
};


//
// constructors and destructor
//
TestGEMRecHitAnalyzer::TestGEMRecHitAnalyzer(const edm::ParameterSet& iConfig){
  edm::Service<TFileService> fs;
   //now do what ever initialization is needed
  GEMRecHit_Token = consumes<GEMRecHitCollection>(edm::InputTag("gemRecHits"));
  //  standAloneMuonRecHit_Token = consumes<standAloneMuonRecHitCollection>(edm::InputTag("standAloneMuonRecHits"));
  cscSegments_Token = consumes<CSCSegmentCollection>(edm::InputTag("cscSegments"));

  RecHitAna = fs->make<TTree>("RecHitAna","RecHitAna");

  RecHitAna->Branch("ngems", &ngems);
  RecHitAna->Branch("gemregion", gemregion, "gemregion[ngems]/D");
  RecHitAna->Branch("gemstation", gemstation, "gemstation[ngems]/D");
  RecHitAna->Branch("gemring", gemring, "gemring[ngems]/D");
  RecHitAna->Branch("gemlayer", gemlayer, "gemlayer[ngems]/D");
  RecHitAna->Branch("gemetapart", gemetapart, "gemetapart[ngems]/D");
  RecHitAna->Branch("gemchamber", gemchamber, "gemchamber[ngems]/D");
  RecHitAna->Branch("gemglobalx", gemglobalx, "gemglobalx[ngems]/D");
  RecHitAna->Branch("gemglobaly", gemglobaly, "gemglobaly[ngems]/D");
  RecHitAna->Branch("gemglobalz", gemglobalz, "gemglobalz[ngems]/D");
  RecHitAna->Branch("gemglobalr", gemglobalr, "gemglobalr[ngems]/D");
  RecHitAna->Branch("gembunchx", gembunchx, "gembunchx[ngems]/D");
  //  RecHitAna->Branch("gemclustsize", gemclustsize);
  //  RecHitAna->Branch("gemfirstcluststrip", gemfirstcluststrip);

  RecHitAna->Branch("ncscs", &ncscs);
  RecHitAna->Branch("cscregion", cscregion, "cscregion[ncscs]/D");
  RecHitAna->Branch("cscstation", cscstation, "cscstation[ncscs]/D");
  RecHitAna->Branch("cscring", cscring, "cscring[ncscs]/D");
  //  RecHitAna->Branch("csclayer", csclayer, "csclayer[ncscs]/D");
  //  RecHitAna->Branch("cscetapart", cscetapart, "cscetapart[ncscs]/D");
  //  RecHitAna->Branch("cscchamber", cscchamber, "cscchamber[ncscs]/D");
  RecHitAna->Branch("nRecHitsCSCSeg", nRecHitsCSCSeg, "nRecHitsCSCSeg[ncscs]/D");
  RecHitAna->Branch("cscSegAngle", cscSegAngle, "cscSegAngle[ncscs]/D");
  RecHitAna->Branch("cscSegXo", cscSegXo, "cscSegXo[ncscs]/D");
  RecHitAna->Branch("cscSegYo", cscSegYo, "cscSegYo[ncscs]/D");
  RecHitAna->Branch("cscSegZo", cscSegZo, "cscSegZo[ncscs]/D");
  RecHitAna->Branch("cscSegXi", cscSegXi, "cscSegXi[ncscs]/D");
  RecHitAna->Branch("cscSegYi", cscSegYi, "cscSegYi[ncscs]/D");
  RecHitAna->Branch("cscSegZi", cscSegZi, "cscSegZi[ncscs]/D");

  //  RecHitAna->Branch("cscSegr", cscSegr, "cscSegr[ncscs]/D");
  //  RecHitAna->Branch("cscbunchx", cscbunchx, "cscbunchx[ncscs]/D");

}


TestGEMRecHitAnalyzer::~TestGEMRecHitAnalyzer(){
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called for each event  ------------
void TestGEMRecHitAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  // ================
  // GEM recHits
  // ================
  iSetup.get<MuonGeometryRecord>().get(gemGeom);

  edm::Handle<GEMRecHitCollection> gemRecHits; 
  iEvent.getByToken(GEMRecHit_Token,gemRecHits);
  // count the number of GEM rechits
  int nGEMRH = 0;
  ngems = gemRecHits->size();
  //  std::cout<< "Primo check sul numero di eventi: " << ngems << std::endl;

  GEMRecHitCollection::const_iterator recHit;
   
  for (recHit = gemRecHits->begin(); recHit != gemRecHits->end(); recHit++) {
    GEMDetId rollId = (GEMDetId)(*recHit).gemId();
    LocalPoint recHitPos=recHit->localPosition();
    const GEMEtaPartition* rollasociated = gemGeom->etaPartition(rollId);
    const BoundPlane & GEMSurface = rollasociated->surface(); 
    GlobalPoint GEMGlobalPoint = GEMSurface.toGlobal(recHitPos);

    gemregion[nGEMRH]  = rollId.region();
    gemstation[nGEMRH] = rollId.station();
    gemring[nGEMRH]    = rollId.ring();
    gemlayer[nGEMRH]   = rollId.layer();
    gemetapart[nGEMRH] = rollId.roll();
    gemchamber[nGEMRH] = rollId.chamber();

    //    std::cout<<"GEM Rec Hit in [DetId] = ["<<rollId<<"] with BX = "<<recHit->BunchX()<<" and Global Position = "<<GEMGlobalPoint<<std::endl;

    gembunchx[nGEMRH]  = recHit->BunchX();
    //    gemclustsize[nGEMRH] = recHit->clusterSize();
    //    gemfirstcluststrip[nGEMRH] = recHit->firstClusterStrip();
    gemglobalx[nGEMRH] = GEMGlobalPoint.x();
    gemglobaly[nGEMRH] = GEMGlobalPoint.y();
    gemglobalz[nGEMRH] = GEMGlobalPoint.z();
    gemglobalr[nGEMRH] = pow(pow(gemglobalx[nGEMRH],2)+pow(gemglobaly[nGEMRH],2),0.5);
    nGEMRH++;
  }
  
  //  std::cout<< "Numero RecHit nell'evento: " << nGEMRH << std::endl;

  // =======================
  // Muon standAlone recHits
  // =======================

  // count the number of GEM rechits
  //  int nCSC = 0;
  //  ::const_iterator cscSeg;


  // ============
  // CSC Segments
  // ============
  iSetup.get<MuonGeometryRecord>().get(cscGeom);

  edm::Handle<CSCSegmentCollection> cscSegments; 
  iEvent.getByToken(cscSegments_Token, cscSegments);
  CSCSegmentCollection::const_iterator segment;

 
  //  int segmentsInThisEventInTheEndcap=0;

  /*  for(segment = cscSegments->begin(); segment!=cscSegments->end(); ++segment){
    CSCSegmentsCounter[segment->cscDetId()]++;
    //    segmentsInThisEventInTheEndcap++;
    }*/

  for(segment = cscSegments->begin(); segment!=cscSegments->end(); ++segment){
    std::cout << " csc segment "<<std::endl;
    CSCDetId CSCId = segment->cscDetId();
    std::cout << " CSCId "<<std::endl;
    if(/*CSCSegmentsCounter[CSCId]==1 && */ CSCId.ring()==1 && cscSegments->size()>=2){ //&& CSCId.station()!=4 //per le gem esistono solo le stazioni 1 e 2 del ring 1
      ncscs = cscSegments->size();
      cscregion[ncscs] = CSCId.endcap();
      cscstation[ncscs] = CSCId.station();
      cscring[ncscs] = CSCId.ring();

      std::cout << " endcap "<<CSCId.endcap()<<std::endl;

      LocalPoint segmentPositionLocal = segment->localPosition();
      std::cout << " after local point "<<std::endl;
      
      //GlobalPoint segmentPositionGlobal = segment->globalPosition();
      LocalVector segmentDirectionLocal = segment->localDirection();
      std::cout << " after local direction "<<std::endl;
      nRecHitsCSCSeg[ncscs] = segment->nRecHits();
      std::cout << " before taking layer "<<std::endl;
      const CSCChamber* TheChamber=cscGeom->chamber(CSCId);
      //      const CSCLayer* layer = cscGeom->layer(CSCId);
      std::cout << " after taking chamber "<<std::endl;
      //      const BoundPlane & CSCSurface = layer->surface(); CSCSurface
      //      std::cout << " layer "<<layer<<std::endl;
      
      GlobalPoint GlobalPointout = TheChamber->toGlobal(LocalPoint(segmentPositionLocal.x()+segmentDirectionLocal.x(),segmentPositionLocal.y()+segmentDirectionLocal.y(),segmentPositionLocal.z()+segmentDirectionLocal.z()));
      GlobalPoint GlobalPointin = TheChamber->toGlobal(segmentPositionLocal);
			     
      //      std::cout << " extrap x "<<GlobalPointExtrapolated.x()<<std::endl;
      //      if((segment->dimension()==4) && (segment->nRecHits()<=10 && segment->nRecHits()>=4)){
      //      if(debug) std::cout<<"CSC \t \t CSC Segment Dimension "<<segment->dimension()<<std::endl;
      cscSegXo[ncscs] = GlobalPointin.x();
      cscSegXo[ncscs] = GlobalPointin.y();
      cscSegZo[ncscs] = GlobalPointin.z();
      cscSegXi[ncscs] = GlobalPointout.x();
      cscSegYi[ncscs] = GlobalPointout.y();
      cscSegZi[ncscs] = GlobalPointout.z();
	//      }
      std::cout << " acos "<<acos(cscSegZi[ncscs])*180/3.1415926<<std::endl;
      cscSegAngle[ncscs] = acos(cscSegZi[ncscs])*180/3.1415926;
    }
    //    GlobalPoint segmentPositionInGlobal=TheChamber->toGlobal(segmentPosition);

  
  }
  RecHitAna->Fill();
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void TestGEMRecHitAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TestGEMRecHitAnalyzer);
