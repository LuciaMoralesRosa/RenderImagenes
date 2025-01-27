#include "pathTracing.hpp"
#include "../escenas/escena1.hpp"


const int N_HILOS = 16;
const int N_RPP = 512;


    //g++ pt.cpp -o3 -o main
    // ./main sceneFinal2.objx nuevaEscena.ppm
    // ./main nuevaEscena.ppm

/*
g++ pt.cpp ../aleatorios/random.cpp ../aleatorios/randomBRDF.cpp ../color/rgb.cpp ../geometria/matriz.cpp ../geometria/vector.cpp ../geometria/direccion.cpp ../geometria/punto.cpp ../geometria/rayo.cpp ../escena/camara.cpp pathTracing.cpp -o main
*/

int main(int argc, char* argv[]) {

	// Check the number of arguments.
	if (argc != 2) {
		//cerr << "Parametros incorrectos - Uso: " << argv[0] << " <output_file>" << endl;
		cerr << "Parametros incorrectos - Uso: ./main <fichero_salida>" << endl;
		return 1;
	}

	Camara camara;
    list<Primitiva*> primitivas = {};
    vector<Luz> luces = {};

	// Creacion de la escena
    Escena1 escena = Escena1();
    escena.crearEscena(camara, primitivas, luces);

	// Renderizado de la escena
	unsigned t0 = clock();
    pathTracing(camara, primitivas, luces, N_RPP, N_HILOS, argv[1]);
    unsigned t1 = clock();
	
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Tiempo de renderizado: " << time << " s" << endl;

}