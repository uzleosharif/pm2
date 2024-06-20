// SPDX-License-Identifier: MIT

#pragma once

#include <array>
#include <cstddef>
#include <algorithm>
#include <string_view>
#include <ranges>
#include <vector>
#include <fstream>
#include <ios>
#include <span>

#include "common.hpp"

#include <utils.hpp>
#include <crypto/sha.hpp>

namespace rng = std::ranges;

namespace pm {

template <std::size_t salt_length>
[[nodiscard]] auto GenerateSalt() -> std::array<char, salt_length> {
  std::array<char, salt_length> salt{};
  rng::generate(salt, utils::GenerateRandomChar);
  return salt;
}

[[nodiscard]] auto GetMasterPassword() -> std::string;

[[nodiscard]] auto SaltPassword(std::span<char const> salt,
                                std::string_view user_password) -> std::string;

template <HashAlgorithm hash_algorithm>
[[nodiscard]] auto HashPassword(std::string_view user_password)
    -> std::vector<std::byte> {
  if constexpr (hash_algorithm == HashAlgorithm::Sha256) {
    return crypto::Sha256(user_password) | rng::to<std::vector>();
  }
}

template <bool kEncrypt>
auto SavePassword(std::span<char const> salt,
                  std::vector<std::byte>&& password) {
  if constexpr (kEncrypt) {
    // TODO(USH): Encryption/Decryption support
    // password = crypto::Encrypt(password); ...
    // via crypto library
  }

  std::ofstream file_stream{kPasswordFilePath | rng::to<std::string>(),
                            std::ios::binary};
  if (not file_stream.is_open()) {
    throw std::ios_base::failure{"Unable to open password file."};
  }
  rng::copy(salt, std::ostreambuf_iterator<char>(file_stream));
  rng::copy(password | std::views::transform([](std::byte elem) -> char {
              return static_cast<char>(elem);
            }),
            std::ostreambuf_iterator<char>(file_stream));
}

}  // namespace pm
