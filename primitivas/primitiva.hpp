#pragma once 

#include <memory>
#include <iostream>
#include "../materiales/BRDF.hpp"

using namespace std;

/**
 * @brief Base class for representing geometric primitives
 */
class Primitiva {
public:
    shared_ptr<BRDF> brdf;
    Primitiva(const shared_ptr<BRDF>& _b) : brdf(_b) {}; 

   
    virtual Interseccion interseccion(const Rayo& r, double minT, double maxT = INFINITY) = 0; 

    virtual ~Primitiva() { }
};