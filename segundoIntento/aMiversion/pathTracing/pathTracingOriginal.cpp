#include "pathTracingOriginal.hpp"

const int N_REBOTES = 10;

RGB colorInterseccion(const Primitiva* primitiva, list<Primitiva*> primitivas,
	const Punto& pInterseccion, Luz& luz, const Camara& camara,
	RGB& colorDisipado, Efecto efecto, Direccion direccionRayo){

	// Comprobar si el plano esta contra la luz
	if(primitiva->planoContraLuz(camara, luz, pInterseccion)) {
		// Si está contra la luz -> negro.
		return RGB(0);
	}

	Vector distanciaLuz = distancia(luz.centro, pInterseccion);
	float modDistancia = distanciaLuz.modulo();
	float t;

	// Comprobar si alguna primitiva le da sombra
	for (Primitiva* p : primitivas){
		if(p->intersecta(Rayo(luz.centro, -distanciaLuz), t)
		&& (1 - t) * modDistancia > 1e-6
		&& (p != primitiva || distancia(pInterseccion, luz.centro - t * (distanciaLuz)).modulo() > 1e-4)) {
			return RGB(0);
		}
	}

	// Esta a la luz -> calcular color
	RGB Li = luz.potencia / (pow(modDistancia, 2));
	float cosine = abs(escalar(primitiva->obtenerNormal(pInterseccion), distanciaLuz.normalizar()));

	BRDF brdf(primitiva->obtenerMaterial(), primitiva->obtenerNormal(pInterseccion));
	return Li * brdf.getFr(efecto, direccionRayo, pInterseccion) * cosine * colorDisipado;

}

void renderizarSeccion(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, int minX, int maxX,	int minY, int maxY,
	vector<RGB>& valoresPixeles){
/*
	Vector modL = camara.l.normalizar();					// L and U normalized vectors.
	Vector modU = camara.u.normalizar();
	Vector sightOrigin = camara.f + camara.l + camara.u;	// Point located at the top left corner of the image.
	GeneradorAleatorios rand(0, 1);							// Random number generator.
	RGB colorPixel, rayColor;							// Total color for one pixel / ray.
	Rayo ray;											// Current ray.
	Direccion rayDirection;								// Direction of ray.
	float t, minT;										// Distance to the closest figure.
	Punto hit;											// Point on whith the ray hits.
	Primitiva* primitiva;								// Closest figure to the camara.
	RGB scatter;										// Color of the light scattered by the figure.
	Efecto ph;										// Phenomenom of a interaction.

	// For each pixel in the section.
	for (int i = minX; i < maxX; i++)
		for (int j = minY; j < maxY; j++) {

			colorPixel = RGB();

			// For each ray que pasa por este pixel.
			for (int k = 0; k < rpp; k++) {

				// Ray color starts being 0.
				rayColor = RGB();

				// At first, scatter doesn't affect the total color.
				scatter = RGB(1);

				// Get the direction of the ray.
				rayDirection = Direccion(sightOrigin - (j+rand.get())*camara.basePixel*modL
						- (i+rand.get())*camara.alturaPixel*modU);
				// Build the ray using the camara's origin and the direction.
				ray = Rayo(camara.o, rayDirection);

				// While the ray hits a figure and it's not absorbed.
				while (true) {

					// Get the first figure that intersects the ray, and the
					// point of the intersection.
					minT = 1e6;
					primitiva = nullptr;
					for (Primitiva* p : primitivas)
						if (p->intersecta(ray, t) && t < minT) {
							minT = t;
							primitiva = p;
					}
					if (primitiva == nullptr) break;
					hit = ray.obtenerOrigen() + minT*ray.obtenerDireccion();

					// Get the phenomenom of the interaction.
					BRDF brdf = BRDF(primitiva->obtenerMaterial(), primitiva->obtenerNormal(hit));
					ph = brdf.obtenerEfecto();

					// ABSORPTION: finish.
					if (ph == ABSORCION)
							break;

					// LIGHT: add the light color and finish.
					else if (ph == LUZ) {
						rayColor += brdf.kl * scatter;
						break;
					} 

					// REFLECTION: update scatter and get new ray.
					else if (ph == REFLEXION)
							scatter *= brdf.getFr(ph, rayDirection, hit);

					// REFRACTION: update scatter and get new ray.
					else if (ph == REFRACCION)
							scatter *= brdf.getFr(ph, rayDirection, hit);

					// DIFFUSE: add contribution, update scatter and get new ray.
					else {
						for (int i = 0; i < luces.size(); ++i)
								rayColor += colorInterseccion(primitiva, primitivas,
												hit, luces[i], camara,
												scatter, ph, rayDirection);
						scatter *= M_PI * brdf.getFr(ph, rayDirection, hit);
					}

					// Update the ray.
					hit = hit + 1e-4 * rayDirection;
					ray = Rayo(hit, rayDirection);

				}

				// If valid, add the ray color to the pixel color.
				if (isnan(rayColor[0]) || isnan(rayColor[1]) || isnan(rayColor[2]))
						k--;
				else
						colorPixel += rayColor;
			}

			// Store the pixel color.
			valoresPixeles[i*camara.base + j] = colorPixel;
	}
*/
	
	Direccion modL = camara.l.normalizar();				// Vector L de camara normalizado
	Direccion modU = camara.u.normalizar();				// Vector U de camara normalizado
	Punto pIzqArriba = camara.f + camara.l + camara.u;	// Punto arriba a la izquierda de la imagen
	GeneradorAleatorios rand(0, 1);						// Generador numero aleatorio
	RGB colorPixel;										// Color del pixel
	RGB colorRayo;										// Color del rayo
	Rayo rayoCamara;									// Rayo actual desde la camara
	Direccion direccionRayo;							// Direccion del rayo actual
	float t, minT;										// Distancia a la primitiva mas cercana
	Punto pInter;										// Punto de interseccion del rayo con primitiva
	Primitiva* primitiva;								// Primitiva intersectada
	RGB colorEmitido;									// Color emitido por la primitiva
	Efecto efecto;											// Efecto de interaccion


	// Recorrer todos los pixeles de la seccion
	for (int i = minX; i < maxX; i++)
		for (int j = minY; j < maxY; j++) {

			// Establecer color inicial del pixel a negro
			colorPixel = RGB();

			// Para cada rayo lanzado a este pixel, ie, N_RPP
			for (int k = 0; k < rpp; k++) {

				// Estavlecer color del rayo a negro
				colorRayo = RGB();

				// Establecer color de emision a blanco
				colorEmitido = RGB(1);

				// antialising -> vector randomizado
				direccionRayo = Direccion(pIzqArriba
					- (j + rand.get()) * camara.basePixel * modL
					- (i + rand.get()) * camara.alturaPixel * modU);
				
				// Crear el rayo desde la camara
				rayoCamara = Rayo(camara.o, direccionRayo);

				// Mientras el rayo de a una primitiva y no sea absorbido
				bool terminar = false;
				int nRebotes = 0;
				//while (!terminar || nRebotes < N_REBOTES) {
				while (nRebotes < N_REBOTES) {

					// Obtener la figura y el punto de interseccion
					minT = 1e6;
					primitiva = nullptr;
					for (Primitiva* p : primitivas){
						if (p->intersecta(rayoCamara, t) && t < minT) {
							// Si intersecta y tiene menor distancia guardamos el dato
							minT = t;
							primitiva = p;
						}
					}

					if (primitiva == nullptr) {
						// Si no ha intersectado con ninguna primitiva
						break;
					} 

					pInter = rayoCamara.obtenerOrigen() + minT*rayoCamara.obtenerDireccion();

					// Obtener el efecto provocado por la primitiva
					BRDF brdf = BRDF(primitiva->obtenerMaterial(), primitiva->obtenerNormal(pInter));
					efecto = brdf.obtenerEfecto();

					switch(efecto) {
						case ABSORCION:
							terminar = true;
							break;
						case LUZ:
							colorRayo += brdf.kl * colorEmitido;
							terminar = true;
							break;
						case REFLEXION:
							colorEmitido *= brdf.getFr(efecto, direccionRayo, pInter);
							break;
						case REFRACCION:
							colorEmitido *= brdf.getFr(efecto, direccionRayo, pInter);
							break;
						default:
							for (int i = 0; i < luces.size(); ++i){
								colorRayo += colorInterseccion(primitiva, primitivas,
									pInter, luces[i], camara,
									colorEmitido, efecto, direccionRayo);
							}
							colorEmitido *= M_PI * brdf.getFr(efecto, direccionRayo, pInter);
							break;
					}
					
					// Update the ray.
					pInter = pInter + 1e-4 * direccionRayo;
					rayoCamara = Rayo(pInter, direccionRayo);

					nRebotes++;
				}

				// If valid, add the ray color to the pixel color.
				if (isnan(colorRayo[0]) || isnan(colorRayo[1]) || isnan(colorRayo[2])){
					k--;
				}
				else{
					colorPixel += colorRayo;
				}
			}

			// Store the pixel color.
			valoresPixeles[i*camara.base + j] = colorPixel;
	}

}


void pathTracing(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, int hilos, string file){	

	// Valores de la camara
	int altura = camara.altura;
	int base = camara.base;
	int baseAltura = base * altura;
	
	// Vector con los pixeles calculados de la imagen
	vector<RGB> pixelesImagen(baseAltura);

	// Reparto del trabajo entre los hilos para que cada uno capture una seccion
	DivisorSecciones secciones(base, altura, hilos);

	vector<thread> arrayHilos(hilos);
	for (int t = 0; t < hilos; t++) {
		arrayHilos[t] = thread([&camara, &primitivas, &luces, rpp, &secciones, &pixelesImagen](){
			int minX, maxX, minY, maxY;
			// While there are sections left to capture, get one and capture it.
			while (secciones.obtenerSeccion(minX, maxX, minY, maxY)) {
				renderizarSeccion(camara, primitivas, luces, rpp, minX, maxX, minY, maxY,
				pixelesImagen);
			}
		});
	}

	// Esperar a que los hilos terminen de trabajar y cerrarlos
	for (int t = 0; t < hilos; t++){
		arrayHilos[t].join();	
	} 

	// Encontrar el valor maximo
	float max = 0;
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < base; j++) {
			RGB colorPixel = pixelesImagen[i * altura + j];
			if (colorPixel[0] > max) {
				max = colorPixel[0];
			}
			if (colorPixel[1] > max) {
				max = colorPixel[1];
			}
			if (colorPixel[2] > max) {
				max = colorPixel[2];
			}
		}
	}

	// Obtener el maximo total dados los rayos por pixel y normalizar
	float nuevoMax = max * 255 / rpp;

	// Normalizar los valores de los pixeles
	vector<RGB> pixeles(baseAltura);
	for(int i = 0; i < baseAltura; i++)
		pixeles[i] = pixelesImagen[i] * 255 / rpp;

	// Creacion y escritura de la imagen
	ImagenPPM img(base, altura, nuevoMax, pixeles);
	img.escribirImagen(file);
}

