/***************************************************************************************
* poly define
* example
*        5 <the degree of the first polynomial + 1>
*        3 2 0 3 1 <3x^4 + 2x^3 + 3x + 1>
***************************************************************************************/

#ifndef _POLY_HEADER_
#define _POLY_HEADER_

#include <vector>

class CTerm;

using namespace std;

class CPoly
{
    int m_deg;		//degree of this polynomial
    vector<CTerm> m_poly;	//store all terms of the polynomial

public:
    CPoly();
    CPoly(CPoly& poly);
    ~CPoly() {}

public:	//access function
    int Size() {return m_poly.size();}

    int GetDeg() {return m_deg;}
    void SetDeg(int deg) {m_deg=deg; }

    vector<CTerm>& GetPoly() {return m_poly;}

    CTerm& At(int index) { return m_poly[index]; }
    void Append(CTerm& term) {m_poly.push_back(term); }

    void Copy(CPoly& poly);

    void Clear();

public:
    void Sprod(CTerm& term);
    void Multiplication(const CPoly& other);

    void Display();
};

#endif

