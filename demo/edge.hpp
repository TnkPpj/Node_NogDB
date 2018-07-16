#ifndef EDGE_H
#define EDGE_H

#include <nan.h>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogEdge : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogEdge() ;
        ~NogEdge() ;

        static NAN_METHOD(New) ;
  
        static NAN_METHOD(Create) ;
        static NAN_METHOD(Update) ;
        static NAN_METHOD(UpdateSrc) ;
        static NAN_METHOD(UpdateDst) ;
        static NAN_METHOD(Destroy) ;
        static NAN_METHOD(Get) ;
        static NAN_METHOD(GetCursor) ;
        static NAN_METHOD(GetSrc) ;
        static NAN_METHOD(GetDst) ;
        static NAN_METHOD(GetSrcDst) ;
        static NAN_METHOD(GetIndex) ;
        static NAN_METHOD(GetIndexCursor) ;
};

#endif