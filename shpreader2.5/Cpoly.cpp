#include "Cpoly.h"

Cpoly::Cpoly()
{

}

Cpoly::~Cpoly()
{

}

void Cpoly::setPartsVec(int iaParts[],int iNumParts)
{
    for(int i=0;i<iNumParts;i++)
    {
        m_vec_iParts.push_back(iaParts[i]);
    }
}

void Cpoly::printData()
{
    cout<<"box: "<<endl;
    for(int i=0;i<4;i++)
    {
        cout<<m_adBox[i]<<"  ";
    }
    cout<<"parts: "<<endl;
    for(int i=0;i<m_vec_iParts.size();i++)
    {
        cout<<m_vec_iParts[i]<<"  ";
    }

    cout<<endl<<"points: "<<endl;
    for(int i=0;i<m_vec_Cpoints.size();i++)
    {
        cout<<m_vec_Cpoints[i].x<<"  "<<m_vec_Cpoints[i].y<<endl;
    }
    cout<<endl;
}

int Cpoly::getNumParts()
{
    return m_vec_iParts.size();
}

const vector<int> &Cpoly::getParts()
{
    return m_vec_iParts;
}
