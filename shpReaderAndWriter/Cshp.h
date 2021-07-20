#ifndef CSHP_H
#define CSHP_H
#include <iostream>
#include <vector>
using namespace std;
struct structPoint   //点结构体
{
    double x;
    double y;
};

class Cshp
{
public:
    Cshp();
    virtual ~Cshp();
    virtual void setPointsVec(structPoint aCpoint[],int iNumPoints);
    virtual void setBox(double adBox[]);
    virtual int getNumPoints();
    virtual void printData();
    virtual const vector<structPoint> &getPoints();
    virtual const double * getBox();
protected:
    double m_adBox[4];     //每个shape记录的边界框
    vector<structPoint> m_vec_Cpoints;//点集


};

#endif // CSHP_H
