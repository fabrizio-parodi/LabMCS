#ifndef _ODESOLVER
#define _ODESOLVER

#include <vector>
#include "Vettore.h"
#include "PuntoMateriale.h"

using namespace std;

class OdeSolver{
 public:
  OdeSolver(string method="Eulero", vector<PuntoMateriale> p=vector<PuntoMateriale>(0)):m_method(method),m_p(p),m_t(0),m_h(0.1){}
  void                   SetPoint(int i,PuntoMateriale tmp);
  vector<PuntoMateriale> GetPoint();
  void           T(double t0);
  double         T();
  void           Step(double h);
  double         Step();
  void           Cinematica();
  std::function < Vettore(int i,int j, double t, vector<PuntoMateriale> p) > fInterna;
  std::function < Vettore(int i,double t, vector<PuntoMateriale> p) >        fEsterna;
 private:
  string   m_method;
  vector<PuntoMateriale> m_p;
  double   m_t,m_h; 
  Vettore  m_eqDiff(int i, double t, vector<PuntoMateriale>);
};


#endif
