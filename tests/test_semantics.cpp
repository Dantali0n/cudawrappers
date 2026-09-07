#include <array>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstring>
#include <iostream>
#include <string>

#include <cudawrappers/cu.hpp>

/**
 * This file tests class semantics such as invoking copy and move constructors.
 * It should be compiled and linked with address-sanitizer using:
 *  `-fsanitize=address`
 */

TEST_CASE("Test cu::Context", "[copy constructor]") {
  int iterations = 4;
  cu::init();
  cu::Device device(0);
  std::vector<cu::Context> contexts;

  SECTION("Test vector emplace out-of-scope") {
    for (size_t i = 0; i < iterations; ++i) {
      contexts.emplace_back(CU_CTX_SCHED_YIELD, device);
      contexts.back().setCurrent();
    }

    for (size_t i = 0; i < iterations; ++i) {
      std::cout << contexts.at(0).getCurrent() << std::endl;
    }
  }

  SECTION("Test launchHostFunc") {

  }
}
