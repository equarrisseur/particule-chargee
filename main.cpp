
#include "Particule.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TFile.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TApplication.h"
#include "TROOT.h"
#include "TF2.h"
#include "TH2.h"
#include "TGraph2D.h"
#include "TStyle.h"
#include<fstream>
#include<iomanip>

using namespace std;


int main(int argc, char **argv){
 TApplication theApp("App", &argc, argv);  
int N =300; // Nombres d'intervalles donc de point BREF 
double ti=0;    
double tf=400000;

ParticuleChargee B(5e-5,0,0,0,0,0,100,100,100);
//                 Bx,By,Bz,Ex,Ey,Ez,Imp0_X,Imp0_Y,Imp0_Z
B.rk4(N,ti,tf);
double x,y,z;

ofstream f;
f.open("Donnees.dat");
//f << setw(20) << "i" << setw(20) <<" u "<< setw(20) << "si"<<setw(20) << "si-sii"<< setw(20) << "si-exp(0.3)" <<endl;
for(int i=0 ; i < N ; i++)
    {
        
       f << setw(20) <<B.getx()[i]<< setw(20)<< B.gety()[i] << setw(20) <<B.getz()[i]<< endl;

    }
f.close();




    //TFile *fichier_root=TFile::Open("Particulechargee.root","RECREATE");
    TCanvas *C=new TCanvas();//"c1","dessin",0,0,900,700);
//C->SetLogy();
  //C->cd();
//TGraph2D *test = new TGraph2D(N, B.getx(),B.gety() ,B.getz());
//test->SetTitle("Trajectoire de la particule");
   TGraph2D *f2 = new TGraph2D();
for(int i= 0;i<N;i++){
x=B.getx()[i];
y=B.gety()[i];
z=B.getz()[i];
cout <<x <<endl << y <<endl<<z <<endl;
f2->SetPoint(i,x,y,z);}
gStyle->SetPalette(1);
   f2->SetMarkerStyle(7);
 f2->SetMarkerSize(1);
  f2->SetLineColor(4);
//f2->GetXaxis()->SetRangeUser(0,1e9);
//f2->GetZaxis()->SetRangeUser(0,1e9);
//f2->GetZaxis()->SetRangeUser(0,1e9);
f2->GetXaxis()->SetTitle("X");
f2->GetYaxis()->SetTitle("Y");
f2->GetZaxis()->SetTitle("Z");
C->Update();

 //TLegend *leg=gPad->BuildLegend();
 // leg->SetFillColor(0);
 
  
//  f2->Write();
 

  f2->SetTitle("Loic la grenouille");
  f2->Draw("pcol");


   //f2->Draw("pcol");
   
   C->SaveAs("Test.png");
 theApp.Run();
  
   //fichier_root->Close();














/*
//B.tracerizi("LOAWL",N);
    TCanvas c1("c1","dessin",900,700);  
  TFile *fichier_root=TFile::Open("Particule","RECREATE");
  TGraph graphe_fonction(N); 
  graphe_fonction.SetName("testts.png");
  graphe_fonction.SetTitle("testts.png"); 


  graphe_fonction.SetMarkerColor(2); 
  graphe_fonction.SetMarkerStyle(20); 
  graphe_fonction.SetLineColor(2); 
  graphe_fonction.SetFillColor(0); 
   
 
  for(int i = 0; i < N; i++ ){
    double imp=B.getPx()[i];
    double imp2=imp*imp;
    double m=1.672e-27;
    double c=299792458;
    double NRJ=sqrt((imp2)*c*c+(m*m*c*c*c*c));
    graphe_fonction.SetPoint(i,i,imp*c*c/NRJ); 
  }
  graphe_fonction.Draw("ALP"); 
 
  (graphe_fonction.GetXaxis())->SetTitle("t"); 
  TLegend *leg=gPad->BuildLegend();
  leg->SetFillColor(0);
  
  graphe_fonction.Write();
 
  c1.SaveAs("testts.png");
   
  fichier_root->Close(); 
    // Affichage des figures si mode interactif (pas en mode batch)
  
if(!gROOT->IsBatch()) theApp.Run(); 
*/
 return 0 ;
}










// TENTATIVE DE GRAOHE 3D
/*
TApplication theApp("App", &argc, argv); 
    
    TCanvas c1("c1","dessin",900,700);  //Canvas pour dessiner
    TFile *fichier_root=TFile::Open("Particulechargee.root","RECREATE");
    TCanvas *C=new TCanvas();
    C->cd();

   TGraph2D *f2 = new TGraph2D();
for(int i= 0;i<100;i++){
x=B.getx()[i];
y=B.gety()[i];
z=B.getz()[i];
f2->SetPoint(100,x,y,z);
   }
  
      
   f2->SetTitle("Trajectoire de la particule");
   f2->Draw("E");
   
   C->SaveAs("Test.png");
   
  //f2->Write();
   
   theApp.Run();
  
   fichier_root->Close();*/

  
