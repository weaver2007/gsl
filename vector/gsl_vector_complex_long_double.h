/* vector/gsl_vector_complex_long_double.h
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Gerard Jungman, Brian Gough
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

#ifndef __GSL_VECTOR_COMPLEX_LONG_DOUBLE_H__
#define __GSL_VECTOR_COMPLEX_LONG_DOUBLE_H__

#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_vector_complex.h>
#include <gsl/gsl_block_complex_long_double.h>

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS

struct gsl_vector_complex_long_double_struct
{
  size_t size;
  size_t stride;
  long double *data;
  gsl_block_complex_long_double *block;
};

typedef struct gsl_vector_complex_long_double_struct gsl_vector_complex_long_double;

gsl_vector_complex_long_double *gsl_vector_complex_long_double_alloc (const size_t n);
gsl_vector_complex_long_double *gsl_vector_complex_long_double_calloc (const size_t n);

gsl_vector_complex_long_double gsl_vector_complex_long_double_view (long double * v, size_t n);

gsl_vector_complex_long_double 
*gsl_vector_complex_long_double_alloc_from_block (gsl_block_complex_long_double * b, 
                                            const size_t offset, 
                                            const size_t n, 
                                            const size_t stride);

gsl_vector_complex_long_double 
*gsl_vector_complex_long_double_alloc_from_vector (gsl_vector_complex_long_double * v, 
                                             const size_t offset, 
                                             const size_t n, 
                                             const size_t stride);

void gsl_vector_complex_long_double_free (gsl_vector_complex_long_double * v);

int gsl_vector_complex_long_double_view_from_vector (gsl_vector_complex_long_double *v, 
                                               gsl_vector_complex_long_double *base,
                                               size_t offset, size_t n, size_t stride);

gsl_vector_complex_long_double gsl_vector_complex_long_double_subvector (gsl_vector_complex_long_double *v, size_t i, size_t n);
gsl_vector_complex_long_double gsl_vector_complex_long_double_subvector_with_stride (gsl_vector_complex_long_double *v, size_t i, size_t n, size_t stride);

const gsl_vector_complex_long_double gsl_vector_complex_long_double_const_subvector (const gsl_vector_complex_long_double *v, size_t i, size_t n);
const gsl_vector_complex_long_double gsl_vector_complex_long_double_const_subvector_with_stride (const gsl_vector_complex_long_double *v, size_t i, size_t n, size_t stride);


gsl_complex_long_double 
*gsl_vector_complex_long_double_ptr (const gsl_vector_complex_long_double * v, size_t i);

gsl_complex_long_double 
gsl_vector_complex_long_double_get (const gsl_vector_complex_long_double * v, const size_t i);

void gsl_vector_complex_long_double_set (gsl_vector_complex_long_double * v, const size_t i,
                                   gsl_complex_long_double z);

void gsl_vector_complex_long_double_set_zero (gsl_vector_complex_long_double * v);
void gsl_vector_complex_long_double_set_all (gsl_vector_complex_long_double * v,
                                       gsl_complex_long_double z);
int gsl_vector_complex_long_double_set_basis (gsl_vector_complex_long_double * v, size_t i);

int gsl_vector_complex_long_double_fread (FILE * stream,
				    gsl_vector_complex_long_double * v);
int gsl_vector_complex_long_double_fwrite (FILE * stream,
				     const gsl_vector_complex_long_double * v);
int gsl_vector_complex_long_double_fscanf (FILE * stream,
				     gsl_vector_complex_long_double * v);
int gsl_vector_complex_long_double_fprintf (FILE * stream,
				      const gsl_vector_complex_long_double * v,
				      const char *format);

int gsl_vector_complex_long_double_memcpy (gsl_vector_complex_long_double * dest, const gsl_vector_complex_long_double * src);

int gsl_vector_complex_long_double_reverse (gsl_vector_complex_long_double * v);

int gsl_vector_complex_long_double_swap (gsl_vector_complex_long_double * v, gsl_vector_complex_long_double * w);
int gsl_vector_complex_long_double_swap_elements (gsl_vector_complex_long_double * v, const size_t i, const size_t j);

int gsl_vector_complex_long_double_isnull (const gsl_vector_complex_long_double * v);

extern int gsl_check_range;

#ifdef HAVE_INLINE

extern inline
gsl_complex_long_double
gsl_vector_complex_long_double_get (const gsl_vector_complex_long_double * v,
			      const size_t i)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= v->size)
    {
      const gsl_complex_long_double zero = {{0, 0}};
      GSL_ERROR_VAL ("index out of range", GSL_EINVAL, zero);
    }
#endif
  return *GSL_COMPLEX_LONG_DOUBLE_AT (v, i);
}

extern inline
void
gsl_vector_complex_long_double_set (gsl_vector_complex_long_double * v,
			      const size_t i, gsl_complex_long_double z)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= v->size)
    {
      GSL_ERROR_VOID ("index out of range", GSL_EINVAL);
    }
#endif
  *GSL_COMPLEX_LONG_DOUBLE_AT (v, i) = z;
}

#endif /* HAVE_INLINE */

__END_DECLS

#endif /* __GSL_VECTOR_COMPLEX_LONG_DOUBLE_H__ */
