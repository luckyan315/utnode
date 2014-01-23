#include <node.h>
#include <v8.h>

#include "my_object.h"
#include "emb_object.h"

using namespace v8;  

void InitAll(Handle<Object> exports) {
    MyObject::Init(exports);
    EmbObject::Init(exports);
}

NODE_MODULE(obj, InitAll)
