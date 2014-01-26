#include <node.h>
#include <v8.h>
#include "JsArgConvert.h"




using namespace v8;  

/*  
v8::Handle<v8::Value> skin_method_add(v8::HandleScope & scope, const v8::Arguments & args){
    JsArgConvert::LenGt(args, 2);
    int one = JsArgConvert::ToInt32(args[0]);
    int two = JsArgConvert::ToInt32(args[1]);
    int ret = add(one, two);
    return JsArgConvert::from_int32(scope, ret);
}
Handle<Value> Method_add(const Arguments& args) {
    HandleScope scope;
	try{
        return skin_method_add(scope, args);
	}
	catch(ArgumentLengthError & arg){
        ThrowException(Exception::TypeError(String::New(arg.what())));
        return scope.Close(Undefined());
	}
	catch(ArgumentTypeError & arg){
        ThrowException(Exception::TypeError(String::New(arg.what())));
        return scope.Close(Undefined());
	}
}*/

template<typename T>
class JsCommon{
public:
    static Handle<Value> Method(const Arguments& args) {
        HandleScope scope;
        try{
            T * obj = new T();
            return obj->skin_method(scope, args);
        }
        catch(ArgumentLengthError & arg){
            ThrowException(Exception::TypeError(String::New(arg.what())));
            return scope.Close(Undefined());
        }
        catch(ArgumentTypeError & arg){
            ThrowException(Exception::TypeError(String::New(arg.what())));
            return scope.Close(Undefined());
        }
    }
};

class JsIFunc {
    virtual v8::Handle<v8::Value> skin_method(v8::HandleScope & scope, const v8::Arguments & args) = 0;
};



int add(int one, int two){
    return one + two;
}
class JsAdd : JsIFunc{
public:
    virtual v8::Handle<v8::Value> skin_method(v8::HandleScope & scope, const v8::Arguments & args){
        JsArgConvert::LenGt(args, 2);
        int one = JsArgConvert::ToInt32(args[0]);
        int two = JsArgConvert::ToInt32(args[1]);
        int ret = add(one, two);
        return JsArgConvert::from_int32(scope, ret);
    }
};


double add_d(double one ,double two){
    return one * two;
}
class JsAdd_D : JsIFunc{
public:
virtual v8::Handle<v8::Value> skin_method(v8::HandleScope & scope, const v8::Arguments & args){
    JsArgConvert::LenGt(args, 2);
    double one = JsArgConvert::ToDouble(args[0]);
    double two = JsArgConvert::ToDouble(args[1]);
    double ret = add_d(one, two);
    return JsArgConvert::from_double(scope, ret);
}
};


/* 
Handle<Value> Method_add_d(const Arguments& args) {
    HandleScope scope;

	try{
		JsArgConvert::LenGt(args, 2);
		double one = JsArgConvert::ToDouble(args[0]);
		double two = JsArgConvert::ToDouble(args[1]);
		double ret = add_d(one, two);
		return JsArgConvert::from_double(scope, ret);
	}
	catch(ArgumentLengthError & arg){
        ThrowException(Exception::TypeError(String::New(arg.what())));
        return scope.Close(Undefined());
	}
	catch(ArgumentTypeError & arg){
        ThrowException(Exception::TypeError(String::New(arg.what())));
        return scope.Close(Undefined());
	}
}
*/



double minus_d(double one ,double two){
    return one - two;
}
Handle<Value> Method_minus_d(const Arguments& args) {
    HandleScope scope;

	try{
		JsArgConvert::LenGt(args, 2);
		double one = JsArgConvert::ToDouble(args[0]);
		double two = JsArgConvert::ToDouble(args[1]);
		double ret = minus_d(one, two);
		return JsArgConvert::from_double(scope, ret);
	}
	catch(ArgumentLengthError & arg){
        ThrowException(Exception::TypeError(String::New(arg.what())));
        return scope.Close(Undefined());
	}
	catch(ArgumentTypeError & arg){
        ThrowException(Exception::TypeError(String::New(arg.what())));
        return scope.Close(Undefined());
	}
}

void init(Handle<Object> target) {
    target->Set(String::NewSymbol("add"),
            FunctionTemplate::New(JsCommon<JsAdd>::Method)->GetFunction());
    target->Set(String::NewSymbol("add_d"),
            FunctionTemplate::New(JsCommon<JsAdd_D>::Method)->GetFunction());
    target->Set(String::NewSymbol("minus_d"),
            FunctionTemplate::New(Method_minus_d)->GetFunction());
}
NODE_MODULE(func, init)
