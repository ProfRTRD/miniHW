#include<iostream>
#include<cmath>
#include <vector>
#include <fstream>

//functor F
struct functor_f 
{
  double rho=1.23,miu=1.79e-5;
  int V=45;
  double operator()(double D) 
  {
    return (rho*V*D)/miu;
  }
};
//functor G
struct functor_g
{
  double e=0.0014e-3, D, RE;
  double operator()(double f)
  {
    return 2.0*log((e/3.7*D)+(2.51/RE*sqrt(f)))+(1.0/sqrt(f));
  }
};
//functor H
struct functor_h
{
  double L=0.2,rho=1.23,D;
  int V=45;
  double operator()(double f)
  {
    return f*(L*rho*V*V/2*D);
  }
};

template <typename func_t>
double newton(double x0, double eps, func_t func, int nmax, int & nsteps);

int main (int argc, char *argv[])
{
  double eps = std::atof(argv[1]);
  int NMAX = 1000;
  int steps = 0;
  std::ofstream fout;
  fout.open("functors.txt");
  fout.setf(std::ios::scientific); 
  fout.precision(15);

  //D
  double Dn=0;
  int n= 30;
  for(int ii=1; ii<n; ++ii)
  {
   Dn=ii*0.001;
    functor_f F;
    double RE= F(Dn);

    functor_g G;
    double x0=0.316/std::pow(RE, 0.25);
    double root = newton(x0, eps, G, NMAX, steps);
  
    functor_h H;
    H.D = Dn;
    double dp= H(root);

    fout << "\t" << Dn << "\t" << dp << "\n";
    }
  fout.close();
}


template<typename func_t>
double newton(double x0, double eps, func_t func, int nmax, int & nsteps)
{
  nsteps = 0;
  double xr = x0;
  while(nsteps <= nmax) 
  {
    if (std::fabs(func(xr)) < eps) 
    {
      break;
    } else 
    {
      double h = 0.001;
      double deriv = (func(xr+h/2) - func(xr-h/2))/h;
      xr = xr - func(xr)/deriv;
    }
    nsteps++;
  }

  return xr;
}

