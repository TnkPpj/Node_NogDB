#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "condition.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogCondition::constructor;

NogCondition::NogCondition() {};
NogCondition::~NogCondition() {};

NAN_MODULE_INIT(NogCondition::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogCondition::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("Condition").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("Condition").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogCondition::New) {
      NogCondition* obj = new NogCondition();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
}