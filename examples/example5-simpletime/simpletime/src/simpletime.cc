#include <v8.h>
#include <node.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

using namespace node;
using namespace v8;

class Time : public node::ObjectWrap {
 
  public:
    static Handle<Value> New(const Arguments &args); // new Time() 
    static Handle<Value> Epoch(const Arguments &args); // time.getEpoch();
    static Handle<Value> String(const Arguments &args); // time.getString(); 
    static Handle<Value> AddSeconds(const Arguments &args); // time.addSeconds(); 

  private:
    Time();  // constructor
    ~Time(); // destructor
    time_t value;
    int getEpoch();
    void addSeconds(int);
    char * getString(); 
    
};

void Init(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> tpl = FunctionTemplate::New(Time::New);
  tpl->SetClassName(String::NewSymbol("Time"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Your methods here (Object.prototype.<method>)
  tpl->PrototypeTemplate()->Set(String::NewSymbol("epoch"),
      FunctionTemplate::New(Time::Epoch)->GetFunction());

  // Your methods here (Object.prototype.<method>)
  tpl->PrototypeTemplate()->Set(String::NewSymbol("string"),
      FunctionTemplate::New(Time::String)->GetFunction());

  // Your methods here (Object.prototype.<method>)
  tpl->PrototypeTemplate()->Set(String::NewSymbol("addSeconds"),
      FunctionTemplate::New(Time::AddSeconds)->GetFunction());

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("Time"), constructor);  
}

Time::Time() {
  time (&(this->value));  
}

Time::~Time() {}

int Time::getEpoch() {
  return this->value;
}

void Time::addSeconds(int seconds) {
  this->value += seconds;
}

char * Time::getString() {
  struct tm time;
  char * buf = new char[26];
  localtime_r(&(this->value), &time); 
  memset(buf, 0, 26);
  strftime(buf, 26, "%c", &time);
  return buf;
}

Handle<Value> Time::New(const Arguments& args) {
  HandleScope scope;
  Time* obj = new Time();
  obj->Wrap(args.This());
  return args.This();
}

Handle<Value> Time::Epoch(const Arguments& args)
{
  HandleScope scope;
  Time* obj = Time::Unwrap<Time>(args.This());
  Local<Value> epoch = Number::New(obj->getEpoch());
  return scope.Close(epoch);
}

Handle<Value> Time::AddSeconds(const Arguments& args)
{
  HandleScope scope;
  Time* obj = Time::Unwrap<Time>(args.This());
  if (args.Length() > 0 && args[0]->IsNumber()) {
    int seconds = args[0]->ToInteger()->Value();
    obj->addSeconds(seconds);
  }
  return scope.Close(v8::Undefined());
}


Handle<Value> Time::String(const Arguments& args)
{
  HandleScope scope;
  Time* obj = Time::Unwrap<Time>(args.This());
  char *str = obj->getString(); 
  Local<Value> dateString = String::New(str);
  return scope.Close(dateString);
}

extern "C" {
  static void init(Handle<Object> target)
  {
    Init(target);
  }

  NODE_MODULE(simpletime, init);
}
