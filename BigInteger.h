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

struct BigInteger mul(struct BigInteger,struct BigInteger);
struct BigInteger add(struct BigInteger,struct BigInteger);
struct BigInteger sub(struct BigInteger,struct BigInteger);
struct BigInteger div1(struct BigInteger,struct BigInteger);
struct BigInteger mod(struct BigInteger,struct BigInteger);
