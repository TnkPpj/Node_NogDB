#ifndef RESULT_H
#define RESULT_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogResult : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogResult() ;
        ~NogResult() ;

        static NAN_METHOD(New) ;
};

#endif