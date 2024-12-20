#include <iostream>
#include <string>
#include <thread>
#include <tuple>
#include <chrono>
#include <functional>

#include "../color/RGB.hpp"
#include "../geometria/Direccion.hpp"
#include "../geometria/Punto.hpp"
#include "../imagen/imagenPPM.hpp"
#include "../imagen/tonemapping.hpp"
#include "../primitivas/interseccion.hpp"
#include "../primitivas/rayo.hpp"
#include "../primitivas/esfera.hpp"
#include "../primitivas/plano.hpp"
#include "../escena/escena.hpp"
#include "../escena/escenas.hpp"
#include "../pathTracing/pathtracer.hpp"

using namespace std;


/* Compilacion:
g++ testing.cpp ../varios/misc.cpp ../color/RGB.cpp ../imagen/imagenPPM.cpp ../imagen/tonemapping.cpp ../geometria/vector.cpp ../geometria/Direccion.cpp ../geometria/Punto.cpp ../geometria/matriz4x4Nueva.cpp ../geometria/coordenadas.cpp ../primitivas/rayo.cpp ../primitivas/esfera.cpp ../primitivas/rectangulo.cpp ../primitivas/cubo.cpp ../primitivas/plano.cpp ../escena/luz.cpp ../escena/camara.cpp ../escena/escena.cpp ../materiales/BRDFSimple.cpp ../materiales/emisor.cpp ../pathTracing/pathtracer.cpp -o testing

*/

/*
//---------------------------- TONE MAPPING COLOR ----------------------------//
void test_ImagenTonemappingColor() {
    cout << "Inicio del test: test_ImagenTonemappingColor ---------------------" << endl;

    string imagenPrueba = "../testsImagenes/test_ImagenesEjemplo/forest_path.ppm";
    ImagenPPM imagenTest(imagenPrueba);

    ImagenPPM imagenClamp = tonemapping::clamp(imagenTest);
    ImagenPPM imagenEqualize = tonemapping::equalize(imagenTest);
    ImagenPPM imagenEqualizeClamp200 = tonemapping::equalizeClamp(imagenTest, 200);
    ImagenPPM imagenEqualizeClamp50 = tonemapping::equalizeClamp(imagenTest, 50);
    ImagenPPM imagenGamma = tonemapping::gamma(imagenTest, 2.2);
    ImagenPPM imagenGammaClamp = tonemapping::gammaClamp(imagenTest, 2.2);

    vector<ImagenPPM> imagenes = {imagenClamp, imagenEqualize, imagenEqualizeClamp200, imagenEqualizeClamp50, imagenGamma, imagenGammaClamp};
    for(int i = 0; i < imagenes.size(); i++) {
        string nombre = "ImagenPrueba_" + to_string(i) + ".ppm";
        imagenes[i].escrituraPPM(nombre);
    }
    cout << "Finalizacion del test: test_ImagenTonemappingColor ----------------" << endl;
}
//---------------------------- TONE MAPPING COLOR ----------------------------//


//------------------------------ CIELO DEGRADADO -----------------------------//
RGB ray_color(const Rayo& r) {
    Direccion unit_direction = normalizar(r.getDireccion());
    auto a = 0.5 * (unit_direction.getY() + 1.0);
    return RGB(1.0, 1.0, 1.0) * (1.0 - a)+ RGB(0.5, 0.7, 1.0) * a;
}

void write_color(std::ostream& out, const RGB& pixel_color) {
    auto r = pixel_color.getR();
    auto g = pixel_color.getG();
    auto b = pixel_color.getB();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    //out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

void test_cieloDegradado() {
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = Punto(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = Direccion(viewport_width, 0, 0);
    auto viewport_v = Direccion(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - Punto(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

    // Render
    ImagenPPM imagen(image_width, image_height);
    vector<vector<RGB>> pixeles;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
            auto ray_direction = pixel_center - (camera_center - Punto(0,0,0));
            Rayo r(camera_center, ray_direction);

            RGB pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
            imagen.setPixelMatriz(j, i, pixel_color);
        }
    }
    imagen.escrituraPPM("imagenCielo.ppm");
}
//------------------------------ CIELO DEGRADADO -----------------------------//

//------------------------------- CREAR ESFERA -------------------------------//
bool hit_sphere(const Punto& center, double radius, const Rayo& r) {
    Direccion oc = center - r.getOrigen();
    auto a = productoEscalar(r.getDireccion(), r.getDireccion());
    auto b = -2.0 * productoEscalar(r.getDireccion(), oc);
    auto c = productoEscalar(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

RGB ray_color_esfera(const Rayo& r) {
    if (hit_sphere(Punto(0,0,-1), 0.5, r))
        return RGB(1, 0, 0);

    Direccion unit_direction = normalizar(r.getDireccion());
    auto a = 0.5*(unit_direction.getY() + 1.0);
    return RGB(1.0, 1.0, 1.0) * (1.0-a) + RGB(0.5, 0.7, 1.0)*a;
}

void test_crearEsfera() {
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = Punto(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = Direccion(viewport_width, 0, 0);
    auto viewport_v = Direccion(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - Punto(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

    // Render
    ImagenPPM imagen(image_width, image_height);
    vector<vector<RGB>> pixeles;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
            auto ray_direction = pixel_center - (camera_center - Punto(0,0,0));
            Rayo r(camera_center, ray_direction);

            RGB pixel_color = ray_color_esfera(r);
            write_color(std::cout, pixel_color);
            imagen.setPixelMatriz(j, i, pixel_color);
        }
    }
    imagen.escrituraPPM("imagenEsferaCielo.ppm");
}
//------------------------------- CREAR ESFERA -------------------------------//


//------------------------------ CREAR ESFERA 2 ------------------------------//
RGB ray_color_esfera_2(const Rayo& r) {
    Interseccion inter;
    std::shared_ptr<BRDF> brdf_ptr = std::make_shared<BRDF>();
    Punto centro(0,0,-1);
    Esfera esfera(centro, 0.5, brdf_ptr);
    if (esfera.interseccion(r).intersecta)
        return RGB(1, 0, 0);

    Direccion unit_direction = normalizar(r.getDireccion());
    auto a = 0.5*(unit_direction.getY() + 1.0);
    return RGB(1.0, 1.0, 1.0) * (1.0-a) + RGB(0.5, 0.7, 1.0)*a;
}

void test_crearEsfera_2() {
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = Punto(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = Direccion(viewport_width, 0, 0);
    auto viewport_v = Direccion(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - Punto(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

    // Render
    ImagenPPM imagen(image_width, image_height);
    vector<vector<RGB>> pixeles;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
            auto ray_direction = pixel_center - (camera_center - Punto(0,0,0));
            Rayo r(camera_center, ray_direction);

            RGB pixel_color = ray_color_esfera(r);
            write_color(std::cout, pixel_color);
            imagen.setPixelMatriz(j, i, pixel_color);
        }
    }
    imagen.escrituraPPM("imagenEsferaCielo2.ppm");
}
//------------------------------ CREAR ESFERA 2 ------------------------------//

//-------------------------- CREAR ESFERA DEGRADADA --------------------------//
RGB ray_color_esfera_degradado(const Rayo& r) {
    Interseccion inter;
    std::shared_ptr<BRDF> brdf_ptr = std::make_shared<BRDF>();
    Punto centro(0,0,-1);
    Esfera esfera(centro, 0.5, brdf_ptr);
    inter = esfera.interseccion(r);
    if (inter.intersecta){
        if(inter.distancia > 0.0) {
            Direccion D = normalizar(r.evaluar(inter.distancia) - Punto(0,0,-1));
            return RGB(D.getX()+1, D.getY()+1, D.getZ()+1) * 0.5;
        }
    }

    Direccion unit_direction = normalizar(r.getDireccion());
    auto a = 0.5*(unit_direction.getY() + 1.0);
    return RGB(1.0, 1.0, 1.0) * (1.0-a) + RGB(0.5, 0.7, 1.0)*a;
}

void test_crearEsfera_degradado() {
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = Punto(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = Direccion(viewport_width, 0, 0);
    auto viewport_v = Direccion(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - Punto(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

    // Render
    ImagenPPM imagen(image_width, image_height);
    vector<vector<RGB>> pixeles;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
            auto ray_direction = pixel_center - (camera_center - Punto(0,0,0));
            Rayo r(camera_center, ray_direction);

            RGB pixel_color = ray_color_esfera_degradado(r);
            write_color(std::cout, pixel_color);
            imagen.setPixelMatriz(j, i, pixel_color);
        }
    }
    imagen.escrituraPPM("imagenEsferaDegradada.ppm");
}
//------------------------------ CREAR ESFERA 2 ------------------------------//
*/
//---------------------------- PATH TRACING ESFERA ---------------------------//
void test_pathTracer() {
    ValoresEscena valores;
    valores.width = 256;
    valores.height = 256;
    valores.factorAntialising = 64;
    valores.hilos = thread::hardware_concurrency();
    valores.rebotes = 10;

    string fichero = "testPathtracer.ppm";

    Escena escena = cornellBox_Difusa(valores);

    ImagenPPM imagen(valores.width, valores.height);

    auto s = measureTime<std::chrono::milliseconds>(
        [&]()
        {
            imagen = escena.dibujarEscena(
                [&](const Escena &sc) -> ImagenPPM
                {
                    return pathTracing(escena);
                });
        }
    );

    cout << "Listo (" << (double)s / 1000.0 << " s)." << endl;

    imagen.setValorMax(imagen.getNumeroMayor());

    ImagenPPM gamma = tonemapping::gamma(imagen, 2.2);
    cout << "Guardando imagen en " << fichero << endl;

    gamma.setValorMax(gamma.getNumeroMayor());
    gamma.escrituraPPM(fichero);
}


//---------------------------- PATH TRACING ESFERA ---------------------------//


//----------------------------------------------------------------------------//
//------------------------------- CODIGO MAIN --------------------------------//
//----------------------------------------------------------------------------//
int main(){

    cout << "Elige el test a ejecutar:" << endl;
    cout << "\t 1 - test_ImagenTonemappingColor" << endl;
    cout << "\t 2 - test_cieloDegradado" << endl;
    cout << "\t 3 - test_crearEsfera" << endl;
    cout << "\t 4 - test_crearEsfera_2 (Con interseccion)" << endl;
    cout << "\t 5 - test_crearEsfera_degradada" << endl;
    cout << "\t 6 - test_pathTracer" << endl;


    int eleccion;
    cin >> eleccion;

    switch (eleccion){
    /*
    case 1:
        test_ImagenTonemappingColor();
        break;
    case 2:
        test_cieloDegradado();
        break;
    case 3:
        test_crearEsfera();
        break;
    case 4:
        test_crearEsfera_2();
        break;
    case 5:
        test_crearEsfera_degradado();
        break;
    */
    case 6:
        test_pathTracer();
        break;
    default:
        break;
    }

}