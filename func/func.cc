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

using namespace v8;  
Handle<Value> Method_add(const Arguments& args) {
    HandleScope scope;
    if(args.Length() < 2) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }
    if(!args[0]->IsInt32() || !args[1]->IsInt32()){
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }
    int one = args[0]->IntegerValue();
    int two = args[1]->IntegerValue();
    int ret = add(one, two);
    Local<v8::Integer> ret_val = v8::Integer::New(ret);
    return scope.Close(ret_val);
}

Handle<Value> Method_add_d(const Arguments& args) {
    HandleScope scope;
    if(args.Length() < 2) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }
    if(!args[0]->IsNumber() || !args[1]->IsNumber()){
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    double one = args[0]->NumberValue();
    double two = args[1]->NumberValue();
    double ret = add_d(one, two);
    Local<Number> ret_val = v8::Number::New(ret);
    return scope.Close(ret_val);
}

Handle<Value> Method_minus_d(const Arguments& args) {
    HandleScope scope;
    if(args.Length() < 2) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }
    if(!args[0]->IsNumber() || !args[1]->IsNumber()){
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    double one = args[0]->NumberValue();
    double two = args[1]->NumberValue();
    double ret = minus_d(one, two);
    Local<Number> ret_val = v8::Number::New(ret);
    return scope.Close(ret_val);
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
