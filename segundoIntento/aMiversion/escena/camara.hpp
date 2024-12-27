#pragma once

#include "../geometria/vector.hpp"
#include "../geometria/direccion.hpp"
#include "../geometria/punto.hpp"


/**
 * @class Camara
 * @brief Representa una cámara en un sistema de coordenadas 3D.
 *
 * La clase Camara modela una cámara en un entorno 3D. Está definida por su
 * origen y tres vectores que determinan su orientación: izquierdo (l), hacia
 * arriba (u) y hacia adelante (f). Además, define las dimensiones de la imagen 
 * que la cámara proyecta y el tamaño de cada píxel en términos de las
 * dimensiones de la imagen.
 */
class Camara {

public:

	/** 
     * @brief Origen de la cámara.
     *
     * Representa el punto en el espacio desde el cual la cámara observa.
     */
	Punto o;

	/** 
     * @brief Vectores que definen la orientación de la cámara.
     *
     * - l: El vector que indica la dirección hacia la izquierda de la cámara.
     * - u: El vector que indica la dirección hacia arriba de la cámara.
     * - f: El vector que indica la dirección hacia adelante de la cámara.
     */
	Direccion l, u, f;

	/** 
     * @brief Dimensiones de la imagen en píxeles.
     *
     * - base: El ancho de la imagen en píxeles.
     * - altura: La altura de la imagen en píxeles.
     */
	int base, altura;

    /** 
     * @brief Dimensiones de cada píxel en unidades espaciales.
     *
     * - basePixel: La anchura de cada píxel en unidades espaciales.
     * - alturaPixel: La altura de cada píxel en unidades espaciales.
     */	double basePixel, alturaPixel;

public:

	 /**
     * @brief Constructor por defecto de la cámara.
     * 
     * Inicializa la cámara con un origen en el punto (0, 0, 0) y los vectores
     * de orientación predeterminados.
     */
	Camara();

	 /**
     * @brief Constructor de la cámara con parámetros.
     * 
     * @param origen El punto de origen de la cámara.
     * @param left El vector que define la dirección hacia la izquierda de la
     * cámara.
     * @param up El vector que define la dirección hacia arriba de la cámara.
     * @param forward El vector que define la dirección hacia adelante de la
     * cámara.
     * @param b El ancho de la imagen en píxeles.
     * @param a La altura de la imagen en píxeles.
     */
	Camara(const Punto& origen, const Direccion& left, const Direccion& up,
			const Direccion& forward, int b, int a);

};
