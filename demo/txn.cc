#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "txn.hpp"
#include "context.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogTxn::constructor;

NogTxn::NogTxn(nogdb::Context ctx, const nogdb::Txn::Mode& mode) : txn(ctx,mode)  {};
NogTxn::~NogTxn() {};

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

NAN_METHOD(NogTxn::New) {
//       if(info.Length()==2){
    v8::Handle<v8::Object> fromObj = info[0]->ToObject();
    v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(NogContext::constructor);

    std::cout << constructorHandle->HasInstance(fromObj) << std::endl;
//   }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    std::cout << info.Length() << std::endl;
    NogContext* obj = ObjectWrap::Unwrap<NogContext>(maybe1.ToLocalChecked());
    nogdb::Context ctx = obj->ctx;
    Nan::Utf8String val(info[1]->ToString());
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
