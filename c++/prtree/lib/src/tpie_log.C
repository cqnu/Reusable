//
// File: tpie_log.C
// Authors: Darren Erik Vengroff <dev@cs.duke.edu>
//          Octavian Procopiuc <tavi@cs.duke.edu>
// Created: 5/12/94
//

#include <versions.H>
VERSION(tpie_log_C,"$Id: tpie_log.C,v 1.1 2008/07/28 17:08:02 m Exp $");

// We are logging
#define TPL_LOGGING	1

#include <stdlib.h>
#include <time.h>
#include <tpie_tempnam.H>
#include <tpie_log.H>

#define TPLOGPFX "tpielog"

// Local initialization function. Create a permanent repository for the log
// file name. Should be called only once, by theLogName() below.
static char *__tpie_log_name() {
  static char tln[128];
  TPIE_OS_SRANDOM(time(NULL));
  strncpy(tln, tpie_tempnam(TPLOGPFX, TPLOGDIR), 128);
  return tln;
}

char *tpie_log_name() {
  static char *tln = __tpie_log_name();
  return tln;
}


logstream &tpie_log() {
  static logstream log(tpie_log_name(), TPIE_LOG_DEBUG, TPIE_LOG_DEBUG);
  return log;
}

void tpie_log_init(TPIE_LOG_LEVEL level) {
  LOG_SET_THRESHOLD(level);
}
