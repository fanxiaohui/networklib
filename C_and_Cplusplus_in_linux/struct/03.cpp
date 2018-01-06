#include<cstdio>
#include<cstring>
#include<cstdlib>

struct T{
    char name[100000];
    T * next;
    int val;
    T(int val,char* name):val(val){
        strcpy(this->name,name);
    }
    T operator+(T const &other){
        char name[100];
        sprintf(name,"%s+%s",this->name,other.name);
        return T(this->val + other.val, name);
    }
    ~T(){
//        this->val = 0;
        printf("delete %s\n" ,this->name);
    }
};

int num = 0;



T* sum(T &a,T const &b){
    T c = a + b;
    num++;
    T* p = &c;
    return p;
}

T* fun(int step=0){

    if(step>0){
        step--;
        T*p = fun(step);
        printf("%d %0x\n",step, (unsigned int)(p));
    }

  T c(1,"");
  T* p = &c;
  return p;
}


int main(){
    T*p = fun(3);
    printf("%d %0x\n",3, (unsigned int)(p));
/*
    int a = 1;
    int const * b = &a;
    const int * c = &a;
    int * const d = &a;

    *d = 1;
    b = c;
*/

//    T a(1,"first");
//    T b(2,"second");
//    T *c = sum(a,b);
//    a.val = 4;
//    b.val = 8;
//   T*d = sum(a,b);
//    c->val = 2;
//    c->next = new T(1,"new");
//    printf("%d\n",c->val);
//    printf("%0x  %0x\n",(unsigned int )c, (unsigned int )(d));
  
//    T * e = (T*)0Xbfee5414;
//    p->val = 133; 
//    printf("%d\n",c->val);

  //  printf("%0x %0x %d\n",(unsigned int)c,(unsigned int)c->next, sizeof(T));

    return 0;
}

