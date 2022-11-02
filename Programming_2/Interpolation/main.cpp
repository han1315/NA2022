#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Interpolation.h"
#define PI acos(-1)

using namespace std;

int main()
{
  Interpolation<double> Z;
  
  cout<<"Question B :"<<endl;
  Z.RungePhenomenon();
  cout<<endl;

  cout<<"Question C :"<<endl;
  Z.Chebyshev();
  cout<<endl;

  cout<<"Question D :"<<endl;
  Z.Q_D();
  cout<<endl;

  cout<<"Position of car for t=10s : ";
  Z.ValueHermite(10);
  cout<<"Speed of car for t=10s : ";
  Z.fd(10);
  cout<<endl;

  cout<<"Question E :"<<endl;
  Z.Q_E();
  cout<<endl;
}
