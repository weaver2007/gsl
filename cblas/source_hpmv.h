/* blas/source_hpmv.h
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Gerard Jungman
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * Author:  G. Jungman
 * RCS:     $Id$
 */

{
  int conj = (order == CblasColMajor) ? -1 : 1;
    size_t i, j;

    const double alpha_real = REAL0(alpha), alpha_imag = IMAG0(alpha);
    const double beta_real = REAL0(beta), beta_imag = IMAG0(beta);

    if ((alpha_real == 0.0 && alpha_imag == 0.0)
	&& (beta_real == 1.0 && beta_imag == 0.0))
	return;

    /* form  y := beta*y */
    if (beta_real == 0.0 && beta_imag == 0.0) {
      size_t iy = OFFSET(N, incY);
      for (i = 0; i < N; i++) {
	REAL(Y, iy) = 0.0;
	IMAG(Y, iy) = 0.0;
	iy += incY;
      }
    } else if (!(beta_real == 1.0 && beta_imag == 0.0)) {
      size_t iy = OFFSET(N, incY);
      for (i = 0; i < N; i++) {
	const BASE y_real = REAL(Y, iy);
	const BASE y_imag = IMAG(Y, iy);
	const BASE tmpR = y_real * beta_real - y_imag * beta_imag;
	const BASE tmpI = y_real * beta_imag + y_imag * beta_real;
	REAL(Y, iy) = tmpR;
	IMAG(Y, iy) = tmpI;
	iy += incY;
      }
    }

    if (alpha_real == 0.0 && alpha_imag == 0.0)
	return;

    /* form  y := alpha*A*x + y */

    if ((order == CblasRowMajor && Uplo == CblasUpper)
        || (order == CblasColMajor && Uplo == CblasLower)) {

      size_t ix = OFFSET(N, incX);
      size_t iy = OFFSET(N, incY);
      for (i = 0; i < N; i++) {
        BASE x_real = REAL(X, ix);
        BASE x_imag = IMAG(X, ix);
        BASE temp1_real = alpha_real * x_real - alpha_imag * x_imag;
        BASE temp1_imag = alpha_real * x_imag + alpha_imag * x_real;
        BASE temp2_real = 0.0;
        BASE temp2_imag = 0.0;
        const size_t j_min = i + 1;
        const size_t j_max = N;
        size_t jx = OFFSET(N, incX) + j_min * incX;
        size_t jy = OFFSET(N, incY) + j_min * incY;
        BASE Aii_real = REAL(Ap, TPUP(N, i, i));
        /* Aii_imag is zero */
        REAL(Y, iy) += temp1_real * Aii_real;
        IMAG(Y, iy) += temp1_imag * Aii_real;
        for (j = j_min; j < j_max; j++) {
          BASE Aij_real = REAL(Ap, TPUP(N, i, j));
          BASE Aij_imag = conj * IMAG(Ap, TPUP(N, i, j));
          REAL(Y, jy) += temp1_real * Aij_real - temp1_imag * (-1.0) * Aij_imag;
          IMAG(Y, jy) += temp1_real * (-1.0) * Aij_imag + temp1_imag * Aij_real;
          x_real = REAL(X, jx);
          x_imag = IMAG(X, jx);
          temp2_real += x_real * Aij_real - x_imag * Aij_imag;
          temp2_imag += x_real * Aij_imag + x_imag * Aij_real;
          jx += incX;
          jy += incY;
        }
        REAL(Y, iy) += alpha_real * temp2_real - alpha_imag * temp2_imag;
        IMAG(Y, iy) += alpha_real * temp2_imag + alpha_imag * temp2_real;
        ix += incX;
        iy += incY;
      }
} else if ((order == CblasRowMajor && Uplo == CblasLower)
           || (order == CblasColMajor && Uplo == CblasUpper)) {

      size_t ix = OFFSET(N, incX);
      size_t iy = OFFSET(N, incY);
      for (i = 0; i < N; i++) {
        BASE x_real = REAL(X, ix);
        BASE x_imag = IMAG(X, ix);
        BASE temp1_real = alpha_real * x_real - alpha_imag * x_imag;
        BASE temp1_imag = alpha_real * x_imag + alpha_imag * x_real;
        BASE temp2_real = 0.0;
        BASE temp2_imag = 0.0;
        const size_t j_min = 0;
        const size_t j_max = i;
        size_t jx = OFFSET(N, incX) + j_min * incX;
        size_t jy = OFFSET(N, incY) + j_min * incY;
        BASE Aii_real = REAL(Ap, TPLO(N, i, i));
        /* Aii_imag is zero */
        REAL(Y, iy) += temp1_real * Aii_real;
        IMAG(Y, iy) += temp1_imag * Aii_real;
        for (j = j_min; j < j_max; j++) {
          BASE Aij_real = REAL(Ap, TPLO(N, i, j));
          BASE Aij_imag = conj * IMAG(Ap, TPLO(N, i, j));
          REAL(Y, jy) += temp1_real * Aij_real - temp1_imag * (-1.0) * Aij_imag;
          IMAG(Y, jy) += temp1_real * (-1.0) * Aij_imag + temp1_imag * Aij_real;
          x_real = REAL(X, jx);
          x_imag = IMAG(X, jx);
          temp2_real += x_real * Aij_real - x_imag * Aij_imag;
          temp2_imag += x_real * Aij_imag + x_imag * Aij_real;
          jx += incX;
          jy += incY;
        }
        REAL(Y, iy) += alpha_real * temp2_real - alpha_imag * temp2_imag;
        IMAG(Y, iy) += alpha_real * temp2_imag + alpha_imag * temp2_real;
        ix += incX;
        iy += incY;
      }

} else {
      BLAS_ERROR ("unrecognized operation");
}
}



