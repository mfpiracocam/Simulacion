#include<iostream>
#include<cmath>
using namespace std;

const double ERR=1e-7;

double f(double x,double t){
  return x;
}

void UnPasoDeEuler(double & x,double & t,double dt){
  double dx; 
  dx=f(x,t)*dt;
  t+=dt;  x+=dx;
} 

int main(void){
  double t,x,dt=0.1;

  for(t=0,x=1;t<2; ){
    cout<<t<<" "<<x<<endl;
    UnPasoDeEuler(x,t,dt);
  }

  return 0;
}
