set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    cmdhandlerzfpgatest.cpp
    cmdparserzfpgatest.cpp
    timer.cpp
    filewrapper.cpp
    dataformatting.cpp
)

set(HEADERS
    cmdhandlerzfpgatest.h
    cmdparserzfpgatest.h
    globals.h
    timer.h
    filewrapper.h
    dataformatting.h
)

add_library(${PROJECT_NAME}_lib STATIC
    ${SOURCES}
    ${HEADERS}
)

set_target_properties(${PROJECT_NAME}_lib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME}_lib PROPERTIES SOVERSION ${ZFPGATESTER_VERSION_MAJOR})

target_link_libraries(${PROJECT_NAME}_lib
    PUBLIC
    ${QTX}::Core
    ${QTX}::Network
    simplecmdiobase
)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}_lib>
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_NAME}_lib
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
