#include "pathtracer.hpp"

RGB nextEventEstimation(const Escena& escena, const Punto origen, const Interseccion& it) {
    RGB totalContrib;
    for (auto l : escena.luces) {
        auto lp = dynamic_pointer_cast<LuzPuntual>(l);
        if (lp == nullptr) {
            continue;
        }
        
        Direccion rayoDirecto = lp->getCentro() - origen;

        Rayo r(origen, rayoDirecto.normalizada());

        Interseccion interseccion;
        interseccion.intersecta = false;

        double distanciaMenor = INFINITY;

        for (auto& p : escena.primitivas) {
            Interseccion inter = p->interseccion(r, 0, rayoDirecto.modulo());
            // Obtener la interseccion mas cercana al origen del rayo
            if (inter.intersecta && inter.distancia < distanciaMenor) {
                // Si la interseccion encontrada intersecta en una distancia
                // menor a la actual se sustituye
                interseccion = inter;
                distanciaMenor = inter.distancia;
            }
        }

        // Si el rayo de sombra no intersecta con nada -> se añade su contribucion
        if (!interseccion.intersecta) {
            double contribucionGeometrica = abs(productoEscalar(it.normal, normalizar(rayoDirecto)));

            RGB materialContrib = it.textura->eval(r(it.distancia), rayoDirecto, r.getDireccion(), it) / M_PI;

            RGB lightContrib = l->getPotencia() / productoEscalar(rayoDirecto, rayoDirecto) * materialContrib * contribucionGeometrica;
            totalContrib = totalContrib + lightContrib;
        }
    }

    return totalContrib;
}

/**
 * @brief Perform path tracing up to n bounces starting with ray r on the scene.
 * 
 * @param escena The scene
 * @param r The ray
 * @param n The number of remaining bounces
 * @return RGB 
 */
RGB pathTraceRay(const Escena& escena, const Rayo& r, unsigned int rebotesRestantes) {
    if(rebotesRestantes > escena.getValores().rebotes) {
        throw std::runtime_error("El numero de rebotes restantes es mayor que el total");
    }
    
    RGB contrib;
    Interseccion interseccion;
    interseccion.intersecta = false;

    double menorDistancia = INFINITY;
    for (auto p : escena.primitivas) {

        Interseccion inter = p->interseccion(r, 0);
        if (inter.intersecta && inter.distancia < menorDistancia){
            interseccion = inter;
            menorDistancia = inter.distancia;
        }
    }
    
    // Trazar rayo de luz directa
    if(interseccion.intersecta) {
        if (interseccion.textura->esEmisor()) {
            // The object is an emitter, just add the emission value
            return interseccion.textura->eval(Vector3(), Vector3(), Vector3(), Interseccion{});
        } else {

            auto result = interseccion.textura->sample(normalizar(r.getDireccion()), r(interseccion.distancia), interseccion);
            
            // Check if ray was absorbed
            if (!result.has_value()) {
                return RGB();
            } 

            auto [ omega, li, isDelta ] = result.value();
            Rayo out(r(interseccion.distancia), omega);

            contrib = contrib 
                + nextEventEstimation(escena, r(interseccion.distancia), interseccion);
                
            if ( rebotesRestantes < escena.getValores().rebotes ) {
                contrib = contrib + li * pathTraceRay(escena, out, rebotesRestantes + 1);
            }   
        }
    } else {
        return escena.sampledColor(r.getDireccion());
    }

    //cout << "contrib final del bounce: " << n << "," << contrib << endl;
    return contrib;
}

ImagenPPM pathTracing(const Escena& escena) {

    // task function should have pixel position and rays as arguments
    using TaskFn = std::function<Pixel(void)>;

    Threadpool<TaskFn, Pixel> tp(escena.getValores().hilos);

    ImagenPPM imagen(escena.getValores().width, escena.getValores().height);

    for (unsigned int i = 0; i < imagen.getAltura(); i++) {
        for (unsigned int j = 0; j < imagen.getBase(); j++) {
            tp.encolarTarea([&, i, j]() -> Pixel {
                RGB contrib;

                list<Rayo> listaRayos = escena.getCamara().rayoPorPixel(j, i, escena.getValores().factorAntialising);

                for(const Rayo& r : listaRayos) {
                    contrib = contrib + pathTraceRay(escena, r, 0);
                }
                Pixel pixelResultante;
                pixelResultante.x = j;
                pixelResultante.y = i;
                pixelResultante.contribucion = contrib / (double)listaRayos.size() ;
                return pixelResultante; 
            });
        }
    }
    double aux = 0;

    for (unsigned int i = 0; i < imagen.getAltura(); i++) {
        for (unsigned int j = 0; j < imagen.getBase(); j++) {
            double progreso = double( i * imagen.getBase() + j ) / double(imagen.getAltura() * imagen.getBase());
            if (progreso >= aux) {
                aux += 0.01;
                cout << setprecision(3) << progreso << " % .. " << flush;
            }

            Pixel res = tp.getResultado();
            imagen.setPixelMatriz(res.y, res.x, res.contribucion);

            double maximo = max({imagen.getValorMax(), res.contribucion.getR(), res.contribucion.getG(), res.contribucion.getB()});
            imagen.setValorMax(maximo);
        }
    }
    return imagen;
}