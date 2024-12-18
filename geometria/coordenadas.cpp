#include "coordenadas.hpp"

ostream& operator<< (ostream& os, Coordenada coor){

    os << coor.matrix;

    return os;
}

Coordenada translation(const Coordenada& coord, const Vector3 v){

    Coordenada transform;

    transform.matrix[0][3] = v.x;
    transform.matrix[1][3] = v.y;
    transform.matrix[2][3] = v.z;

    return transform(coord);
}

Coordenada rotationX(const Coordenada& coord, double theta) {

    Coordenada transform;

    double coseno = cos(theta);
    double seno = sin(theta);

    transform.matrix[1][1] = coseno;
    transform.matrix[2][1] = seno;
    transform.matrix[1][2] = -seno;
    transform.matrix[2][2] = coseno;

    return transform(coord);
}

Coordenada rotationY(const Coordenada& coord,  double theta){

    Coordenada transform;

    double coseno = cos(theta);
    double seno = sin(theta);

    transform.matrix[0][0] = coseno;
    transform.matrix[2][0] = -seno;
    transform.matrix[0][2] = seno;
    transform.matrix[2][2] = coseno;

    return transform(coord);
}

Coordenada rotationZ(const Coordenada& coord, double theta){

    Coordenada transform;

    double coseno = cos(theta);
    double seno = sin(theta);
    
    transform.matrix[0][0] = coseno;
    transform.matrix[1][0] = seno;
    transform.matrix[0][1] = -seno;
    transform.matrix[1][1] = coseno;

    return transform(coord);
}

Coordenada scale(const Coordenada& coord, const Vector3 v){

    Coordenada transform;

    transform.matrix[0][0] = v.x;
    transform.matrix[1][1] = v.y;
    transform.matrix[2][2] = v.z;

    return transform(coord);
}

Coordenada changeBasis(const Coordenada& coord, const Vector3 u, const Vector3 v, const Vector3 w, const Vector3 o){

    Coordenada transform;

    transform.matrix[0][0] = u.x;
    transform.matrix[1][0] = u.y;
    transform.matrix[2][0] = u.z;

    transform.matrix[0][1] = v.x;
    transform.matrix[1][1] = v.y;
    transform.matrix[2][1] = v.z;

    transform.matrix[0][2] = w.x;
    transform.matrix[1][2] = w.y;
    transform.matrix[2][2] = w.z;

    transform.matrix[0][3] = o.x;
    transform.matrix[1][3] = o.y;
    transform.matrix[2][3] = o.z;

    return transform(coord);
}

Coordenada inverseTransformation(Coordenada coor) {
    return Coordenada(coor.matrix.inverse());
}