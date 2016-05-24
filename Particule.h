#ifndef _PARTICULE_H_
#define _PARTICULE_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Vecteur.h"


class ChampEMG{
  protected:
  Vecteur B;
  Vecteur E;
  double const c=299792458;
  public:
  ChampEMG(double Bx,double By, double Bz, double Ex,double Ey,double Ez);
  void set_B(double Bx,double By,double Bz);   // méthode pour donner les valeurs de B 
  void set_E(double Ex,double Ey,double Ez);    // et de E
  
};


class ParticuleChargee : public ChampEMG{
 private:
  double q;            // Charge de la particule
  double m;           // masse de la particule
  Vecteur Imp_0;    // Impulsion initiale
double EE;
double *xtab, *ytab, *ztab,*Pxtab, *Pytab, *Pztab;
double gamma;
	
public:
  ParticuleChargee(double Bx,double By,double Bz,double Ex,double Ey,double Ez,double Vx0,double Vy0,double Vz0); //Donne une vitesse initiale
  ~ParticuleChargee();
  void set_m(double masse);
  void set_q(double charge);
 Vecteur f(double t, Vecteur y );
  Vecteur rk4(int N, double t0, double tf);
double * getx() {return xtab;}
double* gety() {return ytab;}
double* getz() {return ztab;}
double * getPx() {return Pxtab;}
double* getPy() {return Pytab;}
double* getPz() {return Pztab;}
//void tracerizi(const char * nom_fichier, int N);
};

#endif

