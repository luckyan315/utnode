//#define BUILDING_NODE_EXTENSION

#include <node.h>
#include "my_object.h"

using namespace v8;

Persistent<Function> MyObject::constructor;

MyObject::MyObject(double value, int ival, char * str) : value_(value) {
    test_.dval_ = value;
    test_.ival_ = ival;
    test_.str_ = str;
}

MyObject::~MyObject() {
}

void MyObject::Init(Handle<Object> exports) {

    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("MyObject"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne"),
            FunctionTemplate::New(PlusOne)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("print"),
            FunctionTemplate::New(Print)->GetFunction());
    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("MyObject"), constructor);
}

Handle<Value> MyObject::New(const Arguments& args) {
    HandleScope scope;

    if(args.Length() < 3){
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new MyObject(...)`
        double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        int ival = args[1]->IsUndefined() ? 0 : args[1]->IntegerValue();

        String::AsciiValue s2(args[2]);
        char * str = 0;
        if(!args[2]->IsUndefined() && args[2]->IsString()){
            str = *s2;
        }

        MyObject* obj = new MyObject(value, ival, str);
        obj->Wrap(args.This());
        return args.This();
    } else {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        const int argc = 3;
        Local<Value> argv[argc] = { args[0], args[1] , args[2]};
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

Handle<Value> MyObject::PlusOne(const Arguments& args) {
    HandleScope scope;

    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.This());
    obj->value_ += 1;

    return scope.Close(Number::New(obj->value_));
}

Handle<Value> MyObject::Print(const Arguments& args) {
    HandleScope scope;

    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.This());
    printf("obj value is single value %f, struct double val %f, struct int value %d, struct string value %s\n", obj->value_, obj->test_.dval_, obj->test_.ival_, obj->test_.str_);

    return scope.Close(Undefined());
}
