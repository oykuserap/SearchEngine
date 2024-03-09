#include "catch.hpp"
#include "AVL_Tree.h"


TEST_CASE("AVL tree of integers", "[AVL_Int]"){
    //due to the abstraction of most of the internal workings of the AVL tree the tests are primarily that it can find the elements in the tree
    AVL_Tree<int, int> tests;
    tests.insert(1,1);
    tests.insert(3,1);
    tests.insert(4,2);
    tests.insert(6,8);


    SECTION("Testing find") {
        REQUIRE(tests.search(6) == 8);
        REQUIRE(tests.search(4) == 2);
    }


}