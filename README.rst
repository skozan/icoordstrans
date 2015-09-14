ICOORDSTRANS
------------

.. attention::
   This project is highly unmaintained and is kept for historical
   reasons.  Most operations provided by this library are covered by
   the free software "Proj4". However it can be still useful for some
   transforms between old Greek system - Hatt and modern reference
   systems.

- Some technical reference written in Greek can be found here__.
- Download `win32 binaries`__ 
- Some `excel file`__ that takes advantage of the DLL and
  `another one`__ with Hatt transforms. `Autonomous`__ software for
  transforms, requires the DLL.

__ http://users.itia.ntua.gr/soulman/icoordstrans/
__ http://users.itia.ntua.gr/soulman/icoordstrans/icoordstrans.dll
__ http://users.itia.ntua.gr/soulman/icoordstrans/gr87transformsV2.xls
__ http://users.itia.ntua.gr/soulman/icoordstrans/gr87transformsHatt.xls
__ http://users.itia.ntua.gr/soulman/icoordstrans/test_program.zip

.. note::
   According to users, in order win32 binary to work with newer
   (64bit?) versions of Microsoft Excel, dll should be placed in:
   ``C:\Program Files (x86)\Microsoft Office\Office12``. This
   is untested by me.

Software library for geodetic transformations on earth
ellipsoidal surface.

Copyright 2006, Stefanos Kozanis

Library is distributed as a Public Domain software with
no terms.


C code compiles under Microsoft Visual C++ 6. I suppose
that it compiles under any C compiler with few
modifications on the code. A Makefile is included,
I have tested it on a Linux system with gcc.

Stefanos Kozanis
October, 3 2006
