#include <stdio.h>
#include "vox_enum.h"

int main(int argc, char* argv[])
{
    FILE*  f = fopen("e.vox", "wb");

    fputc(VOX_ACCESS, f);
    fputc(VOX_GRANTED, f);

    fclose(f);

    return 0;
}