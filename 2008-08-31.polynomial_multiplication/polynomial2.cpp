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

#define MAX_FILENAME_LENGTH 100

class CPolynomial
{
    char *m_sInputFile;		//input file name

    int m_nDegFirst;		//the degree of the first polynomial
    int m_nCountFirst;		//the term count of the first polynomial
    int *m_pCoefFirst;		//the coefficients of the first polynomial
    int *m_pDegFrist;		//the degree of each term

    int m_nDegSecond;		//the degree of the second polynomial
    int m_nCountSecond;		//the term count of the second polynomial
    int *m_pCoefSecond;		//the coefficients of the second polynomial
    int *m_pDegSecond;		//the degree of each term

    char *m_sOutputFile;	//output file name

    int m_nDegResult;		//the degree of the result polynomial
    int m_nCountResult;		//the term count of the result polynomial
    int *m_pCoefResult;		//the coefficients of the result polynomial
    int *m_pDegResult;		//the degree of each term

public:
    bool m_bSuccess;

public:
    CPolynomial(const char *inputfile,const char *outputfile);
    ~CPolynomial();

public:
    void Initialization();

    void Multiplication();
    void Multiplication(const int nADeg,const int nACount,const int *pACoef,const int *pADeg,
                        const int nBDeg,const int nBCount,const int *pBCoef,const int *pBDeg,const int &nLength,
                        int &nCDeg,int &nCCount,int *pCCoef,int *pCDeg);

    void Sprod(const int termdeg,const int termcoef,const int nBDeg,const int nBCount,const int *pBCoef,const int *pBDeg,
               int &nDDeg,int &nDCount,int *pDCoef,int *pDDeg);

    void Addition(const int nADeg,const int nACount,const int *pACoef,const int *pADeg,
                  const int nBDeg,const int nBCount,const int *pBCoef,const int *pBDeg,
                  int &nCDeg,int &nCCount,int *pCCoef,int *pCDeg);

    void WriteResult();
    void Display();
    void Display(int nCount,int *pCoef,int *pDeg);
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

    int coef;

    //read the degree and coefficients of the first polynomial
    fscanf(fp,"%d",&m_nDegFirst);
    m_nCountFirst=0;
    int *pCoefFirst=new int[m_nDegFirst];
    int *pDegFirst=new int[m_nDegFirst];
    m_nDegFirst--;
    for(int i=0; i<m_nDegFirst+1; i++)
    {
        fscanf(fp,"%d",&coef);
        if(coef)
        {
            *(pCoefFirst+m_nCountFirst)=coef;
            *(pDegFirst+m_nCountFirst++)=m_nDegFirst-i;
        }
    }
    m_pCoefFirst=new int[m_nCountFirst];
    memcpy(m_pCoefFirst,pCoefFirst,m_nCountFirst*sizeof(int));
    m_pDegFrist=new int[m_nCountFirst];
    memcpy(m_pDegFrist,pDegFirst,m_nCountFirst*sizeof(int));
    delete[] pCoefFirst;
    pCoefFirst=NULL;
    delete[] pDegFirst;
    pDegFirst=NULL;

    //read the degree and coefficients of the second polynomial
    fscanf(fp,"%d",&m_nDegSecond);
    m_nCountSecond=0;
    int *pCoefSecond=new int[m_nDegSecond];
    int *pDegSecond=new int[m_nDegSecond];
    m_nDegSecond--;
    for(int i=0; i<m_nDegSecond+1; i++)
    {
        fscanf(fp,"%d",&coef);
        if(coef)
        {
            *(pCoefSecond+m_nCountSecond)=coef;
            *(pDegSecond+m_nCountSecond++)=m_nDegSecond-i;
        }
    }
    m_pCoefSecond=new int[m_nCountSecond];
    memcpy(m_pCoefSecond,pCoefSecond,m_nCountSecond*sizeof(int));
    m_pDegSecond=new int[m_nCountSecond];
    memcpy(m_pDegSecond,pDegSecond,m_nCountSecond*sizeof(int));
    delete[] pCoefSecond;
    pCoefSecond=NULL;
    delete[] pDegSecond;
    pDegSecond=NULL;

    fclose(fp);

    //initialize the result info
    m_nDegResult=0;
    m_nCountResult=0;
    m_pCoefResult=NULL;
    m_pDegResult=NULL;

    m_bSuccess=true;
}

CPolynomial::~CPolynomial()
{
    if(m_pCoefFirst)
    {
        delete[] m_pCoefFirst;
        m_pCoefFirst=NULL;
    }
    if(m_pDegFrist)
    {
        delete[] m_pDegFrist;
        m_pDegFrist=NULL;
    }
    if(m_pCoefSecond)
    {
        delete[] m_pCoefSecond;
        m_pCoefSecond=NULL;
    }
    if (m_pDegSecond)
    {
        delete[] m_pDegSecond;
        m_pDegSecond=NULL;
    }
    if (m_pCoefResult)
    {
        delete[] m_pCoefResult;
        m_pCoefResult=NULL;
    }
    if (m_pDegResult)
    {
        delete[] m_pDegResult;
        m_pDegResult=NULL;
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
    m_nCountFirst=0;
    m_pCoefFirst=NULL;
    m_pDegFrist=NULL;

    m_nDegSecond=0;
    m_nCountSecond=0;
    m_pCoefSecond=NULL;
    m_pDegSecond=NULL;

    m_sOutputFile=NULL;

    m_nDegResult=0;
    m_nCountResult=0;
    m_pCoefResult=NULL;
    m_pDegResult=NULL;

    m_bSuccess=false;
}

void CPolynomial::Multiplication()
{
    if(m_nCountFirst==0 || m_nCountSecond==0)
    {
        m_nDegResult=0;
        m_pCoefResult=NULL;
        return;
    }

    //initialization
    int nLength=m_nDegFirst+m_nDegSecond+1;
    m_nDegResult=0;
    m_nCountResult=0;	//assume that the count is one space than degree
    m_pCoefResult=new int[nLength];
    memset(m_pCoefResult,0,nLength*sizeof(int));
    m_pDegResult=new int[nLength];
    memset(m_pDegResult,0,nLength*sizeof(int));

    //multiply the two polynomials
    Multiplication(m_nDegFirst,m_nCountFirst,m_pCoefFirst,m_pDegFrist,m_nDegSecond,m_nCountSecond,m_pCoefSecond,
                   m_pDegSecond,nLength,m_nDegResult,m_nCountResult,m_pCoefResult,m_pDegResult);
}

/************************************************************************
* polynomial multiplication: C(x) = A(x) * B(x)
* parameter:
*     nADeg  : degree of polynomial A
*     nACount: terms count of polynomial A
*     pACoef : coefficients of polynomial A
*     pADeg  : degrees of polynomial A
*     nBDeg  : degree of polynomial B
*     nBCount: terms count of polynomial B
*     pBCoef : coefficients of polynomial B
*     pBDeg  : degrees of polynomial B
*     nLength: the length of original C(x)
* return value:
*     nCDeg  : degree of polynomial C
*     nCCount: terms count of polynomial C
*     pCCoef : coefficients of polynomial C
*     pCDeg  : degrees of polynomial C
************************************************************************/
void CPolynomial::Multiplication(const int nADeg,const int nACount,const int *pACoef,const int *pADeg,
                                 const int nBDeg,const int nBCount,const int *pBCoef,const int *pBDeg,
                                 const int &nLength,int &nCDeg,int &nCCount,int *pCCoef,int *pCDeg)
{
    //create a temporarily space to store the result of production
    int nDDeg=0;
    int nDCount=nBCount;
    int *pDCoef=new int[nDCount];
    int *pDDeg=new int[nDCount];

    //create a temporarily space to store the previous C(x)
    int nEDeg=nCDeg;
    int nECount=nCCount;
    int *pECoef=new int[nLength];
    int *pEDeg=new int[nLength];

    //multiply the two polynomials
    int aterm=0;
    while(aterm<nACount)
    {
        //D(x) = term * B(x), term present each term of polynomial A
        int termdeg=*(pADeg+aterm);
        int termcoef=*(pACoef+aterm);

        //initialization
        memset(pDCoef,0,nDCount*sizeof(int));
        memset(pDDeg,0,nDCount*sizeof(int));

        //make production: D(x) = term * B(x)
        Sprod(termdeg,termcoef,nBDeg,nBCount,pBCoef,pBDeg,nDDeg,nDCount,pDCoef,pDDeg);

        //copy C(x) to E(x)
        nEDeg=nCDeg;
        nECount=nCCount;
        memcpy(pECoef,pCCoef,nLength*sizeof(int));
        memcpy(pEDeg,pCDeg,nLength*sizeof(int));
        //clear C(x)
        memset(pCCoef,0,nLength*sizeof(int));
        memset(pCDeg,0,nLength*sizeof(int));

        //make addition: C(x) = D(x) + E(x)
        Addition(nEDeg,nECount,pECoef,pEDeg,nDDeg,nDCount,pDCoef,pDDeg,nCDeg,nCCount,pCCoef,pCDeg);

        //next
        aterm++;
    }

    //delete the temporarily coefficient array
    delete[] pECoef;
    pECoef=NULL;
    delete[] pEDeg;
    pEDeg=NULL;

    delete[] pDCoef;
    pDCoef=NULL;
    delete[] pDDeg;
    pDDeg=NULL;
}

/************************************************************************
* polynomial Sprod: D(x) = term * B(x)
* parameter:
*     termdeg  : degree of term ("term" presents a term of a polynomial)
*     termcoef : coefficients of term
*     nBDeg  : degree of polynomial B
*     nBCount: terms count of polynomial B
*     pBCoef : coefficients of polynomial B
*     pBDeg  : degrees of polynomial B
* return value:
*     nDDeg : degree of polynomial D
*     nDCount: terms count of polynomial D
*     pDCoef: coefficients of polynomial D
*     pDDeg  : degrees of polynomial D
************************************************************************/
void CPolynomial::Sprod(const int termdeg,const int termcoef,
                        const int nBDeg,const int nBCount,const int *pBCoef,const int *pBDeg,
                        int &nDDeg,int &nDCount,int *pDCoef,int *pDDeg)
{
    nDDeg=termdeg+nBDeg;
    nDCount=nBCount;

    //multiply term and polynomial A
    for(int j=0; j<nBCount; j++)
    {
        int btermdeg=*(pBDeg+j);//nBDeg-j;
        int btermcoef=*(pBCoef+j);

        *(pDCoef+j)=termcoef*btermcoef;
        *(pDDeg+j)=termdeg+btermdeg;
    }
}

/************************************************************************
* polynomial addition: C(x) = A(x) + B(x)
* parameter:
*     nADeg  : degree of polynomial A
*     nACount: terms count of polynomial A
*     pACoef : coefficients of polynomial A
*     pADeg  : degrees of polynomial A
*     nBDeg  : degree of polynomial B
*     nBCount: terms count of polynomial B
*     pBCoef : coefficients of polynomial B
*     pBDeg  : degrees of polynomial B
*     nLength: the length of original C(x)
* return value:
*     nCDeg  : degree of polynomial C
*     nCCount: terms count of polynomial C
*     pCCoef : coefficients of polynomial C
*     pCDeg  : degrees of polynomial C
************************************************************************/
void CPolynomial::Addition(const int nADeg,const int nACount,const int *pACoef,const int *pADeg,
                           const int nBDeg,const int nBCount,const int *pBCoef,const int *pBDeg,
                           int &nCDeg,int &nCCount,int *pCCoef,int *pCDeg)
{
    if(nACount==0 && nBCount==0)
    {
        nCDeg=0;
        nCCount=0;
        return;
    }

    if(nACount==0)
    {
        nCDeg=nBDeg;
        nCCount=nBCount;
        memcpy(pCCoef,pBCoef,nBCount*sizeof(int));
        memcpy(pCDeg,pBDeg,nBCount*sizeof(int));
        return;
    }

    if(nBDeg==0)
    {
        nCDeg=nADeg;
        nCCount=nACount;
        memcpy(pCCoef,pACoef,nBCount*sizeof(int));
        memcpy(pCDeg,pADeg,nBCount*sizeof(int));
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
    while(aterm<nACount && bterm<nBCount)
    {
        atermdeg=*(pADeg+aterm);
        btermdeg=*(pBDeg+bterm);

        if(atermdeg==btermdeg)
        {
            *(pCCoef+cterm)=*(pACoef+aterm++)+*(pBCoef+bterm++);
            *(pCDeg+cterm++)=atermdeg;
        }
        else if(atermdeg<btermdeg)
        {
            *(pCCoef+cterm)=*(pBCoef+bterm++);
            *(pCDeg+cterm++)=btermdeg;
        }
        else
        {
            *(pCCoef+cterm)=*(pACoef+aterm++);
            *(pCDeg+cterm++)=atermdeg;
        }
    }

    //add remaining terms
    if(aterm<nACount)
    {
        while(aterm<nACount)
        {
            *(pCCoef+cterm)=*(pACoef+aterm);
            *(pCDeg+cterm++)=*(pADeg+aterm++);
        }
    }
    else if(bterm<nBCount)
    {
        while(bterm<nBCount)
        {
            *(pCCoef+cterm)=*(pBCoef+bterm);
            *(pCDeg+cterm++)=*(pBDeg+bterm++);
        }
    }
    nCCount=cterm;
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
    int ndeg=m_nDegResult;
    fprintf(fp,"%d\n",ndeg+1);

    int i=0;
    while(i<m_nCountResult)
    {
        if(*(m_pDegResult+i)!=ndeg)
            fprintf(fp,"0 ");
        else
            fprintf(fp,"%d  ",*(m_pCoefResult+i++));
        ndeg--;
    }

    fclose(fp);
}

//display all polynomials
void CPolynomial::Display()
{
    printf("\n  A(x) = ");
    Display(m_nCountFirst,m_pCoefFirst,m_pDegFrist);

    printf("\n  B(x) = ");
    Display(m_nCountSecond,m_pCoefSecond,m_pDegSecond);

    printf("\n\n  C(x) = A(x) * B(x)\n       = ");
    Display(m_nCountResult,m_pCoefResult,m_pDegResult);
    printf("\n");
}

/************************************************************************
* display a polynomial
* parameter:
*     nCount: terms count of this polynomial
*     pCoef : coefficients of this polynomial
*     pDeg  : degrees of this polynomial
************************************************************************/
void CPolynomial::Display(int nCount,int *pCoef,int *pDeg)
{
    //output the first term
    if(*(pDeg)==0)
    {
        printf("%d",*(pCoef));
    }
    else if(*(pDeg)==1)
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
            printf("x^%d",*(pDeg));
        else if(*(pCoef)==-1)
            printf("-x^%d",*(pDeg));
        else
            printf("%dx^%d",*(pCoef),*(pDeg));
    }

    for(int i=1; i<nCount; i++)
    {
        if(*(pCoef+i)>0)
        {
            if(*(pDeg+i)==0)
                printf(" + %d",*(pCoef+i));
            else if(*(pDeg+i)==1)
            {
                if(*(pCoef+i)==1)
                    printf(" + x");
                else
                    printf(" + %dx",*(pCoef+i));
            }
            else
            {
                if(*(pCoef+i)==1)
                    printf(" + x^%d",*(pDeg+i));
                else
                    printf(" + %dx^%d",*(pCoef+i),*(pDeg+i));
            }
        }
        else if(*(pCoef+i)<0)
        {
            if(*(pDeg+i)==0)
                printf(" - %d",-*(pCoef+i));
            else if(*(pDeg+i)==1)
            {
                if(*(pCoef+i)==-1)
                    printf(" - x");
                else
                    printf(" - %dx",-*(pCoef+i));
            }
            else
            {
                if(*(pCoef+i)==-1)
                    printf(" - x^%d",*(pDeg+i));
                else
                    printf(" - %dx^%d",-*(pCoef+i),*(pDeg+i));
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
    while(strcmp(sinput,"q")!=0)  //on Linux platform, it is strcasecmp; while Win32, it is stricmp
    {
        if(strcmp(sinput,"i")==0)   //on Win32, it is stricmp
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

