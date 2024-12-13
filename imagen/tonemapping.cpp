#include "tonemapping.hpp"


namespace tonemapping {

    ImagenPPM clamp(const ImagenPPM& imagen, const int valor){
        ImagenPPM resultado = imagen;
        resultado.setValorMax(valor);
        vector<vector<RGB>> matriz = imagen.getMatrizPixeles();
        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                resultado.setPixelMatriz(i, j, clamp(color, valor));
            }
        }
        return resultado;
    }

    ImagenPPM equalize(const ImagenPPM& imagen){
        ImagenPPM resultado = imagen;
        resultado.setValorMax(1);
        vector<vector<RGB>> matriz = imagen.getMatrizPixeles();
        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                resultado.setPixelMatriz(i, j, equalize(color, imagen.getValorMax()));
            }
        }
        return resultado;
    }

    ImagenPPM gamma(const ImagenPPM& imagen, double gamma){
        ImagenPPM resultado = imagen;
        resultado.setValorMax(1);
        vector<vector<RGB>> matriz = imagen.getMatrizPixeles();
        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                resultado.setPixelMatriz(i, j, gammaCorrection(color, imagen.getValorMax(), 1 / gamma));
            }
        }
        return resultado;
    }

    ImagenPPM equalizeClamp(const ImagenPPM& imagen, double v) {
        ImagenPPM resultado = imagen;
        resultado.setValorMax(1);
        vector<vector<RGB>> matriz = imagen.getMatrizPixeles();
        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                resultado.setPixelMatriz(i, j, equalizeClamp(color, v));
            }
        }
        return resultado;
    }

    ImagenPPM gammaClamp(const ImagenPPM& imagen, double gamma) {
        ImagenPPM resultado = imagen;
        resultado.setValorMax(1);
        vector<vector<RGB>> matriz = imagen.getMatrizPixeles();
        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                resultado.setPixelMatriz(i, j, gammaClamp(color, imagen.getValorMax(), 1 / gamma));
            }
        }
        return resultado;
    }

    ImagenPPM simpleReinhard(const ImagenPPM& imagen, const double a, const double delta) {
        ImagenPPM resultado = imagen;
        resultado.setValorMax(1);
        vector<vector<RGB>> matriz = imagen.getMatrizPixeles();

        double lw = 0;
        unsigned int num = 0;

        // compute Lw term
        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                if (color.getLuminancia() > delta) { 
                    lw += log(color.getLuminancia());
                    num++;
                }
            }
        }

        lw = exp(lw / double(num));

        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                double L = color.getLuminancia() * a / lw;
                if (color.getLuminancia() > 0) {
                    resultado.setPixelMatriz(i, j, cambiarLuminancia(color, L / (1.0 + L)));
                }
            }
        }
        return resultado;
    }

    ImagenPPM extendedReinhard(const ImagenPPM& imagen, const double a, const double delta, const double lwhite) {
        ImagenPPM resultado = imagen;
        resultado.setValorMax(1);
        vector<vector<RGB>> matriz = imagen.getMatrizPixeles();

        double lw = 0;
        unsigned int num = 0;

        // compute Lw term
        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                if (color.getLuminancia() > delta) { 
                    lw += log(color.getLuminancia());
                    num++;
                }
            }
        }

        lw = exp(lw / double(num));

        #ifdef DEBUG
            cout << "\e[0;33mWarning!\e[0;37m a = " << a << "is bigger than the log-avg luminance lw = " << lw << "!" << endl;
        #endif

        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                double L = color.getLuminancia() * a / lw;
                if (color.getLuminancia() > 0) {
                    double newL = (L * (1 + L / (lwhite * lwhite))) / (1.0 + L);
                    resultado.setPixelMatriz(i, j, cambiarLuminancia(color, newL));
                }
            }
        }
        return resultado;
    }

    ImagenPPM filmicUncharted(const ImagenPPM& imagen) {
        ImagenPPM resultado = imagen;
        resultado.setValorMax(1);
        vector<vector<RGB>> matriz = imagen.getMatrizPixeles();
        for (unsigned int i = 0; i < imagen.getAltura(); i++) {
            for (unsigned int j = 0; j < imagen.getBase(); j++) {
                RGB color = matriz[i][j];
                resultado.setPixelMatriz(i, j, filmicUncharted(color));
            }
        }
        return resultado;
    }
}