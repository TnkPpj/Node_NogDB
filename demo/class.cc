#include <nan.h>
#include <nogdb/nogdb.h>

#include "classDescriptor.hpp"
#include "txn.hpp"

void Create(const Nan::FunctionCallbackInfo<v8::Value>& info) {
      if(info.Length()!=4){
            Nan::ThrowError("4 arguments required");
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
      if(!info[2]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      }
      if(!info[3]->IsString()){
            Nan::ThrowError("arg4: string required");
            return;
      }

      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogClassDescriptor* classDesc = ObjectWrap::Unwrap<NogClassDescriptor>(maybe1.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

      Nan::Utf8String val(info[2]->ToString());
      std::string name (*val);

      Nan::Utf8String val2(info[3]->ToString());
      std::string type (*val2);

      if(type=="VERTEX"||type=="vertex"){
            classDesc->classDescriptor = nogdb::Class::create(txn->txn,name,nogdb::ClassType::VERTEX);
      } else if(type=="EDGE"||type=="edge"){
            classDesc->classDescriptor = nogdb::Class::create(txn->txn,name,nogdb::ClassType::EDGE);
      } else {
            Nan::ThrowError("classType Invalid");
      }
      // const ClassDescriptor Class::create(Txn &txn, const std::string &className, ClassType type)
}

void CreateExtend(const Nan::FunctionCallbackInfo<v8::Value>& info) {
      if(info.Length()!=4){
            Nan::ThrowError("4 arguments required");
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
      if(!info[2]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      }
      if(!info[3]->IsString()){
            Nan::ThrowError("arg4: string required");
            return;
      }
  
      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogClassDescriptor* classDesc = ObjectWrap::Unwrap<NogClassDescriptor>(maybe1.ToLocalChecked());
  
      Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
  
      Nan::Utf8String val(info[2]->ToString());
      std::string className (*val);

      Nan::Utf8String val2(info[3]->ToString());
      std::string superClassName (*val2);

      classDesc->classDescriptor = nogdb::Class::createExtend(txn->txn,className,superClassName);
// const ClassDescriptor Class::createExtend(Txn &txn, const std::string &className, const std::string &superClass)
}

void Alter(const Nan::FunctionCallbackInfo<v8::Value>& info) {
      if(info.Length()!=3){
            Nan::ThrowError("3 arguments required");
            return;
      }
      
      v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

      v8::Handle<v8::Object> arg_1 = info[0]->ToObject();

      if(!txnType->HasInstance(arg_1)){
            Nan::ThrowError("arg1: Txn required");
            return;
      }
      if(!info[1]->IsString()){
            Nan::ThrowError("arg2: string required");
            return;
      }
      if(!info[2]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      }
      
      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
      
      Nan::Utf8String val(info[1]->ToString());
      std::string oldClassName (*val);

      Nan::Utf8String val2(info[2]->ToString());
      std::string newClassName (*val2);

      nogdb::Class::alter(txn->txn,oldClassName,newClassName);
  // void Class::alter(Txn &txn, const std::string &oldClassName, const std::string &newClassName)
}

void Drop(const Nan::FunctionCallbackInfo<v8::Value>& info) {
      if(info.Length()!=2){
            Nan::ThrowError("2 arguments required");
            return;
      }
      
      v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

      v8::Handle<v8::Object> arg_1 = info[0]->ToObject();

      if(!txnType->HasInstance(arg_1)){
            Nan::ThrowError("arg1: Txn required");
            return;
      }
      if(!info[1]->IsString()){
            Nan::ThrowError("arg2: string required");
            return;
      }

      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
      
      Nan::Utf8String val(info[1]->ToString());
      std::string name (*val);

      nogdb::Class::drop(txn->txn,name);
  // void Class::drop(Txn &txn, const std::string &className)
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
