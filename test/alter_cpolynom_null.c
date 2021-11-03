/* Copyright (C) 2013, 2017 D.V. Wiebe
 *
 ***************************************************************************
 *
 * This file is part of the GetData project.
 *
 * GetData is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * GetData is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with GetData; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "test.h"

int main(void)
{
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  int i, ret, error, n, error2, r = 0;
  gd_entry_t E;
#ifdef GD_NO_C99_API
  const double a[2][2] = {{1, 2}, {2, 3}};
#endif
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0700);

  MAKEFORMATFILE(format,
    "data RAW INT32 8\n"
    "polynom POLYNOM data 1;2 2;3 1;9\n"
  );

  D = gd_open(filedir, GD_RDWR | GD_VERBOSE);
  ret = gd_alter_cpolynom(D, "polynom", 1, NULL, NULL);
  error = gd_error(D);

  CHECKI(error,0);

  n = gd_entry(D, "polynom", &E);
  error2 = gd_error(D);

  gd_discard(D);

  CHECKS(E.field, "polynom");
  CHECKI(E.field_type, GD_POLYNOM_ENTRY);
  CHECKI(E.EN(polynom,poly_ord), 1);
  CHECKX(E.flags, GD_EN_COMPSCAL | GD_EN_CALC);
  CHECKS(E.in_fields[0], "data"); 

  for (i = 0; i < 2; ++i) {
#ifdef GD_NO_C99_API
    CHECKCi(i,E.EN(polynom,ca)[i], a[i]);
#else
    CHECKCi(i,E.EN(polynom,ca)[i], i + 1 + _Complex_I * (i + 2));
#endif
  }

  unlink(format);
  rmdir(filedir);

  CHECKI(error2,0);
  CHECKI(n,0);
  CHECKI(ret,0);
  gd_free_entry_strings(&E);

  return r;
}
