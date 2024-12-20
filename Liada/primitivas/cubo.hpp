#pragma once

#include <vector>
#include <memory>
#include "../materiales/BRDF.hpp"
#include "../primitivas/rectangulo.hpp"
#include "../primitivas/primitiva.hpp"

using namespace std;

class Cubo : public Primitiva {
private:
    vector<shared_ptr<Primitiva>> ladosCubo; 
public:
    Cubo(const Punto& p0, const Punto& p1, const shared_ptr<BRDF>& brdf);

    Interseccion interseccion(const Rayo& r, double minT = 0.001, double maxT = INFINITY) override;
};