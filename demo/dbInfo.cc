#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "dbInfo.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogDBInfo::constructor;

NogDBInfo::NogDBInfo() {};
NogDBInfo::~NogDBInfo() {};

NAN_MODULE_INIT(NogDBInfo::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogDBInfo::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("DBInfo").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    v8::Local<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
    SetAccessor(itpl, Nan::New<v8::String>("dbPath").ToLocalChecked(), NogDBInfo::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("maxDB").ToLocalChecked(), NogDBInfo::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("maxDBSize").ToLocalChecked(), NogDBInfo::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("maxPropertyId").ToLocalChecked(), NogDBInfo::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("numProperty").ToLocalChecked(), NogDBInfo::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("maxClassId").ToLocalChecked(), NogDBInfo::getAtt);
    SetAccessor(itpl, Nan::New<v8::String>("numClass").ToLocalChecked(), NogDBInfo::getAtt);

    Set(target, Nan::New<v8::String>("DBInfo").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogDBInfo::New) {
    NogDBInfo* obj = new NogDBInfo();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}
  
NAN_GETTER(NogDBInfo::getAtt) {
    NogDBInfo* obj = ObjectWrap::Unwrap<NogDBInfo>(info.This());
    
    Nan::Utf8String s(property);
    std::string str(*s, s.length());

    if (str == "dbPath"){
        // info.GetReturnValue().Set(Nan::New<v8::String>(obj->dbInfo.dbPath).ToLocalChecked());
    }else if (str == "maxDB"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxDB).ToLocalChecked());
    }else if (str == "maxDBSize"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxDBSize).ToLocalChecked());
    }else if (str == "maxPropertyId"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxPropertyId).ToLocalChecked());
    }else if (str == "numProperty"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.numProperty).ToLocalChecked());
    }else if (str == "maxClassId"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.maxClassId).ToLocalChecked());
    }else if (str == "numClass"){
        // info.GetReturnValue().Set(Nan::New<v8::Uint32>(obj->dbInfo.numClass).ToLocalChecked());   
    }
}