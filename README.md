# The C /dev/full bug

Today a friend share with me an article that was very interesting:

https://blog.sunfishcode.online/bugs-in-hello-world/

I like Perl and I like C, so why not to combine both to 'bypass' this
bug shared by sunfishcode.

# Compiling

    cc -o hello_world_bug hello_world_bug.c `perl -MExtUtils::Embed -e ccopts -e ldopts`

If you don't want to compile it I'll left the pre-copiled binary.

# Testing

    ./hello_world_bug

    Hello World!

--------------------------------------------------------------------------------

    ./hello_world_bug > /dev/full

    Unable to flush stdout: No space left on device

