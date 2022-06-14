#include <Windows.h>

bool doSleep() {
  // Get the foreground window which the user is currently working on.
  HWND wnd = ::GetForegroundWindow();
  if (!wnd) {
    return false;
  }
  else {
    SendMessage(wnd, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    return true;
  }
}

bool doLockScreen() {
  LockWorkStation();
  return true;
}
