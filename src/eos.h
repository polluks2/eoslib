/**
 * The Adam EOS C binding
 *
 * @author Thomas Cherryhomes
 * @email <thom.cherryhomes@gmail.com>
 */

#ifndef EOS_H
#define EOS_H

#define EOS_FILENAME_LEN 12

/* MIOC Bank Configurations */
#define BANK_CONFIG_SMARTWRITER_ROM_NORMAL_RAM 0
#define BANK_CONFIG_NORMAL_RAM_NORMAL_RAM 1
#define BANK_CONFIG_EXPANSION_RAM_NORMAL_RAM 2
#define BANK_CONFIG_OS7_ROM_NORMAL_RAM 3
#define BANK_CONFIG_SMARTWRITER_ROM_EXPANSION_ROM 4
#define BANK_CONFIG_NORMAL_RAM_EXPANSION_ROM 5
#define BANK_CONFIG_EXPANSION_RAM_EXPANSION_ROM 6
#define BANK_CONFIG_OS7_RAM_EXPANSION_ROM 7
#define BANK_CONFIG_SMARTWRITER_ROM_EXPANSION_RAM 8
#define BANK_CONFIG_NORMAL_RAM_EXPANSION_RAM 9
#define BANK_CONFIG_EXPANSION_RAM_EXPANSION_RAM 10
#define BANK_CONFIG_OS7_EXPANSION_RAM 11
#define BANK_CONFIG_SMARTWRITER_ROM_CARTRIDGE_ROM 12
#define BANK_CONFIG_NORMAL_RAM_CARTRIDGE_ROM 13
#define BANK_CONFIG_EXPANSION_RAM_CARTRIDGE_ROM 14
#define BANK_CONFIG_OS7_ROM_CARTRIDGE_ROM 15

/* VDP table numbers */
#define VDP_TABLE_SPRITE_ATTRIBUTE 0
#define VDP_TABLE_SPRITE_PATTERN 1
#define VDP_TABLE_PATTERN_NAMETABLE 2
#define VDP_TABLE_PATTERN_GENERATOR 3
#define VDP_TABLE_PATTERN_COLOR 4

typedef struct _pcb
{
  unsigned char status;
  unsigned short addr;
  unsigned char active_devices;
} PCB;

typedef struct _dcb
{
  unsigned char status;
  void *buf;
  unsigned short len;
  unsigned long block;
  unsigned char unit;
  unsigned char reserved0;
  unsigned char reserved1;
  unsigned char reserved2;
  unsigned char reserved3;
  unsigned char reserved4;
  unsigned char reserved5;
  unsigned char dev;
  unsigned short max_len;
  unsigned char type;
  unsigned char dev_status;
} DCB;

/* EOS File Control Block (FCB) structure */
typedef struct _fcb
{
  char filename[EOS_FILENAME_LEN];
  unsigned char attributes;
  unsigned long start_block;
  unsigned short allocated_blocks;
  unsigned short used_blocks;
  unsigned short last_block_bytes_used;
  unsigned char dev;
  unsigned char file_mode;
  unsigned short current_block;
  unsigned short last_block;
  unsigned short block_pos;
  unsigned char fcb_len;
} FCB;

/* EOS directory entry */
typedef struct _directoryEntry
{
  char filename[EOS_FILENAME_LEN];
  unsigned char attributes;
  unsigned long start_block;
  unsigned short allocated_blocks;
  unsigned short blocks_used;
  unsigned short last_block_bytes_used;
  unsigned char year;
  unsigned char month;
  unsigned char day;
} DirectoryEntry;

typedef struct _fileManager
{
  unsigned char year;
  unsigned char month;
  unsigned char dday;
  DirectoryEntry currentEntry;
  FCB *fcb;
  void *dir_buf; // TODO: get structure of this buffer?
  unsigned char file_number;
  unsigned short bytes_requested;
  unsigned short bytes_to_process;
  void *user_buf;
  void *fcb_begin;
  void *fcb_end;
  unsigned long current_block;
  char* filename;
  unsigned long blockno;
  unsigned long start_of_blocks_left;
  unsigned short blocks_left;
} FileManager;

typedef struct _gameControllerData
{
  unsigned char joystick2;
  unsigned char joystick2_button_left;
  unsigned char joystick2_button_right;
  unsigned char joystick2_keypad;
  unsigned char joystick2_spinner;
  unsigned char joystick1;
  unsigned char joystick1_button_left;
  unsigned char joystick1_button_right;
  unsigned char joystick1_keypad;
  unsigned char joystick1_spinner;
  
} GameControllerData;

/* Executive calls */

// aliases - TOS listing use different names
#define eos_start             eos_init
#define eos_dly_aft_hrd_res   eos_hard_reset_net
#define eos_sync              eos_synchronize_clocks
#define eos_scan_active       eos_scan_for_devices
#define eos_reloc_pcb         eos_relocate_pcb
#define eos_goto_wp           eos_exit_to_smartwriter
#define eos_switch_mem        eos_switch_memory_banks

void eos_init(void);
void eos_hard_init(void);
void eos_hard_reset_net(void);
void eos_delay_after_hard_reset(void);
void eos_synchronize_clocks(void);
void eos_scan_for_devices(void);
void eos_relocate_pcb(void);
void eos_soft_init(void *pcb); // TODO make typedef pcb
void eos_exit_to_smartwriter(void);
unsigned char eos_switch_memory_banks(unsigned char bconfig);

/* Console Output */

// aliases - TOS listing use different names
#define eos_cons_init         eos_console_init
#define eos_cons_disp         eos_console_display_regular
#define eos_cons_out          eos_console_display_special

void eos_console_init(unsigned char cols, unsigned char rows, unsigned char left, unsigned char top, unsigned short addr);
void eos_console_display_regular(char c, unsigned char col, unsigned char row);
void eos_console_display_special(char c, unsigned char col, unsigned char row);

/* Printer Interface */

// aliases - TOS listing use different names
#define eos_pr_ch             eos_print_character
#define eos_pr_buff           eos_print_buffer
#define eos_pr_stat           eos_printer_status
#define eos_start_pr_ch       eos_start_print_character
#define eos_end_pr_ch         eos_end_print_character

unsigned char eos_print_character(char c);
unsigned char eos_print_buffer(const char *c);
unsigned char eos_printer_status(void);
unsigned char eos_start_print_character(char c);
unsigned char eos_end_print_character(char c);

/* Keyboard Interface */

// aliases - TOS listing use different names
#define eos_req_kbd_stat      eos_keyboard_status
#define eos_rd_kbd            eos_read_keyboard
#define eos_start_rd_kbd      eos_start_read_keyboard
#define eos_end_rd_kbd        eos_end_read_keyboard

unsigned char eos_keyboard_status(void);
unsigned char eos_read_keyboard(void);
unsigned char eos_start_read_keyboard(void);
unsigned char eos_end_read_keyboard(void);

/* File Operations */

// aliases - TOS listing use different names
#define eos_fmgr_init         eos_file_manager_init
#define eos_scan_for_file     eos_check_directory_for_file
#define eos_query_file        eos_find_file_1
#define eos_file_query        eos_find_file_2
#define eos_check_fcb         eos_find_file_in_fcb
#define eos_mode_check        eos_check_file_mode
#define eos_set_file          eos_update_file_in_directory
#define eos_init_tape_dir     eos_initialize_directory
#define eos_set_date          eos_put_date

void eos_file_manager_init(void *fcb_buf, void *fcs_buf);
unsigned char eos_check_directory_for_file(const char *filename, unsigned long *block, unsigned char device_number);
unsigned char eos_find_file_1(const char *filename, DirectoryEntry *entry, unsigned long *block, unsigned char device_number);
unsigned char eos_find_file_2(const char *filename, DirectoryEntry *entry, unsigned long *block, unsigned char device_number);
unsigned char eos_find_file_in_fcb(const char *filename, unsigned char *filemode, FCB *fcb);
unsigned char eos_check_file_mode(const char *filename, FCB *fcb);
unsigned char eos_make_file(unsigned char dev, const char *filename, unsigned long size);
unsigned char eos_update_file_in_directory(unsigned char dev, const char *filename, FCB *fcb);
unsigned char eos_open_file(unsigned char dev, const char *filename, unsigned char mode, unsigned char *fileno);
unsigned char eos_close_file(unsigned char fileno);
unsigned short eos_read_file(unsigned char fileno, unsigned short len, void *buf, unsigned char *errorcode);
unsigned char eos_write_file(unsigned char fileno, unsigned short len, void *buf);
unsigned char eos_trim_file(unsigned char dev, const char *filename);
unsigned char eos_initialize_directory(unsigned char dev, unsigned char dirsize, unsigned short mediumsize, const char *volumename);
unsigned char eos_reset_file(unsigned char fileno);
unsigned char eos_get_date(unsigned char *day, unsigned char *month, unsigned char *year);
unsigned char eos_put_date(unsigned char day, unsigned char month, unsigned char year);
unsigned char eos_delete_file(unsigned char dev, const char *filename, unsigned long size);
unsigned char eos_rename_file(unsigned char dev, const char *oldname, const char *newname);

/* Device Operations */

// aliases - TOS listing use different names
#define eos_get_pcb_addr      eos_find_pcb
#define eos_get_dcb_addr      eos_find_dcb
#define eos_request_status    eos_request_device_status
#define eos_rd_dev_dep_stat   eos_get_device_status
#define eos_soft_res_dev      eos_soft_reset_device
#define eos_soft_res_kbd      eos_soft_reset_keyboard
#define eos_soft_res_pr       eos_soft_reset_printer
#define eos_rd_1_block        eos_read_one_block
#define eos_start_rd_1_block  eos_start_read_one_block
#define eos_end_rd_1_block    eos_end_read_one_block
#define eos_wr_1_block        eos_write_one_block
#define eos_start_wr_1_block  eos_start_write_one_block
#define eos_end_wr_1_block    eos_end_write_one_block
#define eos_start_rd_ch_dev   eos_start_read_character_device
#define eos_end_rd_ch_dev     eos_end_read_character_device
#define eos_start_wr_ch_dev   eos_start_write_character_device
#define eos_end_wr_ch_dev     eos_end_write_character_device

unsigned short eos_find_pcb(void);
DCB *eos_find_dcb(unsigned char dev);
unsigned char eos_request_device_status(unsigned char dev, DCB *dcb);
unsigned char eos_get_device_status(unsigned char dev);
unsigned char eos_soft_reset_device(unsigned char dev);
unsigned char eos_soft_reset_keyboard(void);
unsigned char eos_soft_reset_printer(void);
unsigned char eos_read_block(unsigned char dev, unsigned long blockno, void* buf);
unsigned char eos_read_one_block(unsigned char dev, unsigned long blockno, void* buf);
unsigned char eos_start_read_one_block(unsigned char dev, unsigned long blockno, void* buf);
unsigned char eos_end_read_one_block(unsigned char dev);
unsigned char eos_write_block(unsigned char dev, unsigned long blockno, void* buf);
unsigned char eos_write_one_block(unsigned char dev, unsigned long blockno, void* buf);
unsigned char eos_start_write_one_block(unsigned char dev, unsigned long blockno, void* buf);
unsigned char eos_end_write_one_block(unsigned char dev);
unsigned char eos_start_read_character_device(unsigned char dev, void* buf, unsigned short len);
unsigned char eos_end_read_character_device(unsigned char dev);
unsigned char eos_read_character_device(unsigned char dev, void* buf, unsigned short len);
unsigned char eos_start_write_character_device(unsigned char dev, void* buf, unsigned short len);
unsigned char eos_end_write_character_device(unsigned char dev);
unsigned char eos_write_character_device(unsigned char dev, void* buf, unsigned short len);

/* Video RAM Management */

// aliases - TOS listing use different names
#define eos_port_collection   eos_set_vdp_ports
#define eos_init_table        eos_set_vram_table_address
#define eos_load_ascii        eos_load_ascii_in_vdp
#define eos_write_register    eos_write_vdp_register
#define eos_read_register     eos_read_vdp_register
#define eos_calc_offset       eos_calculate_pattern_position
#define eos_px_to_ptrn_pos    eos_point_to_pattern_position
#define eos_wr_spr_attribute  eos_write_sprite_table

unsigned char eos_set_vdp_ports(void);
void eos_set_vram_table_address(unsigned char table, unsigned short addr);
void eos_load_ascii_in_vdp(void);
void eos_put_ascii_in_vdp(unsigned short num, unsigned short addr, unsigned short ch);
void eos_write_vram(unsigned short num, unsigned short addr, unsigned short buf);
void eos_read_vram(unsigned short num, unsigned short addr, unsigned short buf);
unsigned short eos_put_vram(unsigned char table, unsigned short first, void* buf, unsigned short len);
unsigned short eos_get_vram(unsigned char table, unsigned short first, void* buf, unsigned short len);
void eos_write_vdp_register(unsigned char reg, unsigned char val);
unsigned char eos_read_vdp_register(unsigned char reg, unsigned char val);
void eos_fill_vram(unsigned short val, unsigned short count, unsigned short addr);
unsigned short eos_calculate_pattern_position(unsigned char y, unsigned char x);
unsigned char eos_point_to_pattern_position(unsigned short offset);
void eos_write_sprite_table(unsigned short num, void* attr, void* priority);

/* Game Controllers */

// aliases - TOS listing use different names
#define eos_poller            eos_read_game_controller

void eos_read_game_controller(unsigned char controllers, void* decode);
void eos_update_spinner(void);

/* Sound Routines */

// aliases - TOS listing use different names
#define eos_turn_off_sound    eos_sound_off
#define eos_sounds            eos_play_sound
#define eos_effect_over       eos_end_sound

void eos_sound_init(unsigned char entries, void* sound_table);
void eos_sound_off(void);
unsigned char eos_start_sound(unsigned char soundno, void* end, void* nextnote, void* table);
unsigned char eos_play_sound(void);
void eos_end_sound(unsigned short* soundno, unsigned short* nextnote, void* soundtable);

/* Subroutines */
void eos_decrement_low_nibble(unsigned char *b);
void eos_decrement_high_nibble(unsigned char *b);
void eos_move_high_nibble_to_low_nibble(unsigned char *b);
void eos_add_a_to_hl(char a, unsigned short *b);

// The EOS returns a variety of error codes. Several of these are errors returned by the 
// Device Control Blocks. In order to interpret these from the table below, the high bit 
// must be stripped with an AND 7F.
#define EOS_ERR_NONE           0
#define EOS_ERR_DCB_NOT_FOUND  1 
#define EOS_ERR_DCB_BUSY       2
#define EOS_ERR_DCB_IDLE       3
#define EOS_ERR_NO_DATE        4
#define EOS_ERR_NO_FILE        5
#define EOS_ERR_FILE_EXISTS    6 // or printer busy
#define EOS_ERR_NO_FCB         7
#define EOS_ERR_MATCH          8 // or file incompatible
#define EOS_ERR_BAD_FNUM       9 // bad file number (greater than 2).
#define EOS_ERR_EOF_ERR       10
#define EOS_ERR_TOO_BIG       11
#define EOS_ERR_FULL_DIR      12 // or no key pressed on keyboard read
#define EOS_ERR_FULL_TAPE     13 // Storage media full
#define EOS_ERR_FILE_NM       14 // File number error
#define EOS_ERR_RENAME        15
#define EOS_ERR_DELETE        16
#define EOS_ERR_RANGE         17 // or bad mode
#define EOS_ERR_CANT_SYNC1    18 // Synchronize error on clock
#define EOS_ERR_CANT_SYNC2    19 // Synchronize error byte 2
#define EOS_ERR_PRT           20 
#define EOS_ERR_RQ_TP_STAT    21 // Media status error
#define EOS_ERR_DEVICE_DEPD   22 // Device error, usually with tapes or disks
#define EOS_ERR_PROG_NON_EXIST 23 //Program doesn't exist
#define EOS_ERR_NO_DIR        24 // Storage medium fails directory validity check
#define EOS_ERR_TIMEOUT       0x9B // ??? 27 Device time out

// The following are result codes returned from the AdamNet, in response to
// eos_read/write/block/character and status calls.
// They come from the 6801 Master Listing

#define ADAMNET_OK                 0x80 // All good
#define ADAMNET_READY_TIMEOUT      0x81 // 0xDx (READY) packet was not responded in time.
#define ADAMNET_RTS_COMM_ERR       0x82 // ???
#define ADAMNET_SEND_TIMEOUT       0x83 // 0x6x (SEND) packet was not responded in time.
#define ADAMNET_SEND_COMM_ERR      0x84 // ???
#define ADAMNET_SEND_DATA_BREAK    0x85 // Peripheral sent a BREAK during a send response. (0xBx)
#define ADAMNET_READY_NACK         0x86 // 0xDx (READY) packet was acknowledged with a 0xCx (NACK)
#define ADAMNET_READY_BREAK        0x87 // Peripheral sent a BREAK during a ready. (0xDx)
#define ADAMNET_SEND_DATA_NACK     0x88 // 0x6x (SEND) packet was acknowledged with a 0xCx (NACK)
#define ADAMNET_RECEIVE_TIMEOUT    0x89 // 0x4x (RECEIVE) packet was not responded in time.
#define ADAMNET_RECEIVE_BREAK      0x8A // Peripheral sent a BREAK while ADAM was requesting a receive (0x4x)
#define ADAMNET_RECEIVE_BREAK_DATA 0x8B // Peripheral sent a BREAK while ADAM was receiving data
#define ADAMNET_RECEIVE_NACK       0x8C // Peripheral responded with NACK (0xCx) during a Receive  (0x4x)
#define ADAMNET_CLR_TIMEOUT        0x8D // Peripheral did not respond with (0xBx) in time
#define ADAMNET_CLR_ERR            0x8E // Error during CLR (0x3x) phase (not sure?)
#define ADAMNET_CLR_BREAK          0x8F // Peripheral sent BREAK after a CLR (0x3x)
#define ADAMNET_DATA_IN_ERROR      0x90 // Am guessing this is a general framing error?
#define ADAMNET_DATA_IN_TIMEOUT    0x91 // Timeout while receiving part of a data byte.
#define ADAMNET_BAD_ASIG           0x92 // ???
#define ADAMNET_STAT_TIMEOUT       0x93 // 0x01 (STATUS) paccket was not responded in time.
#define ADAMNET_STAT_BREAK         0x94 // Peripheral sent a BREAK while Adam was waiting for STATUS (0x1x)
#define ADAMNET_STATUS_BREAK       0x95 // What? There's another one?
#define ADAMNET_TCU_ERR1           0x96 // Master 6801 couldn't transmit, this is bad.
#define ADAMNET_TCU_ERR2           0x97 // Master 6801 couldn't transmit, this is bad.
#define ADAMNET_TRANS_TO1          0x98 // Master 6801 Timed out while transmitting, this is bad.
#define ADAMNET_TRANS_TO2          0x99 // Master 6801 timed out while transmitting, this is bad.
#define ADAMNET_HAVE_ORFE          0x9A // ???
#define ADAMNET_TIMEOUT            0x9B // General Timeout outside of a particular packet state.
#define ADAMNET_BAD_RDRF           0x9C // I suspect this is when the receive packet size doesn't match
#define ADAMNET_BAD_TDRE           0x9D // ???
#define ADAMNET_BAD_ORFE           0x9E // ???

#endif /* EOS_H */
