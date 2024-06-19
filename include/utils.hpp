// SPDX-License-Identifier: MIT

#pragma once

#include <random>
#include <fstream>
#include <stdexcept>
#include <cstddef>

#include <nlohmann/json.hpp>

namespace utils {

template <class T>
concept Integral = std::is_integral_v<T> and (sizeof(T) > 1);

inline auto LoadConfig(std::string_view config_file_path) -> nlohmann::json {
  std::ifstream config_file_stream{std::string{config_file_path}};
  if (not config_file_stream.is_open()) {
    throw std::runtime_error{
        std::format("Config file {} not found.", config_file_path)};
  }

  auto config_json = nlohmann::json::parse(config_file_stream);
  return config_json;
}

inline auto GenerateRandomChar() -> char {
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> dis{32, 126};
  return static_cast<char>(dis(gen));
}

auto SwapEndianness(Integral auto value) -> decltype(value) {
  using T = decltype(value);
  T result{0};
  for (std::size_t i{0}; i < sizeof(T); ++i) {
    result <<= 8;
    result |= (value & 0xff);
    value >>= 8;
  }
  return result;
}

}  // namespace utils
