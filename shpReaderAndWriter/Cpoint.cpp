#include "Cpoint.h"

Cpoint::Cpoint()
{

}

Cpoint::~Cpoint()
{

}

void Cpoint::setOnePointVec(structPoint &CtempPoint)
{
    m_vec_Cpoints.push_back(CtempPoint);
}

void Cpoint::printData()
{
    cout<<"box: "<<endl;
    for(int i=0;i<4;i++)
    {
        cout<<m_adBox[i]<<"  ";
    }
    cout<<endl<<"points: "<<endl;
    for(int i=0;i<m_vec_Cpoints.size();i++)
    {
        cout<<m_vec_Cpoints[i].x<<"  "<<m_vec_Cpoints[i].y<<endl;
    }
    cout<<endl;

}

const structPoint &Cpoint::getPointData()
{
    return m_vec_Cpoints[0];
}
