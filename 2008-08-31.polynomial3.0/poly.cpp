/***************************************************************************************
* poly implementation
* example
*        5 <the degree of the first polynomial + 1>
*        3 2 0 3 1 <3x^4 + 2x^3 + 3x + 1>
***************************************************************************************/

#include "poly.h"
#include "term.h"

CPoly::CPoly()
{
    m_deg=0;
    m_poly.clear();
}

//copy constructor
CPoly::CPoly(CPoly& other)
{
    m_deg=other.GetDeg();
    vector<CTerm> poly=other.GetPoly();
    for(unsigned int i=0; i<poly.size(); i++)
        m_poly.push_back(poly.at(i));
}

//copy another polynomial into this
void CPoly::Copy(CPoly& other)
{
    m_deg=other.GetDeg();
    vector<CTerm> poly=other.GetPoly();
    for(unsigned int i=0; i<poly.size(); i++)
        m_poly.push_back(poly.at(i));
}

void CPoly::Clear()
{
    m_deg=0;
    m_poly.clear();
}

void CPoly::Sprod(CTerm& term)
{
    int nSize=m_poly.size();
    for(int i=0; i<nSize; i++)
        m_poly[i].Multiplication(term);
    m_deg+=term.GetDeg();
}

//display a polynomial
void CPoly::Display()
{
    //output the first term
    if(Size()>0)
        this->At(0).Display0();

    //output the rest terms
    for(int i=1; i<Size(); i++)
        this->At(i).Display1();
}

