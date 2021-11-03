/* Copyright (C) 2011, 2013, 2017 D.V. Wiebe
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
  const char *format1 = "dirfile/format1";
  const char *format2 = "dirfile/format2";
  int ret, e1, e2, r = 0;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0700);

  MAKEFORMATFILE(format, "B CONST UINT8 1\nINCLUDE format1 A Z\n");
  MAKEFORMATFILE(format1, "/INCLUDE format2 B Y\n");
  MAKEFORMATFILE(format2, "data RAW UINT8 11\n");

  D = gd_open(filedir, GD_RDWR);
  ret = gd_alter_affixes(D, 1, NULL, "");
  e1 = gd_error(D);
  gd_spf(D, "ABdataY");
  e2 = gd_error(D);
  gd_discard(D);

  unlink(format2);
  unlink(format1);
  unlink(format);
  rmdir(filedir);

  CHECKI(ret,0);
  CHECKI(e1,0);
  CHECKI(e2,0);

  return r;
}
