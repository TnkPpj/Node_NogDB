#include <nan.h>

#include <nogdb/nogdb.h>
#include "propertyDescriptor.hpp"
#include "txn.hpp"

#include "property.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogProperty::constructor;

NogProperty::NogProperty() {};
NogProperty::~NogProperty() {};

NAN_MODULE_INIT(NogProperty::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogProperty::New);
    constructor.Reset(tpl);

    tpl->SetClassName(Nan::New<v8::String>("Property").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "add", NogProperty::Add);
    SetPrototypeMethod(tpl, "alter", NogProperty::Alter);
    SetPrototypeMethod(tpl, "remove", NogProperty::Remove);
    SetPrototypeMethod(tpl, "createIndex", NogProperty::CreateIndex);
    SetPrototypeMethod(tpl, "dropIndex", NogProperty::DropIndex);

    Set(target, Nan::New<v8::String>("Property").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogProperty::New) {
    NogProperty* obj = new NogProperty();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(NogProperty::Add) {
      if(info.Length()!=5){
            Nan::ThrowError("5 arguments required");
            return;
      }
      
      v8::Local<v8::FunctionTemplate> propertyDescriptorType = Nan::New<v8::FunctionTemplate>(NogPropertyDescriptor::constructor);
      v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

      v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
      v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
      // get propertyDescriptor for return
      if(!propertyDescriptorType->HasInstance(arg_1)){
            Nan::ThrowError("arg1: PropertyDescriptor required");
            return;
      }
      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogPropertyDescriptor* propertyDescriptor = ObjectWrap::Unwrap<NogPropertyDescriptor>(maybe1.ToLocalChecked());
      // get txn
      if(!txnType->HasInstance(arg_2)){
            Nan::ThrowError("arg2: Txn required");
            return;
      }
      Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
      // get className
      if(!info[2]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      }
      Nan::Utf8String val(info[2]->ToString());
      std::string className (*val);
      // get propertyName
      if(!info[3]->IsString()){
            Nan::ThrowError("arg4: string required");
            return;
      }
      Nan::Utf8String val2(info[3]->ToString());
      std::string propertyName (*val2);
      // get propertyType
      if(!info[4]->IsString()){
            Nan::ThrowError("arg5: string required");
            return;
      }
      Nan::Utf8String val3(info[4]->ToString());
      std::string type (*val3);
      nogdb::PropertyType proptype;
      if(type=="TINYINT")                 proptype = nogdb::PropertyType::TINYINT;
      else if(type=="UNSIGNED_TINYINT")   proptype = nogdb::PropertyType::UNSIGNED_TINYINT;
      else if(type=="SMALLINT")           proptype = nogdb::PropertyType::SMALLINT;
      else if(type=="UNSIGNED_SMALLINT")  proptype = nogdb::PropertyType::UNSIGNED_SMALLINT;
      else if(type=="INTEGER")            proptype = nogdb::PropertyType::INTEGER;
      else if(type=="UNSIGNED_INTEGER")   proptype = nogdb::PropertyType::UNSIGNED_INTEGER;
      else if(type=="BIGINT")             proptype = nogdb::PropertyType::BIGINT;
      else if(type=="UNSIGNED_BIGINT")    proptype = nogdb::PropertyType::UNSIGNED_BIGINT;
      else if(type=="TEXT")               proptype = nogdb::PropertyType::TEXT;
      else if(type=="REAL")               proptype = nogdb::PropertyType::REAL;
      else if(type=="BLOB")               proptype = nogdb::PropertyType::BLOB;
      else Nan::ThrowError("propertyType Invalid");
      // add property
      propertyDescriptor->propertyDescriptor = nogdb::Property::add(*txn->txn,className,propertyName,proptype);
}

NAN_METHOD(NogProperty::Alter) {
      if(info.Length()!=4){
            Nan::ThrowError("4 arguments required");
            return;
      }
      
      v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

      v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
      // get Txn
      if(!txnType->HasInstance(arg_1)){
            Nan::ThrowError("arg1: Txn required");
            return;
      }
      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
      // get className
      if(!info[1]->IsString()){
            Nan::ThrowError("arg2: string required");
            return;
      }
      Nan::Utf8String val(info[1]->ToString());
      std::string className (*val);
      // get oldName
      if(!info[2]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      }
      Nan::Utf8String val2(info[2]->ToString());
      std::string oldName (*val2);
      // get newName
      if(!info[3]->IsString()){
            Nan::ThrowError("arg4: string required");
            return;
      }
      Nan::Utf8String val3(info[3]->ToString());
      std::string newName (*val3);
      // alter property
      nogdb::Property::alter(*txn->txn,className,oldName,newName);
}

NAN_METHOD(NogProperty::Remove) {
      if(info.Length()!=3){
            Nan::ThrowError("3 arguments required");
            return;
      }
      
      v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

      v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
      // get Txn
      if(!txnType->HasInstance(arg_1)){
            Nan::ThrowError("arg1: Txn required");
            return;
      }
      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
      // get className
      if(!info[1]->IsString()){
            Nan::ThrowError("arg2: string required");
            return;
      }
      Nan::Utf8String val(info[1]->ToString());
      std::string className (*val);
      // get propertyName
      if(!info[2]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      }
      Nan::Utf8String val2(info[2]->ToString());
      std::string propertyName (*val2);
      // remove property
      nogdb::Property::remove(*txn->txn,className,propertyName);
}

NAN_METHOD(NogProperty::CreateIndex) {
      if(info.Length()!=4){
            Nan::ThrowError("4 arguments required");
            return;
      }
      
      v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

      v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
      // get Txn
      if(!txnType->HasInstance(arg_1)){
            Nan::ThrowError("arg1: Txn required");
            return;
      }
      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
      // get className
      if(!info[1]->IsString()){
            Nan::ThrowError("arg2: string required");
            return;
      }
      Nan::Utf8String val(info[1]->ToString());
      std::string className (*val);
      // get propertyName
      if(!info[2]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      }
      Nan::Utf8String val2(info[2]->ToString());
      std::string propertyName (*val2);
      // get isUnique
      if(!info[3]->IsBoolean()){
            Nan::ThrowError("arg4: bool required");
            return;
      }
      bool isUnique = info[3]->BooleanValue();
      // create index
      nogdb::Property::createIndex(*txn->txn,className,propertyName,isUnique);
}

NAN_METHOD(NogProperty::DropIndex) {
      if(info.Length()!=3){
            Nan::ThrowError("3 arguments required");
            return;
      }
      
      v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

      v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
      // get Txn
      if(!txnType->HasInstance(arg_1)){
            Nan::ThrowError("arg1: Txn required");
            return;
      }
      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
      // get className
      if(!info[1]->IsString()){
            Nan::ThrowError("arg2: string required");
            return;
      }
      Nan::Utf8String val(info[1]->ToString());
      std::string className (*val);
      // get propertyName
      if(!info[2]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      }
      Nan::Utf8String val2(info[2]->ToString());
      std::string propertyName (*val2);
      // drop index
      nogdb::Property::dropIndex(*txn->txn,className,propertyName);
}
