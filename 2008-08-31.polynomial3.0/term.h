/***************************************************************************************
* term define
* example: 3x^6
*          3 represents the coefficient of this term
*          6 represents the degree of this term
***************************************************************************************/

#ifndef _TERM_HEADER_
#define _TERM_HEADER_

class CTerm
{
    int m_coef;	//coefficient
    int m_deg;	//degree

public:	//constructor and destructor
    CTerm(int coef = 0,int deg = 0): m_coef(coef), m_deg(deg) {}
    CTerm(const CTerm& term): m_coef(term.m_coef), m_deg(term.m_deg) {}
    ~CTerm() {}

    CTerm& operator=(const CTerm& other);

    //access method
    int GetCoef() { return m_coef; }
    int GetDeg() { return m_deg; }

public:	//operation method
    void Multiplication(const CTerm& term);

    void Display0();
    void Display1();
};

#endif
