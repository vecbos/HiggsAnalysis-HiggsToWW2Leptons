#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/EleTrackerIsolationAlgo.h"
#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWElectronIsolator.h"


HWWElectronIsolator::HWWElectronIsolator(const edm::ParameterSet& iConfig)
{
  //electronsLabel_=iConfig.getParameter<InputTag>("ElectronCollectionLabel");
  selectedElectronsRefLabel_ =iConfig.getParameter<InputTag>("SelectedElectronRefCollectionLabel");
  tracksLabel_  	     =iConfig.getParameter<InputTag>("TrackCollectionLabel");
  doRefCheck_		     =iConfig.getParameter<bool>("doRefCheck");
  extRadius_		     =iConfig.getParameter<double>("ExtRadius");
  intRadius_		     =iConfig.getParameter<double>("IntRadius");  
  theTrackIsolCut_	     =iConfig.getParameter<double>("TrackIsolCut");
}


HWWElectronIsolator::~HWWElectronIsolator()
{
}

void HWWElectronIsolator::select(edm::Handle<reco::PixelMatchGsfElectronCollection> electrons, const edm::Event& iEvent)
{
  using namespace edm;
  using namespace reco;
  using namespace std;

  selected_.clear();
  Handle<TrackCollection>tracks;
  Handle<RefVector<PixelMatchGsfElectronCollection> >electronsRef;

  iEvent.getByLabel(tracksLabel_,tracks);
  if(doRefCheck_==true)
    iEvent.getByLabel(selectedElectronsRefLabel_,electronsRef);

  const TrackCollection tracksC= (*tracks.product());

  for(unsigned i =0; i<electrons->size(); i++)
  {
     EleTrackerIsolationAlgo* trackIsolation = new EleTrackerIsolationAlgo(&(*electrons)[i],tracksC);
     
     trackIsolation->setExtRadius(extRadius_);
     trackIsolation->setIntRadius(intRadius_);
     
     float sumPt_tracker = trackIsolation->getPtTracks();
     Ref<reco::PixelMatchGsfElectronCollection> electronRAWRef(electrons,i);
     
     bool selected=true;
     if(doRefCheck_==true)
       if (find(electronsRef->begin(), electronsRef->end(),electronRAWRef)==electronsRef->end())
       {
         selected=false;
       }

     if (sumPt_tracker/(*electrons)[i].pt()< theTrackIsolCut_ && selected==true)
     {
       selected_.push_back(electronRAWRef);
     }
  }
}





