#include "FunctionMin.hpp"
#include "Functions.hpp"



int main(int argc, char **argv){

    GetPot command_line(argc, argv);
    const std::string filename = command_line.follow("../examples/parameters.txt", 2, "-f", "--file");

    // Parameters struct declared in Parameters.hpp
    Parameters data(filename);

    // Functions struct declared in Functions.hpp
    Functions func;

    // uses the function in the text of the challenge
    if(data.dimension == 2){
        func.fun = fun2D;
        func.grad_fun = grad_fun2D;
    }

    // uses an example of function R3 -> R
    if(data.dimension == 3){
        func.fun = fun3D;
        func.grad_fun = grad_fun3D;
    }

    if (data.method == gradient_exp){
        std::cout << "Using gradient exponential decay method:" << std::endl;
        point min = minimize<gradient_exp>(data, func.fun, func.grad_fun);
    }

    if (data.method == gradient_inverse){
        std::cout << "Using gradient inverse decay method:" << std::endl;
        point min = minimize<gradient_inverse>(data, func.fun, func.grad_fun);
    }
    
    if (data.method == gradient_Armijo){
        std::cout << "Using gradient Armijo method:" << std::endl;
        point min = minimize<gradient_Armijo>(data, func.fun, func.grad_fun);
    }
    
    

    return 0;
}
