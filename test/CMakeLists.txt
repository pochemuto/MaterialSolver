project(tests)

foreach(cpp_file combinations polynomial compass)

    add_executable(${cpp_file} ${cpp_file}.cpp common.h)
    add_test(NAME ${cpp_file} COMMAND ${cpp_file})

endforeach()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
                  DEPENDS combinations polynomial compass)