//
// Created by giangvu on 5/27/25.
//

#ifndef LIBFATUTILS_H
#define LIBFATUTILS_H

#include <stdio.h>
#include <stdlib.h>

#define CLUSTER_OFFSET 0xC000   //Where the cluster begin (48 KiB)
#define CLUSTER_SIZE 16384     //Size of a cluster (16 KiB - Octet)
//Cluster size = Sectors per cluster * sector size = 32 * 512 = 16384


/**
 * @brief Converts a file offset to its corresponding FAT cluster number.
 *
 * This function computes the FAT cluster number that contains the given byte offset.
 * The calculation assumes that clusters start at CLUSTER_OFFSET in the filesystem,
 * and each cluster has a size of CLUSTER_SIZE bytes. In FAT filesystems, cluster
 * numbers start at 2 (clusters 0 and 1 are reserved).
 *
 * @param offset The byte offset within the filesystem image.
 * @return The corresponding cluster number (starting from 2), or (unsigned long int)-1 if the offset is before the first cluster.
 *
 * @note If the offset is smaller than CLUSTER_OFFSET, the function prints an error message to stderr and returns (unsigned long int)-1.
 */
unsigned long int offset_to_cluster(unsigned long int offset);

/**
 * @brief Extracts a specific cluster from a FAT filesystem image and saves it to an output file.
 *
 * @param fs      Path to the FAT filesystem image file to read from.
 * @param cluster The cluster number to extract (should be >= 2, as clusters 0 and 1 are reserved in FAT).
 * @param output  Path to the output file where the cluster's contents will be saved.
 *
 * @note The function should:
 *   - Calculate the byte offset of the requested cluster in the image using CLUSTER_OFFSET and CLUSTER_SIZE.
 *   - Open the image file, seek to the cluster's start, and read CLUSTER_SIZE bytes.
 *   - Write those bytes to the output file.
 *   - Handle errors (e.g., file not found, read/write failure, invalid cluster number) gracefully.
 */
void save_cluster(const char *fs, unsigned long cluster, const char *output);


#endif //LIBFATUTILS_H
