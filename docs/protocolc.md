# protocol.c 

As I mentioned in earlier explanations : every source file or header file (header optional) should start with a metadata of what that file is, when it is created, in some cases I even include the description of what it is about (not here, I have made an entire docs in this case.). You should also do so.(you would not regret it.)

### Metadata Section 

This is purely for human reference and using `sed` for organising my code. The standard will be useful for other fellow programmers - telling them at each file that : **fr (friend), use c 23 standard.** By doing so, you don't use a different C standard while compiling and miss a feature. (Honestly, the C 23 brings many features - search web.)

```c 
// name : protocol.c 
// date : 2026-06-27 
// std  : C 23 standard 

```

## `extern` finds these definitions.

The `extern`s used in the `protocol.h` file will find the correct signature definitions from this include file. If you defined it elsewhere in another file, you get a multiple definitions error. 

**And guess what?** What do you think will give this error? compiler, assembler or linker?

>[!WARNING]
> If you got it right, then you are right. It should be a compiler right? **Nah**. If you **read a couple of books, most importantly and first of all - the error message itself**, you will notice it is an error from the linker. Below are the set of proof of concept (I call them experimentation code) codes that will make you understand what happened. 

### The Setup 

Suppose we have two source files using same header, and doing the following. The sources are `headers.c` and `anotherconstant.c` with the header file named `constant.h`

**headers.c**

```c 
// name : headers.c 
// date : 2026-06-29 
// std  : C 23 standard 


// how to compile this : gcc headers.c anotherconstant.c -o main 

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include "constant.h"

const char* constant = "help";
const char* realconstant = "hello?";

//--------------------------------------- main program ----------------------------------
int main(void) {
    

    // with 'constant' being available in both the headers. 
    printf("This was redefined in another file: %s\n", constant);
    printf("This was from anotherconstant.c: %s\n", anotherconstant);
    printf("This was from constant.c: %s\n", realconstant);    
    return EXIT_SUCCESS;
}


```


**anotherconstant.c**

```c
// name : anotherconstant.c 
// date : 2026-06-29 
// std  : C 23 standard 

#include "constant.h"

const char* anotherconstant = "another";
const char* constant = "help";
```


**constant.h**

```c
#pragma once 

extern const char *constant;
extern const char *anotherconstant;
extern const char *realconstant;
```


**Compile it :**

If you read the code above, you would have finished compiling by now. And there comes this error. (I suspect you are not a NixOS user.)

```txt
/usr/bin/ld: /tmp/ccf5HVKo.o:(.data.rel.local+0x8): multiple definition of `constant'; /tmp/ccZYdZ35.o:(.data.rel.local+0x0): first defined here
collect2: error: ld returned 1 exit status

```
Now take your own time understanding the error. I do it by following these steps. 

1) Read that error message: try to highlight stuffs. 

2) Assume that you know the error message : try to figure out something by doing a guess work of what could be going behind. 

3) Now Verify your assumption by mathematical contradiction.

4) Do a google search if your verification worked.

5) Last and most importantly, fix the code. 

### The socket path 

