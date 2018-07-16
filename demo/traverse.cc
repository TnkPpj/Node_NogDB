#include <nan.h>
#include <nogdb/nogdb.h>

#include "classFilter.hpp"
#include "pathFilter.hpp"
#include "recordDescriptor.hpp"
#include "resultSet.hpp"
#include "resultSetCursor.hpp"
#include "txn.hpp"

#include "traverse.hpp"

using namespace Nan;

Nan::Persistent<v8::FunctionTemplate> NogTraverse::constructor;

NogTraverse::NogTraverse() {};
NogTraverse::~NogTraverse() {};

NAN_MODULE_INIT(NogTraverse::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NogTraverse::New);
    constructor.Reset(tpl);

    tpl->SetClassName(Nan::New<v8::String>("Traverse").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "inEdgeBfs", NogTraverse::InEdgeBfs);
    SetPrototypeMethod(tpl, "outEdgeBfs", NogTraverse::OutEdgeBfs);
    SetPrototypeMethod(tpl, "allEdgeBfs", NogTraverse::AllEdgeBfs);
    SetPrototypeMethod(tpl, "inEdgeDfs", NogTraverse::InEdgeDfs);
    SetPrototypeMethod(tpl, "outEdgeDfs", NogTraverse::OutEdgeDfs);
    SetPrototypeMethod(tpl, "allEdgeDfs", NogTraverse::AllEdgeDfs);
    SetPrototypeMethod(tpl, "shortestPath", NogTraverse::ShortestPath);
    SetPrototypeMethod(tpl, "inEdgeBfsCursor", NogTraverse::InEdgeBfsCursor);
    SetPrototypeMethod(tpl, "outEdgeBfsCursor", NogTraverse::OutEdgeBfsCursor);
    SetPrototypeMethod(tpl, "allEdgeBfsCursor", NogTraverse::AllEdgeBfsCursor);
    SetPrototypeMethod(tpl, "inEdgeDfsCursor", NogTraverse::InEdgeDfsCursor);
    SetPrototypeMethod(tpl, "outEdgeDfsCursor", NogTraverse::OutEdgeDfsCursor);
    SetPrototypeMethod(tpl, "allEdgeDfsCursor", NogTraverse::AllEdgeDfsCursor);
    SetPrototypeMethod(tpl, "shortestPathCursor", NogTraverse::ShortestPathCursor);

    Set(target, Nan::New<v8::String>("Traverse").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(NogTraverse::New) {
    NogTraverse* obj = new NogTraverse();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(NogTraverse::InEdgeBfs) {
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse inEdgeBfs only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse inEdgeBfs
        resultSet->resultSet = nogdb::Traverse::inEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse inEdgeBfs classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse inEdgeBfs
        resultSet->resultSet = nogdb::Traverse::inEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::OutEdgeBfs) {
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse outEdgeBfs only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse outEdgeBfs
        resultSet->resultSet = nogdb::Traverse::outEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse outEdgeBfs classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse outEdgeBfs
        resultSet->resultSet = nogdb::Traverse::outEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::AllEdgeBfs) {
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse allEdgeBfs only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse allEdgeBfs
        resultSet->resultSet = nogdb::Traverse::allEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse allEdgeBfs classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse allEdgeBfs
        resultSet->resultSet = nogdb::Traverse::allEdgeBfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::InEdgeDfs) {
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse inEdgeDfs only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse inEdgeDfs
        resultSet->resultSet = nogdb::Traverse::inEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse inEdgeDfs classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse inEdgeDfs
        resultSet->resultSet = nogdb::Traverse::inEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::OutEdgeDfs) {
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse OutEdgeDfs only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse OutEdgeDfs
        resultSet->resultSet = nogdb::Traverse::outEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse OutEdgeDfs classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse OutEdgeDfs
        resultSet->resultSet = nogdb::Traverse::outEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::AllEdgeDfs) {
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse AllEdgeDfs only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse AllEdgeDfs
        resultSet->resultSet = nogdb::Traverse::allEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse AllEdgeDfs classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse AllEdgeDfs
        resultSet->resultSet = nogdb::Traverse::allEdgeDfs(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::ShortestPath) {
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
    // get srcVertexRecordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* srcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // get dstVertexRecordDescriptor
    if(!recordDescriptorType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
    NogRecordDescriptor* dstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe4.ToLocalChecked());
    // traverse shortestPath only classFilter
    if(info.Length()==5){
        // get classFilter
        if(!classFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse shortestPath
        resultSet->resultSet = nogdb::Traverse::shortestPath(txn->txn,
                                                            srcVertexRecordDesc->recordDescriptor,
                                                            dstVertexRecordDesc->recordDescriptor,
                                                            classFilter->classFilter);
    } 
    // traverse shortestPath pathFilter & classFilter
    else if (info.Length()==6){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe5.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe6 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe6.ToLocalChecked());
        // traverse shortestPath
        resultSet->resultSet = nogdb::Traverse::shortestPath(txn->txn,
                                                            srcVertexRecordDesc->recordDescriptor,
                                                            dstVertexRecordDesc->recordDescriptor,
                                                            pathFilter->pathFilter,classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::InEdgeBfsCursor) {
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
    // get resultSetCursor for return
    if(!resultSetCursorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSetCursor required");
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse inEdgeBfsCursor only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse inEdgeBfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::inEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse inEdgeBfsCursor classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse inEdgeBfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::inEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::OutEdgeBfsCursor) {
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
    // get resultSetCursor for return
    if(!resultSetCursorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSetCursor required");
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse OutEdgeBfsCursor only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse OutEdgeBfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::outEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse OutEdgeBfsCursor classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse outEdgeBfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::outEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::AllEdgeBfsCursor) {
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
    // get resultSetCursor for return
    if(!resultSetCursorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSetCursor required");
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse allEdgeBfsCursor only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse allEdgeBfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::allEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse allEdgeBfsCursor classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse allEdgeBfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::allEdgeBfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::InEdgeDfsCursor) {
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
    // get resultSetCursor for return
    if(!resultSetCursorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSetCursor required");
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse inEdgeDfsCursor only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse inEdgeDfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::inEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse inEdgeDfsCursor classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse inEdgeDfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::inEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::OutEdgeDfsCursor) {
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
    // get resultSetCursor for return
    if(!resultSetCursorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSetCursor required");
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse outEdgeDfsCursor only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse outEdgeDfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::outEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse outEdgeDfsCursor classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse outEdgeDfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::outEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::AllEdgeDfsCursor) {
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
    // get resultSetCursor for return
    if(!resultSetCursorType->HasInstance(arg_1)){
        Nan::ThrowError("arg1: ResultSetCursor required");
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
    // get minDepth
    if(!info[3]->IsUint32()){
        Nan::ThrowError("arg4: string required");
        return;
    }
    unsigned int minDepth = info[3]->Uint32Value();
    // get maxDepth
    if(!info[4]->IsUint32()){
        Nan::ThrowError("arg5: string required");
        return;
    }
    unsigned int maxDepth = info[4]->Uint32Value();
    // traverse allEdgeDfsCursor only classFilter
    if(info.Length()==6){
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe4.ToLocalChecked());
        // traverse allEdgeDfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::allEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,classFilter->classFilter);
    }
    // traverse allEdgeDfsCursor classFilter & pathFilter
    else if (info.Length()==7){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[5]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe4.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_7)){
            Nan::ThrowError("arg7: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[6]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse allEdgeDfsCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::allEdgeDfsCursor(txn->txn,recordDesc->recordDescriptor,
                                                            minDepth,maxDepth,pathFilter->pathFilter,
                                                            classFilter->classFilter);
    }
}

NAN_METHOD(NogTraverse::ShortestPathCursor) {
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
    // get srcVertexRecordDescriptor
    if(!recordDescriptorType->HasInstance(arg_3)){
        Nan::ThrowError("arg3: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe3 = Nan::To<v8::Object>(info[2]);
    NogRecordDescriptor* srcVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe3.ToLocalChecked());
    // get dstVertexRecordDescriptor
    if(!recordDescriptorType->HasInstance(arg_4)){
        Nan::ThrowError("arg4: RecordDescriptor required");
        return;
    }
    Nan::MaybeLocal<v8::Object> maybe4 = Nan::To<v8::Object>(info[3]);
    NogRecordDescriptor* dstVertexRecordDesc = ObjectWrap::Unwrap<NogRecordDescriptor>(maybe4.ToLocalChecked());
    // traverse shortestPathCursor only classFilter
    if(info.Length()==5){
        // get classFilter
        if(!classFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe5.ToLocalChecked());
        // traverse shortestPathCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::shortestPathCursor(txn->txn,
                                                            srcVertexRecordDesc->recordDescriptor,
                                                            dstVertexRecordDesc->recordDescriptor,
                                                            classFilter->classFilter);
    } 
    // traverse shortestPathCursor pathFilter & classFilter
    else if (info.Length()==6){
        // get pathFilter
        if(!pathFilterType->HasInstance(arg_5)){
            Nan::ThrowError("arg5: PathFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe5 = Nan::To<v8::Object>(info[4]);
        NogPathFilter* pathFilter = ObjectWrap::Unwrap<NogPathFilter>(maybe5.ToLocalChecked());
        // get classFilter
        if(!classFilterType->HasInstance(arg_6)){
            Nan::ThrowError("arg6: classFilter required");
            return;
        }
        Nan::MaybeLocal<v8::Object> maybe6 = Nan::To<v8::Object>(info[5]);
        NogClassFilter* classFilter = ObjectWrap::Unwrap<NogClassFilter>(maybe6.ToLocalChecked());
        // traverse shortestPathCursor
        resultSetCursor->resultSetCursor = nogdb::Traverse::shortestPathCursor(txn->txn,
                                                            srcVertexRecordDesc->recordDescriptor,
                                                            dstVertexRecordDesc->recordDescriptor,
                                                            pathFilter->pathFilter,classFilter->classFilter);
    }
}