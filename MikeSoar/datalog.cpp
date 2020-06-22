/* Modified TrackSoar firmware for M. Patalsky
 * Added datalogging capability to SD card.
 * 6/20/2020 J. Cuiffi, Penn State New Kensington 
 */
// configuration options are set in config.hpp

#include "config.hpp"
#include "datalog.hpp"
#include "gps.hpp"
#include <SD.h>

// Public (extern) variables, readable from other modules
// data file name - to be stored in root dir.
char datafile[15];
// sd card and file write working ok
bool sd_ok;

// create new file with header
bool create_header(){
  File logfile = SD.open(datafile, FILE_WRITE);
  if (!logfile){
    return false;
  } else {
    // write header based on options
    logfile.print("GPS_Time");
    logfile.print(",GPS_Lat");
    logfile.print(",GPS_Lon");
    logfile.print(",GPS_Course_Deg");
    logfile.println("");
    logfile.close();
    return true;
  }
  return false;
}

// write data to file - opens and closes each time
void log_data(){
  File logfile = SD.open(datafile, FILE_WRITE);
  if (logfile){
    // write data based on options
    logfile.print(gps_time);
    logfile.print(",");
    logfile.print(gps_aprs_lat);
    logfile.print(",");
    logfile.print(gps_aprs_lon);
    logfile.print(",");
    logfile.print(gps_course);
    logfile.println("");
    logfile.close();
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
