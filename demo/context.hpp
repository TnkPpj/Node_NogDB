#ifndef CONTEXT_H
#define CONTEXT_H

#include <nan.h>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogContext : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::Context ctx;

    private:
        explicit NogContext(std::string dbname) ;
        ~NogContext() ;

        static NAN_METHOD(New) ;
  
        static NAN_METHOD(getMaxVersionId) ;
        static NAN_METHOD(getMaxTxnId) ;
        static NAN_METHOD(getMinActiveTxnId) ;
};

#endif