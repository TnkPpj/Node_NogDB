#include <nan.h>
#include <nogdb/nogdb.h>

#include "classFilter.hpp"
#include "record.hpp"
#include "recordDescriptor.hpp"
#include "resultSet.hpp"
#include "resultSetCursor.hpp"
#include "condition.hpp"
// #include "multiCondition"
#include "txn.hpp"

#include "vertex.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogVertex::constructor;

NogVertex::NogVertex() {};
NogVertex::~NogVertex() {};

NAN_MODULE_INIT(NogVertex::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogVertex::New);
    constructor.Reset(tpl);

    tpl->SetClassName(Nan::New<v8::String>("Vertex").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "create", NogVertex::Create);
    SetPrototypeMethod(tpl, "update", NogVertex::Update);
    SetPrototypeMethod(tpl, "destroy", NogVertex::Destroy);
    SetPrototypeMethod(tpl, "get", NogVertex::Get);
    SetPrototypeMethod(tpl, "getCursor", NogVertex::GetCursor);
    SetPrototypeMethod(tpl, "getInEdge", NogVertex::GetInEdge);
    SetPrototypeMethod(tpl, "getOutEdge", NogVertex::GetOutEdge);
    SetPrototypeMethod(tpl, "getAllEdge", NogVertex::GetAllEdge);
    SetPrototypeMethod(tpl, "getInEdgeCursor", NogVertex::GetInEdgeCursor);
    SetPrototypeMethod(tpl, "getOutEdgeCursor", NogVertex::GetOutEdgeCursor);
    SetPrototypeMethod(tpl, "getAllEdgeCursor", NogVertex::GetAllEdgeCursor);
    SetPrototypeMethod(tpl, "getIndex", NogVertex::GetIndex);
    SetPrototypeMethod(tpl, "getIndexCursor", NogVertex::GetIndexCursor);

    Set(target, Nan::New<v8::String>("Vertex").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogVertex::New) {
    NogVertex* obj = new NogVertex();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(NogVertex::Create) {
    if(info.Length()!=3){
        Nan::ThrowError("3 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordType = Nan::New<v8::FunctionTemplate>(NogRecord::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    // get recordDescriptor for return
    if(!recordDescriptorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: recordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogRecordDescriptor* recordDescriptor = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe1.ToLocalChecked());
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
    // get Record
    if(!recordType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: record required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe3.ToLocalChecked());
    // create vertex
    recordDescriptor->recordDescriptor = nogdb::Vertex::create(*txn->txn,className,r->record);
}

NAN_METHOD(NogVertex::Update) {
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
        Nan::ThrowError("arg3: record required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecord* r = ObjectWrap::Unwrap<NogRecord>(maybe3.ToLocalChecked());
    // update vertex
    nogdb::Vertex::update(*txn->txn,recordDesc->recordDescriptor,r->record);
}

NAN_METHOD(NogVertex::Destroy) {
    if(info.Length()!=2){
        Nan::ThrowError("2 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    // get Txn
    if(!txnType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: Txn required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    NogTxn* txn = ObjectWrap::Unwrap<NogTxn>(maybe1.ToLocalChecked());
    // get recordDescriptor or className
    if(!recordDescriptorType->HasInstance(arg_2)&&!info[1]->IsString()){
        Nan::ThrowError("arg2: RecordDescriptor or string required");
        return;
    }
    if(recordDescriptorType->HasInstance(arg_2)){
        Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
        NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe2.ToLocalChecked());
        // destroy vertex by recordDescriptor
        nogdb::Vertex::destroy(*txn->txn,recordDesc->recordDescriptor);
    }else if(info[1]->IsString()){
        Nan::Utf8String val(info[1]->ToString());
        std::string className (*val);
        // destroy vertex by className
        nogdb::Vertex::destroy(*txn->txn,className);        
    }
}

NAN_METHOD(NogVertex::Get) {
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
    // get vertex without condition
    if(info.Length()==3)    resultSet->resultSet = nogdb::Vertex::get(*txn->txn,className);
    // get vertex with condition or multiCondition
    else if(info.Length()==4){
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe3.ToLocalChecked());
            resultSet->resultSet = nogdb::Vertex::get(*txn->txn,className,condition->condition);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe3.ToLocalChecked());
        //     resultSet->resultSet = nogdb::Vertex::get(*txn->txn,className,multiCondition->multiCondition);
        // } 
        // type error
        else{
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
    }
}

NAN_METHOD(NogVertex::GetCursor) {
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
    // getCursor vertex without condition
    if(info.Length()==3)    resultSetCursor->resultSetCursor = nogdb::Vertex::getCursor(*txn->txn,className);
    // getCursor vertex with condition or multiCondition
    else if(info.Length()==4){
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe3.ToLocalChecked());
            resultSetCursor->resultSetCursor = nogdb::Vertex::getCursor(*txn->txn,className,condition->condition);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe3.ToLocalChecked());
        //     resultSetCursor->resultSetCursor = nogdb::Vertex::getCursor(*txn->txn,className,multiCondition->multiCondition);
        // } 
        // type error
        else{
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
    } 
}

NAN_METHOD(NogVertex::GetInEdge) {
    if(info.Length()!=4 && info.Length()!=5){
        Nan::ThrowError("4 or 5 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
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
    // getInEdge vertex without condition
    if(info.Length()==4){
        if(!classFilterType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // getInEdge
        resultSet->resultSet = nogdb::Vertex::getInEdge(*txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    }
    // getInEdge vertex with condition or multiCondition
    else if(info.Length()==5){
        // check condition / multiCondition type
        if(!conditionType->HasInstance(arg_4) ){//&& !MultiConditionType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
        // get classFilter
        if(!classFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe4.ToLocalChecked());
            // getInEdge
            resultSet->resultSet = nogdb::Vertex::getInEdge(*txn->txn,recordDesc->recordDescriptor,condition->condition,classFilter->classFilter);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe4.ToLocalChecked());
        //     // getInEdge
        //     resultSet->resultSet = nogdb::Vertex::getInEdge(*txn->txn,recordDesc->recordDescriptor,multiCondition->multiCondition,classFilter->classFilter);
        // } 
    }
}

NAN_METHOD(NogVertex::GetOutEdge) {
    if(info.Length()!=4 && info.Length()!=5){
        Nan::ThrowError("4 or 5 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
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
    // getOutEdge vertex without condition
    if(info.Length()==4){
        if(!classFilterType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // getOutEdge
        resultSet->resultSet = nogdb::Vertex::getOutEdge(*txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    }
    // getOutEdge vertex with condition or multiCondition
    else if(info.Length()==5){
        // check condition / multiCondition type
        if(!conditionType->HasInstance(arg_4) ){//&& !MultiConditionType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
        // get classFilter
        if(!classFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe4.ToLocalChecked());
            // getOutEdge
            resultSet->resultSet = nogdb::Vertex::getOutEdge(*txn->txn,recordDesc->recordDescriptor,condition->condition,classFilter->classFilter);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe4.ToLocalChecked());
        //     // getOutEdge
        //     resultSet->resultSet = nogdb::Vertex::getOutEdge(*txn->txn,recordDesc->recordDescriptor,multiCondition->multiCondition,classFilter->classFilter);
        // } 
    }
}

NAN_METHOD(NogVertex::GetAllEdge) {
    if(info.Length()!=4 && info.Length()!=5){
        Nan::ThrowError("4 or 5 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetType = Nan::New<v8::FunctionTemplate>(NogResultSet::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
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
    // getAllEdge vertex without condition
    if(info.Length()==4){
        if(!classFilterType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // getAllEdge
        resultSet->resultSet = nogdb::Vertex::getAllEdge(*txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    }
    // getAllEdge vertex with condition or multiCondition
    else if(info.Length()==5){
        // check condition / multiCondition type
        if(!conditionType->HasInstance(arg_4) ){//&& !MultiConditionType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
        // get classFilter
        if(!classFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe4.ToLocalChecked());
            // getAllEdge
            resultSet->resultSet = nogdb::Vertex::getAllEdge(*txn->txn,recordDesc->recordDescriptor,condition->condition,classFilter->classFilter);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe4.ToLocalChecked());
        //     // getAllEdge
        //     resultSet->resultSet = nogdb::Vertex::getAllEdge(*txn->txn,recordDesc->recordDescriptor,multiCondition->multiCondition,classFilter->classFilter);
        // }
    }
}

NAN_METHOD(NogVertex::GetInEdgeCursor) {
    if(info.Length()!=4 && info.Length()!=5){
        Nan::ThrowError("4 or 5 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
    // get resultSetCursor
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
    // get recordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // getInEdgeCursor vertex without condition
    if(info.Length()==4){
        if(!classFilterType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // getInEdgeCursor
        resultSetCursor->resultSetCursor = nogdb::Vertex::getInEdgeCursor(*txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    }
    // getInEdgeCursor vertex with condition or multiCondition
    else if(info.Length()==5){
        // check condition / multiCondition type
        if(!conditionType->HasInstance(arg_4) ){//&& !MultiConditionType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
        // get classFilter
        if(!classFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe4.ToLocalChecked());
            // getInEdgeCursor
            resultSetCursor->resultSetCursor = nogdb::Vertex::getInEdgeCursor(*txn->txn,recordDesc->recordDescriptor,condition->condition,classFilter->classFilter);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe4.ToLocalChecked());
        //     // getInEdgeCursor
        //     resultSetCursor->resultSetCursor = nogdb::Vertex::getInEdgeCursor(*txn->txn,recordDesc->recordDescriptor,multiCondition->multiCondition,classFilter->classFilter);
        // } 
    }   
}

NAN_METHOD(NogVertex::GetOutEdgeCursor) {
    if(info.Length()!=4 && info.Length()!=5){
        Nan::ThrowError("4 or 5 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
    // get resultSetCursor
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
    // get recordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // getInEdgeCursor vertex without condition
    if(info.Length()==4){
        if(!classFilterType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // getOutEdgeCursor
        resultSetCursor->resultSetCursor = nogdb::Vertex::getOutEdgeCursor(*txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    }
    // getOutEdgeCursor vertex with condition or multiCondition
    else if(info.Length()==5){
        // check condition / multiCondition type
        if(!conditionType->HasInstance(arg_4) ){//&& !MultiConditionType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
        // get classFilter
        if(!classFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe4.ToLocalChecked());
            // getOutEdgeCursor
            resultSetCursor->resultSetCursor = nogdb::Vertex::getOutEdgeCursor(*txn->txn,recordDesc->recordDescriptor,condition->condition,classFilter->classFilter);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe4.ToLocalChecked());
        //     // getOutEdgeCursor
        //     resultSetCursor->resultSetCursor = nogdb::Vertex::getOutEdgeCursor(*txn->txn,recordDesc->recordDescriptor,multiCondition->multiCondition,classFilter->classFilter);
        // } 
    }   
}

NAN_METHOD(NogVertex::GetAllEdgeCursor) {
    if(info.Length()!=4 && info.Length()!=5){
        Nan::ThrowError("4 or 5 arguments required");
        return;
    }
    
    v8::Local<v8::FunctionTemplate> resultSetCursorType = Nan::New<v8::FunctionTemplate>(NogResultSetCursor::constructor);
    v8::Local<v8::FunctionTemplate> txnType = Nan::New<v8::FunctionTemplate>(NogTxn::constructor);
    v8::Local<v8::FunctionTemplate> recordDescriptorType = Nan::New<v8::FunctionTemplate>(NogRecordDescriptor::constructor);
    v8::Local<v8::FunctionTemplate> classFilterType = Nan::New<v8::FunctionTemplate>(NogClassFilter::constructor);
    v8::Local<v8::FunctionTemplate> conditionType = Nan::New<v8::FunctionTemplate>(NogCondition::constructor);
    // v8::Local<v8::FunctionTemplate> multiConditionType = Nan::New<v8::FunctionTemplate>(NogMultiCondition::constructor);

    v8::Handle<v8::Object> arg_1 = info[0]->ToObject();
    v8::Handle<v8::Object> arg_2 = info[1]->ToObject();
    v8::Handle<v8::Object> arg_3 = info[2]->ToObject();
    v8::Handle<v8::Object> arg_4 = info[3]->ToObject();
    v8::Handle<v8::Object> arg_5 = info[4]->ToObject();
    // get resultSetCursor
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
    // get recordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* recordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // getAllEdgeCursor vertex without condition
    if(info.Length()==4){
        if(!classFilterType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // getAllEdgeCursor
        resultSetCursor->resultSetCursor = nogdb::Vertex::getAllEdgeCursor(*txn->txn,recordDesc->recordDescriptor,classFilter->classFilter);
    }
    // getAllEdgeCursor vertex with condition or multiCondition
    else if(info.Length()==5){
        // check condition / multiCondition type
        if(!conditionType->HasInstance(arg_4) ){//&& !MultiConditionType->HasInstance(arg_4)){
            Nan::ThrowError("arg4: condition or multiCondition required");
            return;
        }
        // get classFilter
        if(!classFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: ClassFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // condition
        if(conditionType->HasInstance(arg_4)){
            Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
            NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe4.ToLocalChecked());
            // getAllEdgeCursor
            resultSetCursor->resultSetCursor = nogdb::Vertex::getAllEdgeCursor(*txn->txn,recordDesc->recordDescriptor,condition->condition,classFilter->classFilter);
        } 
        // // multiCondition
        // else if(multiConditionType->HasInstance(arg_4)){
        //     Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
        //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe4.ToLocalChecked());
        //     // getAllEdgeCursor
        //     resultSetCursor->resultSetCursor = nogdb::Vertex::getAllEdgeCursor(*txn->txn,recordDesc->recordDescriptor,multiCondition->multiCondition,classFilter->classFilter);
        // } 
    }   
}

NAN_METHOD(NogVertex::GetIndex) {
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
    // getIndex vertex with condition or multiCondition
    // condition
    if(conditionType->HasInstance(arg_4)){
        Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
        NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe3.ToLocalChecked());
        resultSet->resultSet = nogdb::Vertex::getIndex(*txn->txn,className,condition->condition);
    } 
    // // multiCondition
    // else if(multiConditionType->HasInstance(arg_4)){
    //     Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
    //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe3.ToLocalChecked());
    //     resultSet->resultSet = nogdb::Vertex::getIndex(*txn->txn,className,multiCondition->multiCondition);
    // } 
    // type error
    else{
        Nan::ThrowError("arg4: condition or multiCondition required");
        return;
    }
}

NAN_METHOD(NogVertex::GetIndexCursor) {
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
    // getIndexCurcor vertex with condition or multiCondition
    // condition
    if(conditionType->HasInstance(arg_4)){
        Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
        NogCondition* condition = ObjectWrap::Unwrap<NogCondition>(maybe3.ToLocalChecked());
        resultSetCursor->resultSetCursor = nogdb::Vertex::getIndexCursor(*txn->txn,className,condition->condition);
    } 
    // // multiCondition
    // else if(multiConditionType->HasInstance(arg_4)){
    //     Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[3]);
    //     NogMultiCondition* MultiCondition = ObjectWrap::Unwrap<NogMultiCondition>(maybe3.ToLocalChecked());
    //     resultSetCursor->resultSetCursor = nogdb::Vertex::getIndexCursor(*txn->txn,className,multiCondition->multiCondition);
    // } 
    // type error
    else{
        Nan::ThrowError("arg4: condition or multiCondition required");
        return;
    }
}