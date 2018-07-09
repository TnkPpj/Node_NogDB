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
    SetPrototypeMethod(tpl, "hasNext", NogResultSetCursor::hasNext);
    SetPrototypeMethod(tpl, "hasPrevious", NogResultSetCursor::hasPrevious);
    SetPrototypeMethod(tpl, "hasAt", NogResultSetCursor::hasAt);
    SetPrototypeMethod(tpl, "next", NogResultSetCursor::next);
    SetPrototypeMethod(tpl, "previous", NogResultSetCursor::previous);
    SetPrototypeMethod(tpl, "empty", NogResultSetCursor::empty);
    SetPrototypeMethod(tpl, "size", NogResultSetCursor::size);
    SetPrototypeMethod(tpl, "count", NogResultSetCursor::count);
    SetPrototypeMethod(tpl, "first", NogResultSetCursor::first);\
    SetPrototypeMethod(tpl, "last", NogResultSetCursor::last);
    SetPrototypeMethod(tpl, "to", NogResultSetCursor::to);

    Set(target, Nan::New<v8::String>("ResultSetCursor").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogResultSetCursor::New) {
    NogResultSetCursor* obj = new NogResultSetCursor();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}
NAN_METHOD(NogResultSetCursor::hasNext){}
NAN_METHOD(NogResultSetCursor::hasPrevious){}
NAN_METHOD(NogResultSetCursor::hasAt){}
NAN_METHOD(NogResultSetCursor::next){}
NAN_METHOD(NogResultSetCursor::previous){}
NAN_METHOD(NogResultSetCursor::empty){}
NAN_METHOD(NogResultSetCursor::size){}
NAN_METHOD(NogResultSetCursor::count){}
NAN_METHOD(NogResultSetCursor::first){}
NAN_METHOD(NogResultSetCursor::last){}
NAN_METHOD(NogResultSetCursor::to){}