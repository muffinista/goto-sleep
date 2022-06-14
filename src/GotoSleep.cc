#include <node.h>
// #include <iostream>

#include "gotosleep.h"

namespace GotoSleep {
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::Boolean;
  using v8::Value;

  void gotoSleep(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    bool result = doSleep();
    args.GetReturnValue().Set(Boolean::New(isolate, static_cast<bool>(result)));

    doSleep();
  }
  void lockScreen(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    bool result = doLockScreen();
    args.GetReturnValue().Set(Boolean::New(isolate, static_cast<bool>(result)));
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "gotoSleep", gotoSleep);
    NODE_SET_METHOD(exports, "lockScreen", lockScreen);
  }

  NODE_MODULE(gotoSleep, init)
}  // GotoSleep
