#include <nan.h>
#include "nogdb.h"

void InitNogdb(v8::Local<v8::Object> exports) {
  NogdbTest::Init(exports);
  NogContext::Init(exports);
  NogTxn::Init(exports);
  NogDBInfo::Init(exports);
  NogClassDescriptor::Init(exports);
}

NODE_MODULE(nogdb, InitNogdb)