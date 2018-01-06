#include<stdio.h>
#include<string.h>

/*
    从没有针头的链表中删除所有值为x的节点。
    使用引用的简练的代码的证明
*/

struct T{
    T* next;
    int val ;
    T(int val = 0):val(val){};

}a(1),b(2),c(3);


int main(){
    a.next = &b;
    b.next = &c;

    T* p = a.next;
    p = p->next;

    printf("val = %d \n",p->val);
    printf("a = %d  b = %d  c = %d\n ",(int)(&a), (int)(&b), (int)(&c));
    printf("a.next = %d\n", (int)(a.next));

    T* & pp = a.next;
    pp = pp->next;

    printf("val = %d \n",pp->val);
    printf("a = %d  b = %d  c = %d\n ",(int)(&a), (int)(&b), (int)(&c));
    printf("a.next = %d\n", (int)(a.next));


    return 0;
}
