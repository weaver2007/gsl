/* Author:  G. Jungman
 * RCS:     $Id$
 */
/* Low level tridiagonal solvers.
 * Used internally in other areas of GSL.
 */
#ifndef __GSL_TRIDIAG_H__
#define __GSL_TRIDIAG_H__

#include <stdlib.h>

static
int solve_tridiag(
  const double diag[], size_t d_stride,
  const double offdiag[], size_t o_stride,
  const double b[], size_t b_stride,
  double x[], size_t x_stride,
  size_t N
  );

static
int solve_cyc_tridiag(
  const double diag[], size_t d_stride,
  const double offdiag[], size_t o_stride,
  const double b[], size_t b_stride,
  double x[], size_t x_stride,
  size_t N
  );


#endif /* __GSL_TRIDIAG_H__ */
