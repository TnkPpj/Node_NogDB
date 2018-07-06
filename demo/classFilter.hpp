#ifndef CLASS_FILTER_H
#define CLASS_FILTER_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogClassFilter : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogClassFilter() ;
        ~NogClassFilter() ;

        static NAN_METHOD(New) ;
};

#endif