#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

#include "classFilter.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogClassFilter::constructor;

NogClassFilter::NogClassFilter() {};
NogClassFilter::~NogClassFilter() {};

NAN_MODULE_INIT(NogClassFilter::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogClassFilter::New);
    constructor.Reset(tpl);
    tpl->SetClassName(Nan::New<v8::String>("ClassFilter").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    SetPrototypeMethod(tpl, "add", NogClassFilter::add);
    SetPrototypeMethod(tpl, "remove", NogClassFilter::remove);
    SetPrototypeMethod(tpl, "size", NogClassFilter::size);
    SetPrototypeMethod(tpl, "empty", NogClassFilter::empty);

    Set(target, Nan::New<v8::String>("ClassFilter").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogClassFilter::New) {
      NogClassFilter* obj = new NogClassFilter();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
}

NAN_METHOD(NogClassFilter::add){

}
NAN_METHOD(NogClassFilter::remove){
    
}
NAN_METHOD(NogClassFilter::size){
    
}
NAN_METHOD(NogClassFilter::empty){
    
}