#include "c01e02.hpp"
#include "c01e03.hpp"
#include "c01e04.hpp"
#include "c01e05.hpp"
#include "c01e06.hpp"
#include "c01e07.hpp"
#include "c01e08.hpp"

#include "gtest/gtest.h"

#include <utils/pr.hpp>
#include <utils/matrix.hpp>

using namespace a150_cci::c01;

#include <iostream>

TEST(ch01e02, revers)
{
    char str[] = "nowa";
    e02::revers(str, 4);
}

TEST(ch01e04, remove_duplicates)
{
    //TODO:
}

TEST(ch01e04, is_anagram)
{
    //TODO:
}

TEST(ch01e05, replace_space)
{
    std::string s = " mowa trawa dupa ";
    std::string const exp = "%20mowa%20trawa%20dupa%20";

    e05::replace_space(s);

    ASSERT_EQ(s, exp);

    //TODO:
}


TEST(ch01e06, rotate_left)
{
    unsigned N = 10;
    utils::matrix<uint32_t> mm(N, N);

    for (int i = 0, c = 1; i < N; ++i)
        for (int j = 0; j < N; ++j)
            mm[i][j] = c++;

    e06::rotate_right(mm);

    e06::rotate_left(mm);

    //TODO: add assertions
}


TEST(ch01e07, set_zero)
{
#if 0
int main() {

    int M, N;
    cin >> M >> N;

    matrix<int> mm(M, N);

    for (int i = 0, c = 1; i < mm.__row_size; ++i)
        for (int j = 0; j < mm.__col_size; ++j)
            mm[i][j] = c++;
    
    cin >> N;

    for (int i = 0; i < N; ++i) {
        int c, r;
        cin >> r >> c;

        mm[r][c] = 0;
    }

    cout << mm << endl;

    set_zero(mm);

    cout << mm << endl;
    
}
#endif
}

TEST(ch01e08, is_rotate)
{
    ASSERT_TRUE(e08::is_rotate("12345", "23451"));
}
