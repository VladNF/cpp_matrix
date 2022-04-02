cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 42)
endif()

project(hw05_matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

# Build googletest
exec_program(git ARGS submodule update --init --recursive)
get_filename_component(GTEST_SOURCE ../googletest ABSOLUTE)
add_subdirectory(
    "${GTEST_SOURCE}" 
    "googletest"
)


add_executable(matrix main.cpp matrix.hpp)
add_executable(test_matrix test_matrix.cpp matrix.hpp)

set_target_properties(matrix test_matrix PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(test_matrix PRIVATE
    gtest gtest_main
)

if (MSVC)
    target_compile_options(
        matrix PRIVATE
        /W4
    )
    target_compile_options(
        test_matrix PRIVATE
        /W4
    )
else ()
    target_compile_options(
        matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        test_matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT j@vladnf.ru)

include(CPack)

enable_testing()

add_test(test_matrix test_matrix)
