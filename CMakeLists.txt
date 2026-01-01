cmake_minimum_required(VERSION 3.1)

project(zfpgatester LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(ZFPGATESTER_VERSION_MAJOR "0")
set(ZFPGATESTER_VERSION_MINOR "1")
set(ZFPGATESTER_VERSION_PATCH "0")

set(PROJECT_VERSION "${ZFPGATESTER_VERSION_MAJOR}.${ZFPGATESTER_VERSION_MINOR}.${ZFPGATESTER_VERSION_PATCH}")

include(FeatureSummary)
include(GNUInstallDirs)

set(QT_MAJOR_VER "5" CACHE STRING "Qt major version")
set(QTX "Qt${QT_MAJOR_VER}")

find_package(${QTX} COMPONENTS Core Network Test CONFIG REQUIRED)
find_package(simplecmdiobase REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
