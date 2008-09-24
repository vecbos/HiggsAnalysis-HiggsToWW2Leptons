#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "PhysicsTools/UtilAlgos/interface/ObjectSelector.h"
#include "PhysicsTools/UtilAlgos/interface/SortCollectionSelector.h"
#include "PhysicsTools/Utilities/interface/PtComparator.h"
#include "PhysicsTools/UtilAlgos/interface/PtMinSelector.h"
#include "PhysicsTools/UtilAlgos/interface/SingleElementCollectionSelector.h"
#include "PhysicsTools/UtilAlgos/interface/ObjectCountFilter.h"
#include "PhysicsTools/UtilAlgos/interface/SingleObjectSelector.h"
//#include "PhysicsTools/UtilAlgos/interface/SingleObjectRefVectorSelector.h"
#include "DataFormats/Common/interface/RefVector.h" 

#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWElectronSelector.h"
#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWMuonSelector.h"
#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWElectronIsolator.h"
#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWMuonIsolator.h"
#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWJetCleaner.h"

typedef ObjectSelector<HWWElectronSelector> HWWElectronSelection;
typedef ObjectSelector<HWWElectronSelector, edm::RefVector<reco::GsfElectronCollection> > HWWElectronSelectionRef;
typedef ObjectSelector<HWWMuonSelector> HWWMuonSelection;
typedef ObjectSelector<HWWMuonSelector, edm::RefVector<reco::MuonCollection> > HWWMuonSelectionRef;

typedef ObjectSelector<HWWElectronIsolator> HWWElectronIsolation;
typedef ObjectSelector<HWWElectronIsolator, edm::RefVector<reco::GsfElectronCollection> > HWWElectronIsolationRef;
typedef ObjectSelector<HWWMuonIsolator> HWWMuonIsolation;
typedef ObjectSelector<HWWMuonIsolator, edm::RefVector<reco::MuonCollection> > HWWMuonIsolationRef;
//Jet cleaning
typedef ObjectSelector<HWWJetCleaner> HWWJetCleaning;
typedef ObjectSelector<HWWJetCleaner, edm::RefVector<reco::CaloJetCollection> > HWWJetCleaningRef;

DEFINE_SEAL_MODULE () ;
DEFINE_ANOTHER_FWK_MODULE(HWWElectronSelection);
DEFINE_ANOTHER_FWK_MODULE(HWWElectronSelectionRef);
DEFINE_ANOTHER_FWK_MODULE(HWWMuonSelection);
DEFINE_ANOTHER_FWK_MODULE(HWWMuonSelectionRef);

DEFINE_ANOTHER_FWK_MODULE(HWWElectronIsolation);
DEFINE_ANOTHER_FWK_MODULE(HWWElectronIsolationRef);
DEFINE_ANOTHER_FWK_MODULE(HWWMuonIsolation);
DEFINE_ANOTHER_FWK_MODULE(HWWMuonIsolationRef);
DEFINE_ANOTHER_FWK_MODULE(HWWJetCleaning);
DEFINE_ANOTHER_FWK_MODULE(HWWJetCleaningRef) ;
