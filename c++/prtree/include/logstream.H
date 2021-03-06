// Copyright (c) 1994 Darren Erik Vengroff
//
// File: logstream.H
// Author: Darren Erik Vengroff <dev@cs.duke.edu>
// Created: 5/12/94
//
// $Id: logstream.H,v 1.1 2008/07/28 17:08:02 m Exp $
//

#ifndef _LOGSTREAM_H
#define _LOGSTREAM_H

// Get definitions for working with Unix and Windows
#include <portability.H>

#include <fstream>

// For size_t
#include <sys/types.h>

// A macro for declaring output operators for log streams.
#define _DECLARE_LOGSTREAM_OUTPUT_OPERATOR(T) logstream& operator<<(T)

// A log is like a regular output stream, but it also supports messages
// at different priorities.  If a message's priority is at least as high
// as the current priority threshold, then it appears in the log.  
// Otherwise, it does not.  Lower numbers have higher priority; 0 is
// the highest.  1 is the default if not 

class logstream : public std::ofstream {

  public:
    static bool log_initialized;
    unsigned int priority;
    unsigned int threshold;

    logstream(const char *fname, unsigned int p = 0, unsigned int tp = 0);
    ~logstream();

    // Output operators

    _DECLARE_LOGSTREAM_OUTPUT_OPERATOR(const char *);
    _DECLARE_LOGSTREAM_OUTPUT_OPERATOR(const char);
    _DECLARE_LOGSTREAM_OUTPUT_OPERATOR(const int);
    _DECLARE_LOGSTREAM_OUTPUT_OPERATOR(const unsigned int);
    _DECLARE_LOGSTREAM_OUTPUT_OPERATOR(const long int);
    _DECLARE_LOGSTREAM_OUTPUT_OPERATOR(const long unsigned int);
    _DECLARE_LOGSTREAM_OUTPUT_OPERATOR(const float);
    _DECLARE_LOGSTREAM_OUTPUT_OPERATOR(const double);
    
    //  WIN32 does not support data type "long long".
    TPIE_OS_UNIX_ONLY_DATA_TYPE_LONG_LONG
};


// The logmanip template is based on the omanip template from iomanip.h 
// in the libg++ sources.

template <class TP> class logmanip {
    logstream& (*_f)(logstream&, TP);
    TP _a;
public:
    logmanip(logstream& (*f)(logstream&, TP), TP a) : _f(f), _a(a) {}

#if (__GNUC__ > 2) || (__GNUC__ == 2 &&  __GNUC_MINOR__ >= 8)
    friend logstream& operator<< <> (logstream& o, const logmanip<TP>& m);
#else
    friend logstream& operator<< (logstream& o, const logmanip<TP>& m);
#endif
};

template <class TP>
logstream& operator<< (logstream& o, const logmanip<TP>& m)
{
  (*m._f)(o, m._a); return o;
}

logmanip<unsigned int> setpriority(unsigned int p);
logmanip<unsigned int> setthreshold(unsigned int p);

#endif // _LOGSTREAM_H 
