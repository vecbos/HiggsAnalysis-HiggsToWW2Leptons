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
// Revised by: Emanuele Di Marco
//         Created:  Wed Jan 30 11:13:18 CET 2008
// $Id: HWWElectronSelector.cc,v 1.3 2008/09/24 13:26:17 emanuele Exp $
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
#include "DataFormats/Common/interface/ValueMap.h"

#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWElectronSelector.h"

#include <string.h>

HWWElectronSelector::HWWElectronSelector(const edm::ParameterSet& iConfig)
{
  electronIdCutsLabel_ = iConfig.getParameter<edm::InputTag>("electronIdCutsLabel");
}


HWWElectronSelector::~HWWElectronSelector()
{}


void
HWWElectronSelector::select (edm::Handle<reco::GsfElectronCollection> electrons,
                             const edm::Event& iEvent,
		             const edm::EventSetup& iEventSetup)
{

  using namespace edm;
  using namespace reco;
  selected_.clear();

  std::vector<edm::Handle<edm::ValueMap<float> > > eIDValueMap(2);
  
  if ( iEvent.getByLabel( electronIdCutsLabel_ , eIDValueMap[0] ) ) {

    const edm::ValueMap<float> & eIdmapCuts = * eIDValueMap[0] ;

    // Loop over electrons
    for (unsigned int i = 0; i < electrons->size(); i++) {	  
      Ref<reco::GsfElectronCollection> electronRef(electrons,i);

      bool eleid = false;

      if( eIdmapCuts[electronRef] > 0 ) eleid = true;
      
      if (eleid==true) selected_.push_back (electronRef);
      
    }
  } else {
    LogWarning("HWWElectronSelector") << "Product " << electronIdCutsLabel_ << " not available";
  }

}
