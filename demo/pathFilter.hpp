#ifndef PATH_FILTER_H
#define PATH_FILTER_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogPathFilter : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogPathFilter() ;
        ~NogPathFilter() ;

        static NAN_METHOD(New) ;
};

#endif