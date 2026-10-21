### Program Structure

1. Import necessary headers. Note that I also imported `<string.h>` to use `strcmp()` & `strcpy()`, if anyone cares.

2. The helper function `processList()` takes an array of words, then prints out the word count per word. I did this by creating a type named `Dict` which behaves like a tuple `(name, count)` that stores informatino about a word and how many times it appears in the input array. Iterating through the input array, if an array element matches a `Dict` object's `name` member field, we simply increase the `count` field of the same object by `1`. If the whole array does not contain any existing word within our `Dict` array, then we create a new `Dict` object inside the `Dict` array which holes a tuple `([WORD_NAME], 1)`.

3. Now we can start creating child processes. The 3 child processes are created one after another like so:

```c
pid_t pids[3]; // array that holds p0, p1, p2

for (size_t i=0; i<3; i++){
    pids[i] = fork(); // this creates the child process
    /* child process codes */
}
```

If an error is encountered during the process of childbirth, `fork()` will return a negative integer, it's caught and thrown and the entire process exits:

```c
if (pids[i] < 0) {
    /* error handling code */
}
```

Else, `fork()` returns `0` and we can proceed to obtain the child's pid with `getpid()`. A switch statement is used to distinguish with array to feed to the child. Then we call `processList()` on that fed array.

Finally, we terminate the finished child processes with `waitpid()`. 

### How to compile

1. In the same directory as `Makefile`, run:

```shell
make
```

This will yield an executable named `main.out`.

### How to execute

1. In the same directory as `main.out`, run:

```shell
./main.out
```



