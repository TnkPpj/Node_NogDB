#ifndef CLASS_DESCRIPTOR_H
#define CLASS_DESCRIPTOR_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogClassDescriptor : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::ClassDescriptor& classDescriptor;

    private:
        explicit NogClassDescriptor() ;
        ~NogClassDescriptor() ;
  
        static NAN_METHOD(New) ;

        static NAN_GETTER(getAtt) ;
};

#endif