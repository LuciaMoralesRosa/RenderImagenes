#include "imagen.hpp"

#include <regex>
#include <fstream>

double Imagen::getMaxNumber() {
    double valorMax = 0;
    for ( unsigned int i = 0; i < altura; i++ ) {
        for ( unsigned int j = 0; j < base; j++ ) {
            valorMax = max(valorMax, maxChannel(matrizPixeles[i][j]));
        }
    }
    return valorMax;
}

void readHeader(ifstream& f) {
    string header;
    
    getline(f, header);

    if ( header != "P3"){
        throw runtime_error("Different format !!");
    }
}

Imagen Imagen::readPPM(const string& path){
    ifstream f(path);

    if( !f.is_open() ){
    
        throw runtime_error("Can't read from " + path);
    }

    readHeader(f);
    string line;
    getline(f, line);
    double valorMax;
    bool maxCommentFound = false;

    while ( line[0] == '#' ){
        
        if ( line.substr(0, 5) == "#MAX=" ) {
            maxCommentFound = true;
            valorMax = atof(line.substr(5, string::npos).c_str());
        }
        
        getline(f, line);

    }

    unsigned int base, altura;

    istringstream is(line);
    is >> base >> altura;

    double resolution;

    f >> resolution;

    if ( !maxCommentFound ) valorMax = 1;

    vector<vector<RGB>> data(altura, vector<RGB>(base));
    double red,green,blue;

    for ( unsigned int i = 0; i < altura; i++ ) {
        for ( unsigned int j = 0; j < base; j++ ) {
            f >> red >> green >> blue;

            red *= valorMax / resolution;
            green *= valorMax / resolution;
            blue *= valorMax / resolution;

            RGB color(red,green,blue);
            data[i][j] = color;
        }
    }

    Imagen imagen(base, altura, data, valorMax);

    cout << imagen << endl;

    return imagen;
}


void Imagen::writeToPPM(const string& path, unsigned int res) const {
    ofstream out(path);

    if ( !out.is_open() ) {
        throw runtime_error("Can't write to " + path);
    }

    out << "P3" << endl;
    out << "#MAX=" << valorMax << endl;
    out << "# " << path << endl;
    out << base << " " << altura << endl;
    out << res << endl;
    for ( unsigned int i = 0; i < altura; i++ ) {
        for ( unsigned int j = 0; j < base; j++ ) {

            int r = matrizPixeles[i][j].red * (double)res / valorMax;
            int g = matrizPixeles[i][j].green * (double)res / valorMax;
            int b = matrizPixeles[i][j].blue * (double)res / valorMax;
            out << r << " " << g << " " << b << "  "; 
        }
        out << endl;
    }
};
 
void Imagen::writeToBMP(const string& path) const {
    ofstream out(path, ios::binary);

    if ( !out.is_open() ) {
        throw runtime_error("Can't write to '" + path + "'.");
    }

    // write signature
    out.write("BM", 2);

    // write file size (should be 54 + 3 * base * altura since its color depth
    // is 24 bits.
    
    // Imagen size : 3 * (base + padding) * altura
    
    unsigned int padding = (4 - (base * 3) % 4) % 4; 
    uint32_t rasterSize = 3 * (base + padding) * altura;
    uint32_t fileSize = 54 + rasterSize;
    out.write((char *) &fileSize, sizeof(fileSize));

    uint32_t zero = 0;
    out.write((char *) &zero, sizeof(zero));

    /* Write info header: 40 bytes */
    uint32_t dataOffset = 54;
    out.write((char *) &dataOffset, sizeof(dataOffset));

    // Write header size
    uint32_t infoHeaderSize = 40;
    out.write((char *) &infoHeaderSize, sizeof(infoHeaderSize));

    // Write base and altura
    uint32_t w = base, h = altura;
    out.write((char *) &w, sizeof(w));
    out.write((char *) &h, sizeof(h));

    // Write default plane value
    uint16_t planes = 1;
    out.write((char *) &planes, sizeof(planes));

    uint16_t depth = 24;
    out.write((char *) &depth, sizeof(depth));

    // No compression by default
    uint32_t compression = 0;
    out.write((char *) &compression, sizeof(compression));

    out.write((char *) &fileSize, sizeof(fileSize));

    // write zeros
    uint32_t additionalInfo[] = {70, 70, 1 << 24, 0};
    out.write((char *) additionalInfo, sizeof(additionalInfo));

    uint8_t* dataPtr = (uint8_t*)calloc((size_t)rasterSize, sizeof(uint8_t));

    unsigned int readIndex = 0;

    #ifdef DEBUG
        cout << "file size (B): " << fileSize << endl;
        cout << "data offset (B): " << dataOffset << endl;
        cout << "info header size (B): " << infoHeaderSize << endl;
        cout << "base, altura (px): (" << base << ", " << altura << ")" << endl;
        cout << "max value: " << valorMax << endl;
    #endif

    // assume bits per pixel is 24 for now
    for ( int i = altura - 1; i >= 0; i-- ) {
        for ( int j = 0; j < base; j++ ) {
            uint8_t b = (uint8_t)(matrizPixeles[i][j].blue * 255.0 / valorMax);
            uint8_t g = (uint8_t)(matrizPixeles[i][j].green * 255.0 / valorMax);
            uint8_t r = (uint8_t)(matrizPixeles[i][j].red * 255.0 / valorMax);

            dataPtr[readIndex++] = b;
            dataPtr[readIndex++] = g;
            dataPtr[readIndex++] = r;
        }
        // skip padding
        readIndex += padding;
    }

    // free memory after loading Imagen into object
    free(dataPtr);

    out.write((char *) dataPtr, rasterSize);
}

Imagen Imagen::readBMP(const string& path) {
    ifstream in(path, ios::binary);

    if ( !in.is_open() ) {
        throw runtime_error("Can't read from '" + path + "'.");
    }

    /* Read header: 14 bytes */

    // Read BMP signature and check if it is "BM", otherwise break
    char signature[2];
    in.read(signature, 2);

    if ( strcmp(signature, "BM") != 0 ) {
        throw runtime_error("Invalid signature (" + string(signature) + ")");
    }

    // read file size
    uint32_t fileSize;
    in.read((char*) &fileSize, sizeof(fileSize));

    // Ignore 4 reserved bytes
    in.ignore(4);

    uint32_t dataOffset;
    in.read((char *) &dataOffset, sizeof(dataOffset));

    /* Read info header: 40 bytes by default, read header size just in case */

    // Read header size
    uint32_t infoHeaderSize;
    in.read((char *) &infoHeaderSize, sizeof(infoHeaderSize));

    // read base and altura
    uint32_t base, altura;
    in.read((char *) &base, sizeof(base));
    in.read((char *) &altura, sizeof(altura));

    // Ignore planes
    in.ignore(2);

    // Read bit count (log2 of color depth)
    uint16_t bitCount;
    in.read((char *) &bitCount, sizeof(bitCount));

    // Ignore compression data ( assume it's type 0 - no compression )
    in.ignore(4);

    // Read raster data size
    uint32_t rasterSize;
    in.read((char *) &rasterSize, sizeof(rasterSize));

    // Ignore 16 bytes (x,y resolutions; )
    in.ignore(16);

    if ( bitCount <= 8 ) {
        // ignore palette for now
        in.ignore(4 * (1 << bitCount));
    }

    #ifdef DEBUG
        cout << "signature: " << string(signature) << endl;
        cout << "file size (B): " << fileSize << endl;
        cout << "data offset (B): " << dataOffset << endl;
        cout << "info header size (B): " << infoHeaderSize << endl;
        cout << "base, altura (px): (" << base << ", " << altura << ")" << endl;
        cout << "bits per pixel: " << bitCount << endl;
    #endif

    // Ignore additional info header file (palettes and such) for now
    in.ignore(dataOffset - 54);

    Imagen img(base, altura);
    img.valorMax = 255;
    uint8_t* dataPtr = (uint8_t*)malloc((size_t)rasterSize);

    in.read((char*)dataPtr, rasterSize);

    unsigned int readIndex = 0;

    unsigned int padding = (4 - (base * 3) % 4) % 4; 
    // assume bits per pixel is 24 for now
    for ( int i = altura - 1; i >= 0; i-- ) {
        for ( int j = 0; j < base; j++ ) {
            uint8_t b = dataPtr[readIndex++];
            uint8_t g = dataPtr[readIndex++];
            uint8_t r = dataPtr[readIndex++];

            img.matrizPixeles[i][j] = RGB(r,g,b);
        }
        // skip padding
        readIndex += padding;
    }

    // free memory after loading Imagen into object
    free(dataPtr);

    return img;
}

ostream& operator<<(ostream& os, const Imagen& Imagen){
    os << "Imagen { w:" << Imagen.base << ", h:" << Imagen.altura << ", max:" << Imagen.valorMax << " }" << endl;
    return os;
}