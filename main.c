#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <file> <array_name>\n", argv[0]);
        return 1;
    }

    // Read file
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        fprintf(stderr, "Failed to open file %s for reading\n", argv[1]);
        return 1;
    }

    fseek(input, 0, SEEK_END);
    size_t file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *buff = malloc(file_size);
    if (buff == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    size_t result = fread(buff, file_size, 1, input);
    if (result <= 0)
    {
        fprintf(stderr, "Failed to read file. Error: %s\n", strerror(errno));
        return 1;
    }
    fclose(input);

    // Write to stdout
    int comma = 0;

    fprintf(stdout, "#include <stddef.h>\n\n"); // Required for 'size_t' type
    fprintf(stdout, "const size_t %s_length = %zu;\n\n", argv[2], file_size);
    fprintf(stdout, "const char %s[%zu] = {", argv[2], file_size);
    for (size_t i = 0; i < file_size; ++i)
    {
        if (comma)
            fprintf(stdout, ", ");
        else
            comma = 1;
        if ((i % 12) == 0)
            fprintf(stdout, "\n\t");
        fprintf(stdout, "0x%.2x", buff[i] & 0xff);
    }
    fprintf(stdout, "\n};\n\n");

    return 0;
}
