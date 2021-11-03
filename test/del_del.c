/* Copyright (C) 2008-2011, 2013, 2017 D.V. Wiebe
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
  const char *data = "dirfile/data";
  unsigned char c[8];
  int fd, ret, e1, n, e2, e3, r = 0;
  DIRFILE *D;

  memset(c, 0, 8);
  rmdirfile();
  mkdir(filedir, 0700);

  MAKEFORMATFILE(format, "data RAW UINT8 8\n");
  MAKEDATAFILE(data, unsigned char, i, 256);

  D = gd_open(filedir, GD_RDWR);
  ret = gd_delete(D, "data", 0);
  e1 = gd_error(D);
  CHECKI(ret, 0);
  CHECKI(e1, GD_E_OK);

  n = gd_getdata(D, "data", 5, 0, 1, 0, GD_UINT8, c);
  e2 = gd_error(D);
  CHECKI(n, 0);
  CHECKI(e2, GD_E_BAD_CODE);

  e3 = gd_discard(D);
  CHECKI(e3, 0);

  fd = unlink(data);
  unlink(format);
  rmdir(filedir);
  CHECKI(fd, 0);

  return r;
}
