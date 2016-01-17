//
// Created by dybisz on 20.12.15.
//

#include <gtest/gtest.h>
#include <language/interval.h>
#include <language/alphabet.h>


using namespace std;

TEST(AlphabetTest, Alphabet_Init) {
    Interval i1(0, 1);
    Interval i2(1, 2);
    Interval i3(2, 3);

    Alphabet* a = new Alphabet(4);

    // == operator for intervals is ofc overloaded
    EXPECT_EQ(i1, ((*a)(0)));
    EXPECT_EQ(i2, ((*a)(1)));
    EXPECT_EQ(i3, ((*a)(2)));

    delete a;
}

TEST(AlphabetTest, Equality_Check) {
    Alphabet* a1 = new Alphabet(5);
    Alphabet* a2 = new Alphabet(5);

    EXPECT_EQ((*a1),(*a2));

    delete a1;
    delete a2;
}

TEST(AlphabetTest, Access_Symbol) {
    Symbol s1(1);
    Symbol s2(2);
    Symbol s3(3);

    Alphabet* a = new Alphabet(3);

    // Via integer check
    EXPECT_EQ(((*a)[0]), 1);
    EXPECT_EQ(((*a)[1]), 2);
    EXPECT_EQ(((*a)[2]), 3);

    // Via symbols check
    EXPECT_EQ(((*a)[0]), s1);
    EXPECT_EQ(((*a)[1]), s2);
    EXPECT_EQ(((*a)[2]), s3);

    delete a;
}
