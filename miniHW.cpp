//SANTIAGO ACERO Y JUAN JOSE GONZALEZ FLOREZ
#include <eigen3/Eigen/Dense>
#include <iostream>

int main(void){
  const int N = 6;
  Eigen::MatrixXd A(6,6);
  A << 1, 1, 1, 0, 0, 0,
    0, -1, 0, 1, -1, 0,
    0, 0, -1, 0, 0, 1,
    0,0,0,0,1,-1,
    0,10,-10,0,-15,-5,
    5,-10,0,-20,0,0;
  Eigen::VectorXd B(6,1);
  B << 0, 0, 0, 0, 0, 200;

  Eigen::MatrixXd Solucion(6,1);
  Solucion = A.colPivHouseholderQr().solve(B);

  std::cout << Solucion << std::endl;
  
    
  


}
