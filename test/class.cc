#include <nan.h>

#include <nogdb/nogdb.h>
#include "nogdb.h"

void Create(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogClassDescriptor* classDesc = ObjectWrap::Unwrap<NogClassDescriptor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  v8::String::Utf8Value val(info[2]->ToString());
  std::string name (*val);

  v8::String::Utf8Value val2(info[3]->ToString());
  std::string type (*val2);

  // info.GetReturnValue().Set(num);
}

void CreateExtend(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogClassDescriptor* classDesc = ObjectWrap::Unwrap<NogClassDescriptor>(maybe1.ToLocalChecked());
  
  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
  
  v8::String::Utf8Value val(info[2]->ToString());
  std::string className (*val);

  v8::String::Utf8Value val2(info[3]->ToString());
  std::string superClassName (*val2);

  // info.GetReturnValue().Set(num);
}

void Alter(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
  
  v8::String::Utf8Value val(info[1]->ToString());
  std::string oldClassName (*val);

  v8::String::Utf8Value val2(info[2]->ToString());
  std::string newClassName (*val2);

  // info.GetReturnValue().Set(num);
}

void Drop(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
  
  v8::String::Utf8Value val(info[1]->ToString());
  std::string name (*val);

  // info.GetReturnValue().Set(num);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("create").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Create)->GetFunction());
  exports->Set(Nan::New("createExtend").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(CreateExtend)->GetFunction()); 
  exports->Set(Nan::New("alter").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Alter)->GetFunction());
  exports->Set(Nan::New("drop").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Drop)->GetFunction());       
}

NODE_MODULE(addon, Init)
