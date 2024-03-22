#include "GetPot"
#include "Parameters.hpp"

Parameters::Parameters(const std::string &filename)
{
    GetPot file(filename.c_str());

    dimension = file("dimension", 2);

    initial_condition.resize(dimension);;

    tol_step = file("tol_step", 1e-6);

    tol_residual = file("tol_residual", 1e-6);

    initial_alpha = file("initial_alpha", 0.1);

    param = file("param", 0.2);

    max_iterations = file("max_iterations", 1e4);

}