#ifndef RECORD_DESCRIPTOR_H
#define RECORD_DESCRIPTOR_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogRecordDescriptor : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogRecordDescriptor() ;
        ~NogRecordDescriptor() ;

        static NAN_METHOD(New) ;
};

#endif