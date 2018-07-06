#ifndef RECORD_H
#define RECORD_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogRecord : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::Record record;

    private:
        explicit NogRecord() ;
        ~NogRecord() ;

        static NAN_METHOD(New) ;
};

#endif