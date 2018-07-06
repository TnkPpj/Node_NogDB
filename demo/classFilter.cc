#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "classFilter.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogClassFilter::constructor;

NogClassFilter::NogClassFilter() {};
NogClassFilter::~NogClassFilter() {};

NAN_MODULE_INIT(NogClassFilter::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogClassFilter::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("ClassFilter").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("ClassFilter").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogClassFilter::New) {
      NogClassFilter* obj = new NogClassFilter();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
}