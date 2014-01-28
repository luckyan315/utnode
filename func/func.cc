#include <node.h>
#include <v8.h>
#include "JsArgConvert.h"
#include "JsFuncAdap.h"


using namespace v8;  

int add(int a1, int a2){
    return a1 + a2;
}
class JsAdd : public JsIFunc{
public:
    v8::Handle<v8::Value> Method(v8::HandleScope & scope, const v8::Arguments & args){
        JsArgConvert::LenGt(args, 2);
        int a1 = JsArgConvert::ToInt32(args[0]);
        int a2 = JsArgConvert::ToInt32(args[1]);
        int ret = add(a1, a2);
        return JsArgConvert::FromInt32(scope, ret);
    }
};


double add_d(double a1 ,double a2){
    return a1 * a2;
}
class JsAdd_D : public  JsIFunc{
public:
    v8::Handle<v8::Value> Method(v8::HandleScope & scope, const v8::Arguments & args){
        JsArgConvert::LenGt(args, 2);
        double a1 = JsArgConvert::ToDouble(args[0]);
        double a2 = JsArgConvert::ToDouble(args[1]);
        double ret = add_d(a1, a2);
        return JsArgConvert::FromDouble(scope, ret);
    }
};


double minus_d(double a1 ,double a2){
    return a1 - a2;
}
class JsMinus_D : public JsIFunc { 
public:
    v8::Handle<v8::Value> Method(v8::HandleScope & scope, const v8::Arguments & args){
        JsArgConvert::LenGt(args, 2);
        double a1 = JsArgConvert::ToDouble(args[0]);
        double a2 = JsArgConvert::ToDouble(args[1]);
        double ret = minus_d(a1, a2);
        return JsArgConvert::FromDouble(scope, ret);
    }
};

#include <string.h>
int32_t str_test(char * pstr){
    if(pstr == NULL){
        return -1;
    }
    printf("print from c++ :[%s]\n", pstr);
    return (int32_t)strlen(pstr);
}

class JsStrTest : public JsIFunc {
public:
    v8::Handle<v8::Value> Method(v8::HandleScope & scope, const v8::Arguments & args){
        JsArgConvert::LenGt(args, 1);
        boost::shared_array<char> a1  = JsArgConvert::ToNewCharPtr(args[0]);
        int32_t ret = str_test(a1.get());
        return JsArgConvert::FromInt32(scope, ret);
    }
};

void init(Handle<Object> target) {
    target->Set(String::NewSymbol("add"),
            FunctionTemplate::New(JsFuncAdap<JsAdd>::Method)->GetFunction());
    target->Set(String::NewSymbol("add_d"),
            FunctionTemplate::New(JsFuncAdap<JsAdd_D>::Method)->GetFunction());
    target->Set(String::NewSymbol("minus_d"),
            FunctionTemplate::New(JsFuncAdap<JsMinus_D>::Method)->GetFunction());
    target->Set(String::NewSymbol("str_t"),
            FunctionTemplate::New(JsFuncAdap<JsStrTest>::Method)->GetFunction());
}
NODE_MODULE(func, init)
