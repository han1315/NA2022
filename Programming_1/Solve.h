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
  Comparable A;
  Comparable B;
  Comparable C;
  Comparable D;
  Comparable sig = 11.5 / 180 * PI;
  Comparable delta = DBL_EPSILON;
  Comparable eps = DBL_EPSILON;

  virtual void Dom(int y)
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
      break;
    
    case 5:
      c = 4.5;
      break;
      
    case 6:
      c = 7.7;
      break;

    case 7:
      c = PI / 2;
      d = 0;
      break;
      
    case 8:
      c = 1.4;
      d = 1;
      break;

    case 9:
      c = -0.5;
      d = 0;
      break;

    case 10:
      a = 0;
      b = 1;
      c = 0;
      d = 1;
      break;

    case 11:
      c = 33 /180 * PI;
      break;

    case 12:
      c = 33 /180 * PI;
      break;

    case 13:
      c = 33 / 180 * PI;
      d = 333 / 180 * PI;
      break;
    }
  }
  
  virtual Comparable f(Comparable x , int y)
  {
    switch (y)
    {
    case 1:
      return (1.0 / x - tan(x));
      break;

    case 2:
      return (1.0 / x - pow(2,x));
      break;
      
    case 3:
      return (1 / pow(2,x) + exp(x) + 2 * cos(x) - 6);
      break;

    case 4:
      return ((pow(x,3) + 4 * pow(x,2) + 3 * x + 5) / (2 * pow(x,3) - 9 * pow(x,2) + 18 * x - 2));
      break;

    case 5:
      return (tan(x));
      break;
      
    case 6:
      return (tan(x));
      break;

    case 7:
      return (sin(x / 2) - 1);
      break;
      
    case 8:
      return (exp(x) - tan(x));
      break;

    case 9:
      return (x * x * x - 12 * x * x + 3 * x + 1);
      break;

    case 10:
      return (10 * (0.5 * PI * 1 * 1 - 1 * 1 * asin(x / 1) - x * sqrt(1 * 1 - x * x)) -12.4);
      break;

    case 11:
      A = 89 * sin(sig);
      B = 89 * cos(sig);
      C = (49 + 0.5 * 55) * sin(sig) - 0.5 * 55 * tan(sig);
      D = (49 + 0.5 * 55) * cos(sig) - 0.5 * 55;
      return (A * sin(x) * cos (x) + B * sin(x) * sin(x) - C * cos(x) - D * sin(x));
      break;

    case 12:
      return (89 * sin(sig) * sin(x) * cos(x) + 89 * cos(sig) * sin(x) * sin(x) - (((49 + 0.5 * 30) * sin(sig) - 0.5 * 30 * tan(sig)) * cos(x)) - ((49 + 0.5 * 30) * cos(sig) - 0.5 * 30) * sin(x));
      break;

    case 13:
      A = 89 * sin(sig);
      B = 89 * cos(sig);
      C = (49 + 0.5 * 30) * sin(sig) - 0.5 * 30 * tan(sig);
      D = (49 + 0.5 * 30) * cos(sig) - 0.5 * 30;
      return (A * sin(x) * cos (x) + B * sin(x) * sin(x) - C * cos(x) - D * sin(x));
      break;
    }
  }

  virtual Comparable fd(Comparable x , int y)
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

    case 7:
      break;
      
    case 8:
      break;

    case 9:
      break;

    case 10:
      return (-10 / (sqrt(1 - x * x)) - 10 * (-2 * x * x +1) / sqrt(1 - x * x));
      break;

    case 11:
      A = 89 * sin(sig);
      B = 89 * cos(sig);
      C = (49 + 0.5 * 55) * sin(sig) - 0.5 * 55 * tan(sig);
      D = (49 + 0.5 * 55) * cos(sig) - 0.5 * 55;
      return (A * (cos(x) * cos (x) - sin(x) * sin(x)) + 2 * B * sin(x) * cos(x) + C * sin(x) - D * cos(x));
      break;

    case 12:
      return (89 * sin(sig) * (cos(x) * cos(x) - sin(x) * sin(x)) + 89 * cos(sig) * sin(x) * cos(x) * 2 + (((49 + 0.5 * 30) * sin(sig) - 0.5 * 30 * tan(sig)) * sin(x)) - ((49 + 0.5 * 30) * cos(sig) - 0.5 * 30) * cos(x));
      break;

    case 13:
      break;
    }
  }

  virtual int sgn(Comparable x)
  {
    return ((x > 0) - (x < 0));
  } 

  virtual Comparable root()
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

