
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
using namespace std;

using namespace std;
// CONSTRUCTEUR CLASS CHAMP EMG          
ChampEMG::ChampEMG(double Bx,double By, double Bz, double Ex,double Ey,double Ez){
double Bi[3]={Bx,By,Bz};
double Ei[3]={Ex,Ey,Ez};
Vecteur b(3,Bi);
Vecteur a(3,Ei);
B=b;
E=a;
}
//============================

// METHODE POUR CHANGER COMPOSANTES DU CHAMP EMG ====
void ChampEMG::set_B(double Bx,double By,double Bz){
   B(1)=Bx; B(2)=By; B(3)=Bz;
}       
void ChampEMG::set_E(double Ex,double Ey,double Ez) {        
   E(1)=Ex; E(2)=Ey ; E(3)=Ez;
}
//===============================


//CONSTRUCTEUR CLASS PARTICULE CHARGEE ========
ParticuleChargee:: ParticuleChargee(double Bx,double By,double Bz,double Ex,double Ey,double Ez,double Vx0,double Vy0,double Vz0) :ChampEMG( Bx, By, Bz,  Ex, Ey, Ez) {
   q=1.6e-19;
   m=1.672e-27;
   gamma=1/(sqrt(1-((Vx0*Vx0+Vy0*Vy0+Vz0*Vz0)/(c*c))));
   //cout<<"gamma= "<<gamma<<endl;
   //cout << B << "   b  "<< E<<endl;
   double a[3]={Vx0*m*gamma,Vy0*m*gamma,Vz0*m*gamma};
   Vecteur p(3,a);
   Imp_0=p;
   //cout << "Imp  " << Imp_0<<endl;
}
//==============================

//DESTRUCTEUR CLASS PARTICULE CHARGEE ======
ParticuleChargee::~ParticuleChargee(){
	delete[] xtab;
	delete[] ytab;
	delete[] ztab;
	delete[] Pxtab;
	delete[] Pytab;
	delete[] Pztab;

}
//====================

// Methode -> masse et charge
 void ParticuleChargee::set_m(double masse){
 m=masse;
}
 void ParticuleChargee::set_q(double charge){
 q=charge;
}
//===================

//ECRITURE DES EQUATIONS =======
Vecteur ParticuleChargee::f(double t, Vecteur y ){
   Vecteur fonction(6);

   EE=sqrt((y(1)*y(1)+y(2)*y(2)+y(3)*y(3))+m*m*c*c);
   EE=EE*c;
   fonction(1)=(q/c)*(E(1)+(B(3)*y(2)-B(2)*y(3))*(c*c/EE));
   fonction(2)=(q/c)*(E(2)+(B(1)*y(3)-B(3)*y(1))*(c*c/EE));
   fonction(3)=(q/c)*(E(3)+(B(2)*y(1)-B(1)*y(2))*(c*c/EE)); 
 
   fonction(4)=y(1)*(c*c/EE);
   fonction(5)=y(2)*(c*c/EE);
   fonction(6)=y(3)*(c*c/EE);
 return fonction; 
}
//================

//RESOLUTION DES EQUATIONS AVEC RK4
Vecteur ParticuleChargee::rk4(int N, double t0, double tf){
double h =(tf-t0)/N;
xtab = new double[N];
ytab = new double[N];
ztab = new double[N];
Pxtab = new double[N];
Pytab = new double[N];
Pztab = new double[N];
double T0[6]={Imp_0(1),Imp_0(2),Imp_0(3),1,1,1};
Vecteur y(6,T0);

Vecteur k1(6),k2(6),k3(6),k4(6);
for(int i=1; i<=N ;i++){
xtab[i-1]=y(4);
ytab[i-1]=y(5);
ztab[i-1]=y(6);
Pxtab[i-1]=y(1);
Pytab[i-1]=y(2);
Pztab[i-1]=y(3);
//cout<< y<<endl;
double tn=t0+(i-1)*h;
k1=h*f(tn,y);
k2=h*f(tn+h/2,y+1./2*k1);
k3=h*f(tn+h/2,y+1./2*k2);
k4=h*f(tn+h,y+k3);
y=y+(k1+2*(k2+k3)+k4)/6;
} 
return y;
}

/*void ParticuleChargee::tracerizi(const char * nom_fichier, int N){
 
   TCanvas c1("c1","dessin",900,700);  
  TFile *fichier_root=TFile::Open("Particule","RECREATE");
  TGraph graphe_fonction(N); 
  graphe_fonction.SetName(nom_fichier);
  graphe_fonction.SetTitle(nom_fichier); 


  graphe_fonction.SetMarkerColor(2); 
  graphe_fonction.SetMarkerStyle(20); 
  graphe_fonction.SetLineColor(2); 
  graphe_fonction.SetFillColor(0); 
   
 
  for(int i = 0; i < N; i++ ){
    double imp=Pxtab[i];
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
 
  c1.SaveAs(nom_fichier);
   
  fichier_root->Close(); 
    // Affichage des figures si mode interactif (pas en mode batch)
 
      
}*/


//=============================


/* tracer en trois dimensions 
void EDO1Systeme::ecrirexyzROOT(const char * nom_fichier)
{
  TFile fichier( nom_fichier , "RECREATE" );

  TGraph* gr=new TGraph [D];
  TGraph* grp=new TGraph [D];
  for (int d=0; d<D; d++)
    {
      TString s("Fonction "); TString name("F");
      gr[d].Set(N+1); // mets le nombre de points dans les graphes
      s+=(d+1);name+=(d+1);
      gr[d].SetNameTitle(name,s);
      grp[d].Set(N+1); // mets le nombre de points dans les graphes des derivees
      s+=" derivee"; name+="p";
      grp[d].SetNameTitle(name,s);
      for (int i = 0 ; i < N+1 ; i++) 
	{
	  gr[d].SetPoint(i,xtab[i],ytab[i](d+1));
	  grp[d].SetPoint(i,xtab[i],yptab[i](d+1));
	}
      gr[d].Write();
      grp[d].Write();
    }
  delete [] gr;
  delete [] grp;

  fichier.Close();
}
*/
