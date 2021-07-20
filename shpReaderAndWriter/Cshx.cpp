#include "Cshx.h"

Cshx::Cshx()
{

}

Cshx::~Cshx()
{

}

void Cshx::setAttributeValue(int iOffset, int iContentLength)
{
    m_iOffset=iOffset;
    m_iContentLength=iContentLength;
}

int Cshx::getOffset()
{
    return m_iOffset;
}

int Cshx::getContentLength()
{
    return m_iContentLength;
}
