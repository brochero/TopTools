
#include<vector>
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include<iostream>


/***************************
  SF: ID, ISO and Trigger
***************************/
      
void SFIDISOTrigger(std::vector<float> &result,
		    TLorentzVector Lep0, TLorentzVector Lep1, int channel,
		    TH2F *hmuIDSF, TH2F *hmumuTriggerSF,
		    TH2F *heIDSF, TH2F *heeTriggerSF,
		    TH2F *hmueTriggerSF){

  /***************************
    SF: ID, ISO and Trigger
  ***************************/
  float SF_ID_ISO=1.0;
  float SF_ID_ISO_Error=0.0;
  float SF_Tr=1.0;
  float SF_Tr_Error=0.0;

  float SF_ID_ISO_Tr=1.0;

  // LEGACY
  int NbinmuEta=8;
  int NbinmuPt =10;
  float VbinmuEta[9] = {-2.4 , -2.1 , -1.2 , -0.9 , 0.0 , 0.9 , 1.2 , 2.1 , 2.4}; // muon Eta values
  float VbinmuPt[11] = {10, 20 , 25 , 30 , 35 , 40 , 50, 60 , 90, 140 , 1000}; // muon Pt values

  // int NbineEta=10;
  // int NbinePt =4;
  // float VbineEta[11]={-2.5 , -2.0 , -1.556 , -1.442 , -0.8 , 0.0 , 0.8 , 1.442 , 1.556 , 2.0 , 2.5}; // electron Eta values
  // float VbinePt[5] ={20 , 30 , 40 , 50 , 1000}; // electron Pt values

  // LEGACY
  int NbineEta=8;
  int NbinePt =4;
  float VbineEta[9]={-2.5 , -1.556 , -1.4442 , -0.8 , 0.0 , 0.8 , 1.4442 , 1.556 , 2.5}; // electron Eta values
  float VbinePt[5] ={20 , 30 , 40 , 50 , 1000}; // electron Pt values

  float SFLep0[2]={0.0 , 0.0};// [0]=muon && [1]=electron
  float SFLep1[2]={0.0 , 0.0};
  float SFErrorLep0[2]={0.0 , 0.0};// [0]=muon && [1]=electron
  float SFErrorLep1[2]={0.0 , 0.0};

  float VbinTrmumuEta[5]={0.0 , 0.9 , 1.2 , 2.1 , 2.4};
  float VbinTreeEta[3]  ={0.0 , 1.479 , 2.5};
  float VbinXTrmueEta[3]={0.0 , 1.479 , 2.5}; // electron
  float VbinYTrmueEta[3]={0.0 , 1.2 , 2.4}; // muon

  int NXTrmumubinEta=4;
  int NYTrmumubinEta=4;
  int NXTreebinEta=2;
  int NYTreebinEta=2;

  int NXTrmuebinEta=2;
  int NYTrmuebinEta=2;

  float SFTrmumu=0.0;
  float SFTree=0.0;
  float SFTrmue=0.0;
  float SFTremu=0.0;

  float SFErrorTrmumu=0.0;
  float SFErrorTree=0.0;
  float SFErrorTrmue=0.0;
  float SFErrorTremu=0.0;

  /***************************
         Lepton 0: muon 
  ***************************/
  
  for(int binmuPt=0;binmuPt<NbinmuPt;binmuPt++){
    if(Lep0.Pt()>VbinmuPt[binmuPt] && Lep0.Pt()<=VbinmuPt[binmuPt+1]){ 
      
      for(int binmuEta=0;binmuEta<NbinmuEta;binmuEta++){
	if(Lep0.Eta()>VbinmuEta[binmuEta] && Lep0.Eta()<=VbinmuEta[binmuEta+1]){ 
	  SFLep0[0]=hmuIDSF->GetBinContent(binmuEta+1,binmuPt+1);
	  SFErrorLep0[0]=hmuIDSF->GetBinError(binmuEta+1,binmuPt+1);
	  break;
	}// if(Lep0.Eta())
      }// for(binmuEta)
      
    }// if(Lep0.Pt())
  }// for(binmuPt)
  
  /***************************
       Lepton 0: electron
  ***************************/
  
  for(int binePt=0;binePt<NbinePt;binePt++){
    if(Lep0.Pt()>VbinePt[binePt] && Lep0.Pt()<=VbinePt[binePt+1]){ 
      
      for(int bineEta=0;bineEta<NbineEta;bineEta++){
	if(Lep0.Eta()>VbineEta[bineEta] && Lep0.Eta()<=VbineEta[bineEta+1]){ 
	  SFLep0[1]=heIDSF->GetBinContent(bineEta+1,binePt+1);
	  SFErrorLep0[1]=heIDSF->GetBinError(bineEta+1,binePt+1);
	  break;
	}// if(Lep0.Eta())
      }// for(bineEta)
      
    }// if(Lep0.Pt())
  }// for(binePt)
  
  
  /***************************
        Lepton 1: muon 
  ***************************/
  
  for(int binmuPt=0;binmuPt<NbinmuPt;binmuPt++){
    if(Lep1.Pt()>VbinmuPt[binmuPt] && Lep1.Pt()<=VbinmuPt[binmuPt+1]){ 
      
      for(int binmuEta=0;binmuEta<NbinmuEta;binmuEta++){
	if(Lep1.Eta()>VbinmuEta[binmuEta] && Lep1.Eta()<=VbinmuEta[binmuEta+1]){ 
	  SFLep1[0]=hmuIDSF->GetBinContent(binmuEta+1,binmuPt+1);
	  SFErrorLep1[0]=hmuIDSF->GetBinError(binmuEta+1,binmuPt+1);
	  break;
	}// if(Lep1.Eta())
      }// for(binmuEta)
      
    }// if(Lep1.Pt())
  }// for(binmuPt)
  
  /***************************
          Lepton 1: electron 
  ***************************/
  
  for(int binePt=0;binePt<NbinePt;binePt++){
    if(Lep1.Pt()>VbinePt[binePt] && Lep1.Pt()<=VbinePt[binePt+1]){ 
      
      for(int bineEta=0;bineEta<NbineEta;bineEta++){
	if(Lep1.Eta()>VbineEta[bineEta] && Lep1.Eta()<=VbineEta[bineEta+1]){ 
	  SFLep1[1]=heIDSF->GetBinContent(bineEta+1,binePt+1);
	  SFErrorLep1[1]=heIDSF->GetBinError(bineEta+1,binePt+1);
	  break;
	}// if(Lep1.Eta())
      }// for(bineEta)
      
    }// if(Lep1.Pt())
  }// for(binePt)
  
  
  //////////////////
  // Trigger mumu //
  //////////////////
  
  for(int binXTrEta=0;binXTrEta<NXTrmumubinEta;binXTrEta++){
    if(fabs(Lep0.Eta())>VbinTrmumuEta[binXTrEta] && fabs(Lep0.Eta())<=VbinTrmumuEta[binXTrEta+1]){ 
      
      for(int binYTrEta=0;binYTrEta<NYTrmumubinEta;binYTrEta++){
	if(fabs(Lep1.Eta())>VbinTrmumuEta[binYTrEta] && fabs(Lep1.Eta())<=VbinTrmumuEta[binYTrEta+1]){ 
	  
	  SFTrmumu=hmumuTriggerSF->GetBinContent(binXTrEta+1,binYTrEta+1);
	  SFErrorTrmumu=hmumuTriggerSF->GetBinError(binXTrEta+1,binYTrEta+1);
	  break;
	  
	}// if(Lep1.Eta())
      }// for(binYTrEta)
      
    }// if(Lep0.Eta())
  }// for(binXTrEta)
  
  
  /////////////////
  // Trigger ee //
  /////////////////
  
  for(int binXTrEta=0;binXTrEta<NXTreebinEta;binXTrEta++){
    if(fabs(Lep0.Eta())>VbinTreeEta[binXTrEta] && fabs(Lep0.Eta())<=VbinTreeEta[binXTrEta+1]){ 
      
      for(int binYTrEta=0;binYTrEta<NYTreebinEta;binYTrEta++){
	if(fabs(Lep1.Eta())>VbinTreeEta[binYTrEta] && fabs(Lep1.Eta())<=VbinTreeEta[binYTrEta+1]){ 
	  
	  SFTree=heeTriggerSF->GetBinContent(binXTrEta+1,binYTrEta+1);
	  SFErrorTree=heeTriggerSF->GetBinError(binXTrEta+1,binYTrEta+1);
	  break;
	  
	}// if(Lep1.Eta())
      }// for(binYTrEta)
      
    }// if(Lep0.Eta())
  }// for(binXTrEta)
  
  /////////////////
  // Trigger emu //
  /////////////////
  
  for(int binXTrEta=0;binXTrEta<NXTrmuebinEta;binXTrEta++){
    if(fabs(Lep0.Eta())>VbinXTrmueEta[binXTrEta] && fabs(Lep0.Eta())<=VbinXTrmueEta[binXTrEta+1]){ 
      
      for(int binYTrEta=0;binYTrEta<NYTreebinEta;binYTrEta++){
	if(fabs(Lep1.Eta())>VbinYTrmueEta[binYTrEta] && fabs(Lep1.Eta())<=VbinYTrmueEta[binYTrEta+1]){ 
	  
	  SFTremu=hmueTriggerSF->GetBinContent(binXTrEta+1,binYTrEta+1);
	  SFErrorTremu=hmueTriggerSF->GetBinError(binXTrEta+1,binYTrEta+1);
	  break;
	  
	}// if(Lep1.Eta())
      }// for(binYTrEta)
      
    }// if(Lep0.Eta())
  }// for(binXTrEta)
  
  /////////////////
  // Trigger mue //
  /////////////////
  
  for(int binXTrEta=0;binXTrEta<NXTrmuebinEta;binXTrEta++){
    if(fabs(Lep1.Eta())>VbinXTrmueEta[binXTrEta] && fabs(Lep1.Eta())<=VbinXTrmueEta[binXTrEta+1]){ 
      
      for(int binYTrEta=0;binYTrEta<NYTreebinEta;binYTrEta++){
	if(fabs(Lep0.Eta())>VbinYTrmueEta[binYTrEta] && fabs(Lep0.Eta())<=VbinYTrmueEta[binYTrEta+1]){ 
	  
	  SFTrmue=hmueTriggerSF->GetBinContent(binXTrEta+1,binYTrEta+1);
	  SFErrorTrmue=hmueTriggerSF->GetBinError(binXTrEta+1,binYTrEta+1);
	  break;
	  
	}// if(Lep0.Eta())
      }// for(binYTrEta)
      
    }// if(Lep1.Eta())
  }// for(binXTrEta)
  
  
  //emu=2;mue=-2
  if(channel==0){// mumu
    SF_ID_ISO=SFLep0[0]*SFLep1[0];
    SF_ID_ISO_Error=((SFLep0[0]+SFErrorLep0[0])*(SFLep1[0]+SFErrorLep1[0])) - (SFLep0[0]*SFLep1[0]);
    SF_Tr=SFTrmumu;
    SF_Tr_Error=SFErrorTrmumu;
    
    SF_ID_ISO_Tr=SFLep0[0]*SFLep1[0]*SFTrmumu;
  }

  if(channel==1){// ee
    SF_ID_ISO=SFLep0[1]*SFLep1[1];
    SF_ID_ISO_Error=((SFLep0[1]+SFErrorLep0[1])*(SFLep1[1]+SFErrorLep1[1])) - (SFLep0[1]*SFLep1[1]);
    SF_Tr=SFTree;
    SF_Tr_Error=SFErrorTree;
    
    SF_ID_ISO_Tr=SFLep0[1]*SFLep1[1]*SFTree;
  }

  if(channel==2){// emu
    SF_ID_ISO=SFLep0[1]*SFLep1[0];
    SF_ID_ISO_Error=((SFLep0[1]+SFErrorLep0[1])*(SFLep1[0]+SFErrorLep1[0])) - (SFLep0[1]*SFLep1[0]);
    SF_Tr=SFTremu;
    SF_Tr_Error=SFErrorTremu;
    
    SF_ID_ISO_Tr=SFLep0[1]*SFLep1[0]*SFTremu;
  }

  if(channel==-2){// mue
    SF_ID_ISO=SFLep0[0]*SFLep1[1];
    SF_ID_ISO_Error=((SFLep0[0]+SFErrorLep0[0])*(SFLep1[1]+SFErrorLep1[1])) - (SFLep0[0]*SFLep1[1]);
    SF_Tr=SFTrmue;
    SF_Tr_Error=SFErrorTrmue;
    
    SF_ID_ISO_Tr=SFLep0[0]*SFLep1[1]*SFTrmue;
  }
  
  
  /*******************************************
   Trigger,ID & ISO Scale Factors/bin(Pt,Eta)
  *******************************************/

  result.push_back(SF_ID_ISO_Tr); //[0]  
  result.push_back(SF_ID_ISO); //[1]  
  result.push_back(SF_ID_ISO_Error); //[2]  
  result.push_back(SF_Tr); //[3]  
  result.push_back(SF_Tr_Error); //[4]  

  if(channel==0){
    result.push_back(SFLep0[0]); //[5]  
    result.push_back(SFErrorLep0[0]); //[6]  
    result.push_back(SFLep1[0]); //[7]  
    result.push_back(SFErrorLep1[0]); //[8]  
  }
  if(channel==1){
    result.push_back(SFLep0[1]); //[5]  
    result.push_back(SFErrorLep0[1]); //[6]  
    result.push_back(SFLep1[1]); //[7]  
    result.push_back(SFErrorLep1[1]); //[8]  
  }
  if(channel==2){
    result.push_back(SFLep0[1]); //[5]  
    result.push_back(SFErrorLep0[1]); //[6]  
    result.push_back(SFLep1[0]); //[7]  
    result.push_back(SFErrorLep1[0]); //[8]  
  }
  if(channel==-2){
    result.push_back(SFLep0[0]); //[5]  
    result.push_back(SFErrorLep0[0]); //[6]  
    result.push_back(SFLep1[1]); //[7]  
    result.push_back(SFErrorLep1[1]); //[8]  
  }
  
}
 
