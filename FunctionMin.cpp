#include "FunctionMin.hpp"

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
    for(k = 0; k < max_iter && !converged; ++k){

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
                alpha = alpha_0 * exp(par*k);

            // for the gradient method using the inverse decay rule
            if constexpr(method == gradient_inverse)
                alpha = alpha_0 / (1 + par*k);

            // for the gradient method using the Armijo rule
            if constexpr(method == gradient_Armijo)
                alpha = Armijo_alpha(fun, curr, grad_curr, alpha_0, par, max_iter/2);
                // used arbitrary max_iterations

        }

        std::swap(next, curr);

    } // end of for loop

    if(k == max_iter)
        std::cout << "Method " << method << " reached max iterations without converging" << std::endl;

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
        std::cout << "calculation of alpha for Armijo did not converge" << std::endl;

    return alpha_0;
}


double int_pow(double val, unsigned pow){
    for(unsigned i = 1; i<pow; ++i)
        val *= val;
    return val;
}