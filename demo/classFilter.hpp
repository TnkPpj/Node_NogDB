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
        explicit NogClassFilter(const std::set<std::string> &classNames_) ;
        ~NogClassFilter() ;

        static NAN_METHOD(New) ;
        static NAN_METHOD(Add) ;
        static NAN_METHOD(Remove) ;
        static NAN_METHOD(Size) ;
        static NAN_METHOD(Empty) ;
        static NAN_METHOD(GetClassName);
};

#endif