cmake_minimum_required(VERSION 3.1)

#set project name and language
project(zfpgatester LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Automoc and RCC ON. Needed in QT projects
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#C++ 14 Flag
set(CMAKE_CXX_STANDARD 14)
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
find_package(Qt5 COMPONENTS Core Network Test CONFIG REQUIRED)
find_package(simplecmdiobase REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()

# spawn out some info on configuration
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)






