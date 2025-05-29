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


# MediaAccessControl

Previously, I discussed this topic before introducing the NetworkAdapter. Essentially, we can consider the NetworkAdapter as a simplified version.

## NetworkAdapter

This project represents the default configuration for obtaining a complete network frame. There's nothing particularly special here. You can explore the project, and within the C file, you'll find the necessary components. It utilizes the `UseMediaAccessControlLibrary` and is primarily employed in the Receiver section of the C file.

Now, let's return to the main topic.

# MediaAccessControl


| Bit Position | 7 | 6 | 5 | 4 | 3 | 2 | 1 (U/L) | 0 (I/G) |
| :----------- | :- | :- | :- | :- | :- | :- | :-------- | :-------- |
| Bit Value    | 0 | 0 | 0 | 0 | 0 | 0 | 0         | 0         |



The I/G (Individual/Group) bit indicates whether a MAC address targets a single device (Unicast) or a group of devices (Multicast/Broadcast).
I will not focus on this area, as I'm unsure if an ISP can send multicast, or if we ever need to consider that.

The U/L (Universal/Local) bit is the second least significant bit of the first byte of a MAC address. This bit plays a big role: if it's 1, that means it's a locally administered address. When I'm focusing on global network packets, if this bit is 1, I'll just tell Linux it's not a packet for me and return 0.

There are basically two MAC addresses in an Ethernet frame: one is the source MAC address from the network card that sent the packet, and the other is the destination MAC address of the next hop (which could be another device on the local network or the router if the packet is going outside the local network).

There isn't a single standard name for this specific area of code; however, we might informally refer to it in relation to IEEE 802.3. For my project, I call this the Media Access Control (MAC) project, because it fundamentally deals with the information found at that layer.

Within the MAC header, there's an extra field called EtherType. If the EtherType is 2048, it indicates an RFC 791 (IPv4) packet. If it's 34527, it indicates an RFC 8200 (IPv6) packet. This is why you can see two extra include files in the header – they're for these specific protocols.

Don't worry, the system has two or more ways to jump, depending on the EtherType, it will jump to the correct location. It will then jump back to the MediaAccessControl project, from where it will proceed in the correct manner.

It's also a placeholder for the router or device that's connected; I just call it "router." It's pretty simple.

After all, this API, which provides calls like `Hookup`, `Unhook`, `Register`, and `Send`, is basically only used in Project RFC791 and RFC8200.


# RFC791 /)! & RFC8200 ("==) and MediaAccessControl->Register

Ever tried to make a mistake, like pressing Shift and the numbers simultaneously?

Well, these two network layers have some common stuff. Both **RFC 791 (IPv4)** and **RFC 8200 (IPv6)** work with the TCP and UDP layers above them.

`MediaAccessControl->Register` gets called, but here, we just include the common information from whichever it is: **RFC 9293 (TCP)** or **RFC 8304 (UDP)**. The naming convention isn't exactly the same in these two versions, but I've performed some naming magic and settled on `nextheader`. It's a perfect name!

Therefore, it looks like this: `MediaAccessControl->Register` includes `nextheader` and `destinationPort`. You can check the code to see how it calls these two projects (RFC 9293 and RFC 8304); basically, it checks if the port is allowed before returning the Router.