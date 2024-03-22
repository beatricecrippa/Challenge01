#include "FunctionMin.hpp"

double fun(point const & x){
    return x(0)*x(1) + 4*int_pow(x(0),4) + int_pow(x(1),2) + 3*x(0);
}

point grad_fun(point const & x){
    point y(x.size());
    y(0) = x(1) + 16*int_pow(x(0),3) + 3;
    y(1) = x(0) + 2*x(1);
    return y;
}

int main(){

    const method_type method = gradient_Armijo;
    const unsigned dim = 2;

    parameters data;
    data.initial_alpha = 0.1;
    data.initial_condition.resize(dim);
    data.initial_condition << 0,0;
    data.parameter = 0.2;
    // data.max_iterations = 10;

    point min = minimize<method>(data, fun, grad_fun);

    return 0;
}