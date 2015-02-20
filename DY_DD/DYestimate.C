#include<vector>
#include <stdio.h>
#include<iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TFile.h"

using namespace std;


int DYestimateValue(TString channel, TString cut, float *result[]){

  TString fl  = "hSF-DDDY_7TeV_v2_TrLe_v1TightObj_5100pb-1";

  if(cut != "dilepton" && cut != "2Jets" && cut != "MET" && cut != "1btag") return 1;
  if ( !channel.Contains("mumu") && !channel.Contains("ee") ) return 1; 

  
  float DYMC_in  = 0.;
  float DYMC_out = 0.;
  
  float Entries_DYMC_in  = 0.;
  float Entries_DYMC_out = 0.;
  
  float EvData_in_mumu = 0.;
  float EvData_in_ee = 0.;

  float EvData_in = 0.;
  float EvData_in_mue = 0.;

  
  // MC: Drell-Yan
  //TFile *fMC = TFile::Open("/gpfs/csic_projects/cms/brochero/ttbar/TopCodeLegacy/TopResults/"+fl+"_ZDY.root");
  TFile *fMC = TFile::Open("/home/brochero/ttbar/TopCodeLegacy/TopResults/"+fl+"_ZDY.root");
 
  TString htitle_Z_In  = "hDYIn_" + channel + "_" + cut;
  TString htitle_Z_Out = "hDYOut_" + channel + "_" + cut;

  TH1F* dummy;

  dummy = (TH1F*) fMC->Get(htitle_Z_In);
  Entries_DYMC_in  = dummy->GetEntries(); // Entries 
  DYMC_in  = dummy->Integral(-1,1000);    // Events


  dummy = (TH1F*) fMC->Get(htitle_Z_Out);
  Entries_DYMC_out  = dummy->GetEntries();// Entries 
  DYMC_out  = dummy->Integral(-1,1000);   // Events

  // Data: Muons
  //TFile *fMu = TFile::Open("/gpfs/csic_projects/cms/brochero/ttbar/TopCodeLegacy/TopResults/"+fl+"_DataMu.root");
  TFile *fMu = TFile::Open("/home/brochero/ttbar/TopCodeLegacy/TopResults/"+fl+"_DataMu.root");
  
  // For k2 error
  TString htitle_In_Data_mumu  = "hDYIn_mumu_2Jets"; //?????????
  dummy = (TH1F*) fMu->Get(htitle_In_Data_mumu);
  EvData_in_mumu  = dummy->Integral(-1,1000);  

  // Data: Electrons
  //TFile *fEG = TFile::Open("/gpfs/csic_projects/cms/brochero/ttbar/TopCodeLegacy/TopResults/"+fl+"_DataEG.root");
  TFile *fEG = TFile::Open("/home/brochero/ttbar/TopCodeLegacy/TopResults/"+fl+"_DataEG.root");

  // For k2 error
  TString htitle_In_Data_ee  = "hDYIn_ee_2Jets"; //????????????????
  dummy = (TH1F*) fEG->Get(htitle_In_Data_ee);
  EvData_in_ee  = dummy->Integral(-1,1000);  

  // Files
  TFile *fData = NULL; 
  if (channel.Contains("mumu"))    fData = fMu;
  else if (channel.Contains("ee")) fData = fEG;

  TString htitle_In_Data  = "hDYIn_" + channel + "_" + cut;
  dummy = (TH1F*) fData->Get(htitle_In_Data);
  EvData_in  = dummy->Integral(-1,1000);  

  // Data: Muons/Electrons (as reference)
  //TFile *fMuEG = TFile::Open("/gpfs/csic_projects/cms/brochero/ttbar/TopCodeLegacy/TopResults/"+fl+"_DataMuEG.root");
  TFile *fMuEG = TFile::Open("/home/brochero/ttbar/TopCodeLegacy/TopResults/"+fl+"_DataMuEG.root");

  TString htitle_In_mue = "hDYIn_mue_" + cut;
  dummy = (TH1F*) fMuEG->Get(htitle_In_mue);
  EvData_in_mue = dummy->Integral(-1,1000);  

  // R 
  cout << "DYMC_out = " << DYMC_out << "\t" << "DYMC_in = " << DYMC_in << endl; 
  float R_noCF = DYMC_out / DYMC_in;
  float err_DYMC_in  = sqrt(Entries_DYMC_in)  * (DYMC_in  / Entries_DYMC_in);
  float err_DYMC_out = sqrt(Entries_DYMC_out) * (DYMC_out / Entries_DYMC_out);
  float err_R2_noCF = R_noCF*R_noCF * ( (err_DYMC_out/DYMC_out)*(err_DYMC_out/DYMC_out) +
                                        (err_DYMC_in/DYMC_in)  *(err_DYMC_in/DYMC_in) );
  float err_R_noCF = sqrt(err_R2_noCF);

  // include Rout/in corrections from data:
  float R, err_R2, err_R;
  float CF_NPV, err_CF_NPV;
  float CF_NJets, err_CF_NJets;
  // if (channel.Contains("mumu")) { CF_NPV = 1.0; err_CF_NPV = 0.0; CF_NJets = 1.0; err_CF_NJets = 0.0;}
  // if (channel.Contains("ee"))   { CF_NPV = 1.0; err_CF_NPV = 0.0; CF_NJets = 1.0; err_CF_NJets = 0.0;}
  // Old version
  if (channel.Contains("mumu")) { CF_NPV = 1.0142; err_CF_NPV = 0.0003; CF_NJets = 1.054; err_CF_NJets = 0.048;}
  if (channel.Contains("ee"))   { CF_NPV = 1.0221; err_CF_NPV = 0.0003; CF_NJets = 1.124; err_CF_NJets = 0.057;}
  // Ana, After NewJEC
  // if (channel.Contains("mumu")) { CF_NPV = 1.04891; err_CF_NPV = 0.0004; CF_NJets = 1.145; err_CF_NJets = 0.052;}
  // if (channel.Contains("ee"))   { CF_NPV = 1.05722; err_CF_NPV = 0.0004; CF_NJets = 1.204; err_CF_NJets = 0.063;}
  // CF: 26/02/2013 with SF
  // if (channel.Contains("mumu")) { CF_NPV = 1.02683; err_CF_NPV = 0.000354263; CF_NJets = 1.1348; err_CF_NJets = 0.052131;}
  // if (channel.Contains("ee"))   { CF_NPV = 1.08112; err_CF_NPV = 0.000409365; CF_NJets = 1.2143; err_CF_NJets = 0.0650496;}
  // CF: 26/02/2013 without SF
  // if (channel.Contains("mumu")) { CF_NPV = 1.05018; err_CF_NPV = 0.000362903; CF_NJets = 1.14559; err_CF_NJets = 0.0525447;}
  // if (channel.Contains("ee"))   { CF_NPV = 1.05949; err_CF_NPV = 0.000394314; CF_NJets = 1.20418; err_CF_NJets = 0.0632952;}
 
  R = R_noCF * CF_NPV * CF_NJets;

  err_R2 = R*R * ( (err_R_noCF/R_noCF)*(err_R_noCF/R_noCF) + 
		   (err_CF_NPV/CF_NPV)*(err_CF_NPV/CF_NPV) + 
                   (err_CF_NJets/CF_NJets)*(err_CF_NJets/CF_NJets) );

  err_R = sqrt(err_R2);

  // k
  float k = 0.;
  if (channel.Contains("mumu"))      k = 0.5 * sqrt((double)EvData_in_mumu/(double)EvData_in_ee);
  else if (channel.Contains("ee"))   k = 0.5 * sqrt((double)EvData_in_ee/(double)EvData_in_mumu);
  cout << "k = " << k << " estimated from histograms!!!!!" <<endl; 

  // Normal  
  // if (channel.Contains("mumu"))      k = 0.572957;
  // else if (channel.Contains("ee"))   k = 0.436333;
  // cout << "k = " << k << " fixed by hand.........." << endl; 

  // 2Jets
  // if (channel.Contains("mumu"))      k = 0.585928;
  // else if (channel.Contains("ee"))   k = 0.426673;
  // cout << "k = " << k << " fixed by hand.........." <<endl; 
  // cout << "WARNING!!! 2Jets k = " << k << " fixed by hand.........." <<endl; 

  // Final Estimation
  float NDY_DD = R * (EvData_in - k*EvData_in_mue);
  cout << "EvData_in= " << EvData_in << "  EvData_in_mue= " << EvData_in_mue <<endl; 
  ///////////// evaluate uncertainty
  float err_k2 = 0.;
  if (channel.Contains("mumu"))      err_k2 = 0.25 * ( (1./(4.*EvData_in_ee)) + (EvData_in_mumu/(4.*EvData_in_ee*EvData_in_ee)) ); 
  else if (channel.Contains("ee"))   err_k2 = 0.25 * ( (1./(4.*EvData_in_mumu)) + (EvData_in_ee/(4.*EvData_in_mumu*EvData_in_mumu)) );

  float err_tmp = EvData_in + k*k*EvData_in_mue + EvData_in_mue*EvData_in_mue*err_k2;

  float err_DY_DD2 = NDY_DD*NDY_DD * ( (err_R2/(R*R)) +  (err_tmp*R*R/(NDY_DD*NDY_DD)) ); 

  float err_DY_DD = sqrt(err_DY_DD2);

  // Output
  // cout << "---------------------------------" << endl;
  // cout << " At " << cut << " level and channel " << channel << endl;
  // cout << "--------------------------------"  << endl;

  // cout << " DY MC :  " << DYMC_out << " +- " << err_DYMC_out << endl;
  // cout << " DY DD :  " << NDY_DD   << " +- " << err_DY_DD    << endl;
  // cout << " R     :  " << R        << " +- " << err_R        << endl;

  // cout << "-------------------------------" << endl;

  float SF_DY=NDY_DD/DYMC_out;
  float err_SF_DY=SF_DY*sqrt((err_DY_DD/NDY_DD)*(err_DY_DD/NDY_DD) +
			     (err_DYMC_out/DYMC_out)*(err_DYMC_out/DYMC_out));

  *result[0]=DYMC_out;     // [0]
  *result[1]=err_DYMC_out; // [1] 
  *result[2]=NDY_DD;       // [2] 
  *result[3]=err_DY_DD;    // [3]

  if (cut == "dilepton"){

    cout << "Dilepton level has no DY estimation!" << endl;
    cout << "DY_MC = DY_DD!!!" << endl;

    *result[4]=1.0  ;        // [4]
  }
  else if(cut == "1btag" && channel.Contains("btag0")){
    *result[4]=0.0;          // [4]  
  }
  else{
    *result[4]=SF_DY;        // [4]
  }
    *result[5]=err_SF_DY;    // [5]
    *result[6]=R;            // [6]
    *result[7]=err_R;        // [7]

  return 0;
}


void DYestimate(){

  float *pMM_dilepton[8],MM_dilepton[8];
  float *pMM_2jets[8],MM_2jets[8];
  float *pEE_2jets[8],EE_2jets[8];
  float *pMM_MET[8],MM_MET[8];
  float *pEE_MET[8],EE_MET[8];
  float *pMM_1btag[8],MM_1btag[8];
  float *pEE_1btag[8],EE_1btag[8];

  for(int j=0;j<8;j++){
    MM_dilepton[j]  = 0.0;
    pMM_dilepton[j] = &MM_dilepton[j];

    MM_2jets[j]  = 0.0;
    pMM_2jets[j] = &MM_2jets[j];

    EE_2jets[j]  = 0.0;
    pEE_2jets[j] = &EE_2jets[j];

    MM_MET[j]  = 0.0;
    pMM_MET[j] = &MM_MET[j];

    EE_MET[j]  = 0.0;
    pEE_MET[j] = &EE_MET[j];

    MM_1btag[j]  = 0.0;
    pMM_1btag[j] = &MM_1btag[j];

    EE_1btag[j]  = 0.0;
    pEE_1btag[j] = &EE_1btag[j];
  }

  //DYestimateValue("mumu","dilepton", pMM_dilepton);
  //DYestimateValue("ee","dilepton", pMM_dilepton);

  DYestimateValue("mumu","2Jets", pMM_2jets);
  DYestimateValue("ee","2Jets", pEE_2jets);

  DYestimateValue("mumu","MET", pMM_MET);
  DYestimateValue("ee","MET", pEE_MET);

  DYestimateValue("mumu","1btag", pMM_1btag);
  DYestimateValue("ee","1btag", pEE_1btag);

  TString filename = Form("/home/brochero/ttbar/TopCodeLegacy/TopResults/DYTables/DYestimate_7TeV_v3.tex");
  FILE* fp = fopen(filename.Data(), "w");

  cout << filename << endl;

  // Save table
  //----------------------------------------------------------------------------
  fprintf(fp,"\\begin{table}[htbp!]\n");
  fprintf(fp,"\\begin{center}\n");
  fprintf(fp,"\\begin{small}\n");


  fprintf(fp,"\\begin{tabular}{|l|c|c|c|}\n");
  fprintf(fp,"\\hline\n");
  fprintf(fp,"  & $\\geq$ 2 jets & $\\geq$ 2 jets + \\MET & $\\geq$ 2 jets + \\MET + $\\geq$ 1 btag \\\\ \\hline \n");
  fprintf(fp,"\\hline\n");
  fprintf(fp, " ee & &  & \\\\ \n");
  fprintf(fp, "%s & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f \\\\ \n", 
	  "$R_{out/in}$", EE_2jets[6], EE_2jets[7], EE_MET[6], EE_MET[7], EE_1btag[6], EE_1btag[7]);
  fprintf(fp, "%s & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f \\\\ \n", 
	  "DY data-driven estimate ",   EE_2jets[2], sqrt(EE_2jets[2]*EE_2jets[2]*(0.3*0.3) + EE_2jets[3]*EE_2jets[3]), 
	  EE_MET[2],   sqrt(EE_MET[2]*(EE_MET[2])*(0.3*0.3) + EE_MET[3]*EE_MET[3]), 
	  EE_1btag[2], sqrt(EE_1btag[2]*(EE_1btag[2])*(0.3*0.3) + EE_1btag[3]*EE_1btag[3]));
  fprintf(fp, "%s & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f \\\\ \n", 
	  "DY MC",                      EE_2jets[0], EE_2jets[1], EE_MET[0], EE_MET[1], EE_1btag[0], EE_1btag[1]);

  float SF_err_EE_2jets=(EE_2jets[2]/EE_2jets[0])*sqrt((1.0/(EE_2jets[0]*EE_2jets[0]))*EE_2jets[1]*EE_2jets[1] + (1.0/(EE_2jets[2]*EE_2jets[2]))*(/*EE_2jets[2]*EE_2jets[2]*(0.3*0.3) +*/ EE_2jets[3]*EE_2jets[3]) );
  float SF_err_EE_MET=(EE_MET[2]/EE_MET[0])*sqrt((1.0/(EE_MET[0]*EE_MET[0]))*EE_MET[1]*EE_MET[1] + (1.0/(EE_MET[2]*EE_MET[2]))*(/*EE_MET[2]*EE_MET[2]*(0.3*0.3) +*/ EE_MET[3]*EE_MET[3]) );
  float SF_err_EE_1btag=(EE_1btag[2]/EE_1btag[0])*sqrt((1.0/(EE_1btag[0]*EE_1btag[0]))*EE_1btag[1]*EE_1btag[1] + (1.0/(EE_1btag[2]*EE_1btag[2]))*(/*EE_1btag[2]*EE_1btag[2]*(0.3*0.3) +*/ EE_1btag[3]*EE_1btag[3]) );

  fprintf(fp,"\\hline \n");
  fprintf(fp, "%s & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f \\\\ \n",
          "SF data/MC",                      EE_2jets[2]/EE_2jets[0], SF_err_EE_2jets, EE_MET[2]/EE_MET[0], SF_err_EE_MET, EE_1btag[2]/EE_1btag[0],SF_err_EE_1btag);
  fprintf(fp,"\\hline \n");
  fprintf(fp,"\\hline\n");
  fprintf(fp, "$\\mumu$ & & & \\\\ \n");
  fprintf(fp, "%s & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f \\\\ \n", 
	  "$R_{out/in}$", MM_2jets[6], MM_2jets[7], MM_MET[6], MM_MET[7], MM_1btag[6], MM_1btag[7]);
  fprintf(fp, "%s & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f \\\\ \n", 
   	  "DY data-driven estimate ",   MM_2jets[2], sqrt( MM_2jets[2]*MM_2jets[2]*(0.3*0.3) + MM_2jets[3]*MM_2jets[3]), 
	  MM_MET[2],   sqrt(MM_MET[2]*MM_MET[2]*(0.3*0.3) + MM_MET[3]*MM_MET[3]), 
	  MM_1btag[2], sqrt(MM_1btag[2]*MM_1btag[2]*(0.3*0.3) + MM_1btag[3]*MM_1btag[3]));
  fprintf(fp, "%s & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f & %.1f $\\pm$ %.1f \\\\ \n", 
	  "DY MC",                      MM_2jets[0], MM_2jets[1], MM_MET[0], MM_MET[1], MM_1btag[0], MM_1btag[1]);;

  float SF_err_MM_2jets=(MM_2jets[2]/MM_2jets[0])*sqrt((1.0/(MM_2jets[0]*MM_2jets[0]))*MM_2jets[1]*MM_2jets[1] + (1.0/(MM_2jets[2]*MM_2jets[2]))*(/*MM_2jets[2]*MM_2jets[2]*(0.3*0.3) +*/ MM_2jets[3]*MM_2jets[3]) );
  float SF_err_MM_MET=(MM_MET[2]/MM_MET[0])*sqrt((1.0/(MM_MET[0]*MM_MET[0]))*MM_MET[1]*MM_MET[1] + (1.0/(MM_MET[2]*MM_MET[2]))*(/*MM_MET[2]*MM_MET[2]*(0.3*0.3) +*/ MM_MET[3]*MM_MET[3]) );
  float SF_err_MM_1btag=(MM_1btag[2]/MM_1btag[0])*sqrt((1.0/(MM_1btag[0]*MM_1btag[0]))*MM_1btag[1]*MM_1btag[1] + (1.0/(MM_1btag[2]*MM_1btag[2]))*(/*MM_1btag[2]*MM_1btag[2]*(0.3*0.3) +*/ MM_1btag[3]*MM_1btag[3]) );

  fprintf(fp,"\\hline \n");
  fprintf(fp, "%s & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f \\\\ \n",
          "SF data/MC",                      MM_2jets[2]/MM_2jets[0],SF_err_MM_2jets, MM_MET[2]/MM_MET[0],SF_err_MM_MET, MM_1btag[2]/MM_1btag[0],SF_err_MM_1btag); 
  fprintf(fp,"\\hline\n");
  fprintf(fp,"\\end{tabular}\n");
  fprintf(fp,"\\end{small}\n");
  fprintf(fp,"\\end{center}\n");
  fprintf(fp,"\\caption{Drell-Yan data-driven estimate in the \\eepm\\ and \\mmpm\\ channels compared with simulation for several steps of the analysis.}\\label{tab:dy}\n");
  fprintf(fp,"\\end{table}\n");
  
  fclose(fp);

}
