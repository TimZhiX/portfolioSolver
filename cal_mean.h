/*****************************************************************************
File name: cal_mean.h
Description: calculate mean matrix
*****************************************************************************/

#pragma once
#include <iostream>

void cal_mean(double *meanMatrix, double **retMatrix, int numberAssets, int numberReturns);
void cal_mean(double *meanMatrix, double **retMatrix, int numberAssets, int numberReturns, int startDay);
