#ifndef NOGDB_H
#define NOGDB_H

#include <cmath>
#include <nan.h>
#include <string>

#include <nogdb/nogdb.h>

using namespace Nan;

static Persistent<v8::FunctionTemplate> constructor;

class NogdbTest : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogdbTest() ;
  ~NogdbTest() ;

  static NAN_METHOD(New) ;
  static NAN_METHOD(TXNWrite) ;
  static NAN_METHOD(TXNRead) ;
};

class NogContext : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

    nogdb::Context ctx;

 private:
  explicit NogContext(std::string dbname) ;
  ~NogContext() ;

  static NAN_METHOD(New) ;
  
  static NAN_METHOD(getMaxVersionId) ;
  static NAN_METHOD(getMaxTxnId) ;
  static NAN_METHOD(getMinActiveTxnId) ;
};

class NogTxn : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

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

class NogDBInfo : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;
    nogdb::DBInfo& dbInfo;

 private:
  explicit NogDBInfo() ;
  ~NogDBInfo() ;
  static NAN_METHOD(New) ;

  static NAN_GETTER(getAtt) ;
};

class NogClassDescriptor : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;
    nogdb::ClassDescriptor& classDesc;

 private:
  explicit NogClassDescriptor() ;
  ~NogClassDescriptor() ;
  static NAN_METHOD(New) ;

  static NAN_GETTER(getAtt) ;
};

// class NogdbClass : public Nan::ObjectWrap {
//  public:
//   static NAN_MODULE_INIT(Init) ;

//  private:
//   explicit NogdbClass() ;
//   ~NogdbClass() ;

//   static NAN_METHOD(New) ;
// };

#endif
