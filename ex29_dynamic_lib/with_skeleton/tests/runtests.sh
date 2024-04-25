echo "Running unit tests:"

for i in tests/*_tests
do
    if test -f $i
    then
        if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so print_a_message "hello world" 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            #exit 1
        fi
        if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so uppercase "hello world" 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            #exit 1
        fi
         if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so lowercase "HELLO tHere" 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            #exit 1
        fi
         if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so fail_on_purpose "i fail" 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            #exit 1
        fi
          if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so fail_on_purpose 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            #exit 1
        fi
         if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so adfasfasdf asdfadff 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            #exit 1
        fi
             if $VALGRIND ./$i ./build/libx.so adfasfasdf asdfadff 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            #exit 1
        fi
    fi
done

echo ""
