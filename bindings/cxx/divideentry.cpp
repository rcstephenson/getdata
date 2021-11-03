// Copyright (C) 2010-2011 D. V. Wiebe
//
///////////////////////////////////////////////////////////////////////////
//
// This file is part of the GetData project.
//
// GetData is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// GetData is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with GetData; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
#include "internal.h"

using namespace GetData;

DivideEntry::DivideEntry(const char* field_code, const char* in_field1,
    const char* in_field2, int fragment_index) : Entry()
{
  E.field = strdup(field_code);
  E.field_type = GD_DIVIDE_ENTRY;
  E.in_fields[0] = strdup(in_field1);
  E.in_fields[1] = strdup(in_field2);
  E.fragment_index = fragment_index;
}

int DivideEntry::SetInput(const char* field, int index)
{
  if (index < 0 || index > 1)
    return -1;

  char* ptr = strdup(field);

  if (ptr == NULL)
    return -1;

  free(E.in_fields[index]);
  E.in_fields[index] = ptr;

  if (D != NULL)
    return gd_alter_entry(D->D, E.field, &E, 0);
  
  return 0;
}
