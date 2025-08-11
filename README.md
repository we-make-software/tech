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

If we look at a system, then we need to make order. That is the best approach to take in server programming or general programming. A list is the best structure to use. You can use the default list system in Linux, but for me, it limits a lot of developer options. It does not give full control.

What I like to do is create my own list system where I have full control.

Think about this: in binary, we can use bits to indicate access methods, call related functions in order, or something else a developer might need. What I need is speed, so I want my list system to be more flexible. Even if it costs some extra bytes in RAM, I prefer speed. Maybe you have your own view, but I like to have a wrapper around the list or main information.

typedef struct  ListFunction{
  	struct work_struct Work;
 	void*Data;
}ListFunction;

```ListInfomation
Struct ListInfomation{
	u8 x8:1,x16:1,x32:1,x64:1,Lock:4;

	u8 Count[]	
};
Struct ListInfomationX8{
	u8 x8:1,x16:1,x32:1,x64:1,Lock:4;
	u8 Count;	
};
Struct ListInfomationX16{
	u8 x8:1,x16:1,x32:1,x64:1,Lock:4;
	u16 Count;	
};
Struct ListInfomationX32{
	u8 x8:1,x16:1,x32:1,x64:1,Lock:4;
	u32 Count;	
};
Struct ListInfomationX64{
	u8 x8:1,x16:1,x32:1,x64:1,Lock:4;
	u64 Count;	
};
```

If we think about it, the maximum size of a list is 18446744073709551615ULL. We will never use that because it’s too large for RAM. We need to control the list by removing data when it’s not needed. But again, a list can also be x8, x16, x32, or x64 max size. So the wrapper for this list needs to be flexible of counter.





[Prev][Next]



