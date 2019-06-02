#include <iostream>
#include "csv.h"
#include "matrix.h"
#include "CGM.h"
#include "string_to_double.h"
#include "readData.h"
#include "cal_mean.h"
#include "cal_cov.h"

using namespace std;

int  main (int argc, char *argv[])
{

    int numberAssets = 83;
    int numberReturns = 700;

    // Dynamic Array
    double **retMatrix = new double*[numberAssets];     // matrix to store return
    double *meanMatrix = new double[numberAssets];      // matrix to store mean
    double **covMatrix = new double*[numberAssets];     // matrix to store covariance

    // allocate memory
    for(int i = 0; i < numberAssets; i++)
    {
        retMatrix[i] = new double[numberReturns];
        covMatrix[i] = new double[numberAssets];
    }

    // read the data
    string fileName = "asset_returns.csv";

    // returnMatrix[i][j] stores the value of asset i, return j
    readData(retMatrix, fileName);

    // set initial window size as 100 days
    numberReturns = 100;

    // calculate the average return
    cal_mean(meanMatrix, retMatrix, numberAssets, numberReturns);

    // calculate covariance matrix
    cal_cov(covMatrix, meanMatrix, retMatrix, numberAssets, numberReturns);

    // initialize input
    Matrix Q(85,85);
    for (int i = 0; i < 83; i++)
        for (int j = 0; j < 83; j++)
            Q.set(i,j,covMatrix[i][j]);

    for (int i = 0; i < 83; i++)
    {
        Q.set(83,i,-meanMatrix[i]);
        Q.set(84,i,-1);
        Q.set(i,83,-meanMatrix[i]);
        Q.set(i,84,-1);
    }


    Matrix x0(85,1);
    for (int i = 0; i < 83; i++)
        x0.set(i,0,1./83); // initial weights


    Matrix b(85,1);
    b.set(83,0,-0.1);   // set target return of portfolio (rp)
    b.set(84,0,-1);

    // Conjugate Gradient Method to get optimized weights
    x0 = CGM(x0,Q,b);



    /////////////////////////////////////////////////////
    // Back testing


    //calculate the average return
    double mean_oos = 0;
    double cov_oos = 0;
    int startDay = 100;
    numberReturns = 12;
    cal_mean(meanMatrix, retMatrix, numberAssets, numberReturns, startDay);


    for(int i = 0; i < numberAssets; i++)
        mean_oos += x0.get(i,0) * meanMatrix[i];
    cout << "mean_oos = " << mean_oos << endl;

    // calculate covariance matrix
    cal_cov(covMatrix, meanMatrix, retMatrix, numberAssets, numberReturns, startDay);
    Matrix covMatrix_oos(covMatrix,83,83);  // turn Array into Matrix class
    Matrix w = x0.getSubMatrix(0,82,0,0);
    cov_oos = (w.Trans() * covMatrix_oos * w).get(0,0);
    cout <<"cov_oos = " << cov_oos << endl;


//////////////////////////////////////////////











    // free memory
    for(int i = 0; i < numberAssets; i++)
    {
        delete[] retMatrix[i];
        delete[] covMatrix[i];
    }
    delete[] retMatrix;
    delete[] covMatrix;
    delete[] meanMatrix;

    return 0;
}
