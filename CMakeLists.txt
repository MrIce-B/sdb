cmake_minimum_required(VERSION 3.19)

project("sdb" LANGUAGES CXX) 

set(CMAKE_BUILD_TYPE "Debug")

find_package(PkgConfig REQUIRED)

pkg_check_modules(libedit REQUIRED IMPORTED_TARGET libedit)

include(CTest)

add_subdirectory("src")
add_subdirectory("tools")

if(BUILD_TESTING)
    find_package(Catch2 CONFIG REQUIRED)
    add_subdirectory("test")
endif()

# if install libedit error , you can try the code :
# sudo apt update
# sudo apt install libncurses5-dev libncursesw5-dev
target_link_libraries(sdb PRIVATE sdb::libsdb PkgConfig::libedit)