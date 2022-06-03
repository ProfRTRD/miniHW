//BARETO TORRES ZAIR VALENTIN Y GONZALEZ FLOREZ JUAN JOSE
#include <eigen3/Eigen/Dense>
#include <iostream>

int main(int argc, char **argv) {
  int N = std::atoi(argv[1]);
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(N, N); // matriz aleatoria de NXN
  Eigen::VectorXd b = Eigen::VectorXd::Random(N);
  //std::cout << "Here is the matrix A:\n" << A << std::endl;
  //std::cout << "Here is the vector b:\n" << b << std::endl;
  Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
          // resuelve el sistema, con la funcion house holder, resuelve
          // empleando el vector especificado (b en este caso)
  //std::cout << "The solution is:\n" << x << std::endl;
  std::cout << "Verification:\n" << (A * x - b).norm() << std::endl;
}
