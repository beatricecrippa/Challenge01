#include "FunctionMin.hpp"


double fun(point const & x){
    return x(0)*x(1) + 4*int_pow(x(0),4) + int_pow(x(1),2) + 3*x(0);
}

point grad_fun(point const & x){
    point y(x.size());
    y(0) = x(1) + 16*x(0) + 3;
    y(1) = x(0) + 2*x(1);
    return y;
}

int main(){

    const method_type method = gradient_Armijo;

    parameters data;
    data.initial_alpha = 0.2;
    data.initial_condition << 1,1;
    data.parameter = 0.35;

    
    point min = minimize<method>(data, fun, grad_fun);

    std::cout << "Method converged, minimum: " << min << std::endl;
    return 0;
}