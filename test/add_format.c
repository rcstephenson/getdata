/* Copyright (C) 2008-2011, 2013 D. V. Wiebe
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
  int error, n, r = 0;
  DIRFILE *D;
  gd_entry_t E;

  E.field =  "new";
  E.field_type = GD_RAW_ENTRY;
  E.fragment_index = 21;
  E.EN(raw,spf) = 2;
  E.EN(raw,data_type) = GD_UINT8;

  rmdirfile();
  D = gd_open(filedir, GD_RDWR | GD_CREAT);
  gd_add(D, &E);
  error = gd_error(D);

  /* check */
  n = gd_nfields(D);

  gd_discard(D);

  unlink(format);
  rmdir(filedir);

  CHECKI(n,1);
  CHECKI(error, GD_E_BAD_INDEX);

  return r;
}
