#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

HANDLE hfile;
char selfname[250];

void deleteself() {
	hfile = ::CreateFile("delself.cmd", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hfile == INVALID_HANDLE_VALUE)	//����bat�ļ�
		return;
	::GetModuleFileName(NULL, selfname, 250);
	string bat;
	bat = "del ";	//����ɾ������bat�ļ�������
	bat += selfname;
	bat += "\r\n del delself.cmd";
	DWORD dword;
	::WriteFile(hfile, bat.c_str(), bat.size()+1, &dword, NULL);	//д��bat�ļ�
	::CloseHandle(hfile);
	WinExec("delself.cmd", SW_HIDE);	//Ӧ�ڳ���ӽ�����ʱִ��bat�������������ڴ����޷�ɾ��
}

int main() {
	deleteself();
	return 0;
}