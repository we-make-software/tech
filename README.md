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
struct WeMakeSoftware {
	struct WeMakeSoftware*next;
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
#include "System.h"

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

Be careful when you develop. We're still humans and a machine is just a machine. Writing code that gets converted into what happens inside the machine requires understanding the steps and the basic idea of how the central processing unit and random access memory work and the storage.

We should also be careful with network cards because we don't really know what each one supports. Some may support DMA or other features. But what if we just supported all network card brands through a common standard?

If we think about attaching a task to a central processing unit in Linux, we need to remember that other programs may also need the CPU. In my view, placing a task in a `work_struct` and using the default workqueue system in Linux gives us a better option to avoid a crash. If you directly assign a CPU to a task, then you need to be careful.

A downside is that a `work_struct` will only be active when a kernel worker thread is available on a CPU. Linux does have internal mechanisms to handle the number of pending `work_struct` items, but this isn't always effective. A good thing is that we can cancel an ongoing task. What if we made a wrapper around the idea of a `work_struct`?

How would we do this? This would basically remove the need for a developer to think about the CPU and the loop for handling tasks.

Random access memory can be used by other programs, so we can't assume a specific block is free. The Linux kernel's Memory Management Unit (MMU) is responsible for tracking memory. It does not use a loop to check every area for free space. Instead, it uses optimized data structures like the buddy allocator and slab allocator to quickly find and allocate space. The kernel already knows where free spaces are.

If we think about storage for KVM or virtual environments, designing a custom solution for each virtual disk or device would take a long time. A simpler approach is to use an LVM logical volume as a raw block device and build our own storage format on top of it. This way, we don’t need to deal with standard filesystems like ext4; we can manage the storage blocks ourselves. The underlying RAID or disk management is best handled by the host server, although we can attach event handlers to monitor the LV. Essentially, the system only needs to report if a block or LV encounters an error, not individual files. So, it’s important to distinguish between the logical volume itself and the storage it resides on. The maximum size we can address is u64 = 18,446,744,073,709,551,615 bytes, which is 16,384 PB it would be hard to reach that, but okay, we got it.


Confused like me? Don’t worry! Coding in your brain takes time.

The difference between C and assembly is that C is human-readable, while assembly is almost not human-readable. C operates at the kernel level, can provide high speed, but requires a step-by-step understanding of how the code executes. However, the more we develop in C, the more we forget about the basics. We create functions and tasks that handle different things, like I showed earlier about connecting kernel object files. But let’s forget about that for now. What I mean is, let’s step away from the details and just write so we don’t have to think about it and can make it standard. What I am thinking is to create a domain-specific language on top of what we have already built.



If we go back to `System.c`, we need a get function that basically returns the library. So the new struct would look like this:

```c
struct WeMakeSoftware {
    unsigned char *name;
    void (*start)(void);
    void (*end)(void);
    void *library;
	struct WeMakeSoftware *prev;
};
```

We have a name as an unsigned char pointer, which is fine. We have `start`, `end`, then the library pointer, and `prev`.

Thinking smart: when we need to start, we have all this information. Do we need all of it during runtime? After calling `start`, we probably don’t need the `start` pointer anymore. To save RAM, we can separate the structs: `WeMakeSoftwareStartup` has all the information needed to initialize, and `WeMakeSoftwareApplicationInterface` has only the information needed at runtime, like `name`, `end`, and `prev`, but no `start` pointer.

This respects memory usage while keeping the information organized.

But what I want you to focus on is optimization:

```c
struct WeMakeSoftwareStartup {
    unsigned char *name;
    void (*start)(void), (*end)(void), *library;
    struct WeMakeSoftware *prev;
};
```

Do you see the difference? It looks shorter, but in reality, it has the **same size**.

The point is, there’s no single “right” way to write it. Everyone can choose their style, but it’s worth remembering that some developers prioritize optimization and compactness, while others prioritize clarity and readability. We write in C, not assembly. Remember that. I hope you all get the point.


There are many ways to do things. We can also change the struct like this:

```c
struct WeMakeSoftware {
    unsigned char *name;
    void (*start)(void);
    void (*end)(void);
    void *library;
	struct list_head list;
};
```

Think about this: the information needs to be **static inside each kernel object file** we build. What do you think about that idea?

When we talk about allocations up to 4096 bytes, kmalloc is actually very fast. The Linux kernel uses slab or slub allocators that keep caches of objects in powers-of-two sizes (32, 64, 128, 256, 512, 1024, 2048, 4096, …). So if we request 4096 bytes, the allocator just takes an entry from the 4096-byte cache, which usually maps exactly to a single page. This means allocation is basically just popping a pointer from a freelist, an O(1) operation. We only hit the buddy allocator when we go above one page (for example, 8192 bytes). So for allocations of 4 KB or less, kmalloc is very efficient.

If we place a struct as static in a file it will not use kmalloc but instead be stored inside the data or bss section of the kernel module. That means the struct is always there for the full lifetime of the module. If we use kmalloc then the struct is allocated from the kernel heap at runtime and we can free it again when we don’t need it. Static is fixed and always present, kmalloc is dynamic and flexible.

Example:

```c
// Static storage (always exists while module is loaded)
static struct WeMakeSoftware my_static = {
    .name = "static-example",
    .start = NULL,
    .end = NULL,
    .library = NULL,
};

// Dynamic storage (allocated and freed at runtime)
struct WeMakeSoftware *my_dynamic;

my_dynamic = kmalloc(sizeof(*my_dynamic), GFP_KERNEL);
if (my_dynamic) {
    my_dynamic->name = "dynamic-example";
    my_dynamic->start = NULL;
    my_dynamic->end = NULL;
    my_dynamic->library = NULL;
    // ...
    kfree(my_dynamic);
}
```

For a domain language system you might want **static structs** for things that are always there, like the core definition of the module or its interface. They don’t change and don’t need to be freed. But for objects that come and go, like tasks, packets, or connections, it is better to use **kmalloc**, because you can allocate and free them dynamically as the system runs.

A static struct still uses RAM. It lives in the data or bss section of the module and is always present while the module is loaded. Kmalloс allocates memory dynamically from the kernel heap and can free it when it’s no longer needed. Static is fixed and always occupies RAM, kmalloc is flexible but only exists when you allocate it.

`kstrdup` is a kernel function that makes a copy of a string in RAM. It takes the original string, allocates space in the kernel heap, and stores the copy there. You can use the copy safely in your module, and when the module ends, you free the memory with `kfree`. This allows each instance to have its own string, instead of sharing a static pointer. Use it whenever you need a dynamic string in kernel code.

Sometimes Linux provides useful headers or systems we can use. I like `list_head`; it’s perfect in many ways for what I’m doing right now. Maybe later it won’t be ideal, but for my current purpose, it works perfectly. That’s why I added it to the struct.

```c
#include "../Run/Run.h"

struct WeMakeSoftware {
    unsigned char *name;
    void (*start)(void);
    void (*end)(void);
    void *library;
	struct list_head list;
};

static LIST_HEAD(list);

void* WeMakeSoftwareGet(unsigned char*);
void* WeMakeSoftwareGet(unsigned char* name){
    struct WeMakeSoftware* wms;
    list_for_each_entry(wms, &list, list){
        if (strcmp(wms->name, name) == 0)
            return wms->library;
    }
    return NULL;
}
EXPORT_SYMBOL(WeMakeSoftwareGet);

void WeMakeSoftwareAdd(struct WeMakeSoftware*);
void WeMakeSoftwareAdd(struct WeMakeSoftware* wms){
    list_add_tail(&wms->list, &list);
}
EXPORT_SYMBOL(WeMakeSoftwareAdd);

void WeMakeSoftwareStart(void);
void WeMakeSoftwareStart(void){
    struct WeMakeSoftware* wms;
    list_for_each_entry(wms, &list, list){
        if (wms->start)
            wms->start();
    }
}
EXPORT_SYMBOL(WeMakeSoftwareStart);

void WeMakeSoftwareEnd(void);
void WeMakeSoftwareEnd(void){
    struct WeMakeSoftware* wms;
    list_for_each_entry_reverse(wms, &list, list){
        if (wms->end)
            wms->end();
    }
}
EXPORT_SYMBOL(WeMakeSoftwareEnd);

static void DefaultStart(void){}
static void DefaultEnd(void){}

Run(System);
```

If you see this code, it should be fairly easy to read. I hope you got a little bit of knowledge on how to read code now. If not, take your time and study it carefully. Understanding kernel lists, function pointers, and `EXPORT_SYMBOL` is key here.

It’s okay to be lazy that’s why we make the DSL

This is the DSL for it if you read this header you can understand what happens maybe or we take it from there

```c
#ifndef System_h
#define System_h
#include "../Run/Run.h"
/* System-DSL Start */
#define WeMakeSoftwareLibrary(description)\
    struct Project_##description

extern void* WeMakeSoftwareGet(unsigned char*SystemName);

#define InitSystemLibrary(description) \
static struct Project_##description* Get##description(void) { \
    static struct Project_##description *project = NULL; \
    if (!project) \
        project = WeMakeSoftwareGet(#description); \
    return project; \
}

#define WeMakeSoftwareRun(description, projectEnd, ...) \
static void WeMakeSoftwareStart(void); \
struct WeMakeSoftware{ \
    unsigned char *name; \
    void (*start)(void); \
    void (*end)(void); \
    void *library; \
    struct list_head list; \
}; \
static struct WeMakeSoftware weMakeSoftware; \
static struct Project_##description* InitProject(void){ \
    static struct Project_##description library={__VA_ARGS__}; \
    return &library; \
} \
extern void WeMakeSoftwareAdd(struct WeMakeSoftware*); \
static void DefaultStart(void){ \
    weMakeSoftware.name=kstrdup(#description, GFP_KERNEL); \
    weMakeSoftware.start=&WeMakeSoftwareStart; \
    weMakeSoftware.end=projectEnd; \
    weMakeSoftware.library=(void*)InitProject(); \
    INIT_LIST_HEAD(&weMakeSoftware.list); \
    WeMakeSoftwareAdd(&weMakeSoftware); \
} \
static void DefaultEnd(void){ \
    list_del(&weMakeSoftware.list); \
    kfree(weMakeSoftware.name); \
} \
Run(description); \
static void WeMakeSoftwareStart(void)

/* System-DSL End */
#endif
```

As I said before System.c is the only file that has the EXPORT_SYMBOL. From now on we are not going to use EXPORT_SYMBOL anymore. System.h is the new DSL, we can call this System-DSL. This is just a sketch, a start we can build on. Not everything needs to be built in one go, but this is so you remember.

So what the idea is: we need some kind of application library interface. By default, I call it `static struct Project_##description`; the description is the project name. The rules are: it can’t have spaces or any symbols, and it must be ASCII.

The `InitSystemLibrary` needs to be used to configure the project. When we go deeper you will understand. So every time I come with the title `System-DSL`, then it’s about this.


I believe the network layer is important when it comes to servers, which is why I start with the network layer. I will add other projects as I go. For this reason, I have another file in the *System* folder called **Directory.h**, which will serve as the main entry point for all headers that will be connected.


As developers we want to save time and keep things simple. I like to improve my main `Makefile` to make project setup easier:

```make
MODULES_FROM_DIRECTORY := $(shell grep '^#include "' ../foldername/.h | sed -e 's/#include "..\///' -e 's/\/\.h"//'

MODULES := System $(MODULES_FROM_DIRECTORY) Run

REVERSE = $(if $(1),$(call REVERSE,$(wordlist 2,$(words $(1)),$(1))) $(firstword $(1)))

REVERSE_MODULES := $(call REVERSE,$(MODULES))

```

In the `System` folder there is a `Directory.h` file where all project header folders are listed. Each project only needs three files: `.c`, `.h`, and `Makefile`.

This lets me focus on creating the project rather than managing file names. Extra build features can be added later.

The `Makefile` reads `Directory.h` and generates a module list. `System` and `Run` are always included as standard modules.

In this system, the folder name is the project name. Each project lives in its own folder, and the `.h` file inside it is just a placeholder. The Makefile extracts the folder name from include lines like `#include "../foldername/.h"` and uses it as the module name. This way, the folder defines the project, not the file.

Lets change topic a little bit so we don’t focus on only one thing but many. Lets go back to the CPU, the central processing unit. The CPU is limited by cores and workload.

We also have the GPU, the graphics processing unit, which can have many cores. So where should we place a task, CPU or GPU?

The best approach is to think of it like a sandwich. The first layer must always be the CPU. The CPU handles control and hardware tasks. Then we can send tasks to the GPU for copy, paste, write, and calculation. The GPU is very fast at these data-parallel operations.

However, tasks that involve hardware interaction should always stay on the CPU. The GPU cannot handle hardware directly. It is only for reading, writing  or performing calculations.

This CPU/GPU sandwich is the basic idea to keep in mind when deciding where to run tasks. CPU controls the flow, GPU accelerates the heavy work.

This is how it might look:

- Start with the CPU.
- Pass the necessary information (like memory allocation with `kmalloc` or other data).
- Send the task to the GPU.
- Let the GPU run and process the task.

You have two options:
- Let the GPU run in the background and end the CPU task.
- Or, have the CPU wait for the GPU to finish before continuing.


There are some problems. Most hardware vendors write drivers for Windows or Linux only. We must follow their rules. Windows is a closed environment that needs license after license, and sometimes even a certificate just to access hardware if you want to make your own software. Too heavy, no thanks. Linux is open and has many developers, but you still must follow the system rules, otherwise you can end up with CPU locks or random errors.

As software developers we do not know what protocols the user will choose. We cannot force someone to use one email service, it is always their choice. Linux gives more freedom, but not for everything.

Take work_struct as an example. It is basically a structure that lets a function run inside a kernel thread. A thread is not a CPU core task. If you have 8 cores, the scheduled thread can run on any of them when it is ready. You can check the CPU state, but you cannot know exactly how many tasks are running because there can be pending tasks. You can check pending tasks too, but even that consumes CPU.

After boot, Linux itself already needs around 10 to 20 threads to run. At any moment there may be more. The scheduler can jump a task to any available CPU, which makes it very hard to follow. I have tried, and it is not easy to trace.

Maybe it is better to make a wrapper around work_struct. With one central function that checks if there are tasks waiting. It can forward work or send a signal and also measure how long a task has been waiting. Then we can build a calculation system that says what is normal, what is medium, and what is high. If something is a miss, we tell the user. For example, this server was too slow, use another one.

By keeping track of these functions we can learn about misses and delays. The same approach can also be used for GPU scheduling.

When we talk about RAM (Random Access Memory), Linux has a standard way to manage it. That is why it is good to use kmalloc so we do not accidentally overwrite other data. Other software is also using memory, and while we technically could access any pointer, it is unsafe and not practical to track every pointer manually. We also cannot always know when a RAM block is free, so it is better to let Linux manage it.

The same idea applies to GPU memory, called VRAM (Video Random Access Memory). GPUs have their own memory space, separate from the CPU. The GPU cannot directly access CPU memory, so it needs its own address space. That is why VRAM exists, it lets the GPU handle its own data safely while the CPU manages physical addresses.

Here is the point. We can send tasks to the GPU, but the GPU cannot directly start tasks on the CPU. As developers, we need some kind of loop or mechanism to detect when a GPU task is finished. Without a wait function on the CPU side, we cannot know when the task completes. If we add a wait inside the CPU function, it consumes a thread.

This raises questions, how often should we check, how fast should the check be. RAM is fast, but not infinitely fast. A function might still be running, or maybe it is time to start a new function in another thread to speed things up. It is all about making choices, when to check, when to execute, and in what order.


When we talk about a network card, we don’t know what protocols the user will use, and we can’t say “you must use this software.” We need to balance flexibility so the user can choose their own setup, like turning off a mail system or using other services. It is entirely up to the user, because different people have different views on networking.

My approach is to stick with the Linux network layer 2 using netfilter and `sk_buff`. Linux already provides a very good system that works from almost nothing up to 10 Gbit or higher on a network card. This way, user-space is where slow or badly written code belongs, slow areas like Python, C#, PHP, C++, and so on, while critical packet handling stays fast and reliable in C.

We have TX and RX. TX stands for transmit, which is outgoing data from your system. RX stands for receive, which is incoming data to your system. Since we work at Layer 2, we can basically call it incoming and outgoing traffic.

When it comes to storage, there are different hardware options. SSD, NVMe, or RAID, it is up to the user what they want to use, and we cannot control that. Some users like to use RAID, which combines multiple drives for redundancy or better performance.

For simplicity, we can just use a binary file and rely on the Linux standard file system to read and write data. This way, we do not interfere with the user’s choice of how to set up their server.

It is a good idea to check what gives the fastest read and write speed. NVMe is the fastest in my view, but other technologies may become faster in the future. Technology is always growing, so we cannot predict everything.


You might want to use the newest C standards, but kernel development requires sticking to C89/C90 for safety and portability reasons. The simplest way to see why is with arrays and memory allocation. In user space, someone might write a variable-length array like this:

```c
int n = get_size();
int arr[n];
```

That looks convenient, but this is dangerous in the kernel. The kernel stack is very small, typically a few kilobytes on many architectures. If `n` is large, `arr[n]` will overflow the stack. Stack overflow in kernel space can cause an immediate kernel oops or panic, or it can silently overwrite nearby kernel data and break other code in unpredictable ways. These bugs are extremely hard to trace because memory corruption shows up far from where it actually happened.

Kernel code avoids that by using dynamic allocation with `kmalloc`, so the data lives in heap memory managed by the kernel. The pattern looks like this:

```c
int n = get_size();
int *arr = kmalloc(sizeof(int) * n, GFP_KERNEL);
if (!arr) {
    /* handle allocation failure cleanly */
    return -ENOMEM;
}

/* use arr safely */
arr[0] = 10;
arr[1] = 20;

kfree(arr);
```

This moves the allocation off the limited stack and into memory the kernel controls. If allocation fails, you get a clear error path instead of undefined memory corruption. If you must allocate in atomic contexts, you would use `GFP_ATOMIC`, but that is a separate consideration and used only when sleeping is not allowed.

Beyond the stack overflow problem, newer C features introduce subtle risks in kernel code. Variable-length arrays, complex initializers, or other language niceties can change how the compiler lays out data, aligns memory, or optimizes code. In kernel space, tiny differences in alignment, padding, or optimization assumptions can break low-level code, change volatile behavior, or defeat inline assembly expectations. The kernel must behave predictably across many compilers and CPU architectures, and C89/C90 is the common denominator that keeps behavior stable.

That does not mean you cannot use modern C features at all. User-space programs can and often should use the newest C standards where productivity and language features matter. The kernel is different because it has to be extremely stable, portable, and predictable. For kernel code, we focus on simple, explicit C89/C90 style plus explicit dynamic allocation like `kmalloc` to avoid stack overflows and undefined behavior. This choice is not about being old-fashioned, it is about safety and reliability in a hostile, constrained environment.


