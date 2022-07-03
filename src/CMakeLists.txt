set(CMAKE_INCLUDE_CURRENT_DIR ON)

#sum up project Files
set(SOURCES
    cmdhandlerzfpgatest.cpp
    cmdparserzfpgatest.cpp
    timer.cpp
    filehandler.cpp
)

set(HEADERS
    cmdhandlerzfpgatest.h
    cmdparserzfpgatest.h
    globals.h
    timer.h
    filehandler.h
)

add_library(${PROJECT_NAME}_lib STATIC
            ${SOURCES}
            ${HEADERS}
            )

#set target Version
set_target_properties(simplecmdiobase PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(simplecmdiobase PROPERTIES SOVERSION ${ZFPGATESTER_VERSION_MAJOR})

#link dependencies
target_link_libraries(${PROJECT_NAME}_lib
    PUBLIC
    Qt5::Core
    Qt5::Network
    simplecmdiobase
)

# announce headers - target perspective
target_include_directories(${PROJECT_NAME}_lib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}_lib>
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

#create executable
add_executable(${PROJECT_NAME} main.cpp)

#link dependencies
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_NAME}_lib
)

#install executable to bin
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

