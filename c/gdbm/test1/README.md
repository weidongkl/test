# example to use gdb.h

### To compile this example
```bash
gcc example.c -lgdbm -o example
```

To run it, you will need an example database. The easiest way to create it is by using the gdbtool program, which is part of the gdbm package (see gdbmtool):
```bash
$ gdbmtool test.gdbm store foo bar
```
This creates database file test.gdbm and stores a single record in it. The record’s key is ‘foo’, and the value is ‘bar’. Now you can run the example program to see how it works:

```bash
$ ./example test.gdbm foo
bar
$ ./example test.gdbm baz
no such key
```
