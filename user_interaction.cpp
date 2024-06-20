// SPDX-License-Identifier: MIT

#include "user_interaction.hpp"

#include <filesystem>
#include <print>

#include "common.hpp"
#include "user_authentication.hpp"

namespace fs = std::filesystem;

namespace {

auto inline WelcomeScreen() noexcept {
  std::println("*** welcome to uzleo password-manager system ***");
}

}  // namespace

namespace pm::ui {

auto RunApp() -> void {
  WelcomeScreen();

  if (not fs::exists(kPasswordFilePath)) {
    try {
      std::println(
          "[INFO] Currently no passwords file exists on filesystem ({})",
          kPasswordFilePath);

      auto const salt{ua::GenerateSalt<pm::kSaltLength>()};
      ua::SavePassword<pm::kDoEncryption>(
          salt, ua::HashPassword<pm::kHashAlgorithm>(
                    ua::SaltPassword(salt, ua::GetMasterPassword())));
    } catch (const std::exception& ex) {
      std::println(
          "[ERROR] Got exception while storing the master password. Exception: "
          "{}",
          ex.what());
    }
  } else {
    ua::VerifyPassword();
  }
}

}  // namespace pm::ui
