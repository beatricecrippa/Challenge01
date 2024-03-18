#ifndef FUNCTIONMIN_H_
#define FUNCTIONMIN_H_

#include <functional>
#include <Eigen/Dense>
#include <cmath>

typedef Eigen::VectorXd point;
typedef std::function<double(point const &)> function_type;
typedef std::function<point(point const &)> gradient_type;

struct parameters{
    point initial_condition;
    double tol_step;
    double tol_residual;
    double initial_alpha;
    double parameter;
    unsigned max_iterations;
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
double Armijo_alpha(function_type const & fun, point const & grad_curr, double alpha0, double sigma, unsigned max_iter);


// function that operates the minimization
template<method_type method>
point minimize(parameters const & data, function_type const & fun, gradient_type const & grad_fun);


#endif /* FUNCTIONMIN_H_ */