long cmovdiff(long x, long y)
{
    long rval = y - x;
    long eval = x - y;
    long ntest = x >= y;
    /* Line blow requires single instruction; */
    if (ntest)
        rval = eval;
    return rval;
}