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

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        expression.c
        expression.h
        prop.cpp
        prop.h
        lexer.c
        parser.c)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_SOURCE_DIR}/parser.c)
FLEX_TARGET(Scanner lexer.l  ${CMAKE_CURRENT_SOURCE_DIR}/lexer.c)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(props main.cpp ${SOURCE_FILES} ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS})
target_link_libraries(props "fl")

enable_testing()
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(props_test test.cpp ${SOURCE_FILES})
target_link_libraries(props_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(props_test props_test)
