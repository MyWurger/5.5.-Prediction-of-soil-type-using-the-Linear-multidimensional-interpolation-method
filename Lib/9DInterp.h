#ifndef INTERP
#define INTERP
#include <vector>
#include<string>
#include <cmath>
#include "stdio.h"

using namespace std;


class T9DInterp
{
private:
    //ВХОДНЫЕ ДАННЫЕ
    vector<vector<double>> _vecOfCanals; //входной канал излучений
    vector<double>_gumus; //входные данные вектора
    vector<double>_point; //точкка для которой ищем гумус
    int _optimal;//диапазон в котором ищем минимальные к нашей точке точки
    int _testingPointIndex;


    //ПЕРЕМЕННЫЕ ДЛЯ ВЫЧИСЛЕНИЙ
    vector<vector <double>>_optimalDesision; //вектор ближайших точек из заданного диапазона
    vector<double> gumusOptimal; //значения гумуса соответствующие найденным рядом точкам
    vector<double> gumusKramer; //значения гумуса соотв-ее набору точек с самым минимальным расстоянием до данной
    vector<double> distsForAll; //массив расстояний до всех точек из диапазона ближайших точек
    vector<double> endKoefOfMatr; //коэффиценты матрицы после крамера
    vector<vector<double>>pointsForFindingKoef; //матрица для Крамера

    //переменная для поиска определителя для векторного произведения векторов
    double DET = 1;

    //вспомогательный вектор
    static vector<double>vec;

    //ВСПОМОГАТЕЛЬНЫЕ ВЫЧИСЛИТЕЛЬНЫЕ ФУНКЦИИ

    //расстояние от исходной точки до всех необходимых вершин
    double distFromPointsToVertex(vector <double> point,vector<double>a,vector<double>b,vector<double>c,
                                  vector<double>d,vector<double>e,vector<double>f,
                                  vector<double>g,vector<double>h,vector<double>i);

    //расстояние между точками
    double getDist(vector<double>x1,vector<double>x2);

    //нахождение набора точек соотв-го минимальному диапазону
    void findOptimalDesisionOfMin();


    //периметр 9-мерной фигуры составленного из найденных точек
    double            SquareBig(vector<double>a,vector<double>b,vector<double>c,
                                vector<double>d,vector<double>e,vector<double>f,
                                vector<double>g,vector<double>h,vector<double>i);

    //периметр 9-мерной фигуры составленного из любых 8 найденных точек и одной нашей , для которой гумус ищется
    double            SquareManySmall(vector<double>a,vector<double>b,vector<double>c,
                                      vector<double>d,vector<double>e,vector<double>f,
                                      vector<double>g,vector<double>h,vector<double>i,vector<double>point);

    //вспомогательная функция для составления вектора для поиска векторного произведения векторов
    vector<double>make_vector(vector<double>start,vector<double>end);

    //метод Гаусса для решения СЛАУ
    void Gaus(vector<vector<double>>matrix,vector<double > gumus);

    //проверка на то , находится ли точка внутри нашей 9-ти мерной фигуры
    bool pointInside();

    //сброс значения определителя до 1
    void setDET_1();


public:


    T9DInterp (vector<vector<double>> vecOfCanals,vector<double>gumus,vector<double>point,int optimal, int testingPointIndex);
    ~T9DInterp();

    void gnuplotWriter(string dirName,vector<double>vec1=vec,vector<double>vec2=vec);

    //заполнение массива данными
    void setSignal(vector <double > vec);

    //вывод результата
    double getResult();

    //запуск всей обработки
    void exec();

};

#endif
