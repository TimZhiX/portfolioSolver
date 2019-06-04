/*****************************************************************************
File name: cal_mean.cpp
Description: calculate mean matrix
*****************************************************************************/

#include "cal_mean.h"

void cal_mean(double *meanMatrix, double **retMatrix, int numberAssets, int numberReturns)
{
    //calculate the average return
    for(int i = 0; i < numberAssets; i++)
    {
        double mean = 0;
        for(int j = 0; j < numberReturns; j++)
            mean += retMatrix[i][j] / numberReturns;
        meanMatrix[i] = mean;
    }
}

void cal_mean(double *meanMatrix, double **retMatrix, int numberAssets, int numberReturns, int startDay)
{
    //calculate the average return from specific startDay
    for(int i = 0; i < numberAssets; i++)
    {
        double mean = 0;
        for(int j = startDay; j < startDay + numberReturns; j++)
            mean += retMatrix[i][j] / numberReturns;
        meanMatrix[i] = mean;
    }
}
