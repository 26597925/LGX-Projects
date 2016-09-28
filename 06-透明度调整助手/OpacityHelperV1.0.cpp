#define _WIN32_WINNT 0x0400
#include <windows.h>  
#include <iostream>
#include <vector> 
#include <algorithm>
using namespace std;

MSG msg;
BYTE value;
HHOOK hook = 0;
HWND hwnd = NULL;
DWORD processid = 0;
HANDLE hthread;
HINSTANCE hInst;
int key;
int check;
bool running;
vector<HWND> windows;
vector<BYTE> values;


void set() {	//����͸����
	SetWindowLong(hwnd,GWL_EXSTYLE, 0x80000); 
	if(hInst) {
		typedef BOOL (WINAPI *MYFUNC)(HWND, COLORREF, BYTE,DWORD); 
		MYFUNC SetLayeredWindowAttributes = NULL; 
		SetLayeredWindowAttributes=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes"); 
		if(SetLayeredWindowAttributes)
			SetLayeredWindowAttributes(hwnd, 0, value, 2); 
	}
}

int checkwindowchanged(HWND hwnd) {
	if (find(windows.begin(), windows.end(), hwnd) == windows.end()) {		//δ�������Ĵ��ڽ��еǼǣ�����״̬
		windows.push_back(hwnd);
		values.push_back(255);
		return -1;
	} else {		//�������Ĵ���ȡ��״̬
		return find(windows.begin(), windows.end(), hwnd) - windows.begin(); 
	}
}

void change(bool status) {
	if (running) {
		hwnd = ::GetForegroundWindow();
		check = checkwindowchanged(hwnd);	//��ⴰ���Ƿ�Ǽǹ�
		if (check != -1) {
			value = values[check];
		} else {
			value = 255;
			check = checkwindowchanged(hwnd);
		}
		if (status) {	//����״̬+
			value = values[check];
			value += 20;
			values[check] += 20;
		} else {	//����״̬-
			value = values[check];
			value -= 20;
			values[check] -= 20;
		}
		set();
	} else ;
}

LRESULT CALLBACK hookproc (int code, WPARAM wparam, LPARAM lparam) {
	bool flag = false;
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lparam;
	if (wparam == WM_KEYDOWN)
		flag = true;
	key = p->vkCode;
	if (flag) {
		char windowname[250];
		if (key == 107 && running) {	//��⵽С����"+"�����Ӳ�͸����
			change(true);
			GetWindowText(hwnd, windowname, 250);
			cout << "Opacity of "<< windowname << " changed: " << (int)(BYTE)(values[check] - 20) << " + 20 = "  << (int)value << endl;
		} else if (key == 109 && running) {		//��⵽С����"-"����ٲ�͸����
			change(false);
			GetWindowText(hwnd, windowname, 250);
			cout << "Opacity of "<< windowname << " changed: " << (int)(BYTE)(values[check] + 20)<< " - 20 = " << (int)value << endl;
		} else if (key == 118)		//��⵽�ȼ�F7�����ֹرջ���
			running = !running;
		else ;
	} else ;
	key = 0;
	return CallNextHookEx (hook, code, wparam, lparam);
 }

void messageloop() {		//��Ϣѭ��
	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	};
}

void sethook() {		//�������Ӽ���������
	processid = GetCurrentThreadId();
	hook = SetWindowsHookEx (WH_KEYBOARD_LL, &hookproc, GetModuleHandle (NULL), 0);
	if (hook == NULL)
		exit(0);
}

int main() {
	running = true;
	hInst = LoadLibrary("User32.DLL"); 
	sethook();
	messageloop();
	return 0;
}  