#ifndef DB_H
#define DB_H

#include <nan.h>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogDb : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogDb() ;
        ~NogDb() ;

        static NAN_METHOD(New) ;
  
        static NAN_METHOD(GetRecord) ;
        static NAN_METHOD(GetSchema) ;
        static NAN_METHOD(GetDbInfo) ;
};

#endif