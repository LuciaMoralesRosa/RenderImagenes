#include "pathTracing.hpp"

int main(int argc, char* argv[]) {

    //g++ pt.cpp -o3 -o main
    // ./main sceneFinal2.objx nuevaEscena.ppm
    // ./main nuevaEscena.ppm


/*
g++ pt.cpp ../aleatorios/random.cpp ../aleatorios/randomBRDF.cpp ../color/rgb.cpp ../geometria/matriz.cpp ../geometria/vector.cpp ../geometria/direccion.cpp ../geometria/punto.cpp ../geometria/rayo.cpp ../escena/camara.cpp pathTracing.cpp -o main
*/

	// Check the number of arguments.
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <scene_file> <output_file>" << endl;
		return 1;
	}

	Camara camera;
    list<Primitiva*> listFigures = {};
    vector<Luz> lightSources = {};
    int raysPerPixel, threads, photons, neighbors;
	float radius;

	// Populate the camera, lights and figures.
	unsigned t0 = clock();
    
    camera = Camara(Punto(0,0,-3.5), Direccion(-1,0,0), Direccion(0,1,0), Direccion(0,0,3), 256, 256);
    
    Material m1(RGB(0.8, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), 0);
    Material m2(RGB(0.0, 0.8, 0.0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), 0);
    Material m3(RGB(0.8, 0.8, 0.8), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), 0);
    Material m4(RGB(0.8, 0.8, 0.8), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), 0);
    Material m5(RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0.99, 0.99, 0.99), 0);

    Material m6(RGB(0.11, 0.41, 0.375), RGB(0.4, 0.4, 0.4), RGB(0, 0, 0), RGB(0, 0, 0), 0);
    Material m7(RGB(0,0,0), RGB(0.4, 0.4, 0.4), RGB(0.4, 0.4, 0.4), RGB(0, 0, 0), 1.5);

    listFigures.push_back(new Plano(0, Direccion(1,0,0), 1, m1));
    listFigures.push_back(new Plano(1, Direccion(-1,0,0), 1, m2)); 
    listFigures.push_back(new Plano(2, Direccion(0,1,0), 1, m3));    
    listFigures.push_back(new Plano(4, Direccion(0,0,-1), 1, m4));
    listFigures.push_back(new Plano(3, Direccion(0,-1,0), 1, m5));

    listFigures.push_back(new Esfera(5, Punto(-0.5, -0.7, 0.25), 0.3, m6));
    listFigures.push_back(new Esfera(6, Punto(0.5, -0.7, -0.25), 0.3, m7));
    
    lightSources.push_back(Luz(Punto(0, 0.5, 0), RGB(0.99, 0.99, 0.99)));

	raysPerPixel = 512;
    threads = 16;
    photons = 100000;
        
    unsigned t1 = clock();

	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "File reading time: " << time << " s" << endl;

	// Check if the population was successful.
	//if (!popDone) return 1;

	// Capture the scene and store it at the specified file.
	t0 = clock();
	pathTracing(camera, listFigures, lightSources, raysPerPixel, threads, argv[1]);
	t1 = clock();

	time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Image processing time: " << time << " s" << endl;

}