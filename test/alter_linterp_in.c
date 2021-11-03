/* Copyright (C) 2016, 2017 D.V. Wiebe
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
  gd_entry_t e;
  int ret, e1, e2, e3, r = 0;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0700);

  MAKEFORMATFILE(format, "lut LINTERP data table\n");

  D = gd_open(filedir, GD_RDWR | GD_VERBOSE);
  ret = gd_alter_linterp(D, "lut", "in2", NULL, 0);
  e1 = gd_error(D);
  CHECKI(ret, 0);
  CHECKI(e1, 0);

  gd_entry(D, "lut", &e);
  e2 = gd_error(D);
  CHECKI(e2, 0);
  CHECKS(e.in_fields[0], "in2");
  CHECKS(e.EN(linterp,table), "table");
  gd_free_entry_strings(&e);

  e3 = gd_close(D);
  CHECKI(e3, 0);

  unlink(format);
  rmdir(filedir);

  return r;
}