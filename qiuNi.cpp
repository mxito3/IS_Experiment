#include <iostream>  
#include<algorithm>  
#include<cstdio>  
using namespace std;  
int x,y,q;  
void ex_Eulid(int a,int  b){  
    if(b==0){  
        x=1;y=0;q=a;  
    }  
    else{  
        ex_Eulid(b,a%b);  
        double temp=x;  
        x=y;
        y=temp-a/b*y;  
    }  
}  
int main() {  
    int a,b;  
    cin>>a>>b;  
    if(a<b)swap(a,b);  
    ex_Eulid(a,b);  
    printf("%d=(%d)*%d+(%d)*%d\n",q,x,a,y,b);  
    return 0;  
}  
