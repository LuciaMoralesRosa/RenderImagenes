// Main function.
#include "pathTracing.cpp"

void inicializarManualmente(Camera& camera, list<Figure*>& listFigures,
				vector<LightSource>& lightSources, int& raysPerPixel,
				int& threads, int& photons, float& radius, int& neighbors) {
    // Camera, list of figures and light sources.
	camera = Camera(Point(0,0,-3.5), Direction(-1,0,0), Direction(0,1,0), Direction(0,0,3), 256, 256);
    
    listFigures.push_back(new Plane(0, Direction(1,0,0), 1, Color(0.8, 0, 0), Color(0, 0, 0), Color(0, 0, 0), Color(0, 0, 0), 0));
    listFigures.push_back(new Plane(1, Direction(-1,0,0), 1, Color(0.0, 0.8, 0.0), Color(0, 0, 0), Color(0, 0, 0), Color(0, 0, 0), 0)); 
    listFigures.push_back(new Plane(2, Direction(0,1,0), 1, Color(0.8, 0.8, 0.8), Color(0, 0, 0), Color(0, 0, 0), Color(0, 0, 0), 0));    
    listFigures.push_back(new Plane(4, Direction(0,0,-1), 1, Color(0.8, 0.8, 0.8), Color(0, 0, 0), Color(0, 0, 0), Color(0, 0, 0), 0));
    listFigures.push_back(new Plane(3, Direction(0,-1,0), 1, Color(0, 0, 0), Color(0, 0, 0), Color(0, 0, 0), Color(0.99, 0.99, 0.99), 0));

    listFigures.push_back(new Sphere(5, Point(-0.5, -0.7, 0.25), 0.3, Color(0.11, 0.41, 0.375), Color(0.4, 0.4, 0.4), Color(0, 0, 0), Color(0, 0, 0), 0));
    listFigures.push_back(new Sphere(6, Point(0.5, -0.7, -0.25), 0.3, Color(0,0,0), Color(0.4, 0.4, 0.4), Color(0.4, 0.4, 0.4), Color(0, 0, 0), 1.5));
    
    lightSources.push_back(LightSource(Point(0, 0.5, 0), Color(0.99, 0.99, 0.99)));

	raysPerPixel = 512;
    threads = 16;
    photons = 100000;
}


int main(int argc, char* argv[]) {

	// Check the number of arguments.
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <scene_file> <output_file>" << endl;
		return 1;
	}

	Camera camera;
    list<Figure*> listFigures = {};
    vector<LightSource> lightSources = {};
    int raysPerPixel, threads, photons, neighbors;
	float radius;

	// Populate the camera, lights and figures.
	unsigned t0 = clock();
	//bool popDone = populateList (camera, listFigures, lightSources, raysPerPixel, threads, photons, radius, neighbors, argv[1], false);
    
    //inicializarManualmente(camera, listFigures, lightSources, raysPerPixel, threads, photons, radius, neighbors);
    bool nuevaPoblacion = newPopulate(camera, listFigures, lightSources, raysPerPixel, threads, photons, radius, neighbors, argv[1], false);
    
    unsigned t1 = clock();

	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "File reading time: " << time << " s" << endl;

	// Check if the population was successful.
	//if (!popDone) return 1;

	// Capture the scene and store it at the specified file.
	t0 = clock();
	pathTracing(camera, listFigures, lightSources, raysPerPixel, threads, argv[2]);
	t1 = clock();

	time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Image processing time: " << time << " s" << endl;

}