//
// Created by giangvu on 5/27/25.
//

#include "libfatutils.h"


/**
 * @brief Main function for the saveclust program.
 *
 * This program extracts one or more clusters from a FAT filesystem image and saves each
 * cluster to a separate output file. The output files are named using the provided prefix
 * followed by a dot and the cluster number (e.g., "prefix.5" for cluster 5).
 *
 * @param argc Argument count. Must be at least 4: program name, image file, prefix, and at least one cluster number.
 * @param argv Argument vector. Usage: saveclust <image_file> <prefix> <cluster1> [<cluster2> ...]
 *   - argv[1]: Path to the FAT filesystem image file.
 *   - argv[2]: Prefix for output files.
 *   - argv[3...]: List of cluster numbers to extract (as strings).
 *
 * @return 0 on success, non-zero on error.
 *
 * @note For each cluster number:
 *   - Construct an output filename as "<prefix>.<cluster_number>".
 *   - Call save_cluster(image_file, cluster_number, output_filename).
 *   - Handle errors gracefully (e.g., invalid cluster number, file I/O errors).
 *   - Print informative messages if desired.
 */
int main(int argc, char* argv[]) {

    if (argc < 4) {
        fprintf(stderr, "Usage: saveclust <file> <prefix> <list of clusters>\n");
        exit(EXIT_FAILURE);
    }
    char* file_image=argv[1];
    char* prefix=argv[2];
    for (int i = 3; i < argc; i++) {
        // Convert cluster number from string to unsigned long
        unsigned long cluster = strtoul(argv[i], NULL, 0);

        // Allocate buffer for output filename
        char output_file[256];
        snprintf(output_file, sizeof(output_file), "%s.%d", prefix, i);
        save_cluster(file_image, cluster, output_file);
    }
}
