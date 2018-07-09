#include <nan.h>
#include <nogdb/nogdb.h>

#include "classFilter.hpp"
#include "pathFilter.hpp"
#include "recordDescriptor.hpp"
#include "resultSet.hpp"
#include "resultSetCursor.hpp"
#include "txn.hpp"

void InEdgeBfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void InEdgeBfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void OutEdgeBfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void OutEdgeBfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void AllEdgeBfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void AllEdgeBfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void InEdgeDfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void InEdgeDfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void OutEdgeDfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void OutEdgeDfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void AllEdgeDfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void AllEdgeDfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7){
        Nan::ThrowError("7 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  if(!pathFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_7)){
    Nan::ThrowError("arg7: classFilter required");
    return;
  }
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void ShortestPath(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=6){
        Nan::ThrowError("6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
  v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_4)){
    Nan::ThrowError("arg4: RecordDescriptor required");
    return;
  }
  if(!pathFilterType->HasInstance(arg_5)){
    Nan::ThrowError("arg5: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: classFilter required");
    return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* srcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
  NogRecordDescriptor* dstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe5.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe6 = Nan::To<v8::Object>(info[5]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe6.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}

void ShortestPathCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=6){
        Nan::ThrowError("6 arguments required");
        return;
  }
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
  v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_4)){
    Nan::ThrowError("arg4: RecordDescriptor required");
    return;
  }
  if(!pathFilterType->HasInstance(arg_5)){
    Nan::ThrowError("arg5: PathFilter required");
    return;
  }
  if(!classFilterType->HasInstance(arg_6)){
    Nan::ThrowError("arg6: classFilter required");
    return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* srcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
  NogRecordDescriptor* dstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe4.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
  NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe5.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe6 = Nan::To<v8::Object>(info[5]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe6.ToLocalChecked());

  // info.GetReturnValue().Set(num);
}


void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("inEdgeBfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(InEdgeBfs)->GetFunction());
  exports->Set(Nan::New("inEdgeBfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(InEdgeBfsCursor)->GetFunction()); 
  exports->Set(Nan::New("outEdgeBfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(OutEdgeBfs)->GetFunction());
  exports->Set(Nan::New("outEdgeBfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(OutEdgeBfsCursor)->GetFunction());
  exports->Set(Nan::New("allEdgeBfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(AllEdgeBfs)->GetFunction());
  exports->Set(Nan::New("allEdgeBfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(AllEdgeBfsCursor)->GetFunction());
  exports->Set(Nan::New("inEdgeDfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(InEdgeDfs)->GetFunction());
  exports->Set(Nan::New("inEdgeDfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(InEdgeDfsCursor)->GetFunction()); 
  exports->Set(Nan::New("outEdgeDfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(OutEdgeDfs)->GetFunction());
  exports->Set(Nan::New("outEdgeDfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(OutEdgeDfsCursor)->GetFunction());
  exports->Set(Nan::New("allEdgeDfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(AllEdgeDfs)->GetFunction());
  exports->Set(Nan::New("allEdgeDfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(AllEdgeDfsCursor)->GetFunction());
  exports->Set(Nan::New("shortestPath").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(ShortestPath)->GetFunction());
  exports->Set(Nan::New("shortestPathCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(ShortestPathCursor)->GetFunction());
}

NODE_MODULE(traverse, Init)
