/***************************************************************************************
* polynomial define
***************************************************************************************/

#ifndef _POLYNOMIAL_HEADER_
#define _POLYNOMIAL_HEADER_

#include "poly.h"

class CPolynomial
{
    CPoly m_apoly;
    CPoly m_bpoly;
    CPoly m_cpoly;	//the resulting polynomial

    char *m_sInputFile;
    char *m_sOutputFile;

public:
    bool m_bSuccess;

    CPolynomial(const char *inputfile,const char *outputfile);
    ~CPolynomial();

public:
    void Addition(CPoly& apoly,CPoly& bpoly,CPoly& cpoly);
    void Multiplication();
    void Multiplication(CPoly& apoly,CPoly& bpoly,CPoly& cpoly);

    void WriteResult();
    void Display();
};

#endif
