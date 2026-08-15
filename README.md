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