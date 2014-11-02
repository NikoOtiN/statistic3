#include <QVector>
#include <iostream>
#include <chrono>
#include <random>

using namespace std;
double sum(QVector<double> v, int el, int size);
QVector<double> createX(int n,int start=0);
QVector<double> createSample(int n, double expect, double variation);

//Создание вектора наблюдений
QVector<double> createSample(int n, double expect, double variation)
{
   unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine generator(seed1);
   std::normal_distribution<double> distribution(expect,variation);
    QVector<double> sample;
    for(int i = 0; i < n ; i++)
    {
        sample.push_back(distribution(generator));
    }
    return sample;
}

//Подсчет простого скользящего среднего.
QVector<double> simple_moving_averge_v3(int n, QVector<double> v)
{
    QVector<double> res;
    double sum = 0;
    int j = (n-1)/2;
    for(int t= j; t < v.size()-j; t++ )
    {
        sum =0;
        for(int i = t-j; i<=t+j; i++)
        {
            sum+=v.at(i);
        }
        res.push_back(sum/n);
    }
    return res;
}

//Подсчет взвешенного скользящего среднего.
QVector<double> weighted_moving_average(QVector<double> v)
{
    QVector<double> res;
    double sum = 0;
    for(int i = 2;i< v.size()-2;i++)
    {
        sum = -3*v.at(i-2) + 12*v.at(i-1) + 17*v.at(i) + 12*v.at(i+1) - 3*v.at(i+2);
        sum = sum/36;
        res.push_back(sum);
    }
    return res;
}

QVector<double> createX(int n,int start)
{
    QVector<double> x;
    for(int i = start;i<start+n; i++)
    {
        x.push_back(i);
    }
    return x;
}

