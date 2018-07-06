#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "result.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogResult::constructor;

NogResult::NogResult() {};
NogResult::~NogResult() {};

NAN_MODULE_INIT(NogResult::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogResult::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("Result").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("Result").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogResult::New) {
    NogResult* obj = new NogResult();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}