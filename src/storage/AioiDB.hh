#pragma once

struct AioiDB
{
    static float get(int att, int def)
    {
        if(att > 17 || def > 17 || att <= 0 || def <= 0)
            return 1;
        constexpr float local_db[17][17] =
        { /** 1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17 */
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0, 1, 1, 0.5 },              /**< 1 */
            { 1, 0.5, 0.5, 1, 2, 2, 1, 1, 1, 1, 1, 2, 0.5, 1, 0.5, 1, 2 },          /**< 2 */
            { 1, 2, 0.5, 1, 0.5, 1, 1, 1, 2, 1, 1, 1, 2, 1, 0.5, 1, 1 },            /**< 3 */
            { 1, 1, 2, 0.5, 0.5, 1, 1, 1, 0.5, 2, 1, 1, 1, 1, 0.5, 1, 1 },          /**< 4 */
            { 1, 0.5, 2, 1, 0.5, 1, 1, 0.5, 2, 0.5, 1, 0.5, 2, 1, 0.5, 1, 0.5 },    /**< 5 */
            { 1, 0.5, 0.5, 1, 2, 0.5, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 0.5 },          /**< 6 */
            { 2, 1, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 0.5, 0.5, 2, 0, 1, 2, 2 },          /**< 7 */
            { 1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 1, 0 },          /**< 8 */
            { 1, 2, 1, 2, 0.5, 1, 1, 2, 1, 0, 1, 0.5, 2, 1, 1, 1, 2 },              /**< 9 */
            { 1, 1, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 0.5 },            /**< 10 */
            { 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0.5, 1, 1, 1, 1, 0, 0.5 },              /**< 11 */
            { 1, 0.5, 1, 1, 2, 1, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 1, 2, 0.5 },      /**< 12 */
            { 1, 2, 1, 1, 1, 2, 0.5, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 0.5 },            /**< 13 */
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 0.5 },              /**< 14 */
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0.5 },                /**< 15 */
            { 1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 0.5 },            /**< 16 */
            { 1, 0.5, 0.5, 0.5, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0.5 }           /**< 17 */
        };
        return local_db[att - 1][def - 1];
    }
};
