         

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <eigen3/Eigen/Dense>
using namespace Eigen ;
using namespace std ;
    int main()
    {    
          float t; // the time steps
          int i=0;

          std::cout << "enter the time steps" << std::endl;
          std:: cin  >> t;
                MatrixXd X_est(4,1);
                MatrixXd x_pred (4,1);
                MatrixXd F_lin(4,4);    // A = F* AT-1
                MatrixXd H_dep(2,4);     // the linear dependency of measurements
                MatrixXd P_cov(4,4);
                MatrixXd P_cov_pred(4,4);
                MatrixXd K(4,4);
                MatrixXd Z_mes(6,2);    // the measurement function
                MatrixXd Z_data (2,1);
                MatrixXd r_data (2,2);

          X_est<< 0,0,0,0;

          F_lin << 1,0,t,0,
          0,1,0,t,
          0,0,1,0,
          0,0,0,1;

          H_dep<< 1,0,0,0,
          0,1,0,0;


          P_cov<<1000,0,0,0,
          0,1000,0,0,
          0,0,1000,0,
          0,0,0,1000;

          Z_mes << 5,0,
          6,0,
          7.2,0.22,
          8.45,0.31,
          9.1,0,
          11.0,0;
          r_data << 2,0
                   ,0,2;



          for(i=0;i<6;++i)
          {
                  Z_data << Z_mes(i,0),Z_mes(i,1);  
                  x_pred = F_lin * X_est;      
                  P_cov_pred = F_lin * P_cov * F_lin.transpose(); 



                  K = P_cov_pred * H_dep.transpose() * ( H_dep*P_cov_pred*H_dep.transpose() +r_data).inverse();
                  X_est = x_pred + K*(Z_data - H_dep* x_pred);
                  // P_cov_estimate = P_cov - K * H_dep * P_cov;
                  //X = F_lin * x_estimate ;
                  // P_cov = F_lin * P_cov_estimate * F_lin.transpose(); 
                  P_cov = P_cov_pred - K * H_dep * P_cov_pred;
                  cout << "\nState std> v;\n" << X_est << endl;
                  cout << "\ncov\n" << P_cov << endl;

          } 




          MatrixXd F(2,2); 


 }
