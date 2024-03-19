#ifndef FUNCTIONMIN_H_
#define FUNCTIONMIN_H_

#include <functional>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>

typedef Eigen::VectorXd point;
typedef std::function<double(point const &)> function_type;
typedef std::function<point(point const &)> gradient_type;

struct parameters{
    point initial_condition;
    double tol_step = 1e-6;
    double tol_residual = 1e-6;
    double initial_alpha;
    double parameter;
    unsigned max_iterations = 1e4;
};

/*
enum gradient_type{
    numerical,
    analytical,
};
*/

enum method_type{
    gradient_exp,
    gradient_inverse,
    gradient_Armijo,
};

/*
template<gradient_type gradient, method_type method>
point minimize(parameters const & data, function_type const & fun, gradient_type const & grad_fun);
*/


// function used to update alpha using the Armijo rule
// fun is the function to minimize, curr is the current point x_k, grad_curr is the gradient of the function evaluated at x_k
// alpha0 is the initial alpha, sigma is the additional parameter for the method, max_iter is the maximum number of iterations of the loop in this funcition
double Armijo_alpha(function_type const & fun, point const & curr, point const & grad_curr, double alpha_0, double sigma, unsigned max_iter);


// function that operates the minimization
template<method_type method>
point minimize(parameters const & data, function_type const & fun, gradient_type const & grad_fun);


// function to calculate positive integer powers
double int_pow(double val, unsigned pow);


#endif /* FUNCTIONMIN_H_ */