#pragma once
#include <iostream>

void cal_cov(double **covMatrix, double *meanMatrix, double **retMatrix, int numberAssets, int numberReturns);
void cal_cov(double **covMatrix, double *meanMatrix, double **retMatrix, int numberAssets, int numberReturns, int startDay);
