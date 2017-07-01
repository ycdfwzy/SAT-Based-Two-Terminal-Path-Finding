/*++
Copyright (c) 2014 Microsoft Corporation

Module Name:

    simplex.h

Abstract:

    Multi-precision simplex tableau.

Author:

    Nikolaj Bjorner (nbjorner) 2014-01-15

Notes:

--*/

#include"simplex.h"
#include"sparse_matrix_def.h"
#include"simplex_def.h"
namespace simplex {
    template class simplex<mpz_ext>;
    template class simplex<mpq_ext>;
};
