
#ifndef  JSARGCONVERT_H
#define  JSARGCONVERT_H

#include <v8.h>
#include "JsException.h"


class JsArgConvert{

public:
// length validation
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


//convert js value to cpp  value 
static bool ToBoolean(const v8::Local<v8::Value> & val){
	if(val->IsUndefined() || !val->IsBoolean()){
		throw ArgumentTypeError();	
	}
	return val->BooleanValue();
}

static int32_t ToInt32(const v8::Local<v8::Value> & val){
	if(val->IsUndefined() 
        || (!val->IsInt32() && !val->IsBoolean()) ){
		throw ArgumentTypeError();	
	}
	return val->Int32Value();
}
static uint32_t ToUint32(const v8::Local<v8::Value> & val){
	if(val->IsUndefined() 
        || (!val->IsUint32() && ! val->IsBoolean())){
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


//convert js value from  cpp value 
static v8::Handle<v8::Value> FromBool(v8::HandleScope & scope , const bool ret){
	return 	scope.Close(v8::Boolean::New(ret));
}
static v8::Handle<v8::Value> FromBool(v8::HandleScope & scope , const int32_t ret){
	return 	scope.Close(v8::Boolean::New(ret));
}
static v8::Handle<v8::Value> FromInt32(v8::HandleScope & scope , const int32_t ret){
	return 	scope.Close(v8::Integer::New(ret));
}
static v8::Handle<v8::Value> FromUint32(v8::HandleScope & scope , const uint32_t ret){
	return 	scope.Close(v8::Integer::New(ret));
}
static v8::Handle<v8::Value> FromFloat(v8::HandleScope & scope , const float ret){
    return FromDouble(scope, (const double)ret);
}
static v8::Handle<v8::Value> FromDouble(v8::HandleScope & scope , const double ret){
	return 	scope.Close(v8::Number::New(ret));
}
static v8::Handle<v8::Value> FromCharPtr(v8::HandleScope & scope , const char * ret){
	return 	scope.Close(v8::String::New(ret));
}
};

#endif   /* JSARGCONVERT_H */
