cmake_minimum_required(VERSION 3.1)

#set project name and language
project(zfpgatester LANGUAGES CXX)

#Automoc and RCC ON. Needed in QT projects
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#C++ 11 Flag
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set project Version
set(ZFPGATESTER_VERSION_MAJOR "0")
set(ZFPGATESTER_VERSION_MINOR "1")
set(ZFPGATESTER_VERSION_PATCH "0")

set(PROJECT_VERSION "${ZFPGATESTER_VERSION_MAJOR}.${ZFPGATESTER_VERSION_MINOR}.${ZFPGATESTER_VERSION_PATCH}")

#Adding cmake functions like feature_summary()
include(FeatureSummary)
include(GNUInstallDirs)

#Find dependecies
find_package(Qt5 COMPONENTS Core Network CONFIG REQUIRED)
find_package(simplecmdiobase REQUIRED)

#sum up project Files 
set(SOURCES
    cmdhandlerzfpgatest.cpp
    cmdparserzfpgatest.cpp
    main.cpp
)

set(HEADERS
    cmdhandlerzfpgatest.h
    cmdparserzfpgatest.h
    globals.h
)

#create executable
add_executable(zfpgatester
    ${SOURCES}
    ${HEADERS}
)

#link dependencies
target_link_libraries(zfpgatester
    PUBLIC
    Qt5::Core
    Qt5::Network
    simplecmdiobase
)


#install executable to bin
install(TARGETS zfpgatester
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

# spawn out some info on configuration
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)






