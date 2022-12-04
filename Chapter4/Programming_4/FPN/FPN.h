#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class FPN
{
public:
  double b=2;
  double p=3;
  double L=-1;
  double U=1;
  double UFL;
  double OFL;
  vector<double> Q,R;
  
  FPN()
  {
    UFL=pow(b,L);
    OFL=pow(b,U)*(b-pow(b,1-p));
  }

  void Q1()
  {
    cout<<"UFL : "<<UFL<<endl;
    cout<<"OFL : "<<OFL<<endl;
    cout<<endl;
  }

  void Q2()
  {
    for (int i=L;i<=U;i++)
    {
      for (int j=pow(2,p-1);j<=pow(2,p)-1;j++)
      {
	double temp=j;
	for (int k=1;k<=abs(p-1-i);k++)
	{
          if (p-1-i>0)
          {
	    temp=temp/2;
          }
	  else
          {
	    temp=temp*2;
          }
	}
        Q.push_back(temp);
	Q.push_back(-temp);
      }
    }
    Q.push_back(0);
    sort(Q.begin(),Q.end());
    cout << "All normal numbers of F : "<<endl<<Q[0];
    for (int i=1;i<size(Q);i++)
    {
      cout<<" , "<<Q[i];
    }
    cout<<endl;
    cout<<endl;
  }

  void Q3()
  {
    for (int i=1;i<=pow(2,p-1)-1;i++)
    {
        double temp=i;
        for (int j=1;j<=p+abs(L);j++)
        {
            temp=temp/2;
        }
        R.push_back(temp);
        R.push_back(-temp);
    }
    sort(R.begin(),R.end());
    cout<<"All subnormal numbers of F : "<<endl<<R[0];
    for (int i=1;i<size(R);i++)
    {
        cout<<" , "<<R[i];
    }
    cout<<endl;
    cout<<endl;
  }
};

