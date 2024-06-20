
// SPDX-License-Identifier: MIT

#include <print>

#include "user_authentication.hpp"
#include "common.hpp"

auto main() -> int {
  try {
    auto const salt{pm::GenerateSalt<pm::kSaltLength>()};
    pm::SavePassword<pm::kDoEncryption>(
        salt, pm::HashPassword<pm::kHashAlgorithm>(
                  pm::SaltPassword(salt, pm::GetMasterPassword())));
  } catch (const std::exception& ex) {
    std::println(
        "[ERROR] Got exception while storing the master password. Exception: "
        "{}",
        ex.what());
  }
}
