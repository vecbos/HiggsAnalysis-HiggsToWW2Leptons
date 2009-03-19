#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/EleTrackerIsolationAlgo.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronIsoCollection.h"
#include "DataFormats/Candidate/interface/CandAssociation.h"
#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWElectronIsolator.h"


HWWElectronIsolator::HWWElectronIsolator(const edm::ParameterSet& iConfig)
{
  selectedElectronsRefLabel_ = iConfig.getParameter<InputTag>("SelectedElectronRefCollectionLabel");
  trackIsolationProducer_    = iConfig.getParameter<InputTag>("TrackIsolationProducerLabel");
  doRefCheck_		     = iConfig.getParameter<bool>("doRefCheck");
  theTrackIsolCut_	     = iConfig.getParameter<double>("TrackIsolCut");
}


HWWElectronIsolator::~HWWElectronIsolator()
{
}

void HWWElectronIsolator::select(edm::Handle<reco::GsfElectronCollection> electrons,
                                 const edm::Event& iEvent,
		                 const edm::EventSetup& iEventSetup)
{
  using namespace edm;
  using namespace reco;
  using namespace std;

  selected_.clear();
  Handle<RefVector<GsfElectronCollection> > electronsRef;


  edm::Handle< edm::ValueMap<double> > tkIsolationHandle;
  try { iEvent.getByLabel(trackIsolationProducer_, tkIsolationHandle); }
  catch ( cms::Exception& ex ) { printf("Can't get tracker isolation product\n"); }

  const edm::ValueMap<double>& tkIsolationVal = *tkIsolationHandle;

  if(doRefCheck_==true)
    iEvent.getByLabel(selectedElectronsRefLabel_,electronsRef);

  for(unsigned i =0; i<electrons->size(); i++) {
    
    Ref<reco::GsfElectronCollection> electronRAWRef(electrons,i);
    double sumPt = tkIsolationVal[electronRAWRef];
     
    bool selected=true;
    if(doRefCheck_==true) {
      if (find(electronsRef->begin(), electronsRef->end(),electronRAWRef)==electronsRef->end()) {
	selected=false;
      }
    }

    if (sumPt < theTrackIsolCut_ && selected==true)
      selected_.push_back(electronRAWRef);
  }
}
