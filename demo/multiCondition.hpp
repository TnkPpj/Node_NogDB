#ifndef MULTI_CONDITION_H
#define MULTI_CONDITION_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogMultiCondition : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;
        
        nogdb::MultiCondition multiCondition();

    private:
        explicit NogMultiCondition() ;
        ~NogMultiCondition() ;

        static NAN_METHOD(New) ;
};

#endif