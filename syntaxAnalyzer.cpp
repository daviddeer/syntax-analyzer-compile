
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

int sym;    //当前的符号
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

    printf("请输入分析的文件名:");
    gets(filename);
    /*scanf("%s",filename);*/
    do
    {
        if((fin=fopen(filename,"r"))==NULL)
        {
            printf("不能打开文件.\n");
            return 0;
        }
        getsym();            //读第一个单词，将单词类别放入sym中
        S();               //开始按E->TA  分析
        if (sym==nul)
        {
            printf("语法正确\n");
        }
        else
        {
            printf("语法错11\n");
        }
        fclose(fin);

        printf("继续分析则输入文件名，否则回车");
        scanf("%s",filename);
        gets(filename);
    }
    while (strlen(filename)>0);
    return 0;
}

/*
* 词法分析，获取一个符号
*/
void getsym()
{
    ch=fgetc(fin);

    while (ch==' ' || ch==10 || ch==13 || ch==9)  /* 忽略空格、换行、回车和TAB */
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
        printf("--词法错\n");
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
        printf("语法错S\n");
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
        printf("语法错A\n");
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
        printf("语法错E\n");
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
        printf("语法错R\n");
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
        printf("语法错T\n");
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
        printf("语法错P\n");
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
        printf("语法错F\n");
        exit(0);
    }
}

void V()
{
    if (sym==ident)          //当前单词为indent类型
    {
        printf("character matched.\n");
        getsym();
    }
    else
    {
        printf("语法错V: 缺变量\n ");
        exit(0);
    }
}

