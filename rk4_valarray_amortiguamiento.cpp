#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <valarray>
#include <cstdlib>

typedef std::valarray<double> state_t; // alias for state type

void initial_conditions(state_t & y);
void print(const state_t & y, double time);
//void fderiv(const state_t & y, state_t & dydt, double t);
template <class deriv_t, class system_t, class printer_t>
void integrate_euler(deriv_t deriv, system_t & y, double tinit, double tend, double dt, printer_t writer);
template <class deriv_t, class system_t, class printer_t>
void integrate_rk4(deriv_t deriv, system_t & y, double tinit, double tend, double dt, printer_t writer);


int main(int argc, char **argv)
{
  if (argc != 6) {
    std::cerr << "ERROR. Usage:\n" << argv[0] << " T0 TF DT W" << std::endl;
    std::exit(1);
  }
  const double T0 = std::atof(argv[1]);
  const double TF = std::atof(argv[2]);
  const double DT = std::atof(argv[3]);
  const double W  = std::atof(argv[4]);
  const double B  = std::atof(argv[5]);
  const int N = 2;

  auto fderiv = [W,B](const state_t & y, state_t & dydt, double t){
    dydt[0] = y[1];
    dydt[1] = -B*y[1]+ -W*W*y[0];
  };

  state_t y(N);
  initial_conditions(y);
  //integrate_euler(fderiv, y, 0.0, TF, DT, print);
  integrate_rk4(fderiv, y, 0.0, TF, DT, print);

  return 0;
}

void initial_conditions(state_t & y)
{
  y[0] = 0.9876;
  y[1] = 0.0;
}

void print(const state_t & y, double time)
{
  std::cout << time << "\t" << y[0] << "\t" << y[1] << std::endl;
}

// void fderiv(const state_t & y, state_t & dydt, double t)
// {
//   dydt[0] = y[1];
//   dydt[1] = -W*W*y[0];
// }

template <class deriv_t, class system_t, class printer_t>
void integrate_euler(deriv_t deriv, system_t & y, double tinit, double tend, double dt, printer_t writer)
{
  int N = y.size();
  system_t dydt(N);
  double time = 0;
  int nsteps = (tend - tinit)/dt;
  for(int ii = 0; ii < nsteps; ++ii) {
    time = 0.0 + ii*dt;
    deriv(y, dydt, time);
    y += dydt*dt;
    print(y, time);
  }
}

template <class deriv_t, class system_t, class printer_t>
void integrate_rk4(deriv_t deriv, system_t & y, double tinit, double tend, double dt, printer_t writer)
{
  int N = y.size();
  system_t dydt(N);
  system_t k1(N), k2(N), k3(N), k4(N), aux(N);

  double time = 0;
  int nsteps = (tend - tinit)/dt;
  for(int ii = 0; ii < nsteps; ++ii) {
    time = 0.0 + ii*dt;
    // k1
    deriv(y, dydt, time);
    k1 = dydt*dt;
    // k2 aux
    aux = y + k1/2;
    //k2
    deriv(aux, dydt, time + dt/2);
    k2 = dydt*dt;
    // k3 aux
    aux = y + k2/2;
    //k3
    deriv(aux, dydt, time + dt/2);
    k3 = dydt*dt;
    // k4 aux
    aux = y + k3;
    //k4
    deriv(aux, dydt, time + dt);
    k4 = dydt*dt;
    // write new data
    y += (k1 + 2*k2 + 2*k3 + k4)/6.0;
    // call writer
    print(y, time);
  }
}
