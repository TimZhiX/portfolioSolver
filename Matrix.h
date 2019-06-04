/*****************************************************************************
File name: Matrix.h
Description: Class Matrix
*****************************************************************************/

#pragma once
#include <iostream>
#include <iomanip>
#include <string>

#define OVERFLOWED 1E-12

class Matrix
{
public:
    Matrix(double** items, int m, int n);    // copy Matrix from Array
    Matrix(int m, int n);                    // m*n zero Matrix
    Matrix(int n);                           // n*n unit Matrix
    Matrix(const Matrix &);                  // copy Matrix
    Matrix(double* items, int m, int n);     // copy Matrix from Array
    ~Matrix();                               // Destructor

    int getRowNum() const;                   // get number of rows
    int getColNum() const;                   // get number of cols

    Matrix Trans() const;                    // Transpose
    Matrix Inverse();                        // Inverse
    Matrix getSubMatrix(int startRow, int endRow, int startColumn, int endColumn); 
											 // get SubMatrix

    double get(int i, int j) const;          // get element
    void set(int i, int j, double val);      // set element

    Matrix operator +(const Matrix &m);      // plus
    Matrix operator -(const Matrix &m);      // minus
    Matrix operator *(const Matrix &m);      // multiply
    Matrix operator *(const double f);       // multiply by constant
    Matrix& operator=(const Matrix& m);      // copy Matrix


    friend std::ostream& operator <<(std::ostream &os, const Matrix &m); 
	                                         // overloading

private:
    double *item;                            // point to the first element in Matrix
    int rowNum;                              // number of rows
    int colNum;                              // number of cols

private:
											 // Elementary Transformation
    void RowSwap(int i, int j, double multiply);
    void RowSwap(int i, int j);
    void FlowOver();
};


