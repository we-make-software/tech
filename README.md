# C - WeMakeSoftware 
 
Well, C is a pretty flexible language, but nobody controls how we write and use it. 
But if others need to read the code, there must be a standard, right? 
Hmm, I’m not sure. If we are pros, then why make a strict design on how to write it? 
As long as it can be read, do we really need to make rules on how to write or how we build? 
Okay, I’m not big on writing documentation, but we can make a story. 
But the story in programming changes with each step. 
So the story needs a system, not just the code itself. 
 
We need to combine the story with true data standards, laws, rules, and hardware. Manufacturers have done a great job. 
We are all different users behind the screen. Everything we see is a timer and action when to do what and show the story as an image to the person who reads it. 
A story needs a title, but for real, I don’t want to inform the title. Whoever made the story, you can check we-make-software.com to see who joined the story. You can also join the story. 
 
But to make this code work for everyone we need to settle on some ground rules. The ground rules include the project name in the documentation and function names. We don’t use names like a b c d e f g or random letters. 
We need a story and it needs a beginning. After all Microsoft is a really closed environment we can’t do so much there only user-end things. But in Linux we can work in the kernel and focus on speed which is important. 
We can follow the rules Linux has and build a story. 
 
If we think about code the problem is jumping between code. Well that is a big problem because everything is read from top to bottom, but can we make this in the kernel? Yes, we can make it. 
But to manage that we need to set up a start and an end. 
But that is really a signal. This signal needs to be sent from the last project, else we can’t make a project in between. 
 
So the first project needs to send a signal to the project that starts. We can call the first project System. Linux has made EXPORT_SYMBOL. Well, as I say, code is read from top to bottom, so if we place EXPORT_SYMBOL at the bottom, then the projects in between can’t use it. 
So the point is, before coding, we need to decide how we work with this so projects can cross and we can jump in the story. We can attempt as many possible ways to place a title and reuse functions in each story. 
Let’s begin by making a project called System and Run. 

Let’s start with the run. The more you read, the more you will forget about the run. It happens to everyone. 
Let’s make the system remember the run or more like let the system remember Run.h 
What is this .h? It’s a header file, a helper. But we can name the extension anything, though by default developers call it .h. Simple, right?
Not everything needs to be remembered, but like Linux, they have a standard way to start. They need MODULE_DESCRIPTION, MODULE_LICENSE, MODULE_AUTHOR, __init, __exit, module_init, and module_exit. 
 
 
But remember we need to use headers a lot, so let’s learn about headers.
When we include a header, we can use the language macros for the compiler so we don’t add the same code all the time.
By using # we enter the macro code. It’s pretty good to know because it can make future code easier to write.
Macro code is only for the compiler.


When we talk about avoiding using the same header, that part is hard to control. But if we follow some simple header rules, then it is no longer hard to understand.

How well can we use `ifndef` and what can it do? It means if we did not define it, then it will run the code, but if it is defined, then it will not run.

So basically, if we write:
 ```c 
#ifndef Run_h
#define Run_h
// any code we can have for the header
#endif
 ```

What it does is it will only run all the code inside once, as you can see in the comment. It will only be used one time and not double.

Now you understand why we use this wrapper in each header. Bravo! Next step.

Wait a minute, did you see a new word like `define`? This is where we can define some code that we can use for the C code and macro code. We can define a name. A define in a macro does not need a value all the time. We just define it, but we can also place a value. Then the code can look something like this:

```c
#ifndef Run_h
#define Run_h
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define Run(description)\
 MODULE_DESCRIPTION(#description);\
 MODULE_LICENSE("GPL");\
 MODULE_AUTHOR("We-Make-Software.Com");\
 static int __init RunInit(void){\
  DefaultStart();\
  return 0;\
 }\
 static void __exit RunExit(void){\
  DefaultEnd();\
 }\
 module_init(RunInit);\
 module_exit(RunExit)

#define Void static void

#endif
```

If you look closely, you’ll see that #ifndef and #define have a name that’s a short identifier we use as developers.
But some symbols are not allowed in names, like spaces and special characters.


Then you can see we use `#include`. There is another way to include files, which I will explain later. Here, I use angle brackets. This is how we include system headers in Linux.
I include three files: module, kernel, and init. These are used by the macro Run.
In the macro Run, I have parentheses. This lets me send text as a parameter. I will show you how later.
I just want to show that we can send a parameter to a `#define`. In this case, we use `MODULE_DESCRIPTION`. I do this by writing `#description`, which turns the text into a string. This is called stringification.

To make it short about define, I made two versions: Run and Void. As you see, Void is one line, and Run uses backslashes for macro newlines. But remember, there is not a big difference. It is just about reading. Which way is the fastest to read?

The naming is important. I didn’t name Void with lowercase because it is used by C. void means “nothing” or “no value.” A function with return type void doesn’t return anything. A function with void in parameters means it takes no arguments. void pointer is a pointer to any type, a generic pointer. In this code, Void is just a shortcut for static void.

In Linux, we need to tell where Init and Exit are. We use module_init and module_exit. These connect the code with the Linux compiler to run at start and end.

I have two functions called inside RunInit and RunExit, I will explain later. In RunInit, there is a parameter void. In C, functions need a parameter type. If no value is sent, we still write void. The function returns 0. This means success to Linux. You can return other numbers for errors, but here I return 0.

We need to write some code in C, a small program, not a big one. This is C. You can see it in the parentheses of many functions or voids. If someone shows code without this, then it is not C, maybe C++. But that will never be at the kernel level; that is for user level. By the way, we are strong, so we work in the kernel, not in the noob area of user space.

The file needs the extension c to work, so each builder knows it is C. We will get to that area.


```c
#include "Run.h"
extern void WeMakeSoftwareStart(void);
extern void WeMakeSoftwareEnd(void);
Void DefaultStart(void){
    WeMakeSoftwareStart();
}
Void DefaultEnd(void){
    WeMakeSoftwareEnd();
}
Run(WeMakeSoftware)
```


As you see, this time the macro #include uses double quotes " ". That’s because we include a file that is already in the project. Cool, right? Now you know the header file is Run.h.

The next thing is extern. This connects with EXPORT_SYMBOL, which I will explain later. After that, you see Void DefaultStart and Void DefaultEnd. When the compiler compiles it, these become static void. It just replaces the name we defined before. Nothing magical here, right? Then I call the external functions, which I will write about later.

Then we have the Run macro. As you see, I don’t need to use quotes to write WeMakeSoftware because we use stringification. Again, it just replaces the code with the define. Nothing magical, right?

Makefile is powerful when it comes to building with gcc.

```makefile
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
EXTRA_CFLAGS += -I../System
KBUILD_EXTRA_SYMBOLS := ../System/Module.symvers
Project := $(notdir $(shell pwd))
obj-m := $(Project).o
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
start:
	make all
	sudo insmod $(Project).ko
stop:
	sudo rmmod $(Project).ko
	make clean
```

This is a Makefile that can be simple for each project, but it will not be the same as the one in the System folder. I will explain Makefile functions later, but this is just to give you an overview.

```makefile
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
Project := $(notdir $(shell pwd))
obj-m := $(Project).o
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
start:
	make all
	sudo insmod $(Project).ko
stop:
	sudo rmmod $(Project).ko
	make clean
```

This is the system Makefile. As you can see, it does not have `EXTRA_CFLAGS` or `KBUILD_EXTRA_SYMBOLS` because this is the initial start. This includes code that can change, so I can explain almost all of it in the code, but it’s up to you to read it.

In the root, we also have a Makefile.


```makefile
MODULES := System Run

REVERSE = $(if $(1),$(call reverse,$(wordlist 2,$(words $(1)),$(1))) $(firstword $(1)))

REVERSE_MODULES := $(call REVERSE,$(MODULES))

all:
	@for m in $(MODULES); do \
		$(MAKE) -C $$m start || true; \
	done

stop:
	@for m in $(REVERSE_MODULES); do \
		$(MAKE) -C $$m stop || $(MAKE) -C $$m clean || true; \
	done

log:
	sudo dmesg -w

clean:
	sudo dmesg -C

test:
	make all
	make log

github:
	git add .
	git commit -m "Auto-commit $(shell date '+%Y-%m-%d %H:%M:%S')"
	git push origin main


```

A Makefile does not have an extension, so name the file `Makefile`. There are a few commands in this Makefile, but I will explain them later when the time comes.

We need to talk about CPU that is the central processing unit. In a server or computer we can have many CPUs maybe they are called cores I don't know. Everyone in this world thinks the CPU is the brain but I would say it is not. It is more about the loop and the RAM and the next step what we developers make. That is the brain and tactic. The problem here is what happens if different CPUs read data and need to change it add something or modify that data. Then what happens is maybe a crash or multiple same data being added. This is something we need to understand as developers.

Sometimes we can ignore adding a task if it only needs to add data. Or maybe we need to add and remove a task. As developers, we think about splitting microseconds every second counts. We need to have full control over each task.

But as first layer of connection it’s okay to be slow after each struct function is connected then we have the speed.


The system needs to hold references to all other projects, but it also needs to have start and stop signals. That’s why the Run project is the last, and the System project is the first.

What is the best way to hold references? It’s simply a list that shows what’s next. If we add a simple Linux list, we basically waste a lot of bytes.

Because what I think is we only need next, name, and a pointer to the struct of that function, like an API if you know what that is.
The design needs to be \[next]\[name size]\[name]\[pointer to the struct]. Okay, the next is a pointer to the next value.
Because we don’t know what version we work on, let’s say if x86 then the pointer can be different size, if x64 then it’s another size.
But C is smart: when we make a struct design for this, we can simply say "\[struct name]\*next" and the compiler will automatically find the correct size.

```c
struct SystemLibrary {
	struct SystemLibrary*next;
	u8 size;
	u8*name;
	void*connection;
};
```

We can always change the design and think about it. We just need to know the basic information and understand how a computer works. I also think this SystemLibrary needs to be built into each ko file, which is a kernel object, and this is what we build. If we include this SystemLibrary inside each ko file that we make between System and Run, then we don’t need to allocate extra space for it. So, we need to keep that in mind when building.

You probably forgot about `#ifndef`. If you did, please start reading from the top. Because in the System folder, we are going to add a header file `.h`.

It will look like this:

```c
#ifndef System_h
#define System_h
#include "../Run/Run.h"
#endif
```



As you see, we include `Run.h` and have full control over what we do and what we include. Let’s say I want to add the minimal code needed to make the Run project work with System.

Then the code will look like this:

```c
#include "../Run/Run.h"

void WeMakeSoftwareStart(void);
void WeMakeSoftwareStart(void) {
}

EXPORT_SYMBOL(WeMakeSoftwareStart);

void WeMakeSoftwareEnd(void);
void WeMakeSoftwareEnd(void) {
}

EXPORT_SYMBOL(WeMakeSoftwareEnd);

Void DefaultStart(void) {}
Void DefaultEnd(void) {}

Run(System);
```

We are using `EXPORT_SYMBOL` in `System.c`. We need to declare the function; this cannot be `static`. It is a simple `void` function. We also need to declare it; that is a rule in C. We can ignore declaring it, but then we will get a warning. That’s why I make functions static so I don’t get that warning. As you can see, we have these two functions `WeMakeSoftwareStart` and `WeMakeSoftwareEnd` that are used to run the project. We export them, and these two functions are only needed for that run project. This is the area where the signal goes in.

Remember you can use `EXPORT_SYMBOL` in your project however you like, but just a reminder: code runs from top to bottom, so you can’t jump around in the code. With my setup, we can jump.

If you also remember, the Makefile for other projects had some code like:

```makefile
EXTRA_CFLAGS += -I../System
KBUILD_EXTRA_SYMBOLS := ../System/Module.symvers
```

That’s because now we have a link to it. When we build, we create a Module.symvers file that basically links to the System.
