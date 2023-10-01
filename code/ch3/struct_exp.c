struct rec
{
    int i;
    int j;
    int a[2];
    int *p;
};

void init_rec(struct rec *recp)
{
    recp->i = 1;
    recp->j = 2;
    int a2[2] = {3, 4};
    // 直接将数组的值复制给结构体的成员
    for (int k = 0; k < 2; k++)
    {
        recp->a[k] = a2[k];
    }
    int c = 11;
    recp->p = &c;
}