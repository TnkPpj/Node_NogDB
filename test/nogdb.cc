#include <cmath>
#include <nan.h>
#include <string>

#include "nogdb.h"

#include <nogdb/nogdb.h>

using namespace Nan;

  NAN_MODULE_INIT(NogdbTest::Init) {
      v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogdbTest::New);
      constructor.Reset(tpl);
      tpl->SetClassName(Nan::New<v8::String>("Test").ToLocalChecked());
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      SetPrototypeMethod(tpl, "txnW", NogdbTest::TXNWrite);
      SetPrototypeMethod(tpl, "txnR", NogdbTest::TXNRead);

      Set(target, Nan::New<v8::String>("Test").ToLocalChecked(), tpl->GetFunction());
  }

  NogdbTest::NogdbTest() {};
  NogdbTest::~NogdbTest() {};

  NAN_METHOD(NogdbTest::New) {
      NogdbTest* obj = new NogdbTest();
      obj->Wrap(info.This());
      
      info.GetReturnValue().Set(info.This());
  }


  NAN_MODULE_INIT(NogContext::Init) {
      v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogContext::New);
      constructor.Reset(tpl);
      tpl->SetClassName(Nan::New<v8::String>("Context").ToLocalChecked());
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      SetPrototypeMethod(tpl, "getMaxVersionId", NogContext::getMaxVersionId);
      SetPrototypeMethod(tpl, "getMaxTxnId", NogContext::getMaxTxnId);
      SetPrototypeMethod(tpl, "getMinActiveTxnId", NogContext::getMinActiveTxnId);

      Set(target, Nan::New<v8::String>("Context").ToLocalChecked(), tpl->GetFunction());
  }

  NogContext::NogContext(std::string dbname) : ctx(dbname) {};
  NogContext::~NogContext() {};

  static NAN_METHOD(NogContext::New) {
      v8::String::Utf8Value val(info[0]->ToString());
      std::string dbname (*val);
      NogContext* obj = new NogContext(dbname);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
  }
  
  static NAN_METHOD(NogContext::getMaxVersionId) {
      NogContext* obj = ObjectWrap::Unwrap<NogContext>(info.Holder());
      int maxVerId =  obj->ctx.getMaxVersionId();
      info.GetReturnValue().Set(maxVerId);
  }

  static NAN_METHOD(NogContext::getMaxTxnId) {
      NogContext* obj = ObjectWrap::Unwrap<NogContext>(info.Holder());
      int maxTxnId =  obj->ctx.getMaxTxnId();
      info.GetReturnValue().Set(maxTxnId);
  }

  static NAN_METHOD(NogContext::getMinActiveTxnId) {}


   NAN_MODULE_INIT(NogTxn::Init) {
      v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogTxn::New);
      constructor.Reset(tpl);
      tpl->SetClassName(Nan::New<v8::String>("Txn").ToLocalChecked());
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      SetPrototypeMethod(tpl, "commit", NogTxn::commit);
      SetPrototypeMethod(tpl, "rollback", NogTxn::rollback);
      SetPrototypeMethod(tpl, "getTxnId", NogTxn::getTxnId);
      SetPrototypeMethod(tpl, "getVersionId", NogTxn::getVersionId);
      SetPrototypeMethod(tpl, "getTxnMode", NogTxn::getTxnMode);

      Set(target, Nan::New<v8::String>("Txn").ToLocalChecked(), tpl->GetFunction());
  }

  NogTxn::NogTxn(nogdb::Context ctx, const nogdb::Txn::Mode& mode) : txn(ctx,mode)  {};
  NogTxn::~NogTxn() {};

  NAN_METHOD(NogTxn::New) {
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    std::cout << info.Length() << std::endl;
    NogContext* obj = ObjectWrap::Unwrap<NogContext>(maybe1.ToLocalChecked());
    nogdb::Context ctx = obj->ctx;
    v8::String::Utf8Value val(info[1]->ToString());
    std::string str (*val);
    if(str=="READ_WRITE"){
        NogTxn* obj2 = new NogTxn(ctx,nogdb::Txn::Mode::READ_WRITE);
      obj2->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    }else if(str=="READ_ONLY"){
        NogTxn* obj2 = new NogTxn(ctx,nogdb::Txn::Mode::READ_ONLY);
      obj2->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    }
  }

  NAN_METHOD(NogTxn::commit) {
      NogTxn* obj = ObjectWrap::Unwrap<NogTxn>(info.Holder());
      obj->txn.commit();
  }
  NAN_METHOD(NogTxn::rollback) {
      NogTxn* obj = ObjectWrap::Unwrap<NogTxn>(info.Holder());
      obj->txn.rollback();
  }
  NAN_METHOD(NogTxn::getTxnId) {
      NogTxn* obj = ObjectWrap::Unwrap<NogTxn>(info.Holder());
      int txnId =  obj->txn.getTxnId();
      info.GetReturnValue().Set(txnId);
  }
  NAN_METHOD(NogTxn::getVersionId) {
      NogTxn* obj = ObjectWrap::Unwrap<NogTxn>(info.Holder());
      int verId =  obj->txn.getVersionId();
      info.GetReturnValue().Set(verId);
  }
  NAN_METHOD(NogTxn::getTxnMode) {
      NogTxn* obj = ObjectWrap::Unwrap<NogTxn>(info.Holder());
      int txnMode =  obj->txn.getTxnMode();
      info.GetReturnValue().Set(txnMode);
  }


  NAN_MODULE_INIT(NogDBInfo::Init) {
      v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogDBInfo::New);
      constructor.Reset(tpl);
      tpl->SetClassName(Nan::New<v8::String>("DBInfo").ToLocalChecked());
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      v8::Local<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
      SetAccessor(itpl, Nan::New<v8::String>("dbPath").ToLocalChecked(), NogDBInfo::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("maxDB").ToLocalChecked(), NogDBInfo::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("maxDBSize").ToLocalChecked(), NogDBInfo::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("maxPropertyId").ToLocalChecked(), NogDBInfo::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("numProperty").ToLocalChecked(), NogDBInfo::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("maxClassId").ToLocalChecked(), NogDBInfo::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("numClass").ToLocalChecked(), NogDBInfo::getAtt);

      Set(target, Nan::New<v8::String>("DBInfo").ToLocalChecked(), tpl->GetFunction());
  }

  NogDBInfo::NogDBInfo() {};
  NogDBInfo::~NogDBInfo() {};

  NAN_METHOD(NogDBInfo::New) {
      NogDBInfo* obj = new NogDBInfo();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
  }

  NAN_GETTER(NogDBInfo::getAtt) {
    NogDBInfo* obj = ObjectWrap::Unwrap<NogDBInfo>(info.This());
    
    v8::String::Utf8Value s(property);
    std::string str(*s, s.length());

    if (str == "dbPath"){
        // info.GetReturnValue().Set(Nan::New<v8::String>(obj->dbInfo.dbPath).ToLocalChecked());
    }else if (str == "maxDB"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxDB).ToLocalChecked());
    }else if (str == "maxDBSize"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxDBSize).ToLocalChecked());
    }else if (str == "maxPropertyId"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxPropertyId).ToLocalChecked());
    }else if (str == "numProperty"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.numProperty).ToLocalChecked());
    }else if (str == "maxClassId"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxClassId).ToLocalChecked());
    }else if (str == "numClass"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.numClass).ToLocalChecked());   
    }
  }


   NAN_MODULE_INIT(NogClassDescriptor::Init) {
      v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogClassDescriptor::New);
      constructor.Reset(tpl);
      tpl->SetClassName(Nan::New<v8::String>("ClassDescriptor").ToLocalChecked());
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      v8::Local<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
      SetAccessor(itpl, Nan::New<v8::String>("id").ToLocalChecked(), NogClassDescriptor::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("name").ToLocalChecked(), NogClassDescriptor::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("type").ToLocalChecked(), NogClassDescriptor::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("properties").ToLocalChecked(), NogClassDescriptor::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("super").ToLocalChecked(), NogClassDescriptor::getAtt);
      SetAccessor(itpl, Nan::New<v8::String>("sub").ToLocalChecked(), NogClassDescriptor::getAtt);

      Set(target, Nan::New<v8::String>("getClassDescriptor").ToLocalChecked(), tpl->GetFunction());
  }
  NogClassDescriptor::NogClassDescriptor() {};
  NogClassDescriptor::~NogClassDescriptor() {};
  
  NAN_METHOD(NogClassDescriptor::New) {
      NogClassDescriptor* obj = new NogClassDescriptor();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
  }

  NAN_GETTER(NogClassDescriptor::getAtt) {
    NogClassDescriptor* obj = ObjectWrap::Unwrap<NogClassDescriptor>(info.This());
    
    v8::String::Utf8Value s(property);
    std::string str(*s, s.length());

    if (str == "id"){
        // info.GetReturnValue().Set(Nan::New<v8::String>(obj->dbInfo.dbPath).ToLocalChecked());
    }else if (str == "name"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxDB).ToLocalChecked());
    }else if (str == "type"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxDBSize).ToLocalChecked());
    }else if (str == "properties"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxPropertyId).ToLocalChecked());
    }else if (str == "super"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.numProperty).ToLocalChecked());
    }else if (str == "sub"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxClassId).ToLocalChecked());
    }
  }

NAN_METHOD(NogdbTest::TXNWrite){
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* obj = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
    std::cout << obj->txn.getTxnId() << std::endl;
}

NAN_METHOD(NogdbTest::TXNRead){
 Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* obj = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

    nogdb::Txn &txn = obj->txn;
    std::cout << txn.getTxnId() << std::endl;
    std::cout << txn.getVersionId() << std::endl;
    std::cout << txn.getTxnMode() << std::endl;
    std::cout << "----------------" << std::endl;
    try {
        obj->txn.commit();
    } catch (const nogdb::Error &e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
  
// void InitNogdb(v8::Local<v8::Object> exports) {
//   NogdbTest::Init(exports);
//   NogContext::Init(exports);
//   NogTxn::Init(exports);
//   NogDBInfo::Init(exports);
//   NogClassDescriptor::Init(exports);
// }

// NODE_MODULE(nogdb, InitNogdb)
