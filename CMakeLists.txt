cmake_minimum_required(VERSION 3.2)
project(allocator)

IF($ENV{TRAVIS_BUILD_NUMBER})
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
ELSE()
    project(allocator VERSION 0.0.1)
ENDIF()

set(CMAKE_CXX_STANDARD 14)

add_executable(allocator main.cpp my_allocator.h my_forward_list.h factorial.h my_debuger.h test/test.cpp newdelete.h newdelete.cpp)

set_target_properties(allocator PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT shadow.balz@mail.ru)

include(CPack)