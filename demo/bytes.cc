#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "bytes.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogBytes::constructor;

NogBytes::NogBytes() {};
NogBytes::~NogBytes() {};

NAN_MODULE_INIT(NogBytes::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogBytes::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("Bytes").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("Bytes").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogBytes::New) {
      NogBytes* obj = new NogBytes();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
}