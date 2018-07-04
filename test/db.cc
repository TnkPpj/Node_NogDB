#include <nan.h>

#include <nogdb/nogdb.h>
#include "nogdb.h"

void GetDbInfo(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogDBInfo* dbInfo = ObjectWrap::Unwrap<NogDBInfo>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void GetSchema(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogClassDescriptor* classDesc = ObjectWrap::Unwrap<NogClassDescriptor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
  
  v8::String::Utf8Value val(info[2]->ToString());
  std::string className (*val);

  // info.GetReturnValue().Set(num);
}

void GetRecord(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("getDbInfo").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetDbInfo)->GetFunction());
  exports->Set(Nan::New("getSchema").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetSchema)->GetFunction()); 
  exports->Set(Nan::New("getRecord").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetRecord)->GetFunction());
}

NODE_MODULE(addon, Init)
