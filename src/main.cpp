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

    GetPot command_line(argc, argv);
    const std::string filename = command_line.follow("../examples/parameters.txt", 2, "-f", "--file");


    Parameters data(filename);

    if (data.method == gradient_exp){
        std::cout << "Using gradient exponential decay method" << std::endl;
        point min = minimize<gradient_exp>(data, fun, grad_fun);
    }

    if (data.method == gradient_inverse){
        std::cout << "Using gradient inverse decay method" << std::endl;
        point min = minimize<gradient_inverse>(data, fun, grad_fun);
    }
    
    if (data.method == gradient_Armijo){
        std::cout << "Using gradient Armijo method" << std::endl;
        point min = minimize<gradient_Armijo>(data, fun, grad_fun);
    }
    
    

    return 0;
}
