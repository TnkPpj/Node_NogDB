#ifndef RECORD_ID_H
#define RECORD_ID_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogRecordId : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::RecordId recordId;

    private:
        explicit NogRecordId() ;
        ~NogRecordId() ;

        static NAN_METHOD(New) ;
};

#endif