#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include "Parameters.hpp"


struct Functions{
    function_type fun;
    gradient_type grad_fun;
};


// function to calculate positive integer powers
double int_pow(double val, unsigned pow){
    double res = val;
    for(unsigned i = 1; i<pow; ++i)
        res *= val;
    return res;
}


// function in the text of the challenge
double fun2D(point const & x){
    return x(0)*x(1) + 4*int_pow(x(0),4) + int_pow(x(1),2) + 3*x(0);
}

// gradient of the function in the text of the challenge
point grad_fun2D(point const & x){
    point y(x.size());
    y(0) = x(1) + 16*int_pow(x(0),3) + 3;
    y(1) = x(0) + 2*x(1);
    return y;
}

// x^2+6*y^2+z^2 - z
double fun3D(point const & x){
    return x(0)*x(0) + 6*x(1)*x(1) + x(2)*x(2) - x(2);
}

// (2 x, 12 y, -1 + 2 z)
point grad_fun3D(point const & x){
    point y(x.size());
    y(0) = 2*x(0);
    y(1) = 12*x(1);
    y(2) = 2*x(2) -1;
    return y;
}






#endif /* FUNCTIONS_HPP_ */