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

