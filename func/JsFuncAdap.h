
#ifndef  JSFUNCADAP_H
#define  JSFUNCADAP_H

#include <v8.h>
#include "JsException.h"

class JsIFunc {
public:
    virtual v8::Handle<v8::Value> Method(v8::HandleScope & scope, const v8::Arguments & args) = 0;
};

template<typename T>
class JsFuncAdap{
public:
    static v8::Handle<v8::Value> Method(const v8::Arguments& args) {
        v8::HandleScope scope;
        try{
            T * obj = new T();
            return obj->Method(scope, args);
        }
        catch(ArgumentLengthError & arg){
            v8::ThrowException(v8::Exception::TypeError(v8::String::New(arg.what())));
            return scope.Close(v8::Undefined());
        }
        catch(ArgumentTypeError & arg){
            v8::ThrowException(v8::Exception::TypeError(v8::String::New(arg.what())));
            return scope.Close(v8::Undefined());
        }
    }
};


#endif   /* JSFUNCADAP_H */
