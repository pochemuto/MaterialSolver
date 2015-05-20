project(tests)

set(TEST_SOURCES combinations polynomial compass exhaustive)
set(COMMONS ../struct/Result.cpp common.h)

foreach(cpp_file ${TEST_SOURCES})

    add_executable(${cpp_file} ${cpp_file}.cpp ${COMMONS})
    add_test(NAME ${cpp_file} COMMAND ${cpp_file})

endforeach()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
                  DEPENDS ${TEST_SOURCES})