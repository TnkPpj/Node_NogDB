#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "condition.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogCondition::constructor;

NogCondition::NogCondition(std::string propertyName) :condition(propertyName) {};
NogCondition::~NogCondition() {};

NAN_MODULE_INIT(NogCondition::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogCondition::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("Condition").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Set(target, Nan::New<v8::String>("Condition").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogCondition::New) {
    if(info.Length()!=1){
        Nan::ThrowError("1 arguments required :( String )");
        return;
    }
    if(!info[0]->IsString()){
        Nan::ThrowError("arg1 string required");
        return;
    }
    Nan::Utf8String val(info[0]->ToString());
    std::string propertyName (*val);
    NogCondition* obj = new NogCondition(propertyName);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}