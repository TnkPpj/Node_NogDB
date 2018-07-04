#include <nan.h>

#include <nogdb/nogdb.h>
#include "nogdb.h"

void Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogPropertyDescriptor* propDesc = ObjectWrap::Unwrap<NogPropertyDescriptor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  v8::String::Utf8Value val(info[2]->ToString());
  std::string className (*val);

  v8::String::Utf8Value val2(info[3]->ToString());
  std::string propertyName (*val2);

  v8::String::Utf8Value val3(info[4]->ToString());
  std::string type (*val3);

  // info.GetReturnValue().Set(num);
}

void Alter(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
  
  v8::String::Utf8Value val(info[1]->ToString());
  std::string className (*val);

  v8::String::Utf8Value val2(info[2]->ToString());
  std::string oldName (*val2);

  v8::String::Utf8Value val3(info[3]->ToString());
  std::string newName (*val3);

  // info.GetReturnValue().Set(num);
}

void Remove(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
  
  v8::String::Utf8Value val(info[1]->ToString());
  std::string className (*val);

  v8::String::Utf8Value val2(info[2]->ToString());
  std::string propertyName (*val2);

  // info.GetReturnValue().Set(num);
}

void CreateIndex(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
  
  v8::String::Utf8Value val(info[1]->ToString());
  std::string ClassName (*val);

  v8::String::Utf8Value val2(info[2]->ToString());
  std::string propertyName (*val2);

  bool isUnique = info[3]->BooleanValue();

  // info.GetReturnValue().Set(num);
}

void DropIndex(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
  
  v8::String::Utf8Value val(info[1]->ToString());
  std::string ClassName (*val);

  v8::String::Utf8Value val2(info[2]->ToString());
  std::string propertyName (*val2);

  // info.GetReturnValue().Set(num);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("add").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Add)->GetFunction());
  exports->Set(Nan::New("alter").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Alter)->GetFunction()); 
  exports->Set(Nan::New("remove").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Remove)->GetFunction());
  exports->Set(Nan::New("createIndex").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(CreateIndex)->GetFunction());  
  exports->Set(Nan::New("dropIndex").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(DropIndex)->GetFunction());       
}

NODE_MODULE(addon, Init)
