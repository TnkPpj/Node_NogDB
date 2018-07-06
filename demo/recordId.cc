#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "recordId.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogRecordId::constructor;

NogRecordId::NogRecordId() {};
NogRecordId::~NogRecordId() {};

NAN_MODULE_INIT(NogRecordId::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogRecordId::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("RecordId").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("RecordId").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogRecordId::New) {
    NogRecordId* obj = new NogRecordId();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}