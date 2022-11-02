#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#define PI acos(-1)

using namespace std;

template <typename Comparable>
class Interpolation
{
public:
  vector<vector<double>> f;
  vector<double> ans;
  
  Comparable fc_x(int x)
  {
    return (1.0/(1.0+25.0*x*x));
  }
  
  void NewtonMethod(vector<double> a,vector<double> b)
  {
    int n=size(a);
    vector<Comparable> xn;
    vector<Comparable> fn;
    vector<Comparable> A;
    for(int i=0;i<n;i++)
    {
      xn.push_back(a[i]);
      fn.push_back(b[i]);
    }

    A.push_back(fn[0]);
    int m=0;
    int temp=n;
    while(temp!=0)
    {     
      m=m+temp;
      temp=temp-1;
    }

    int l=0;
    temp=2;
    if(n==1)
    {
      A.push_back(fn[0]);
    }
    else 
    {
      while(temp!=n)
      {
	l=l+1;
	temp=temp+1;
      }

      int h=0;
      int k=n-1;
      int count=0;
      for(int i=n;i<m;i++)
      {
	double tempf;
	if(count!=k)
	{
	  tempf=(fn[i-l-1]-fn[i-l-2])/(xn[count+h+1]-xn[count]);
	  fn.push_back(tempf);
	  if(count==0)
	  {
	    A.push_back(tempf);
	  }
	  count=count+1;
	}
	else
	{
	  count=0;
	  k=k-1;
	  l=l-1;
	  h=h+1;
	  tempf=(fn[i-l-1]-fn[i-l-2])/(xn[count+h+1]-xn[count]);
	  fn.push_back(tempf);
	  if(count==0)
	  {
	    A.push_back(tempf);
	  }
	  count=count+1;
	}   	    
      }
    
      int n_p=size(A);
      Comparable p;
      cout<<A[0];
      for(int i=1;i<n_p;i++)  
      {
        cout<<showpos<<A[i];
	for(int j=0;j<i;j++)
	{
	  cout<<"(x"<<showpos<<-xn[j]<<")";
	}
      }
      cout<<endl;
    }
  }

  void RungePhenomenon()
  {
    int count=0;
    for(int i=2;i<=8;i=i+2)
    {
      vector<double> xb;
      vector<double> fb;
      for(int j=0;j<=i;j++)
      {
	xb.push_back(-5.0+10.0*j/i);
	fb.push_back(1.0/(1.0+xb[j]*xb[j]));
      }
      cout<<noshowpos<<"p"<<i<<"(f;x)=";
      NewtonMethod(xb,fb);
      cout<<endl;
    }
  }

  void Chebyshev()
  {
    for(int i=5;i<=20;i=i+5)
    {
      vector<double> xc;
      vector<double> fc;
      for(int j=1;j<=i;j++)
      {
	xc.push_back(cos((2.0*j-1.0)/(2.0*i)*PI));
	fc.push_back(1.0/(1.0+25.0*xc[j-1]*xc[j-1]));
      }
      cout<<noshowpos<<"p"<<i<<"(f;x)=";
      NewtonMethod(xc,fc);
      cout<<endl;
    }
  }

  void Hermite(vector<double> x, vector<double> y, vector<double> z)
  {
    f.resize(x.size()+1);
    for(int i=0;i<=x.size();i++)
    {
      f[i].resize(x.size()+1);
    }
    
    for(int i=0;i<x.size();i++)
    {
      f[i][0]=y[i];
    }

    for(int i=0;i<x.size();i++)
    {
      ans.push_back(x[i]);
    }
    
    for (int i=1;i<x.size();i=i+2)
    {
      f[i][1]=z[i];
    }
    
    for (int i=2;i<x.size();i=i+2)
    {
      f[i][1]=(f[i][0]-f[i-1][0])/(x[i]-x[i-2]);
    }
    
    for (int i=2;i<x.size();i++)
    {
      for (int j=i;j<x.size();j++)
      {
	f[j][i]=(f[j][i-1]-f[j-1][i-1])/(x[j]-x[j-i]);
      }
    }

    cout<<noshowpos<<f[0][0];
    for (int i=1;i<f.size();i++)
    {
      cout<<showpos<<f[i][i];
      for (int j=0;j<i;j++)
      {
	cout<<"(x"<<showpos<<-x[j]<<")";
      }    
    }
    cout<<endl;    
  }

  void ValueHermite(Comparable k)
  {
    Comparable p=f[0][0];
    for (int i=1;i<f.size();i++)
    {
      Comparable temp=f[i][i];
      for (int j=0;j<i;j++)
      {
	temp=temp*(k-ans[j]);
      }
      p=p+temp;
    }
    cout<<noshowpos<<p<<endl;
  }

  void fd(Comparable k)
  {
    Comparable temp;
    temp=75+14.3238*k-30.2859*pow(k,2)+22.0325*pow(k,3)-7.69148*pow(k,4)+1.45825*pow(k,5)-0.15313*pow(k,6)+0.00832472*pow(k,7)-0.000182013*pow(k,8);
    cout<<temp<<endl;
  }
  
  void Q_D()
  {
    vector<double> x={0,0,3,3,5,5,8,8,13,13};
    vector<double> y={0,0,225,225,383,383,623,623,993,993};
    vector<double> z={75,75,77,77,80,80,74,74,72,72};
    cout << "f(x)=";
    Hermite(x,y,z);
  }

  void Q_E()
  {
    vector<double> xe={0,6,10,13,17,20,28};
    vector<double> fe1={6.67,17.3,42.7,37.3,30.1,29.3,28.7};
    vector<double> fe2={6.67,16.1,18.9,15.0,10.6,9.44,8.89};
    cout<<noshowpos<<"sp1(f;x)=";
    NewtonMethod(xe,fe1);
    cout<<endl;
    cout<<noshowpos<<"sp2(f;x)=";
    NewtonMethod(xe,fe2);
    cout<<endl;    
  }
};
