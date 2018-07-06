#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "classDescriptor.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogClassDescriptor::constructor;

NogClassDescriptor::NogClassDescriptor() {};
NogClassDescriptor::~NogClassDescriptor() {};

NAN_MODULE_INIT(NogClassDescriptor::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogClassDescriptor::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("ClassDescriptor").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    v8::Local<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
    SetAccessor(itpl, Nan::New<v8::String>("id").ToLocalChecked(), NogClassDescriptor::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("name").ToLocalChecked(), NogClassDescriptor::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("type").ToLocalChecked(), NogClassDescriptor::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("properties").ToLocalChecked(), NogClassDescriptor::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("super").ToLocalChecked(), NogClassDescriptor::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("sub").ToLocalChecked(), NogClassDescriptor::getAtt);

    Set(target, Nan::New<v8::String>("getClassDescriptor").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogClassDescriptor::New) {
      NogClassDescriptor* obj = new NogClassDescriptor();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
}

NAN_GETTER(NogClassDescriptor::getAtt) {
    NogClassDescriptor* obj = ObjectWrap::Unwrap<NogClassDescriptor>(info.This());
    
    Nan::Utf8String s(property);
    std::string str(*s, s.length());

    if (str == "id"){
        // info.GetReturnValue().Set(Nan::New<v8::String>(obj->dbInfo.dbPath).ToLocalChecked());
    }else if (str == "name"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxDB).ToLocalChecked());
    }else if (str == "type"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxDBSize).ToLocalChecked());
    }else if (str == "properties"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxPropertyId).ToLocalChecked());
    }else if (str == "super"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.numProperty).ToLocalChecked());
    }else if (str == "sub"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxClassId).ToLocalChecked());
    }
}