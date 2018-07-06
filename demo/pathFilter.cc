#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "pathFilter.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogPathFilter::constructor;

NogPathFilter::NogPathFilter() {};
NogPathFilter::~NogPathFilter() {};

NAN_MODULE_INIT(NogPathFilter::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogPathFilter::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("PathFilter").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("PathFilter").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogPathFilter::New) {
    NogPathFilter* obj = new NogPathFilter();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}