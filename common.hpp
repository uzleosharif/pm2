// SPDX-License-Identifier: MIT

#pragma once

#include <string_view>

namespace pm {

enum class HashAlgorithm { Sha256 };

auto constexpr kSaltLength{16U};
auto constexpr kHashAlgorithm{HashAlgorithm::Sha256};
auto constexpr kDoEncryption{false};
std::string_view constexpr kPasswordFilePath{"/tmp/passwords.bin"};

}  // namespace pm
