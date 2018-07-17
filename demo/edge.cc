#include <nan.h>
#include <nogdb/nogdb.h>

#include "record.hpp"
#include "recordDescriptor.hpp"
#include "result.hpp"
#include "resultSet.hpp"
#include "resultSetCursor.hpp"
#include "condition.hpp"
// #include "multiCondition.hpp"
#include "txn.hpp"

#include "edge.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogEdge::constructor;

NogEdge::NogEdge() {};
NogEdge::~NogEdge() {};

NAN_MODULE_INIT(NogEdge::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogEdge::New);
    constructor.Reset(tpl);

    tpl->SetClassName(Nan::New<v8::String>("Edge").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "create", NogEdge::Create);
    SetPrototypeMethod(tpl, "update", NogEdge::Update);
    SetPrototypeMethod(tpl, "updateSrc", NogEdge::UpdateSrc);
    SetPrototypeMethod(tpl, "updateDst", NogEdge::UpdateDst);
    SetPrototypeMethod(tpl, "destroy", NogEdge::Destroy);
    SetPrototypeMethod(tpl, "get", NogEdge::Get);
    SetPrototypeMethod(tpl, "getCursor", NogEdge::GetCursor);
    SetPrototypeMethod(tpl, "getSrc", NogEdge::GetSrc);
    SetPrototypeMethod(tpl, "getDst", NogEdge::GetDst);
    SetPrototypeMethod(tpl, "getSrcDst", NogEdge::GetSrcDst);
    SetPrototypeMethod(tpl, "getIndex", NogEdge::GetIndex);
    SetPrototypeMethod(tpl, "getIndexCursor", NogEdge::GetIndexCursor);

    Set(target, Nan::New<v8::String>("Edge").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogEdge::New) {
    NogEdge* obj = new NogEdge();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(NogEdge::Create) {
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
    // get recordDescriptor for return
    if(!recordDescriptorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe1.ToLocalChecked());
    // get txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // get className
    if(!info[2]->IsString()){
        Nan::ThrowError("arg3: string required");
        return;
    }
    Nan::Utf8String val(info[2]->ToString());
    std::string className (*val);
    // get srcVertexRecordDescriptor
    if(!recordDescriptorType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
    NogRecordDescriptor* srcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // get dstVertexRecordDescriptor
    if(!recordDescriptorType->HasInstance(arg_5)){
        Nan::ThrowError("arg5: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[4]);
    NogRecordDescriptor* dstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe4.ToLocalChecked());
    // get record
    if(!recordType->HasInstance(arg_6)){
        Nan::ThrowError("arg6: Record required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[5]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe5.ToLocalChecked());
    // create edge
    recordDesc->recordDescriptor = nogdb::Edge::create(*txn->txn,className,
                                                        srcVertexRecordDesc->recordDescriptor,
                                                        dstVertexRecordDesc->recordDescriptor,
                                                        r->record);
}

NAN_METHOD(NogEdge::Update) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordType = Nan::New<v8::FunctionTemplate>(NogRecord::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    // get Txn
    if(!txnType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
    // get recordDescriptor
    if(!recordDescriptorType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());
    // get record
    if(!recordType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: Record required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe3.ToLocalChecked());
    // update edge
    nogdb::Edge::update(*txn->txn,recordDesc->recordDescriptor,r->record);
}

NAN_METHOD(NogEdge::UpdateSrc) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    // get txn
    if(!txnType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
    // get recordDescriptor
    if(!recordDescriptorType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());
    // get newSrcVertexReccordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* newSrcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // updateSrc
    nogdb::Edge::updateSrc(*txn->txn,recordDesc->recordDescriptor,newSrcVertexRecordDesc->recordDescriptor);
}

NAN_METHOD(NogEdge::UpdateDst) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    // get txn
    if(!txnType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
    // get reccordDescriptor
    if(!recordDescriptorType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());
    // get newDstVertexReccordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* newDstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // updateDst
    nogdb::Edge::updateDst(*txn->txn,recordDesc->recordDescriptor,newDstVertexRecordDesc->recordDescriptor);
}

NAN_METHOD(NogEdge::Destroy) {
    if(info.Length()!=2){
        Nan::ThrowError("2 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    // get txn
    if(!txnType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
    if(!recordDescriptorType->HasInstance(arg_2)&&!info[1]->IsString()){
        Nan::ThrowError("arg2: RecordDescriptor or string required");
        return;
    }
    // recordDescriptor
    if(recordDescriptorType->HasInstance(arg_2)){
        Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
        NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());
        // destroy edge
        nogdb::Edge::destroy(*txn->txn,recordDesc->recordDescriptor);
    }
    // className
    else if(info[1]->IsString()){
        Nan::Utf8String val(info[1]->ToString());
        std::string className (*val);
        // destroy edge
        nogdb::Edge::destroy(*txn->txn,className);
    }
}

NAN_METHOD(NogEdge::Get) {
    if(info.Length()!=3 && info.Length()!=4){
        Nan::ThrowError("3 or 4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    // get resultSet for return
    if(!resultSetType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSet required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // get className
    if(!info[2]->IsString()){
        Nan::ThrowError("arg3: string required");
        return;
    }
    Nan::Utf8String val(info[2]->ToString());
    std::string className (*val);
    // get edge without condition
    if(info.Length()==3)    resultSet->resultSet = nogdb::Edge::get(*txn->txn,className);
    // get edge with condition or multiCondition
    else if(info.Length()==4){
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe3.ToLocalChecked());
            resultSet->resultSet = nogdb::Edge::get(*txn->txn,className,condition->condition);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* multiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe3.ToLocalChecked());
        //     resultSet->resultSet = nogdb::Edge::get(*txn->txn,className,multiCondition->multiCondition);
        // } 
        // type error
        else{
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
    }
}

NAN_METHOD(NogEdge::GetCursor) {
    if(info.Length()!=3 && info.Length()!=4){
        Nan::ThrowError("3 or 4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();

    // get resultSetCursor for return
    if(!resultSetCursorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSet required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // get className
    if(!info[2]->IsString()){
        Nan::ThrowError("arg3: string required");
        return;
    }
    Nan::Utf8String val(info[2]->ToString());
    std::string className (*val);
    // getCursor Edge without condition
    if(info.Length()==3)    resultSetCursor->resultSetCursor = nogdb::Edge::getCursor(*txn->txn,className);
    // getCursor Edge with condition or multiCondition
    else if(info.Length()==4){
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe3.ToLocalChecked());
            resultSetCursor->resultSetCursor = nogdb::Edge::getCursor(*txn->txn,className,condition->condition);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* multiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe3.ToLocalChecked());
        //     resultSetCursor->resultSetCursor = nogdb::Edge::getCursor(*txn->txn,className,multiCondition->multiCondition);
        // } 
        // type error
        else{
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
    } 
}

NAN_METHOD(NogEdge::GetSrc) {
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
    // get result for return
    if(!resultType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Result required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResult* result = ObjectWrap::Unwrap<NogResult>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // get recordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // getSrc
    result->result = nogdb::Edge::getSrc(*txn->txn,recordDesc->recordDescriptor);
}

NAN_METHOD(NogEdge::GetDst) {
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
    // get result for return
    if(!resultType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Result required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResult* result = ObjectWrap::Unwrap<NogResult>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // get recordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // getDst
    result->result = nogdb::Edge::getDst(*txn->txn,recordDesc->recordDescriptor);
}

NAN_METHOD(NogEdge::GetSrcDst) {
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
    // get resultSet for return
    if(!resultSetType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSet required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // get recordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // getSrcDst
    resultSet->resultSet = nogdb::Edge::getSrcDst(*txn->txn,recordDesc->recordDescriptor);
}

NAN_METHOD(NogEdge::GetIndex) {
    if(info.Length()!=4){
        Nan::ThrowError("4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    // get resultSet for return
    if(!resultSetType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSet required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSet* resultSet = ObjectWrap::Unwrap<NogResultSet>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // get className
    if(!info[2]->IsString()){
        Nan::ThrowError("arg3: string required");
        return;
    }
    Nan::Utf8String val(info[2]->ToString());
    std::string className (*val);
    // getIndex Edge with condition or multiCondition
    // condition
    if(conditionType->HasInstance(arg_4)){
        Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
        NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe3.ToLocalChecked());
        resultSet->resultSet = nogdb::Edge::getIndex(*txn->txn,className,condition->condition);
    } 
    // // multiCondition
    // else if(multiConditionType->HasInstance(arg_4)){
    //     Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
    //     NogMultiCondition* multiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe3.ToLocalChecked());
    //     resultSet->resultSet = nogdb::Edge::getIndex(*txn->txn,className,multiCondition->multiCondition);
    // } 
    // type error
    else{
        Nan::ThrowError("arg4: condition or multiCondition required");
        return;
    }
}

NAN_METHOD(NogEdge::GetIndexCursor) {
    if(info.Length()!=4){
        Nan::ThrowError("4 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();

    // get resultSetCursor for return
    if(!resultSetCursorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSet required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogResultSetCursor* resultSetCursor = ObjectWrap::Unwrap<NogResultSetCursor>(maybe1.ToLocalChecked());
    // get Txn
    if(!txnType->HasInstance(arg_2)){
        Nan::ThrowError("arg2: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe2.ToLocalChecked());
    // get className
    if(!info[2]->IsString()){
        Nan::ThrowError("arg3: string required");
        return;
    }
    Nan::Utf8String val(info[2]->ToString());
    std::string className (*val);
    // getIndexCurcor edge with condition or multiCondition
    // condition
    if(conditionType->HasInstance(arg_4)){
        Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
        NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe3.ToLocalChecked());
        resultSetCursor->resultSetCursor = nogdb::Edge::getIndexCursor(*txn->txn,className,condition->condition);
    } 
    // // multiCondition
    // else if(multiConditionType->HasInstance(arg_4)){
    //     Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
    //     NogMultiCondition* multiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe3.ToLocalChecked());
    //     resultSetCursor->resultSetCursor = nogdb::Edge::getIndexCursor(*txn->txn,className,multiCondition->multiCondition);
    // } 
    // type error
    else{
        Nan::ThrowError("arg4: condition or multiCondition required");
        return;
    }
}