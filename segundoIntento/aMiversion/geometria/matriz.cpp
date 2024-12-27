#include "matriz.hpp"

//------------------------------- CONSTRUCTORES ------------------------------//
Matriz::Matriz() {
    // Crear una matriz e inicializarla a 0
    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++)
            m[i][j] = 0;
    }
}

Matriz::Matriz(double m[DIM][DIM]) {
    // Crear una matriz e inicializarla con los valores dados
    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++)
            this->m[i][j] = m[i][j];
    }
}
//------------------------------- CONSTRUCTORES ------------------------------//


//----------------------------- METODOS PRIVADOS -----------------------------//
void Matriz::cambiarFilas(Matriz matriz, int fila1, int fila2) {
    for(int i = 0; i < DIM; i++) {
        swap(matriz.m[fila1][i], matriz.m[fila2][i]);
    }
}
//----------------------------- METODOS PRIVADOS -----------------------------//


//----------------------------- METODOS PUBLICOS -----------------------------//
// | 1 0 0 x |
// | 0 1 0 y |
// | 0 0 1 z |
// | 0 0 0 1 |
void Matriz::matrizTraslacion(double x, double y, double z){
    // Inicializar la matriz a la identidad
    for(int i = 0; i < DIM; i++) {
        m[i][i] = 1;
    }
    // Asignar los valores de traslación
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}

// | x 0 0 0 |
// | 0 y 0 0 |
// | 0 0 z 0 |
// | 0 0 0 1 |
void Matriz::matrizEscala(double x, double y, double z){
    // Asignar los valores de escala
    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
    // Cuarta dimension de la matriz
    m[3][3] = 1;
}

// | 1    0       0     0 |
// | 0  cos(â) -sin(â)  0 |
// | 0  sin(â)  cos(â)  0 |
// | 0    0       0     1 |
void Matriz::matrizRotacionX(double angulo){
    // Convertir el ángulo a radianes
    angulo = angulo * M_PI / 180;
    // Asignar los valores de rotación
    m[0][0] = 1;
    m[1][1] = cos(angulo);
    m[1][2] = -sin(angulo);
    m[2][1] = sin(angulo);
    m[2][2] = cos(angulo);
    m[3][3] = 1;
}

// | cos(â) 0  sin(â)  0 |
// |   0    1    0     0 |
// |-sin(â) 0  cos(â)  0 |
// |   0    0    0     1 |
void Matriz::matrizRotacionY(double angulo){
    // Convertir el ángulo a radianes
    angulo = angulo * M_PI / 180;
    // Asignar los valores de rotación
    m[0][0] = cos(angulo);
    m[0][2] = sin(angulo);
    m[1][1] = 1;
    m[2][0] = -sin(angulo);
    m[2][2] = cos(angulo);
    m[3][3] = 1;
}

// | cos(â) -sin(â) 0   0 |
// | sin(â)  cos(â) 0   0 |
// |   0       0    1   0 |
// |   0       0    0   1 |
void Matriz::matrizRotacionZ(double angulo){
    // Convertir el ángulo a radianes
    angulo = angulo * M_PI / 180;
    // Asignar los valores de rotación
    m[0][0] = cos(angulo);
    m[0][1] = -sin(angulo);
    m[1][0] = sin(angulo);
    m[1][1] = cos(angulo);
    m[2][2] = 1;
    m[3][3] = 1;
}

bool Matriz::invertirMatriz() {
    // Crear una matriz identidad
    Matriz identidad = Matriz();
    for(int i = 0; i < DIM; i++) {
        identidad.m[i][i] = 1.0;
    }

    for(int i = 0; i < DIM; i++) {
        // Buscar el pivote en cada columna
        int filaPivote = i;
        for(int j = i + 1; j < DIM; j++) {
            if(abs(m[j][i]) > abs(m[filaPivote][i])) {
                // El pivote sera el mayor valor en la columna
                filaPivote = j;
            }
        }

        // Cambiar las filas si la fila del pivote mas grande no es la actual
        if(filaPivote != i) {
            cambiarFilas(m, i, filaPivote);
            cambiarFilas(identidad, i, filaPivote);
        }

        double privote = m[i][i];
        if(privote == 0.0) {
            cout << "La matriz no puede ser invertida." << endl;
            // Como no se puede invertir la matriz, se retorna false
            return false;
        }

        // Normalizar el pivote de forma que sea 1
        for(int j = 0; j < DIM; j++) {
            m[i][j] /= privote;
            // Aplicar la misma operación a la matriz identidad
            identidad.m[i][j] /= privote;
        }

        // Eliminar los elementos no diagonales
        for(int j = 0; j < DIM; j++) {
            if(j != i) {
                double factor = m[j][i];
                for(int k = 0; k < DIM; k++) {
                    m[j][k] -= factor * m[i][k];
                    // Aplicar la misma operación a la matriz identidad
                    identidad.m[j][k] -= factor * identidad.m[i][k];
                }
            }
        }
    }
    // La matriz identidad contiene la matriz inversa
    // Se va a copiar la matriz identidad en la original para obtener la inversa
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            m[i][j] = identidad.m[i][j];
        }
    }

    // Como se ha podido invertir la matriz, se retorna true
    return true;
}

void Matriz::matrizIdentidad() {
    for(int i = 0; i < DIM; i++)
        m[i][i] = 1;
}

void Matriz::establecerComponente(int i, int j, double valor) {
    m[i][j] = valor;
}

double Matriz::obtenerComponente(int i, int j) const {
    return m[i][j];
}
//----------------------------- METODOS PUBLICOS -----------------------------//

//-------------------------------- OPERADORES --------------------------------//
ostream &operator<<(ostream &o, const Matriz &m) {
    for(int i = 0; i < DIM; i++) {
        o <<(i==0?"/ ":i==3?"\\ ":"| ");
        for(int j = 0; j < DIM; j++) {
            o << fixed << setprecision(2) << m.m[i][j] << " ";
        }
        o <<(i==0?"\\\n":i==3?"/\n ":"|\n");
    }
    return o;
}
//-------------------------------- OPERADORES --------------------------------//