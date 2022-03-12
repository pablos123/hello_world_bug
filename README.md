# The C /dev/full bug

Today a friend share with me an article that was very interesting:

https://blog.sunfishcode.online/bugs-in-hello-world/

I like Perl and I like C, so why not to combine both to 'bypass' this
bug shared by sunfishcode.

# Compiling

Every C program that uses Perl must link in the perl library.

First you'll have to choose the appropriate compiler because you need to compile
the program in the same way that your Perl was compiled.

Usually is gcc, but we can check that viewing the __cc__ variable:

    perl -MConfig -e 'print $Config{cc}'

    perl -V | grep cc=

You'll also have to choose the appropriate perl library (libperl.so), EXTERN.h
and perl.h directory; usually will reside in a direcotry named __CORE__:

    perl -MConfig -e 'print $Config{archlib}'

You can check the existence of the files with ls:

    ls /usr/lib/x86_64-linux-gnu/perl/5.30/CORE

Maybe you dont have the liperl.so in this directory. So you will have to find
where it is. You can locate the perl library with:

    locate libperl.so

    /usr/lib/x86_64-linux-gnu/libperl.so
    /usr/lib/x86_64-linux-gnu/libperl.so.5.30
    /usr/lib/x86_64-linux-gnu/libperl.so.5.30.0

In my machine the perl library is not in the same directory as EXTERN.h and perl.h

What is interesting here is that the linker will search for the __libperl.so__
file to link properly. If you don't have it but you have, for example,
__libperl.so.5.30__ you can 'hack' this problem with symbolic links!

    sudo ln -s /usr/lib/x86_64-linux-gnu/libperl.so.5.30 /usr/lib/x86_64-linux-gnu/libperl.so

If your compiler complains that certain functions are undefined, or that it can't
locate __-lperl__, then you need to change the path following the -L.
If it complains that it can't find EXTERN.h and perl.h, you need to change the
path following the -I.

The final version of my compile command is this one:

    gcc -I/usr/lib/x86_64-linux-gnu/perl/5.30/CORE -L/usr/lib/x86_64-linux-gnu/ -o hello_world_bug hello_world_bug.c `perl -MExtUtils::Embed -e ccopts -e ldopts`

For more information you can refer to:

https://perldoc.perl.org/perlembed

This program shows the error if Perl handles the error, older version of Perl
will have the issue:

https://www.reddit.com/r/perl/comments/taenkc/unable_to_flush_stdout/

# Testing

    ./hello_world_bug

    Hello World!

--------------------------------------------------------------------------------

    ./hello_world_bug > /dev/full

    Unable to flush stdout: No space left on device
