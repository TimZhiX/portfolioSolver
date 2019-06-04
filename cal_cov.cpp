/*****************************************************************************
File name: cal_cov.cpp
Description: calculate covariance matrix
*****************************************************************************/

#include "cal_cov.h"

void cal_cov(double **covMatrix, double *meanMatrix, double **retMatrix, int numberAssets, int numberReturns)
{
    for(int i = 0; i < numberAssets; i++)
    {
        for(int j = 0; j < numberAssets; j++)
        {
            double cov = 0;
            for(int k = 0; k < numberReturns; k++)
                cov += (retMatrix[i][k] - meanMatrix[i]) * (retMatrix[j][k] - meanMatrix[j]) / (numberReturns - 1);
            covMatrix[i][j] = cov;
        }
    }
}

void cal_cov(double **covMatrix, double *meanMatrix, double **retMatrix, int numberAssets, int numberReturns, int startDay)
{
    for(int i = 0; i < numberAssets; i++)
    {
        for(int j = 0; j < numberAssets; j++)
        {
            double cov = 0;
            for(int k = startDay; k < startDay + numberReturns; k++)
                cov += (retMatrix[i][k] - meanMatrix[i]) * (retMatrix[j][k] - meanMatrix[j]) / (numberReturns - 1);
            covMatrix[i][j] = cov;
        }
    }
}
