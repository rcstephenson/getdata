function gd_madd_sbit(D, parent, field_code, in_fields, bitnum, numbits)
% GD_MADD_SBIT  Add a SBIT metafield
%
%   GD_MADD_SBIT(DIRFILE,PARENT,NAME,INPUT,BITNUM,NUMBITS)
%             adds a SBIT metafield called NAME under PARENT to the dirfile
%             specified by DIRFILE.  The input field is INPUT, the first bit is
%             BITNUM and the length is NUMBITS.
%
%   The DIRFILE object should have previously been created with GD_OPEN.
%
%   See the documentation on the C API function gd_madd_sbit(3) in section 3
%   of the UNIX manual for more details.
%
%   See also GD_ADD_SBIT, GD_MADD, GD_OPEN

  GD = getdata_constants();
  gd_madd(D, struct('field', field_code, 'field_type', GD.SBIT_ENTRY, ...
  'in_fields', {in_fields}, 'bitnum', bitnum, 'numbits', numbits), parent);
end

% Copyright (C) 2013 D. V. Wiebe
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% This file is part of the GetData project.
%
% GetData is free software; you can redistribute it and/or modify it under
% the terms of the GNU Lesser General Public License as published by the
% Free Software Foundation; either version 2.1 of the License, or (at your
% option) any later version.
%
% GetData is distributed in the hope that it will be useful, but WITHOUT
% ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
% FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
% License for more details.
%
% You should have received a copy of the GNU Lesser General Public License
% along with GetData; if not, write to the Free Software Foundation, Inc.,
% 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
