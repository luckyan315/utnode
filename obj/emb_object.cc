#include <node.h>
#include "emb_object.h"
#include "my_object.h"

using namespace v8;


Persistent<Function> EmbObject::constructor;

EmbObject::EmbObject(test_t * test, int ival){
    emb_test_.ptest_ = test;
    emb_test_.num_ = ival;
}

EmbObject::~EmbObject() {
}

void EmbObject::Init(Handle<Object> exports) {

    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("EmbObject"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne"),
            FunctionTemplate::New(PlusOne)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("print"),
            FunctionTemplate::New(Print)->GetFunction());
    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("EmbObject"), constructor);
}

Handle<Value> EmbObject::New(const Arguments& args) {
    HandleScope scope;

    if(args.Length() < 2){
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new EmbObject(...)`
        MyObject * pMyobj = args[0]->IsUndefined() ? 0 : node::ObjectWrap::Unwrap<MyObject>(args[0]->ToObject());
        int ival = args[1]->IsUndefined() ? 0 : args[1]->IntegerValue();

        
        EmbObject* obj = new EmbObject(pMyobj->GetPtr(), ival);
        obj->Wrap(args.This());
        return args.This();
    } else {
        // Invoked as plain function `EmbObject(...)`, turn into construct call.
        const int argc = 2;
        Local<Value> argv[argc] = { args[0], args[1]};
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

Handle<Value> EmbObject::PlusOne(const Arguments& args) {
    HandleScope scope;

    EmbObject* obj = ObjectWrap::Unwrap<EmbObject>(args.This());
    obj->emb_test_.num_ += 1;

    return scope.Close(Number::New(obj->emb_test_.num_));
}

Handle<Value> EmbObject::Print(const Arguments& args) {
    HandleScope scope;

    EmbObject* obj = ObjectWrap::Unwrap<EmbObject>(args.This());
    printf("int value [%d]\nobj struct double val [%f], struct int value [%d], struct string value [%s]\n", obj->emb_test_.num_, obj->emb_test_.ptest_->dval_, obj->emb_test_.ptest_->ival_, obj->emb_test_.ptest_->str_);

    return scope.Close(Undefined());
}
