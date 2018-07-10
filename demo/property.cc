#include <nan.h>

#include <nogdb/nogdb.h>
#include "propertyDescriptor.hpp"
#include "txn.hpp"

void Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {
      if(info.Length()!=5){
            Nan::ThrowError("5 arguments required");
            return;
      }
      
      v8::Local<v8::FunctionTemplate> propertyDescriptorType = Nan::New<v8::FunctionTemplate>(NogPropertyDescriptor::constructor);
      v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

      v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
      v8::Handle<v8::Object> arg_2 = info[1]->ToObject();

      if(!propertyDescriptorType->HasInstance(arg_1)){
            Nan::ThrowError("arg1: PropertyDescriptor required");
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
      if(!info[4]->IsString()){
            Nan::ThrowError("arg5: string required");
            return;
      }

      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogPropertyDescriptor* propDesc = ObjectWrap::Unwrap<NogPropertyDescriptor>(maybe1.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

      Nan::Utf8String val(info[2]->ToString());
      std::string className (*val);

      Nan::Utf8String val2(info[3]->ToString());
      std::string propertyName (*val2);

      Nan::Utf8String val3(info[4]->ToString());
      std::string type (*val3);
      nogdb::PropertyType proptype;

      if(type=="TINYINT") proptype = nogdb::PropertyType::TINYINT;
      else if(type=="UNSIGNED_TINYINT") proptype = nogdb::PropertyType::UNSIGNED_TINYINT;
      else if(type=="SMALLINT") proptype = nogdb::PropertyType::SMALLINT;
      else if(type=="UNSIGNED_SMALLINT") proptype = nogdb::PropertyType::UNSIGNED_SMALLINT;
      else if(type=="INTEGER") proptype = nogdb::PropertyType::INTEGER;
      else if(type=="UNSIGNED_INTEGER") proptype = nogdb::PropertyType::UNSIGNED_INTEGER;
      else if(type=="BIGINT") proptype = nogdb::PropertyType::BIGINT;
      else if(type=="UNSIGNED_BIGINT") proptype = nogdb::PropertyType::UNSIGNED_BIGINT;
      else if(type=="TEXT") proptype = nogdb::PropertyType::TEXT;
      else if(type=="REAL") proptype = nogdb::PropertyType::REAL;
      else if(type=="BLOB") proptype = nogdb::PropertyType::BLOB;
      else Nan::ThrowError("propertyType Invalid");

      propDesc->propertyDescriptor = nogdb::Property::add(txn->txn,className,propertyName,proptype);
      // const PropertyDescriptor Property::add(Txn &txn, const std::string &className, const std::string &propertyName, PropertyType type)
}

void Alter(const Nan::FunctionCallbackInfo<v8::Value>& info) {
      if(info.Length()!=4){
            Nan::ThrowError("4 arguments required");
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
      if(!info[3]->IsString()){
            Nan::ThrowError("arg4: string required");
            return;
      }

      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
      
      Nan::Utf8String val(info[1]->ToString());
      std::string className (*val);

      Nan::Utf8String val2(info[2]->ToString());
      std::string oldName (*val2);

      Nan::Utf8String val3(info[3]->ToString());
      std::string newName (*val3);

      nogdb::Property::alter(txn->txn,className,oldName,newName);
      // void Property::alter(Txn &txn, const std::string &className, const std::string &oldPropertyName, const std::string &newPropertyName)
}

void Remove(const Nan::FunctionCallbackInfo<v8::Value>& info) {
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
      if(!info[2]->IsString()){
            Nan::ThrowError("arg2: string required");
            return;
      }
      if(!info[3]->IsString()){
            Nan::ThrowError("arg3: string required");
            return;
      }

      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
      
      Nan::Utf8String val(info[1]->ToString());
      std::string className (*val);

      Nan::Utf8String val2(info[2]->ToString());
      std::string propertyName (*val2);

      nogdb::Property::remove(txn->txn,className,propertyName);
      // void Property::remove(Txn &txn, const std::string &className, const std::string &propertyName)
}

void CreateIndex(const Nan::FunctionCallbackInfo<v8::Value>& info) {
      if(info.Length()!=4){
            Nan::ThrowError("4 arguments required");
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
      if(!info[3]->IsBoolean()){
            Nan::ThrowError("arg4: bool required");
            return;
      }

      Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
      NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
      
      Nan::Utf8String val(info[1]->ToString());
      std::string className (*val);

      Nan::Utf8String val2(info[2]->ToString());
      std::string propertyName (*val2);

      bool isUnique = info[3]->BooleanValue();

      nogdb::Property::createIndex(txn->txn,className,propertyName,isUnique);
      // void Property::createIndex(Txn &txn, const std::string &className, const std::string &propertyName, bool isUnique)
}

void DropIndex(const Nan::FunctionCallbackInfo<v8::Value>& info) {
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
      std::string className (*val);

      Nan::Utf8String val2(info[2]->ToString());
      std::string propertyName (*val2);

      nogdb::Property::dropIndex(txn->txn,className,propertyName);
      // void Property::dropIndex(Txn &txn, const std::string &className, const std::string &propertyName)
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
