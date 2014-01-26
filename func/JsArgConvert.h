
#ifndef  JSARGCONVERT_H
#define  JSARGCONVERT_H

#include <stdexcept>
class ArgumentLengthError : public std::logic_error{
public:
	ArgumentLengthError() : logic_error("argument  length error"){}
};

class ArgumentTypeError : public std::logic_error{
public:
	ArgumentTypeError(): logic_error("argument type is error"){}

};



#include <v8.h>

class JsArgConvert{

public:
static void LenGt(const v8::Arguments & args, int len){
	if(args.Length() < len){
		throw ArgumentLengthError();	
	}
}
static void LenEq(const v8::Arguments & args, int len){
	if(args.Length() != len){
		throw ArgumentLengthError();	
	}
}
static void LenLt(const v8::Arguments & args, int len){
	if(args.Length() > len){
		throw ArgumentLengthError();	
	}
}

static int32_t ToBoolean(const v8::Local<v8::Value> & val){
	if(val->IsUndefined() || !val->IsBoolean()){
		throw ArgumentTypeError();	
	}
	return val->BooleanValue();
}

static int32_t ToInt32(const v8::Local<v8::Value> & val){
	if(val->IsUndefined() || !val->IsInt32()){
		throw ArgumentTypeError();	
	}
	return val->Int32Value();
}
static uint32_t ToUint32(const v8::Local<v8::Value> & val){
	if(val->IsUndefined() || !val->IsUint32()){
		throw ArgumentTypeError();	
	}
	return val->Uint32Value();
}
static float ToFloat(const v8::Local<v8::Value> & val){
    return (float)ToDouble(val);
}
static double ToDouble(const v8::Local<v8::Value> & val){
	if(val->IsUndefined() || !val->IsNumber()){
		throw ArgumentTypeError();	
	}
	return val->NumberValue();
}

static v8::Handle<v8::Value> from_bool(v8::HandleScope & scope , const int32_t ret){
	return 	scope.Close(v8::Boolean::New(ret));
}
static v8::Handle<v8::Value> from_int32(v8::HandleScope & scope , const int32_t ret){
	return 	scope.Close(v8::Integer::New(ret));
}
static v8::Handle<v8::Value> from_uint32(v8::HandleScope & scope , const uint32_t ret){
	return 	scope.Close(v8::Integer::New(ret));
}
static v8::Handle<v8::Value> from_double(v8::HandleScope & scope , const double ret){
	return 	scope.Close(v8::Number::New(ret));
}
static v8::Handle<v8::Value> from_float(v8::HandleScope & scope , const float ret){
    return from_double(scope, (const double)ret);
}

};

#endif   /* JSARGCONVERT_H */
