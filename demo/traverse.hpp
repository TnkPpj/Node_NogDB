#ifndef TRAVERSE_H
#define TRAVERSE_H

#include <nan.h>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogTraverse : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

    private:
        explicit NogTraverse() ;
        ~NogTraverse() ;

        static NAN_METHOD(New) ;
  
        static NAN_METHOD(InEdgeBfs) ;
        static NAN_METHOD(OutEdgeBfs) ;
        static NAN_METHOD(AllEdgeBfs) ;
        static NAN_METHOD(InEdgeDfs) ;
        static NAN_METHOD(OutEdgeDfs) ;
        static NAN_METHOD(AllEdgeDfs) ;
        static NAN_METHOD(ShortestPath) ;
        static NAN_METHOD(InEdgeBfsCursor) ;
        static NAN_METHOD(OutEdgeBfsCursor) ;
        static NAN_METHOD(AllEdgeBfsCursor) ;
        static NAN_METHOD(InEdgeDfsCursor) ;
        static NAN_METHOD(OutEdgeDfsCursor) ;
        static NAN_METHOD(AllEdgeDfsCursor) ;
        static NAN_METHOD(ShortestPathCursor) ;
};

#endif