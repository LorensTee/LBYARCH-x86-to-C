cmake_minimum_required(VERSION 3.16)
project(dot_product_kernel C ASM_NASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG   "-O0 -g")
set(CMAKE_C_FLAGS_RELEASE "-O2")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

add_executable(dot_product_kernel
    src/main.c
    src/kernel_c.c
    src/dot_product_asm.asm
)

target_link_libraries(dot_product_kernel m)
