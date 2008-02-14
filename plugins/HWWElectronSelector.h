#ifndef HWWELECTRONSELECTOR
#define HWWELECTRONSELECTOR

class HWWElectronSelector  {
 public:
  explicit HWWElectronSelector(const edm::ParameterSet&);
  ~HWWElectronSelector();
  // Collections to be selected
  typedef reco::PixelMatchGsfElectronCollection collection;
  typedef std::vector<reco::PixelMatchGsfElectronRef> ::const_iterator const_iterator;
  //define iterators with above typedef
  const_iterator begin () const { return selected_.begin () ; }
  const_iterator end () const { return  selected_.end () ; }
 
  void select (edm::Handle<reco::PixelMatchGsfElectronCollection>, const edm::Event&) ;
  // ----------member data ---------------------------
 private:
 
  std::vector<reco::PixelMatchGsfElectronRef> selected_ ;
  edm::InputTag electronIDAssocProducer_;
  std::string electronIDAssocProducerProduct_;
};

#endif
