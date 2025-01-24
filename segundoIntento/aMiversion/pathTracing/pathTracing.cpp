#include "pathTracing.hpp"


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



void capturarSeccion(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, int minX, int maxX,	int minY, int maxY,
	vector<RGB>& valoresPixeles){

	Vector modL = camara.l.normalizar();					// L and U normalized vectors.
	Vector modU = camara.u.normalizar();
	Vector sightOrigin = camara.f + camara.l + camara.u;	// Point located at the top left corner of the image.
	GeneradorAleatorios rand(0, 1);							// Random number generator.
	RGB pxColor, rayColor;							// Total color for one pixel / ray.
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

			pxColor = RGB();

			// For each ray.
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
						pxColor += rayColor;
			}

			// Store the pixel color.
			valoresPixeles[i*camara.base + j] = pxColor;
	}

}



void capturarTrabajador(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, SpaceSectioner& tiles,
	vector<RGB>& valoresPixeles){

	int minX, maxX, minY, maxY;
	// While there are sections left to capture, get one and capture it.
	while (tiles.getSection(minX, maxX, minY, maxY)) {
		capturarSeccion(camara, primitivas, luces, rpp,	minX, maxX, minY, maxY,
		valoresPixeles);
	}
}



void pathTracing(Camara& camara, list<Primitiva*> primitivas,
	vector<Luz> luces, int rpp, int threads, string fileName){

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
	SpaceSectioner tiles(camara.base, camara.altura, threads, threads);

	// Divide the work between the threads. Each one will be capturing a section
	// of the image while there are sections left.
	vector<thread> threadsArray(threads);
	for (int t = 0; t < threads; t++) {
		int minH = t * camara.altura / threads;
		int maxH = (t + 1) * camara.altura / threads;
		threadsArray[t] = thread(&capturarTrabajador, ref(camara), ref(primitivas),
				ref(luces), rpp, ref(tiles), ref(finalImage));
	}

	// Wait for all threads to finish.
	for (int t = 0; t < threads; t++) threadsArray[t].join();

	// Find the maximum value of the pixels.
	float max = 0;
	for (int i = 0; i < camara.altura; i++) {
		for (int j = 0; j < camara.base; j++) {
			RGB pxColor = finalImage[i*camara.altura + j];
			if (pxColor[0] > max) max = pxColor[0];
			if (pxColor[1] > max) max = pxColor[1];
			if (pxColor[2] > max) max = pxColor[2];
		}
	}
	output << max * 255 / rpp << endl;

	// Write the final image into the file.
	for (int i = 0; i < camara.altura; i++) {
		for (int j = 0; j < camara.base; j++) {
			RGB pxColor = finalImage[i*camara.base + j];
			output << pxColor*255/rpp << "    ";
		}
		output << endl;
	}
	output.close();

}

