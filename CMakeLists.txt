#
#  This file is part of props
#  Copyright (c) 2017 props's authors
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.8)
project(props)

find_package(BISON)
find_package(FLEX)

FLEX_TARGET(Scanner lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/lexer.c
    DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/lexer.h)
BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_SOURCE_DIR}/parser.c
    DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/parser.h)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_library(props_lib prop.h expression.h)
target_compile_features(props_lib PRIVATE cxx_std_11)
target_link_libraries(props_lib PUBLIC "fl")
target_sources(props_lib
    PRIVATE
      ${BISON_Parser_OUTPUTS}
      ${FLEX_Scanner_OUTPUTS}
      prop.cpp
      expression.c)

add_executable(props main.cpp)
target_compile_features(props PRIVATE cxx_std_11)
target_link_libraries(props props_lib)

enable_testing()
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(props_test test.cpp ${SOURCE_FILES})
target_link_libraries(props_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} props_lib)
target_compile_features(props_test PRIVATE cxx_std_11)
add_test(props_test props_test)
