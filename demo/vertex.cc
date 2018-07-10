#include <nan.h>
#include <nogdb/nogdb.h>

#include "classFilter.hpp"
#include "record.hpp"
#include "recordDescriptor.hpp"
#include "resultSet.hpp"
#include "resultSetCursor.hpp"
#include "txn.hpp"

void Get(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();

    if(!resultSetType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSet required");
        return;
    }
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg1: Txn required");
        return;
    }
    if(!info[2]->IsString()){
          Nan::ThrowError("arg3: string required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::Utf8String val(info[2]->ToString());
    std::string className (*val);

    resultSet->resultSet = nogdb::Vertex::get(txn->txn,className);
    // ResultSet Vertex::get(const Txn &txn, const std::string &className)
}

void GetCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();

    if(!resultSetCursorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSet required");
        return;
    }
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    if(!info[2]->IsString()){
        Nan::ThrowError("arg3: string required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::Utf8String val(info[2]->ToString());
    std::string className (*val);

    resultSetCursor->resultSetCursor = nogdb::Vertex::getCursor(txn->txn,className);
    // ResultSetCursor Vertex::getCursor(Txn &txn, const std::string &className) 
}

void GetInEdge(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=4){
        Nan::ThrowError("4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();

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
    if(!classFilterType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: ClassFilter required");
        return;
    }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

  resultSet->resultSet = nogdb::Vertex::getInEdge(txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
  // ResultSet Vertex::getInEdge(const Txn &txn, const RecordDescriptor &recordDescriptor, const ClassFilter &classFilter)
}

void GetInEdgeCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=4){
        Nan::ThrowError("4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();

    if(!resultSetCursorType->HasInstance(arg_1)){
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
    if(!classFilterType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: ClassFilter required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
    NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

    resultSetCursor->resultSetCursor = nogdb::Vertex::getInEdgeCursor(txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    // ResultSetCursor Vertex::getInEdgeCursor(Txn &txn, const RecordDescriptor &recordDescriptor, const ClassFilter &classFilter)
}

void GetOutEdge(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=4){
        Nan::ThrowError("4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();

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
    if(!classFilterType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: ClassFilter required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
    NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

    resultSet->resultSet = nogdb::Vertex::getOutEdge(txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    // ResultSet Vertex::getOutEdge(const Txn &txn, const RecordDescriptor &recordDescriptor, const ClassFilter &classFilter)
}

void GetOutEdgeCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=4){
        Nan::ThrowError("4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();

    if(!resultSetCursorType->HasInstance(arg_1)){
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
    if(!classFilterType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: ClassFilter required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
    NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

    resultSetCursor->resultSetCursor = nogdb::Vertex::getOutEdgeCursor(txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    // ResultSetCursor Vertex::getOutEdgeCursor(Txn &txn, const RecordDescriptor &recordDescriptor, const ClassFilter &classFilter)
}

void GetAllEdge(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=4){
        Nan::ThrowError("4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();

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
    if(!classFilterType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: ClassFilter required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
    NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());

    resultSet->resultSet = nogdb::Vertex::getAllEdge(txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    // ResultSet Vertex::getAllEdge(const Txn &txn, const RecordDescriptor &recordDescriptor, const ClassFilter &classFilter)
}

void GetAllEdgeCursor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()!=4){
      Nan::ThrowError("4 arguments required");
      return;
  }
  
  v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
  v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
  v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
  v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);

  v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
  v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
  v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
  v8::Handle<v8::Object> arg_4 = info[3]->ToObject();

  if(!resultSetCursorType->HasInstance(arg_1)){
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
  if(!classFilterType->HasInstance(arg_4)){
      Nan::ThrowError("arg4: ClassFilter required");
      return;
  }

  Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
  NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
  NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

  Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
  NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
  
  resultSetCursor->resultSetCursor = nogdb::Vertex::getAllEdgeCursor(txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    // ResultSetCursor Vertex::getAllEdgeCursor(Txn &txn, const RecordDescriptor &recordDescriptor, const ClassFilter &classFilter)
}

void Create(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=4){
        Nan::ThrowError("4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordType = Nan::New<v8::FunctionTemplate>(NogRecord::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();

    if(!recordDescriptorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: RecordDescriptor required");
        return;
    }
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    if(!info[2]->IsString()){
        Nan::ThrowError("arg3: string required");
        return;
    }
    if(!recordType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: record required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::Utf8String val(info[2]->ToString());
    std::string className (*val);

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe3.ToLocalChecked());

    recordDesc->recordDescriptor = nogdb::Vertex::create(txn->txn,className,r->record);
    // const RecordDescriptor Vertex::create(Txn &txn, const std::string &className, const Record &record)
}

void Update(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> recordType = Nan::New<v8::FunctionTemplate>(NogRecord::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();

    if(!txnType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Txn required");
        return;
    }
    if(!recordDescriptorType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: RecordDescriptor required");
        return;
    }
    if(!recordType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: record required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe3.ToLocalChecked());

    nogdb::Vertex::update(txn->txn,recordDesc->recordDescriptor,r->record);
    // void Vertex::update(Txn &txn, const RecordDescriptor &recordDescriptor, const Record &record)
}

void Destroy(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=2){
        Nan::ThrowError("2 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();

    if(!txnType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Txn required");
        return;
    }
    if(!recordDescriptorType->HasInstance(arg_2)&&!info[1]->IsString()){
        Nan::ThrowError("arg2: RecordDescriptor or string required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

    if(recordDescriptorType->HasInstance(arg_2)){
        Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
        NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());

        nogdb::Vertex::destroy(txn->txn,recordDesc->recordDescriptor);
        // void Vertex::destroy(Txn &txn, const RecordDescriptor &recordDescriptor)
    }else if(info[1]->IsString()){

        Nan::Utf8String val(info[1]->ToString());
        std::string className (*val);

        nogdb::Vertex::destroy(txn->txn,className);
        // void Vertex::destroy(Txn &txn, const std::string &className)
    }
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("get").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Get)->GetFunction());
  exports->Set(Nan::New("getCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetCursor)->GetFunction()); 
  exports->Set(Nan::New("getInEdge").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetInEdge)->GetFunction());
  exports->Set(Nan::New("getInEdgeCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetInEdgeCursor)->GetFunction());
  exports->Set(Nan::New("getOutEdge").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetOutEdge)->GetFunction());
  exports->Set(Nan::New("getOutEdgeCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetOutEdgeCursor)->GetFunction());
  exports->Set(Nan::New("getAllEdge").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetAllEdge)->GetFunction());
  exports->Set(Nan::New("getAllEdgeCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetAllEdgeCursor)->GetFunction());
  exports->Set(Nan::New("create").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Create)->GetFunction());
  exports->Set(Nan::New("update").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Update)->GetFunction());
  exports->Set(Nan::New("destroy").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Destroy)->GetFunction());
}

NODE_MODULE(vertex, Init)
