#!/bin/bash

# URL of the file
URL="https://www.cjoint.com/doc/23_03/MCBn305uIy7_sysmic-org-access.log.gz"

# Download, decompress, filter, extract IPs, count occurrences, and save to file
wget -O - "$URL" | zcat | egrep -o '^\d+\.\d+\.\d+\.\d+\b|^([a-fA-F0-9]+\:){7}[a-fA-F0-9]+\b' | sort | uniq -c > frequency.log

# Sort numerically and output the most frequent IPs
sort -nr frequency.log | awk '{print $2}' > result.log

