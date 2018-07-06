#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "resultSet.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogResultSet::constructor;

NogResultSet::NogResultSet() {};
NogResultSet::~NogResultSet() {};

NAN_MODULE_INIT(NogResultSet::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogResultSet::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("ResultSet").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("ResultSet").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogResultSet::New) {
    NogResultSet* obj = new NogResultSet();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}