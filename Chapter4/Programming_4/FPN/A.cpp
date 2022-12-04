#include <iostream>
#include <cmath>

using namespace std;

double f(double x)
{
  return (pow(x,8)-8*pow(x,7)+28*pow(x,6)-56*pow(x,5)+70*pow(x,4)-56*pow(x,3)+28*pow(x,2)-8*x+1);
}

double g(double x)
{
  return ((((((((x-8)*x+28)*x-56)*x+70)*x-56)*x+28)*x-8)*x+1);
}

double h(double x)
{
  return (pow(x-1,8));
}

int main()
{
  cout<<"f(x) :"<<endl;
  for(double i=0.99;i<=1.01;i=i+0.0002)
  {
    cout<<i<<" "<<f(i)<<endl;
  }

  cout<<endl;
  cout<<"g(x) :"<<endl;
  for(double i=0.99;i<=1.01;i=i+0.0002)
  {
    cout<<i<<" "<<g(i)<<endl;
  }

  cout<<endl;
  cout<<"h(x) :"<<endl;
  for(double i=0.99;i<=1.01;i=i+0.0002)
  {
    cout<<i<<" "<<h(i)<<endl;
  }
}
