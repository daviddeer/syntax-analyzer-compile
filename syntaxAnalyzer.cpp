
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum symbol
{
    nul,         ident,         plus,      times,	lparen,
    rparen,    divide,     sub,     morethan,   lessthan
};

/*enum symbol sym;

#define nul 0
#define ident 1
#define plus 2
#define times 3
#define lparen 4
#define rparen 5
#define divide 6
#define sub 7*/

int sym;    //��ǰ�ķ���
char ch;

FILE* fin;

void getsym();
void S();
void E();
void A();
void R();
void T();
void P();
void F();
void V();

int main()
{
    char filename[20];

    printf("������������ļ���:");
    gets(filename);
    /*scanf("%s",filename);*/
    do
    {
        if((fin=fopen(filename,"r"))==NULL)
        {
            printf("���ܴ��ļ�.\n");
            return 0;
        }
        getsym();            //����һ�����ʣ�������������sym��
        S();               //��ʼ��E->TA  ����
        if (sym==nul)
        {
            printf("�﷨��ȷ\n");
        }
        else
        {
            printf("�﷨��11\n");
        }
        fclose(fin);

        printf("���������������ļ���������س�");
        scanf("%s",filename);
        gets(filename);
    }
    while (strlen(filename)>0);
    return 0;
}

/*
* �ʷ���������ȡһ������
*/
void getsym()
{
    ch=fgetc(fin);

    while (ch==' ' || ch==10 || ch==13 || ch==9)  /* ���Կո񡢻��С��س���TAB */
        ch=fgetc(fin);

    if (ch==EOF)
        sym=nul;

    else if (ch>='a' && ch<='z')
        sym = ident;
    else if(ch == '+')
        sym = plus;
    else if (ch == '*')
        sym = times;
    else if (ch == '/')
        sym = divide;
    else if (ch == '-')
        sym = sub;
    else if (ch == '(')
        sym = lparen;
    else if (ch == ')')
        sym = rparen;
    else if (ch == '>')
        sym = morethan;
    else if (ch == '<')
        sym = lessthan;
    else
    {
        printf("--�ʷ���\n");
        exit(0);
    }
    return;
}


/*
V->a|...|z
*/
void S()
{
    if(sym == ident || sym == lparen)
    {
        printf("S->EA\n");
        E();
        A();
    }
    else
    {
        printf("�﷨��S\n");
        exit(0);
    }
}

void A()
{
    switch(sym)
    {
    case morethan:
        printf("A->>E\n");
        getsym();
        E();
        break;
    case lessthan:
        printf("A-><E\n");
        getsym();
        E();
        break;
    case nul:
        break;
    default:
        printf("�﷨��A\n");
        exit(0);
    }
}

void E()
{
    if(sym==lparen||sym==ident)
    {
        printf("E->TR\n");
        T();
        R();
    }
    else
    {
        printf("�﷨��E\n");
        exit(0);
    }
}

void R()
{
    switch(sym)
    {
    case plus:
        printf("R->+TR\n");
        getsym();
        T();
        R();
        break;
    case sub:
        printf("R->-TR\n");
        getsym();
        T();
        R();
        break;
    case nul:
        break;
    case morethan:
        break;
    case lessthan:
        break;
    case rparen:
        break;
    default:
        printf("�﷨��R\n");
        exit(0);
    }
}

void T()
{
    if(sym==lparen||sym==ident)
    {
        printf("T->FP\n");
        F();
        P();
    }
    else
    {
        printf("�﷨��T\n");
        exit(0);
    }
}

void P()
{
    switch(sym)
    {
    case times:
        printf("P->*FP\n");
        getsym();
        F();
        P();
        break;
    case divide:
        printf("P->/FP\n");
        getsym();
        F();
        P();
        break;
    case nul:
        break;
    case plus:
        break;
    case morethan:
        break;
    case lessthan:
        break;
    case sub:
        break;
    case rparen:
        break;
    default:
        printf("�﷨��P\n");
        exit(0);
    }
}

void F()
{
    switch(sym)
    {
    case lparen:
        printf("F->(E)\n");
        getsym();
        E();
        getsym();
        break;
    case ident:
        printf("F->V\n");
        V();
        break;
    default:
        printf("�﷨��F\n");
        exit(0);
    }
}

void V()
{
    if (sym==ident)          //��ǰ����Ϊindent����
    {
        printf("character matched.\n");
        getsym();
    }
    else
    {
        printf("�﷨��V: ȱ����\n ");
        exit(0);
    }
}

