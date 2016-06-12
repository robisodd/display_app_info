#include "pebble.h"
#include "pebble_process_info.h"

void display_app_info() {
  // Don't forget: #include "pebble_process_info.h"
  extern const PebbleProcessInfo __pbl_app_info;
  
  printf("APP Version: %d.%d", __pbl_app_info.process_version.major, __pbl_app_info.process_version.minor);
  printf("Name: %s",           __pbl_app_info.name);
  printf("Company: %s",        __pbl_app_info.company);
  
  char uuidString[UUID_STRING_BUFFER_LENGTH];
  uuid_to_string((Uuid*)&__pbl_app_info.uuid, uuidString);
  printf("UUID: %s", uuidString);
}



Window *main_window;
int main(void) {
  display_app_info();
//   window_stack_push(window_create(), true); // For some reason, this doesn't work...
  main_window = window_create();               // This HAS to be global, for some reason...
  window_stack_push(main_window, true);        // And you HAVE to display a window for displayAppInfo to work
  app_event_loop();
}




// This is the PebbleProcessInfo structure
/*
typedef struct __attribute__((__packed__)) {
  uint8_t major; //!< "compatibility" version number
  uint8_t minor;
} Version;

#define PROCESS_NAME_BYTES 32
#define COMPANY_NAME_BYTES 32

typedef struct __attribute__((__packed__)) {
  char header[8];                   //!< Sentinal value, should always be 'PBLAPP'
  Version struct_version;           //!< version of this structure's format
  Version sdk_version;              //!< version of the SDK used to build this process
  Version process_version;          //!< version of the process
  uint16_t load_size;               //!< size of the binary in flash, including this metadata but not the reloc table
  uint32_t offset;                  //!< The entry point of this executable
  uint32_t crc;                     //!< CRC of the data only, ie, not including this struct or the reloc table at the end
  char name[PROCESS_NAME_BYTES];    //!< Name to display on the menu
  char company[COMPANY_NAME_BYTES]; //!< Name of the maker of this process
  uint32_t icon_resource_id;        //!< Resource ID within this bank to use as a 32x32 icon
  uint32_t sym_table_addr;          //!< The system will poke the sdk's symbol table address into this field on load
  uint32_t flags;                   //!< Bitwise OR of PebbleProcessInfoFlags
  uint32_t num_reloc_entries;       //!< The number of entries in the address relocation list
  struct __attribute__((__packed__)) {
    uint8_t byte0;
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
    uint8_t byte4;
    uint8_t byte5;
    uint8_t byte6;
    uint8_t byte7;
    uint8_t byte8;
    uint8_t byte9;
    uint8_t byte10;
    uint8_t byte11;
    uint8_t byte12;
    uint8_t byte13;
    uint8_t byte14;
    uint8_t byte15;
  } uuid;                           //!< The process's UUID
  uint32_t resource_crc;            //!< CRC of the resource data only
  uint32_t resource_timestamp;      //!< timestamp of the resource data
  uint16_t virtual_size;            //!< The total amount of memory used by the process (.text + .data + .bss)
} PebbleProcessInfo;
*/