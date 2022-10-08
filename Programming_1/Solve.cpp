#include <iostream>
#include <cfloat>
#include <cmath>
#include "Solve.h"

#define PI acos(-1)
using namespace std;

int main()
{
  BisectionMethod<double> A;
  NewtonMethod<double> B,D,E;
  SecantMethod<double> C;
  
  cout<<"Question B"<<endl;
  A.B_Method(1);
  cout<<"1 : "<<A.root()<<endl;
  A.B_Method(2);
  cout<<"2 : "<<A.root()<<endl;
  A.B_Method(3);
  cout<<"3 : "<<A.root()<<endl;
  A.B_Method(4);
  cout<<"4 : "<<A.root()<<endl;
  cout<<endl;
  
  cout<<"Question C"<<endl;
  B.N_Method(5);
  cout<<"roots near 4.5 : "<<B.root()<<endl;
  B.N_Method(6);
  cout<<"roots near 7.7 : "<<B.root()<<endl;
  cout<<endl;

  cout<<"Question D"<<endl;
  C.S_Method(7);
  cout<<"1 : "<<C.root()<<endl;
  C.S_Method(8);
  cout<<"2 : "<<C.root()<<endl;
  C.S_Method(9);
  cout<<"3 : "<<C.root()<<endl;
  cout<<endl;

  cout<<"Question E"<<endl;
  A.B_Method(10);
  cout<<"Bisection Method : "<<A.root()<<endl;
  B.N_Method(10);
  cout<<"Newton Method : "<<B.root()<<endl;
  C.S_Method(10);
  cout<<"Secant Method : "<<C.root()<<endl;
  cout<<endl;

  double y,z;
  cout<<"Question F"<<endl;
  D.N_Method(11);
  z = D.root();
  y = z * 180 / PI;
  cout<<"a : "<<y<<endl;
  E.N_Method(12);
  z = E.root();
  y = z * 180 / PI;
  cout<<"b : "<<y<<endl;
  C.S_Method(13);
  z = C.root();
  y = z * 180 / PI;
  cout<<"c : "<<y<<endl;
  cout<<endl;
}
