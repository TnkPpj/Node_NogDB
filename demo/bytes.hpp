#ifndef BYTES_H
#define BYTES_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogBytes : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::Bytes bytes;

    private:
        explicit NogBytes() ;
        ~NogBytes() ;

        static NAN_METHOD(New) ;
};

#endif