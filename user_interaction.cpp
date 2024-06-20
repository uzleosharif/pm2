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

namespace pm {

auto RunApp() -> void {
  WelcomeScreen();

  if (not fs::exists(kPasswordFilePath)) {
    try {
      std::println(
          "[INFO] Currently no passwords file exists on filesystem ({})",
          kPasswordFilePath);

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
  } else {
    //
  }
}

}  // namespace pm
