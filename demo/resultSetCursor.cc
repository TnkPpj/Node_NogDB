#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "resultSetCursor.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogResultSetCursor::constructor;

NogResultSetCursor::NogResultSetCursor() {};
NogResultSetCursor::~NogResultSetCursor() {};

NAN_MODULE_INIT(NogResultSetCursor::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("ResultsetCursor").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("ResultSetCursor").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogResultSetCursor::New) {
    NogResultSetCursor* obj = new NogResultSetCursor();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}