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

        nogdb::ClassFilter classFilter;

    private:
        explicit NogClassFilter() ;
        ~NogClassFilter() ;

        static NAN_METHOD(New) ;
        static NAN_METHOD(add) ;
        static NAN_METHOD(remove) ;
        static NAN_METHOD(size) ;
        static NAN_METHOD(empty) ;
};

#endif