// Copyright (c) 1995 Darren Vengroff
//
// File: bit_matrix.C
// Author: Darren Vengroff <darrenv@eecs.umich.edu>
// Created: 1/9/95
//

#include <versions.H>
VERSION(bit_matrix_C,"$Id: bit_matrix.C,v 1.1 2008/07/28 17:08:02 m Exp $");

#include <bit_matrix.H>

bit_matrix::bit_matrix(unsigned int rows, unsigned int cols) :
        matrix<bit>(rows, cols)
{
}

bit_matrix::bit_matrix(matrix<bit> &mb) :
        matrix<bit>(mb)
{
}
    
bit_matrix::~bit_matrix(void)
{
}

bit_matrix bit_matrix::operator=(const bit_matrix &rhs) {
    return this->matrix<bit>::operator=((matrix<bit> &)rhs);
}

bit_matrix & bit_matrix::operator=(const TPIE_OS_OFFSET &rhs)
{
    unsigned int rows = this->rows();
    unsigned int ii;

    if (this->cols() != 1) {
#if HANDLE_EXCEPTIONS
        throw matrix_base<bit>::range();
#else
        tp_assert(0, "Range error.");
#endif
    }
    
    for (ii = 0; ii < rows; ii++) {
        (*this)[ii][0] = (long int)(rhs & (1 << ii)) >> ii;
    }
    
    return *this;
}    

bit_matrix::operator TPIE_OS_OFFSET(void)
{
    TPIE_OS_OFFSET res;

    unsigned int rows = this->rows();
    unsigned int ii;

    if (this->cols() != 1) {
#if HANDLE_EXCEPTIONS
        throw matrix_base<bit>::range();
#else
        tp_assert(0, "Range error.");
#endif
    }

    for (res = 0, ii = 0; ii < rows; ii++) {
        res |= (long int)((*this)[ii][0]) << ii;
    }
    
    return res;
}


bit_matrix operator+(const bit_matrix &op1, const bit_matrix &op2)
{
    matrix<bit> sum = ((matrix<bit> &)op1) + ((matrix<bit> &)op2);

    return sum;
}

bit_matrix operator*(const bit_matrix &op1, const bit_matrix &op2)
{
    matrix<bit> prod = ((matrix<bit> &)op1) * ((matrix<bit> &)op2);

    return prod;
}

std::ostream &operator<<(std::ostream &s, bit_matrix &bm)
{
    return s << (matrix<bit> &)bm;
}
