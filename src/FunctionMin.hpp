#ifndef CHALLENGE01_FUNCTIONMIN_H_
#define CHALLENGE01_FUNCTIONMIN_H_

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


// function to calculate positive integer powers
double int_pow(double val, unsigned pow);



// function that operates the minimization
template<method_type method>
point minimize(parameters const & data, function_type const & fun, gradient_type const & grad_fun){

    // x_k and x_k+1
    point curr = data.initial_condition;
    point next = curr;

    // variable to store grad_fun(curr) to avoid repeting the calculation of the value
    point grad_curr = curr; // updated inside the loop

    // parameters
    double alpha_0 = data.initial_alpha;
    double alpha = alpha_0;
    double par = data.parameter;

    // variables used to check for convergence
    double step = 1;
    double residual = 1;
    unsigned max_iter = data.max_iterations;
    bool converged = false;
    
    unsigned k;
    for(k = 1; k < max_iter && !converged; ++k){

        // updating the graduent
        grad_curr = grad_fun(curr);

        // iteration step
        next = curr - alpha * grad_curr;
        
        // check for convergence
        step = (next-curr).norm();
        residual = grad_curr.norm();
        if(step < data.tol_step || residual < data.tol_residual)
            converged = true;

        // if not converged update alpha
        else{

            // for the gradient method using the exponential decay rule
            if constexpr(method == gradient_exp)
                alpha = alpha_0 * exp(-par*k);

            // for the gradient method using the inverse decay rule
            if constexpr(method == gradient_inverse)
                alpha = alpha_0 / (1 + par*k);

            // for the gradient method using the Armijo rule
            if constexpr(method == gradient_Armijo)
                alpha = Armijo_alpha(fun, curr, grad_curr, alpha_0, par, max_iter/10);
                // used arbitrary max_iterations

        }
       
        std::swap(next, curr);


    } // end of for loop

    if(k == max_iter)
        std::cout << "Method " << method << " reached max iterations without converging" << std::endl;
    else
        std::cout << "Method converged in " << k << " iterations, minimum: \n" << curr << std::endl;

    return curr;   
}

#endif /* CHALLENGE01_FUNCTIONMIN_H_ */