#include "tonemapping.hpp"
//#include <core/core.hpp>
#include <tuple>
#include <algorithm>

namespace tonemapping {

    Imagen clamp(const Imagen& imagen){

        Imagen resultado = imagen;
        resultado.valorMax = 1;
        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                resultado.matrizPixeles[i][j] = clamp(color, 1);
            }
        }
        return resultado;
    }

    Imagen equalize(const Imagen& imagen){
        Imagen resultado = imagen;

        resultado.valorMax = 1;

        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                resultado.matrizPixeles[i][j] = equalize(color,imagen.valorMax);
            }
        }
        return resultado;
        
    }

    Imagen gamma(const Imagen& imagen, double gamma){

        Imagen resultado = imagen;
        resultado.valorMax = 1;
        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                resultado.matrizPixeles[i][j] = gammaCorrection(color, imagen.valorMax, 1 / gamma);
            }
        }
        return resultado;
    }

    Imagen equalizeClamp(const Imagen& imagen, double v) {
        Imagen resultado = imagen;
        resultado.valorMax = 1;
        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                resultado.matrizPixeles[i][j] = equalizeClamp(color, v);
            }
        }
        return resultado;

    }

    Imagen gammaClamp(const Imagen& imagen, double gamma) {

        Imagen resultado = imagen;
        resultado.valorMax = 1;
        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                resultado.matrizPixeles[i][j] = gammaClamp(color, imagen.valorMax, 1 / gamma);
            }
        }
        return resultado;
    }

    Imagen simpleReinhard(const Imagen& imagen, const double a, const double delta) {
        Imagen resultado = imagen;
        resultado.valorMax = 1;

        double lw = 0;
        unsigned int num = 0;

        // compute Lw term
        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                if ( color.getLuminance() > delta ) { 
                    lw += log(color.getLuminance());
                    num++;
                }
            }
        }

        lw = exp(lw / double(num));

        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                double L = color.getLuminance() * a / lw;
                if ( color.getLuminance() > 0 )
                    resultado.matrizPixeles[i][j] = changeLuminance(color, L / ( 1.0 + L ));
            }
        }
        return resultado;
    }

    Imagen extendedReinhard(const Imagen& imagen, const double a, const double delta, const double lwhite) {
        Imagen resultado = imagen;
        resultado.valorMax = 1;

        double lw = 0;
        unsigned int num = 0;

        // compute Lw term
        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                if ( color.getLuminance() > delta ) { 
                    lw += log(color.getLuminance());
                    num++;
                }
            }
        }

        lw = exp(lw / double(num));

        #ifdef DEBUG
            cout << "\e[0;33mWarning!\e[0;37m a = " << a << "is bigger than the log-avg luminance lw = " << lw << "!" << endl;
        #endif

        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                double L = color.getLuminance() * a / lw;
                if ( color.getLuminance() > 0 ) {
                    double newL = (L * ( 1 + L / (lwhite * lwhite))) / ( 1.0 + L );
                    resultado.matrizPixeles[i][j] = changeLuminance(color, newL);
                }
            }
        }
        return resultado;
    }

    Imagen filmicUncharted(const Imagen& imagen) {
        Imagen resultado = imagen;
        resultado.valorMax = 1;
        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                resultado.matrizPixeles[i][j] = filmicUncharted(color);
            }
        }
        return resultado;
    }

    /*** Local operator ***/
/*
    double gaussian(unsigned int x, unsigned int y, double alpha, double scale) {

        double as2 = alpha * alpha * scale * scale;
        double f1 = 1.0 / (M_PI * as2);
        double f2 = exp(-x * x + y * y / as2);

        return f1 * f2;
    }

    // Convolution of the imagen with a gaussian kernel
    // TODO: precalculate kernel
    double computeV(const Imagen& imagen, unsigned int x, unsigned int y, double alpha, double scale) {

        double conv = 0;

        // round up
        int kernelSize = ceil(scale * alpha);

        for ( unsigned int i = std::max(0.0, ceil(y - kernelSize)); i < std::min(y + kernelSize, imagen.altura); i++ )  {
            for ( unsigned int j = std::max(0.0, ceil(x - kernelSize)); j < std::min(x + kernelSize, imagen.base); j++ ) {
                conv += imagen.matrizPixeles[i][j].getLuminance() * gaussian(j - x, i - y, alpha, scale);
            }
        }

        return conv;
    }

    tuple<double, double, double> computeCircleSurround(const Imagen& imagen,
        unsigned int x, unsigned int y,
        double key, double sharp, double center, double surround, double scale) {

        // center < surround

        // cout << "Circle surround -> x : " << x << ", y : " << y << endl;

        double v1 = computeV(imagen, x, y, center, scale);
        double v2 = computeV(imagen, x, y, surround, scale);
        double v  = (v1 - v2) / (key * pow(2, sharp) / ( scale * scale ) + v1);
        return { v1, v2, v };
    }

    Imagen localReinhard(const Imagen& imagen,
        double key, double sharp, double center, double surround, double threshold) {

        Imagen resultado = imagen;
        resultado.valorMax = 1;

        //double*** kernelPyramid = generateKernels(8, 1, 43, 1.6);
        
        for ( unsigned int i = 0; i < imagen.altura; i++ ) {
            for ( unsigned int j = 0; j < imagen.base; j++ ) {
                RGB color = imagen.matrizPixeles[i][j];
                double v, v1, scale;
                
                // try scales from 1 to 43 by a 1.6 step
                for ( double s = 1; s < 43; s += 1.6 ) {
                    auto [ v1s, v2s, vs ] = computeCircleSurround(imagen, j, i, key, sharp, center, surround, s);
                    
                    if ( abs(vs) < threshold ) {
                        v1 = v1s;
                        v = vs;
                        scale = s;
                        break;
                    }
                }

                //cout << "Circle surround -> x : " << j << ", y : " << i << endl;
                //cout << "v1 : " << v1 << ", v : " << v << ", scale : " << scale << endl;

                double prevLuminance = imagen.matrizPixeles[i][j].getLuminance();
                double newLuminance = clampHigh(prevLuminance / ( v1 + 1 ), 1);

                resultado.matrizPixeles[i][j] = changeLuminance(resultado.matrizPixeles[i][j], newLuminance);
            }

            cout << "row " << i << endl; 
        }

        return resultado;
    }   
*/

}