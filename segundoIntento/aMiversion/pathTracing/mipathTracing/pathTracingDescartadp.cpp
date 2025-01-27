#include "pathTracing.hpp"


RGB colorInterseccion (const Primitiva* primitiva, list<Primitiva*> primitivas, const Punto& pInter,
    Luz& luz, const Camara& camara, RGB& colorDisipado, Efecto efecto,
    Direccion direccionCamara){
    
	// Check if the plane is against the light.
	if (primitiva->planoContraLuz(camara, luz, pInter)) {
		return RGB(0);
	}

	// Check if the point is in shadow.
	Vector direccionRayo = distancia(luz.centro, pInter);
	float moduloRayo = direccionRayo.modulo();
	float d; // Distancia al punto de interseccion

	for (Primitiva* p : primitivas) {
		bool intersecta = p->intersecta(Rayo(pInter, direccionRayo), d);
		bool hayDistancia = (1 - d) * moduloRayo > 1e-6;
		bool noEsElMismo = p != primitiva ||
			distancia(pInter, luz.centro - d * (direccionRayo)).modulo() > 1e-4;

		if (intersecta && hayDistancia && noEsElMismo) {
			return RGB(0);
		}
	}

	// Calculate the color of the hit.
	RGB Li = luz.potencia / (moduloRayo * moduloRayo);
	float cosine = abs(escalar(primitiva->obtenerNormal(pInter), direccionRayo.normalizar()));
    BRDF brdf(primitiva->obtenerMaterial(), primitiva->obtenerNormal(pInter));
	return Li * brdf.getFr(efecto, direccionCamara, pInter) * cosine * colorDisipado;
}


void captureSection(Camara& camara, list<Primitiva*> primitivas, vector<Luz> luces,
    int rpp, int minX, int maxX, int minY, int maxY, vector<RGB>& valoresPixeles){
    Vector modL = camara.l.normalizar(); // Vector L de camara normalizado
	Vector modU = camara.u.normalizar(); // Vector U de camara normalizado
	Vector esquinaSupIzq = camara.f + camara.l + camara.u;	
	GeneradorAleatorios rand(0, 1);	// Generador de numeros aleatorios entre 0 y 1
	RGB colorPixel, colorRayo; // Color del pixel y del rayo
	Rayo rayoCamara; // Rayo de la camara al punto a evaluar
	Direccion direccionCamara; // Direccion del rayo de la camara al punto a evaluar
	float t, minT; // Distancia menor a la que intersecta el rayo
	Punto pInter; // Punto de interseccion del rayo
	Primitiva* primitiva; // Primitiva con la que intersecta el rayo
	RGB colorDisipado; // Color disipado por la primitiva
	Efecto efecto;	// Efecto de la interseccion
	
	// Para cada pixel en la seccion [minX, maxX]x[minY, maxY]
	for (int i = minY; i < maxY; i++){
		for (int j = minX; j < maxX; j++) {

			colorPixel = RGB();

			// Para cada rayo lanzado por pixel
			for (int k = 0; k < rpp; k++) {

				// El rayo empieza sin color
				colorRayo = RGB();
				colorDisipado = RGB(1);

				// Obtenemos la direccion del rayo desde la camara al punto a evaluar
				// Esquina superior como referencia + j bases de pixel + i alturas de pixel
				direccionCamara = Direccion(esquinaSupIzq -
					(j + rand.get()) * camara.basePixel * modL -
					(i + rand.get()) * camara.alturaPixel * modU);

				// Creamos el rayo de la camara al punto a evaluar
				rayoCamara = Rayo(camara.o, direccionCamara);

				// Mientras el rayo intersecte con una primitiva y no sea 
				// absorbido
				while (true) {
					minT = 1e6; // Distancia minima a la que intersecta
					primitiva = nullptr; // Primitiva con la que intersecta

					// Obtener la primera primitiva con la que intersecta
					for (Primitiva* p : primitivas) {
						if (p->intersecta(rayoCamara, t) && t < minT) {
							minT = t;
							primitiva = p;
						}
					}

					// No ha intersectado con primitiva -> termina el bucle
					if (primitiva == nullptr) { break; }

					// Si ha intersectado, obtenemos el punto de interseccion
					pInter = rayoCamara.obtenerOrigen() + minT * rayoCamara.obtenerDireccion();

					// Obtenemos el efecto dependiendo del material de la primitiva
                    BRDF brdf = BRDF(primitiva->obtenerMaterial(), primitiva->obtenerNormal(pInter));
					efecto = brdf.obtenerEfecto();

					bool terminar = false;
					switch(efecto) {
						case ABSORCION:
							terminar = true;
							break;
						case LUZ:
							colorRayo += brdf.kl * colorDisipado;
							terminar = true;
							break;
						case REFLEXION || REFRACCION:
							colorDisipado *= brdf.getFr(efecto, direccionCamara, pInter);
							break;
						default:
							for (int i = 0; i < luces.size(); ++i) {
								colorRayo += colorInterseccion(primitiva, primitivas,
									pInter, luces[i], camara, colorDisipado,
									efecto, direccionCamara);
							}
							colorDisipado *= M_PI * brdf.getFr(efecto, direccionCamara, pInter);
					}

					if (terminar) { break; }

					// Actualizamos el rayo para que siga desde el punto de interseccion
					pInter = pInter + 1e-4 * direccionCamara;
					rayoCamara = Rayo(pInter, direccionCamara);

				}

				// Si el color es valido, se suma a la suma total del pixel
				if (isnan(colorRayo[0]) || isnan(colorRayo[1]) || isnan(colorRayo[2])) {
					k--;
				}
				else {
					colorPixel += colorRayo;
				}
			}

			// Guardamos el color del pixel en el vector de valores de pixeles
			valoresPixeles[j * camara.altura + i] = colorPixel;
        }
	}
}

void captureSlave (Camara& camara, list<Primitiva*> primitivas, vector<Luz> luces,
    int rpp, GestorDeSecciones& secciones, vector<RGB>& valoresPixeles){
    int minX, maxX, minY, maxY;
    // While there are sections left to capture, get one and capture it.
    while (secciones.getSection(minX, maxX, minY, maxY)){
        captureSection(camara, primitivas, luces, rpp, minX, maxX, minY, maxY,
			valoresPixeles);
	}
}

void escribirImagen(ofstream& salida, int b, int a, vector<RGB>& pixeles, float max, int rpp) {
	// Escribir la cabecera de la imagen
	salida << "P3" << endl;
	salida << b << " " << a << endl;

	// Escribir el valor maximo de los pixeles
	salida << max * 255 / rpp << endl;

	// Escribir los pixeles en la imagen
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			RGB color = pixeles[j * a + i];
			salida << color * 255 / rpp << "    ";
		}
		salida << endl;
	}
	salida.close();
}

void pathTracing(Camara& camara, list<Primitiva*> primitivas, vector<Luz> luces,
    int rpp, int hilos, string fichero){
    
	// Apertura del fichero donde escribir la imagen
	ofstream salida(fichero);
	if (!salida.is_open()) {
		// Si no se puede abrir el fichero
		cerr << "Error en la apertura del fichero \"" << fichero << "\"" << endl;
		exit(1);
	}

	int base = camara.base;
	int altura = camara.altura;
	
	// Estructura para almacenar los pixeles de la imagen
	vector<RGB> pixeles(altura * base);

	// Divide the image into sections.
	GestorDeSecciones secciones(base, altura, hilos);

	// Divide the work between the hilos. Each one will be capturing a section
	// of the image while there are sections left.
	vector<thread> threadsArray(hilos);
	for (int t = 0; t < hilos; t++) {
		threadsArray[t] = thread(&captureSlave, ref(camara), ref(primitivas),
				ref(luces), rpp, ref(secciones), ref(pixeles));
	}

	// Wait for all hilos to finish.
	for (int t = 0; t < hilos; t++) {
		threadsArray[t].join();
	}

	// Encontrar el valor maximo de los pixeles
	float max = 0;
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < base; j++) {
			RGB pxColor = pixeles[i*base + j];
			if (pxColor[0] > max) { max = pxColor[0]; }
			if (pxColor[1] > max) { max = pxColor[1]; }
			if (pxColor[2] > max) { max = pxColor[2]; }
		}
	}

	double valorMax = max * 255 / rpp;

	ImagenPPM imagen(base, altura, valorMax);

	// Establecer los colores en la imagen
	vector<RGB> coloresImagen(base * altura);

	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < base; j++) {
			RGB color = pixeles[j * altura + i];
			coloresImagen.push_back(color * 255 / rpp);
		}
	}

	imagen.establecerPixeles(coloresImagen);

	imagen.escribirImagen(fichero);
	
	//escribirImagen(salida, base, altura, pixeles, max, rpp);

}






