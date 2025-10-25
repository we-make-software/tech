# C - WeMakeSoftware 

This repo isn’t a tutorial or a finished product. It’s a living lab. Reading it feels like stepping inside someone’s mind as they experiment with system-level programming: messy, jumpy, and full of ideas in motion. It doesn’t hand you answers; it makes you think, stumble, and explore, exactly the way real low-level development works. The chaos isn’t a flaw; it’s the experience.

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

We have the CPU, the central processing unit, which is responsible for managing and controlling the system. The CPU handles control, scheduling, and all hardware interaction tasks.

When assigning tasks, the best approach is to remember that the CPU must always be the first layer. It controls the overall flow and decides when and how work should be performed. The CPU manages memory, coordinates with devices, and ensures synchronization between different operations.

Start with the CPU.
Prepare or allocate memory as needed, for example using kmalloc or other methods.
Execute the task directly on the CPU.
Optionally, schedule background work or wait for completion before continuing.

Most hardware vendors write drivers for Windows or Linux only, so we must follow their rules. Windows is a closed environment that requires multiple licenses and certificates just to access hardware, which makes it too heavy and restrictive. Linux is open and has many developers, but you still must follow system rules, otherwise you can end up with CPU locks or random errors.

There are some problems. Most hardware vendors write drivers for Windows or Linux only. We must follow their rules. Windows is a closed environment that needs license after license, and sometimes even a certificate just to access hardware if you want to make your own software. Too heavy, no thanks. Linux is open and has many developers, but you still must follow the system rules, otherwise you can end up with CPU locks or random errors.

As software developers we do not know what protocols the user will choose. We cannot force someone to use one email service, it is always their choice. Linux gives more freedom, but not for everything.

Take work_struct as an example. It is basically a structure that lets a function run inside a kernel thread. A thread is not a CPU core task. If you have 8 cores, the scheduled thread can run on any of them when it is ready. You can check the CPU state, but you cannot know exactly how many tasks are running because there can be pending tasks. You can check pending tasks too, but even that consumes CPU.

After boot, Linux itself already needs around 10 to 20 threads to run. At any moment there may be more. The scheduler can jump a task to any available CPU, which makes it very hard to follow. I have tried, and it is not easy to trace.

Maybe it is better to make a wrapper around work_struct. With one central function that checks if there are tasks waiting. It can forward work or send a signal and also measure how long a task has been waiting. Then we can build a calculation system that says what is normal, what is medium, and what is high. If something is a miss, we tell the user. For example, this server was too slow, use another one.

The same idea applies to system memory. The CPU uses its own address space to manage data safely and efficiently. It controls how memory is allocated, accessed, and released. This separation ensures that data is handled properly while the CPU manages physical addresses.

Here is the point. We can send tasks between different parts of the system, but direct hardware-level communication must always be managed by the CPU. As developers, we need some kind of loop or mechanism to detect when a task is finished. Without a wait function on the CPU side, we cannot know when the task completes. If we add a wait inside the CPU function, it consumes a thread.

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


The primary function of **user-space** is the **Presentation Layer**: handling all user interaction, such as displaying graphics, buttons, inputs, and real-time visual feedback. However, a crucial constraint in modern software architecture is **power consumption**, as network activity is highly resource-intensive and rapidly drains device batteries. Given the wide and unpredictable variation in client devices ranging from mobile (Android, iOS) to desktops and laptops, it is inefficient and risky to rely on the client's local CPU and memory for heavy computational tasks. Therefore, the optimal solution for achieving both speed and battery conservation is **Server-Side Offloading**. In this model, complex, demanding operations (like heavy data processing or analytics) are **sent to a powerful server** to handle the difficult computation. The server then formats the result into the smallest, most efficient **"display-ready" package** and sends only that minimal data back to the client. This approach allows the user-space layer on the device to remain "thin," focusing solely on quickly rendering the pre-processed data, which minimizes the time the power-hungry network radio is active and conserves the device's resources.


We cannot be hardware support for a user, but for a server we can inform actions such as a broken disk. This is essentially a messaging system that notes the system status. We can provide more information about the hardware to the technical team so they can replace it when needed. As developers, we need to think about every aspect. If I miss an aspect, you are welcome to tell me and we can review it together. I do not want to be number one or you to be number one. The idea is to create a story. Each story should be as digital as possible, step by step, with minimal clicks and automatic actions. That is the idea behind kernel development: to make everything smooth and easy while still keeping it usable for the user.


Now you understand my point of view. I hope this gives you an idea of how the system works. If you have a better way, please tell me.

In hardware development, we can issue commands that trigger specific operations or function calls directly on the hardware. It’s like turning a wheel or making objects move instantly. From a developer’s perspective, hardware is a highly deterministic and extremely fast engine that executes instructions at incredible speed. This direct control over execution is what distinguishes hardware programming from software programming.

Let’s go deeper. The CPU clock is like a metronome ticking billions of times per second. Every tick lets the CPU do a small operation like read an instruction, add numbers, or write to memory. L1 cache is super fast and sits directly on the CPU core. It stores the most frequently used data and instructions and can be accessed in just a few cycles. L2 cache is bigger but a bit slower, helping the CPU when the L1 cache doesn’t have the needed data. L3 cache is even larger and shared between cores, but slower compared to L1 and L2. It is used to reduce the need to fetch data from RAM. RAM is much slower and located outside the CPU. Accessing RAM can take hundreds of cycles compared to just a few for L1.

The clock speed, measured in hertz, tells how many ticks happen per second. For example, 3 GHz means three billion ticks every second, and each tick is a chance for the CPU to move one step forward. You can have many functions running in the CPU, or multiple cores executing different instructions independently. Each core can handle its own workload simultaneously, which makes the system faster and more efficient when processing multiple tasks in parallel.

When multiple tasks want to access the same data, the CPU uses mutexes to avoid conflicts. A task tries to lock a mutex before using the resource. If the mutex is already locked, the task sleeps, pausing its execution and letting other tasks run. When the mutex is free, the CPU wakes the sleeping task so it can continue safely.

Sending a signal is like telling the CPU “okay, go to the next step.” The CPU handles this efficiently: running tasks may complete, sleep, or wait for a signal, while other tasks on the same or different cores proceed in parallel. Each core can run many functions simultaneously, fetching data from caches or RAM, waiting on mutexes, and waking when the signal arrives.

This coordination of cores, caches, mutexes, sleep, and signals is what makes CPU multitasking extremely efficient, allowing many tasks to run fast without interfering with each other.

When the CPU needs to write data to storage, such as an SSD, NVMe, or traditional HDD, it cannot access it as fast as the caches or even RAM. Storage is much slower because it is outside the CPU and RAM hierarchy. The CPU relies on the memory controller and I/O buses to communicate with the storage device.

You can think of storage as the L4 level in the memory hierarchy. Data must first leave the CPU caches and RAM and travel through the system’s buses, controllers, and interfaces to reach the storage. This introduces latency, and even the fastest NVMe drives are hundreds or thousands of times slower than RAM.

When writing to disk, the CPU can continue with other tasks while the storage controller handles the actual write operation. Some systems use write caches or buffers to temporarily hold data before committing it to the storage medium. This helps improve performance but does not remove the inherent slowness of storage compared to CPU caches.

In short, writing to storage is slow because it involves moving data across multiple levels: from CPU registers to L1/L2/L3 caches, to RAM, and finally through the I/O path to the storage device. Understanding this helps optimize which data should stay in memory and which can be safely stored to disk.

The problem is that not all data can stay in RAM; therefore, we need to transfer some of it to storage. Otherwise, there would be too much data in memory. There will be small gaps if we want to work fast, but we can try to optimize and keep the process efficient. The key is to understand the idea and plan the workflow first.

I will attempt to go through all the steps as thoroughly as possible, but you can also review the code. I will mainly indicate which projects to look at and point out specific functions, and I may showcase code snippets here.

Synchronous means the code waits for a task to finish before moving to the next step. Asynchronous means the code can start a task and continue without waiting for it to finish; it handles the result later, usually via callbacks, promises, or signals. Basically, synchronous operations happen inside an asynchronous flow when needed, but asynchronous does not require synchronous execution.

Using work_struct is an example of asynchronous execution in the kernel. The work function itself runs synchronously on a CPU core once scheduled, so synchronous code lives inside the asynchronous work queue.

Ah, got it! You want it **embedded directly in your text**, not as a separate table. Here’s how you can write it naturally in your explanation:





For a project, it is important to have a task manager to control or place a task in a wait state, or to see if there are any pending tasks. Linux does not provide this information directly, so we need to keep track of it in the system. Therefore, we create a wrapper called `TaskHandler`. With this, we can get a view of how many tasks we can run, whether there is a free spot, or if we need to reserve some tasks for a specific project, for example network handling.

If we look at network traffic, for a 1 Gbit link and a packet size of 1500 bytes (MTU), one packet takes about 12 microseconds. For 10 Gbit, the same packet will take roughly 1.2 microseconds, because the link is ten times faster.

The number of tasks needed to process all packets in a given time interval can be calculated with:

```
number_of_tasks = time_interval / packet_interval
```

For example, if we want to make sure we can handle every packet in a 0.05 second window:

* At 1 Gbit:

```
number_of_tasks = 0.05 / 0.000012 ≈ 4166
```

* At 10 Gbit:

```
number_of_tasks = 0.05 / 0.0000012 ≈ 41666
```

This calculation helps us determine how many `work_struct` instances we need to schedule to handle incoming and outgoing packets efficiently, ensuring the system keeps up with high-speed network traffic.

As you can see, 41,666 is higher than 4,166, so we choose 41,666 for the network. In networking, we have both RX (receive) and TX (transmit). If we split that number evenly, it becomes RX (20,833) and TX (20,833). Keeping these numbers in mind helps ensure the network remains efficient when we build the TaskHandler.

There are different types of priorities when running a work_struct: low, medium, or high. High priority tasks need to run first, for example streaming video or other time-critical operations. Medium priority tasks come next, handling normal data flow. Low priority tasks can wait; they are not urgent, such as background input or non-critical updates. If no high or medium tasks are pending, low priority tasks can run freely. This ensures important data is processed first while still keeping the system active and balanced.

Yes, it is a very good idea. By controlling what runs first, you make sure critical tasks are processed immediately while less important tasks wait. This gives predictability and efficiency, especially in high-speed networks or systems with many tasks at the same time. Without this control, Linux will schedule tasks based on its own priorities, which may not match your project’s needs. By pre-managing with a TaskHandler, you can align system execution with your goals, reduce latency for important operations, and make sure nothing gets delayed or starved. It is basically bringing order to chaos in multitasking environments, exactly what high-performance systems need. After all, everything happens in a snap.


Now we will talk about what we can do and showcase code, but the focus is more on upgrading and making the system more developer-friendly. A lot of code can change in this process.

The basic focus is:

* Make the system developer-friendly
* Upgrade the System-DSL project
* Build the TaskHandler project

As developers, we need to focus on continuous upgrades to improve the system each time. I will walk through my ideas, views, and new perspectives.


I know I have not tested my code and a lot of changes happened in the file system, and how to do it. Maybe there was a file name that was renamed to make it easier to use later, but my idea was:

### Project Structure Idea

* **ProjectName** (folder defines the project)

  * `Makefile`
  * `.c` (source code; no need for a custom name)
  * `.h` (header file; no need for a custom name)

**Notes:**

* No extra naming is needed for `.c` or `.h` files because the folder itself represents the project name.
* This structure keeps the project organized and developer-friendly.


Then, if we check the Run folder, the Makefile needs to be the same as Run/Makefile. Basically, for each new project, we can write the Makefile as

```
include ../Run/Makefile
```

This way, we don’t need to make a big drama about it. It will be easier if we can call a command in the terminal to create a new project, so it automatically prepares a template for us.

Let’s keep in mind that the Makefile in each new project only needs to have this line, nothing more.

When we talk about include it gives me idea to upgrade both System Makefile and Run Makefile. I also think about remove the old Directory.h and just add a .h file in the root. Then in each folder we only see .c file .h file and Makefile that’s the only stuff we will see. I hope you take time to see in each folder how it’s build.

When we talk about the CPU and you have a basic idea of how it works, like a clock, as we discussed before, developers create different layers when working in the kernel. In the kernel, we basically work in ring 0, which has full access to hardware, can execute any CPU instruction, and can access any memory. All Linux kernel code runs here. There are also other rings, such as ring 1 and ring 2, which are typically unused in modern operating systems like Linux. They exist in the architecture, but Linux does not assign kernel or driver code to them. Ring 3 has restricted access, cannot execute privileged instructions, and cannot access kernel memory directly. All user-space programs run in ring 3.

I don’t want to focus too much on the Makefile, that’s why I keep jumping out of it, so we can focus on the real code. As developers, we just give instructions on what to do, that’s basically all. When upgrading the System-DSL, the goal is to make it easier to use. We had a DSL before, and now we want to improve it. Macros are a perfect tool between the compiler and the code. Basically, as developers, we use them to tell the compiler how the code should be translated before compiling. They make writing code easier for us. You just need to remember that a macro is not the code for the kernel object file itself, but more like a translator or a set of small instructions that prepare or modify the code before it is compiled into the kernel object.

Sometimes developers like short names or want to change the DSL name. We have this DSL “WeMakeSoftwareRun,” and we can make it shorter by calling it “WMSR” We don’t need to change the first define for this to work.

We can simply write:

```c
#define WMSR(description, projectEnd, ...) WeMakeSoftwareRun(description, projectEnd, __VA_ARGS__)
```

This is the basic way to build on top of a macro. Some call it an alias, it is your choice what you want to call it.


As you can see in the `WMSR` macro, the three dots `...` represent the arguments. We need to set up a `#define` to handle that. The idea is to have a define that includes both the name and the function, and another define that omits the name when the function name is the same. We will call the version with a name `WMSNAF`, and the version without a name `WMSF`; `WMSF` assumes the function name is the same. Both will pass their data to the original `WeMakeSoftwareRun` macro using `__VA_ARGS__`. Later we can build a struct for this, but for now let’s focus on the macro.

The `WMSNAF` macro is defined as

```c
#define WMSNAF(name, function) .name = function
```

What it does is it takes the first argument as the field name in the struct and the second argument as the function pointer to assign. It is not a string, it is the actual function pointer. So if we have a struct like `struct Project_MyProject` and we use `WMSNAF(MyFunction, SomeFunction)`, it becomes `.MyFunction = SomeFunction` inside the struct. This lets us assign any function to any field with a custom name.

The `WMSF` macro is defined as

```c
#define WMSF(function) .##function = function
```

This macro is for when the field name and the function name are the same. We don’t need to repeat the name twice. For example, if the struct has a field called `OtherFunction` and the function is also called `OtherFunction`, using `WMSF(OtherFunction)` expands to `.OtherFunction = OtherFunction`. This saves us from typing the same name twice and keeps the code shorter.

Both macros are used inside the struct created by `InitProject()` in `WeMakeSoftwareRun`. The `InitProject()` function creates a static struct for the project with the description name and initializes it with all the fields passed via `__VA_ARGS__`. So when we write

```c
WMSR(MyProject, ProjectEnd, 
    WMSNAF(MyFunction, SomeFunction),
    WMSF(OtherFunction)
) {}
```

the `WMSNAF` macro assigns `.MyFunction = SomeFunction` and `WMSF` assigns `.OtherFunction = OtherFunction` inside `struct Project_MyProject`. After macro expansion, the struct looks like

```c
static struct Project_MyProject library = {
    .MyFunction = SomeFunction,
    .OtherFunction = OtherFunction
};
```

This shows clearly where the macros go and what they do. They fill the struct fields automatically so we don’t need to manually assign each function.

If you see, we still need to make a signature system. It is important. You need to know that we are going to use a semicolon `;` and not a comma `,`. In `WMSR` we use commas, but in this signature system we are going to use semicolons. The semicolon is an important note, and you need to understand it. In the struct, there is no comma, only a semicolon when it is a new line.


We can make a macro called `WMSS` like this:

```c
#define WMSS(description, ...) struct Project_##description { __VA_ARGS__ };
```

What this does is it creates a **static struct** with the name `Project_` followed by the description you give. The `__VA_ARGS__` is where you put all the fields for the struct, and here you can use **semicolons** for each new field.

For example, if we write:

```c
WMSS(MyProject,
    void (*MyFunction)(int);
    int (*OtherFunction)(char*);
)
```

It will expand to:

```c
static struct Project_MyProject {
    void (*MyFunction)(int);
    int (*OtherFunction)(char*);
};
```

So now we have a **struct ready to use** in our DSL. You can define the fields with semicolons, and the macro handles the rest automatically. This is the first step before using `WMSR` to assign the functions with `WMSNAF` or `WMSF`.




```c
#ifndef TaskHandler_h_Upgrade
#define TaskHandler_h_Upgrade
#include "../Run/Run.h"

#define WMSR(description, projectEnd, ...) WeMakeSoftwareRun(description, projectEnd, __VA_ARGS__)

#define WMSNAF(name, function) .name = function

#define WMSF(function) .##function = function

#define WMSS(description, ...) static struct Project_##description { __VA_ARGS__ };

#endif
#ifdef TaskHandler_h

#endif
```

`ifdef` is basically a macro that needs to be defined. It is good to use in cases like this, where we can include it only when we really need it in the C file. You will later understand how powerful `ifdef` is when we go deeper, but before that, we need to set up the TaskHandler C file.

Yes, I get it perfectly 😄 You’re defining `TaskHandler_h` to activate the `#ifdef` area you prepared earlier. Here’s your text corrected, keeping your natural style and meaning:


```c
#define TaskHandler_h  
#include "../.h"

WMSR(TaskHandler, NULL, FUNCTIONS COMING LATER) {
    // Start
}
```

It follows the same structure we made above. As you can see, I have defined `TaskHandler_h`, which will activate the area we talked about earlier. Do you get it?



Now we have activated `TaskHandler_h`, then we can go back to the header file. Between the `#ifdef TaskHandler_h` and `#endif`, we write:

```c
WMSS(TaskHandler, signature of many functions will go here)

#define GetTaskHandler InitSystemLibrary(TaskHandler)
#endif
```

We need to make a helper and set up the basic `WMSS` system. As you can see, we will later go deeper into how a signature will look. But we also need to make a helper for other kernel objects that follow the same structure.

Earlier I made `InitSystemLibrary` as a DSL. We can define a setup for the next kernel object so it can call the same pattern. For example every module will define something like:

```c
#define Get<ModuleName> InitSystemLibrary(<ModuleName>)
```

This way every kernel object like TaskHandler, MemoryManager, or IOHandler will expose its struct through a consistent entry point.

In our case `GetTaskHandler` points to `InitSystemLibrary(TaskHandler)` which returns the struct of this TaskHandler project so every other project can use it easily and uniformly.


When a function is compiled it goes into the .text section of the object or kernel module. This is true for both static and non-static functions. The code exists in memory once the kernel or module is loaded. The CPU does not execute it until the function is called.

A static function is private to the file which allows the compiler to optimize it. For example it can inline small functions or remove unused ones. The function still sits in the .text section and is ready to run but it does not run automatically. When you call it directly or through a pointer the CPU jumps to the address in .text and executes the code.

Non-static functions are global and behave the same in memory. They also live in .text and only run when called. The difference is that other files can call them directly because they are visible globally.

Using static keeps control and avoids name conflicts while still existing in memory like any other function. Passing a pointer to a static function does not create a new copy, it just gives access to the same code in .text.

The .text section contains **machine code**, which is basically what assembly (ASM) compiles down to. When you write C code and compile it, the compiler translates it into assembly instructions, and then the assembler and linker turn that into **binary instructions** that live in the .text section.

So the CPU doesn’t see your C code or even the assembly text you wrote. It sees the **binary opcodes** in .text and executes them directly when a function is called.

You can think of .text as the **final machine-level version of all your code**, ready for the CPU to run.

Everything in .text is executable, and that’s why it’s separate from sections that store variables or uninitialized memory.


It can be fun if we, as a team, begin to write and probably learn from each other, see different perspectives, and improve. When I write, I jump around a lot; I don’t write in sections. It’s like, oh, this just came to mind, so I write about it, or I write about the moment when I write code. My name is Pirasath Luxchumykanthan. I hope you can join so we can mix this document with different items or topics. There are many different ways to learn and improve. Jumping around like this might make it harder to follow, but it also lets the reader experience the train of thought and connect ideas themselves instead of just passively reading a rigid structure.


“Use if statements during setup; rely on optimized structures during runtime (I will explain later what I mean by this).”


Earlier I made a macro named Void. It was static void. When we talk about C89 and a void function, and we do not send a parameter, we must include one parameter. This parameter tells the compiler that we promise this function takes no parameters. In C99 it is allowed not to do this, but as we work in C89, we must make that promise.

So basically, if we write the "end" function, it will look like this:

```c
Void End(void) {
  
}
```
So as you can see, we have this (void) in C89. Now you know what it means.

Now we can change the WMSR and add End. It will look like this:

```c
WMSR(TaskHandler, &End, FUNCTIONS COMING LATER) {
// Start
}
```
We use & because we need to get the pointer to that function, and to get the pointer we use &.

A pointer is an area in memory that stores the address of some data. If we say NULL, we declare that it has no pointer. When we create a pointer, the CPU and the system, in this case Linux, will provide a unique address for it.

How many addresses can exist depends on the architecture. For a 32-bit CPU, the maximum address is the maximum value of a 32-bit unsigned integer. For a 64-bit CPU, the maximum address is the maximum value of a 64-bit unsigned integer.

The kernel object itself isn’t strictly x86, but the reason people often talk about x86 or x86_64 in Linux kernel contexts is because of the CPU architecture the kernel is compiled for. Linux kernels are architecture-specific. When you compile a kernel, it targets a specific CPU architecture such as x86, x86_64, ARM, etc. This determines the pointer size, which is 32 bits on x86 and 64 bits on x86_64, the CPU instructions the kernel can use, how virtual and physical memory is addressed, and how system calls, registers, and stack frames are structured.

So when we say a kernel object is x86 or x86_64, we mean it is compiled for that CPU architecture, which affects the pointer size, alignment, and how the kernel accesses memory. On x86_64 Linux, kernel objects are 64-bit, and pointers are 64-bit, giving access to much larger memory. The logic of kernel objects is the same across architectures, but the memory addresses and sizes depend on the CPU type.

When we talk about task and that’s what we mainly going to do now it’s good to have some kind of system a wrapper that wrap around the task. Many tasks can have steps like 1 2 3 4 and so on. If we make a new task on top of another task we need to stop or replace or change a step on the go. This is a benefit if we already know where the CPU is it will go fast. Maybe we can’t stop all but we can cancel and save a lot of cycles in the CPU if we get a new task. What I mean by this is data is still in memory and we are changing data but some data we already know is going to change so why change it with the old data. This can be stopped. If we have full control it’s important to keep in mind when we make functions.  

Many developers don’t think like this but it’s a big problem and can make software slower. The minus side of this is we make a lot of pointers to different functions and a lot of functions, but the good side is we save a lot of CPU cycles. What we need to respect is the CPU not the code.

Today developers make a function and call it directly. This is a big problem because there is no step. For low-level developers like me, I see it as wrong coding. Maybe it can be right, I can’t make the choice for you. In my world, I see step functions, helper functions, and next step functions.

What I see from this text I just made is that a helper function is basically a helper to a step function. If this step function fails, then don’t go to the next step or go to another step. It needs to point to the right step and skip some steps. Not everything needs to be done. Important steps need to be done, like expiry time. If we say expiry time 10 seconds but we already add a buffer of 2 seconds, now it is 11 seconds at the moment. Why call the function that updates the time for that 10 second expiry?

It is like a step can say what the next step is. In Linux, I don’t see any kind of structure that does that, but we can make it. I have tested this way and I will say this is the most effective way to handle tasks. It also needs to allow running multiple steps on the go. It sounds like a really messed up world, but if we just make a wrapper or handler that does this, then everything later will be easier.



We cannot be 100% certain, but we can say it is almost okay. We can use the Linux workqueue header file because a task is based in RAM and the CPU is just looping. We can detect when it is pending or not pending, or set a time limit. The CPU loops fast in RAM, but it is important to know when a task is pending or not. This is also an important note when making choices about what to do and preparing other tasks or a self-test system.

We cannot control how much RAM a user uses. They may have many other programs running like an email server or something else, and we do not need to care about that. We just need to make rules on the go for what each job needs to do. We can base our calculations and decisions on the information we have to prepare other possible tasks and create a self-test system with rules.

We can prepare and register a function, record how long it takes, and then choose another way to handle other tasks. We can decide if something is important or if it can run later. There are many aspects that need to be handled when designing a function.

If you remember the text RX 20,833 and TX 20,833, well it would be a big dream if we could do that. But this is the real number. Now we know the CPU and Linux work in a work_struct system. How does this make this a fake number? Okay, let me explain. WQ_DFL_MAX_ACTIVE just limits how many can run simultaneously. It can be 512, less, or more, depending on cores.

The calculation is like this: cores * WQ_DFL_MAX_ACTIVE. For example, 16 cores * 512 = 8,192. That means we can run 8,192 work_structs right now in the moment, in the split second. But again, we can’t see other programs.

We keep that number and make the judgment of when to run what. As fast as possible, we end a function and let others come in. We need to look at the maximum delay, what we humans can see with our eyes, when the packet will come to the client. We need to focus on what to send first and have a better view about eyes and brain.

Okay, for example, how long does it take for you to read a text? 20 nanoseconds(ns) or more?

Humans notice delays above roughly 100 to 200 milliseconds, which is 100,000,000 ns to 200,000,000 ns. I found this information in human factor research and HCI studies, such as *The Humane Interface* by Jef Raskin and papers about human perceptual thresholds.

So basically, if we can make a function that stays within 150,000,000 ns, it basically means streaming. Other tasks can have a delay that is not streaming. The CPU is fast enough to handle this, but we cannot overload it. We need multiple servers and gateways to provide the best view for the client. The client may not even know how many servers they are connected to, but we can control that in the background.

Do you want me to do that next?


Remember, we are not responsible for the connection between the client and their ISP.

But we can notice if they have a bad internet connection between them and their ISP.

In this development process I need to make NetworkHandler at the same time I make TaskHandler. When we work with a Linux system we must allow, handle, or reject actions and do small system tasks. Think of it like a firewall. A firewall detects attack patterns and prepares responses. It is good to have a firewall on the server, but it is not enough. If the server detects an attack it should send a block command to the firewall or upstream via an API so the CPU can focus on the tasks that need to run instead of processing attack traffic.


The reason I write like this, jumping between ideas, is that it helps in learning and shows my upgrades at the same time. I write step by step so you can see the actions I take. The code itself will change, but the README does not need to change every time. I can simply note where I updated or improved something, making it easier for others to get ideas. Every day brings new ideas and new ways to improve. The best way is always getting better.


After all we’ve talked about and all these ideas, have we actually installed the server yet? Let’s do that so we can turn things around and get into the mindset of what we can build or come up with.

If we go to [https://www.kernel.org/](https://www.kernel.org/), it’s the same as [https://github.com/torvalds/linux](https://github.com/torvalds/linux). There are updates almost every day, though not all of them are necessary for everyone.

We can basically build everything ourselves, which gives us more control. But for now, let’s make sure we’re working with the newest Linux version.

The next step will be a guide on how to upgrade your hosting provider’s Linux version to the latest Linux kernel, along with a better understanding of how Linux works.


Layer by layer. What I mean by this is that a server or hardware is built layer by layer. I’m trying to make this documentation, tutorial, or story fun. Just like everything has layers, this README also has layers.

Don’t get confused. It’s okay to keep reading or start over from the top. Maybe a lightbulb will go off now or later, but understanding comes slowly, and relearning is perfectly fine. If you get confused, just read from the top again.

Im not sure if you need to install a fresh Linux system or need to upgrade.
But if you plan to install a fresh new system, that is not possible because kernel.org does not provide a full operating system.
It only provides the Linux kernel part, not the user space or the installer.
That means it does not include any package manager, tools, or other components that make it possible to install like an ISO system.
To make it installable, you would need to build your own image, add a bootloader, add user space programs, and then create a bootable ISO.
So kernel.org is only used to build or upgrade an existing kernel, not to install a full system.
I am going to do it over SSH.
SSH means Secure Shell, it is a network protocol that allows you to connect to another machine remotely, and it uses port 22 by default.
This way you can upgrade or control the kernel directly without reinstalling the full system.
Remember port 22, we are not going to block it or work with it in this system for now. Maybe later we can build a system that can block and open it on demand, but for now this port will stay open. It is a port, not everyone needs access to it.

Basically, I use Debian. I don’t care what version, because we are going to upgrade it to the newest kernel release candidate. I don’t know why it’s called a release candidate, but we are going to talk about what’s inside Linux itself and maybe use something from it or improve it.

Before installing the kernel, we need to install the newest GCC. There will always be a new version, but we are going to use GCC for C89. We never know who will manage the userspace.

For the Linux kernel, using the newest GCC doesn’t change the language features used in the kernel, because it still sticks to C89. So, in that sense, it doesn’t make a difference for writing kernel code.

But for userspace programs and learning, it is recommended to use the newest GCC. For the kernel, however, it does not matter.

If we are going to understand GCC, it is a compiler; it simply compiles code to different CPU architectures. It is old and works well. There are many alternatives, like Clang, but GCC has been on the market for a long time and they have done a great job. Not everything can be done in GCC, but we will come back to that later. On this server, with many user tasks, we are going to use GCC, specifically C89, and build a lot of DSLs and functions that can make many things possible.


Before we install GCC on Debian, we need to know where to place it and how to remember to place it there. We also need to know how to download it. This will be the next few steps before installing the newest kernel.

First, we need to log in via SSH. You are probably using Windows, so we need to use an SSH terminal. We can use PowerShell, which Windows provides. I don’t know if you have an old version of PowerShell, but if you do, you can download the latest version. I will search for PowerShell on Microsoft; you will probably get a link like this: [https://learn.microsoft.com/en-us/powershell/](https://learn.microsoft.com/en-us/powershell/).

If not, try searching for or typing “download newest PowerShell for Windows.” You will probably get a link. Follow the guide on that page to install it.

To use SSH in PowerShell, you need to type:

```powershell
ssh username@server_ip
```

The username is usually `root`. The host should provide both the username and password. The first time you connect, it will ask you to verify the server's fingerprint. Follow the prompt, and then you will enter the remote system, which will look like you are logged in directly on the server.

Here’s a clear overview of the **standard Linux filesystem hierarchy**:

* **`/`** – Root directory. Everything starts here.
* **`/bin`** – Essential binaries (commands needed for booting and repairing).
* **`/sbin`** – Essential system binaries (for system administration, usually root-only).
* **`/etc`** – Configuration files for system and services.
* **`/dev`** – Device files (hardware devices like disks, terminals).
* **`/proc`** – Virtual filesystem with process and kernel info.
* **`/sys`** – Virtual filesystem for kernel and device info.
* **`/usr`** – Secondary hierarchy for user programs and data:

  * `/usr/bin` – Most user commands.
  * `/usr/sbin` – Non-essential system binaries.
  * `/usr/lib` – Libraries for binaries.
  * `/usr/share` – Architecture-independent data.
* **`/var`** – Variable data like logs, mail, databases.
* **`/tmp`** – Temporary files.
* **`/home`** – User home directories.
* **`/boot`** – Bootloader and kernel images.
* **`/opt`** – Optional software packages.
* **`/lib`** – Essential shared libraries for binaries in `/bin` and `/sbin`.

This is the **core standard layout**, used by almost all Linux distributions.

Don’t worry, we will go through many of these folders, and you will understand each or almost each one. Some folders I basically ignore, like `/boot`, which is where Linux lives. Then we have `/opt` and `/home` ( yes ), you got the point. I will only talk about the folders that I feel are important.

`/tmp` is a folder that is usually cleared on boot or every 10 days. Placing files in `/tmp` is useful for deleting source code once it has been built, as it is no longer needed. Therefore, `/tmp` is a good place to temporarily store GCC and kernel sources if you forget to delete them later.

Before installing GCC and the libraries it requires, it is always good to make sure your system is up to date. You can do this by running:

```bash
apt-get update
apt-get install build-essential wget tar libgmp-dev libmpfr-dev libmpc-dev
cd /tmp
wget https://ftp.gnu.org/gnu/gcc/gcc-x.x.x/gcc-x.x.x.tar.xz
tar -xf gcc-x.x.x.tar.xz
cd gcc-x.x.x
./contrib/download_prerequisites
cd /usr/local/src
mkdir gcc-build
cd gcc-build
../gcc-x.x.x/configure --enable-languages=c,c++ --disable-multilib --prefix=/usr/local/gcc-x.x
nohup make -j1 > build.log 2>&1 &

```

Remember that "x.x.x" refers to the version number.  
You can find the latest GCC release here: [GCC releases](https://gcc.gnu.org/pub/gcc/releases/)

It can take a long time to install GCC, but once it’s installed, we won’t need to do it again. GCC is very capable and can compile for many CPU architectures. This installation of the compiler only needs to be done on **one server**, the **builder server** or **developer server**.

Remember, we need to **split the environment** between the client and developer servers. As developers, we should only access the client server when we need to make updates; otherwise, we don’t touch it.


But again, the easy part is that we can upload the kernel (`vmlinuz`) to GitHub, and then we can feed the server with the new iPXE. **iPXE** is an open-source network boot firmware that allows computers to boot over the network instead of relying on local storage. By using iPXE, the server can fetch the latest kernel and necessary boot files directly from our GitHub release, load them into RAM, and start running without needing a full OS installation on disk. This makes updates fast, centralized, and easy to manage across multiple servers.


How often will updates be needed? Well, we need an **automated system** to handle this. Sometimes, when running kernel objects, parts of Linux may be outdated, but if we minimize Linux dependencies, we save effort.
GitHub has a date system that allows us to check when a release was published, and it also provides an API and webhooks. We will explore these options in more detail later.

The key is to make sure the **headers we use don’t become incompatible**. Basically, we follow what Linux does. In practice, big changes rarely happen; they usually just make some things easier.

If you accidentally log off SSH or lose connection, you can recover and see where you left off by running:

```bash
cd /usr/local/src/gcc-build
tail -f build.log
```
When it's finished, you can do the same:
```bash
nohup make install > install.log 2>&1 &
```



Would you like me to make it sound a bit more technical or keep this simple style?



**⚠️ WARNING ⚠️**: You just upgraded your knowledge a lot! Handle it wisely. problem its i can provide a link but micrsoft change link all the time..



---

💫 Building in progress, check back for updates

