#include <iostream>
#include <windows.h>

#include "run.h"

LRESULT keyboardCallback(int code, WPARAM wParam, LPARAM lParam) {
  printf("Called hook handler\n");
  return CallNextHookEx(0, code, wParam, lParam);
}

int run() {
  HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardCallback, 0, 0);

  if (FAILED(hr)) {
    printf("Failed to call SetWindowsHookEx\n");
    return -1;
  }

  MSG msg{};

  while (GetMessage(&msg, 0, 0, 0) != 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  if (UnhookWindowsHookEx(hHook) == 0) {
    printf("Failed to call UnhookWindowsHookEx()\n");
  }

  printf("Done\n");

  return 0;
}
