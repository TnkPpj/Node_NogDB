#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "context.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogContext::constructor;

NogContext::NogContext(std::string dbname) : ctx(dbname) {};
NogContext::~NogContext() {};

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

NAN_METHOD(NogContext::New) {
    Nan::Utf8String val(info[0]->ToString());
    std::string dbname (*val);
    NogContext* obj = new NogContext(dbname);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}
  
NAN_METHOD(NogContext::getMaxVersionId) {
    NogContext* obj = ObjectWrap::Unwrap<NogContext>(info.Holder());
    int maxVerId =  obj->ctx.getMaxVersionId();
    info.GetReturnValue().Set(maxVerId);
}

NAN_METHOD(NogContext::getMaxTxnId) {
    NogContext* obj = ObjectWrap::Unwrap<NogContext>(info.Holder());
    int maxTxnId =  obj->ctx.getMaxTxnId();
    info.GetReturnValue().Set(maxTxnId);
}

NAN_METHOD(NogContext::getMinActiveTxnId) {}