# Boot Sector Structure (FAT12/FAT16)

### Endianness Reminder
- **Little Endian**: When reading bytes `00 02`, it means `0x0200`.

---

## Boot Sector Layout for FAT12

| Bytes     | Content Description                                                                 |
|-----------|--------------------------------------------------------------------------------------|
| 0–2       | Jump to bootstrap                                                                    |
| 3–10      | OEM name/version (Original Equipment Manufacturer)                                  |
| 11–12     | Number of bytes per sector                                                           |
| 13        | Number of sectors per cluster                                                        |
| 14–15     | Number of reserved sectors                                                           |
|           | ➤ FAT12 and FAT16 use 1. FAT32 uses 32                                               |
| 16        | Number of FAT copies                                                                 |
| 17–18     | Number of root directory entries (each entry takes 32 bytes)                         |
| 19–20     | Total number of sectors in the filesystem                                            |
| 21        | Media descriptor type (e.g., F0 = 1.44 MB floppy, F8 = hard disk)                    |
| 22–23     | Number of sectors per FAT                                                            |
| 24–25     | Number of sectors per track                                                          |
| 26–27     | Number of heads                                                                      |
| 28–29     | Number of hidden sectors                                                             |
| 30–509    | Bootstrap                                                                            |
| 510–511   | Signature (`0x55AA`)                                                                 |

---

## Example Boot Sector (Hex)
- Use an online hex editor for easier adress reading : https://hexed.it/
- Have a calculator with hex <-> decimal could be handy

```
eb 3c 90 4d 53 44 4f 53 35 2e 30 00 02 01 01 00
02 e0 00 40 0b f0 09 00 12 00 02 00 00 00 00 00
00 00 00 00 00 00 29 ca 18 39 19 4d 53 44 4f 53
20 20 20 20 20 20 46 41 54 31 32 20 20 20 fa 33
c0 8e d0 bc 00 7c 16 07 bb 78 00 36 c5 37 1e 56
16 53 bf 3e 7c b9 0b 00 fc f3 a4 06 1f c6 45 fe
0f 8b 0e 18 7c 88 4d f9 89 47 02 c7 07 3e 7c fb
cd 13 72 79 33 c0 39 06 13 7c 74 08 8b 0e 13 7c
89 0e 20 7c a0 10 7c f7 26 16 7c 03 06 1c 7c 13
16 1e 7c 03 06 0e 7c 83 d2 00 a3 50 7c 89 16 52
7c a3 49 7c 89 16 4b 7c b8 20 00 f7 26 11 7c 8b
...
0001f0 53 4d 53 44 4f 53 20 20 20 53 59 53 00 00 55 aa
```

---

## 🔍 Characteristics of the Example

1. **Sector Size**:
    - Bytes 11–12: `0x0200` → **512 bytes per sector**

2. **Cluster Size**:
    - Byte 13: `0x01` → 1 sector/cluster → **512 bytes**

3. **Root Directory Size**:
    - Bytes 17–18: `0x00E0` = 224 entries
    - Entry size: 32 bytes
    - → `224 × 32 = 7168 bytes`

4. **FAT Size**:
    - Bytes 22–23: `0x0009` = 9 sectors per FAT
    - → `9 × 512 = 4608 bytes`

5. **Number of FATs**:
    - Byte 16: `0x02` → **2 copies** (FAT1 & FAT2)

6. **Root Directory Start Address**:
    - Reserved sectors = 1 → `1 × 512 = 512 bytes`
    - FAT size = 4608 × 2 = 9216 bytes
    - Total before root: `512 + 9216 = 9728 bytes` = **0x2600**

7. **Hidden Sectors**:
    - Bytes 28–29: `0x0000`

8. **Data Area Start (first usable cluster for files)**:
    - Root directory starts at `0x2600`
    - Root directory size = 7168 bytes = 14 sectors
    - Cluster after root = 19 (FAT end) + 14 = **Sector 33**
    - → Address: **0x21**

---

## Exercise

### Question 0:
- Download the zip file from Moodle
- Do this in command
```bashrc
$ gunzip image . fat . gz
$ file image . fat
image.fat : x86 boot sector , mkdosfs boot message display, code offset 0 x3c ,
OEM - ID "mkdosfs" , sectors/cluster 32 , root entries 512 , Media descriptor
0 xf8 , sectors/FAT 32 , heads 64 , sectors 100000 (volumes > 32 MB) , serial
number 0 x6c075cbd , label : " " , FAT (12 bit )
```
#### **Explanation**:
* Sectors per cluster: 32 
* Bytes per sector: 512 
* Cluster size: 32 × 512 = 16 KiB 
* Reserved sectors: 32 (from your description: "The first 16KiB are reserved for descriptive structure of FAT and other things." 16KiB / 512 = 32 sectors)
* Sectors per FAT: 32 (so each FAT is 16KiB)
* Number of FATs: 2 (main + backup)

So the **First data cluster** starts after:
* Reserved sectors (boot sector and reserved area)
* All FATs (main and backup)
* The root directory (for FAT12/16; for FAT32, root directory is in the data area)

#### Calculation
- Reserved area: 32 sectors = 16KiB 
- FAT1: 32 sectors = 16KiB 
- FAT2: 32 sectors = 16KiB 
- Total before data area: 32 + 32 + 32 = 96 sectors => 96 × 512 = 49,152 bytes = 0xC000

So, the first data cluster (cluster 2 in FAT) starts at offset 0xC000

### Question 1: Write a grep to list all the offsets which look like HTML
- `-a` : Treat binary file as text
- `-b` : Print byte offset of each matched line
- `-o` : Print only matched parts (HTML tags in this case)

```bash
grep -aob '<[^>]\+>' image.fat 
```

### Question 2: Write a Makefile
(see Makefile)

### Question 3: Write the `offset_to_cluster` function defined in `libfatutils.h/.c`
  (see files)

### Question 4: Write the main in `off2clust.c`
- Use `readline` and `strtoul`
  (see files)

### Question 5: How much clusters are used in my image.fat file ?
```bashrc
make clean
make && make install
grep -aob '<[^>]\+>' image.fat | cut -d ":" -f 1 | ./off2clust
```
- Data are found in cluster 4, 5 and 6 ==> 3 clusters

### Question 6 :
- Rappel fonction `open`, `lseek`, `read`

### Question 10 : Reconstruct the lost file using 2 created binary files
```bashrc
make clean
make && sudo make install
grep -aob '<[^>]\+>' image.fat | cut -d ":" -f 1 | ./off2clust
./saveclust image.fat part 3 4 5
cat part.3 part.4 part.5 > reconstructed_file.html
```