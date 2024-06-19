// SPDX-License-Identifier: MIT

#pragma once

#include <array>
#include <cstddef>
#include <algorithm>
#include <string_view>

#include "utils.hpp"
#include "common.hpp"

namespace pm {

template <std::size_t salt_length>
[[nodiscard]] inline auto GenerateSalt() -> std::array<char, salt_length> {
  std::array<char, salt_length> salt{};
  std::ranges::generate(salt, utils::GenerateRandomChar);
  return salt;
}

[[nodiscard]] auto HashPasswordViaSha256(std::string_view password)
    -> std::string;

template <pm::HashAlgorithm hash_algorithm>
[[nodiscard]] auto HashPassword(std::string_view password,
                                std::string_view salt) -> std::string {
  if constexpr (hash_algorithm == pm::HashAlgorithm::SHA256) {
    return HashPasswordViaSha256(std::string{password} + std::string{salt});
  }
}

}  // namespace pm
