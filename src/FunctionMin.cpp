#include "FunctionMin.hpp"

double Armijo_alpha(function_type const & fun, point const & curr, point const & grad_curr, double alpha_0, double sigma, unsigned max_iter){

    double fun_curr = fun(curr);
    double norm_sq = grad_curr.norm()*grad_curr.norm();
    unsigned it = 0;
    while( ((fun_curr - fun(curr - alpha_0*grad_curr)) < sigma*alpha_0*norm_sq) && it < max_iter ){
        alpha_0 /= 2;
        ++it;
    }
    if (it == max_iter)
        std::cout << "calculation of alpha for Armijo did not converge, alpha: " << alpha_0 << std::endl;

    return alpha_0;
}


double int_pow(double val, unsigned pow){
    double res = val;
    for(unsigned i = 1; i<pow; ++i)
        res *= val;
    return res;
}