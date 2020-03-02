#include <cstdio>

int main()
{
    FILE* file = fopen("test.vox", "w");

    for (int i = 0; i < 616; i++)
    {
        fprintf(file, "%i\n", i);
    }

    fclose(file);

    return 0;
}