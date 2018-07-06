#ifndef RESULT_SET_H
#define RESULT_SET_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogResultSet : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogResultSet() ;
        ~NogResultSet() ;

        static NAN_METHOD(New) ;
};

#endif