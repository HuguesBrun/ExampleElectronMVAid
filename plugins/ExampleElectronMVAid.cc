#include "ExampleElectronMVAid.h"



ExampleElectronMVAid::ExampleElectronMVAid(const edm::ParameterSet& iConfig)

{
    electronsCollection_      = iConfig.getParameter<edm::InputTag>("electronsCollection");
    MVAidCollection_      = iConfig.getParameter<edm::InputTag>("MVAId");
    outputFile_   = iConfig.getParameter<std::string>("outputFile");
    rootFile_ = TFile::Open(outputFile_.c_str(),"RECREATE");
}


ExampleElectronMVAid::~ExampleElectronMVAid()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ExampleElectronMVAid::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    beginEvent(); //create the vectors
    
    ///load the collections:
    edm::Handle<vector<pat::Electron>> electronsCollection;
    iEvent.getByLabel(electronsCollection_ , electronsCollection);
    
    const vector<pat::Electron> * theElectrons = electronsCollection.product();
    
    
    T_Event_RunNumber = iEvent.id().run();
    T_Event_EventNumber = iEvent.id().event();
    T_Event_LuminosityBlock = iEvent.id().luminosityBlock();
    
    
    
    unsigned int nbElectron =  theElectrons->size();
    
    for(unsigned i = 0 ; i < nbElectron; i++){

        T_Elec_Eta->push_back((theElectrons->at(i)).eta());
        T_Elec_Phi->push_back((theElectrons->at(i)).phi());
        T_Elec_Px->push_back((theElectrons->at(i)).px());
        T_Elec_Py->push_back((theElectrons->at(i)).py());
        T_Elec_Pz->push_back((theElectrons->at(i)).pz());
        T_Elec_Pt->push_back((theElectrons->at(i)).pt());
        T_Elec_Energy->push_back((theElectrons->at(i)).energy());
        T_Elec_Charge->push_back((theElectrons->at(i)).charge());
        
        T_Elec_MVAoutput->push_back((theElectrons->at(i)).electronID("trigMVAid"));

    }
    
    mytree_->Fill();
    
    endEvent();

}


// ------------ method called once each job just before starting event loop  ------------
void 
ExampleElectronMVAid::beginJob()
{
    mytree_ = new TTree("eventsTree","");
    mytree_->Branch("T_Event_RunNumber", &T_Event_RunNumber, "T_Event_RunNumber/I");
    mytree_->Branch("T_Event_EventNumber", &T_Event_EventNumber, "T_Event_EventNumber/I");
    mytree_->Branch("T_Event_LuminosityBlock", &T_Event_LuminosityBlock, "T_Event_LuminosityBlock/I");

    mytree_->Branch("T_Elec_Eta", "std::vector<float>", &T_Elec_Eta);
    mytree_->Branch("T_Elec_Phi", "std::vector<float>", &T_Elec_Phi);
    mytree_->Branch("T_Elec_Px", "std::vector<float>", &T_Elec_Px);
    mytree_->Branch("T_Elec_Py", "std::vector<float>", &T_Elec_Py);
    mytree_->Branch("T_Elec_Pz", "std::vector<float>", &T_Elec_Pz);
    mytree_->Branch("T_Elec_Pt", "std::vector<float>", &T_Elec_Pt);
    mytree_->Branch("T_Elec_Energy", "std::vector<float>", &T_Elec_Energy);
    mytree_->Branch("T_Elec_Charge", "std::vector<int>", &T_Elec_Charge);
    mytree_->Branch("T_Elec_MVAoutput", "std::vector<float>", &T_Elec_MVAoutput);



}



// ------------ method called once each job just after ending the event loop  ------------
void 
ExampleElectronMVAid::endJob() 
{
    rootFile_->Write();
    rootFile_->Close();
}


void
ExampleElectronMVAid::beginEvent()
{
    T_Elec_Eta = new std::vector<float>;
    T_Elec_Phi = new std::vector<float>;
    T_Elec_Px = new std::vector<float>;
    T_Elec_Py = new std::vector<float>;
    T_Elec_Pz = new std::vector<float>;
    T_Elec_Pt = new std::vector<float>;
    T_Elec_Energy = new std::vector<float>;
    T_Elec_Charge = new std::vector<int>;
    T_Elec_MVAoutput = new std::vector<float>;
    
}

void
ExampleElectronMVAid::endEvent()
{
    delete T_Elec_Eta;
    delete T_Elec_Phi;
    delete T_Elec_Px;
    delete T_Elec_Py;
    delete T_Elec_Pz;
    delete T_Elec_Pt;
    delete T_Elec_Energy;
    delete T_Elec_Charge;
    delete T_Elec_MVAoutput;
    
}

// ------------ method called when starting to processes a run  ------------
/*
void 
ExampleElectronMVAid::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
ExampleElectronMVAid::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
ExampleElectronMVAid::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
ExampleElectronMVAid::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ExampleElectronMVAid::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters

}

//define this as a plug-in
DEFINE_FWK_MODULE(ExampleElectronMVAid);
