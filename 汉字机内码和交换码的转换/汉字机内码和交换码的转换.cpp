// 汉字机内码和交换码的转换.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<bitset>
#include<fstream>
#include<string>
using namespace std;



static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
int Base64Encode(char *src, char *des)//返回一个四字节的char数组?
{
	des[0] = src[0] >> 2;
	unsigned char temp = (src[0] & 0x03) << 4;
	des[1] = temp | (src[1] >> 4);
	temp = (src[1] & 0x0F) << 2;
	des[2] = temp | (src[2] >> 6);
	des[3] = src[2] & 0x3F;
	return 0;
}
int Base64Decode(unsigned char *src, char *des) {//四字节变成三字节
	//src[0] = (des[1] << 6) | des[0];
	//src[1] = (des[2] << 4) | ((des[1] & 0x3C) >> 2);
	//src[2] = (des[3] << 2) | ((des[2] & 0x30) >> 4);
	src[0] = (des[0] << 2) + ((des[1] & 0x30) >> 4);
	src[1] = ((des[1] & 0xf) << 4) + ((des[2] & 0x3c) >> 2);
	src[2] = ((des[2] & 0x3) << 6) + des[3];
	return 0;
}
int main()
{
	char src[4];
	char des[5];
	short a = 10;
	/*cout << "输入short的值:";
	cin >> a;*/
	bitset<16> b0(a);
	// 输出二进制
	cout << b0 << endl;
	ifstream infile;
	ofstream outfile("b.txt");
	infile.open("a.dat", ofstream::binary);
	while (infile.read(src, sizeof(char) * 3))
	{
		src[3] = '\0';
		Base64Encode(src, des);
		des[4] = '\0';
		for (int i = 0; i <= 3; ++i) {
			des[i] = base64_chars[des[i]];
		}
		outfile << des;
		memset(src, 0, 4);
	}
	int count = 0;
	for (int i = 0; i <= 2; ++i) {
		if (src[i] != 0)
			continue;
		Base64Encode(src, des);
		for (int j = 0; j <= 3; ++j) {
			des[j] = base64_chars[des[j]];
		}
		if (i == 1)
			des[2] = des[3] = '=';
		else if (i == 2)
			des[3] = '=';
		des[4] = '\0';

		outfile << des;
	}//编码结果在b.txt中
	infile.close();
	outfile.close();
	unsigned char src2[4];
	infile.open("b.txt");
	ofstream outfile2("c.txt");
	while (infile.read(des, sizeof(char) * 4)) {
		for (int i = 0; i <= 4; i++) {
			des[i] = base64_chars.find(des[i]);
			
		}
		des[4] = '\0';
		for (int l = 0; l <= 3; ++l) {
			if (des[l] >= 0)
				continue;
			des[l] = 0;
		}
		Base64Decode(src2, des);
		src2[3] = '\0';
		outfile2 << src2;

	}//解码结果在c.txt



}


