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
