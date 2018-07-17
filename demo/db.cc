#include <nan.h>
#include <nogdb/nogdb.h>

#include "classDescriptor.hpp"
#include "dbInfo.hpp"
#include "record.hpp"
#include "recordDescriptor.hpp"
#include "txn.hpp"

#include "db.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogDb::constructor;

NogDb::NogDb() {};
NogDb::~NogDb() {};

NAN_MODULE_INIT(NogDb::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogDb::New);
    constructor.Reset(tpl);

    tpl->SetClassName(Nan::New<v8::String>("Db").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "getRecord", NogDb::GetRecord);
    SetPrototypeMethod(tpl, "getSchema", NogDb::GetSchema);
    SetPrototypeMethod(tpl, "getDbInfo", NogDb::GetDbInfo);

    Set(target, Nan::New<v8::String>("Db").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogDb::New) {
    NogDb* obj = new NogDb();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}


NAN_METHOD(NogDb::GetRecord) {
    if(info.Length()!=3){
      Nan::ThrowError("3 arguments required");
      return;
    }
    
    v8::Local<v8::FunctionTemplate> recordType = Nan::New<v8::FunctionTemplate>(NogRecord::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    // get record for return
    if(!recordType->HasInstance(arg_1)){
      Nan::ThrowError("arg1: Record required");
      return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
      Nan::ThrowError("arg2: Txn required");
      return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // get recordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
      Nan::ThrowError("arg3: RecordDescriptor required");
      return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // getRecord
    r->record = nogdb::Db::getRecord(*txn->txn,recordDesc->recordDescriptor);
}


NAN_METHOD(NogDb::GetSchema) {
    if(info.Length()!=3){
          Nan::ThrowError("3 arguments required");
          return;
    }
    
    v8::Local<v8::FunctionTemplate> classDescriptorType = Nan::New<v8::FunctionTemplate>(NogClassDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    // get classDescriptor for return
    if(!classDescriptorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ClassDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogClassDescriptor* classDesc = ObjectWrap::Unwrap<NogClassDescriptor>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // check className or classId
    if(!info[2]->IsString()||!info[2]->IsInt32()){
        Nan::ThrowError("arg3: string or int required");
        return;
    }
    // className
    if(info[2]->IsString()){
        Nan::Utf8String val(info[2]->ToString());
        std::string className (*val);
        // getSchema
        classDesc->classDescriptor = nogdb::Db::getSchema(*txn->txn,className);
    }
    // classId
    else if(info[2]->IsInt32()){
        Nan::Maybe<int32_t> val = Nan::To<int32_t>(info[2]);
        int classId = val.FromJust();
        // getSchema
        classDesc->classDescriptor = nogdb::Db::getSchema(*txn->txn,classId);
    }
}

NAN_METHOD(NogDb::GetDbInfo) {
    if(info.Length()!=2){
        Nan::ThrowError("2 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> dbInfoType = Nan::New<v8::FunctionTemplate>(NogDBInfo::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    // get dbInfo for return
    if(!dbInfoType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: DbInfo required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogDBInfo* dbInfo = ObjectWrap::Unwrap<NogDBInfo>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // getDbInfo
    dbInfo->dbInfo = nogdb::Db::getDbInfo(*txn->txn);
}