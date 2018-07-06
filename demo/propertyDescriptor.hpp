#ifndef PROPERTY_DESCRIPTOR_H
#define PROPERTY_DESCRIPTOR_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogPropertyDescriptor : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::PropertyDescriptor propertyDescriptor;

    private:
        explicit NogPropertyDescriptor() ;
        ~NogPropertyDescriptor() ;

        static NAN_METHOD(New) ;
};

#endif