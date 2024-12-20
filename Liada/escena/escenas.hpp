#include "escena.hpp"
#include "camara.hpp"
#include "../textura/textura.hpp"
#include "../materiales/BRDFSimple.hpp"
#include "../materiales/emisor.hpp"
#include "../primitivas/plano.hpp"
#include "../primitivas/esfera.hpp"
#include "../primitivas/cubo.hpp"

Escena cornellBox_Difusa(const ValoresEscena& valores) {

    Camara camara(Direccion(-1,0,0), Direccion(0, 1, 0), Direccion(0, 0, 3),
        Punto(0, 0, -3.5), valores.width, valores.height);

    Escena sc(valores, camara);

    auto BRDFPL = make_shared<BRDFSimple>(RGB(1, 0, 0));
    auto BRDFPR = make_shared<BRDFSimple>(RGB(0, 1, 0));
    auto BRDFL = make_shared<BRDFSimple>(RGB(0.6, 0.75, 0.8));
    auto BRDFR = make_shared<BRDFSimple>(RGB(0.6, 0.7, 0.2));
    auto gray = make_shared<BRDFSimple>(RGB(0.7, 0.7, 0.7));
    auto pL = make_shared<Plano> (1, Direccion(1, 0, 0), BRDFPL);
    auto pR = make_shared<Plano> (1, Direccion(-1, 0, 0), BRDFPR);
    auto pF = make_shared<Plano> (1, Direccion(0, 1, 0), gray);
    auto pC = make_shared<Plano> (1, Direccion(0, -1, 0), gray);
    auto pB = make_shared<Plano> (1, Direccion(0, 0, -1), gray);
    auto pBack = make_shared<Plano> (-4, Direccion(0, 0, 1), gray);


    auto sL = make_shared<Esfera>(Punto(-0.5, -0.7, 0.25), 0.3, BRDFL);
    auto sR = make_shared<Esfera>(Punto( 0.5, -0.7, -0.25), 0.3, BRDFR);
    auto light  = make_shared<LuzPuntual>(Punto(0.0, 0.5, 0), RGB(1,1,1));

    sc.anadirPrimitiva(pL);
    sc.anadirPrimitiva(pR);
    sc.anadirPrimitiva(pF);
    sc.anadirPrimitiva(pC);
    sc.anadirPrimitiva(pB);

    sc.anadirPrimitiva(sL);
    sc.anadirPrimitiva(sR);

    sc.anadirLuz(light);

    return sc;
}

Escena cornellBoxOriginal(const ValoresEscena& valores) {

    Camara camara(
        Direccion(-1,0,0), Direccion(0, 1, 0), Direccion(0, 0, 3), Punto(0, 0, -3.5), 
        valores.width, valores.height
    );

    Escena sc(valores, camara);

    auto BRDFPL = make_shared<BRDFSimple>(RGB(1, 0, 0));
    auto BRDFPR = make_shared<BRDFSimple>(RGB(0, 1, 0));
    auto BRDFL = make_shared<BRDFSimple>(RGB(0.6, 0.75, 0.8));
    auto BRDFR = make_shared<BRDFSimple>(RGB(0.6, 0.7, 0.2));
    auto gray = make_shared<BRDFSimple>(RGB(0.7, 0.7, 0.7));
    auto pL = make_shared<Plano> (1, Direccion(1, 0, 0), BRDFPL);
    auto pR = make_shared<Plano> (1, Direccion(-1, 0, 0), BRDFPR);
    auto pF = make_shared<Plano> (1, Direccion(0, 1, 0), gray);
    auto pC = make_shared<Plano> (1, Direccion(0, -1, 0), gray);
    auto pB = make_shared<Plano> (1, Direccion(0, 0, -1), gray);
    auto pBack = make_shared<Plano> (-4, Direccion(0, 0, 1), gray);

    auto rL = make_shared<Cubo>(Punto(-0.7, -1, 0), Punto(-0.3, 0.2, 0.4), BRDFL);
    auto rR = make_shared<Cubo>(Punto(0.3, -1, -0.4), Punto(0.7, -0.3, 0), BRDFR);
    auto light  = make_shared<LuzPuntual>(Punto(0.0, 0.5, 0), RGB(1,1,1));

    sc.anadirPrimitiva(pL);
    sc.anadirPrimitiva(pR);
    sc.anadirPrimitiva(pF);
    sc.anadirPrimitiva(pC);
    sc.anadirPrimitiva(pB);

    sc.anadirPrimitiva(rL);
    sc.anadirPrimitiva(rR);

    sc.anadirLuz(light);

    return sc;
}

Escena cornellBoxOriginal2(const ValoresEscena& valores) {

    Camara camara(
        Direccion(-1,0,0), Direccion(0, 1, 0), Direccion(0, 0, 3), Punto(0, 0, -3.5), 
        valores.width, valores.height);

    Escena sc(valores, camara);

    auto emissionPink = make_shared<Emisor>(RGB(1, 0, 1));
    auto emissionCyan = make_shared<Emisor>(RGB(0, 1, 1));
    auto BRDFL = make_shared<BRDFSimple>(RGB(0.6, 0.75, 0.8));
    auto BRDFR = make_shared<BRDFSimple>(RGB(0.6, 0.7, 0.2));
    auto gray = make_shared<BRDFSimple>(RGB(0.7, 0.7, 0.7));
    auto pL = make_shared<Plano> (2, Direccion(1, 0, 0), emissionPink);
    auto pR = make_shared<Plano> (2, Direccion(-1, 0, 0), emissionCyan);
    auto pF = make_shared<Plano> (1, Direccion(0, 1, 0), gray);
    auto pC = make_shared<Plano> (1, Direccion(0, -1, 0), gray);
    auto pB = make_shared<Plano> (1, Direccion(0, 0, -1), gray);
    auto pBack = make_shared<Plano> (-4, Direccion(0, 0, 1), gray);

    auto rL = make_shared<Cubo>(Punto(-0.7, -1, 0), Punto(-0.3, 0.2, 0.4), BRDFL);
    auto rR = make_shared<Cubo>(Punto(0.3, -1, -0.4), Punto(0.7, -0.3, 0), BRDFR);
    auto light  = make_shared<LuzPuntual>(Punto(0.0, 0.5, 0), RGB(1,1,1));

    sc.anadirPrimitiva(pL);
    sc.anadirPrimitiva(pR);
    sc.anadirPrimitiva(pF);
    sc.anadirPrimitiva(pC);
    sc.anadirPrimitiva(pB);

    sc.anadirPrimitiva(rL);
    sc.anadirPrimitiva(rR);

    //sc.anadirLuz(light);

    return sc;
}