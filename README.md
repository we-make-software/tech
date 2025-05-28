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

The implementation of this is pretty easy: we include the `RunSetup` header in the C file. As you can see, I use `extern`, which basically links to the `System` project.

What you'll notice if you check the .h file is the #description. This hashtag makes it a string.

The Makefile plays a crucial role; it builds the other projects. It basically has `make start` and `make stop`, and we need to focus on this Makefile. It's unique and will be the same, but not in the `System` folder.

# System

We don't include `System.h` inside `System.c` because, as I've mentioned, the `.h` file serves as a helper that only includes `Run.h`. If you examine the `.c` file, you'll see we use `EXPORT_SYMBOL` to link the different tasks from System. Also, the Makefile isn't set up the same way. Essentially, this system is a placeholder for all future projects, so we won't need to think about `EXPORT_SYMBOL` anymore. This design will incorporate `SystemSetup` and `GetSystemLibrary` as new macros, making the System project always the starting point. 

`SystemLibrary` is a **macro** that can be used in other header files. Its purpose is to simplify the creation of **structs** for the ongoing project, making the naming easier to manage. You can look at the `NetworkAdapter` header file to see an example of its use.

Additionally, `InitSystemLibrary` is used in a C file, not typically in a header file.

I also created `Start` and `End` macros to reduce repetitive code – call it laziness! You can see how they're used in the `NetworkAdapter.c` file.

# Globel Makefile


* **make**: This command builds and starts the project.
* **make clean**: This command cleans the project logs.
* **make log**: This command displays the project logs.
* **make test**: This command starts the project and then displays its logs.
* **make stop**: This command stops the running project.



# Media Access Control

Previously, I discussed this topic before introducing the NetworkAdapter. Essentially, we can consider the NetworkAdapter as a simplified version.

## NetworkAdapter

This project represents the default configuration for obtaining a complete network frame. There's nothing particularly special here. You can explore the project, and within the C file, you'll find the necessary components. It utilizes the `UseMediaAccessControlLibrary` and is primarily employed in the Receiver section of the C file.

Now, let's return to the main topic.

# Media Access Control


