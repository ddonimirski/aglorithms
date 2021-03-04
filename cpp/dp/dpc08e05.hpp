#if !defined DP_CH08_E05
#define  DP_CH08_E05

namespace dp::ch08::e05
{
// Given an empty plot of size 2 x n. We want to place tiles
// such that the entire plot is covered. Each tile is of size 2 x 1
// and can be placed either horizontaly or verticaly. 
//
//  1  2  3  4  5
// ----------------      ----------------
// |  |  |  |  |  |      |  |     |  |  |
// ----------------  --> |  |-----|  |  |
// |  |  |  |  |  |      |  |     |  |  |
// ----------------      ----------------
//
// Write function that accept n as input and return total number of
// ways in which we can place the tiles (without breaking any tiles)
//

    int countWays(int n)
    {
        if (n <= 0) return 0;
        if (n == 1) return 1;
        if (n == 2) return 2;
        return countWays(n-1) + countWays(n-2);
    }

//
//  1  2  3  4         1  2  3  4        1  2  3  4        1  2  3  4
// -------------      -------------     -------------     -------------
// |  |  |  |  |      |  |     |  |     |  |  |  |  |     |     |  |  |
// -------------  --> |  |-----|  | --> |  |  |  |  | --> |-----|  |  | 
// |  |  |  |  |      |  |     |  |     |  |  |  |  |     |     |  |  |
// -------------      -------------     -------------     -------------
// |  |  |  |  |      |     |     |     |     |     |     |     |     |
// -------------      -------------     -------------     -------------
//
    int countWays3(int n)
    {
        if (n <= 1 || n%2 == 1) return 0;
        if (n == 2) return 3;
        if (n == 4) return 2 * countWays(4); 
        return countWays3(n - 2) + countWays3(n - 4);
    }
}

#endif // DP_CH08_E05
