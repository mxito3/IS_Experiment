#include "string.h"
#include <cstdlib>
#include "time.h"
#include <vector>
#include <fstream>
#include "iostream"
using namespace std;

/*
加密类
*/
class RC4 {
public:
	/*
	构造函数，参数为密钥长度
	*/
	RC4(int kl) :keylen(kl) {
		srand((unsigned)time(NULL));
		for (int i = 0; i<kl; ++i) {  //随机生产长度为keylen字节的密钥
			int tmp = rand() % 256;
			K.push_back(char(tmp));
		}
	}
	/*
	由明文产生密文
	*/
	void encryption(const string &, const string &, const string &);

private:
	unsigned char S[256]; //状态向量，共256字节
	unsigned char T[256]; //临时向量，共256字节
	int keylen;        //密钥长度，keylen个字节，取值范围为1-256
	vector<char> K;      //可变长度密钥
	vector<char> k;      //密钥流

						 /*
						 初始化状态向量S和临时向量T，供keyStream方法调用
						 */
	void initial() {
		for (int i = 0; i<256; ++i) {
			S[i] = i;
			T[i] = K[i%keylen];
		}
	}
	/*
	初始排列状态向量S，供keyStream方法调用
	*/
	void rangeS() {
		int j = 0;
		for (int i = 0; i<256; ++i) {
			j = (j + S[i] + T[i]) % 256;
			//cout<<"j="<<j<<endl;
			S[i] = S[i] + S[j];
			S[j] = S[i] - S[j];
			S[i] = S[i] - S[j];
		}
	}
	/*
	生成密钥流
	len:明文为len个字节
	*/
	void keyStream(int len);

};
void RC4::keyStream(int len) {
	initial();
	rangeS();

	int i = 0, j = 0, t;
	while (len--) {
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;

		S[i] = S[i] + S[j];
		S[j] = S[i] - S[j];
		S[i] = S[i] - S[j];

		t = (S[i] + S[j]) % 256;
		k.push_back(S[t]);
	}
}
void RC4::encryption(const string &plaintext, const string &ks, const string &ciphertext) {
	ifstream in;
	ofstream out, outks;

	in.open(plaintext.c_str());
	//获取输入流的长度
	in.seekg(0, ios::end);
	int lenFile = in.tellg();
	in.seekg(0, ios::beg);

	//生产密钥流
	keyStream(lenFile);
	outks.open(ks.c_str());
	for (int i = 0; i<lenFile; ++i) {
		outks << (k[i]);
	}
	outks.close();

	//明文内容读入bits中
	unsigned char *bits = new unsigned char[lenFile];
	in.read((char *)bits, lenFile);
	in.close();


	out.open(ciphertext.c_str());
	//将明文按字节依次与密钥流异或后输出到密文文件中
	for (int i = 0; i<lenFile; ++i) {
		out << (unsigned char)(bits[i] ^ k[i]);
	}
	out.close();

	delete[]bits;
}

/*
解密类
*/
class RC4_decryption {
public:
	/*
	构造函数，参数为密钥流文件和密文文件
	*/
	RC4_decryption(const string ks, const string ct) :keystream(ks), ciphertext(ct) {}
	/*
	解密方法，参数为解密文件名
	*/
	void decryption(const string &);

private:
	string ciphertext, keystream;
};


void RC4_decryption::decryption(const string &res) {
	ifstream inks, incp;
	ofstream out;

	inks.open(keystream.c_str());
	incp.open(ciphertext.c_str());

	//计算密文长度
	inks.seekg(0, ios::end);
	const int lenFile = inks.tellg();
	inks.seekg(0, ios::beg);
	//读入密钥流
	unsigned char *bitKey = new unsigned char[lenFile];
	inks.read((char *)bitKey, lenFile);
	inks.close();
	//读入密文
	unsigned char *bitCip = new unsigned char[lenFile];
	incp.read((char *)bitCip, lenFile);
	incp.close();

	//解密后结果输出到解密文件
	out.open(res.c_str());
	for (int i = 0; i<lenFile; ++i)
		out << (unsigned char)(bitKey[i] ^ bitCip[i]);

	out.close();
}

int main() {
	RC4 rc4(16); //密钥长16字节
	rc4.encryption("明文.txt", "密钥流.txt", "密文.txt");
	RC4_decryption decrypt("密钥流.txt", "密文.txt");
	decrypt.decryption("解密文件.txt");


}
