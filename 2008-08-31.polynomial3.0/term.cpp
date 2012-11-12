/***************************************************************************************
* term implementation
* example: 3x^6
*          3 represents the coefficient of this term
*          6 represents the degree of this term
***************************************************************************************/

#include "term.h"
#include <stdio.h>

CTerm& CTerm::operator =(const CTerm& other)
{
    m_coef=other.m_coef;
    m_deg=other.m_deg;
    return *this;
}

void CTerm::Multiplication(const CTerm& term)
{
    m_coef*=term.m_coef;
    m_deg+=term.m_deg;
}

//display the first term of a polynomial
void CTerm::Display0()
{
    if(m_deg==0)
    {
        printf("%d",m_coef);
    }
    else if(m_deg==1)
    {
        if(m_coef==1)
            printf("x");
        else if(m_coef==-1)
            printf("-x");
        else
            printf("%dx",m_coef);
    }
    else
    {
        if(m_coef==1)
            printf("x^%d",m_deg);
        else if(m_coef==-1)
            printf("-x^%d",m_deg);
        else
            printf("%dx^%d",m_coef,m_deg);
    }
}

//display other terms of a polynomial
void CTerm::Display1()
{
    if(m_coef>0)
    {
        if(m_deg==0)
            printf(" + %d",m_coef);
        else if(m_deg==1)
        {
            if(m_coef==1)
                printf(" + x");
            else
                printf(" + %dx",m_coef);
        }
        else
        {
            if(m_coef==1)
                printf(" + x^%d",m_deg);
            else
                printf(" + %dx^%d",m_coef,m_deg);
        }
    }
    else if(m_coef<0)
    {
        if(m_deg==0)
            printf(" - %d",-m_coef);
        else if(m_deg==1)
        {
            if(m_coef==-1)
                printf(" - x");
            else
                printf(" - %dx",-m_coef);
        }
        else
        {
            if(m_coef==-1)
                printf(" - x^%d",m_deg);
            else
                printf(" - %dx^%d",-m_coef,m_deg);
        }
    }
}
