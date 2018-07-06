#ifndef DB_INFO_H
#define DB_INFO_H

#include <nan.h>
#include <string>
#include <nogdb/nogdb.h>

using namespace Nan;

class NogDBInfo : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) ;
        static Persistent<v8::FunctionTemplate> constructor;

        nogdb::DBInfo& dbInfo;

    private:
        explicit NogDBInfo() ;
        ~NogDBInfo() ;
  
        static NAN_METHOD(New) ;

        static NAN_GETTER(getAtt) ;
};
#endif