#include "pathTracing.hpp"


// Returns the color of the ont pInter.

RGB getColorOfHit (const Primitiva* figure, list<Primitiva*> primitivas, const Punto& pInter,
					 Luz& lightSource, const Camara& camara, RGB& colorDisipado,
					 Efecto efecto, Direccion direccionCamara) {

	// Check if the plane is against the light.
	if (figure->planoContraLuz(camara, lightSource, pInter))
			return RGB(0);

	// Check if the point is in shadow.
	Vector distanceToLight = distancia(lightSource.centro, pInter);
	float modDistanceToLight = distanceToLight.modulo();
	float t;
	for (Primitiva* fig : primitivas)
			if (fig->intersecta(Rayo(lightSource.centro, -distanceToLight), t)
			&&	(1 - t) * modDistanceToLight > 1e-6
			&&	(  fig != figure
				|| distancia(pInter, lightSource.centro - t*(distanceToLight)).modulo() > 1e-4))
						return RGB(0);

	// Calculate the color of the pInter.
	RGB Li = lightSource.potencia / (modDistanceToLight*modDistanceToLight);
	float cosine = abs(escalar(figure->obtenerNormal(pInter), distanceToLight.normalizar()));
	BRDF brdf(figure->obtenerMaterial(), figure->obtenerNormal(pInter));
	return Li * brdf.getFr(efecto, direccionCamara, pInter) * cosine * colorDisipado;

}


// Captures a section of the image.
void captureSection(Camara& camara, list<Primitiva*> primitivas, vector<Luz> luces,
					int rpp, int minX, int maxX, int minY, int maxY,
					vector<RGB>& valoresPixeles) {
	
	Vector modL = camara.l.normalizar(); // Vector L de camara normalizado
	Vector modU = camara.u.normalizar(); // Vector U de camara normalizado
	Vector esquinaSupIzq = camara.f + camara.l + camara.u;	
	randomGenerator rand(0, 1);	// Generador de numeros aleatorios entre 0 y 1
	RGB colorPixel, colorRayo; // Color del pixel y del rayo
	Rayo rayoCamara; // Rayo de la camara al punto a evaluar
	Direccion direccionCamara; // Direccion del rayo de la camara al punto a evaluar
	float t, minT; // Distancia menor a la que intersecta el rayo
	Punto pInter; // Punto de interseccion del rayo
	Primitiva* primitiva; // Primitiva con la que intersecta el rayo
	RGB colorDisipado; // Color disipado por la primitiva
	Efecto efecto;	// Efecto de la interseccion
	
	// Para cada pixel en la seccion [minX, maxX]x[minY, maxY]
	for (int i = minY; i < maxY; i++)
		for (int j = minX; j < maxX; j++) {

			colorPixel = RGB();

			// Para cada rayo lanzado por pixel
			for (int k = 0; k < rpp; k++) {

				// Rayo color starts being 0.
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

					// Get the phenomenom of the interaction.
					BRDF brdf(primitiva->obtenerMaterial(), primitiva->obtenerNormal(pInter));
					efecto = brdf.obtenerEfecto();

					bool terminar = false;
					switch(efecto) {
						case ABSORCION:
							terminar = true;
							break;
						case LUZ:
							colorRayo += primitiva->obtenerMaterial().kl * colorDisipado;
							terminar = true;
							break;
						case REFLEXION:
							colorDisipado *= brdf.getFr(efecto, direccionCamara, pInter);
							break;
						case REFRACCION:
							colorDisipado *= brdf.getFr(efecto, direccionCamara, pInter);
							break;
						default:
							for (int i = 0; i < luces.size(); ++i) {
									colorRayo += getColorOfHit(primitiva, primitivas,
													pInter, luces[i], camara,
													colorDisipado, efecto, direccionCamara);
							}
							colorDisipado *= M_PI * brdf.getFr(efecto, direccionCamara, pInter);
							break;
					}

					if(terminar) { break; }

/*
					// ABSORPTION: finish.
					if (efecto == ABSORCION) {
						break;
					}

					// LIGHT: add the light color and finish.
					else if (efecto == LUZ) {
						colorRayo += primitiva->obtenerMaterial().kl * colorDisipado;
						break;
					} 

					// REFLECTION: update colorDisipado and get new rayoCamara.
					else if (efecto == REFLEXION){
							colorDisipado *= brdf.getFr(efecto, direccionCamara, pInter);
					}

					// REFRACTION: update colorDisipado and get new rayoCamara.
					else if (efecto == REFRACCION)
							colorDisipado *= brdf.getFr(efecto, direccionCamara, pInter);

					// DIFFUSE: add contribution, update colorDisipado and get new rayoCamara.
					else {
						for (int i = 0; i < luces.size(); ++i)
								colorRayo += getColorOfHit(primitiva, primitivas,
												pInter, luces[i], camara,
												colorDisipado, efecto, direccionCamara);
						colorDisipado *= M_PI * brdf.getFr(efecto, direccionCamara, pInter);
					}
*/

					// Update the rayoCamara.
					pInter = pInter + 1e-4 * direccionCamara;
					rayoCamara = Rayo(pInter, direccionCamara);

				}

				// If valid, add the rayoCamara color to the pixel color.
				if (isnan(colorRayo[0]) || isnan(colorRayo[1]) || isnan(colorRayo[2]))
						k--;
				else
						colorPixel += colorRayo;
			}

			// Store the pixel color.
			valoresPixeles[j*camara.altura + i] = colorPixel;
	}
}

void captureSlave (Camara& camara, list<Primitiva*> primitivas, vector<Luz> luces,
				int rpp, SpaceSectioner& tiles, vector<RGB>& valoresPixeles) {

	int minX, maxX, minY, maxY;
	// While there are sections left to capture, get one and capture it.
	while (tiles.getSection(minX, maxX, minY, maxY))
		captureSection(camara, primitivas, luces, rpp,
				minX, maxX, minY, maxY, valoresPixeles);

}

// Capture the scene from the camara's point of view.
void pathTracing(Camara& camara, list<Primitiva*> primitivas, vector<Luz> luces,
				int rpp, int threads, string fileName) {

	// Open the file to write the image.
	ofstream output(fileName);
	if (!output.is_open()) {
		cerr << "Error opening output file \"" << fileName << "\"" << endl;
		exit(1);
	}

	// Write the header of the PPM file.
	output << "P3" << endl;
	output << camara.base << " " << camara.altura << endl;
	
	// Structure to store the final image.
	vector<RGB> finalImage(camara.altura * camara.base);

	// Divide the image into sections.
	SpaceSectioner tiles(camara.base, camara.altura, threads);

	// Divide the work between the threads. Each one will be capturing a section
	// of the image while there are sections left.
	vector<thread> threadsArray(threads);
	for (int t = 0; t < threads; t++) {
		int minH = t * camara.altura / threads;
		int maxH = (t + 1) * camara.altura / threads;
		threadsArray[t] = thread(&captureSlave, ref(camara), ref(primitivas),
				ref(luces), rpp, ref(tiles), ref(finalImage));
	}

	// Wait for all threads to finish.
	for (int t = 0; t < threads; t++) threadsArray[t].join();

	// Find the maximum value of the pixels.
	float max = 0;
	for (int i = 0; i < camara.altura; i++) {
		for (int j = 0; j < camara.base; j++) {
			RGB colorPixel = finalImage[i*camara.base + j];
			if (colorPixel[0] > max) max = colorPixel[0];
			if (colorPixel[1] > max) max = colorPixel[1];
			if (colorPixel[2] > max) max = colorPixel[2];
		}
	}
	output << max * 255 / rpp << endl;

	// Write the final image into the file.
	for (int i = 0; i < camara.altura; i++) {
		for (int j = 0; j < camara.base; j++) {
			RGB colorPixel = finalImage[j*camara.altura + i];
			output << colorPixel*255/rpp << "    ";
		}
		output << endl;
	}
	output.close();

}


