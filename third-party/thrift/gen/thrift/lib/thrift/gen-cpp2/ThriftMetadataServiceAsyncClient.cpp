/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#include "thrift/lib/thrift/gen-cpp2/ThriftMetadataServiceAsyncClient.h"

#include <thrift/lib/cpp2/gen/client_cpp.h>

namespace apache { namespace thrift { namespace metadata {
typedef apache::thrift::ThriftPresult<false> ThriftMetadataService_getRpcMetadata_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, apache::thrift::protocol::T_STRUCT,  ::apache::thrift::metadata::ThriftMetadata*>> ThriftMetadataService_getRpcMetadata_presult;

template <typename Protocol_>
void ThriftMetadataServiceAsyncClient::getRpcMetadataT(Protocol_* prot, apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback) {
  std::shared_ptr<apache::thrift::transport::THeader> header(ctx, &ctx->header);
  ThriftMetadataService_getRpcMetadata_pargs args;
  auto sizer = [&](Protocol_* p) { return args.serializedSizeZC(p); };
  auto writer = [&](Protocol_* p) { args.write(p); };
  apache::thrift::clientSendT<Protocol_>(prot, rpcOptions, std::move(callback), ctx->ctx, std::move(header), channel_.get(), "getRpcMetadata", writer, sizer, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE);
  ctx->reqContext.setRequestHeader(nullptr);
}



void ThriftMetadataServiceAsyncClient::getRpcMetadata(std::unique_ptr<apache::thrift::RequestCallback> callback) {
  ::apache::thrift::RpcOptions rpcOptions;
  getRpcMetadata(rpcOptions, std::move(callback));
}

void ThriftMetadataServiceAsyncClient::getRpcMetadata(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback) {
  auto ctx = std::make_shared<apache::thrift::detail::ac::ClientRequestContext>(
      apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId(),
      rpcOptions.releaseWriteHeaders(),
      this->handlers_,
      this->getServiceName(),
      "ThriftMetadataService.getRpcMetadata");
  apache::thrift::RequestCallback::Context callbackContext;
  callbackContext.protocolId =
      apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  callbackContext.ctx = std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx);
  getRpcMetadataImpl(rpcOptions, std::move(ctx), apache::thrift::toRequestClientCallbackPtr(std::move(callback), std::move(callbackContext)));
}

void ThriftMetadataServiceAsyncClient::getRpcMetadataImpl(apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback) {
  switch (apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolWriter writer;
      getRpcMetadataT(&writer, rpcOptions, std::move(ctx), std::move(callback));
      break;
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolWriter writer;
      getRpcMetadataT(&writer, rpcOptions, std::move(ctx), std::move(callback));
      break;
    }
    default:
    {
      apache::thrift::detail::ac::throw_app_exn("Could not find Protocol");
    }
  }
}

void ThriftMetadataServiceAsyncClient::sync_getRpcMetadata( ::apache::thrift::metadata::ThriftMetadata& _return) {
  ::apache::thrift::RpcOptions rpcOptions;
  sync_getRpcMetadata(rpcOptions, _return);
}

void ThriftMetadataServiceAsyncClient::sync_getRpcMetadata(apache::thrift::RpcOptions& rpcOptions,  ::apache::thrift::metadata::ThriftMetadata& _return) {
  apache::thrift::ClientReceiveState _returnState;
  apache::thrift::ClientSyncCallback<false> callback(&_returnState);
  auto protocolId = apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  auto evb = apache::thrift::GeneratedAsyncClient::getChannel()->getEventBase();
  auto ctx = std::make_shared<apache::thrift::detail::ac::ClientRequestContext>(
      protocolId,
      rpcOptions.releaseWriteHeaders(),
      this->handlers_,
      this->getServiceName(),
      "ThriftMetadataService.getRpcMetadata");
  getRpcMetadataImpl(rpcOptions, ctx, apache::thrift::RequestClientCallback::Ptr(&callback));
  callback.waitUntilDone(evb);
  _returnState.resetProtocolId(protocolId);
  _returnState.resetCtx(std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx));
  SCOPE_EXIT {
    if (_returnState.header() && !_returnState.header()->getHeaders().empty()) {
      rpcOptions.setReadHeaders(_returnState.header()->releaseHeaders());
    }
  };
  if (!_returnState.buf()) {
    assert(!!_returnState.exception());
    _returnState.exception().throw_exception();
  }
  return folly::fibers::runInMainContext([&] {
      recv_getRpcMetadata(_return, _returnState);
  });
}



folly::Future< ::apache::thrift::metadata::ThriftMetadata> ThriftMetadataServiceAsyncClient::future_getRpcMetadata() {
  ::apache::thrift::RpcOptions rpcOptions;
  return future_getRpcMetadata(rpcOptions);
}

folly::SemiFuture< ::apache::thrift::metadata::ThriftMetadata> ThriftMetadataServiceAsyncClient::semifuture_getRpcMetadata() {
  ::apache::thrift::RpcOptions rpcOptions;
  return semifuture_getRpcMetadata(rpcOptions);
}

folly::Future< ::apache::thrift::metadata::ThriftMetadata> ThriftMetadataServiceAsyncClient::future_getRpcMetadata(apache::thrift::RpcOptions& rpcOptions) {
  folly::Promise< ::apache::thrift::metadata::ThriftMetadata> _promise;
  auto _future = _promise.getFuture();
  auto callback = std::make_unique<apache::thrift::FutureCallback< ::apache::thrift::metadata::ThriftMetadata>>(std::move(_promise), recv_wrapped_getRpcMetadata, channel_);
  getRpcMetadata(rpcOptions, std::move(callback));
  return _future;
}

folly::SemiFuture< ::apache::thrift::metadata::ThriftMetadata> ThriftMetadataServiceAsyncClient::semifuture_getRpcMetadata(apache::thrift::RpcOptions& rpcOptions) {
  auto callbackAndFuture = makeSemiFutureCallback(recv_wrapped_getRpcMetadata, channel_);
  auto callback = std::move(callbackAndFuture.first);
  getRpcMetadata(rpcOptions, std::move(callback));
  return std::move(callbackAndFuture.second);
}

folly::Future<std::pair< ::apache::thrift::metadata::ThriftMetadata, std::unique_ptr<apache::thrift::transport::THeader>>> ThriftMetadataServiceAsyncClient::header_future_getRpcMetadata(apache::thrift::RpcOptions& rpcOptions) {
  folly::Promise<std::pair< ::apache::thrift::metadata::ThriftMetadata, std::unique_ptr<apache::thrift::transport::THeader>>> _promise;
  auto _future = _promise.getFuture();
  auto callback = std::make_unique<apache::thrift::HeaderFutureCallback< ::apache::thrift::metadata::ThriftMetadata>>(std::move(_promise), recv_wrapped_getRpcMetadata, channel_);
  getRpcMetadata(rpcOptions, std::move(callback));
  return _future;
}

folly::SemiFuture<std::pair< ::apache::thrift::metadata::ThriftMetadata, std::unique_ptr<apache::thrift::transport::THeader>>> ThriftMetadataServiceAsyncClient::header_semifuture_getRpcMetadata(apache::thrift::RpcOptions& rpcOptions) {
  auto callbackAndFuture = makeHeaderSemiFutureCallback(recv_wrapped_getRpcMetadata, channel_);
  auto callback = std::move(callbackAndFuture.first);
  getRpcMetadata(rpcOptions, std::move(callback));
  return std::move(callbackAndFuture.second);
}
void ThriftMetadataServiceAsyncClient::getRpcMetadata(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback) {
  getRpcMetadata(std::make_unique<apache::thrift::FunctionReplyCallback>(std::move(callback)));
}

folly::exception_wrapper ThriftMetadataServiceAsyncClient::recv_wrapped_getRpcMetadata( ::apache::thrift::metadata::ThriftMetadata& _return, ::apache::thrift::ClientReceiveState& state) {
  if (state.isException()) {
    return std::move(state.exception());
  }
  if (!state.buf()) {
    return folly::make_exception_wrapper<apache::thrift::TApplicationException>("recv_ called without result");
  }

  using result = ThriftMetadataService_getRpcMetadata_presult;
  constexpr auto const fname = "getRpcMetadata";
  switch (state.protocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state, _return);
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state, _return);
    }
    default:
    {
    }
  }
  return folly::make_exception_wrapper<apache::thrift::TApplicationException>("Could not find Protocol");
}

void ThriftMetadataServiceAsyncClient::recv_getRpcMetadata( ::apache::thrift::metadata::ThriftMetadata& _return, ::apache::thrift::ClientReceiveState& state) {
  auto ew = recv_wrapped_getRpcMetadata(_return, state);
  if (ew) {
    ew.throw_exception();
  }
}

void ThriftMetadataServiceAsyncClient::recv_instance_getRpcMetadata( ::apache::thrift::metadata::ThriftMetadata& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_getRpcMetadata(_return, state);
}

folly::exception_wrapper ThriftMetadataServiceAsyncClient::recv_instance_wrapped_getRpcMetadata( ::apache::thrift::metadata::ThriftMetadata& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_wrapped_getRpcMetadata(_return, state);
}

}}} // apache::thrift::metadata
