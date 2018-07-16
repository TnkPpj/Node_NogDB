#ifndef CLASS_H
#define CLASS_H

#include <nan.h>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogClass : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogClass() ;
        ~NogClass() ;

        static NAN_METHOD(New) ;
  
        static NAN_METHOD(Create) ;
        static NAN_METHOD(CreateExtend) ;
        static NAN_METHOD(Drop) ;
        static NAN_METHOD(Alter) ;
};

#endif