SHA-1 Cracker
=============
This is a C program to brute force the EngineYard SHA-1 hashing competition
that was run on July 20-21, 2009.

http://www.engineyard.com/blog/2009/programming-contest-win-iphone-3gs-2k-cloud-credit/

The purpose of this program is not to have a maximally optimized cracker, but
rather to see what could be done with reasonable design and minimal
optimization.

This code is free software licensed under the 3-Clause BSD license.  See main.c
for the full license text.

Compiling
---------
Compilation was tested with gcc on Linux and Windows (under Cygwin).  OpenSSL
is required to compile and run.  To compile, use these commands:

Linux:
gcc main.c -lssl -O3

Windows:
gcc main.c -lcrypto -O3

Running
-------
Just run the resulting binary (a.out or a.exe) from the command line.  The
program will print valid competition messages that are successively closer to
the competition phrase, as measured by Hamming distance. CTRL-C the program to
stop it.  If you want to start with another base phrase, you'll have to change
the mess1 variable in the source and recompile.  To run on multiple cores,
compile multiple versions with different start phrases and run them
simultaneously.  The OS should assign them to separate CPUs and cores when
possible.

License
-------
This code is free software licensed under the MIT License. See the
[LICENSE.md](LICENSE.md) file for details.
