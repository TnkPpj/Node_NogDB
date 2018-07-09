#include <nan.h>

#include "bytes.hpp"
#include "classDescriptor.hpp"
#include "classFilter.hpp"
#include "condition.hpp"
#include "context.hpp"
#include "dbInfo.hpp"
#include "multiCondition.hpp"
#include "pathFilter.hpp"
#include "propertyDescriptor.hpp"
#include "record.hpp"
#include "recordDescriptor.hpp"
#include "recordId.hpp"
#include "result.hpp"
#include "resultSet.hpp"
#include "resultSetCursor.hpp"
#include "txn.hpp"

void InitAll(v8::Local<v8::Object> exports) {
  // NogBytes::Init(exports);
  // NogClassDescriptor::Init(exports);
  // NogClassFilter::Init(exports);
  // NogCondition::Init(exports);
  NogContext::Init(exports);
  // NogDBInfo::Init(exports);
  // NogMultiCondition::Init(exports);
  // NogPathFilter::Init(exports);
  // NogPropertyDescriptor::Init(exports);
  // NogRecord::Init(exports);
  // NogRecordDescriptor::Init(exports);
  // NogRecordId::Init(exports);
  // NogResult::Init(exports);
  // NogResultSet::Init(exports);
  // NogResultSetCursor::Init(exports);
  NogTxn::Init(exports);
  
}

NODE_MODULE(nogdb, InitAll)