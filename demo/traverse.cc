#include <nan.h>
#include <nogdb/nogdb.h>

#include "classFilter.hpp"
#include "pathFilter.hpp"
#include "recordDescriptor.hpp"
#include "resultSet.hpp"
#include "resultSetCursor.hpp"
#include "txn.hpp"

void InEdgeBfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::inEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSet Traverse::inEdgeBfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::inEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSet Traverse::inEdgeBfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void InEdgeBfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::inEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSetCursor Traverse::inEdgeBfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::inEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSetCursor Traverse::inEdgeBfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void OutEdgeBfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::outEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSet Traverse::outEdgeBfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::outEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSet Traverse::outEdgeBfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void OutEdgeBfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::outEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSetCursor Traverse::outEdgeBfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::outEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSetCursor Traverse::outEdgeBfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void AllEdgeBfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::allEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSet Traverse::allEdgeBfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::allEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSet Traverse::allEdgeBfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void AllEdgeBfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::allEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSetCursor Traverse::allEdgeBfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::allEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSetCursor Traverse::allEdgeBfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void InEdgeDfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::inEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSet Traverse::inEdgeDfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::inEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSet Traverse::inEdgeDfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void InEdgeDfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::inEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSetCursor Traverse::inEdgeDfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::inEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSetCursor Traverse::inEdgeDfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void OutEdgeDfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::outEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSet Traverse::outEdgeDfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::outEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSet Traverse::outEdgeDfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void OutEdgeDfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::outEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSetCursor Traverse::outEdgeDfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::outEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSetCursor Traverse::outEdgeDfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void AllEdgeDfs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::allEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSet Traverse::allEdgeDfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::allEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSet Traverse::allEdgeDfs(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void AllEdgeDfsCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=7&&info.Length()!=6){
        Nan::ThrowError("7 or 6 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();
  v8::Handle<v8::Object> arg_7 = info[6]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
  }
  if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
  }
  
  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  int minDepth = info[3]->IntegerValue();

  int maxDepth = info[4]->IntegerValue();

  if(info.Length()==6){
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::allEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,classFilter->classFilter);
      // ResultSetCursor Traverse::allEdgeDfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const ClassFilter &classFilter)
  } else if (info.Length()==7){
      if(!pathFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_7)){
          Nan::ThrowError("arg7: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::allEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                        minDepth,maxDepth,pathFilter->pathFilter,
                                                        classFilter->classFilter);
      // ResultSetCursor Traverse::allEdgeDfsCursor(const Txn &txn,
      //                                 const RecordDescriptor &recordDescriptor,
      //                                 unsigned int minDepth,
      //                                 unsigned int maxDepth,
      //                                 const PathFilter &pathFilter,
      //                                 const ClassFilter &classFilter)
  }
}

void ShortestPath(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=6&&info.Length()!=5){
        Nan::ThrowError("6 or 5 arguments required");
        return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
  v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();

  if(!resultSetType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSet required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_4)){
    Nan::ThrowError("arg4: RecordDescriptor required");
    return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* srcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
  NogRecordDescriptor* dstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe4.ToLocalChecked());

  if(info.Length()==5){
      if(!classFilterType->HasInstance(arg_5)){
          Nan::ThrowError("arg5: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::shortestPath(txn->txn,
                                                        srcVertexRecordDesc->recordDescriptor,
                                                        dstVertexRecordDesc->recordDescriptor,
                                                        classFilter->classFilter);
      // ResultSet Traverse::shortestPath(Txn &txn,
      //                                            const RecordDescriptor &srcVertexRecordDescriptor,
      //                                            const RecordDescriptor &dstVertexRecordDescriptor,
      //                                            const ClassFilter &classFilter)
  } else if (info.Length()==6){
      if(!pathFilterType->HasInstance(arg_5)){
          Nan::ThrowError("arg5: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe5.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe6 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe6.ToLocalChecked());

      resultSet->resultSet = nogdb::Traverse::shortestPath(txn->txn,
                                                        srcVertexRecordDesc->recordDescriptor,
                                                        dstVertexRecordDesc->recordDescriptor,
                                                        pathFilter->pathFilter,classFilter->classFilter);
      // ResultSet Traverse::shortestPath(Txn &txn,
      //                                            const RecordDescriptor &srcVertexRecordDescriptor,
      //                                            const RecordDescriptor &dstVertexRecordDescriptor,
      //                                            const PathFilter &pathFilter,
      //                                            const ClassFilter &classFilter)
  }
}

void ShortestPathCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=6&&info.Length()!=5){
        Nan::ThrowError("6 or 5 arguments required");
        return;
  }
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> pathFilterType = Nan::New<v8::FunctionTemplate>(NogPathFilter::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
  v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
  v8::Handle<v8::Object> arg_6 = info[5]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
    Nan::ThrowError("arg1: ResultSetCursor required");
    return;
  }
  if(!txnType->HasInstance(arg_2)){
    Nan::ThrowError("arg2: Txn required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_3)){
    Nan::ThrowError("arg3: RecordDescriptor required");
    return;
  }
  if(!recordDescriptorType->HasInstance(arg_4)){
    Nan::ThrowError("arg4: RecordDescriptor required");
    return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* srcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
  NogRecordDescriptor* dstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe4.ToLocalChecked());

  if(info.Length()==5){
      if(!classFilterType->HasInstance(arg_5)){
          Nan::ThrowError("arg5: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::shortestPathCursor(txn->txn,
                                                        srcVertexRecordDesc->recordDescriptor,
                                                        dstVertexRecordDesc->recordDescriptor,
                                                        classFilter->classFilter);
      // ResultSetCursor Traverse::shortestPathCursor(Txn &txn,
      //                                            const RecordDescriptor &srcVertexRecordDescriptor,
      //                                            const RecordDescriptor &dstVertexRecordDescriptor,
      //                                            const ClassFilter &classFilter)
  } else if (info.Length()==6){
      if(!pathFilterType->HasInstance(arg_5)){
          Nan::ThrowError("arg5: PathFilter required");
          return;
      }
      if(!classFilterType->HasInstance(arg_6)){
          Nan::ThrowError("arg6: classFilter required");
          return;
      }
      Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
      NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe5.ToLocalChecked());

      Nan::MaybeLocal<v8::Object> maybe6 = Nan::To<v8::Object>(info[5]);
      NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe6.ToLocalChecked());

      resultSetCursor->resultSetCursor = nogdb::Traverse::shortestPathCursor(txn->txn,
                                                        srcVertexRecordDesc->recordDescriptor,
                                                        dstVertexRecordDesc->recordDescriptor,
                                                        pathFilter->pathFilter,classFilter->classFilter);
      // ResultSetCursor Traverse::shortestPathCursor(Txn &txn,
      //                                            const RecordDescriptor &srcVertexRecordDescriptor,
      //                                            const RecordDescriptor &dstVertexRecordDescriptor,
      //                                            const PathFilter &pathFilter,
      //                                            const ClassFilter &classFilter)
  }
}


void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("inEdgeBfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(InEdgeBfs)->GetFunction());
  exports->Set(Nan::New("inEdgeBfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(InEdgeBfsCursor)->GetFunction()); 
  exports->Set(Nan::New("outEdgeBfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(OutEdgeBfs)->GetFunction());
  exports->Set(Nan::New("outEdgeBfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(OutEdgeBfsCursor)->GetFunction());
  exports->Set(Nan::New("allEdgeBfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(AllEdgeBfs)->GetFunction());
  exports->Set(Nan::New("allEdgeBfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(AllEdgeBfsCursor)->GetFunction());
  exports->Set(Nan::New("inEdgeDfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(InEdgeDfs)->GetFunction());
  exports->Set(Nan::New("inEdgeDfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(InEdgeDfsCursor)->GetFunction()); 
  exports->Set(Nan::New("outEdgeDfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(OutEdgeDfs)->GetFunction());
  exports->Set(Nan::New("outEdgeDfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(OutEdgeDfsCursor)->GetFunction());
  exports->Set(Nan::New("allEdgeDfs").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(AllEdgeDfs)->GetFunction());
  exports->Set(Nan::New("allEdgeDfsCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(AllEdgeDfsCursor)->GetFunction());
  exports->Set(Nan::New("shortestPath").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(ShortestPath)->GetFunction());
  exports->Set(Nan::New("shortestPathCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(ShortestPathCursor)->GetFunction());
}

NODE_MODULE(traverse, Init)
