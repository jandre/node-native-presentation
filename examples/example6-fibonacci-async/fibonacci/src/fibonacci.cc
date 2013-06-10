#include <v8.h>
#include <node.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

using namespace node;
using namespace v8;


Handle<Value> Calculate(const Arguments& args);

void Init(Handle<Object> target) {
  HandleScope scope;
  target->Set(String::NewSymbol("calculate"), FunctionTemplate::New(Calculate)->GetFunction());
}

unsigned int fibonacci(int n) {

  if (n <= 0)
    return 0;

  if (n == 1)
    return 1;

  return fibonacci(n  - 1) + fibonacci(n - 2);
}

// Holds all of the 
struct FibonacciContext {  

  uv_work_t request;
  int input; // the value passed to fibonacci();
  unsigned int result; // save the result to be calculated
  Persistent<Function> callback; // js callback

  FibonacciContext(int n, Handle<Function> callback) {
    this->input = n;
    this->callback = Persistent<Function>::New(callback); 
    // set the data to point to myself
    this->request.data = this;
  }

  ~FibonacciContext() {
    this->request.data = NULL;
    this->callback.Dispose(); 
  }
};

void FibonacciWorker(uv_work_t *req) {
  // don't touch v8 objects! 
  FibonacciContext* context = static_cast<FibonacciContext*>(req->data);
  int n = context->input;
  context->result = fibonacci(n);
}

void FibonacciWorkerAfter(uv_work_t *req) {
  // back in v8 land
   HandleScope scope;
   FibonacciContext* context = static_cast<FibonacciContext*>(req->data);
   Local<Value> argv[] = { Local<Value>::New(v8::Null()), Number::New(context->result) };
   // call the callback(null, result);
   context->callback->Call(Context::GetCurrent()->Global(), 2, argv);
   delete context;
   return;
};

Handle<Value> Calculate(const Arguments& args) {
  HandleScope scope;
  Local<Function> callback;
  int n;

  if (args.Length() > 0 && args[0]->IsNumber()) {
    n = args[0]->ToInteger()->Value();
  } else {
    return ThrowException(Exception::Error(String::New("You must supply an integer")));
  }

  if (args.Length() > 1 && args[1]->IsFunction()) {
    callback = Local<Function>::Cast(args[1]); 
  } else {
    return ThrowException(Exception::Error(String::New("You must supply a callback")));
  }

  FibonacciContext *context = new FibonacciContext(n, callback);
  
  uv_queue_work(uv_default_loop(), &context->request,
         FibonacciWorker, FibonacciWorkerAfter);

  return scope.Close(Undefined());
}

extern "C" {
  static void init(Handle<Object> target)
  {
    Init(target);
  }

  NODE_MODULE(fibonacci, init);
}
