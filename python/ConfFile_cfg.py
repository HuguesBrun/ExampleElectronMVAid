import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
                                      #the mini-AOD file with the MVA
                                      'file:/afs/cern.ch/user/h/hbrun/CMSSW_7_0_6_patch3_miniAOD/src/miniAOD-prod_PAT.root'
    )
)

process.exampleAnalyzer = cms.EDAnalyzer('ExampleElectronMVAid',
                                         electronsCollection       	= cms.InputTag("slimmedElectrons","","PAT"),
                                         MVAId                       = cms.InputTag("mvaTrigV050nsCSA14","","addMVAid"), #not used when running on PAT
                                         outputFile		        = cms.string("ElecMVAtree.root")
                                         )

process.p = cms.Path(process.exampleAnalyzer)
