/*
 * Authors (alphabetical order)
 * - Andre Bernet <bernet.andre@gmail.com>
 * - Andreas Weitl
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bryan J. Rentoul (Gruvin) <gruvin@gmail.com>
 * - Cameron Weeks <th9xer@gmail.com>
 * - Erez Raviv
 * - Gabriel Birkus
 * - Jean-Pierre Parisy
 * - Karl Szmutny
 * - Michael Blandford
 * - Michal Hlavinka
 * - Pat Mackenzie
 * - Philip Moss
 * - Rob Thomson
 * - Romolo Manfredini <romolo.manfredini@gmail.com>
 * - Thomas Husterer
 *
 * opentx is based on code named
 * gruvin9x by Bryan J. Rentoul: http://code.google.com/p/gruvin9x/,
 * er9x by Erez Raviv: http://code.google.com/p/er9x/,
 * and the original (and ongoing) project by
 * Thomas Husterer, th9x: http://code.google.com/p/th9x/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <stdint.h>
#include "opentx.h"
#include "inttypes.h"
#include "string.h"

volatile  uint32_t Spi_complete; // TODO in the driver ?

// Logic for storing to EEPROM/loading from EEPROM
// If main needs to wait for the eeprom, call mainsequence without actioning menus
// General configuration
// 'main' set flag STORE_GENERAL
// 'eeCheck' sees flag STORE_GENERAL, copies data, starts 2 second timer, clears flag STORE_GENERAL
// 'eeCheck' sees 2 second timer expire, locks copy, initiates write, enters WRITE_GENERAL mode
// 'eeCheck' completes write, unlocks copy, exits WRITE_GENERAL mode

// 'main' set flag STORE_MODEL(n)

// 'main' set flag STORE_MODEL_TRIM(n)


// 'main' needs to load a model


// These may not be needed, or might just be smaller
// TODO in the driver ?
uint8_t Spi_tx_buf[24] ;
uint8_t Spi_rx_buf[24] ;

struct t_file_entry File_system[MAX_MODELS+1] ;

// TODO check everything here
uint8_t	Eeprom32_process_state = E32_IDLE;
uint8_t	Eeprom32_state_after_erase ;
uint8_t	Eeprom32_write_pending ;
uint8_t Eeprom32_file_index ;
uint8_t *Eeprom32_buffer_address ;
uint8_t *Eeprom32_source_address ;
uint32_t Eeprom32_address ;
uint32_t Eeprom32_data_size ;

#define EE_NOWAIT	1

uint32_t get_current_block_number( uint32_t block_no, uint16_t *p_size, uint32_t *p_seq ) ;
void write32_eeprom_block( uint32_t eeAddress, register uint8_t *buffer, uint32_t size, uint32_t immediate=0 ) ;

// New file system

// Start with 16 model memories, initial test uses 34 and 35 for these
// Blocks 0 and 1, general
// Blocks 2 and 3, model 1
// Blocks 4 and 5, model 2 etc
// Blocks 32 and 33, model 16

uint8_t Current_general_block ;		// 0 or 1 is active block
uint8_t Other_general_block_blank ;

struct t_eeprom_buffer
{
    struct t_eeprom_header header ;
    union t_eeprom_data
    {
        EEGeneral general_data ;
        ModelData model_data ;
        uint8_t   bytes[4096-sizeof(t_eeprom_header)];
    } data ;
} Eeprom_buffer ;

void eeDeleteModel(uint8_t id)
{
  eeCheck(true);

  memset(modelHeaders[id].name, 0, sizeof(g_model.header.name));

  Eeprom32_source_address = (uint8_t *)&g_model ;   // Get data from here
  Eeprom32_data_size = 0 ;                          // This much
  Eeprom32_file_index = id + 1 ;                    // This file system entry
  Eeprom32_process_state = E32_BLANKCHECK ;
  eeWaitFinished();
}

bool eeCopyModel(uint8_t dst, uint8_t src)
{
  // eeCheck(true) should have been called before entering here

  uint16_t size = File_system[src+1].size ;
  read32_eeprom_data( (File_system[src+1].block_no << 12) + sizeof( struct t_eeprom_header), ( uint8_t *)&Eeprom_buffer.data.model_data, size) ;

  if (size > sizeof(g_model.header.name))
    memcpy(modelHeaders[dst].name, Eeprom_buffer.data.model_data.header.name, sizeof(g_model.header.name));
  else
    memset(modelHeaders[dst].name, 0, sizeof(g_model.header.name));

  Eeprom32_source_address = (uint8_t *)&Eeprom_buffer.data.model_data;    // Get data from here
  Eeprom32_data_size = sizeof(g_model) ;                                  // This much
  Eeprom32_file_index = dst + 1 ;                                         // This file system entry
  Eeprom32_process_state = E32_BLANKCHECK ;
  eeWaitFinished();
  return true;
}

void eeSwapModels(uint8_t id1, uint8_t id2)
{
  // eeCheck(true) should have been called before entering here

  uint16_t id2_size = File_system[id2+1].size;
  uint32_t id2_block_no = File_system[id2+1].block_no;

  eeCopyModel(id2, id1);

  // block_no(id1) has been shifted now, but we have the size

  // TODO flash saving with function above ...
  if (id2_size > sizeof(g_model.header.name)) {
    read32_eeprom_data( (id2_block_no << 12) + sizeof( struct t_eeprom_header), ( uint8_t *)&Eeprom_buffer.data.model_data, id2_size);
    memcpy(modelHeaders[id1].name, Eeprom_buffer.data.model_data.header.name, sizeof(g_model.header.name));
  }
  else {
    memset(modelHeaders[id1].name, 0, sizeof(g_model.header.name));
  }

  Eeprom32_source_address = (uint8_t *)&Eeprom_buffer.data.model_data;    // Get data from here
  Eeprom32_data_size = id2_size ;                                         // This much
  Eeprom32_file_index = id1 + 1 ;                                         // This file system entry
  Eeprom32_process_state = E32_BLANKCHECK ;
  eeWaitFinished();
}

// Read eeprom data starting at random address
void read32_eeprom_data(uint32_t eeAddress, register uint8_t *buffer, uint32_t size, uint32_t immediate)
{
#ifdef SIMU
  assert(size);
  eeprom_pointer = eeAddress;
  eeprom_buffer_data = (char*)buffer;
  eeprom_buffer_size = size;
  eeprom_read_operation = true;
  Spi_complete = false;
  sem_post(eeprom_write_sem);
#else
  register uint8_t *p = Spi_tx_buf ;
  *p = 3 ;                     // Read command
  *(p+1) = eeAddress >> 16 ;
  *(p+2) = eeAddress >> 8 ;
  *(p+3) = eeAddress ;	       // 3 bytes address
  spi_PDC_action( p, 0, buffer, 4, size ) ;
#endif

  if (immediate )
    return ;

  while (!Spi_complete) {
#ifdef SIMU
    sleep(5/*ms*/);
#endif
  }
}

void write32_eeprom_block( uint32_t eeAddress, register uint8_t *buffer, uint32_t size, uint32_t immediate )
{
#ifdef SIMU
  assert(size);
  eeprom_pointer = eeAddress;
  eeprom_buffer_data = (char*)buffer;
  eeprom_buffer_size = size+1;
  eeprom_read_operation = false;
  Spi_complete = false;
  sem_post(eeprom_write_sem);
#else
  eeprom_write_enable();

  register uint8_t *p = Spi_tx_buf;
  *p = 2; // Write command
  *(p + 1) = eeAddress >> 16;
  *(p + 2) = eeAddress >> 8;
  *(p + 3) = eeAddress; // 3 bytes address
  spi_PDC_action(p, buffer, 0, 4, size);
#endif

  if (immediate)
    return;

  while (!Spi_complete) {
#ifdef SIMU
    sleep(5/*ms*/);
#endif
  }
}

uint8_t byte_checksum( uint8_t *p, uint32_t size )
{
	uint32_t csum ;

	csum = 0 ;
	while( size )
	{
		csum += *p++ ;
		size -= 1 ;
	}
	return csum ;
}

uint32_t ee32_check_header( struct t_eeprom_header *hptr )
{
	uint8_t csum ;

	csum = byte_checksum( ( uint8_t *) hptr, 7 ) ;
	if ( csum == hptr->hcsum )
	{
		return 1 ;
	}
	return 0 ;
}

// Pass in an even block number, this and the next block will be checked
// to see which is the most recent, the block_no of the most recent
// is returned, with the corresponding data size if required
// and the sequence number if required
uint32_t get_current_block_number( uint32_t block_no, uint16_t *p_size, uint32_t *p_seq )
{
  struct t_eeprom_header b0 ;
  struct t_eeprom_header b1 ;
  uint32_t sequence_no ;
  uint16_t size ;
  read32_eeprom_data( block_no << 12, ( uint8_t *)&b0, sizeof(b0) ) ;		// Sequence # 0
  read32_eeprom_data( (block_no+1) << 12, ( uint8_t *)&b1, sizeof(b1) ) ;	// Sequence # 1

  if ( ee32_check_header( &b0 ) == 0 )
  {
    b0.sequence_no = 0 ;
    b0.data_size = 0 ;
    b0.flags = 0 ;
  }

  size = b0.data_size ;
  sequence_no = b0.sequence_no ;
  if ( ee32_check_header( &b0 ) == 0 )
  {
    if ( ee32_check_header( &b1 ) != 0 )
    {
      size = b1.data_size ;
      sequence_no = b1.sequence_no ;
      block_no += 1 ;
    }
    else
    {
      size = 0 ;
      sequence_no = 1 ;
    }
  }
  else
  {
    if ( ee32_check_header( &b1 ) != 0 )
    {
      if ( b1.sequence_no > b0.sequence_no )
      {
        size = b1.data_size ;
        sequence_no = b1.sequence_no ;
        block_no += 1 ;
      }
    }
  }
  
  if ( size == 0xFFFF )
  {
    size = 0 ;
  }
  if ( p_size )
  {
    *p_size = size ;
  }
  if ( sequence_no == 0xFFFFFFFF )
  {
    sequence_no = 0 ;
  }
  if ( p_seq )
  {
    *p_seq = sequence_no ;
  }
//	Block_needs_erasing = erase ;		
  
  return block_no ;
}

bool eeLoadGeneral()
{
  uint16_t size = File_system[0].size;

  memset(&g_eeGeneral, 0, sizeof(EEGeneral));

  if (size > sizeof(EEGeneral)) {
    size = sizeof(EEGeneral) ;
  }

  if (size) {
    read32_eeprom_data( ( File_system[0].block_no << 12) + sizeof( struct t_eeprom_header), ( uint8_t *)&g_eeGeneral, size) ;
  }

  if (g_eeGeneral.version != EEPROM_VER) {
    TRACE_DEBUG("EEPROM version %d (%d) instead of %d (%d)\n", g_eeGeneral.version, g_eeGeneral.variant, EEPROM_VER, EEPROM_VARIANT);
    if (!eeConvert())
      return false;
  }

  return true;
}

void eeLoadModel(uint8_t id)
{
  if (id<MAX_MODELS) {

#if defined(SDCARD)
    closeLogs();
#endif

    if (pulsesStarted()) {
      pausePulses();
    }

    pauseMixerCalculations();

    uint16_t size = File_system[id+1].size ;

    memset(&g_model, 0, sizeof(g_model));

#if defined(SIMU)
    if (size > 0 && size != sizeof(g_model)) {
      printf("Model data read=%d bytes vs %d bytes\n", size, (int)sizeof(ModelData));
    }
#endif

    if (size > sizeof(g_model)) {
      size = sizeof(g_model) ;
    }

    if(size < 256) { // if not loaded a fair amount
      modelDefault(id) ;
      eeCheck(true);
    }
    else {
      read32_eeprom_data((File_system[id+1].block_no << 12) + sizeof(struct t_eeprom_header), (uint8_t *)&g_model, size) ;
    }

    resetAll();

    if (pulsesStarted()) {
      checkAll();
      resumePulses();
    }

    activeSwitches = 0;
    activeFnSwitches = 0;
    activeFunctions = 0;
    memclear(lastFunctionTime, sizeof(lastFunctionTime));

    for (uint8_t i=0; i<MAX_TIMERS; i++) {
      if (g_model.timers[i].persistent) {
        timersStates[i].val = g_model.timers[i].value;
      }
    }

    resumeMixerCalculations();
    // TODO pulses should be started after mixer calculations ...

#if defined(FRSKY)
    frskySendAlarms();
#endif

#if defined(CPUARM) && defined(SDCARD)
    refreshModelAudioFiles();
#endif

    LOAD_MODEL_BITMAP();

    SEND_FAILSAFE_1S();
  }
}

bool eeModelExists(uint8_t id)
{
  return ( File_system[id+1].size > 0 ) ;
}

void eeLoadModelName(uint8_t id, char *name)
{
  memclear(name, sizeof(g_model.header.name));
  if (id < MAX_MODELS) {
    id += 1;
    if (File_system[id].size > sizeof(g_model.header.name) ) {
      read32_eeprom_data((File_system[id].block_no << 12)+8, (uint8_t *)name, sizeof(g_model.header.name));
    }
  }
}

#if defined(CPUARM)
void eeLoadModelHeader(uint8_t id, ModelHeader *header)
{
  memclear(header, sizeof(ModelHeader));
  if (id < MAX_MODELS) {
    id += 1;
    if (File_system[id].size > sizeof(ModelHeader)) {
      read32_eeprom_data((File_system[id].block_no << 12)+8, (uint8_t *)header, sizeof(ModelHeader));
    }
  }
}
#endif

void fill_file_index()
{
  for (uint32_t i = 0 ; i < MAX_MODELS + 1 ; i += 1 )
  {
    File_system[i].block_no = get_current_block_number( i * 2, &File_system[i].size, &File_system[i].sequence_no ) ;
  }
}

void eeReadAll()
{
  fill_file_index() ;

  if (!eeLoadGeneral() )
  {
    generalDefault();
    modelDefault(0);

    ALERT(STR_EEPROMWARN, STR_BADEEPROMDATA, AU_BAD_EEPROM);

    if (pwrCheck() == e_power_off) {
      // the radio has been powered off during the ALERT
      pwrOff(); // turn power off now
    }

    MESSAGE(STR_EEPROMWARN, STR_EEPROMFORMATTING, NULL, AU_EEPROM_FORMATTING);

    /* we remove all models */
    for (uint32_t i=0; i<MAX_MODELS; i++)
      eeDeleteModel(i);

    eeDirty(EE_GENERAL);
    eeDirty(EE_MODEL);
  }
  else {
    eeLoadModelHeaders() ;
  }

  // TODO common!
  stickMode = g_eeGeneral.stickMode;

#if defined(CPUARM)
  for (uint8_t i=0; languagePacks[i]!=NULL; i++) {
    if (!strncmp(g_eeGeneral.ttsLanguage, languagePacks[i]->id, 2)) {
      currentLanguagePackIdx = i;
      currentLanguagePack = languagePacks[i];
    }
  }
#endif
}

void eeWaitFinished()
{
  while (Eeprom32_process_state != E32_IDLE) {
    ee32_process();
#ifdef SIMU
    sleep(5/*ms*/);
#endif
  }
}

void eeCheck(bool immediately)
{
  if (immediately) {
    eeWaitFinished();
  }

  if (s_eeDirtyMsk & EE_GENERAL) {
    s_eeDirtyMsk -= EE_GENERAL;
    Eeprom32_source_address = (uint8_t *)&g_eeGeneral ;               // Get data from here
    Eeprom32_data_size = sizeof(g_eeGeneral) ;                        // This much
    Eeprom32_file_index = 0 ;                                         // This file system entry
    Eeprom32_process_state = E32_BLANKCHECK ;
    if (immediately)
      eeWaitFinished();
    else
      return;
  }

  if (s_eeDirtyMsk & EE_MODEL) {
    s_eeDirtyMsk -= EE_MODEL;
    Eeprom32_source_address = (uint8_t *)&g_model ;           // Get data from here
    Eeprom32_data_size = sizeof(g_model) ;                    // This much
    Eeprom32_file_index = g_eeGeneral.currModel + 1 ;         // This file system entry
    Eeprom32_process_state = E32_BLANKCHECK ;
    if (immediately)
      eeWaitFinished();
  }
}

void ee32_process()
{
  register uint8_t *p ;
  register uint8_t *q ;
  register uint32_t x ;
  register uint32_t eeAddress ;

  if ( Eeprom32_process_state == E32_BLANKCHECK ) {
    eeAddress = File_system[Eeprom32_file_index].block_no ^ 1 ;
    eeAddress <<= 12 ;		                                // Block start address
    Eeprom32_address = eeAddress ;				// Where to put new data
#if 0
    x = Eeprom32_data_size + sizeof( struct t_eeprom_header ) ;	// Size needing to be checked
    p = (uint8_t *) &Eeprom_buffer ;
    read32_eeprom_data( eeAddress, p, x, EE_NOWAIT ) ;
#endif
    Eeprom32_process_state = E32_READSENDING ;
  }

  if ( Eeprom32_process_state == E32_READSENDING )
  {
#if 0
    if ( Spi_complete )
    {
      uint32_t blank = 1 ;
      x = Eeprom32_data_size + sizeof( struct t_eeprom_header ) ;	// Size needing to be checked
      p = (uint8_t *) &Eeprom_buffer ;
      while ( x )
      {
        if ( *p++ != 0xFF )
        {
          blank = 0 ;
          break ;
        }
        x -= 1 ;
      }
      // If not blank, sort erasing here
      if ( blank )
      {
        Eeprom32_state_after_erase = E32_IDLE ; // TODO really needed?
        Eeprom32_process_state = E32_WRITESTART ;
      }
      else
      {
#endif
#ifdef SIMU
        Eeprom32_process_state = E32_WRITESTART ;
#else
        eeAddress = Eeprom32_address ;
        eeprom_write_enable() ;
        p = Spi_tx_buf ;
        *p = 0x20 ;		// Block Erase command
        *(p+1) = eeAddress >> 16 ;
        *(p+2) = eeAddress >> 8 ;
        *(p+3) = eeAddress ;		// 3 bytes address
        spi_PDC_action( p, 0, 0, 4, 0 ) ;
        Eeprom32_process_state = E32_ERASESENDING ;
        Eeprom32_state_after_erase = E32_WRITESTART ;
#endif
      // }
   // }
  }

  if ( Eeprom32_process_state == E32_WRITESTART )
  {
    uint32_t total_size ;
    p = Eeprom32_source_address;
    q = (uint8_t *) &Eeprom_buffer.data;
    if (p != q) {
      for (x = 0; x < Eeprom32_data_size; x += 1) {
        *q++ = *p++; // Copy the data to temp buffer
      }
    }
    Eeprom_buffer.header.sequence_no = ++File_system[Eeprom32_file_index].sequence_no;
    File_system[Eeprom32_file_index].size = Eeprom_buffer.header.data_size = Eeprom32_data_size;
    Eeprom_buffer.header.flags = 0;
    Eeprom_buffer.header.hcsum = byte_checksum((uint8_t *) &Eeprom_buffer, 7);
    total_size = Eeprom32_data_size + sizeof(struct t_eeprom_header);
    eeAddress = Eeprom32_address; // Block start address
    x = total_size / 256; // # sub blocks
    x <<= 8; // to offset address
    eeAddress += x; // Add it in
    p = (uint8_t *) &Eeprom_buffer;
    p += x; // Add offset
    x = total_size % 256; // Size of last bit
    if (x == 0) // Last bit empty
    {
      x = 256;
      p -= x;
      eeAddress -= x;
    }
    Eeprom32_buffer_address = p;
    Eeprom32_address = eeAddress;
    write32_eeprom_block(eeAddress, p, x, EE_NOWAIT);
    Eeprom32_process_state = E32_WRITESENDING ;
  }

  if ( Eeprom32_process_state == E32_WRITESENDING )
  {
    if ( Spi_complete )
    {
      Eeprom32_process_state = E32_WRITEWAITING ;
    }
  }

  if ( Eeprom32_process_state == E32_WRITEWAITING )
  {
    x = eeprom_read_status() ;
    if ( ( x & 1 ) == 0 )
    {
      if ( ( Eeprom32_address & 0x0FFF ) != 0 )		// More to write
      {
        Eeprom32_address -= 256 ;
        Eeprom32_buffer_address -= 256 ;
        write32_eeprom_block( Eeprom32_address, Eeprom32_buffer_address, 256, EE_NOWAIT ) ;
        Eeprom32_process_state = E32_WRITESENDING ;
      }
      else
      {
        File_system[Eeprom32_file_index].block_no ^= 1 ;        // This is now the current block
#if 0
        // now erase the other block
        File_system[Eeprom32_file_index].block_no ^= 1 ;	// This is now the current block
        eeAddress = Eeprom32_address ^ 0x00001000 ;		// Address of block to erase
        eeprom_write_enable() ;
        p = Spi_tx_buf ;
        *p = 0x20 ;		// Block Erase command
        *(p+1) = eeAddress >> 16 ;
        *(p+2) = eeAddress >> 8 ;
        *(p+3) = eeAddress ;		// 3 bytes address
        spi_PDC_action( p, 0, 0, 4, 0 ) ;
        Eeprom32_process_state = E32_ERASESENDING ;
        Eeprom32_state_after_erase = E32_IDLE ;
#endif
        Eeprom32_process_state = E32_IDLE ;
      }
    }
  }

  if ( Eeprom32_process_state == E32_ERASESENDING )
  {
    if ( Spi_complete )
    {
      Eeprom32_process_state = E32_ERASEWAITING ;
    }
  }
		
  if ( Eeprom32_process_state == E32_ERASEWAITING )
  {
    x = eeprom_read_status() ;
    if ( ( x & 1 ) == 0 )
    { // Command finished
      Eeprom32_process_state = Eeprom32_state_after_erase ;
    }
  }
}

#if defined(SDCARD)
const pm_char * eeBackupModel(uint8_t i_fileSrc)
{
  char *buf = reusableBuffer.modelsel.mainname;
  FIL archiveFile;
  DIR archiveFolder;
  UINT written;

  if (!sdMounted()) {
    return STR_NO_SDCARD;
  }

  // check and create folder here
  strcpy(buf, STR_MODELS_PATH);
  FRESULT result = f_opendir(&archiveFolder, buf);
  if (result != FR_OK) {
    if (result == FR_NO_PATH)
      result = f_mkdir(buf);
    if (result != FR_OK)
      return SDCARD_ERROR(result);
  }

  buf[sizeof(MODELS_PATH)-1] = '/';
  strcpy(strcat_modelname(&buf[sizeof(MODELS_PATH)], i_fileSrc), STR_MODELS_EXT);

  result = f_open(&archiveFile, buf, FA_CREATE_ALWAYS | FA_WRITE);
  if (result != FR_OK) {
    return SDCARD_ERROR(result);
  }

  strcpy(statusLineMsg, PSTR("File "));
  strcpy(statusLineMsg+5, &buf[sizeof(MODELS_PATH)]);

  uint16_t size = File_system[i_fileSrc+1].size;

  *(uint32_t*)&buf[0] = O9X_FOURCC;
  buf[4] = g_eeGeneral.version;
  buf[5] = 'M';
  *(uint16_t*)&buf[6] = size;

  result = f_write(&archiveFile, buf, 8, &written);
  if (result != FR_OK || written != 8) {
    f_close(&archiveFile);
    return SDCARD_ERROR(result);
  }

  read32_eeprom_data( (File_system[i_fileSrc+1].block_no << 12) + sizeof( struct t_eeprom_header), ( uint8_t *)&Eeprom_buffer.data.model_data, size) ;
  result = f_write(&archiveFile, (uint8_t *)&Eeprom_buffer.data.model_data, size, &written);
  f_close(&archiveFile);
  if (result != FR_OK || written != size) {
    return SDCARD_ERROR(result);
  }

  showStatusLine();

  return NULL;
}

const pm_char * eeRestoreModel(uint8_t i_fileDst, char *model_name)
{
  char *buf = reusableBuffer.modelsel.mainname;
  FIL restoreFile;
  UINT read;

  if (!sdMounted()) {
    return STR_NO_SDCARD;
  }

  strcpy(buf, STR_MODELS_PATH);
  buf[sizeof(MODELS_PATH)-1] = '/';
  strcpy(&buf[sizeof(MODELS_PATH)], model_name);
  strcpy(&buf[strlen(buf)], STR_MODELS_EXT);

  FRESULT result = f_open(&restoreFile, buf, FA_OPEN_EXISTING | FA_READ);
  if (result != FR_OK) {
    return SDCARD_ERROR(result);
  }

  if (f_size(&restoreFile) < 8) {
    f_close(&restoreFile);
    return STR_INCOMPATIBLE;
  }

  result = f_read(&restoreFile, (uint8_t *)buf, 8, &read);
  if (result != FR_OK || read != 8) {
    f_close(&restoreFile);
    return SDCARD_ERROR(result);
  }

  if (*(uint32_t*)&buf[0] != O9X_FOURCC || (uint8_t)buf[4] != EEPROM_VER || buf[5] != 'M') {
    f_close(&restoreFile);
    return STR_INCOMPATIBLE;
  }

  uint16_t size = max((uint16_t)sizeof(g_model), *(uint16_t*)&buf[6]);

  if (eeModelExists(i_fileDst)) {
    eeDeleteModel(i_fileDst);
  }

  memset((uint8_t *)&Eeprom_buffer.data.model_data, 0, sizeof(g_model));
  result = f_read(&restoreFile, ( uint8_t *)&Eeprom_buffer.data.model_data, size, &read);
  f_close(&restoreFile);

  if (result != FR_OK || read != read) {
    return STR_INCOMPATIBLE;
  }

  // TODO flash saving ...
  if (read > sizeof(g_model.header.name))
    memcpy(modelHeaders[i_fileDst].name, Eeprom_buffer.data.model_data.header.name, sizeof(g_model.header.name));
  else
    memset(modelHeaders[i_fileDst].name, 0, sizeof(g_model.header.name));

  Eeprom32_source_address = (uint8_t *)&Eeprom_buffer.data.model_data;    // Get data from here
  Eeprom32_data_size = sizeof(g_model);                                   // This much
  Eeprom32_file_index = i_fileDst + 1;                                    // This file system entry
  Eeprom32_process_state = E32_BLANKCHECK;
  eeWaitFinished();

  return NULL;
}
#endif
