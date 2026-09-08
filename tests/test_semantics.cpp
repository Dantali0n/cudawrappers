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

struct ContextCopyAndMove {
  ContextCopyAndMove(cu::Context &ctx) : ctx(ctx) {};
  cu::Context ctx;
};

struct ProcessStepGPUData {
  ProcessStepGPUData(cu::Context &context) : context(context) {}
  cu::Context &context;
};

void __attribute__ ((noinline)) push(
  unsigned int device_ordinal, std::vector<cu::Context> &contexts
) {
  auto dev = cu::Device(device_ordinal);
  contexts.emplace_back(CU_CTX_SCHED_YIELD, dev);
}

TEST_CASE("Test cu::Context", "[copy constructor]") {
  int iterations = 4;
  cu::init();
  std::vector<cu::Device> devices;

  for (unsigned int i = 0; i < cu::Device::getCount(); i++) {
    devices.emplace_back(i);
  }
  std::vector<cu::Context> contexts;

  std::cout << "Device count: " << devices.size() << std::endl;
  for (auto& dev : devices) {
    std::cout << "Device uuid: " << dev.getUuid() << std::endl;
  }

  SECTION("Test cu::Context vector emplace") {
    for (size_t i = 0; i < iterations; ++i) {
      contexts.emplace_back(CU_CTX_SCHED_YIELD, devices[i % devices.size()]);
      contexts.back().setCurrent();
    }

    for (size_t i = 0; i < iterations; ++i) {
      contexts.at(i).setCurrent();
      std::cout << "copy emplace: " << contexts.at(i).getCurrent() << std::endl;
    }
  }

  SECTION("Test cu::Context copy constructor") {
    for (size_t i = 0; i < iterations; ++i) {
      contexts.emplace_back(CU_CTX_SCHED_YIELD, devices[i % devices.size()]);
      contexts.back().setCurrent();
    }
    {
      cu::Context ctx = cu::Context(contexts.at(0));
    }
    std::cout << "copy construct: " << contexts.at(0) << std::endl;
  }

  SECTION("Test cu::Context copy and move struct") {
    std::vector<ContextCopyAndMove> container;
    for (size_t i = 0; i < iterations; ++i) {
      contexts.emplace_back(CU_CTX_SCHED_YIELD, devices[i % devices.size()]);
      contexts.back().setCurrent();
      container.emplace_back(contexts.back());
    }
    for (size_t i = 0; i < iterations; ++i) {
      std::cout << "copy and move: " << container.at(i).ctx << std::endl;
    }
  }

  SECTION("Test cu::Context copy and move struct") {

    for (size_t i = 0; i < iterations; ++i) {
      contexts.emplace_back(CU_CTX_SCHED_YIELD, devices[i % devices.size()]);
    }
    for (size_t i = 0; i < iterations; ++i) {
      ProcessStepGPUData container(contexts.at(i));
      std::cout << contexts.at(i).getDevice().getUuid() << std::endl;
    }
  }

  SECTION("Test cu::Context dangling device") {
    for (size_t i = 0; i < iterations; ++i) {
      push(i % cu::Device::getCount(), contexts);
    }

    // Should return 0,1,2 etc
    for (size_t i = 0; i < iterations; ++i) {
      std::cout << contexts.at(i).getDevice().getUuid() << std::endl;
    }
  }
}

