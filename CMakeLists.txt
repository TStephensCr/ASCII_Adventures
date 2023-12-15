cmake_minimum_required(VERSION 3.10)
project(
  project_00819
  VERSION 1.0.0
  DESCRIPTION "cpp game project"
  LANGUAGES C CXX)

# Find and include the ncurses library
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_executable(game src/main.cpp ${SRC_FILES})

# Link against the ncurses library
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(game ${CURSES_LIBRARIES})
