#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "propertyDescriptor.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogPropertyDescriptor::constructor;

NogPropertyDescriptor::NogPropertyDescriptor() {};
NogPropertyDescriptor::~NogPropertyDescriptor() {};

NAN_MODULE_INIT(NogPropertyDescriptor::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogPropertyDescriptor::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("PropertyDescriptor").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("PropertyDescriptor").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogPropertyDescriptor::New) {
    NogPropertyDescriptor* obj = new NogPropertyDescriptor();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}