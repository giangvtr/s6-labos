//
// Created by giangvu on 5/27/25.
//

#include "libfatutils.h"

#include <string.h>

unsigned long int offset_to_cluster (unsigned long int offset)
{
    if (offset >= CLUSTER_OFFSET) {
        unsigned long int cluster = (offset - CLUSTER_OFFSET)/CLUSTER_SIZE;
        return cluster +1;
    }
    fprintf(stderr, "Offset too small: %lu \n", offset);
    return -1;
}

void save_cluster(const char *fs, unsigned long cluster, const char *output) {

    //1. Calculate the byte offset of the requested cluster
    unsigned long int offset_byte = (cluster)*CLUSTER_SIZE + CLUSTER_OFFSET;

    //2. Open the file image, seek to cluster's start and read CLUSTER_SIZE byte
    FILE *fin = fopen(fs, "rb");
    if (fin == NULL) {
        fprintf(stderr, "Error opening image file %s\n", fs);
        exit(EXIT_FAILURE);
    }

    // 3. Seek to the start of the cluster
    if (fseek(fin, offset_byte, SEEK_SET) != 0) {
        fprintf(stderr, "Error seeking to offset %lu in image file\n", offset_byte);
        fclose(fin);
        exit(EXIT_FAILURE);
    }

    // 4. Allocate buffer and read the cluster data
    unsigned char buffer[CLUSTER_SIZE];
    size_t read_bytes = fread(buffer, 1, CLUSTER_SIZE, fin);
    if (read_bytes != CLUSTER_SIZE) {
        fprintf(stderr, "Error reading cluster data from image file\n");
        fclose(fin);
        exit(EXIT_FAILURE);
    }
    fclose(fin);

    // 5. Open the output file for writing
    FILE *fout = fopen(output, "wb");
    if (fout == NULL) {
        fprintf(stderr, "Error opening output file %s\n", output);
        exit(EXIT_FAILURE);
    }

    // 6. Write the cluster data to the output file
    size_t written_bytes = fwrite(buffer, 1, CLUSTER_SIZE, fout);
    if (written_bytes != CLUSTER_SIZE) {
        fprintf(stderr, "Error writing cluster data to output file\n");
    }
    fclose(fout);
}


