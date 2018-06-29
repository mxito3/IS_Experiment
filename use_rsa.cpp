#include "iostream"
#include <openssl/rsa.h>
#include "string.h"
using namespace std;
int main()
{
    RSA *rsa=RSA_new();
    rsa=RSA_generate_key(1024,3,NULL,NULL);
    char msg0[1000];
    char msg[1000];
    cout<<"请输入明文";
    cin>>msg;
    unsigned char *ciper=(unsigned char*)malloc(RSA_size(rsa));
    int size=RSA_public_encrypt(strlen(msg),(unsigned char*)msg,ciper,rsa,RSA_PKCS1_PADDING);
    RSA_private_decrypt(size,ciper,(unsigned char*)msg0,rsa,RSA_PKCS1_PADDING);
    cout<<endl<<"解密后"<<msg0<<endl;
}
