#
# Enable address sanitizer
#

add_library(asan INTERFACE)
target_compile_options(asan INTERFACE -fsanitize=address -fsanitize-recover=address -fno-omit-frame-pointer -g -O0)
target_link_options(asan INTERFACE -fsanitize=address)

function(enable_target_address_sanitizer target)
    target_link_libraries(${target} PUBLIC asan)
endfunction()

SET(ADDRESS_SANITIZER_ASAN_ENV  "ASAN_OPTIONS=" CACHE INTERNAL "ADDRESS_SANITIZER_ASAN_ENV")
SET(ADDRESS_SANITIZER_LEAK_ENV_OPTS  "detect_leaks=0" CACHE INTERNAL "ADDRESS_SANITIZER_LEAK_ENV_OPTS")
SET(ADDRESS_SANITIZER_CUDA_ENV_OPTS  "protect_shadow_gap=0:replace_intrin=0:detect_stack_use_after_return=0" CACHE INTERNAL "ADDRESS_SANITIZER_CUDA_ENV_OPTS")