#ifndef CPOLY_H
#define CPOLY_H
#include "Cshp.h"
#include <vector>


using namespace std;


class Cpoly:public Cshp
{
public:
    Cpoly();
    virtual ~Cpoly();
    virtual void setPartsVec(int iaParts[],int iNumParts);
    virtual void printData() override;
    virtual int getNumParts();
    virtual const vector<int> &getParts();

protected:

    vector<int> m_vec_iParts;

};

#endif // CPOLY_H
