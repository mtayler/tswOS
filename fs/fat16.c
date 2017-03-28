#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "fat16.h"

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

	printf("bios_drive_num:\t\t\t0x%02X\n", fat_boot->bios_drive_num);
	printf("reserved1:\t\t\t0x%02X\n", fat_boot->reserved1);
	printf("boot_signature:\t\t\t0x%02X\n", fat_boot->boot_signature);
	printf("volume_id:\t\t\t0x%04X\n", fat_boot->volume_id);
	printf("volume_label:\t\t\t%.11s\n", fat_boot->volume_label);
	printf("fat_type_label:\t\t\t%.8s\n", fat_boot->fat_type_label);
}

void read_root_dir(FILE *fp, fat_BS_t *fat_boot) {
	uint16_t total_sectors = fat_boot->total_sectors_16;
	uint16_t fat_size = fat_boot->table_size_16;

	/* First sector in the FAT */
	uint32_t first_fat_sector = fat_boot->reserved_sector_count;

	/* First sector of the root directory */
	uint32_t first_root_dir_sector = first_fat_sector
		+ (fat_boot->table_count * fat_size);

	/* Number of sectors in the root dir */
	uint32_t root_dir_sectors =
		((fat_boot->root_entry_count * 32) + (fat_boot->bytes_per_sector - 1))
		/ fat_boot->bytes_per_sector;
	
	/* First data sector (first sector in which dir and files may be stored */
	uint32_t first_data_sector = first_root_dir_sector + root_dir_sectors;

	/* Total number of data sectors */
	uint16_t data_sectors = fat_boot->total_sectors_16
		- (fat_boot->reserved_sector_count + (fat_boot->table_count * fat_size)
				+ root_dir_sectors);

	/* Get the total number of clusters (rounds down) */
	uint16_t total_clusters = data_sectors / fat_boot->sectors_per_cluster;


	uint32_t current_pos = (first_root_dir_sector) * fat_boot->bytes_per_sector;
	/* Set fp to start of data sector */
	fseek(fp, current_pos, SEEK_SET); 
	table_entry_t entry;
	uint32_t num_entries = 0;
	while (current_pos < first_data_sector * fat_boot->bytes_per_sector) {
		fread(entry, sizeof(entry), 1, fp);
		/* Skip if the entry is unused */
		if (!((*entry & 0xFF) ^ 0x00)) {
			current_pos += sizeof(entry);
			break;
		}
		else if (!((*entry & 0xFF) ^ 0xE5)) {
			current_pos += sizeof(entry);
			continue;
		}
		else {
			printf("0x%0X:\t%.8s.%.3s\n", current_pos, entry, &(entry[8]));
			current_pos += sizeof(entry);
			num_entries++;
		}
	}
	printf("num entries: %d\n", num_entries);
}
