/* Copyright (c) 2019 The node-webrtc project authors. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE.md file in the root of the source tree. All contributing
 * project authors may be found in the AUTHORS file in the root of the source
 * tree.
 */
#include "error_factory.h"

#include <string>

#include "src/converters.h"
#include "src/converters/napi.h"
#include "src/converters/v8.h"  // IWYU pragma: keep
#include "src/functional/validation.h"

Nan::Persistent<v8::Function> node_webrtc::ErrorFactory::DOMException;  // NOLINT

void node_webrtc::ErrorFactory::Init(Napi::Env env, Napi::Object exports) {
  exports.Set("setDOMException", Napi::Function::New(env, SetDOMException));
}

v8::Local<v8::Value> node_webrtc::ErrorFactory::CreateError(const std::string message) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::Error(Nan::New(message).ToLocalChecked()));
}

Napi::Value node_webrtc::ErrorFactory::napi::CreateError(const Napi::Env env, const std::string message) {
  Napi::EscapableHandleScope scope(env);
  return scope.Escape(Napi::Error::New(env, message).Value());
}

v8::Local<v8::Value> node_webrtc::ErrorFactory::CreateInvalidAccessError(const std::string message) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(CreateDOMException(message, kInvalidAccessError));
}

// FIXME(mroberts): Actually implement this.
Napi::Value node_webrtc::ErrorFactory::napi::CreateInvalidAccessError(const Napi::Env env, const std::string message) {
  Napi::EscapableHandleScope scope(env);
  return scope.Escape(Napi::Error::New(env, message).Value());
}

v8::Local<v8::Value> node_webrtc::ErrorFactory::CreateInvalidModificationError(const std::string message) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(CreateDOMException(message, kInvalidModificationError));
}

// FIXME(mroberts): Actually implement this.
Napi::Value node_webrtc::ErrorFactory::napi::CreateInvalidModificationError(const Napi::Env env, const std::string message) {
  Napi::EscapableHandleScope scope(env);
  return scope.Escape(Napi::Error::New(env, message).Value());
}

v8::Local<v8::Value> node_webrtc::ErrorFactory::CreateInvalidStateError(const std::string message) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(CreateDOMException(message, kInvalidStateError));
}

// FIXME(mroberts): Actually implement this.
Napi::Value node_webrtc::ErrorFactory::napi::CreateInvalidStateError(const Napi::Env env, const std::string message) {
  Napi::EscapableHandleScope scope(env);
  return scope.Escape(Napi::Error::New(env, message).Value());
}

v8::Local<v8::Value> node_webrtc::ErrorFactory::CreateNetworkError(const std::string message) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(CreateDOMException(message, kNetworkError));
}

// FIXME(mroberts): Actually implement this.
Napi::Value node_webrtc::ErrorFactory::napi::CreateNetworkError(const Napi::Env env, const std::string message) {
  Napi::EscapableHandleScope scope(env);
  return scope.Escape(Napi::Error::New(env, message).Value());
}

v8::Local<v8::Value> node_webrtc::ErrorFactory::CreateOperationError(const std::string message) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(CreateDOMException(message, kOperationError));
}

// FIXME(mroberts): Actually implement this.
Napi::Value node_webrtc::ErrorFactory::napi::CreateOperationError(const Napi::Env env, const std::string message) {
  Napi::EscapableHandleScope scope(env);
  return scope.Escape(Napi::Error::New(env, message).Value());
}

v8::Local<v8::Value> node_webrtc::ErrorFactory::CreateRangeError(const std::string message) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::RangeError(Nan::New(message).ToLocalChecked()));
}

Napi::Value node_webrtc::ErrorFactory::napi::CreateRangeError(const Napi::Env env, const std::string message) {
  Napi::EscapableHandleScope scope(env);
  return scope.Escape(Napi::RangeError::New(env, message).Value());
}

v8::Local<v8::Value> node_webrtc::ErrorFactory::CreateSyntaxError(const std::string message) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::SyntaxError(Nan::New(message).ToLocalChecked()));
}

// FIXME(mroberts): Actually implement this.
Napi::Value node_webrtc::ErrorFactory::napi::CreateSyntaxError(const Napi::Env env, const std::string message) {
  Napi::EscapableHandleScope scope(env);
  return scope.Escape(Napi::Error::New(env, message).Value());
}

const char* node_webrtc::ErrorFactory::DOMExceptionNameToString(DOMExceptionName name) {
  switch (name) {
    case kInvalidAccessError:
      return "InvalidAccessError";
    case kInvalidModificationError:
      return "InvalidModificationError";
    case kInvalidStateError:
      return "InvalidStateError";
    case kNetworkError:
      return "NetworkError";
    case kOperationError:
      return "OperationError";
  }
}

v8::Local<v8::Value> node_webrtc::ErrorFactory::CreateDOMException(const std::string message, const DOMExceptionName name) {
  Nan::EscapableHandleScope scope;
  auto prefix = DOMExceptionNameToString(name);
  if (!DOMException.IsEmpty()) {
    auto constructor = Nan::New(DOMException);
    v8::Local<v8::Value> cargv[2];
    cargv[0] = Nan::New(message).ToLocalChecked();
    cargv[1] = Nan::New(prefix).ToLocalChecked();
    auto result = Nan::NewInstance(constructor, 2, cargv);
    if (!result.IsEmpty()) {
      return scope.Escape(result.ToLocalChecked());
    }
  }
  return scope.Escape(Nan::Error(Nan::New(std::string(prefix) + ": " + message).ToLocalChecked()));
}

Napi::Value node_webrtc::ErrorFactory::SetDOMException(const Napi::CallbackInfo& info) {
  auto maybeDOMException = node_webrtc::From<Napi::Function>(info[0]);
  if (maybeDOMException.IsInvalid()) {
    Napi::TypeError::New(info.Env(), maybeDOMException.ToErrors()[0]).ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto domException = node_webrtc::napi::UnsafeToV8(maybeDOMException.UnsafeFromValid());
  DOMException.Reset(domException.As<v8::Function>());
  return info.Env().Undefined();
}