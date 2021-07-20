#include "Cshp.h"

Cshp::Cshp()
{

}

Cshp::~Cshp()
{

}

void Cshp::setPointsVec(structPoint aCpoint[], int iNumPoints)
{
    for(int i=0;i<iNumPoints;i++)
    {
        m_vec_Cpoints.push_back(aCpoint[i]);
    }
}

void Cshp::setBox(double adBox[])
{
    for(int i=0;i<4;i++)
    {
        m_adBox[i]=adBox[i];
    }
}

int Cshp::getNumPoints()
{
    return m_vec_Cpoints.size();
}

void Cshp::printData()
{
    cout<<"box: "<<endl;
    for(int i=0;i<4;i++)
    {
        cout<<m_adBox[i]<<"  ";
    }
    cout<<endl<<"points: "<<endl;
    for(int i=0;i<m_vec_Cpoints.size();i++)
    {
        cout<<m_vec_Cpoints[i].x<<"  "<<m_vec_Cpoints[i].y;
    }
    cout<<endl;
}

const vector<structPoint> &Cshp::getPoints()
{
    return m_vec_Cpoints;
}

const double *Cshp::getBox()
{
    return m_adBox;
}
