1. in makefile change skeleton - line 35 was $(LIBS)-for dinamic linking became $(TEST_SRC) $(TARGET) for static compaling
			       - line 36 delete $(TESTS)
			       - + line 37 added $(CC) $(CFLAGS) -o $(TESTS)

2. (line 1) -rdynamic - reset implicit declarasion of function
3. (line 1) -isrc - include path for searching, it's a hint for compailer
4. in tests/runtests.sh added in line 16  if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so uppercase "hello world" 2>> tests/tests.log


In ex37 added in src 2 files (darray.c and darray.h) from ex34
