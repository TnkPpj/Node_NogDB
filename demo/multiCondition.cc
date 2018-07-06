#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "multiCondition.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogMultiCondition::constructor;

NogMultiCondition::NogMultiCondition() {};
NogMultiCondition::~NogMultiCondition() {};

NAN_MODULE_INIT(NogMultiCondition::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogMultiCondition::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("MultiCondition").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("MultiCondition").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogMultiCondition::New) {
      NogMultiCondition* obj = new NogMultiCondition();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
}