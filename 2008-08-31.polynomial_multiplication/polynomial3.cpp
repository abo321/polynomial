/***************************************************************************************
* polynomial multiplication (visual studio 2005)
* input: inputFileName, representing two polynomials as the following format
*        5 <the degree of the first polynomial + 1>
*        3 2 0 3 1 <3x^4 + 2x^3 + 3x + 1>
*        4 <the degree of the second polynomial + 1>
*        2 3 1 4 <2x^3 + 3x^2 + x + 4>
* output: outputFileName, representing the resulting polynomial from the multiplication
of the two polynomials specified in the input file
*        8 <the degree of the resulting polynomial + 1>
*        6 13 9 20 19 6 13 4 <6x^7+13x^6+9x^5+20x^4+19x^3+6x^2 +13x + 4>
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

#define MAX_FILENAME_LENGTH 100

//////////////////////////////////////////////////////////////////////////
class CTerm
{
    int m_coef;	//coefficient
    int m_deg;	//degree

public:	//constructor and destructor
    CTerm(int coef = 0,int deg = 0): m_coef(coef), m_deg(deg) {}
    CTerm(const CTerm& term): m_coef(term.m_coef), m_deg(term.m_deg) {}
    ~CTerm() {}

public:
    CTerm& operator=(const CTerm& other);

public:	//access method
    int GetCoef() {return m_coef;}
    int GetDeg() {return m_deg;}

public:	//operation method
    void Multiplication(const CTerm& term);

    void Display0();
    void Display1();
};

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
//////////////////////////////////////////////////////////////////////////

class CPoly
{
    int m_deg;		//degree of this polynomial
    vector<CTerm> m_poly;

public:
    CPoly();
    CPoly(CPoly& poly);
    ~CPoly() {}

public:
    int Size() {return m_poly.size();}

    int GetDeg() {return m_deg; }
    void SetDeg(int deg) {m_deg=deg; }

    vector<CTerm> GetPoly() {return m_poly; }

    CTerm At(int index) { return m_poly[index]; }
    void Append(CTerm term) { m_poly.push_back(term); }

    void Copy(CPoly& poly);

    void Clear();

public:
    void Sprod(CTerm& term);

    void Multiplication(const CPoly& other);

    void Display();
};

CPoly::CPoly(): m_deg(0)
{
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
//////////////////////////////////////////////////////////////////////////

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

//show the command menu
void show_menu()
{
    printf("---------------------------------------------\n");
    printf("input command to test the program\n");
    printf("   i or I : input filename to test\n");
    printf("   q or Q : quit\n");
    printf("---------------------------------------------\n");
    printf("$ input command >");
}

int main()
{
    char sinput[10];
    char sinputfile[MAX_FILENAME_LENGTH];
    char soutputfile[MAX_FILENAME_LENGTH];

    show_menu();

    scanf("%s",sinput);
    while(strcmp(sinput,"q")!=0)
    {
        if(strcmp(sinput,"i")==0)
        {
            printf("  input file name : ");
            scanf("%s",sinputfile);

            printf("  output file name: ");
            scanf("%s",soutputfile);

            //polynomial multiplication
            CPolynomial poly(sinputfile,soutputfile);
            if(poly.m_bSuccess)
            {
                poly.Multiplication();
                poly.WriteResult();
                poly.Display();
            }
        }

        //input a command
        printf("\n$ input command >");
        scanf("%s",sinput);
    }

    return 0;
}

