#
# Enable address sanitizer
#

add_library(asan INTERFACE)
target_compile_options(asan INTERFACE -fsanitize=address -fsanitize-recover=address -fno-omit-frame-pointer)
target_link_options(asan INTERFACE -fsanitize=address)

function(enable_target_address_sanitizer target)
    target_link_libraries(${target} PUBLIC asan)
endfunction()