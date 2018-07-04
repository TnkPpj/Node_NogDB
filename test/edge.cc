#include <nan.h>

#include <nogdb/nogdb.h>
#include "nogdb.h"

void Get(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  v8::String::Utf8Value val(info[2]->ToString());
  std::string className (*val);

  // info.GetReturnValue().Set(num);
}

void GetCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  v8::String::Utf8Value val(info[2]->ToString());
  std::string className (*val);

  // info.GetReturnValue().Set(num);
}

void GetSrc(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

// info.GetReturnValue().Set(num);
}

void GetDst(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResult* result = ObjectWrap::Unwrap<NogResult>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

// info.GetReturnValue().Set(num);
}

void GetSrcDst(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResult* result = ObjectWrap::Unwrap<NogResult>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void Create(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  v8::String::Utf8Value val(info[2]->ToString());
  std::string className (*val);

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
  NogRecordDescriptor* srcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[4]);
  NogRecordDescriptor* dstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[5]);
  NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void Update(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe3.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void UpdateSrc(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* newSrcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void UpdateDst(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* newDstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void Destroy(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("get").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Get)->GetFunction());
  exports->Set(Nan::New("getCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetCursor)->GetFunction()); 
  exports->Set(Nan::New("getSrc").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetSrc)->GetFunction());
  exports->Set(Nan::New("getDst").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetDst)->GetFunction());
  exports->Set(Nan::New("getSrcDst").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetSrcDst)->GetFunction());
  exports->Set(Nan::New("create").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Create)->GetFunction());
  exports->Set(Nan::New("update").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Update)->GetFunction());
  exports->Set(Nan::New("updateSrc").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(UpdateSrc)->GetFunction());
  exports->Set(Nan::New("updateDst").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(UpdateDst)->GetFunction());
  exports->Set(Nan::New("destroy").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Destroy)->GetFunction());
}

NODE_MODULE(addon, Init)
