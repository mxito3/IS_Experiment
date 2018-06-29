#include <openssl/bn.h>
#include "iostream"
using namespace std;
int main()
{
    BIGNUM *p,*q,*d,*e,*fn,*m,*n,*c,*one,*temp0,*temp1,*m0;
    BN_CTX *ctx=BN_CTX_new();
    int before;
    p=BN_new();
    temp0=BN_new();
    temp1=BN_new();
    q=BN_new();
    e=BN_new();
    m0=BN_new();
    n=BN_new();
    fn=BN_new();
    d=BN_new();
    c=BN_new();
    m=BN_new();
    one=BN_new();
    BN_set_word(one,1);
    BN_set_word(e,422191);
    BN_generate_prime_ex(p,128,1,NULL,NULL,NULL);
    BN_generate_prime_ex(q,128,1,NULL,NULL,NULL);
    BN_mul(n,p,q,ctx);
    BN_sub(temp0,p,one);
    BN_sub(temp1,q,one);
    BN_mul(fn,temp0,temp1,ctx);
    cout<<"n"<<endl;
    BN_print_fp(stdout,n);
    cout<<endl<<"fn"<<endl;
    BN_print_fp(stdout,fn);
    cout<<endl<<"d"<<endl;
    //求d

    BN_mod_inverse(d,e,fn,ctx);
    BN_print_fp(stdout,d);
    cout<<endl;
    cout<<"请输入明文"<<endl;
    cin>>before;
    BN_set_word(m,before);
    //求密文
    BN_mod_exp(c,m,e,n,ctx);
    cout<<"密文是"<<endl;
    BN_print_fp(stdout,c);
    cout<<endl<<"解密密文是"<<endl;
    BN_mod_exp(m0,c,d,n,ctx);

    cout<<endl<<BN_bn2dec(m0);
    cout<<endl;
    return 0;
}
