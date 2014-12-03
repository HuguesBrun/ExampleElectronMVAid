import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
                                      #the mini-AOD file with the MVA
                                      '/store/mc/Phys14DR/DYJetsToLL_M-50_13TeV-madgraph-pythia8/MINIAODSIM/PU4bx50_PHYS14_25_V1-v1/00000/080957A7-C36E-E411-A5BC-00266CF327C4.root'
    )
)

process.exampleAnalyzer = cms.EDAnalyzer('ExampleElectronMVAid',
                                         electronsCollection       	= cms.InputTag("slimmedElectrons","","PAT"),
                                         MVAId                       = cms.InputTag("mvaTrigV050nsCSA14","","addMVAid"), #not used when running on PAT
                                         outputFile		        = cms.string("ElecMVAtree.root")
                                         )

process.p = cms.Path(process.exampleAnalyzer)
