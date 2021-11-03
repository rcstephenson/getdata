/* Copyright (C) 2014, 2017 D.V. Wiebe
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
#ifndef TEST_LZMA
  return 77;
#else
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  const char *data_lzma = "dirfile/data.lzma";
  const char *data = "dirfile/data";
  uint8_t c[8] = {40, 41, 42, 43, 44, 45, 46, 47};
  char command[4096];
  int n, e1, e2, r = 0;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0700);

  MAKEFORMATFILE(format, "data RAW UINT8 8\n");
  MAKEDATAFILE(data, uint8_t, i, 256);

  /* compress */
  snprintf(command, 4096, "%s -F lzma -f %s > /dev/null", XZ, data);
  if (gd_system(command))
    return 1;

  D = gd_open(filedir, GD_RDWR);
  n = gd_putdata(D, "data", 5, 0, 1, 0, GD_UINT8, c);
  e1 = gd_error(D);
  CHECKI(e1, GD_E_UNSUPPORTED);
  CHECKI(n, 0);

  e2 = gd_discard(D);
  CHECKI(e2, 0);

  unlink(data_lzma);
  unlink(format);
  rmdir(filedir);

  return r;
#endif
}
