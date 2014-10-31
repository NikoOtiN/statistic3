#include <QVector>
#include <iostream>
#include <chrono>
#include <random>

using namespace std;
double sum(QVector<double> v, int el, int size);
QVector<double> simple_moving_averge(int n, QVector<double> v);
QVector<double> createX(int n,int start=0);
QVector<double> createSample(int n);
QVector<double> simple_moving_averge_v2(int n, QVector<double> v);

QVector<double> simple_moving_averge(int n, QVector<double> v)
{
    QVector<double> res;
    double x = 0;
    for(int i = 0; i <= v.size()-n; i++)
    {
        x = sum(v,i,n)/n;
        res.push_back(x);
    }
    return res;
}


double sum(QVector<double> v, int el, int size)
{
    if(size<0||(size+el)>v.size())
    {
    }
    auto end = v.begin()+el+size;
    double sum = 0;
    for(auto it = v.begin()+el;it < end; it++)
    {
        sum += *it;
    }
    return sum;
}

QVector<double> createSample(int n)
{
   unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine generator(seed1);
   std::normal_distribution<double> distribution(5.0,2.0);
    QVector<double> sample;
    for(int i = 0; i < n ; i++)
    {
        sample.push_back(distribution(generator));
    }
    return sample;
}

QVector<double> simple_moving_averge_v2(int n, QVector<double> v)
{
    QVector<double> res;
    int j = (n-1)/2;
    double sum = 0;
    for(int i = 0; i<n; i++)
    {
        sum += v.at(i);
    }
    double x1 = sum/n;
    res.push_back(x1);
    double tmp = 0;
    for(int i = 1; i<v.size()-j-1;i++)
    {
        tmp = res.at(i-1) + ((v.at(i+j)-v.at(i-j+1))/n);
        res.push_back(tmp);
    }
    return res;
}

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

