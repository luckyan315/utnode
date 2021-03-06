#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>

#include "test_t.h"

class MyObject : public node::ObjectWrap {
    public:
        static void Init(v8::Handle<v8::Object> exports);

        test_t * GetPtr() {return &test_;}

    private:
        explicit MyObject(double value = 0, int ival = 0, char * str = 0);
        ~MyObject();

        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Persistent<v8::Function> constructor;

        static v8::Handle<v8::Value> PlusOne(const v8::Arguments& args);
        static v8::Handle<v8::Value> Print(const v8::Arguments& args);

        MyObject* Unwrap(v8::Local<v8::Object> obj);

        double value_;
        test_t test_;
};

#endif
