#include <bits/stdc++.h>
using namespace std;
int main()
{
    int m = 0, m1 = 0, m2 = 0, p, count = 0, i;
    printf("enter the memory capacity:");
    scanf("%d", &m);
    printf("enter the number of processess:");
    scanf("%d", &p);
    for (i = 0; i < p; i++)
    {
        printf("\nenter memory req for proces %d:", i + 1);
        scanf("%d", &m1);
        count = count + m1;
        if (m1 <= m)
        {
            if (count == m)
                printf("there is no further memory remaining:");
            printf("the memory alocated for process %d is:%d", i + 1, m1);
            m2 = m - m1;
            printf("\nremainig memory is:%d", m2);
            m = m2;
        }
        else
        {
            printf("\nmemory is not allocated for process %d", i + 1);
        }
        printf("\nexternal fragmentation for this processs is %d:", m2);
    }
}
