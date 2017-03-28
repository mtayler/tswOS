#include <stdio.h>
#include <stdlib.h>

#include "fat16.h"

int main(void) {
	puts("Starting");
	FILE *fp;
	fp = fopen("fat.fs", "r");

	if (fp == NULL) {
		puts("Could not open file");
		return 1;
	}
	puts("Opened image");

	fat_BS_t fat_boot;

	fread(&fat_boot, sizeof(fat_boot), 1, fp);
	puts ("Read from image");

	puts("======= Boot sector =======");
	print_fat_boot(&fat_boot);

	puts("==== Number of Entries ====");
	read_root_dir(fp, &fat_boot);

	return 0;
}

