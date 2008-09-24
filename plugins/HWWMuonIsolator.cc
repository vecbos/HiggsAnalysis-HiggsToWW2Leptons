// -*- C++ -*-
//
// Package:    MuonIsolatorProducer
// Class:      MuonIsolatorProducer
// 
/**\class MuonIsolatorProducer MuonIsolatorProducer.cc MyProducer/MuonIsolatorProducer/src/MuonIsolatorProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Thomas Punz
//         Created:  Fri Jan 25 17:54:06 CET 2008
// $Id: HWWMuonIsolator.cc,v 1.2 2008/06/12 14:38:52 ceballos Exp $
//
//


// system include files
#include <memory>


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"

#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWMuonIsolator.h"


HWWMuonIsolator::HWWMuonIsolator(const edm::ParameterSet& iConfig)
{
  using namespace edm;  

  selectedMuonsRefLabel_=iConfig.getParameter<InputTag>("SelectedMuonRefCollectionLabel");

  theTrackerIsoDepositLabel = iConfig.getParameter<InputTag>( "trackerIsoDepositLabel");
  theEcalIsoDepositLabel    = iConfig.getParameter<InputTag>( "ecalIsoDepositLabel");
  theHcalIsoDepositLabel    = iConfig.getParameter<InputTag>( "hcalIsoDepositLabel");

  theTrackIsolCut   = iConfig.getParameter<double>("trackIsolCut"); 
  theCaloIsolCut    = iConfig.getParameter<double>("caloIsolCut"); 
  doRefCheck_=iConfig.getParameter<bool>("doRefCheck");

//	produces<reco::MuonCollection>();
}

HWWMuonIsolator::~HWWMuonIsolator()
{
}

void
HWWMuonIsolator::select(edm::Handle<reco::MuonCollection> muons,
                        const edm::Event& iEvent,
		        const edm::EventSetup& iEventSetup)
{
  using namespace edm;
  using namespace reco;
  using namespace std;

  selected_.clear();
  double muonTrackerDeposit30 = -9999;  
  double muonEcalDeposit30    = -9999; 
  double muonHcalDeposit30    = -9999;

  Handle<RefVector<MuonCollection> >muonsRef;
  if(doRefCheck_==true)
  	  iEvent.getByLabel(selectedMuonsRefLabel_,muonsRef);


  bool muTrackIsol=false;
  bool muCaloIsol=false;

  for (unsigned i = 0;i<muons->size(); i++){ 
  	  muTrackIsol = false;
  	  muCaloIsol = false;
  	  
  	  muonTrackerDeposit30= (*muons)[i].isolationR03().sumPt;   
  	  muonEcalDeposit30   = (*muons)[i].isolationR03().emEt;   
  	  muonHcalDeposit30   = (*muons)[i].isolationR03().hadEt; 
  	  
  	  // *** tracker isolation cut
  	  if(muonTrackerDeposit30 < theTrackIsolCut){ muTrackIsol = true;}
  	  
  	  // *** calo isolation cut 
  	  if( muonEcalDeposit30+muonHcalDeposit30 < theCaloIsolCut){ muCaloIsol = true;}

  	  Ref<MuonCollection>muonRAWRef(muons,i);
  	  bool selected=true;
  	  if(doRefCheck_==true)
  		  if (find(muonsRef->begin(), muonsRef->end(),muonRAWRef)==muonsRef->end())
  		  {
  			  selected=false;
  			  //cout<<"Isolated muon without ID"<<endl;
  		  }
  	  
  	  if(muTrackIsol==true && muCaloIsol == true && selected==true)
  	  {
  		  selected_.push_back(muonRAWRef);
  	  }
  } // loop over muons

  // using the muIsoDeposit association map:  
  /*
   
   
   // ---> get the muons collection and isolation maps from the event
   Handle<reco::MuonCollection> muonsHandle;
   iEvent.getByLabel(theMuonLabel,muonsHandle);
   
   edm::Handle<reco::MuIsoDepositAssociationMap> trackerIso;
   iEvent.getByLabel(theTrackerIsoDepositLabel, trackerIso);
   
   edm::Handle<reco::MuIsoDepositAssociationMap> ecalIso;
   iEvent.getByLabel(theEcalIsoDepositLabel, ecalIso);
   
   edm::Handle<reco::MuIsoDepositAssociationMap> hcalIso;
   iEvent.getByLabel(theHcalIsoDepositLabel, hcalIso);
   
   
   const MuonCollection *muons = muonsHandle.product();
   MuonCollection::const_iterator muon;
   
   bool muTrackIsol = false;
   bool muCaloIsol = false;
   
   for (muon = muons->begin(); muon != muons->end(); muon++){ 
   
   muTrackIsol = false;
   muCaloIsol = false;
   
   const reco::MuIsoDeposit & dept = (*trackerIso)[muon->combinedMuon()];
   const reco::MuIsoDeposit & depe =	(*ecalIso)[muon->combinedMuon()];
   const reco::MuIsoDeposit & deph =	(*hcalIso)[muon->combinedMuon()];
   
   muonTrackerDeposit30= dept.depositWithin(0.3);   
   muonEcalDeposit30   = depe.depositWithin(0.3);   
   muonHcalDeposit30   = deph.depositWithin(0.3); 
   
   
   cout << muon->getIsolationR03().sumPt << " versus " << muonTrackerDeposit30 << endl;
   cout << muon->getIsolationR03().emEt + muon->getIsolationR03().hadEt << " versus " << 
   muonEcalDeposit30+muonHcalDeposit30 << endl;
   
   
   
   // *** tracker isolation cut
   hTrackIsol->Fill(muonTrackerDeposit30, 1.);  
   if(muonTrackerDeposit30 < theTrackIsolCut){ muTrackIsol = true;}
   
   // *** calo isolation cut 
       hCaloIsol->Fill(muonEcalDeposit30+muonHcalDeposit30, 1.);  
       if( muonEcalDeposit30+muonHcalDeposit30 < theCaloIsolCut){ muCaloIsol = true;}
       
       } // loop over muons
       */
}
//define this as a plug-in
//DEFINE_FWK_MODULE(HWWMuonIsolator);
