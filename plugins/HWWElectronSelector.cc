// -*- C++ -*-
//
// Package:    HWWElectronSelector
// Class:      HWWElectronSelector
// 
/**\class HWWElectronSelector HWWElectronSelector.cc HiggsAnalysis/HWWElectronSelector/src/HWWElectronSelector.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Thomas Punz
//         Created:  Wed Jan 30 11:13:18 CET 2008
// $Id: HWWElectronSelector.cc,v 1.1 2008/02/14 16:06:56 ceballos Exp $
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
#include "AnalysisDataFormats/Egamma/interface/ElectronID.h"
#include "AnalysisDataFormats/Egamma/interface/ElectronIDAssociation.h"

#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWElectronSelector.h"

#include <string.h>

HWWElectronSelector::HWWElectronSelector(const edm::ParameterSet& iConfig)
{
  electronIDAssocProducer_ = iConfig.getParameter<edm::InputTag>("electronIDAssocProducer");
  //	  electronCollectionLabel_ = iConfig.getParameter<edm::InputTag>("electronCollectionLabel");
}


HWWElectronSelector::~HWWElectronSelector()
{}


void
HWWElectronSelector::select (edm::Handle<reco::PixelMatchGsfElectronCollection> electrons,
                             const edm::Event& iEvent,
		             const edm::EventSetup& iEventSetup)
{
  using namespace edm;
  using namespace reco;
  selected_.clear();

  //get Id Association  map
  Handle<ElectronIDAssociationCollection> electronIDAssocHandle;  
  iEvent.getByLabel(electronIDAssocProducer_,electronIDAssocHandle);	  

  ElectronIDAssociationCollection::const_iterator electronIDAssocItr;

  // Loop over electrons
  for (unsigned int i = 0; i < electrons->size(); i++)
  {	  
    Ref<reco::PixelMatchGsfElectronCollection> electronRef(electrons,i);
    electronIDAssocItr = electronIDAssocHandle->find( electronRef );
    const ElectronIDRef& id = electronIDAssocItr->val;
    bool eleid = id->cutBasedDecision();
    if (eleid==true)
      selected_.push_back (electronRef);
    // std::cout << "Event " << iEvent.id() << ", electron " << i << ", cut based ID = " << eleid << std::endl;
  }
}
