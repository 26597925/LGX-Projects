#include <windows.h>
#include <winable.h> 
#include <string>
#include <fstream>
#include <iostream>
#define MAX 250
using namespace std;

char src[MAX] = "C:\\Users\\Administrator\\Desktop\\test";		//�����ļ�Ŀ¼
char files[MAX] = "C:\\Users\\Administrator\\Desktop\\out.txt";		//�ļ��б�Ŀ¼
char cmd[MAX];

int main () {

	sprintf(cmd, "cmd /c dir %s\\*.* /a-d /b /s >%s", src, files);	//����srcĿ¼�������ļ�·��������浽files
	system(cmd);

	ifstream in(files);

	char file[MAX];	
	cout << "�����ļ�������:" << endl;
	while (!in.eof()) { 
		in.getline(file, MAX);
		cout << file << endl;
		HANDLE hfile = ::CreateFile(file, GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		::LockFile(hfile, 0, 0, 0, 0);	//��ס�ļ�
		BlockInput(true);	//δ������֮ǰ�������ͼ���
	}
	BlockInput(false);
	system("pause");

	return 0;
};