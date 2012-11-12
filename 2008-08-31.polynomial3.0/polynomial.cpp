/***************************************************************************************
* polynomial implementation
*     addition
*     multiplication
***************************************************************************************/

#include "polynomial.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include "term.h"


/************************************************************************
* constructor : initialize the polynomials
* parameter:
*     inputfile : input file name including two polynomials
*     outputfile: result file name of multiplication
************************************************************************/
CPolynomial::CPolynomial(const char *inputfile,const char *outputfile)
{
    FILE *fp=fopen(inputfile,"r");
    if(fp==NULL)
    {
        printf("\n  can not open file!\n");
        m_bSuccess=false;
        return;
    }

    //save the input file name
    int nlen=strlen(inputfile);
    m_sInputFile=new char[nlen+1];
    strcpy(m_sInputFile,inputfile);

    //save the output file name
    nlen=strlen(outputfile);
    m_sOutputFile=new char[nlen+1];
    strcpy(m_sOutputFile,outputfile);

    int coef;
    int ncount,ndeg;

    //read the degree and coefficients of the first polynomial
    fscanf(fp,"%d",&ncount);
    ndeg=ncount-1;
    for(int i=0; i<ncount; i++)
    {
        fscanf(fp,"%d",&coef);
        if(coef)
        {
            CTerm term(coef,ndeg-i);
            m_apoly.Append(term);
        }
    }
    m_apoly.SetDeg(ndeg);

    //read the degree and coefficients of the second polynomial
    fscanf(fp,"%d",&ncount);
    ndeg=ncount-1;
    for(int i=0; i<ncount; i++)
    {
        fscanf(fp,"%d",&coef);
        if(coef)
        {
            CTerm term(coef,ndeg-i);
            m_bpoly.Append(term);
        }
    }
    m_bpoly.SetDeg(ndeg);

    fclose(fp);

    m_cpoly.Clear();
    m_bSuccess=true;
}

CPolynomial::~CPolynomial()
{
    if(m_sInputFile)
    {
        delete[] m_sInputFile;
        m_sInputFile=NULL;
    }

    if(m_sOutputFile)
    {
        delete[] m_sOutputFile;
        m_sOutputFile=NULL;
    }
}

/************************************************************************
* polynomial multiplication: C(x) = A(x) + B(x)
* parameter:
*     apoly: A(x)
*     bpoly: B(x)
*     cpoly: C(x)
************************************************************************/
void CPolynomial::Addition(CPoly& apoly,CPoly& bpoly,CPoly& cpoly)
{
    int nACount=apoly.Size();
    int nBCount=bpoly.Size();	//poly.m_poly.size();

    if(nACount==0)
    {
        cpoly.Copy(bpoly);
        return;
    }
    if(nBCount==0)
    {
        cpoly.Copy(apoly);
        return;
    }

    //initialization
    int ai=0,bi=0;

    int adeg=apoly.GetDeg();
    int bdeg=bpoly.GetDeg();
    if(adeg<bdeg)
        cpoly.SetDeg(bdeg);
    else
        cpoly.SetDeg(adeg);

    //add the two polynomials
    while(ai<nACount && bi<nBCount)
    {
        CTerm aterm=apoly.At(ai);
        CTerm bterm=bpoly.At(bi);

        if(aterm.GetDeg()==bterm.GetDeg())
        {
            CTerm cterm(aterm.GetCoef()+bterm.GetCoef(),aterm.GetDeg());
            cpoly.Append(cterm);
            ai++;
            bi++;
        }
        else if(aterm.GetDeg()<bterm.GetDeg())
        {
            CTerm cterm(bterm);
            cpoly.Append(cterm);
            bi++;
        }
        else
        {
            CTerm cterm(aterm);
            cpoly.Append(cterm);
            ai++;
        }
    }

    //add remaining terms
    if(ai<nACount)
    {
        while(ai<nACount)
        {
            CTerm cterm(apoly.At(ai));
            cpoly.Append(cterm);
            ai++;
        }
    }
    else if(bi<nBCount)
    {
        while(bi<nBCount)
        {
            CTerm cterm(bpoly.At(bi));
            cpoly.Append(cterm);
            bi++;
        }
    }
}

void CPolynomial::Multiplication()
{
    if(m_apoly.Size()==0 || m_bpoly.Size()==0)
        return;

    //multiply the two polynomials
    Multiplication(m_apoly,m_bpoly,m_cpoly);
}

/************************************************************************
* polynomial multiplication: C(x) = A(x) * B(x)
* parameter:
*     apoly: A(x)
*     bpoly: B(x)
*     cpoly: C(x)
************************************************************************/
void CPolynomial::Multiplication(CPoly& apoly,CPoly& bpoly,CPoly& cpoly)
{
    //A(x) * B(x)
    int ai=0;
    while(ai<apoly.Size())
    {
        CTerm term=apoly.At(ai);

        //D(x) = term * B(x)
        CPoly dpoly(bpoly);
        dpoly.Sprod(term);

        //make addition: C(x) = D(x) + E(x)
        CPoly epoly(cpoly);
        cpoly.Clear();
        Addition(dpoly,epoly,cpoly);

        //next
        ai++;
    }
}

//write the resulting polynomial to file
void CPolynomial::WriteResult()
{
    FILE *fp=fopen(m_sOutputFile,"w");
    if(fp==NULL)
    {
        printf("can not write file!");
        return;
    }

    //output the degree and coefficients of the resulting polynomial
    int ndeg=m_cpoly.GetDeg();
    fprintf(fp,"%d\n",ndeg+1);

    int i=0;
    while(i<m_cpoly.Size())
    {
        if(m_cpoly.At(i).GetDeg()!=ndeg)
            fprintf(fp,"0 ");
        else
            fprintf(fp,"%d  ",m_cpoly.At(i++).GetCoef());
        ndeg--;
    }

    fclose(fp);
}

//display all polynomials
void CPolynomial::Display()
{
    printf("\n  A(x) = ");
    m_apoly.Display();

    printf("\n  B(x) = ");
    m_bpoly.Display();

    printf("\n\n  C(x) = A(x) * B(x)\n       = ");
    m_cpoly.Display();
    printf("\n");
}
