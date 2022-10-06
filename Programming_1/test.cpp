#include <iostream>
#include <cfloat>
#include <cmath>

#define PI acos(-1)
using namespace std;

template <typename Comparable>
class EquationSolver
{
public:
  Comparable a = 0;
  Comparable b = PI / 2;
  //Comparable b = 1;
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
  
  Comparable f(Comparable x)
  {
    return(1.0 / x - tan(x));
    //return(1.0 / x - pow(2,x));
  }

  Comparable fd(Comparable x)
  {
    return(-1.0 / (x * x) - pow(1.0 / cos(x) , 2));
    //return(-1.0 / (x * x) - pow(2,x) * log (2));    
  }

  int sgn(Comparable x)
  {
    return(( x > 0) - ( x < 0 ));
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
  void B_Method()
  {
    if(sgn(f(a)) != sgn(f(b)))
    { 
      h = b - a;
      u = f(a);
      for(int i=1 ; i<M ; i++)
      {
	h = h / 2;
	c = a + h;
	w = f(c);
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
  void N_Method()
  {
    c =  (a + b) / 2;
    for(int i=0 ; i<M ;i++)
    {        
      u = f(c);
      k = i;
      if(abs(u) < eps)
      {
	break;
      }
      c = c - u / fd(c);
    }
  }
};

template <typename Comparable>
class SecantMethod : public EquationSolver<double>
{
public:
  void S_Method()
  {
    c = (a + b) / 3;
    d = (a + b) / 3 * 2; 
    u = f(c);
    v = f(d);
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
      u = f(c);
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
  A.B_Method();
  cout<<A.root()<<endl;
  B.N_Method();
  cout<<B.root()<<endl;
  C.S_Method();
  cout<<C.root()<<endl;
}
