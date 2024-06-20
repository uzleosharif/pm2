
// SPDX-License-Identifier: MIT

#include "user_authentication.hpp"

#include <print>
#include <iostream>
#include <string>

#include <termios.h>
#include <unistd.h>

namespace {

auto inline DisableTerminalEcho() noexcept {
  termios settings{};
  tcgetattr(STDIN_FILENO, &settings);
  settings.c_lflag and_eq ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

auto inline EnableTerminalEcho() noexcept {
  termios settings{};
  tcgetattr(STDIN_FILENO, &settings);
  settings.c_lflag or_eq ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

}  // namespace

namespace pm::ua {

auto GetMasterPassword() -> std::string {
  std::string user_password{};

  DisableTerminalEcho();
  std::println("Please set up a master password: ");
  std::getline(std::cin, user_password);
  EnableTerminalEcho();

  return user_password;
}

auto SaltPassword(std::span<char const> salt,
                  std::string_view user_password) -> std::string {
  std::string result{};

  result.reserve(salt.size() + user_password.size());
  rng::copy(user_password, std::back_inserter(result));
  rng::copy(salt, std::back_inserter(result));

  return result;
}

auto VerifyPassword() -> bool {
  auto user_password{GetMasterPassword()};

  // TODO:
  // recover stored-salt and stored-hash
  // entered_hash = HashPassword(stored_salt, user_password)
  // entered_hash == stored_hash??

  return true;
}

}  // namespace pm::ua
