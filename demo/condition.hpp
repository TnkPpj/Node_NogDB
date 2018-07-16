#ifndef CONDITION_H
#define CONDITION_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogCondition : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::Condition condition;

    private:
        explicit NogCondition(std::string propertyName) ;
        ~NogCondition() ;

        static NAN_METHOD(New) ;
};

#endif