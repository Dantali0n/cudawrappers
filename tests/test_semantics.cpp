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
  cu::init();
  cu::Device device(0);
  cu::Context context(CU_CTX_SCHED_BLOCKING_SYNC, device);

  SECTION("Test vector emplace out-of-scope") {
    // const size_t size = 1024;
    // cu::DeviceMemory mem = stream.memAllocAsync(size);
    // {
    //
    // }
    // CHECK(mem.size() == size);
    // CHECK_NOTHROW(stream.memFreeAsync(mem));
    // CHECK_NOTHROW(stream.synchronize());
  }

  SECTION("Test launchHostFunc") {

  }
}
