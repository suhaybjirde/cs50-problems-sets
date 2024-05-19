#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;
typedef uint16_t DOUBLEBYTE;

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("USAGE: <filename> <inputFile.wav> <outputFile.wav> <factor>");
        return 1;
    }
    
    int factor = atoi(argv[3]);

    FILE* src = fopen(argv[1], "rb");
    if (src == NULL)
    {
        printf("couldn't allocate memory");
        return 2;
    }

    FILE* dst = fopen(argv[2], "wb");
    if (dst == NULL)
    {
        printf("couldn't allocate memory");
        return 1;
    }
    
    // read the header of the .wav file
    BYTE b[44];

    int read = fread(b, 44, 1, src);
    if (read == 0)
    {
        printf("couldn't read the file!");
        return 3;
    }
    // write the header to the other .wav file
    int written = fwrite(b, 44, 1, dst);
    if (written != 1)
    {
        printf("coudn't write to the file");
        return 4;
    }
    DOUBLEBYTE c;
    while (fread(&c, sizeof(DOUBLEBYTE), 1, src) == 1)
    {
        c = c * factor;
        fwrite(&c, sizeof(DOUBLEBYTE), 1, dst);
    }

    fclose(src);
    fclose(dst);
}