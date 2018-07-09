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

        nogdb::ResultSetCursor resultSetCursor();

    private:
        explicit NogResultSetCursor() ;
        ~NogResultSetCursor() ;

        static NAN_METHOD(New) ;
        static NAN_METHOD(hasNext);
        static NAN_METHOD(hasPrevious);
        static NAN_METHOD(hasAt);
        static NAN_METHOD(next);
        static NAN_METHOD(previous);
        static NAN_METHOD(empty);
        static NAN_METHOD(size);
        static NAN_METHOD(count);
        static NAN_METHOD(first);
        static NAN_METHOD(last);
        static NAN_METHOD(to);
};

#endif