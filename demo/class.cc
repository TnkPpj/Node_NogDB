#include <nan.h>
#include <nogdb/nogdb.h>

#include "classDescriptor.hpp"
#include "txn.hpp"
#include "class.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogClass::constructor;

NogClass::NogClass() {};
NogClass::~NogClass() {};

NAN_MODULE_INIT(NogClass::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogClass::New);
    constructor.Reset(tpl);

    tpl->SetClassName(Nan::New<v8::String>("Class").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "create", NogClass::Create);
    SetPrototypeMethod(tpl, "createExtend", NogClass::CreateExtend);
    SetPrototypeMethod(tpl, "drop", NogClass::Drop);
    SetPrototypeMethod(tpl, "alter", NogClass::Alter);

    Set(target, Nan::New<v8::String>("Class").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogClass::New) {
    NogClass* obj = new NogClass();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(NogClass::Create) {
      if(info.Length()!=4){
            Nan::ThrowError("4 arguments required");
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
      NogClassDescriptor* classDescriptor = ObjectWrap::Unwrap<NogClassDescriptor>(maybe1.ToLocalChecked());
      // get Txn
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
      std::string name (*val);
      // get classType
      if(!info[3]->IsString()){
            Nan::ThrowError("arg4: string required");
            return;
      }
      Nan::Utf8String val2(info[3]->ToString());
      std::string type (*val2);
      nogdb::ClassType classType;
      if(type=="VERTEX"||type=="vertex")   classType = nogdb::ClassType::VERTEX; 
      else  if(type=="EDGE"||type=="edge") classType = nogdb::ClassType::EDGE;
      else Nan::ThrowError("classType Invalid");
      // create class
      classDescriptor->classDescriptor = nogdb::Class::create(txn->txn,name,classType);
}

NAN_METHOD(NogClass::CreateExtend) {
      if(info.Length()!=4){
            Nan::ThrowError("4 arguments required");
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
      NogClassDescriptor* classDescriptor = ObjectWrap::Unwrap<NogClassDescriptor>(maybe1.ToLocalChecked());
      // get Txn
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
      // get superClassName
      if(!info[3]->IsString()){
            Nan::ThrowError("arg4: string required");
            return;
      }
      Nan::Utf8String val2(info[3]->ToString());
      std::string superClassName (*val2);
      // create extendClass
      classDescriptor->classDescriptor = nogdb::Class::createExtend(txn->txn,className,superClassName);
}

NAN_METHOD(NogClass::Drop) {
      if(info.Length()!=2){
            Nan::ThrowError("2 arguments required");
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
      std::string name (*val);
      // drop class
      nogdb::Class::drop(txn->txn,name);
}

NAN_METHOD(NogClass::Alter) {
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
      // get oldClassName
      if(!info[1]->IsString()){
            Nan::ThrowError("arg2: string required");
            return;
      }
      Nan::Utf8String val(info[1]->ToString());
      std::string oldClassName (*val);
      // get newClassName
      if(!info[2]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      } 
      Nan::Utf8String val2(info[2]->ToString());
      std::string newClassName (*val2);
      // alter class
      nogdb::Class::alter(txn->txn,oldClassName,newClassName);
}
