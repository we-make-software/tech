# We-make-software tech

Is this the world with new tech or not? Let's find out!

Before I begin, I need to connect this to GitHub so it's public and open source.

Basically, what I did was add a command to the Makefile in the root directory. This way, when I call `make github`, it will automatically upload any updates I've made.

I'll try to update Linux when I have time, but for now, I'm running the kernel from kernel.org: `6.15.0-rc6+`. 


# Run

Well, if we see the start and end, well, the last project needs to run. This is the signal for the system to tell the other projects when to stop or start.

The difference between a .c file and a .h file is that a .h file acts like a helper for us developers, and the .c file is the engine.

If we consider [System], [all other projects], and [Run], this forms the basic system setup for this project.

If we take a look at the `.h` file in `Run`, the macro named `Setup` basically handles the Linux requirements for execution.

Macros are powerful tools in C and with GCC. (Just so you know, I work in GCC.)

# Root/Makefile

The root makefile play a crusien role it build the other project.
Oka we under stand Run need to be the last System need to be the first.
I design this to make it easy for me not you maybe you can make it easyer then tell me.

but 