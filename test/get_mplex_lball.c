/* Copyright (C) 2012-2013, 2017 D.V. Wiebe
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
  const char *count = "dirfile/count";
  unsigned char c[8];
  int n, i, e1, e2, r = 0;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0700);

  MAKEFORMATFILE(format,
    "mplex MPLEX data count 7 8\n"
    "count RAW UINT8 8\n"
    "data RAW UINT8 8\n"
  );
  MAKEDATAFILE(data, unsigned char, i ? i : 111, 256);
  MAKEDATAFILE(count, unsigned char, i ? i % 3 : 7, 256);

  D = gd_open(filedir, GD_RDONLY | GD_VERBOSE);
  gd_mplex_lookback(D, GD_LOOKBACK_ALL);
  e1 = gd_error(D);
  n = gd_getdata(D, "mplex", 12, 0, 1, 0, GD_UINT8, &c);
  e2 = gd_error(D);

  gd_discard(D);

  unlink(count);
  unlink(data);
  unlink(format);
  rmdir(filedir);

  CHECKI(e1, 0);
  CHECKI(e2, 0);
  CHECKI(n, 8);
  for (i = 0; i < 8; ++i)
    CHECKIi(i, c[i], 111);

  return r;
}