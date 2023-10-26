#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <stdio.h>
#include <stdlib.h>

struct node
{
    unsigned int data : 4;
    struct node* next;
};

struct BigInteger
{
    struct node* head;
    long long int size;
    int sign : 2;
};

struct BigInteger add(struct BigInteger,struct BigInteger);
struct BigInteger sub(struct BigInteger,struct BigInteger);
struct BigInteger mul(struct BigInteger,struct BigInteger);
struct BigInteger div1(struct BigInteger,struct BigInteger);
struct BigInteger mod(struct BigInteger,struct BigInteger);

#endif // BIG_INTEGER_H
