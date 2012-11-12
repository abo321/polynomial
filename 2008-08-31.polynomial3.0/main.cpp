/***************************************************************************************
* main program (visual studio 2005)
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
#include "polynomial.h"
#include "term.h"


#define MAX_FILENAME_LENGTH 100

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
    while(strcmp(sinput,"q")!=0)  //on Linux platform, it is strcasecmp; while on Win32, it is stricmp
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

