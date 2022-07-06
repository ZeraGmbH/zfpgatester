set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest)

if(${GTest_FOUND})

    enable_testing()

    add_test(NAME    ${PROJECT_NAME}-unittest
             COMMAND ${PROJECT_NAME}-unittest)

    set(TEST_SOURCES
         unittest_filehandler.cpp
     )

    add_executable(${PROJECT_NAME}-unittest
        ${TEST_SOURCES}
        )

    target_include_directories(${PROJECT_NAME}-unittest
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

    target_link_libraries(${PROJECT_NAME}-unittest
        PRIVATE
        gtest
        gtest_main
        ${PROJECT_NAME}_lib
        )

endif()
