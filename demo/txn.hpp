#ifndef TXN_H
#define TXN_H

#include <nan.h>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogTxn : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::Txn txn;

    private:
        explicit NogTxn(nogdb::Context ctx, const nogdb::Txn::Mode& mode) ;
        ~NogTxn() ;

        static NAN_METHOD(New) ;

        static NAN_METHOD(commit) ;
        static NAN_METHOD(rollback) ;
        static NAN_METHOD(getTxnId) ;
        static NAN_METHOD(getVersionId) ;
        static NAN_METHOD(getTxnMode) ;
};

#endif