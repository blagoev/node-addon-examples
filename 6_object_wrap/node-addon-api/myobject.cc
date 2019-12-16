#include "myobject.h"

Napi::FunctionReference MyObject::constructor;

Napi::Value create(const Napi::CallbackInfo& info) {
	Napi::EscapableHandleScope scope(info.Env());
	Napi::Value val = MyObject::constructor.New({});
	return scope.Escape(info.Env().Undefined());
}

Napi::Object MyObject::Init(Napi::Env env, Napi::Object exports) {
	Napi::HandleScope scope(env);

	Napi::Function func =
		DefineClass(env,
			"MyObject",
			{ InstanceMethod("plusOne", &MyObject::PlusOne),
			 InstanceAccessor("value", &MyObject::GetValue, nullptr),
			 InstanceMethod("multiply", &MyObject::Multiply),
			 StaticMethod("create", create),
			});

	constructor = Napi::Persistent(func);
	constructor.SuppressDestruct();

	exports.Set("MyObject", func);
	return exports;
}

//This demonstrates mostly an error in the example code and not a bug in NAPI C++ addon code. Still I commented it as an issue 
//Given the example has not enabled c++ exeptions, there should be a `return;` after the `ThrowAsJavaScriptException` statement
MyObject::MyObject(const Napi::CallbackInfo& info)
	: Napi::ObjectWrap<MyObject>(info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	throw Napi::Error::New(env, "TEST");

	int length = info.Length();

	if (length <= 0 || !info[0].IsNumber()) {
		//This does not do `throw Napi::TypeError::New(env, "Number expected")
		//It means the statements after this call will get executed. It's wrong for many reasons mostly because it brakes normal exception behaviour. 
		Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();

		//With eneabled c++ exceptions this should be the correct way
		//throw Napi::TypeError::New(env, "Number expected");

		//With disabled c++ exceptions this should be the correct way
		//return;
	}

	//When this executes the exception thrown to JS is "A number was expected" and not "Number expected" which was the intended behaviour
	Napi::Number value = info[0].As<Napi::Number>();
	this->value_ = value.DoubleValue();
}

//Lets make GetValue call multiply
Napi::Value MyObject::GetValue(const Napi::CallbackInfo& info) {
	Napi::Function func = info.This().As<Napi::Object>().Get("multiply").As<Napi::Function>();
	return func.Call(info.This(), { info.This() });
}

//Lets make PlusOne try to get the value before doing some work
Napi::Value MyObject::PlusOne(const Napi::CallbackInfo& info) {
	Napi::Object object = info[0].As<Napi::Object>();

	//this should fail with 'Not implemented' and throw the same exception to the caller
	Napi::Value value = object.GetFixed("value");
	//do some work with the value

	//return the result
	Napi::Value result = info.Env().Null();
	return result;
}

//Multiply is not implemented right now
Napi::Value MyObject::Multiply(const Napi::CallbackInfo& info) {
	throw Napi::Error::New(info.Env(), "Not implemented");
}
