#include <stdio.h>
#include <stdint.h>

#include "fat32.h"

void print_fat_boot(fat_BS_t *fat_boot) {
	printf("bootjump\t\t\t0x%02X,0x%02X,0x%02X\n",
			fat_boot->bootjump[0],
			fat_boot->bootjump[1],
			fat_boot->bootjump[2]
		  );
	printf("oem_name:\t\t\t%s\n", fat_boot->oem_name);
	printf("bytes_per_sector:\t\t0x%04X\n", fat_boot->bytes_per_sector);
	printf("sectors_per_cluster:\t\t0x%02X\n", fat_boot->sectors_per_cluster);
	printf("reserved_sector_count:\t\t0x%04X\n", fat_boot->reserved_sector_count);
	printf("table_count:\t\t\t0x%02X\n", fat_boot->table_count);
	printf("root_entry_count:\t\t0x%04X\n", fat_boot->root_entry_count);
	printf("total_sectors_16:\t\t0x%04X\n", fat_boot->total_sectors_16);
	printf("media_type:\t\t\t0x%02X\n", fat_boot->media_type);
	printf("table_size_16:\t\t\t0x%04X\n", fat_boot->table_size_16);
	printf("sectors_per_cluster:\t\t0x%04X\n", fat_boot->sectors_per_track);
	printf("head_side_count:\t\t0x%04X\n", fat_boot->head_side_count);
	printf("hidden_sectors_count:\t\t0x%08X\n", fat_boot->hidden_sectors_count);
	printf("total_sectors_32:\t\t0x%08X\n", fat_boot->total_sectors_32);

	printf("extended_section:\t\t");
	for (size_t i=0; i < 54; i++) {
		printf("0x%02X,", fat_boot->extended_section[i]);
		if ((i+1) % 6 == 0) {
			fputs("\n\t\t\t\t", stdout);
		}
	}
	fputs("\n", stdout);
}

int main(void) {
	puts("Starting");
	FILE *fp;
	fp = fopen("test.dmg", "r");

	if (fp == NULL) {
		puts("File not opened");
		return 1;
	}
	puts("Opened image");

	fat_BS_t fat_boot;
	fat_extBS_32_t fat_ext;

	fread(&fat_boot, sizeof(fat_BS_t), 1, fp);
	fread(&fat_ext, sizeof(fat_extBS_32_t), 1, fp);
	puts ("Read from image");

	puts("===== Boot sector =====");
	print_fat_boot(&fat_boot);
	/* print_fat_ext32(&fat_ext); */
	return 0;
}
