#include <node.h>
#include <v8.h>


int add(int one, int two){
    return one + two;
}

double add_d(double one ,double two){
    return one * two;
}

double minus_d(double one ,double two){
    return one - two;
}

#include <stdexcept>

class ArgumentLengthError : public std::logic_error{
public:
	ArgumentLengthError() : logic_error("argument  length error"){}
};

class ArgumentTypeError : public std::logic_error{
public:
	ArgumentTypeError(): logic_error("argument type is error"){}

};

using namespace v8;  

void arg_len_gt(const Arguments & args, int len){
	if(args.Length() < len){
		throw ArgumentLengthError();	
	}
}

int32_t arg_to_int32(const Local<Value> & val){
	if(val->IsUndefined() || !val->IsInt32()){
		throw ArgumentTypeError();	
	}
	return val->IntegerValue();
}

double arg_to_double(const Local<Value> & val){
	if(val->IsUndefined() || !val->IsNumber()){
		throw ArgumentTypeError();	
	}
	return val->NumberValue();
}

Handle<Value> int32_to_ret(HandleScope & scope , const int32_t ret){
	return 	scope.Close(v8::Integer::New(ret));
}
Handle<Value> double_to_ret(HandleScope & scope , const double ret){
	return 	scope.Close(v8::Number::New(ret));
}

Handle<Value> Method_add(const Arguments& args) {
    HandleScope scope;
	try{
		arg_len_gt(args, 2);
		int one = arg_to_int32(args[0]);
		int two = arg_to_int32(args[1]);
		int ret = add(one, two);
		return int32_to_ret(scope, ret);
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

Handle<Value> Method_add_d(const Arguments& args) {
    HandleScope scope;

	try{
		arg_len_gt(args, 2);
		double one = arg_to_double(args[0]);
		double two = arg_to_double(args[1]);
		double ret = add_d(one, two);
		return double_to_ret(scope, ret);
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

Handle<Value> Method_minus_d(const Arguments& args) {
    HandleScope scope;

	try{
		arg_len_gt(args, 2);
		double one = arg_to_double(args[0]);
		double two = arg_to_double(args[1]);
		double ret = minus_d(one, two);
		return double_to_ret(scope, ret);
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
            FunctionTemplate::New(Method_add)->GetFunction());
    target->Set(String::NewSymbol("add_d"),
            FunctionTemplate::New(Method_add_d)->GetFunction());
    target->Set(String::NewSymbol("minus_d"),
            FunctionTemplate::New(Method_minus_d)->GetFunction());
}
NODE_MODULE(func, init)
