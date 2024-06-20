
// SPDX-License-Identifier: MIT

#include "user_authentication.hpp"

namespace pm {

auto GetMasterPassword() -> std::string { return ""; }

auto SaltPassword(std::span<char const> salt,
                  std::string_view user_password) -> std::string {
  std::string result{};
  result.reserve(salt.size() + user_password.size());
  rng::copy(user_password, std::back_inserter(result));
  rng::copy(salt, std::back_inserter(result));
  return result;
}

}  // namespace pm
