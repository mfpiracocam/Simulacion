#include <iostream>
#include <cmath>
#include "Random64.h"

using namespace std;

const int Lx=256;
const double p=0.5;

class LatticeGas
{
private:
  int V[2][1];
  int n[Lx][2], nnew[Lx][2]; // 0 se mueve a la derecha y 1 a la izquierda
public:
  void Inicie(int B, double mu, double sigma, Crandom & ran64);
  void Show(bool ImprimirNew);
  void Colisione(Crandom & ran64);
  void Adveccione(void);
  double GetSigma2(void);
};
void LatticeGas::Inicie(int B,double mu, double sigma, Crandom & ran64)
{
  //iniciar los vectores
  V[0][0]=1; V[1][0]=-1;
  //Iniciar los contenidos
  int i,k;
  for(i=0;i<Lx;i++) //Los borro todos
    n[i][0]=n[i][1]=nnew[i][0]=nnew[i][1]=0;

  while(B>0)//Colocar b bolitas
    {
      i=(int) ran64.gauss(mu,sigma);
      if(i<0) i=0;
      if(i>Lx-1) i=Lx-1;
      k=(int)2*ran64.r();
      if(n[i][k]==0)
	     n[i][k]=1;
       B--;
     }
}

void LatticeGas::Adveccione(void)
{
  for(int i=0; i<Lx;i++)//para cada celda
    for(int k=0;k<2;k++)//en cada direccion
      n[(i+Lx+V[k][0])%Lx][k]=nnew[i][k];
}

void LatticeGas:: Colisione(Crandom & ran64)
{
  for(int i=0; i<Lx; i++)//ir celda por celda
    if(ran64.r()<p)
    {
      nnew[i][0]=n[i][0]; nnew[i][1]=n[i][1];
    }
    else
      {
        nnew[i][0]=n[i][1]; nnew[i][1]=n[i][0];
      }

}

void LatticeGas::Show(bool ImprimirNew)
{
  for (int k=0;k<2;k++)
    {
      for(int i=0;i<Lx;i++)
      {
        if(ImprimirNew) cout<<nnew[i][k];
        else cout<<n[i][k];
      }
      cout<<endl;
    }
}

double LatticeGas::GetSigma2(void)
{
  double N, xprom, sigma2; int i,k;

  //Calculo N
  for(N=0, i =0; i<Lx; i++)
  {
    for(k=0; k<2; k++)   N+=n[i][k];
  }
  //Calculo xprom
  for(xprom=0, i=0; i<Lx; i++)
  {
    for(k=0;k<2; k++);
    xprom+=i*n[i][k];
  }
  xprom/=N;

  //Calculo sigma2
  for(sigma2=0, i=0;i<Lx;i++)
  {
    for(k=0; k<2; k++) sigma2+=i*i*n[i][k];
  }
//sigma2=(sigma2-N);
  sigma2=(sigma2-N*xprom*xprom)/(N-1);

  return sigma2;
}

int main(void)

{
  LatticeGas Difusion;
  Crandom ran64(1);
  //bool ImprimirNew=true;
  int B=64; double mu=Lx/2.0, sigma=32;//Lx/8.0;
  int t, tmax=700;

  Difusion.Inicie(B,mu,sigma,ran64);
  //Difusion.Show(false);
//cout<<endl;
  for(t=0;t<tmax;t++)
    {
      cout<<t<<" "<<Difusion.GetSigma2()<<endl;
      Difusion.Colisione(ran64);
      Difusion.Adveccione();
    }
cout<<endl;
  //Difusion.Show(true);

  return 0;
}
