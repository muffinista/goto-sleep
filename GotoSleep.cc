#include <nan.h>
#include <iostream>

#ifdef IS_MAC
#include <mach/mach_port.h>
#include <IOKit/pwr_mgt/IOPM.h>
#include <IOKit/pwr_mgt/IOPMLib.h>
#endif

#ifdef IS_WINDOWS
#include <Windows.h>
#endif

NAN_METHOD(gotoSleep);
NAN_METHOD(lockScreen);

// Example with node ObjectWrap
// Based on https://nodejs.org/api/addons.html#addons_wrapping_c_objects but using NAN
class GotoSleep : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);

  private:
    explicit GotoSleep();
    ~GotoSleep();

    static NAN_METHOD(New);
    static Nan::Persistent<v8::Function> constructor;
};

Nan::Persistent<v8::Function> GotoSleep::constructor;

NAN_MODULE_INIT(GotoSleep::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("GotoSleep").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("GotoSleep").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

GotoSleep::GotoSleep() {
}

GotoSleep::~GotoSleep() {
}

NAN_METHOD(GotoSleep::New) {
  if (info.IsConstructCall()) {
    GotoSleep *obj = new GotoSleep();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } 
  else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
  }
}

using v8::FunctionTemplate;

#ifdef IS_MAC
bool doSleep() {
  IOReturn                        err;
  io_connect_t                    fb;

  // https://opensource.apple.com/source/PowerManagement/PowerManagement-211.14/pmset/pmset.c.auto.html
  fb = IOPMFindPowerManagement(MACH_PORT_NULL);
  if ( MACH_PORT_NULL != fb ) {
    err = IOPMSleepSystem( fb );

    if (kIOReturnNotPrivileged == err) {
      // printf("Sleep error 0x%08x; You must run this as root.\n", err);
      return false;
    }
    else if ( (MACH_PORT_NULL == fb) || (kIOReturnSuccess != err) ) {
      // printf("Unable to sleep system: error 0x%08x\n", err);
      return false;
    } 
    return true;
  }  

  return false;
}
#endif

NAN_METHOD(gotoSleep) {
  #ifdef IS_MAC
  bool result = doSleep();
  info.GetReturnValue().Set(result);
  #endif

  #ifdef IS_WINDOWS
  // Get the foreground window which the user is currently working on.
  HWND wnd = ::GetForegroundWindow();
  if (!wnd) {
    info.GetReturnValue().Set(false);
  }
  else {
    SendMessage(wnd, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    info.GetReturnValue().Set(true);
  }
  #endif
}

NAN_METHOD(lockScreen) {
  #ifdef IS_MAC
  bool result = doSleep();
  info.GetReturnValue().Set(result);
  #endif

  #ifdef IS_WINDOWS
  LockWorkStation();

  info.GetReturnValue().Set(true);
  #endif
}

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("gotoSleep").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(gotoSleep)).ToLocalChecked());

  Nan::Set(target, Nan::New("lockScreen").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(lockScreen)).ToLocalChecked());

  // Passing target down to the next NAN_MODULE_INIT
  GotoSleep::Init(target);
}

#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(GotoSleep, InitAll);
#else
NODE_MODULE(GotoSleep, InitAll);
#endif