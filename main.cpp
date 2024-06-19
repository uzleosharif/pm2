
// SPDX-License-Identifier: MIT

#include <print>
#include <cstddef>

#include "user_authentication.hpp"
#include "common.hpp"

namespace {

std::size_t constexpr kSaltLength{16};
auto constexpr kHashAlgorithm{pm::HashAlgorithm::SHA256};

}  // namespace

auto main() -> int {
  auto const master_password{"123"};
  auto const salt{pm::GenerateSalt<kSaltLength>()};

  auto hashed_password{pm::HashPassword<kHashAlgorithm>(
      master_password, std::string{salt.data(), salt.size()})};
  std::println("{}", hashed_password);
}
