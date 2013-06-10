#include <v8.h>
#include <node.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

using namespace node;
using namespace v8;

Handle<Value> Uid(const Arguments& args);

void Init(Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::NewSymbol("uid"), Persistent<FunctionTemplate>::New(FunctionTemplate::New(Uid))->GetFunction());
};


Handle<Value> Uid(const Arguments& args)
{
  HandleScope scope;
  struct passwd *user = NULL;

  if (args.Length() > 0 && args[0]->IsString()) {
    String::Utf8Value name(args[0]->ToString());
    user = getpwnam(*name);
  } else {
    return ThrowException(Exception::Error(String::New("you must supply the username")));
  }

  if (user) {
    Handle<Value> result = Number::New(user->pw_uid);
    return scope.Close(result);
  } else {
    return ThrowException(Exception::Error(String::New("username not found")));
  }
}

extern "C" {
  static void init (Handle<Object> target)
  {
    Init(target);
  }

  NODE_MODULE(pwname, init);
}
