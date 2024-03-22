#ifndef FUNCTIONMIN_HPP_
#define FUNCTIONMIN_HPP_

#include "Parameters.hpp"
#include <cmath>



// function used to update alpha using the Armijo rule
// fun is the function to minimize, curr is the current point x_k, grad_curr is the gradient of the function evaluated at x_k
// alpha0 is the initial alpha, sigma is the additional parameter for the method, max_iter is the maximum number of iterations of the loop in this funcition
double Armijo_alpha(function_type const & fun, point const & curr, point const & grad_curr, double alpha_0, double sigma, unsigned max_iter);


// function that operates the minimization
// data is a struct containing the parameters needed, fun is the function to minimize and grad_fun is its gradient
template<method_type method>
point minimize(Parameters const & data, function_type const & fun, gradient_type const & grad_fun){

    // x_k and x_k+1
    point curr = data.initial_condition;
    point next = curr;

    // variable to store grad_fun(curr) to avoid repeting the calculation of the value
    point grad_curr = curr; // updated inside the loop

    // parameters
    double alpha = data.initial_alpha;

    // variables used to check for convergence
    double step = 1;
    double residual = 1;
    bool converged = false;
    
    unsigned k;
    for(k = 1; k < data.max_iterations && !converged; ++k){

        // updating the gradient
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
                alpha = data.initial_alpha * exp(-data.param*k);

            // for the gradient method using the inverse decay rule
            if constexpr(method == gradient_inverse)
                alpha = data.initial_alpha / (1 + data.param*k);

            // for the gradient method using the Armijo rule
            if constexpr(method == gradient_Armijo)
                alpha = Armijo_alpha(fun, curr, grad_curr, data.initial_alpha, data.param, data.max_iterations/10);
                // used arbitrary max_iterations

        }
       
        std::swap(next, curr);


    } // end of for loop

    if(k == data.max_iterations)
        std::cout << "Method reached max iterations without converging" << std::endl;
    else
        std::cout << "Method converged in " << k << " iterations, minimizer point: \n" << curr << std::endl;

    return curr;   
}


double Armijo_alpha(function_type const & fun, point const & curr, point const & grad_curr, double alpha_0, double sigma, unsigned max_iter){

    double fun_curr = fun(curr);
    double norm_sq = grad_curr.norm()*grad_curr.norm();
    unsigned it = 0;
    while( ((fun_curr - fun(curr - alpha_0*grad_curr)) < sigma*alpha_0*norm_sq) && it < max_iter ){
        alpha_0 /= 2;
        ++it;
    }
    if (it == max_iter)
        std::cerr << "calculation of alpha for Armijo did not converge, alpha: " << alpha_0 << std::endl;

    return alpha_0;
}



#endif /* FUNCTIONMIN_HPP_ */