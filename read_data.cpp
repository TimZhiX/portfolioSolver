#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include "csv.h"
#include "matrix.h"

// change type string to type double
double string_to_double( const std::string& s );

// read data from file
void readData( double **data, string fileName );

int  main (int argc, char *argv[])
{

    int numberAssets = 83;
    int numberReturns = 700;

    // matrix to store return
    double **retMatrix = new double*[numberAssets];

    // Array to store mean
    double *meanMatrix = new double[numberAssets];

    // matrix to store covariance
    double **covMatrix = new double*[numberAssets];

    //allocate memory
    for(int i = 0; i < numberAssets; i++)
    {
        retMatrix[i] = new double[numberReturns];
        covMatrix[i] = new double[numberReturns];
    }

    //read the data from the file and store it into the return matrix
    string fileName = "asset_returns.csv";

    // returnMatrix[i][j] stores the asset i, return j value
    readData(retMatrix, fileName);

    // set window size as 100 days
    numberReturns = 100;

    //calculate the average return
    double mean = 0;
    for(int i = 0; i < numberAssets; i++)
    {
        mean = 0;
        for(int j = 0; j < numberReturns; j++)
        {
            double temp = retMatrix[i][j];
//            cout << "Asset " << i << ", Return "<< j <<" = "<< temp<<"\n";
            mean += temp / numberReturns;
        }
        meanMatrix[i] = mean;
//        cout << "Asset "<< i << " Mean = "<< mean << endl;
    }

    // calculate covariance matrix
    double cov = 0;
    for(int i = 0; i < numberAssets; i++)
    {

        for(int j = 0; j < numberAssets; j++)
        {
            cov = 0;
            for(int k = 0; k < numberReturns; k++)
            {
                cov += (retMatrix[i][k] - meanMatrix[i]) * (retMatrix[j][k] - meanMatrix[j]) / (numberReturns - 1);
            }
            covMatrix[i][j] = cov;
//            cout << "i = " << i << ", j = "<< j <<" cov : "<< cov << endl;
        }
    }

    Matrix Q(85,85);
    for (int i = 0; i < 83; i++)
    {
        for (int j = 0; j < 83; j++)
        {
            Q.set(i,j,covMatrix[i][j]);
        }
    }

    for (int i = 0; i < 83; i++)
    {
        Q.set(i,83,-meanMatrix[i]);
        Q.set(i,84,-1);
    }
    for (int j = 0; j < 83; j++)
    {
        Q.set(83,j,-meanMatrix[j]);
        Q.set(84,j,-1);
    }

    Q.set(83,83,0);
    Q.set(83,84,0);
    Q.set(84,83,0);
    Q.set(84,84,0);
//    cout << Q << endl;

    Matrix x0(85,1);
    for (int i = 0; i < 83; i++)
    {
        x0.set(i,0,1./83);
    }
    //lambda
    x0.set(83,0,0.5);
    //mu
    x0.set(84,0,0.8);
//    cout << x0 << endl;

    Matrix b(85,1);
    for (int i = 0; i < 83; i++)
    {
        b.set(i,0,0);
    }
    b.set(83,0,-0.1);
    b.set(84,0,-1);
//    cout << b << endl;


    Matrix s0(b - Q * x0);
    Matrix p0(s0);

double err = 1;
int cnt = 1;
    while(err > 10e-6)
    {
        double a = (s0.Trans() * s0 ).get(0,0) / ( p0.Trans() * Q * p0 ).get(0,0);
//        cout << a << endl;
        x0 = (x0 +  p0 * a) ;

        err = (s0.Trans() * s0 ).get(0,0);
        s0 = (s0 - Q * p0 * a) ;
        double b = ( s0.Trans() * s0 ).get(0,0) / err;
        p0 = (s0 + p0 * b) ;
//        cout << cnt++ <<" : "<<(s0.Trans() * s0).get(0,0) << endl;
//        cout << x0 << endl;
    }
//    cout << x0 << endl;








    /////////////////////////////////////////////////////
    // backtesting


    //calculate the average return
    double window_size = 12;
    double mean_oos = 0;
    numberReturns = 700;
    for(int i = 0; i < numberAssets; i++)
    {
        mean = 0;
        for(int j = 100; j < 100 + window_size; j ++)
        {
            double temp = retMatrix[i][j];
//            cout << "Asset " << i << ", Return "<< j <<" = "<< temp<<"\n";
            mean += temp / numberReturns;
        }
        meanMatrix[i] = mean;
//        cout << "Asset "<< i << " Mean = "<< mean << endl;
//        cout << "weight " << i << " = " << x0.get(i,0) <<endl;
        mean_oos += x0.get(i,0) * mean;
    }
//    cout << "mean_oos = " << mean_oos << endl;

    // calculate covariance matrix
    for(int i = 0; i < numberAssets; i++)
    {

        for(int j = 0; j < numberAssets; j++)
        {
            cov = 0;
            for(int k = 100; k < 100+window_size; k++)
            {
                cov += (retMatrix[i][k] - meanMatrix[i]) * (retMatrix[j][k] - meanMatrix[j]) / (numberReturns - 1);
            }
            covMatrix[i][j] = cov;
//            cout << "i = " << i << ", j = "<< j <<" cov : "<< cov << endl;
        }
    }

    Matrix covMatrix_oos(covMatrix,83,83);
    Matrix w = x0.getSubMatrix(0,82,0,0);

    cout << w.Trans() * covMatrix_oos * w << endl;


//////////////////////////////////////////////











    // free memory
    for(int i = 0; i < numberAssets; i++)
        delete[] retMatrix[i];
    delete[] retMatrix;

    return 0;
}


double string_to_double( const std::string& s )
{
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

void readData(double **data, string fileName)
{
    char tmp[20];
    ifstream file ( strcpy(tmp, fileName.c_str()) );
    Csv csv(file);
    string line;
    if ( file.is_open() )
    {
        int i=0;
        while ( csv.getline(line) != 0 )
        {
            for (int j = 0; j < csv.getnfield(); j++)
            {
                double temp = string_to_double(csv.getfield(j));
//                cout << "Asset " << j << ", Return "<< i <<"="<< temp<<"\n";
                data[j][i]=temp;
            }
            i++;
        }

        file.close();
    }
    else
    {
        cout <<fileName <<" missing\n";
        exit(0);
    }
}

