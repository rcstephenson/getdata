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
/* Attempt to read little-endian FLOAT32 */
#include "test.h"

int main(void)
{
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  const char *data = "dirfile/data";
  float u[10];
  float v[20];
  const unsigned char data_data[128 * 4] = {
    0x00, 0x00, 0xC0, 0x3F,  0x00, 0x00, 0x10, 0x40,
    0x00, 0x00, 0x58, 0x40,  0x00, 0x00, 0xA2, 0x40,
    0x00, 0x00, 0xF3, 0x40,  0x00, 0x40, 0x36, 0x41,
    0x00, 0xB0, 0x88, 0x41,  0x00, 0x08, 0xCD, 0x41,
    0x00, 0xC6, 0x19, 0x42,  0x00, 0xA9, 0x66, 0x42,
    0xC0, 0xFE, 0xAC, 0x42,  0x10, 0xBF, 0x01, 0x43,
    0x98, 0x9E, 0x42, 0x43,  0xF2, 0xF6, 0x91, 0x43,
    0x6B, 0xF2, 0xDA, 0x43,  0xD0, 0x35, 0x24, 0x44,
    0xB8, 0x50, 0x76, 0x44,  0x8A, 0xBC, 0xB8, 0x44,
    0x68, 0x8D, 0x0A, 0x45,  0x1C, 0xD4, 0x4F, 0x45,
    0x15, 0xDF, 0x9B, 0x45,  0xA0, 0xCE, 0xE9, 0x45,
    0xF8, 0x5A, 0x2F, 0x46,  0x3A, 0x84, 0x83, 0x46,
    0x57, 0x46, 0xC5, 0x46,  0xC1, 0xF4, 0x13, 0x47,
    0x22, 0xEF, 0x5D, 0x47,  0x5A, 0x73, 0xA6, 0x47,
    0x07, 0xAD, 0xF9, 0x47,  0xC5, 0x41, 0x3B, 0x48,
    0x54, 0x71, 0x8C, 0x48,  0xFE, 0xA9, 0xD2, 0x48,
    0x7E, 0xFF, 0x1D, 0x49,  0x3D, 0xFF, 0x6C, 0x49,
    0x6E, 0xBF, 0xB1, 0x49,  0x92, 0x4F, 0x05, 0x4A,
    0x5B, 0xF7, 0x47, 0x4A,  0x84, 0xF9, 0x95, 0x4A,
    0x46, 0xF6, 0xE0, 0x4A,  0xB4, 0xB8, 0x28, 0x4B,
    0x0E, 0x15, 0x7D, 0x4B,  0xCA, 0xCF, 0xBD, 0x4B,
    0xD8, 0x5B, 0x0E, 0x4C,  0xC4, 0x89, 0x55, 0x4C,
    0x53, 0x27, 0xA0, 0x4C,  0xFC, 0x3A, 0xF0, 0x4C,
    0x3D, 0x2C, 0x34, 0x4D,  0x2E, 0x21, 0x87, 0x4D,
    0xC5, 0xB1, 0xCA, 0x4D,  0x54, 0x05, 0x18, 0x4E,
    0xFE, 0x07, 0x64, 0x4E,  0xFE, 0x05, 0xAB, 0x4E,
    0x7E, 0x44, 0x00, 0x4F,  0xBD, 0x66, 0x40, 0x4F,
    0x0E, 0x4D, 0x90, 0x4F,  0x95, 0x73, 0xD8, 0x4F,
    0xB0, 0x56, 0x22, 0x50,  0x08, 0x82, 0x73, 0x50,
    0x86, 0xA1, 0xB6, 0x50,  0x24, 0xF9, 0x08, 0x51,
    0xB6, 0x75, 0x4D, 0x51,  0x48, 0x18, 0x9A, 0x51,
    0x6C, 0x24, 0xE7, 0x51,  0x51, 0x5B, 0x2D, 0x52,
    0x7D, 0x04, 0x82, 0x52,  0xBC, 0x06, 0xC3, 0x52,
    0x0D, 0x45, 0x12, 0x53,  0x94, 0x67, 0x5B, 0x53,
    0xAF, 0x8D, 0xA4, 0x53,  0x86, 0xD4, 0xF6, 0x53,
    0x64, 0x1F, 0x39, 0x54,  0x8B, 0xD7, 0x8A, 0x54,
    0x50, 0x43, 0xD0, 0x54,  0x7C, 0x32, 0x1C, 0x55,
    0xBA, 0x4B, 0x6A, 0x55,  0xCC, 0xB8, 0xAF, 0x55,
    0x99, 0xCA, 0x03, 0x56,  0xE6, 0xAF, 0x45, 0x56,
    0xEC, 0x43, 0x94, 0x56,  0xE2, 0x65, 0xDE, 0x56,
    0x6A, 0xCC, 0x26, 0x57,  0x9F, 0x32, 0x7A, 0x57,
    0xF7, 0xA5, 0xBB, 0x57,  0x79, 0xBC, 0x0C, 0x58,
    0xB6, 0x1A, 0x53, 0x58,  0x08, 0x54, 0x9E, 0x58,
    0x0C, 0x7E, 0xED, 0x58,  0x89, 0x1E, 0x32, 0x59,
    0xE7, 0x96, 0x85, 0x59,  0x5A, 0x62, 0xC8, 0x59,
    0xC4, 0x49, 0x16, 0x5A,  0xA6, 0x6E, 0x61, 0x5A,
    0xFC, 0x12, 0xA9, 0x5A,  0x7A, 0x9C, 0xFD, 0x5A,
    0x5C, 0x35, 0x3E, 0x5B,  0x05, 0xA8, 0x8E, 0x5B,
    0x08, 0xFC, 0xD5, 0x5B,  0x06, 0x7D, 0x20, 0x5C,
    0x89, 0xBB, 0x70, 0x5C,  0xA7, 0x8C, 0xB4, 0x5C,
    0x7D, 0x69, 0x07, 0x5D,  0x3C, 0x1E, 0x4B, 0x5D,
    0xAD, 0x56, 0x98, 0x5D,  0x04, 0x82, 0xE4, 0x5D,
    0x83, 0x61, 0x2B, 0x5E,  0x22, 0x89, 0x80, 0x5E,
    0xB3, 0xCD, 0xC0, 0x5E,  0x46, 0x9A, 0x10, 0x5F,
    0x69, 0xE7, 0x58, 0x5F,  0x8F, 0xAD, 0xA2, 0x5F,
    0x56, 0x04, 0xF4, 0x5F,  0x40, 0x03, 0x37, 0x60,
    0x70, 0x42, 0x89, 0x60,  0xA8, 0xE3, 0xCD, 0x60,
    0xBE, 0x6A, 0x1A, 0x61,  0x1D, 0xA0, 0x67, 0x61,
    0x16, 0xB8, 0xAD, 0x61,  0x10, 0x4A, 0x02, 0x62,
    0x18, 0x6F, 0x43, 0x62,  0x52, 0x93, 0x92, 0x62,
    0xFB, 0xDC, 0xDB, 0x62,  0xBC, 0xE5, 0x24, 0x63,
    0x9A, 0x58, 0x77, 0x63,  0x74, 0x82, 0xB9, 0x63,
    0xD7, 0x21, 0x0B, 0x64,  0xC2, 0xB2, 0x50, 0x64,
    0x12, 0x86, 0x9C, 0x64,  0x1B, 0xC9, 0xEA, 0x64
  };
  int fd, i, n, error, r = 0;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0700); 

  v[0] = 1.5;
  for (i = 1; i < 20; ++i)
    v[i] = v[i - 1] * 1.5;

  MAKEFORMATFILE(format, "data RAW FLOAT32 1\nENDIAN little\n");

  fd = open(data, O_CREAT | O_EXCL | O_WRONLY | O_BINARY, 0666);
  write(fd, data_data, 128 * sizeof(float));
  close(fd);

  D = gd_open(filedir, GD_RDONLY | GD_VERBOSE);
  n = gd_getdata(D, "data", 5, 0, 0, 10, GD_FLOAT32, u);
  error = gd_error(D);

  gd_discard(D);

  unlink(data);
  unlink(format);
  rmdir(filedir);

  CHECKI(error, 0);
  CHECKI(n, 10);

  for (i = 0; i < 10; ++i)
    CHECKFi(i, u[i], v[i + 5]);

  return r;
}
