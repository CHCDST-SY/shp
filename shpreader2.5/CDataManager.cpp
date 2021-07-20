#include "CDataManager.h"

CDataManager::CDataManager()
{

}
CDataManager::~CDataManager()
{

}

void CDataManager::setShxHeadData(shpxfilehead &Chead)
{
        m_CshpAndShxHead.ifilenum=Chead.ifilenum;
        for(int i=0;i<5;i++)
        {
            m_CshpAndShxHead.iunused[i]=Chead.iunused[i];
        }
        m_CshpAndShxHead.ishxfile_length=Chead.ishxfile_length;

        m_CshpAndShxHead.iversion=Chead.iversion;
        m_CshpAndShxHead.ishape_type=Chead.ishape_type;
        for(int i=0;i<8;i++)
        {
           m_CshpAndShxHead.boundBox[i]=Chead.boundBox[i];
        }
}

void CDataManager::setShpFileLength(int iFileLength)
{
    m_CshpAndShxHead.ishpfile_length=iFileLength;
}


void CDataManager::obtainShxPointer(Cshx *pShx)
{
    m_vec_shxRecord.push_back(pShx);
}

void CDataManager::obtainShpPointer(Cshp *pShp)
{
    m_vec_shpRecord.push_back(pShp);
}



int CDataManager::getShxFileLength()
{
    return m_CshpAndShxHead.ishxfile_length;
}

int CDataManager::getShpRecordNum()
{
    int iRecordNum=(m_CshpAndShxHead.ishxfile_length*2-100)/8;
    return iRecordNum;
}

int CDataManager::getShpFileLength()
{
    return m_CshpAndShxHead.ishpfile_length;
}

int CDataManager::getShapeType()
{
    return m_CshpAndShxHead.ishape_type;
}

const shpxfilehead &CDataManager::getShpxHead()
{
    return m_CshpAndShxHead;
}

const vector<Cshx *> &CDataManager::getShxRecord()
{
    return m_vec_shxRecord;
}

 Cshp *CDataManager::getShpRecord(int i)
{
     return m_vec_shpRecord[i];
}

void CDataManager::printShpxData()
{
    int i=0;
    while (i<m_vec_shpRecord.size()) {
        m_vec_shpRecord[i]->printData();
        i++;
    }
    i=0;
}

Cshx *CDataManager::operator[](int i)
{
    return m_vec_shxRecord[i];
}


