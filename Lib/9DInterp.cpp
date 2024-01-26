#include "9DInterp.h"
#include "stdio.h"
#include <iomanip>
#include <iostream>
#include "stdio.h"

double max(vector<double>vec)
{
    int max=vec[0];
    for (int i=1;i<vec.size();++i)
    {
        if(vec[i]>max)
        {
            max=vec[i];
        }
    }

    return max;
}
double min(vector<double>vec)
{
    int min=vec[0];
    for (int i=1;i<vec.size();++i)
    {
        if(vec[i]<min)
        {
            min=vec[i];
        }
    }

    return min;
}
double maxInd(vector<double>vec)
{
    int max=0;
    for (int i=1;i<vec.size();++i)
    {
        if(vec[i]>max)
        {
            max=i;
        }
    }

    return max;
}
double minInd(vector<double>vec)
{
    int min=0;
    for (int i=1;i<vec.size();++i)
    {
        if(vec[i]<min)
        {
            min=i;
        }
    }
    return min;
}


T9DInterp::T9DInterp (vector<vector<double>> vecOfCanals, vector<double>gumus, vector<double>point, int optimal, int testingPointIndex)
{
    _vecOfCanals=vecOfCanals;
    _gumus=gumus;
    _point=point;
    _optimal=optimal;
    _testingPointIndex=testingPointIndex;
};

T9DInterp::~T9DInterp()
{

};

double T9DInterp::distFromPointsToVertex(vector<double> point, vector<double> a, vector<double> b, vector<double> c, vector<double> d, vector<double> e, vector<double> f, vector<double> g, vector<double> h, vector<double> i)
{
 return getDist(point,a)+getDist(point,b)+getDist(point,c)+getDist(point,d)+getDist(point,e)+getDist(point,f)+getDist(point,g)+getDist(point,h)+getDist(point,i);
}

double T9DInterp::getDist(vector<double>xVec,vector<double>xPoint)
{
    int dist=0;
    for (int i=0; i<int(xPoint.size());++i)
    {
           dist=dist+pow((xVec[i]-xPoint[i]),2);
    }

    return sqrt(dist);

};

void T9DInterp::findOptimalDesisionOfMin() //находим 10 вершин на минимальном расстоянии от нашей вершины
{
    double tmpDistForOne=0;

    //перебор по всем входным векторам каналов
    for (int i=0;i<int(_vecOfCanals.size());++i)
    {
        //проверка , что точка для которой ищем не входит в вектор каналов
        if(i == _testingPointIndex)
         {
            continue;
         }

          tmpDistForOne=getDist(_vecOfCanals[i],_point);

          //записываем первые n точек
          if(int(_optimalDesision.size())<_optimal)
          {
             distsForAll.push_back(tmpDistForOne);
             _optimalDesision.push_back(_vecOfCanals[i]);
             gumusOptimal.push_back(_gumus[i]);
          }
      else
      {
          //преобразовываем массив таким образом , чтобы в нем оставались точки максимально близкие к нашей
          if (tmpDistForOne>max(distsForAll))
          {
              distsForAll[maxInd(distsForAll)]=tmpDistForOne;
               _optimalDesision[maxInd(distsForAll)]=_vecOfCanals[i];
               gumusOptimal[maxInd(distsForAll)]=_gumus[i];
          }
      }

    }

}


double T9DInterp::SquareBig(vector<double> a, vector<double> b, vector<double> c, vector<double> d, vector<double> e, vector<double> f, vector<double> g, vector<double> h, vector<double> i)
{
    vector <vector<double>> massForGaus;

    massForGaus.push_back(make_vector(a,b));
    massForGaus.push_back(make_vector(a,c));
    massForGaus.push_back(make_vector(a,d));
    massForGaus.push_back(make_vector(a,e));
    massForGaus.push_back(make_vector(a,f));
    massForGaus.push_back(make_vector(a,g));
    massForGaus.push_back(make_vector(a,h));
    massForGaus.push_back(make_vector(a,i));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    return abs(DET);
}

double T9DInterp::SquareManySmall(vector<double> a, vector<double> b, vector<double> c, vector<double> d, vector<double> e, vector<double> f, vector<double> g, vector<double> h,vector<double>i, vector<double> point)
{
    vector <vector<double>> massForGaus;
    double summa=0;

    //БЕЗ 9
    massForGaus.push_back(make_vector(point,a));
    massForGaus.push_back(make_vector(point,b));
    massForGaus.push_back(make_vector(point,c));
    massForGaus.push_back(make_vector(point,d));
    massForGaus.push_back(make_vector(point,e));
    massForGaus.push_back(make_vector(point,f));
    massForGaus.push_back(make_vector(point,g));
    massForGaus.push_back(make_vector(point,h));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    summa+=abs(DET);

    massForGaus.clear();
    //БЕЗ 8
    massForGaus.push_back(make_vector(point,a));
    massForGaus.push_back(make_vector(point,b));
    massForGaus.push_back(make_vector(point,c));
    massForGaus.push_back(make_vector(point,d));
    massForGaus.push_back(make_vector(point,e));
    massForGaus.push_back(make_vector(point,f));
    massForGaus.push_back(make_vector(point,g));
    massForGaus.push_back(make_vector(point,i));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    summa+=abs(DET);
    massForGaus.clear();

    //БЕЗ 7
    massForGaus.push_back(make_vector(point,a));
    massForGaus.push_back(make_vector(point,b));
    massForGaus.push_back(make_vector(point,c));
    massForGaus.push_back(make_vector(point,d));
    massForGaus.push_back(make_vector(point,e));
    massForGaus.push_back(make_vector(point,f));
    massForGaus.push_back(make_vector(point,i));
    massForGaus.push_back(make_vector(point,h));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    summa+=abs(DET);
    massForGaus.clear();

    //БЕЗ 6
    massForGaus.push_back(make_vector(point,a));
    massForGaus.push_back(make_vector(point,b));
    massForGaus.push_back(make_vector(point,c));
    massForGaus.push_back(make_vector(point,d));
    massForGaus.push_back(make_vector(point,e));
    massForGaus.push_back(make_vector(point,i));
    massForGaus.push_back(make_vector(point,g));
    massForGaus.push_back(make_vector(point,h));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    summa+=abs(DET);
    massForGaus.clear();

    //БЕЗ 5
    massForGaus.push_back(make_vector(point,a));
    massForGaus.push_back(make_vector(point,b));
    massForGaus.push_back(make_vector(point,c));
    massForGaus.push_back(make_vector(point,d));
    massForGaus.push_back(make_vector(point,i));
    massForGaus.push_back(make_vector(point,f));
    massForGaus.push_back(make_vector(point,g));
    massForGaus.push_back(make_vector(point,h));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    summa+=abs(DET);
    massForGaus.clear();

    //БЕЗ 4
    massForGaus.push_back(make_vector(point,a));
    massForGaus.push_back(make_vector(point,b));
    massForGaus.push_back(make_vector(point,c));
    massForGaus.push_back(make_vector(point,i));
    massForGaus.push_back(make_vector(point,e));
    massForGaus.push_back(make_vector(point,f));
    massForGaus.push_back(make_vector(point,g));
    massForGaus.push_back(make_vector(point,h));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    summa+=abs(DET);
    massForGaus.clear();

    //БЕЗ 3
    massForGaus.push_back(make_vector(point,a));
    massForGaus.push_back(make_vector(point,b));
    massForGaus.push_back(make_vector(point,i));
    massForGaus.push_back(make_vector(point,d));
    massForGaus.push_back(make_vector(point,e));
    massForGaus.push_back(make_vector(point,f));
    massForGaus.push_back(make_vector(point,g));
    massForGaus.push_back(make_vector(point,h));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    summa+=abs(DET);
    massForGaus.clear();

    //БЕЗ 2
    massForGaus.push_back(make_vector(point,a));
    massForGaus.push_back(make_vector(point,i));
    massForGaus.push_back(make_vector(point,c));
    massForGaus.push_back(make_vector(point,d));
    massForGaus.push_back(make_vector(point,e));
    massForGaus.push_back(make_vector(point,f));
    massForGaus.push_back(make_vector(point,g));
    massForGaus.push_back(make_vector(point,h));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    summa+=abs(DET);
    massForGaus.clear();

    //БЕЗ 1
    massForGaus.push_back(make_vector(point,i));
    massForGaus.push_back(make_vector(point,b));
    massForGaus.push_back(make_vector(point,c));
    massForGaus.push_back(make_vector(point,d));
    massForGaus.push_back(make_vector(point,e));
    massForGaus.push_back(make_vector(point,f));
    massForGaus.push_back(make_vector(point,g));
    massForGaus.push_back(make_vector(point,h));

    setDET_1();

    Gaus(massForGaus,{0,0,0,0,0,0,0,0});
    summa+=abs(DET);
    massForGaus.clear();

    return summa;

}

vector<double> T9DInterp::make_vector(vector<double> start, vector<double> end)
{
    vector<double>result;

    if(start.size()==end.size())
    {
        for(int i=0;i<start.size();i++)
        {
            result.push_back(end[i]-start[i]);
        }
    }
    else
    {
        throw invalid_argument("Vectors have different sizes ! ");

    }

    return result;
}


//поиск трех точек внутри которых находится исходная точка//работает
bool T9DInterp:: pointInside()
{
    vector <double> R;
    vector<vector<double>>tmpKoef;
    vector<vector<vector<double>>>truKombination;
    vector<vector<double>>tmpGumus;

    for(int a=0;a<int(_optimalDesision.size());++a)
    {
        for(int b=a+1;b<int(_optimalDesision.size());++b)
        {
            for(int c=b+1;c<int(_optimalDesision.size());++c)
            {
                for(int d=c+1;d<int(_optimalDesision.size());++d)
                {
                    for(int e=d+1;e<int(_optimalDesision.size());++e)
                    {
                        for(int f=e+1;f<int(_optimalDesision.size());++f)
                        {
                            for(int g=f+1;g<int(_optimalDesision.size());++g)
                            {
                                for(int h=g+1;h<int(_optimalDesision.size());++h)
                                {
                                     for(int i=h+1;i<int(_optimalDesision.size());++i){


                                         double squareBig = SquareBig  (_optimalDesision[a],_optimalDesision[b],_optimalDesision[c],
                                                                        _optimalDesision[d],_optimalDesision[e],_optimalDesision[f],
                                                                        _optimalDesision[g],_optimalDesision[h],_optimalDesision[i]);
                                         double squareSmall = SquareManySmall(    _optimalDesision[a],_optimalDesision[b],_optimalDesision[c],
                                                                                  _optimalDesision[d],_optimalDesision[e],_optimalDesision[f],
                                                                                  _optimalDesision[g],_optimalDesision[h],_optimalDesision[i],_point);

                                         if(abs( squareSmall - squareBig )< squareBig*1e-9)
                                            {
                                                vector<vector<double>>tmpKoef;

                                                tmpKoef.push_back(_optimalDesision[a]);
                                                tmpKoef.push_back(_optimalDesision[b]);
                                                tmpKoef.push_back(_optimalDesision[c]);
                                                tmpKoef.push_back(_optimalDesision[d]);
                                                tmpKoef.push_back(_optimalDesision[e]);
                                                tmpKoef.push_back(_optimalDesision[f]);
                                                tmpKoef.push_back(_optimalDesision[g]);
                                                tmpKoef.push_back(_optimalDesision[h]);
                                                tmpKoef.push_back(_optimalDesision[i]);

                                                tmpGumus.push_back({gumusOptimal[a],gumusOptimal[b],gumusOptimal[c],
                                                                    gumusOptimal[d],gumusOptimal[e],gumusOptimal[f],
                                                                    gumusOptimal[g],gumusOptimal[h],gumusOptimal[i]});

                                                R.push_back(distFromPointsToVertex(_point,_optimalDesision[a],_optimalDesision[b],_optimalDesision[c],
                                                                                         _optimalDesision[d],_optimalDesision[e],_optimalDesision[f],
                                                                                         _optimalDesision[g],_optimalDesision[h],_optimalDesision[i]));
                                                truKombination.push_back(tmpKoef);
                                                //std::cout<<"HURAY!"<<endl;

                                            }
  //                                       std::cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<" "<<h<<" "<<i<<" \n";


                                       }//i
                                 }//h
                             }//g
                        }//f
                    }//e
                 }//d
            }//c
        }//b
    }//a


    if (truKombination.size()!=0)
    {
    pointsForFindingKoef=truKombination[minInd(R)];
    gumusKramer=tmpGumus[minInd(R)];

        return true;
    }
    else
    {
        std::cout<<"Point outside of any figure ! Take anather optimal dessision! "<<endl;
        return false;
    }




}

void T9DInterp::setDET_1()
{
    DET=1;
}

void T9DInterp:: Gaus(vector<vector<double>>matrix,vector<double > gumus)
    {
      endKoefOfMatr.clear();

    double deliteli=1;
    //прямой ход метода гаусса
        for (int k=0;k<matrix.size()-1;++k)
        {
            if(matrix[k][k]!=0) //взяли к-ю строку и к-й столбец
            {
                double d=matrix[k][k];
                deliteli=deliteli*matrix[k][k];
                for(int i=0;i<matrix[k].size();++i)
                {
                    if( matrix[k][i]==0)
                    {
                         matrix[k][i]= abs(double(matrix[k][i])/d);
                    }

                    else{
                    matrix[k][i]= double(matrix[k][i])/d;}

                }//привели строку к виду 1 ....n
                gumus[k]=gumus[k]/d;

                for(int m=k+1;m<matrix.size();++m)
                {
                    double koef=matrix[m][k]/matrix[k][k]*(-1);//лишнее но для понимания пусть так
                    for(int n=0;n<matrix[m].size();++n)//вычли из строки строку
                    {
                        matrix[m][n]=matrix[m][n]+koef*matrix[k][n];
                    }

                    gumus[m]=gumus[m]+koef*gumus[k];

                }//вычли из всех строк строку

            }


        }

    //обратный ход гаусса

        for (int k=matrix.size()-1;k>=0;k--)
        {
            if(matrix[k][k]!=0) //взяли к-ю строку и к-й столбец
            {
                double d=matrix[k][k];
                deliteli=deliteli*d;

                for(int i=0;i<matrix[k].size();++i)
                {
                    if( matrix[k][i]==0)
                    {
                         matrix[k][i]= abs(double(matrix[k][i])/d);
                    }

                    else{
                    matrix[k][i]= double(matrix[k][i])/d;
                    }

                }//привели строку к виду 1 ....n
                gumus[k]=gumus[k]/d;
               // std::cout<<endl;
                for(int m=k-1;m>=0;m--)
                {
                    double koef=matrix[m][k]/matrix[k][k]*(-1);


                    for(int n=0;n<matrix[m].size();++n)//вычли из строки строку
                    {

                        matrix[m][n]=matrix[m][n]+koef*matrix[k][n];
                    }

                    gumus[m]=gumus[m]+koef*gumus[k];


                }//вычли из всех строк строку


            }


        }

        DET=deliteli;
        for(int i=0;i<int(gumus.size());++i)
        {
            endKoefOfMatr.push_back(gumus[i]);
        }


 }

double T9DInterp:: getResult()
{
    double gumus=0;
    for(int i=0;i<_point.size();++i)
    {
        gumus=gumus+(endKoefOfMatr[i]/endKoefOfMatr[endKoefOfMatr.size()-1])*_point[i]*(-1);
    }
    gumus = gumus +(1./endKoefOfMatr[endKoefOfMatr.size()-1])*(-1);

   return gumus;
}

void T9DInterp::exec()
{
    //1 шаг - делаем выборку ближайших точек (по выбранному кол-ву)

    findOptimalDesisionOfMin();

    //2 шаг - ищем комбинацию точек в которую вписана наша (проверяем чтобы эта комбинация по расстоянию былы ближайшая)
    bool isPointInside = pointInside();
    if(!isPointInside){return;}

    //3 шаг - немного допиливаем напильником матрицу для крамера и вызываем крамера для вычисления коэффициентов матрицы    
    vector<double>vecSvCh;
    for (int i=0;i<pointsForFindingKoef.size();++i)
    {
        pointsForFindingKoef[i].push_back(gumusKramer[i]);
        vecSvCh.push_back(-1);

    }

    setDET_1();
    Gaus(pointsForFindingKoef,vecSvCh);

    //4 шаг - подставляем найденные коэффиценты и параметры точки в уравнение , выводим резульат

    std::cout<<"Значение гумуса равно "<<getResult()<<endl;

};
