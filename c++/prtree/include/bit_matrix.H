// Copyright (c) 1994 Darren Vengroff
//
// File: bit_matrix.H
// Author: Darren Vengroff <darrenv@eecs.umich.edu>
// Created: 11/4/94
//
// $Id: bit_matrix.H,v 1.1 2008/07/28 17:08:02 m Exp $
//
#ifndef _BIT_MATRIX_H
#define _BIT_MATRIX_H

// Get definitions for working with Unix and Windows
#include <portability.H>

#include <bit.H>
#include <matrix.H>

#include <sys/types.h>


// typedef matrix<bit> bit_matrix_0;

class bit_matrix : public matrix<bit> {
public:
    bit_matrix::bit_matrix(matrix<bit> &mb);
    bit_matrix(unsigned int rows, unsigned int cols);
    virtual ~bit_matrix(void);

    bit_matrix operator=(const bit_matrix &rhs);
    
    // We can assign from an offset, which is typically a source
    // address for a BMMC permutation.
    bit_matrix &operator=(const TPIE_OS_OFFSET &rhs);

    operator TPIE_OS_OFFSET(void);

    friend bit_matrix operator+(const bit_matrix &op1, const bit_matrix &op2);
    friend bit_matrix operator*(const bit_matrix &op1, const bit_matrix &op2);
};

bit_matrix operator+(const bit_matrix &op1, const bit_matrix &op2);
bit_matrix operator*(const bit_matrix &op1, const bit_matrix &op2);

std::ostream &operator<<(std::ostream &s, bit_matrix &bm);

#endif // _BIT_MATRIX_H 
