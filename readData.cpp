#include "readData.h"
#include "csv.h"
#include "string_to_double.h"



void readData(double **data, std::string fileName)
{
    char tmp[20];
    std::ifstream file ( strcpy(tmp, fileName.c_str()) );
    Csv csv(file);
    std::string line;
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
