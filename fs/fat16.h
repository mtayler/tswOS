#ifndef FAT32_INCLUDED
#define FAT32_INCLUDED

#define READ_ONLY (0x01)
#define HIDDEN (0x02)
#define SYSTEM (0x04)
#define VOLUME_ID (0x08)
#define DIRECTORY (0x10)
#define ARCHIVE (0x20)
#define LFN (READ_ONLY|HIDDEN|SYSTEM|VOLUME_ID)

#define EBPB_SECT_OFF (0x24)

typedef struct fat_BS
{
	uint8_t			bootjump[3];
	uint8_t			oem_name[8];
	uint16_t		bytes_per_sector;
	uint8_t			sectors_per_cluster;
	uint16_t		reserved_sector_count;
	uint8_t			table_count;
	uint16_t		root_entry_count;
	uint16_t		total_sectors_16;
	uint8_t			media_type;
	uint16_t		table_size_16;
	uint16_t		sectors_per_track;
	uint16_t		head_side_count;
	uint32_t		hidden_sectors_count;
	uint32_t		large_sector_count;
	uint8_t			bios_drive_num;
	uint8_t			reserved1;
	uint8_t			boot_signature;
	uint32_t		volume_id;
	uint8_t			volume_label[11];
	uint8_t			fat_type_label[8];
}__attribute__((packed)) fat_BS_t;

typedef uint8_t table_entry_t[32];

void print_fat_boot(fat_BS_t *fat_boot);

void read_root_dir(FILE *fp, fat_BS_t *fat_boot);

#endif // FAT32_INCLUDED
