#include "Vettore.h"
#include "OdeSolverRel.h"

void OdeSolver::SetPoint(int i,PuntoMateriale tmp){
  m_p[i] = tmp;
}

vector<PuntoMateriale> OdeSolver::GetPoint(){
  return m_p;
}

void OdeSolver::T(double t0){
  m_t=t0;
}

double OdeSolver::T(){
  return      m_t;
}

void OdeSolver::Step(double h){
  m_h = h;
}

double OdeSolver::Step(){
  return   m_h;
}


Vettore OdeSolver::m_eqDiff(int i, double t, vector<PuntoMateriale> p){
  //Calcolo dell'accelerazione totale
  Vettore ftot;
  for (int j=0;j<m_p.size();j++){
    if (i!=j) ftot = ftot + fInterna(i,j,t,p);
  }
  //Calcolo dell'accelerazione esterna
  ftot = ftot + fEsterna(i,t,p);
  return ftot*(1/m_p[i].Massa());
}

//Da implementare a cura dello studente
void OdeSolver::Cinematica(){

  if (m_method=="Eulero"){

    vector<Vettore>  k1(m_p.size());
    vector<Vettore>  w1(m_p.size());
    for (int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i,m_t,m_p);
    }

    for (int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].V(m_p[i].V() + w1[i]);
    }

  } else if (m_method=="Rk2"){
    vector<Vettore>        k1(m_p.size());
    vector<Vettore>        w1(m_p.size());
    vector<Vettore>        k2(m_p.size());
    vector<Vettore>        w2(m_p.size());
    auto xt(m_p);

    for (int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i,m_t,m_p);
    }

    for (int i=0;i<m_p.size();i++){
      xt[i].R(m_p[i].R() + k1[i]*0.5);
      xt[i].V(m_p[i].V() + w1[i]*0.5);
    }
 
    for (int i=0;i<m_p.size();i++){
      k2[i] = m_h*xt[i].V();
      w2[i] = m_h*m_eqDiff(i,m_t,xt);
    }

    for (int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k2[i]);
      m_p[i].V(m_p[i].V() + w2[i]);
    }

  } else if (m_method=="Rk4"){

  } else if (m_method=="VerletV"){
    auto xt(m_p);
    auto tmp(m_p);
    for (int i=0;i<m_p.size();i++){
      Vettore vn  = m_p[i].V();
      Vettore an  = m_eqDiff(i,m_t,m_p);
      tmp[i].R(m_p[i].R()+m_h*vn+m_h*m_h/2*an);
      xt[i].R(m_h*vn+m_h*m_h/2*an);
    }
    for (int i=0;i<m_p.size();i++){
      Vettore an  = m_eqDiff(i,m_t,m_p);
      Vettore an1 = m_eqDiff(i,m_t,tmp);
      xt[i].V(m_h/2*(an+an1));
    }
    for (int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + xt[i].R());  
      m_p[i].V(m_p[i].V() + xt[i].V());  
    }
    
  }
  m_t += m_h;

}

