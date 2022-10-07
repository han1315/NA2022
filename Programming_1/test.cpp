#include <iostream>
#include <cfloat>
#include <cmath>

#define PI acos(-1)
using namespace std;

template <typename Comparable>
class EquationSolver
{
public:
  Comparable a;
  Comparable b;
  Comparable c;
  Comparable d;
  Comparable h;
  Comparable u;
  Comparable v;
  Comparable w;
  Comparable M = 100;
  Comparable k; 
  Comparable delta = DBL_EPSILON;
  Comparable eps = DBL_EPSILON;

  void Dom(int y)
  {
    switch (y)
    {
    case 1:
      a = 0;
      b = PI /2;
      break;

    case 2:
      a = 0;
      b = 1;
      break;
      
    case 3:
      a = 1;
      b = 3;
      break;

    case 4:
      a = 0;
      b = 4;
    
    case 5:
      c = 4.5;

    case 6:
      c = 7.7;
    }
  }
  
  Comparable f(Comparable x , int y)
  {
    switch (y)
    {
    case 1:
      return(1.0 / x - tan(x));
      break;

    case 2:
      return(1.0 / x - pow(2,x));
      break;
      
    case 3:
      return(1 / pow(2,x) + exp(x) + 2 * cos(x) - 6);
      break;

    case 4:
      return((pow(x,3) + 4 * pow(x,2) + 3 * x + 5) / (2 * pow(x,3) - 9 * pow(x,2) + 18 * x - 2));
      break;

    case 5:
      return (tan(x));
      break;
      
    case 6:
      return (tan(x));
      break;
    }
  }

  Comparable fd(Comparable x , int y)
  {
    switch (y)
    {
    case 1:
      return(-1.0 / (x * x) - pow(1.0 / cos(x) , 2));
      break;

    case 2:
      return(-1.0 / (x * x) - pow(2,x) * log (2));
      break;

    case 3:
      break;

    case 4:
      break;

    case 5:
      return(pow(1.0 / cos(x) , 2));
      break;
      
    case 6:
      return(pow(1.0 / cos(x) , 2));
      break;
    }
  }

  int sgn(Comparable x)
  {
    return((x > 0) - (x < 0));
  } 

  Comparable root()
  {
    return c;
  }
};

template <typename Comparable>
class BisectionMethod : public EquationSolver<double>
{
public:
  void B_Method(int x)
  {
    Dom(x);
    if(sgn(f(a , x)) != sgn(f(b , x)))
    { 
      h = b - a;
      u = f(a , x);
      for(int i=1 ; i<M ; i++)
      {
	h = h / 2;
	c = a + h;
	w = f(c , x);
	k = i;
	if((abs(h) < delta) || (abs(w) < eps))
	{
	  break;
	}
	else if(sgn(w) == sgn(u))
	{
	  a = c;
	}	
      }
    }
  }  
};


template <typename Comparable>
class NewtonMethod : public EquationSolver<double>
{
public:
  void N_Method(int x)
  {
    Dom(x);
    for(int i=0 ; i<M ;i++)
    {        
      u = f(c , x);
      k = i;
      if(abs(u) < eps)
      {
	break;
      }
      c = c - u / fd(c , x);
    }
  }
};

template <typename Comparable>
class SecantMethod : public EquationSolver<double>
{
public:
  void S_Method(int x)
  {
    Dom(x);
    c = (a + b) / 3;
    d = (a + b) / 3 * 2; 
    u = f(c , x);
    v = f(d , x);
    for(int i=1 ; i<M ; i++)
    {
      if(abs(u) > abs(v))
      {
	double _a = u;
	u = v;
	v = _a;
	_a = c;
	c = d;
	d = _a;
      }
      w = (c - d) / (u - v);
      d = c;
      v = u;
      c = c - u * w;
      u = f(c , x);
      k = i;
      if((abs(c - d) < delta) || (abs(u) < eps))
      {
	break;
      }
    }
  } 
};

int main()
{
  BisectionMethod<double> A;
  NewtonMethod<double> B;
  SecantMethod<double> C;
  A.B_Method(1);
  cout<<A.root()<<endl;
  A.B_Method(2);
  cout<<A.root()<<endl;
  A.B_Method(3);
  cout<<A.root()<<endl;
  A.B_Method(4);
  cout<<A.root()<<endl;
  B.N_Method(5);
  cout<<B.root()<<endl;;
  B.N_Method(6);
  cout<<B.root()<<endl;
}
