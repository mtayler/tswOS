#ifndef FAT32_INCLUDED
#define FAT32_INCLUDED

#define READ_ONLY (0x01)
#define HIDDEN (0x02)
#define SYSTEM (0x04)
#define VOLUME_ID (0x08)
#define DIRECTORY (0x10)
#define ARCHIVE (0x20)
#define LFN (READ_ONLY|HIDDEN|SYSTEM|VOLUME_ID)

typedef struct fat_extBS_32
{
	// extended fat32 stuff
	uint32_t		table_size_32;
	uint16_t		extended_flags;
	uint16_t		fat_version;
	uint32_t		root_cluster;
	uint16_t		fat_info;
	uint16_t		backup_BS_sector;
	uint8_t			reserved_0[12];
	uint8_t			drive_number;
	uint8_t			reserved_1;
	uint8_t			boot_signature;
	uint32_t		volume_id;
	uint8_t			volume_label[11];
	uint8_t			fat_type_label[8];
}__attribute__((packed)) fat_extBS_32_t;

typedef struct fat_extBS16_16
{
	uint8_t			bios_drive_num;
	uint8_t			reserved1;
	uint8_t			boot_signature;
	uint16_t		volume_id;
	uint8_t			volume_label[11];
	uint8_t			fat_type_label[8];
}__attribute__((packed)) fat_extBS_16_t;

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
	uint32_t		total_sectors_32;

	// this will be cast to it's specific type once the driver actually
	// knows what type of FAT this is
	uint8_t			extended_section[54];
}__attribute__((packed)) fat_BS_t;


void print_fat_boot(fat_BS_t *fat_boot);

#endif // FAT32_INCLUDED
