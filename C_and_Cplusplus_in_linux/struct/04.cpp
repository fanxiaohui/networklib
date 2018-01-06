#include<cstdio>
#include<cstring>
#include<cstdlib>

struct T{
    T * next;
    int val;
    T(int val):val(val){
    }
    T operator+(T const &other){
        return T(this->val + other.val);
    }
}a(1),b(2);


T* sum(T &a,T const &b){
    T c = a + b;
    T* p = &c;
    return p;
}

T* fun(int step=0){
  int b[16];
  T Cc(1);
  T cc(991);
  int a[16];
  printf("%0X  %0X %0X\n", (unsigned)&b, (unsigned)&Cc, (unsigned)&a);
  a[999] = 2;
  T* Cp = &Cc;
  return Cp;
}


int main(){
    T*p = fun();
    T *c = sum(a,b);
    printf("%d\n",c->val);
    p->val =33; 
    printf("%d\n",c->val);
    return 0;
}

