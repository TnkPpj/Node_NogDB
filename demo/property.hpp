#ifndef PROPERTY_H
#define PROPERTY_H

#include <nan.h>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogProperty : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogProperty() ;
        ~NogProperty() ;

        static NAN_METHOD(New) ;
  
        static NAN_METHOD(Add) ;
        static NAN_METHOD(Alter) ;
        static NAN_METHOD(Remove) ;
        static NAN_METHOD(CreateIndex) ;
        static NAN_METHOD(DropIndex) ;
};

#endif