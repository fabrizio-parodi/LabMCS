#ifndef _CAMPOVETTORIALE
#define _CAMPOVETTORIALE

#include <TVector3.h>

class CampoVettoriale: public TVector3{
 public:
  CampoVettoriale(TVector3 R=TVector3(0,0,0),TVector3 Val=TVector3(0,0,0)):TVector3(Val),m_R(R){;}
  TVector3 R(){return m_R;}
  void R(TVector3 r){m_R = r;}
 protected:
  TVector3 m_R;
};

#endif
