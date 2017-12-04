/*
 *  This file is part of props
 *  Copyright (c) 2017 props's authors
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_TEST_MODULE props
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "prop.h"

BOOST_AUTO_TEST_SUITE(props)
    BOOST_AUTO_TEST_CASE(parseG1) {
        char s1[] = "~P /\\ Q";
        Expression *tmp = nullptr;
        parse_expression(&tmp, s1);
        BOOST_CHECK_EQUAL(tmp->type, AND);
        BOOST_CHECK_EQUAL(tmp->left->type, NOT);
        BOOST_CHECK_EQUAL(tmp->right->value, 'Q');
        BOOST_CHECK_EQUAL(tmp->left->value, 0);
        BOOST_CHECK_EQUAL(tmp->left->right->value, 'P');
    }
    BOOST_AUTO_TEST_CASE(parseE1) {
        char s1[] = "~A /\\";
        Expression *tmp = nullptr;
        parse_expression(&tmp, s1);
        BOOST_CHECK(tmp == nullptr);
    }
BOOST_AUTO_TEST_SUITE_END()

