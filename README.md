THE GETDATA PROJECT
===================

The GetData Project is the reference implementation of the Dirfile Standards.
The Dirfile database format is designed to provide a fast, simple format for
storing and reading binary time-ordered data.  The Dirfile Standards are
described in detail in three Unix manual pages distributed with this package:
dirfile(5), dirfile-format(5) and dirfile-encoding(5), which may be read before
installation by running:

  $ man man/dirfile.5
  $ man man/dirfile-format.5
  $ man man/dirfile-encoding.5

from the top GetData Project directory (the directory containing this README
file).  After installation, they can be read with the standard man command:

  $ man dirfile
  $ man dirfile-format
  $ man dirfile-encoding

More information on the GetData Project and the Dirfile database format may be
found on the World Wide Web:

  http://getdata.sourceforge.net/


WARRANTY AND REDISTRIBUTION
===========================

GetData is free software; you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation: either version 2.1 of the License, or (at your option) any later
version.

GetData is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with GetData in a file called `COPYING'; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA.

The Free Software Foundation has also published the License on the World Wide
Web:

  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html


CONTENTS
========

This package provides:
  * the Dirfile Standards documents (three Unix manual pages)
  * the C GetData library (libgetdata) including Unix manual pages
  * Several utitilities, which also serve as examples of use:
    - checkdirfile, which checks the metadata of a dirfile for problems
    - dirfile2ascii, which can convert all or part of a dirfile to ASCII text
  * several bindings to the library from other languages:
    - C++ (libgetdata++)
    - Fortran 77 (libfgetdata)
    - Fortran 95 (libf95getdata)
    - the Interactive Data Language (IDL; idl_getdata)
    - MATLAB (libgetdata-matlab and associated MEX files)
    - Perl (GetData.pm)
    - Python (pygetdata)

Documentation for the various bindings, if present, can be found in files
named `README.<language>' in the doc/ directory.  The C interface is described
in this document and the associated man pages.

A full list of features new to this release of GetData may be found in the
file called `NEWS'.


DIRFILE STANDARDS VERSION 10
============================

The 0.10.0 release of the GetData Library (January 2017) is the first release to
provide suuport the latest version of the Dirfile Standards, known as Standards
Version 10.

Standards Version 10 introduces the following:
  * Three new field types: INDIR, SARRAY, and SINDIR.
  * Field code namespaces.
  * A new representation suffix, .z, which does nothing, which is occasionally
    needed for disambiguation of syntax.
  * Support for FLAC (Free Lossless Audio Compression) encoding of data.
    (FLAC has been supported by GetData since 0.9.0.)

This is the first update to the Dirfile Standards since Standards Version 9
(July 2012).  A full history of the Dirfile Standards can be found in the
dirfile-format(5) man page.


BUILDING THE LIBRARY
====================

This package may be configured and built using the GNU autotools.  Generic
installation instructions are provided in the file called `INSTALL'.  A brief
summary follows.  If a C99-compliant compiler is used to build the pacakge,
the library will be built with both a C99 API (the default) as well as a ANSI
C (C89) API.  If the compiler used to build the library is not C99-compliant,
only the ANSI C API will be built.

Most users should be able to build the package by simply executing:

  $ ./configure
  $ make

from the top GetData Project directory (the directory containing this README
file).  After the project has been built, you may (optionally) test the build by
executing:

  $ make check

which will run a series of self-tests.  Finally,

  $ make install

will install the utilities, libraries, bindings, and documentation.

The package configuration can be changed, if the default configuration is
insufficient, before building it by passing options to ./configure.  Running

  $ ./configure --help

will display a brief help message summarising available options.

---
**Note** 
> I run:
> $ ./configure --disable-fortran --disable-fortran95 --disable-idl --disable-matlab --disable-perl --disable-php
---

PREREQUISITES
=============

The only library required to build GetData is the C Standard Library.  Several
other external will be used if found by ./configure to provide support for
various data encodings (typically compression schemes).  These are:

- the bzip2 compression library by Julian Seward;
- the libFLAC library by Josh Coalson and the Xiph.Org Foundation;
- the lzma library, part of the XZ Utils suite by Lasse Collin, Ville Koskinen,
  and Igor Pavlov;
- the slim compression library by Joseph Fowler;
- the zlib library by Jean-loup Gailly and Mark Adler; and,
- the zzip library by Tomi Ollila and Guido Draheim.

If these libraries are not found by configure, GetData will lack support for
the associated encoding scheme and fail gracefully if encountering dirfiles so
encoded.

GetData has optional support for regular expression matching of field names.
This support is implemented through the use of two additional libraries,
specifically:

- the POSIX standard regex(7) library (providing regcomp(3) and regexec(3)),
  originally written by Henry Spencer.  On most platforms, this is bundled
  with the C Standard Library.
- the Perl-Compatible Regular Expression (PCRE) library by Philip Hazel.

If these libraries are not found at build time, partial or all regular
expression support will be missing from the library: the appropriate GetData
API (gd_match_entries) will exist, but attempting to preform a regex search
will fail.

Building bindings requires appropriate compilers/interpreters and libraries for
the various languages.  In particular:

- the C++ bindings require a C++90-compliant compiler
- the Fortran-77 bindings require a Fortran-77 compliant compiler
- the Fortran-95 bindings require both a Fortran-95 compliant compiler and a
  Fortran-77 compiler, because the Fortran-95 bindings are built on top of
  the Fortran-77 bindings;
- the IDL bindings require a licenced IDL interpreter, version 5.5 or later;
  they will not work on an unlicenced interpreter in timed demo mode
- the MATLAB bindings require both a MATLAB interpreter and a MEX compiler
- the Perl bindings require a Perl5 interpreter version 5.6 or later, as well
  as the Math::Complex module.
- the PHP bindings support both PHP5 and PHP7.
- the Python bindings support both Python2, from version 2.4, as well as
  Python3, from version 3.2.


USING THE LIBRARY
=================

To use the library in C programs, the header file getdata.h should be included.
This file declares all the various APIs provided by the library.  Programs
linking to static versions of the GetData library need to be linked against the
C Standard Math Library, in addition to GetData itself, plus any other libraries
required to support the compiled regular expression functionality and encodings
supported by the library.

The various small programs in the `util' subdirectory of the package provide
examples of use.

The checkdirfile utility was designed to report syntax errors in the format
file(s) of the large, complex dirfiles used in the analysis of the BLAST
experiment data.  This utility will report all syntax errors it find in the
supplied dirfile, plus any problems in the metadata itself.

Bindings exist for using the GetData library in languages other than C.  If
language bindings exist for your particular library, a README.<language> file
explaining its use should be present in the `doc' subdirectory.

If no bindings exist for your language of choice, you will have to write your
own.  If you are willing to have these bindings redistributed under identical
terms as the GetData Project, we encourage you to submit them for inclusion in
the package.


ENCODING MODULES
================

Encoding schemes which rely on optional external libraries (slim, gzip, bzip2,
&c.) may be built as stand-alone library modules which will be dynamically
loaded, as needed, at runtime by the core GetData library.  This is the
default behaviour in GetData-0.10.  In earlier versions, by default the
encoding support was built directly into the core GetData library.

External modules are used primarily to permit packaging the core GetData library
separately from the parts of the library requiring the optional external
libraries without having to give up the functionality these extra libraries
provide.  To enable this behaviour, pass `--enable-modules' to ./configure.

The modules are dynamically loaded via GNU libtool's portable dlopen wrapper
library, libltdl.  The libltdl library permits dynamic loading of modules on at
least Solaris, Linux, BSD, HP-UX, Win16, Win32, BeOS, Darwin, MacOS X.  It can
usually be found as part of the GNU libtool package on any modern GNU system,
or else obtained for free from the GNU Project.

GetData will fail gracefully if a library module is not found or cannot be
opened at runtime.  In this case, the call which triggered the attempt to load
the module will fail with the GD_E_UNSUPPORTED error.

The POSIX dlopen library (and, by extension, libltdl) is notoriously not thread
safe.  As a result, if a POSIX thread implementation can be found, calls to the
dynamic loader will be wrapped in a mutex.


THE GETDATA HEADER FILE
=======================

The GetData header file, `getdata.h', installed in ${prefix}/include, declares
the new API.  It also includes `getdata_legacy.h' (also installed) which
declares the legacy API.  The legacy header should never be included directly.
Defining the preprocessor symbol `GD_NO_LEGACY_API' before including getdata.h
will prevent the legacy API from being declared.  In cases when the legacy API
is declared, getdata.h will define the symbol GD_LEGACY_API, which can be used
by callers to determine whether the legacy API is present at compile time.

If the legacy API is not built (as a result of passing `--disable-legacy-api'
to ./configure), getdata_legacy.h will not be installed, and the legacy API will
never be declared.

The default GetData API makes use of C99 features.  An ANSI C API is also
available and can be used by defining GD_C89_API before including getdata.h.  If
GetData was built without a C99-compliant compiler, the C99 API will be missing.
In this case, the ANSI C API will be enabled by default (as if GD_C89_API were
always defined) and, furthermore, getdata.h will define the symbol GD_NO_C99_API
to indicate this.


LARGEFILE SUPPORT
=================

The default GetData API uses the standard C type off_t for frame and sample
offsets into the database.  To overcome the addressable limit imposed by a
32-bit off_t, GetData provides an optional API for largefile support. Defining
GD_64BIT_API before including getdata.h will define the 64-bit type
gd_off64_t, as well as declare additional functions that use this 64-bit type.
If the platform provides off64_t, the GetData type will be simply that.

On platforms where off_t is 64-bits wide, this API may still be useful for
portable programming; in this case gd_off64_t is simply off_t. On some
platforms this API may be automatically enabled; in this case, the symbol
GD_64BIT_API is ignored.

The explicit 64-bit functions this API declares are:

  * gd_alter_frameoffset64
  * gd_bof64
  * gd_eof64
  * gd_framenum_subset64
  * gd_frameoffset64
  * gd_getdata64
  * gd_nframes64
  * gd_putdata64
  * gd_seek64
  * gd_tell64 

These functions behave identically to the versions without the -64 suffix,
except they use gd_off64_t in place of off_t. 


AUTHOR
======

The Dirfile Standards and the GetData library were conceived and written by
C. B. Netterfield <netterfield@astro.utoronto.ca>.

Since Standards Version 3 (January 2006), the Dirfile Standards and GetData
have been maintained by D. V. Wiebe <dvw@ketiltrout.net>.

A full list of contributors is given in the file called `AUTHORS'.
