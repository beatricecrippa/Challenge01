#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

#include <functional>
#include <Eigen/Dense>
#include <iostream>
#include "GetPot"

using point = Eigen::VectorXd;
using function_type = std::function<double(point const &)>;
using gradient_type = std::function<point(point const &)>;



enum method_type{
    gradient_exp,
    gradient_inverse,
    gradient_Armijo,
};


struct Parameters{

    // constructor to read parameters using GetPot
    Parameters(const std::string &filename);

    // dimension of the system 
    unsigned dimension;

    // initial point from which to start the iterations
    point initial_condition;

    // tolerance to control the step length
    double tol_step;

    // tolerance to control the norm of the gradient
    double tol_residual;

    // initial value of alpha
    double initial_alpha;

    // value of the additional parameter of the method
    // it's the value of mu for exponential decay and inverse decay
    // it's the value of sigma for Armijo
    double param;

    // maximum number of iterations
    unsigned max_iterations;

    // Algorithm to implement the minimization
    method_type method;
    
};

// helper function used to read the initial condition using GetPot:
// in the file .txt the initial condition is passed as a string, this function 
// converts the string to a point
void string_to_point(point& vec, const std::string& str);




#endif /* PARAMETERS_HPP_ */