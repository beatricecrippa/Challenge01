#include "FunctionMin.hpp"

template<method_type method>
point minimize(parameters const & data, function_type const & fun, gradient_type const & grad_fun){

    // x_k and x_k+1
    point curr = data.initial_condition;
    point next = curr;

    // variable to store grad_fun(curr) to avoid repeting the calculation of the value
    point grad_curr = curr; // updated inside the loop

    // parameters
    double alpha = data.initial_alpha;
    double alpha = alpha_0;
    double par = data.parameter;

    // check for convergence
    double step = 1;
    double residual = 1;
    unsigned max_iter = data.max_iterations;
    bool converged = false;
    
    for(unsigned k = 0; k < max_iter && !converged; ++k){

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
                alpha = data.initial_alpha * exp(par*k);

            // for the gradient method using the inverse decay rule
            if constexpr(method == gradient_inverse)
                alpha = data.initial_alpha / (1 + par*k);

            // for the gradient method using the Armijo rule
            if constexpr(method == gradient_Armijo)
                alpha = Armijo_alpha(fun, grad_curr, data.initial_alpha)

        }


    }




}

double Armijo_alpha(function_type const & fun, point const & grad_curr, double alpha0, double sigma, unsigned max_iter){



}