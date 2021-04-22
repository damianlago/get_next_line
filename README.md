# **get_next_line**
This function will read content line by line from a file descriptor and return it without the newline. May it be a file, stdin or even a network connection. 

---

*This function is made using a static variable only, and is able to manage multiple fd.
*If you call get_next_line inside a while in your main, it will return all content from fd line by line.
*Function Read use the BUFFER_SIZE defined during compilation.

---

## Getting started
```c
$ git clone https://github.com/damianlago/get_next_line.git
$ cd get_next_line
$ gcc get_next_line.c get_next_line_utils.c get_next_line.h 

// You can change the size of BUFFER_SIZE before compilation.
 gcc -D BUFFER_SIZE=xx get_next_line.c get_next_line_utils.c get_next_line.h 

```
---
