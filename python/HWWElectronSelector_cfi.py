import FWCore.ParameterSet.Config as cms

selectedElectrons = cms.EDFilter("HWWElectronSelection",
                                 src              = cms.InputTag("gsfElectrons"),
				 hoverCut         = cms.double(0.150),
				 sigmaetaetaEBCut = cms.double(0.015),
				 sigmaetaetaEECut = cms.double(0.035),
				 deltaphiinCut    = cms.double(0.100),
				 deltaetainCut    = cms.double(0.011)
                                 )
