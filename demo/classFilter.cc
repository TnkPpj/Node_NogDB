#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "classFilter.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogClassFilter::constructor;

NogClassFilter::NogClassFilter(const std::set<std::string> &classNames_):classFilter(classNames_) {};
NogClassFilter::~NogClassFilter() {};

NAN_MODULE_INIT(NogClassFilter::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogClassFilter::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("ClassFilter").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    SetPrototypeMethod(tpl, "add", NogClassFilter::Add);
    SetPrototypeMethod(tpl, "remove", NogClassFilter::Remove);
    SetPrototypeMethod(tpl, "size", NogClassFilter::Size);
    SetPrototypeMethod(tpl, "empty", NogClassFilter::Empty);
    SetPrototypeMethod(tpl, "getClassName", NogClassFilter::GetClassName);

    Set(target, Nan::New<v8::String>("ClassFilter").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogClassFilter::New) {
    if(!info[0]->IsArray()){
        Nan::ThrowError("arg1 Array required");
        return;
    }
    v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(info[0]);
    std::set<std::string> classNames;
    for (unsigned int i = 0; i < array->Length(); i++ ) {
        if (Nan::Has(array, i).FromJust()) {
            if(!Nan::Get(array, i).ToLocalChecked()->IsString()){
                Nan::ThrowError("Array member must be string");
                return;
            }
            Nan::Utf8String val(Nan::Get(array, i).ToLocalChecked()->ToString());
            std::string className (*val);
            classNames.insert(className);
        }
    }
    NogClassFilter* obj = new NogClassFilter(classNames);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(NogClassFilter::Add){
    if(!info[0]->IsString()){
        Nan::ThrowError("arg1 string required");
        return;
    }
    Nan::Utf8String val(info[0]->ToString());
    std::string className (*val);
    NogClassFilter* obj = ObjectWrap::Unwrap<NogClassFilter>(info.Holder());
    obj->classFilter.add(className);
}
NAN_METHOD(NogClassFilter::Remove){
    if(!info[0]->IsString()){
        Nan::ThrowError("arg1 string required");
        return;
    }
    Nan::Utf8String val(info[0]->ToString());
    std::string className (*val);
    NogClassFilter* obj = ObjectWrap::Unwrap<NogClassFilter>(info.Holder());
    obj->classFilter.remove(className);
}
NAN_METHOD(NogClassFilter::Size){
    NogClassFilter* obj = ObjectWrap::Unwrap<NogClassFilter>(info.Holder());
    int size =  obj->classFilter.size();
    info.GetReturnValue().Set(size);
}
NAN_METHOD(NogClassFilter::Empty){
    NogClassFilter* obj = ObjectWrap::Unwrap<NogClassFilter>(info.Holder());
    bool empty = obj->classFilter.empty();
    v8::Local<v8::Boolean> retval = Nan::New(empty);
    info.GetReturnValue().Set(retval);
}
NAN_METHOD(NogClassFilter::GetClassName){
    NogClassFilter* obj = ObjectWrap::Unwrap<NogClassFilter>(info.Holder());
    std::set<std::string> classNames = obj->classFilter.getClassName();
    v8::Local<v8::Array> retval = Nan::New<v8::Array>(classNames.size());
    int i = 0;
    for(std::string className: classNames){
        Nan::Set(retval, i, Nan::New<v8::String>(className).ToLocalChecked());
        i++;
    }
    info.GetReturnValue().Set(retval);
}