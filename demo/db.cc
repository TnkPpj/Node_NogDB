#include <nan.h>
#include <nogdb/nogdb.h>

#include "classDescriptor.hpp"
#include "dbInfo.hpp"
#include "record.hpp"
#include "recordDescriptor.hpp"
#include "txn.hpp"

void GetDbInfo(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=2){
        Nan::ThrowError("2 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> dbInfoType = Nan::New<v8::FunctionTemplate>(NogDBInfo::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();

    if(!dbInfoType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: DbInfo required");
        return;
    }
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogDBInfo* dbInfo = ObjectWrap::Unwrap<NogDBInfo>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    dbInfo->dbInfo = nogdb::Db::getDbInfo(txn->txn);
    // const DBInfo Db::getDbInfo(const Txn &txn)
}

void GetSchema(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=3){
          Nan::ThrowError("3 arguments required");
          return;
    }
    
    v8::Local<v8::FunctionTemplate> classDescriptorType = Nan::New<v8::FunctionTemplate>(NogClassDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();

    if(!classDescriptorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ClassDescriptor required");
        return;
    }
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    if(!info[2]->IsString()||!info[2]->IsInt32()){
        Nan::ThrowError("arg3: string or int required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogClassDescriptor* classDesc = ObjectWrap::Unwrap<NogClassDescriptor>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    if(info[2]->IsString()){
        Nan::Utf8String val(info[2]->ToString());
        std::string className (*val);
        classDesc->classDescriptor = nogdb::Db::getSchema(txn->txn,className);
        // const ClassDescriptor Db::getSchema(const Txn &txn, const std::string &className)
    }else if(info[2]->IsInt32()){
        Nan::Maybe<int32_t> val = Nan::To<int32_t>(info[2]);
        int classId = val.FromJust();
        classDesc->classDescriptor = nogdb::Db::getSchema(txn->txn,classId);
        // const ClassDescriptor Db::getSchema(const Txn &txn, const ClassId &classId)
    }
}

void GetRecord(const Nan::FunctionCallbackInfo<v8::Value>& info) {
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

    if(!recordType->HasInstance(arg_1)){
      Nan::ThrowError("arg1: Record required");
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

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    r->record = nogdb::Db::getRecord(txn->txn,recordDesc->recordDescriptor);
    // Record Db::getRecord(const Txn &txn, const RecordDescriptor &recordDescriptor)
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
