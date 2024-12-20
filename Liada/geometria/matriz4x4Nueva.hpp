#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Class for representing 4x4 double matrices
 * 
 */
class Matriz4x4 {
public:

    /**
     * @brief Construct a new Mat 4 object
     * By default, it creates a 4x4 identity matrix
     */
    inline Matriz4x4() : _mat{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} {};

    /**
     * @brief Construct a new Mat 4 object with values 
     * @param m The value 2d array
     */
    Matriz4x4(double m[4][4]);

    /**
     * @brief Return the sum of two matrices
     * 
     * @param that The other matrix
     * @return Matriz4x4 The sum matrix
     */
    Matriz4x4 operator+(const Matriz4x4 that) const;
    
    /**
     * @brief Return the difference of two matrices
     * 
     * @param that The other matrix
     * @return Matriz4x4 The difference matrix
     */
    Matriz4x4 operator-(const Matriz4x4 that) const;

    /**
     * @brief Return the matrix product of two matrices
     * 
     * @param that The other matrix
     * @return Matriz4x4 The product matrix
     */
    Matriz4x4 operator*(const Matriz4x4 that) const;

    /**
     * @brief Return the matrix multiplied by the scalar f
     * 
     * @param f the scalar value
     * @return Matriz4x4 The scaled-up matrix
     */
    Matriz4x4 operator*(const double f) const;

    /**
     * @brief Return the matrix divided by the scalar f
     * 
     * @param f the scalar value
     * @return Matriz4x4 The scaled-down matrix
     */
    Matriz4x4 operator/(const double f) const;

    /**
     * @brief Return the determinant of this matrix.
     * 
     * @return double The determinant
     */
    double det() const;

    /**
     * @brief Return the inverse of this matrix.
     * 
     * @return Matriz4x4 
     */
    Matriz4x4 inverse() const;

    /**
     * @brief Return the transpose of this matrix.
     * 
     * @return Matriz4x4 The transposed matrix
     */
    Matriz4x4 transpose() const;

    /**
     * @brief Return a matrix row by index
     * 
     * @param i The row index
     * @return decltype(auto) The row of the matrix 
     */
    decltype(auto) operator[](unsigned int i) { return _mat[i]; }
    decltype(auto) operator[](unsigned int i) const { return _mat[i]; }

    /**
     * @brief Print the matrix on an output stream
     * 
     * @param os The output stream
     * @param mat The matrix
     * @return ostream&
     */
    friend ostream& operator<<(ostream& os, const Matriz4x4& mat);
private: 
    /**
     * @brief The inner representation of the 4x4 matrix.
     */
    double _mat[4][4];
};

ostream& operator<<(ostream& os, const Matriz4x4& mat);