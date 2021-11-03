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
  int error, r = 0;
  gd_carray_t *field_list;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0700);

  MAKEFORMATFILE(format, "data4 RAW UINT8 1\n");

  D = gd_open(filedir, GD_RDONLY | GD_VERBOSE);
  field_list = (gd_carray_t*)gd_carrays(D, GD_UINT8);

  error = gd_error(D);

  CHECKI(error, 0);
  CHECKU(field_list[0].n, 0);

  gd_discard(D);
  unlink(format);
  rmdir(filedir);

  return r;
}
