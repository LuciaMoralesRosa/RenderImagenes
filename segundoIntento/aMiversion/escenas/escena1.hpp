#include "escena.hpp"

class Escena1 : public Escena {
    private:

    public:

    Escena1() {}

    void aniadirCamara(Camara& c) override {
        c = Camara(Punto(0,0,-3.5), Direccion(-1,0,0), Direccion(0,1,0), Direccion(0,0,3), 256, 256);
    }

    void aniadirLuces(vector<Luz>& luces) {
        luces.push_back(Luz(Punto(0, 0.5, 0), RGB(0.99, 0.99, 0.99)));
    }

    void aniadirPrimitivas(list<Primitiva*>& primitivas) {
        Material m1(RGB(0.8, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), 0);
        Material m2(RGB(0.0, 0.8, 0.0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), 0);
        Material m3(RGB(0.8, 0.8, 0.8), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), 0);
        Material m4(RGB(0.8, 0.8, 0.8), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), 0);
//        Material m5(RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0.99, 0.99, 0.99), 0);
        Material m5(RGB(1, 1, 1), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), 0);

        Material m6(RGB(0.11, 0.41, 0.375), RGB(0.4, 0.4, 0.4), RGB(0, 0, 0), RGB(0, 0, 0), 0);
        Material m7(RGB(0,0,0), RGB(0.4, 0.4, 0.4), RGB(0.4, 0.4, 0.4), RGB(0, 0, 0), 1.5);

        primitivas.push_back(new Plano(0, Direccion(1,0,0), 1, m1));
        primitivas.push_back(new Plano(1, Direccion(-1,0,0), 1, m2)); 
        primitivas.push_back(new Plano(2, Direccion(0,1,0), 1, m3));    
        primitivas.push_back(new Plano(4, Direccion(0,0,-1), 1, m4));
        primitivas.push_back(new Plano(3, Direccion(0,-1,0), 1, m5));

        primitivas.push_back(new Esfera(5, Punto(-0.5, -0.7, 0.25), 0.3, m6));
        primitivas.push_back(new Esfera(6, Punto(0.5, -0.7, -0.25), 0.3, m7));
    }

    void crearEscena(Camara& camara, list<Primitiva*>& primitivas, vector<Luz>& luces) override {
        aniadirCamara(camara);
        aniadirLuces(luces);
        aniadirPrimitivas(primitivas);
    }
};