/* Copyright (c) 2019 The node-webrtc project authors. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE.md file in the root of the source tree. All contributing
 * project authors may be found in the AUTHORS file in the root of the source
 * tree.
 */
#include "src/interfaces/rtc_rtp_transceiver.h"

#include <webrtc/api/rtp_transceiver_interface.h>
#include <webrtc/api/scoped_refptr.h>

#include "src/converters/arguments.h"
#include "src/converters/absl.h"
#include "src/converters/interfaces.h"
#include "src/enums/webrtc/rtp_transceiver_direction.h"
#include "src/interfaces/rtc_rtp_receiver.h"
#include "src/interfaces/rtc_rtp_sender.h"

namespace node_webrtc {

Napi::FunctionReference& RTCRtpTransceiver::constructor() {
  static Napi::FunctionReference constructor;
  return constructor;
}

RTCRtpTransceiver::RTCRtpTransceiver(
    const Napi::CallbackInfo& info):
  napi::AsyncObjectWrap<RTCRtpTransceiver>("RTCRtpTransceiver", info) {
  if (info.Length() != 2 || !info[0].IsExternal() || !info[1].IsExternal()) {
    Napi::TypeError::New(info.Env(), "You cannot construct a RTCRtpTransceiver").ThrowAsJavaScriptException();
    return;
  }

  auto factory = *static_cast<std::shared_ptr<PeerConnectionFactory>*>(v8::Local<v8::External>::Cast(napi::UnsafeToV8(info[0]))->Value());
  auto transceiver = *static_cast<rtc::scoped_refptr<webrtc::RtpTransceiverInterface>*>(v8::Local<v8::External>::Cast(napi::UnsafeToV8(info[1]))->Value());

  _factory = std::move(factory);
  _transceiver = std::move(transceiver);
}

RTCRtpTransceiver::~RTCRtpTransceiver() {
  wrap()->Release(this);
}

Napi::Value RTCRtpTransceiver::GetMid(const Napi::CallbackInfo& info) {
  CONVERT_OR_THROW_AND_RETURN_NAPI(info.Env(), _transceiver->mid(), result, Napi::Value)
  return result;
}

Napi::Value RTCRtpTransceiver::GetSender(const Napi::CallbackInfo&) {
  return RTCRtpSender::wrap()->GetOrCreate(_factory, _transceiver->sender())->Value();
}

Napi::Value RTCRtpTransceiver::GetReceiver(const Napi::CallbackInfo&) {
  return RTCRtpReceiver::wrap()->GetOrCreate(_factory, _transceiver->receiver())->Value();
}

Napi::Value RTCRtpTransceiver::GetStopped(const Napi::CallbackInfo& info) {
  CONVERT_OR_THROW_AND_RETURN_NAPI(info.Env(), _transceiver->stopped(), result, Napi::Value)
  return result;
}

Napi::Value RTCRtpTransceiver::GetDirection(const Napi::CallbackInfo& info) {
  CONVERT_OR_THROW_AND_RETURN_NAPI(info.Env(), _transceiver->direction(), result, Napi::Value)
  return result;
}

void RTCRtpTransceiver::SetDirection(const Napi::CallbackInfo& info, const Napi::Value& value) {
  auto maybeDirection = From<webrtc::RtpTransceiverDirection>(value);
  if (maybeDirection.IsInvalid()) {
    Napi::TypeError::New(info.Env(), maybeDirection.ToErrors()[0]).ThrowAsJavaScriptException();
    return;
  }
  _transceiver->SetDirection(maybeDirection.UnsafeFromValid());
}

Napi::Value RTCRtpTransceiver::GetCurrentDirection(const Napi::CallbackInfo& info) {
  CONVERT_OR_THROW_AND_RETURN_NAPI(info.Env(), _transceiver->current_direction(), result, Napi::Value)
  return result;
}

Napi::Value RTCRtpTransceiver::Stop(const Napi::CallbackInfo& info) {
  _transceiver->Stop();
  return info.Env().Undefined();
}

Napi::Value RTCRtpTransceiver::SetCodecPreferences(const Napi::CallbackInfo& info) {
  Napi::Error::New(info.Env(), "Not yet implemented; file a feature request against node-webrtc").ThrowAsJavaScriptException();
  return info.Env().Undefined();
}

Wrap <
RTCRtpTransceiver*,
rtc::scoped_refptr<webrtc::RtpTransceiverInterface>,
std::shared_ptr<PeerConnectionFactory>
> * RTCRtpTransceiver::wrap() {
  static auto wrap = new node_webrtc::Wrap <
  RTCRtpTransceiver*,
  rtc::scoped_refptr<webrtc::RtpTransceiverInterface>,
  std::shared_ptr<PeerConnectionFactory>
  > (RTCRtpTransceiver::Create);
  return wrap;
}

RTCRtpTransceiver* RTCRtpTransceiver::Create(
    std::shared_ptr<PeerConnectionFactory> factory,
    rtc::scoped_refptr<webrtc::RtpTransceiverInterface> transceiver) {
  auto env = constructor().Env();
  Napi::HandleScope scope(env);

  auto factoryExternal = Nan::New<v8::External>(static_cast<void*>(&factory));
  auto transceiverExternal = Nan::New<v8::External>(static_cast<void*>(&transceiver));

  auto object = constructor().New({
    napi::UnsafeFromV8(env, factoryExternal),
    napi::UnsafeFromV8(env, transceiverExternal)
  });

  return Unwrap(object);
}

void RTCRtpTransceiver::Init(Napi::Env env, Napi::Object exports) {
  auto func = DefineClass(env, "RTCRtpTransceiver", {
    InstanceAccessor("mid", &RTCRtpTransceiver::GetMid, nullptr),
    InstanceAccessor("sender", &RTCRtpTransceiver::GetSender, nullptr),
    InstanceAccessor("receiver", &RTCRtpTransceiver::GetReceiver, nullptr),
    InstanceAccessor("stopped", &RTCRtpTransceiver::GetStopped, nullptr),
    InstanceAccessor("direction", &RTCRtpTransceiver::GetDirection, &RTCRtpTransceiver::SetDirection),
    InstanceAccessor("currentDirection", &RTCRtpTransceiver::GetCurrentDirection, nullptr),
    InstanceMethod("stop", &RTCRtpTransceiver::Stop),
    InstanceMethod("setCodecPreferences", &RTCRtpTransceiver::SetCodecPreferences),
  });

  constructor() = Napi::Persistent(func);
  constructor().SuppressDestruct();

  exports.Set("RTCRtpTransceiver", func);
}

TO_NAPI_IMPL(RTCRtpTransceiver*, pair) {
  return Pure(pair.second->Value().As<Napi::Value>());
}

TO_JS_IMPL(RTCRtpTransceiver*, value) {
  return Pure(napi::UnsafeToV8(value->Value()));
}

}  // namespace node_webrtc