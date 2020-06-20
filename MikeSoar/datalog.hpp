/* Modified TrackSoar firmware for M. Patalsky
 * Added datalogging capability to SD card.
 * 6/20/2020 J. Cuiffi, Penn State New Kensington 
 */
// configuration options are set in config.hpp
#ifndef __DATALOG_H__
  #define _DATALOG_H__
  
  // data file name - to be stored in root dir.
  extern char datafile[15];
  extern bool sd_ok;
  
  // initialize data file
  void datalog_setup();
  // write data to file
  void log_data();

#endif
