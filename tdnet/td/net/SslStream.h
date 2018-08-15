//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/utils/port/Fd.h"
#include "td/utils/port/SocketFd.h"
#include "td/utils/Slice.h"
#include "td/utils/Status.h"
#include "td/utils/ByteFlow.h"
#include "td/utils/BufferedFd.h"

namespace td {

namespace detail {
class SslStreamImpl;
}

class SslStream {
 public:
  SslStream();
  SslStream(SslStream &&);
  SslStream &operator=(SslStream &&);
  ~SslStream();

  enum class VerifyPeer { On, Off };

  static Result<SslStream> create(CSlice host, CSlice cert_file = CSlice(), VerifyPeer verify_peer = VerifyPeer::On);

  ByteFlowInterface &read_byte_flow();
  ByteFlowInterface &write_byte_flow();

  size_t flow_read(MutableSlice slice);
  size_t flow_write(Slice slice);

  explicit operator bool() const {
    return bool(impl_);
  }

 private:
  std::unique_ptr<detail::SslStreamImpl> impl_;

  SslStream(std::unique_ptr<detail::SslStreamImpl> impl);
};

}  // namespace td
