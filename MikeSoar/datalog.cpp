/* Modified TrackSoar firmware for M. Patalsky
 * Added datalogging capability to SD card.
 * 6/20/2020 J. Cuiffi, Penn State New Kensington 
 */
// configuration options are set in config.hpp

#include "config.hpp"
#include "datalog.hpp"
#include <SD.h>

// create new file with header
bool create_header(){
  File logfile = SD.open(datafile, FILE_WRITE);
  if (!logfile){
    return false;
  } else {
    // write header based on options
    logfile.print("title1");
    logfile.print(",title2");
    logfile.println("");
  }
}


// initialize data file - creates unique name if exists
void datalog_setup(){
  sd_ok = false;
  if (SD.begin(SD_PIN)){
    // open a new file - appends numbers in case file exists
    strcpy(datafile, "DATA00.csv");
    for (uint8_t i = 0; i < 100; i++) {
    datafile[4] = '0' + i/10;
    datafile[5] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
      if (! SD.exists(datafile)) {
        if(create_header()){
          sd_ok = true;
        }
        break;
      }
    }    
  } else {
    sd_ok = false;
  }
  return;
}


// write data to file - opens and closes each time
void log_data(){
  return;
}
