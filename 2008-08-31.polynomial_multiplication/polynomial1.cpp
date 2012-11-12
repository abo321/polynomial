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

#define MAX_FILENAME_LENGTH 100

class CPolynomial
{
    char *m_sInputFile;        //input file name

    int m_nDegFirst;        //the degree of the first polynomial
    int *m_pCoefFirst;        //the coefficients of the first polynomial

    int m_nDegSecond;        //the degree of the second polynomial
    int *m_pCoefSecond;        //the coefficients of the second polynomial

    char *m_sOutputFile;    //output file name

    int m_nDegResult;        //the degree of the result polynomial
    int *m_pCoefResult;        //the coefficients of the result polynomial

public:
    bool m_bSuccess;

public:
    CPolynomial(const char *inputfile,const char *outputfile);
    ~CPolynomial();

public:
    void Initialization();
    void Multiplication();

    void Multiplication(const int nADeg,const int *pACoef,const int nBDeg,const int *pBCoef,int *pCCoef);
    void Sprod(const int termdeg,const int termcoef,const int nBDeg,const int *pBCoef,int &nDDeg,int *pDCoef);
    void Addition(const int nADeg,const int *pACoef,const int nBDeg,const int *pBCoef,int &nCDeg,int *pCCoef);

    void WriteResult();
    void Display();
    void Display(int nDeg, int *pCoef);
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
        Initialization();
        m_bSuccess=false;
        return;
    }

    //record the input file name
    int nlen=strlen(inputfile);
    m_sInputFile=new char[nlen+1];
    strcpy(m_sInputFile,inputfile);

    //record the output file name
    nlen=strlen(outputfile);
    m_sOutputFile=new char[nlen+1];
    strcpy(m_sOutputFile,outputfile);

    //read the degree and coefficients of the first polynomial
    fscanf(fp,"%d",&m_nDegFirst);
    m_pCoefFirst=new int[m_nDegFirst];
    for(int i=0; i<m_nDegFirst; i++)
        fscanf(fp,"%d",m_pCoefFirst+i);
    m_nDegFirst--;

    //read the degree and coefficients of the second polynomial
    fscanf(fp,"%d",&m_nDegSecond);
    m_pCoefSecond=new int[m_nDegFirst];
    for(int j=0; j<m_nDegSecond; j++)
        fscanf(fp,"%d",m_pCoefSecond+j);
    m_nDegSecond--;

    fclose(fp);

    //initialize the result info
    m_nDegResult=0;
    m_pCoefResult=NULL;
}

CPolynomial::~CPolynomial()
{
    if(m_pCoefFirst)
    {
        delete[] m_pCoefFirst;
        m_pCoefFirst=NULL;
    }
    if(m_pCoefSecond)
    {
        delete[] m_pCoefSecond;
        m_pCoefSecond=NULL;
    }
    if (m_pCoefResult)
    {
        delete[] m_pCoefResult;
        m_pCoefResult=NULL;
    }
    if (m_sInputFile)
    {
        delete[] m_sInputFile;
        m_sInputFile=NULL;
    }
    if (m_sOutputFile)
    {
        delete[] m_sOutputFile;
        m_sOutputFile=NULL;
    }
}

void CPolynomial::Initialization()
{
    m_sInputFile=NULL;

    m_nDegFirst=0;
    m_pCoefFirst=NULL;

    m_nDegSecond=0;
    m_pCoefSecond=NULL;

    m_sOutputFile=NULL;

    m_nDegResult=0;
    m_pCoefResult=NULL;

    m_bSuccess=false;
}

void CPolynomial::Multiplication()
{
    if(m_nDegFirst==0 || m_nDegSecond==0)
    {
        m_nDegResult=0;
        m_pCoefResult=NULL;
        return;
    }

    //initialization
    m_nDegResult=m_nDegFirst+m_nDegSecond;
    m_pCoefResult=new int[m_nDegResult+1];
    memset(m_pCoefResult,0,(m_nDegResult+1)*sizeof(int));

    //multiply the two polynomials
    Multiplication(m_nDegFirst,m_pCoefFirst,m_nDegSecond,m_pCoefSecond,m_pCoefResult);
}

/************************************************************************
* polynomial multiplication: C(x) = A(x) * B(x)
* parameter:
*     nADeg : degree of polynomial A
*     pACoef: coefficients of polynomial A
*     nBDeg : degree of polynomial B
*     pBCoef: coefficients of polynomial B
* return value:
*     pCCoef: coefficients of polynomial C
************************************************************************/
void CPolynomial::Multiplication(const int nADeg,const int *pACoef,const int nBDeg,const int *pBCoef,int *pCCoef)
{
    //initialization
    int aterm=0;
    int nCDeg=0;
    int nDDeg=0, *pDCoef=NULL;

    //multiply the two polynomials
    while(aterm<=nADeg)
    {
        //D(x) = term * B(x), term present each term of polynomial A
        int termdeg=nADeg-aterm;
        int termcoef=*(pACoef+aterm);

        //if the coefficient of term is zero, then the result is zero
        if(termcoef==0)
        {
            nDDeg=0;
            pDCoef=NULL;
        }
        else
        {
            //get the new degree of the production and initialize the coefficient array
            nDDeg=termdeg+nBDeg;
            pDCoef=new int[nDDeg+1];
            memset(pDCoef,0,(nDDeg+1)*sizeof(int));

            //make production
            Sprod(termdeg,termcoef,nBDeg,pBCoef,nDDeg,pDCoef);
        }

        //C(x) = C(x) + D(x)
        Addition(nCDeg,pCCoef,nDDeg,pDCoef,nCDeg,pCCoef);

        //next
        aterm++;

        //delete the temporarily coefficient array
        delete[] pDCoef;
        pDCoef=NULL;
    }
}

/************************************************************************
* polynomial Sprod: D(x) = term * B(x)
* parameter:
*     termdeg  : degree of term ("term" presents a term of a polynomial)
*     termcoef : coefficients of term
*     nBDeg : degree of polynomial B
*     pBCoef: coefficients of polynomial B
* return value:
*     nDDeg : degree of polynomial D
*     pDCoef: coefficients of polynomial D
************************************************************************/
void CPolynomial::Sprod(const int termdeg,const int termcoef,const int nBDeg,const int *pBCoef,int &nDDeg,int *pDCoef)
{
    //multiply term and polynomial A
    for(int j=0; j<=nBDeg; j++)
    {
        int btermdeg=nBDeg-j;
        int btermcoef=*(pBCoef+j);

        int dtermdeg=termdeg+btermdeg;
        int dtermcoef=termcoef*btermcoef;

        *(pDCoef+nDDeg-dtermdeg)=dtermcoef;
    }
}

/************************************************************************
* polynomial addition: C(x) = A(x) + B(x)
* parameter:
*     nADeg : degree of polynomial A
*     pACoef: coefficients of polynomial A
*     nBDeg : degree of polynomial B
*     pBCoef: coefficients of polynomial B
* return value:
*     nCDeg : degree of polynomial C
*     pCCoef: coefficients of polynomial C
************************************************************************/
void CPolynomial::Addition(const int nADeg,const int *pACoef,const int nBDeg,const int *pBCoef,int &nCDeg,int *pCCoef)
{
    if(nADeg==0 && nBDeg==0)
    {
        nCDeg=0;
        pCCoef=NULL;
        return;
    }

    if(nADeg==0)
    {
        nCDeg=nBDeg;
        memcpy(pCCoef,pBCoef,(nCDeg+1)*sizeof(int));
        return;
    }

    if(nBDeg==0)
    {
        nCDeg=nADeg;
        memcpy(pCCoef,pACoef,(nCDeg+1)*sizeof(int));
        return;
    }

    //initialization
    int aterm=0,bterm=0,cterm=0;
    int atermdeg,btermdeg;

    if(nADeg>=nBDeg)
        nCDeg=nADeg;
    else
        nCDeg=nBDeg;

    //add the two polynomials
    while(aterm<=nADeg && bterm<=nBDeg)
    {
        atermdeg=nADeg-aterm;    //degree of aterm
        btermdeg=nBDeg-bterm;    //degree of bterm

        if(atermdeg==btermdeg)
            *(pCCoef+cterm++)=*(pACoef+aterm++)+*(pBCoef+bterm++);
        else if(atermdeg<btermdeg)
            *(pCCoef+cterm++)=*(pBCoef+bterm++);
        else
            *(pCCoef+cterm++)=*(pACoef+aterm++);
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
    fprintf(fp,"%d\n",m_nDegResult+1);
    for(int i=0; i<m_nDegResult+1; i++)
        fprintf(fp,"%d  ",*(m_pCoefResult+i));

    fclose(fp);
}

//display all polynomials
void CPolynomial::Display()
{
    printf("\n  A(x) = ");
    Display(m_nDegFirst,m_pCoefFirst);

    printf("\n  B(x) = ");
    Display(m_nDegSecond,m_pCoefSecond);

    printf("\n\n  C(x) = A(x) * B(x)\n       = ");
    Display(m_nDegResult,m_pCoefResult);
    printf("\n");
}

//display a polynomial
void CPolynomial::Display(int nDeg, int *pCoef)
{
    //output the first term
    if(nDeg==0)
    {
        printf("%d",*(pCoef));
    }
    else if(nDeg==1)
    {
        if(*(pCoef)==1)
            printf("x");
        else if(*(pCoef)==-1)
            printf("-x");
        else
            printf("%dx",*(pCoef));
    }
    else
    {
        if(*(pCoef)==1)
            printf("x^%d",nDeg);
        else if(*(pCoef)==-1)
            printf("-x^%d",nDeg);
        else
            printf("%dx^%d",*(pCoef),nDeg);
    }

    for(int i=1; i<nDeg+1; i++)
    {
        if(*(pCoef+i)>0)
        {
            if(nDeg-i==0)
                printf(" + %d",*(pCoef+i));
            else if(nDeg-i==1)
            {
                if(*(pCoef+i)==1)
                    printf(" + x");
                else
                    printf(" + %dx",*(pCoef+i));
            }
            else
            {
                if(*(pCoef+i)==1)
                    printf(" + x^%d",nDeg-i);
                else
                    printf(" + %dx^%d",*(pCoef+i),nDeg-i);
            }
        }
        else if(*(pCoef+i)<0)
        {
            if(nDeg-i==0)
                printf(" - %d",-*(pCoef+i));
            else if(nDeg-i==1)
            {
                if(*(pCoef+i)==-1)
                    printf(" - x");
                else
                    printf(" - %dx",-*(pCoef+i));
            }
            else
            {
                if(*(pCoef+i)==-1)
                    printf(" - x^%d",nDeg-i);
                else
                    printf(" - %dx^%d",-*(pCoef+i),nDeg-i);
            }
        }
    }
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

