#include <windows.h>
#include <iostream>
using namespace std;

HWND hwnd = NULL;
HWND hwnd2 = NULL;
HANDLE hthread = NULL;

void refreshchrome() {	//����chrome��ҳ
		hwnd2=FindWindow("Chrome_WidgetWin_1", NULL);
		hwnd2=GetParent(hwnd2);	//Ҫ���Ӵ��ھ���ҵ������ھ��
		::SetForegroundWindow(hwnd2);
		Sleep(5);
		::SendMessage(hwnd2, WM_KEYDOWN, VK_F5, 0);
		::SendMessage(hwnd2, WM_KEYUP, VK_F5, 0);
}

int main() {
	while (true) {
			hwnd = NULL;	//�ҵ�ǰ���±�notepad++����д�Ĵ���
			hwnd = ::FindWindow("Notepad++", NULL);
			char textname[250];
			GetWindowText(hwnd, textname, 250);		
			if (hwnd == NULL || textname[0] != '*') {	//�Ҳ�������
				Sleep(5);
				continue; 
			} else {	//�ҵ����Զ����沢����chrome��ҳ
				::SetForegroundWindow(hwnd);
				keybd_event(VK_CONTROL, 0, 0 ,0);
				keybd_event(83, 0, 0 ,0);
				keybd_event(83, 0, KEYEVENTF_KEYUP,0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP,0);
				refreshchrome();
				::SetForegroundWindow(hwnd);
			}
	}
	return 0;
}