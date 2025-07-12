# We-Make-Software

GCC and Linux


# A

Well, if we think about it correctly, then A. Okay, how do we start a .ko file in Linux? I try to keep updated with Linux all the time; it's not all the time I do this, but I do it sometimes. Okay, if we think about a header file, that's a basic .h file. A header file is more of what I will call a developer helper. That seems like a pretty good name: helper instead of header. Okay, a different view – many will say this in a comment or point it out. But if we make a foundation, first file A.h. Well, if we solely focus on Linux, we've got some few headers. Let me go through this... Seriously, go check it. I don't think the start and end need more in the future, but not in the start. A project needs to be upgraded to be easier all the time; that's what I believe. We make our own design; that's a basic call – DSL. I like this DSL.

If you look inside A.c, it's simple. It needs to call B.c.

This is how the load needs to be:

B.c A.c

Why is A.c last? Because this is the key information for when to start or end. We're building a runtime, so it's better to know where it starts and where it ends. The last .ko file indicates that, so it's simple. Go look inside the Makefile in the folder A; it's pretty simple, no drama needed.

Okay, we know in Linux we make a .ko (Kernel Object).

So when we run make or make start, it starts to make the code.

As I said, the loading needs to be B.ko then A.ko; that's the order.

When we develop, we need to think about upgrading.

So, in A.c, you will see including A.h. It does not need a higher level.

So, as a developer, the level is like a helper: A.h, B.h, and so on.

We will go back to this loading and header later; you will create an image of how this can be done.

# B

As developers, we get tired of `EXPORT_SYMBOL`. We already have the perfect init function in Project A; well, you have seen the code. This is also the file to use the power of `EXPORT_SYMBOL`.

If you check the basic code in `.h`:

```c
#ifndef B
#define B
#include "../A/A.h"

#define B2(b3) b3; b3

#endif
```

This is powerful because if you see `#ifndef B`, it means if `B` is not defined, then go inside the `if` statement. After we define `B`, we place the old include, so that include now gives us a higher level in the header. I placed a macro `define B2`; that's a DSL I will explain later. About that...

We want to work around A0 so we can avoid `EXPORT_SYMBOL` in the project and build this as an API system. Maybe I don't know what we can call it – maybe just "API," I don't know. But to avoid `EXPORT_SYMBOL`, we need to make a setup for this. Okay, so if you go look inside `B2`, this is the upgrade for project A. `B2` is defined in the `.c` file; it doesn't always have to be defined in the `.h` file, just remember that.

We need to think about storage in memory. The start and exit points of the data need to be known.

That's important, so we need to make a struct that can reduce size and maintain a consistent size.

We don't need to run it twice.

