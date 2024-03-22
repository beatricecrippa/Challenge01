# Readme for Challenge01
Challenge 1 for the course pacs

The code implemets the methods Exponential decay, Inverse decay, Armijo.
It can work with functions in any dimension and any initial condition, other than the case presented in the text of the challenge is already implemented another example in 3 dimensions. All the parameters (except the functions) can be set changing the .txt files in the folder examples, GetPot is used to read parameters from .txt files. New functions can be set in Functions.hpp.
The implementation uses the module eigen to manage vectors in a generic dimension.

The code is devided in:
- src:
    Parameters.hpp containing type definitions, an enumerator definition used to choose the method, struct containing the parameters
    Parameters.cpp containing the code to read from .txt files using GetPot
    Functions.hpp containing a struct to store a function and its gradient, here are also defined the functions used in the examples in 2 and 3 dimensions
    FunctionMin.hpp containing the template function that operates the minimization (template parameter is the method choosen for the minimalization)
    main.cpp 
    Makefile

- include:
    GetPot 

- examples:
    parameters.txt containing the parameters int the text of the challenge
    test_exp.txt containing an example that uses the Exponential decay method
    test_inv.txt containing an example that uses the Inverse decay method
    test_Armijo containing an example in 3D that uses the Armijo method

To compile in the folder ./src run `make` or `make all`
To run with the default parameters in the folder ./src run `./main`
To run with other parameters in the folder ./src run `./main -f ../examples/filename.txt` using the name of the chosen example instead of filename.txt 
To delete all object files in the folder ./src run `make clean`
To delete all the files produced by the compilation in the folder ./src run `make distclean`