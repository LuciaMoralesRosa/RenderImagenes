#include "imagenPPM.hpp"

ImagenPPM::ImagenPPM(const string& fichero) {
    ImagenPPM imagen(lecturaPPM(fichero));
    base = imagen.getBase();
    altura = imagen.getAltura();
    valorMax = imagen.getValorMax();
    matrizPixeles = imagen.getMatrizPixeles();
}


void ImagenPPM::escrituraPPM(const string& fichero, unsigned int res) const {
    ofstream out(fichero);

    if (!out.is_open() ) {
        throw runtime_error("No se puede escribir en " + fichero);
    }

    out << "P3" << endl;
    out << "#MAX=" << valorMax << endl;
    out << "# " << fichero << endl;
    out << base << " " << altura << endl;
    out << res << endl;
    for ( unsigned int i = 0; i < altura; i++ ) {
        for ( unsigned int j = 0; j < base; j++ ) {
            int r = matrizPixeles[i][j].getR() * (double)res / valorMax;
            int g = matrizPixeles[i][j].getG() * (double)res / valorMax;
            int b = matrizPixeles[i][j].getB() * (double)res / valorMax;
            out << r << " " << g << " " << b << "  "; 
        }
        out << endl;
    }
}

void leerFormato(ifstream& f) {
    string formato;
    
    getline(f, formato);

    if ( formato != "P3"){
        throw runtime_error("El formato no se corresponde con P3");
    }
}

ImagenPPM ImagenPPM::lecturaPPM(const string& fichero){
    ifstream f(fichero);

    if(!f.is_open() ){
        throw runtime_error("No se puede leer el fichero " + fichero);
    }

    leerFormato(f);
    string linea;
    getline(f, linea);
    double valorMax, resolucion;
    bool hayComentarioMax = false;

    while (linea[0] == '#'){
        if (linea.substr(0, 5) == "#MAX=") {
            hayComentarioMax = true;
            valorMax = atof(linea.substr(5, string::npos).c_str());
        }
        getline(f, linea);
    }

    unsigned int base, altura;

    istringstream is(linea);
    is >> base >> altura;
    f >> resolucion;

    if (!hayComentarioMax) {
        valorMax = 1;
    }

    vector<vector<RGB>> data(altura, vector<RGB>(base));
    double red, green, blue;

    for ( unsigned int i = 0; i < altura; i++ ) {
        for ( unsigned int j = 0; j < base; j++ ) {
            f >> red >> green >> blue;

            red *= valorMax / resolucion;
            green *= valorMax / resolucion;
            blue *= valorMax / resolucion;

            RGB color(red, green, blue);
            data[i][j] = color;
        }
    }

    ImagenPPM imagen(base, altura, data, valorMax);
    cout << imagen << endl;
    return imagen;
}

// Getters y setters
double ImagenPPM::getNumeroMayor() const{
    double valorMax = 0;
    for ( unsigned int i = 0; i < altura; i++ ) {
        for ( unsigned int j = 0; j < base; j++ ) {
            valorMax = max(valorMax, canalMayor(matrizPixeles[i][j]));
        }
    }
    return valorMax;
}

ostream& operator<<(ostream& os, const ImagenPPM& imagen) {
    os << "Imagen { w:" << imagen.base << ", h:" << imagen.altura << ", max:" << imagen.valorMax << " }" << endl;
    return os;
}
