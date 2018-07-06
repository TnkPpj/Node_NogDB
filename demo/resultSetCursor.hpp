#ifndef RESULT_SET_CURSOR_H
#define RESULT_SET_CURSOR_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogResultSetCursor : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::ResultSetCursor resultSetCursor;

    private:
        explicit NogResultSetCursor() ;
        ~NogResultSetCursor() ;

        static NAN_METHOD(New) ;
};

#endif