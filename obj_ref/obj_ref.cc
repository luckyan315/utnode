#include <node.h>
#include <v8.h>
#include <assert.h>
using namespace v8;  
Handle<Value> Method(const Arguments& args) {
    HandleScope scope;
    return scope.Close(String::New("world"));
}



Handle<Value> UserCreateMethod(const Arguments& args) {
    HandleScope scope;
    char* rc = new char;
    *rc = '1';
    printf("char is %c, rc address %d\n", *rc, (uint32_t)rc);
    return scope.Close(External::Wrap(rc));
    //return scope.Close(String::New("Create OK"));
}

Handle<Value> UserDeleteMethod(const Arguments& args) {
    HandleScope scope;
    char * rc = NULL;
    assert(1 == args.Length());
    if(!args[0]->IsUndefined() && args[0]->IsInt32()){
        uint32_t a = args[0]->ToUint32()->Value();
        rc = (char*)a;
        printf("address is %d, rc %d\n", a, (uint32_t)rc); 
        if(rc != NULL){
            printf("char char %c\n", *rc);
            delete rc;
        }
        else 
            printf("rc is NULL\n");
    }
    else{
        printf("args is undefined\n");
    }
    return scope.Close(String::New("delete OK"));
}

void init(Handle<Object> target) {
    target->Set(String::NewSymbol("hello"),FunctionTemplate::New(Method)->GetFunction());
    target->Set(String::NewSymbol("CreateUser"),FunctionTemplate::New(UserCreateMethod)->GetFunction());
    target->Set(String::NewSymbol("DeleteUser"),FunctionTemplate::New(UserDeleteMethod)->GetFunction());
}



NODE_MODULE(obj_ref, init)
