#include <iostream>
using namespace std;
#define MAXSIZE 256
#define ElemType int
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
}SeqFixedList;

#define LISTINITSIZE 256
#define LISTINCREMENT 128
typedef struct
{
    ElemType *pData[MAXSIZE];
    int length;
    int size;
}SeqFixedList;


