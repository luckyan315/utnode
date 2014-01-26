#include <node.h>
#include <v8.h>
#include "JsArgConvert.h"
#include "JsFuncAdap.h"


using namespace v8;  

int add(int one, int two){
    return one + two;
}
class JsAdd : public JsIFunc{
public:
    v8::Handle<v8::Value> Method(v8::HandleScope & scope, const v8::Arguments & args){
        JsArgConvert::LenGt(args, 2);
        int one = JsArgConvert::ToInt32(args[0]);
        int two = JsArgConvert::ToInt32(args[1]);
        int ret = add(one, two);
        return JsArgConvert::FromInt32(scope, ret);
    }
};


double add_d(double one ,double two){
    return one * two;
}
class JsAdd_D : public  JsIFunc{
public:
    v8::Handle<v8::Value> Method(v8::HandleScope & scope, const v8::Arguments & args){
        JsArgConvert::LenGt(args, 2);
        double one = JsArgConvert::ToDouble(args[0]);
        double two = JsArgConvert::ToDouble(args[1]);
        double ret = add_d(one, two);
        return JsArgConvert::FromDouble(scope, ret);
    }
};


double minus_d(double one ,double two){
    return one - two;
}
class JsMinus_D : public JsIFunc { 
public:
    v8::Handle<v8::Value> Method(v8::HandleScope & scope, const v8::Arguments & args){
        JsArgConvert::LenGt(args, 2);
        double one = JsArgConvert::ToDouble(args[0]);
        double two = JsArgConvert::ToDouble(args[1]);
        double ret = minus_d(one, two);
        return JsArgConvert::FromDouble(scope, ret);
    }
};

#include <string.h>
int init_string(char * pstr){
    if(pstr == NULL){
        return -1;
    }
    return strlen(pstr);
}


void init(Handle<Object> target) {
    target->Set(String::NewSymbol("add"),
            FunctionTemplate::New(JsFuncAdap<JsAdd>::Method)->GetFunction());
    target->Set(String::NewSymbol("add_d"),
            FunctionTemplate::New(JsFuncAdap<JsAdd_D>::Method)->GetFunction());
    target->Set(String::NewSymbol("minus_d"),
            FunctionTemplate::New(JsFuncAdap<JsMinus_D>::Method)->GetFunction());
}
NODE_MODULE(func, init)
