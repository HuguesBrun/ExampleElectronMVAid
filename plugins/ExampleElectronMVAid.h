// -*- C++ -*-
//
// Package:    hugues/ExampleElectronMVAid
// Class:      ExampleElectronMVAid
// 
/**\class ExampleElectronMVAid ExampleElectronMVAid.cc hugues/ExampleElectronMVAid/plugins/ExampleElectronMVAid.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Hugues Louis Brun
//         Created:  Tue, 05 Aug 2014 08:01:14 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

#include "DataFormats/Common/interface/ValueMap.h"

#include "TH1D.h"
#include <map>
#include "TFile.h"
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TString.h"
#include "TTree.h"
//
// class declaration
//

class ExampleElectronMVAid : public edm::EDAnalyzer {
   public:
      explicit ExampleElectronMVAid(const edm::ParameterSet&);
      ~ExampleElectronMVAid();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      virtual void beginEvent();
      virtual void endEvent();

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
    edm::InputTag electronsCollection_;
    edm::InputTag MVAidCollection_;
    edm::InputTag TrigMapCollection_;
    
        std::string outputFile_; // output file
        
        

        
        
        // ---------- output ROOT file
        TFile*  rootFile_;
        
        // ---------- tree declaration
        TTree *mytree_;
        
        // -----------tree variables
        //Events
        int T_Event_RunNumber;
        int T_Event_EventNumber;
        int T_Event_LuminosityBlock;
        
        std::vector<float> *T_Elec_Eta;
        std::vector<float> *T_Elec_Phi;
        std::vector<float> *T_Elec_Px;
        std::vector<float> *T_Elec_Py;
        std::vector<float> *T_Elec_Pz;
        std::vector<float> *T_Elec_Pt;
        std::vector<float> *T_Elec_Energy;
        std::vector<int> *T_Elec_Charge;
    std::vector<float> *T_Elec_MVAoutput;
    std::vector<int> *T_Elec_IsTriggering;

};


