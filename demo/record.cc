#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "record.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogRecord::constructor;

NogRecord::NogRecord() {};
NogRecord::~NogRecord() {};

NAN_MODULE_INIT(NogRecord::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogRecord::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("Record").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("Record").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogRecord::New) {
    NogRecord* obj = new NogRecord();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}