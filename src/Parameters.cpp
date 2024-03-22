#include "Parameters.hpp"

Parameters::Parameters(const std::string &filename)
{
    GetPot file(filename.c_str());

    dimension = file("dimension", 2);

    initial_condition.resize(dimension);
    std::string tmp = file("initial_condition", "");
    string_to_point(initial_condition, tmp);

    tol_step = file("tol_step", 1e-6);

    tol_residual = file("tol_residual", 1e-6);

    initial_alpha = file("initial_alpha", 0.1);

    param = file("param", 0.2);

    max_iterations = file("max_iterations", 1e4);

    method = static_cast<method_type>(file("method", 2));
}

void string_to_point(point& vec, const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    unsigned i = 0;

    while (std::getline(iss, token, ',') && i < vec.size()) {
        double value = std::stod(token);
        vec(i) = value;
        ++i;
    }
}

