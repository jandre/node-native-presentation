#include <v8.h>
#include <node.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

using namespace node;
using namespace v8;

Handle<Value> Get(const Arguments& args);

void Init(Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::NewSymbol("get"), FunctionTemplate::New(Get)->GetFunction());
};

Handle<Value> Get(const Arguments& args)
{
  HandleScope scope;
  struct passwd *user = NULL;
  Local<Function> callback;

  if (args.Length() > 1 && args[1]->IsFunction()) {
    callback = Local<Function>::Cast(args[1]); 
  }

  if (args.Length() > 0 && args[0]->IsString()) {
    String::Utf8Value name(args[0]->ToString());
    user = getpwnam(*name);
  } else {

    Local<Value> err = Exception::Error(String::New("you must supply the username")); 

    if (callback.IsEmpty()) {
      return ThrowException(err);
    } else {
      Local<Value> argv[] = { err };
      return callback->Call(Context::GetCurrent()->Global(), 1, argv);
    }
  }

  if (user) {
    Local<Object> obj = Object::New();
    obj->Set(String::New("uid"), Number::New(user->pw_uid));
    obj->Set(String::New("info"), String::New(user->pw_gecos));
    obj->Set(String::New("dir"), String::New(user->pw_dir));
    obj->Set(String::New("shell"), String::New(user->pw_shell));
    obj->Set(String::New("gid"), Number::New(user->pw_gid));

    if (callback.IsEmpty()) {
      return scope.Close(obj);
    } else {
      Local<Value> argv[] = { Local<Value>::New(v8::Null()), obj };
      return callback->Call(Context::GetCurrent()->Global(), 2, argv);
    }
  } else {

    Local<Value> err = Exception::Error(String::New("username not found")); 

    if (callback.IsEmpty()) {
      return ThrowException(err);
    } else {
      Local<Value> argv[] = { err };
      return callback->Call(Context::GetCurrent()->Global(), 1, argv);
    }

  }
}

extern "C" {
  static void init (Handle<Object> target)
  {
    Init(target);
  }

  NODE_MODULE(pwname, init);
}
