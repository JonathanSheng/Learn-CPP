This repo will serve as a journal as I learn C++, including beginner topics to more advanced topics, such as concurrency, memory, design patterns, etc.


## Debugging

Debug -> Step Into

"Step Into" executes each line starting from main() and executes each line individually

"Step over" executes the next line, but if the next line is a function, the debugger doesn't dive into the function's lines. This is mostly used if we know a function is correct and we can skip the deep dive into the function. This will still execute the function and its value, but we won't step into the function itself.

"Step out" executes the remaining code in the function and returns control.

"Run to Cursor" executes the debugger and stops when it reaches the line that our cursor is on.

"Continue" just continues the program as per usual, until termination or breakpoint

"Breakpoint" is a marker that stops execution.

"Watch window" to show the values of variables as you debug.

"Call stack" helps us see the function call order.

## Memory
We work in bytes (at least 8 bits). This means that the computer can access addresses that are staggered by 8 contiguous bits of memory.
`sizeof` grants the size of a data type in bytes

Measuring an object size:
1. Calculate the size of all NON static members
1. Order of data members matter, byte alignment matters, so we should leave chars towards the end since they're small, and larger primitives in the beginning
1. Size of immediate base class that it derives
1. Inheritance, the pointer has an overhead as well

Data Alignment:
Every object/data type has a size and alignment. If the alignment is 4 for example (int), then the address has to be divisible by 4.
Most of the time, the alignment is the same as the size. This varies for structures, where it is a multiple of the largest member.
We need address alignment because on different CPU architectures, performance issues can arise. Misaligned data can result in cache invalidation and additional cycles in order to read the information.
If we think about it, if we know int is 4 bytes and alignment 4 bytes, this allow the CPU to assume where to look in the address space to find it quickly and derive that it will require the next 4 bits. If it's misaligned, we now have to search (i+1), (i+2) and (i+3) to see where the data lies.

For example, if we had
```

long long x {0};

char* y = reinterpret_cast(char*)(&x);
int* ptr = reinterpret_cast<int*>(y+1); //This line moves the address by +1 byte

return *ptr;

```
this program will receive an undefined error and a complaint about misalignment.

For Structs, our alignment is the order of our members. If our alignment is like 
```
Struct X
{
	short (2)
	char (1)
	int* (8)
	float (4)
}
```
then we'll have to waste 8-(2+1) spaces since int* has to align on 8.
Additionally, the alignment by default is the alignment of the largest member in the struct.
At the end, the structure will grant additional padding to match the alignment so we have 

2 + 1 (5 empty)

8

4 (4 empty padding at end)

9 wasted bytes.
The reason why we have padding at end is intuitive. The reason is because if we have an `array<Struct X>`, we need to ensure each element in the array is properly aligned. They can be held back to back due to this padding.

Fun fact: an empty lambda has a size of 1 byte. Interesting because they are considered a data type.