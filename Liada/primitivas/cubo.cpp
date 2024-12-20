#include "cubo.hpp"

Cubo::Cubo(const Punto& p0, const Punto& p1, const shared_ptr<BRDF>& brdf) 
    : Primitiva(brdf) {
        Vector3 v0 = p0.getVector();
        Vector3 v1 = p1.getVector();
    ladosCubo.push_back(make_shared<RectanguloXY>(v0.x, v1.x, v0.y, v1.y, v1.z, brdf));
    ladosCubo.push_back(make_shared<RectanguloXY>(v0.x, v1.x, v0.y, v1.y, v0.z, brdf));

    ladosCubo.push_back(make_shared<RectanguloXZ>(v0.x, v1.x, v0.z, v1.z, v1.y, brdf));
    ladosCubo.push_back(make_shared<RectanguloXZ>(v0.x, v1.x, v0.z, v1.z, v0.y, brdf));

    ladosCubo.push_back(make_shared<RectanguloYZ>(v0.y, v1.y, v0.z, v1.z, v1.x, brdf));
    ladosCubo.push_back(make_shared<RectanguloYZ>(v0.y, v1.y, v0.z, v1.z, v0.x, brdf));
}

Interseccion Cubo::interseccion(const Rayo& r, double minT, double maxT) {

    Interseccion interseccion;
    interseccion.intersecta = false;
    double menorDistancia = INFINITY;

    for(int i = 0; i < ladosCubo.size(); i++){
        Interseccion inter = ladosCubo[i] -> interseccion(r,minT,maxT);

        if(inter.intersecta && inter.distancia < menorDistancia ){
            interseccion = inter;
            menorDistancia = inter.distancia;
        }
    }
    return interseccion;
}