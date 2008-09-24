import FWCore.ParameterSet.Config as cms

selectedElectrons = cms.EDFilter("HWWElectronSelection",
                                 src = cms.InputTag("pixelMatchGsfElectrons"),
                                 electronIdCutsLabel = cms.InputTag("egammaIDCutsLoose"),
                                 electronIdLikelihoodLabel = cms.InputTag("egammaIDLikelihood"),
                                 useCuts = cms.bool(True)
                                 # likelihoodThreshold_ = cms.double(0.5)
                                 )
