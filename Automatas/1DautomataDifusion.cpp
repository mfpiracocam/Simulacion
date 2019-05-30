#include <iostream>
#include <cmath>
#include "Random64.h"
using namespace std;

const int Lx=200;
const double p=0.5;

class LatticeGas{
private:
  int V[2];              //Velocidades i=0 der, i=1 izq
  int n[Lx][2], nnew[Lx][2];           //n[ix][i]
public:
  LatticeGas(void);      //Constructor
  void Inicie(Crandom & ran64);
  void Show(int copia);
  void Colisione(Crandom & ran64);
  void Adveccione(void);
  int DondeEstaLaBolita(void);
};

LatticeGas::LatticeGas(void){
  V[0]=1; V[1]=-1;
}
void LatticeGas::Inicie(Crandom & ran64){

//inicia vectores en cero
  for(int ix=0; ix<Lx;ix++)
    for(int i=0; i<2; i++)
      {n[ix][i]=0; nnew[ix][i]=0;}
      
  if(ran64.r()<0.5){n[Lx/2][0]=1;}
  else{n[Lx/2][1]=1;}
}

void LatticeGas::Show(int copia){
  for(int i=0; i<2;i++){
    for(int ix=0; ix<Lx; ix++){
      if(copia==0){cout<<n[ix][i];}
      else{cout<<nnew[ix][i];}
    }
    cout<< endl;}
  cout<<endl;

}
void LatticeGas::Colisione(Crandom & ran64){     //n -> nnew
  for(int ix=0; ix<Lx;ix++){
    if(ran64.r()<p){
      for(int i=0; i<2;i++){nnew[ix][i]=n[ix][i];}
    }   //dejelo quieto
    else{
      for(int i=0; i<2;i++){nnew[ix][i]=n[ix][(i+1)%2];}
    }
  }
}
void LatticeGas::Adveccione(void){             // nnew -> n
  for(int ix=0;ix<Lx;ix++){
    for(int i=0;i<2;i++){
      n[(ix+V[i]+Lx)%Lx][i]=nnew[ix][i];
    }
  }
}

int LatticeGas::DondeEstaLaBolita(void){
  int ix=0;
  while(n[ix][0]+n[ix][1]==0){ix++;}
  return ix;
}

//----------------Funciones globales-----------------
const int N=1000;

double Sigma2(LatticeGas * Difusion){
  double Xprom=0, sigma2=0;
  for(int c=0;c<N;c++){Xprom+=Difusion[c].DondeEstaLaBolita();}//xpromedio
  Xprom/=N;
  for(int c=0;c<N;c++){sigma2+=pow(Difusion[c].DondeEstaLaBolita()-Xprom,2);}//xpromedio
  sigma2/=N-1;

  return sigma2;
}


int main(void){
  LatticeGas Difusion[N];
  Crandom ran64(1012);
  int t,tmax=400;
  for(int c=0;c<N;c++)
    Difusion[c].Inicie(ran64);
  for(int t=0;t<tmax;t++){
    cout<<t<<" "<<Sigma2(Difusion)<<endl;
    for(int c=0;c<N;c++){Difusion[c].Colisione(ran64);
      Difusion[c].Adveccione();}
  }


}
