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


int main(int argc, char **argv){

    method_type method = gradient_Armijo;

    Parameters data("../examples/parameters.txt");
    
    if (method == gradient_Armijo)
        point min = minimize<gradient_Armijo>(data, fun, grad_fun);
    

    return 0;
}