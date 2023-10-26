#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
struct BigInteger initialize(char*);
void insert(struct BigInteger*,int);
void display(struct BigInteger);
void reverse(struct BigInteger*);
void swap(struct BigInteger*,struct BigInteger*);
int compare(struct BigInteger,struct BigInteger);
struct BigInteger suba(struct BigInteger,struct BigInteger);
struct BigInteger adds(struct BigInteger,struct BigInteger);
struct BigInteger mul(struct BigInteger,struct BigInteger);
struct BigInteger add(struct BigInteger,struct BigInteger);
struct BigInteger sub(struct BigInteger,struct BigInteger);
struct BigInteger div1(struct BigInteger,struct BigInteger);
struct BigInteger divby2(struct BigInteger);
struct BigInteger mod(struct BigInteger,struct BigInteger);


void insert(struct BigInteger* big,int val)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->data=val;
    temp->next=NULL;
    if(!(big->head))
    {
        big->head=temp;
        big->size++;
        return ;
    }
    struct node* itr=big->head;
    while(itr->next!=NULL)
    {
        itr=itr->next;
    }
    itr->next=temp;
    big->size++;
    return ;
}
struct BigInteger initialize(char* s)
{
    struct BigInteger temp;
    temp.head=NULL;
    temp.sign=1;
    temp.size=0;
    int len=strlen(s);
    if(s[0]=='-')
    {
        temp.sign=-1;
    }
    for(int i=0;i<len;i++)
    {
        if(s[i]=='-')
        {
            continue;
        }
        int val=s[i]-48;
        insert(&temp,val);
    }
    return temp;
}

void display(struct BigInteger ans)
{
    struct node* itr=ans.head;
    while(itr!=NULL)
    {
        printf("%d",itr->data);
        itr=itr->next;
    }
    printf("\n");
}
void reverse(struct BigInteger* temp)
{
    struct node* prev=NULL;
    struct node* curr=temp->head;
    struct node* next=NULL;
    while(curr!=NULL)
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    temp->head=prev;
}
struct BigInteger add(struct BigInteger val1,struct BigInteger val2)
{
    struct BigInteger ans;
    ans.head=NULL;
    ans.size=0;
    ans.sign=1;
    if(val1.sign==-1 && val2.sign==-1)
    {
        ans.sign=-1;
    }
    else if(val1.sign==-1 || val2.sign==-1)
    {
        if(compare(val1,val2)==2 && val2.sign==-1)
        {
            ans=suba(val1,val2);
            ans.head->data=-1*ans.head->data;
        }
        else if(compare(val1,val2)==1 && val1.sign==-1)
        {
            ans=suba(val1,val2);
            ans.head->data=-1*ans.head->data;
        }
        else if(compare(val1,val2)==1 && val2.sign==-1)
        {
            ans=suba(val1,val2);
        }
        else if(compare(val1,val2)==2 && val1.sign==-1)
        {
            ans=suba(val1,val2);
        }
        return ans;
    }
    reverse(&val1);
    reverse(&val2);
    int carry=0;
    int sum=0;
    struct node* itr=val1.head;
    struct node* ptr=val2.head;
    while(itr!=NULL || ptr!=NULL || carry>0)
    {
        int dig1=(itr!=NULL)?itr->data:0;
        int dig2=(ptr!=NULL)?ptr->data:0;
        sum=dig1+dig2+carry;
        carry=sum/10;
        insert(&ans,sum%10);  
        if(itr!=NULL)
        {
            itr=itr->next;
        }
        if(ptr!=NULL)
        {
            ptr=ptr->next;
        }
    }
    reverse(&val1);
    reverse(&val2);
    reverse(&ans);
    struct node* p=ans.head;
    while(p->next!=NULL)
    {
        if(p->data!=0)
        {
            break;
        }
        if(p->data==0)
        {
            p=p->next;
            ans.head=p;
        }
        else
        {
            p=p->next;
        }
        
    }
    ans.head->data=ans.sign*ans.head->data;
    return ans;
}
void swap(struct BigInteger* val1,struct BigInteger* val2)
{
    int flag=0;
    struct node* itr=val1->head;
    struct node* ptr=val2->head;
    if(val1->size<val2->size)
    {
        struct BigInteger temp=*val1;
        *val1=*val2;
        *val2=temp;
    }
    else if(val1->size==val2->size)
    {
        while(itr!=NULL && ptr!=NULL)
        {
            if(itr->data<ptr->data)
            {
                flag=1;
                break;
            }
            itr=itr->next;
            ptr=ptr->next;
        }
        if(flag)
        {
            struct BigInteger temp=*val1;
            *val1=*val2;
            *val2=temp;
        }
    }
}
int compare(struct BigInteger val1,struct BigInteger val2)
{
    if(val1.size<val2.size)
    {
        return 2;
    }
    else if(val1.size==val2.size)
    {
        struct node* itr=val1.head;
        struct node* ptr=val2.head;
        while(itr!=NULL && ptr!=NULL)
        {
            if(itr->data>ptr->data)
            {
                return 1;
            }
            itr=itr->next;
            ptr=ptr->next;
        }
        return 2;
    }
    return 1;
}
struct BigInteger sub(struct BigInteger val1,struct BigInteger val2)
{
    int temp=0;
    struct BigInteger ans;
    ans.head=NULL;
    ans.sign=1;
    ans.size=0;
    if(val1.sign==-1 && val2.sign==-1)
    {
        if(compare(val1,val2)==1)
        {
            ans.sign=-1;
        }
        else
        {
            ans.sign=1;
        }
    }
    else if(val1.sign==-1 && val2.sign==1)
    {
        ans.sign=-1;
        ans=adds(val1,val2);
        ans.head->data=-1*ans.head->data;
        return ans;
    }
    else if(val1.sign==1 && val2.sign==-1)
    {
        ans=adds(val1,val2);
        return ans;
    }
    else
    {
        if(compare(val1,val2)==2)
        {
            ans.sign=-1;
        }
    }
    swap(&val1,&val2);
    reverse(&val1);
    reverse(&val2);
    int borrow=0;
    int diff=0;
    struct node* itr=val1.head;
    struct node* ptr=val2.head;
    while (itr!=NULL || ptr!=NULL)
    {
        int digit1=(itr!=NULL)?itr->data:0;
        int digit2=(ptr!=NULL)?ptr->data:0;
        if(borrow==1)
        {
            digit1=digit1-1;
            borrow=0;
        }
        if(digit1<digit2)
        {
            digit1=digit1+10;
            borrow=1;
        }
        diff=digit1-digit2;
        insert(&ans,diff);
        if(itr!=NULL)
        {
            itr=itr->next;
        }
        if(ptr!=NULL)
        {
            ptr=ptr->next;
        }
    }
    reverse(&val1);
    reverse(&val2);
    reverse(&ans);
    struct node* p=ans.head;
    while(p->next!=NULL)
    {
        if(p->data!=0)
        {
            break;
        }
        if(p->data==0)
        {
            p=p->next;
            ans.head=p;
        }
        else
        {
            p=p->next;
        }
        
    }
    ans.head->data=ans.head->data*ans.sign;
    return ans;
}
struct BigInteger suba(struct BigInteger val1,struct BigInteger val2)
{
    int temp=0;
    struct BigInteger ans;
    ans.head=NULL;
    ans.sign=1;
    ans.size=0;
    swap(&val1,&val2);
    reverse(&val1);
    reverse(&val2);
    int borrow=0;
    int diff=0;
    struct node* itr=val1.head;
    struct node* ptr = val2.head;
    while (itr != NULL || ptr != NULL) {
        int digit1 = (itr != NULL) ? itr->data : 0;
        int digit2 = (ptr != NULL) ? ptr->data : 0;
        if (borrow == 1) {
            digit1 = digit1 - 1;
            borrow = 0;
        }
        if (digit1 < digit2) {
            digit1 = digit1 + 10;
            borrow = 1;
        }
        diff = digit1 - digit2;
        insert(&ans, diff);
        if (itr != NULL) {
            itr = itr->next;
        }
        if (ptr != NULL) {
            ptr = ptr->next;
        }
    }
    reverse(&val1);
    reverse(&val2);
    reverse(&ans);
    return ans;
    }

    struct BigInteger adds(struct BigInteger val1, struct BigInteger val2) {
        struct BigInteger ans;
        ans.head = NULL;
        ans.size = 0;
        ans.sign = 1;
        reverse(&val1);
        reverse(&val2);
        int carry = 0;
        int sum = 0;
        struct node* itr = val1.head;
        struct node* ptr = val2.head;
        while (itr != NULL || ptr != NULL || carry > 0) {
            int dig1 = (itr != NULL) ? itr->data : 0;
            int dig2 = (ptr != NULL) ? ptr->data : 0;
            sum = dig1 + dig2 + carry;
            carry = sum / 10;
            insert(&ans, sum % 10);
            if (itr != NULL) {
                itr = itr->next;
            }
            if (ptr != NULL) {
                ptr = ptr->next;
            }
        }
        reverse(&val1);
        reverse(&val2);
        reverse(&ans);
        return ans;
    }

    struct BigInteger mul(struct BigInteger val1, struct BigInteger val2) {
        struct BigInteger ans;
        ans.head = NULL;
        ans.size = 0;
        ans.sign = 1;
        reverse(&val1);
        reverse(&val2);
        struct node* itr = val1.head;
        struct node* ptr = val2.head;
        int pos = 0;
        while (ptr != NULL) {
            struct BigInteger temp;
            temp.head = NULL;
            temp.size = 0;
            temp.sign = 1;
            itr = val1.head;
            int carry = 0;
            while (itr != NULL || carry > 0) {
                int val1 = (itr != NULL) ? itr->data : 0;
                int prod = ((ptr->data) * val1) + carry;
                carry = prod / 10;
                insert(&temp, prod % 10);
                if (itr != NULL) {
                    itr = itr->next;
                }
            }
            reverse(&temp);
            for (int i = 0; i < pos; i++) {
                insert(&temp, 0);
            }
            struct BigInteger partres;
            partres.head = NULL;
            partres.size = 0;
            partres.sign = 1;
            partres = add(ans, temp);
            pos++;
            ans.head = partres.head;
            ans.size = partres.size;
            ptr = ptr->next;
        }
        if (val1.sign == -1 && val2.sign == -1) {
            ans.sign = 1;
        } else if (val1.sign == -1 || val2.sign == -1) {
            ans.sign = -1;
        }
        reverse(&val1);
        reverse(&val2);
        struct node* p = ans.head;
        while (p->next != NULL) {
            if (p->data != 0) {
                break;
            }
            if (p->data == 0) {
                p = p->next;
                ans.head = p;
            } else {
                p = p->next;
            }
        }
        ans.head->data = (ans.sign) * ans.head->data;
        return ans;
    }

    int comparediv(struct BigInteger val1, struct BigInteger val2) {
        if (val1.size < val2.size) {
            return 2;
        }
        if (val1.size == val2.size) {
            struct node* itr = val1.head;
            struct node* ptr = val2.head;
            while (itr != NULL && ptr != NULL) {
                if (itr->data > ptr->data) {
                    return 1;
                } else if (itr->data < ptr->data) {
                    return 2;
                }
                itr = itr->next;
                ptr = ptr->next;
            }
            return 0;
        }
        if (val1.size > val2.size) {
            return 1;
        }
    }

    struct BigInteger divby2(struct BigInteger val) {
        struct BigInteger result;
        result.head = NULL;
        result.size = 0;
        result.sign = val.sign;

        struct node* current = val.head;
        int carry = 0;

        while (current != NULL) {
            int sum = current->data + carry * 10;
            int quotient = sum / 2;
            carry = sum % 2;

            insert(&result, quotient);

            current = current->next;
        }
        struct node* p = result.head;
        while (p->next != NULL) {
            if (p->data != 0) {
                break;
            }
            if (p->data == 0) {
                p = p->next;
                result.head = p;
                result.size--;
            } else {
                p = p->next;
            }
        }
        return result;
    }

struct BigInteger div1(struct BigInteger val1, struct BigInteger val2) {
    struct BigInteger ans;
    ans.head = NULL;
    ans.size = 0;
    ans.sign = 1;
    if (val2.size == 1 && val2.head->data == 0) {
        return ans;
    }
    if (comparediv(val1, val2) == 2) {
        insert(&ans, 0);
        return ans;
    }
    if (val2.size == 1 && val2.head->data == 1) {
        return val1;
    }
    struct BigInteger low;
    low.head = NULL;
    low.size = 0;
    low.sign = 1;
    insert(&low, 0);
    struct BigInteger one;
    one.head = NULL;
    one.sign = 1;
    one.size = 0;
    insert(&one, 1);
    struct BigInteger high = val1;
    struct BigInteger mid;
    struct BigInteger quotient;
    quotient.head = NULL;
    quotient.size = 0;
    quotient.sign = 1;
    insert(&quotient, 0);
    while (comparediv(low, high) != 1) {
        mid = add(high, low);
        mid = divby2(mid);
        struct BigInteger temp = mul(mid, val2);
        if (comparediv(temp, val1) == 1) {
            high = sub(mid, one);
      } else {
            quotient = mid;
            low = add(mid, one);
        }
    }
    return quotient;    
}

struct BigInteger mod(struct BigInteger num1, struct BigInteger num2) {
    int temp1 = num1.sign, temp2 = num2.sign;
    num1.sign = 1;
    num2.sign = 1;
    struct BigInteger quotient = div1(num1, num2);
    struct BigInteger product = mul(quotient, num2);
    struct BigInteger result = sub(num1, product);
    num1.sign = temp1;
    num2.sign = temp2;
    return result; 
}
