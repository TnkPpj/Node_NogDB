#ifndef VERTEX_H
#define VERTEX_H

#include <nan.h>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogVertex : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogVertex() ;
        ~NogVertex() ;

        static NAN_METHOD(New) ;
  
        static NAN_METHOD(Create) ;
        static NAN_METHOD(Update) ;
        static NAN_METHOD(Destroy) ;
        static NAN_METHOD(Get) ;
        static NAN_METHOD(GetCursor) ;
        static NAN_METHOD(GetInEdge) ;
        static NAN_METHOD(GetOutEdge) ;
        static NAN_METHOD(GetAllEdge) ;
        static NAN_METHOD(GetInEdgeCursor) ;
        static NAN_METHOD(GetOutEdgeCursor) ;
        static NAN_METHOD(GetAllEdgeCursor) ;
        static NAN_METHOD(GetIndex) ;
        static NAN_METHOD(GetIndexCursor) ;
};

#endif