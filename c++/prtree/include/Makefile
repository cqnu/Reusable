# Generated automatically from Makefile.in by configure.
# Makefile for the TPIE include directory.
# $Id: Makefile,v 1.1 2008/07/28 17:08:01 m Exp $

CAT=cat
CP=cp
INDENT= 
INDENTFLAGS= 
PERL=
#ETAGS=etags

# Build the header file that will actually be used by using the
# C preprocessor to expand all of the macros in the source file.
# We can either use the macro definitions directly, or expand them and
# filter the results through GNU indent.  The latter approach makes 
# them more readable for debugging purposes, but since most people don't
# have GNU indent, the configure script turns it off by default.
EXPAND_AMI_SCAN_H = no

# Public targets.

all: ami_scan.H

clean:
	-rm -f ami_scan.H

distclean: clean

# Private targets.

ifeq ($(EXPAND_AMI_SCAN_H),yes)
ami_scan.H: ami_scan_mac.C ami_scan_mac.H ami_scan.H.head ami_scan.H.tail
	$(CAT) ami_scan.H.head > $@
	$(CXX) -E $< | $(INDENT) $(INDENTFLAGS) - | grep -v "^#" | \
	    $(PERL) -e \
	    'while (<>) { print "\n" if /template/; print if /.+/; }' >> $@
	$(CAT) ami_scan.H.tail >> $@
else
ami_scan.H: ami_scan_mac.H ami_scan.H.head ami_scan.H.tail
	cat ami_scan.H.head ami_scan_mac.H ami_scan.H.tail > $@
endif

.PHONY : all clean

