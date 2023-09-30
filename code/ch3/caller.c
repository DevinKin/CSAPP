long Q(long x)
{
    return x;
}
long P(long x, long y)
{
    long u = Q(x);
    long v = Q(y);
    return u + v;
}