#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "recordDescriptor.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogRecordDescriptor::constructor;

NogRecordDescriptor::NogRecordDescriptor() {};
NogRecordDescriptor::~NogRecordDescriptor() {};

NAN_MODULE_INIT(NogRecordDescriptor::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("RecordDescriptor").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("RecordDescriptor").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogRecordDescriptor::New) {
    NogRecordDescriptor* obj = new NogRecordDescriptor();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}