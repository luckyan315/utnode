#ifndef EMB_OBJECT_H
#define EMB_OBJECT_H

#include <node.h>

#include "emb_test_t.h"

class EmbObject : public node::ObjectWrap {
    public:
        static void Init(v8::Handle<v8::Object> exports);

    private:
        explicit EmbObject(test_t * value = 0, int ival = 0);
        ~EmbObject();

        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Persistent<v8::Function> constructor;

        static v8::Handle<v8::Value> PlusOne(const v8::Arguments& args);
        static v8::Handle<v8::Value> Print(const v8::Arguments& args);

        emb_test_t emb_test_;
};

#endif
