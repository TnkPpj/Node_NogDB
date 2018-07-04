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

class NogBytes : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogBytes() ;
  ~NogBytes() ;

  static NAN_METHOD(New) ;
};

class NogRecordId : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogRecordId() ;
  ~NogRecordId() ;

  static NAN_METHOD(New) ;
};

class NogRecord : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogRecord() ;
  ~NogRecord() ;

  static NAN_METHOD(New) ;
};

class NogResult : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogResult() ;
  ~NogResult() ;

  static NAN_METHOD(New) ;
};

class NogResultSetCursor : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogResultSetCursor() ;
  ~NogResultSetCursor() ;

  static NAN_METHOD(New) ;
};

class NogResultSet : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogResultSet() ;
  ~NogResultSet() ;

  static NAN_METHOD(New) ;
};

class NogCondition : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogCondition() ;
  ~NogCondition() ;

  static NAN_METHOD(New) ;
};

class NogMultiCondition : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogMultiCondition() ;
  ~NogMultiCondition() ;

  static NAN_METHOD(New) ;
};

class NogPathFilter : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogPathFilter() ;
  ~NogPathFilter() ;

  static NAN_METHOD(New) ;
};

class NogClassFilter : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogClassFilter() ;
  ~NogClassFilter() ;

  static NAN_METHOD(New) ;
};

class NogPropertyDescriptor : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogPropertyDescriptor() ;
  ~NogPropertyDescriptor() ;

  static NAN_METHOD(New) ;
};

class NogRecordDescriptor : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) ;

 private:
  explicit NogRecordDescriptor() ;
  ~NogRecordDescriptor() ;

  static NAN_METHOD(New) ;
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
