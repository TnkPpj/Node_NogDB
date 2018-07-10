#include <nan.h>
#include <nogdb/nogdb.h>

#include "record.hpp"
#include "recordDescriptor.hpp"
#include "result.hpp"
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
        Nan::ThrowError("arg2: Txn required");
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

    resultSet->resultSet = nogdb::Edge::get(txn->txn,className);
    // ResultSet Edge::get(const Txn &txn, const std::string &className)
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
        Nan::ThrowError("arg1: ResultSetCursor required");
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

    resultSetCursor->resultSetCursor =  nogdb::Edge::getCursor(txn->txn,className);
    // ResultSetCursor Edge::getCursor(Txn &txn, const std::string &className)
}

void GetSrc(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultType = Nan::New<v8::FunctionTemplate>(NogResult::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();

    if(!resultType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Result required");
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

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResult* result = ObjectWrap::Unwrap<NogResult>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    result->result = nogdb::Edge::getSrc(txn->txn,recordDesc->recordDescriptor);
    // Result Edge::getSrc(const Txn &txn, const RecordDescriptor &recordDescriptor)
}

void GetDst(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultType = Nan::New<v8::FunctionTemplate>(NogResult::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();

    if(!resultType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Result required");
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

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResult* result = ObjectWrap::Unwrap<NogResult>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    result->result = nogdb::Edge::getDst(txn->txn,recordDesc->recordDescriptor);
    // Result Edge::getDst(const Txn &txn, const RecordDescriptor &recordDescriptor)
}

void GetSrcDst(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();

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

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    resultSet->resultSet = nogdb::Edge::getSrcDst(txn->txn,recordDesc->recordDescriptor);
    // ResultSet Edge::getSrcDst(const Txn &txn, const RecordDescriptor &recordDescriptor)
}

void Create(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=6){
        Nan::ThrowError("6 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> recordType = Nan::New<v8::FunctionTemplate>(NogRecord::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
    v8::Handle<v8::Object> arg_6 = info[5]->ToObject();

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
    if(!recordDescriptorType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: RecordDescriptor required");
        return;
    }
    if(!recordDescriptorType->HasInstance(arg_5)){
        Nan::ThrowError("arg5: RecordDescriptor required");
        return;
    }
    if(!recordType->HasInstance(arg_6)){
        Nan::ThrowError("arg6: Record required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());

    Nan::Utf8String val(info[2]->ToString());
    std::string className (*val);

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
    NogRecordDescriptor* srcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[4]);
    NogRecordDescriptor* dstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe4.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[5]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe5.ToLocalChecked());

    recordDesc->recordDescriptor = nogdb::Edge::create(txn->txn,className,
                                                        srcVertexRecordDesc->recordDescriptor,
                                                        dstVertexRecordDesc->recordDescriptor,
                                                        r->record);
    // const RecordDescriptor Edge::create(Txn &txn,
    //                                     const std::string &className,
    //                                     const RecordDescriptor &srcVertexRecordDescriptor,
    //                                     const RecordDescriptor &dstVertexRecordDescriptor,
    //                                     const Record &record)
}

void Update(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=6){
        Nan::ThrowError("6 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordType = Nan::New<v8::FunctionTemplate>(NogRecord::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();

    if(!recordDescriptorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: RecordDescriptor required");
        return;
    }
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    if(!recordType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: Record required");
        return;
    }

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe3.ToLocalChecked());

    nogdb::Edge::update(txn->txn,recordDesc->recordDescriptor,r->record);
    // void Edge::update(Txn &txn, const RecordDescriptor &recordDescriptor, const Record &record)
}

void UpdateSrc(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=6){
        Nan::ThrowError("6 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();

    if(!recordDescriptorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: RecordDescriptor required");
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

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* newSrcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    nogdb::Edge::updateSrc(txn->txn,recordDesc->recordDescriptor,newSrcVertexRecordDesc->recordDescriptor);
    // void Edge::updateSrc(Txn &txn,
    //                      const RecordDescriptor &recordDescriptor,
    //                      const RecordDescriptor &newSrcVertexRecordDescriptor)
}

void UpdateDst(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if(info.Length()!=6){
        Nan::ThrowError("6 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();

    if(!recordDescriptorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: RecordDescriptor required");
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
    
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());

    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* newDstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());

    nogdb::Edge::updateDst(txn->txn,recordDesc->recordDescriptor,newDstVertexRecordDesc->recordDescriptor);
    // void Edge::updateSrc(Txn &txn,
    //                      const RecordDescriptor &recordDescriptor,
    //                      const RecordDescriptor &newDstVertexRecordDescriptor)
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

        nogdb::Edge::destroy(txn->txn,recordDesc->recordDescriptor);
        // void Edge::destroy(Txn &txn, const RecordDescriptor &recordDescriptor)
    }else if(info[1]->IsString()){

        Nan::Utf8String val(info[1]->ToString());
        std::string className (*val);

        nogdb::Edge::destroy(txn->txn,className);
        // void Edge::destroy(Txn &txn, const std::string &className)
    }
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("get").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Get)->GetFunction());
  exports->Set(Nan::New("getCursor").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetCursor)->GetFunction()); 
  exports->Set(Nan::New("getSrc").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetSrc)->GetFunction());
  exports->Set(Nan::New("getDst").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetDst)->GetFunction());
  exports->Set(Nan::New("getSrcDst").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetSrcDst)->GetFunction());
  exports->Set(Nan::New("create").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Create)->GetFunction());
  exports->Set(Nan::New("update").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Update)->GetFunction());
  exports->Set(Nan::New("updateSrc").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(UpdateSrc)->GetFunction());
  exports->Set(Nan::New("updateDst").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(UpdateDst)->GetFunction());
  exports->Set(Nan::New("destroy").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Destroy)->GetFunction());
}

NODE_MODULE(addon, Init)
