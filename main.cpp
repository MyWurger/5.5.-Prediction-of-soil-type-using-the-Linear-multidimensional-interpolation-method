#include <iostream>
#include "9DInterp.h"
#include "fstream"

using namespace std;


int main()
{
    std::vector<vector<double>> vecOfCanals;
    std::vector<double> gumus;
    vector<vector<double>>_pointForFindingGumus;

    std::ifstream in("../data/bkp2/Exel.txt"); // окрываем файл для чтения точек каналов
    string s;
    string chislo;
    for(int i=0;i<69;++i){

                           vector<double>canal;

                           //1

                           getline(in, s,' ');
                           chislo=s;
                           canal.push_back(stoi(chislo));
//                           std::cout<<stoi(chislo)<<" ";

                           //2

                           getline(in, s,' ');
                           chislo=s;
                           canal.push_back(stoi(chislo));
//                           std::cout<<stoi(chislo)<<" ";

                           //3

                           getline(in, s,' ');
                           chislo=s;
                           canal.push_back(stoi(chislo));
//                           std::cout<<stoi(chislo)<<" ";

                           //4

                           getline(in, s,' ');
                           chislo=s;
                           canal.push_back(stoi(chislo));
//                           std::cout<<stoi(chislo)<<" ";

                           //5

                           getline(in, s,' ');
                           chislo=s;
                           canal.push_back(stoi(chislo));
//                           std::cout<<stoi(chislo)<<" ";

                           //6

                           getline(in, s,' ');

                           chislo=s;
                           canal.push_back(stoi(chislo));
//                           std::cout<<stoi(chislo)<<" ";

                           //7

                           getline(in, s,' ');
                           chislo=s;
                           canal.push_back(stoi(chislo));
                           //std::cout<<stoi(chislo)<<" ";

                           //8

                           getline(in, s,' ');
                           chislo=s;
                           canal.push_back(stoi(chislo));
                           //std::cout<<stoi(chislo)<<" ";

                           //gumus

                           getline(in, s);
                           chislo=s;
                           gumus.push_back(stod(chislo));
                           //std::cout<<(chislo);

                           //std::cout<<endl;

                           vecOfCanals.push_back(canal);

                           //gumus.push_back(stod(chislo));

//               cout << gumus[i] << endl; // выводим на экран

         //  }
    }
    in.close();



    for(int i=0;i<vecOfCanals.size();++i)
    {
        std::cout<<"Point: " << i << "\n";
        int testingPointIndex = i;
        T9DInterp interp(vecOfCanals,gumus,vecOfCanals[testingPointIndex], 10, testingPointIndex);
        interp.exec();
    }


}






