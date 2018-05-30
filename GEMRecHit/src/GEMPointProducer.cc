// -*- C++ -*-
//
// Package:    GEMPointProducer
// Class:      GEMPointProducer
// 
/**\class GEMPointProducer GEMPointProducer.cc Analysis/GEMPointProducer/src/GEMPointProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Wed Sep 16 14:56:18 CEST 2009
//
//

#include "RecoLocalMuon/GEMRecHit/interface/GEMPointProducer.h"

// system include files

#include <memory>
#include <ctime>

// user include files

GEMPointProducer::GEMPointProducer(const edm::ParameterSet& iConfig) :
  cscSegments(  consumes<CSCSegmentCollection>(iConfig.getParameter<edm::InputTag>("cscSegments")) ),
  dt4DSegments( consumes<DTRecSegment4DCollection>(iConfig.getParameter<edm::InputTag>("dt4DSegments")) ),
  //  tracks(       consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("tracks")) ),
  tracks_(      iConfig.getParameter<edm::InputTag>("tracks") ),
  incldt(       iConfig.getUntrackedParameter<bool>("incldt", true) ),
  inclcsc(      iConfig.getUntrackedParameter<bool>("inclcsc", true) ),
  incltrack(    iConfig.getUntrackedParameter<bool>("incltrack", true) ), 
  debug(        iConfig.getUntrackedParameter<bool>("debug", false) ),
  MinCosAng(    iConfig.getUntrackedParameter<double>("MinCosAng", 0.95) ),
  MaxD(         iConfig.getUntrackedParameter<double>("MaxD", 80.) ),
  MaxDrb4(      iConfig.getUntrackedParameter<double>("MaxDrb4", 150.) ),
  ExtrapolatedRegion( iConfig.getUntrackedParameter<double>("ExtrapolatedRegion", 0.5) ),
  trackTransformerParam( iConfig.getParameter<edm::ParameterSet>("TrackTransformer") )
{
  produces<GEMRecHitCollection>("GEMDTExtrapolatedPoints");
  produces<GEMRecHitCollection>("GEMCSCExtrapolatedPoints");
  produces<GEMRecHitCollection>("GEMTrackExtrapolatedPoints");
}

void GEMPointProducer::produce(edm::StreamID, edm::Event& iEvent, const edm::EventSetup& iSetup) const {
  if(incldt){
    edm::Handle<DTRecSegment4DCollection> all4DSegments;
    iEvent.getByToken(dt4DSegments, all4DSegments);
    if(all4DSegments.isValid()){
      //      DTSegtoGEM DTClass(all4DSegments.product(), iSetup, debug, ExtrapolatedRegion);
      //      iEvent.put(std::move(DTClass.thePoints()), "GEMDTExtrapolatedPoints"); 
    }else{
      if(debug) std::cout<<"GEMHLT Invalid DTSegments collection"<<std::endl;
    }
  }

  if(inclcsc){
    edm::Handle<CSCSegmentCollection> allCSCSegments;
    iEvent.getByToken(cscSegments, allCSCSegments);
    if(allCSCSegments.isValid()){
      CSCSegtoGEM CSCClass(allCSCSegments.product(), iSetup, debug, ExtrapolatedRegion);
      iEvent.put(std::move(CSCClass.thePoints()), "GEMCSCExtrapolatedPoints"); 
    }else{
      if(debug) std::cout<<"GEMHLT Invalid CSCSegments collection"<<std::endl;
    }
  }
  if(incltrack){
    //    edm::Handle<reco::TrackCollection> alltracks;
    //    iEvent.getByToken(tracks,alltracks);
    //    if(!(alltracks->empty())){
    if(debug){ //linea da rimuovere-> preente solo perche quella precedente non funziona
      //      TracktoGEM TrackClass(alltracks.product(), iSetup, debug, trackTransformerParam, tracks_);
      //      iEvent.put(std::move(TrackClass.thePoints()), "GEMTrackExtrapolatedPoints");
    }else{
      if(debug) std::cout<<"GEMHLT Invalid Tracks collection"<<std::endl;
    }
  }
 
}
