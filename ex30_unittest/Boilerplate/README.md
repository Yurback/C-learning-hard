1. in makefile change skeleton - line 34 was $(TARGET) became $(LIBS)
2. (line 1) -rdynamic - reset implicit declarasion of function
3. (line 1) -isrc - include path for searching, it's a hint for compailer
4. in tests/runtests.sh added in line 16  if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so uppercase "hello world" 2>> tests/tests.log

