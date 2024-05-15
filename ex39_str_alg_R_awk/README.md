1. in makefile change skeleton - line 35 was $(LIBS)-for dinamic linking became $(TEST_SRC) $(TARGET) for static compaling - line 36 delete $(TESTS) - + line 37 added $(CC) $(CFLAGS) -o $(TESTS)

2. (line 1) -rdynamic - reset implicit declarasion of function
3. (line 1) -isrc - include path for searching, it's a hint for compailer
4. in tests/runtests.sh added in line 16 if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so uppercase "hello world" 2>> tests/tests.log

In ex37 added in src 2 files (darray.c and darray.h) from ex34
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Команда для выборки нужный цифр из логов
cat times.log | awk -F'COUNT:' '/:/{print $2}' | awk -F',' '{print $1}' >> times2.log

было
RUN --- 9
DEBUG tests/string_algos_tests.c:111: SCAN COUNT: 31628000, END TIME: 2, OPS: 15814000.000000
DEBUG tests/string_algos_tests.c:80: FIND COUNT: 1346000, END TIME: 2, OPS: 673000.000000
DEBUG tests/string_algos_tests.c:55: BINSTR COUNT: 11797000, END TIME: 2, OPS: 5898500.000000
RUN --- 10
DEBUG tests/string_algos_tests.c:111: SCAN COUNT: 32780000, END TIME: 2, OPS: 16390000.000000
DEBUG tests/string_algos_tests.c:80: FIND COUNT: 1401000, END TIME: 2, OPS: 700500.000000
DEBUG tests/string_algos_tests.c:55: BINSTR COUNT: 12374000, END TIME: 2, OPS: 6187000.000000

стало
31628000
1346000
11797000
32780000
1401000
12374000
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
for i in 1 2 3 4 5 6 7 8 9 10

do echo "RUN --- $i" >> times.log
./tests/string_algos_tests 2>&1 | grep COUNT >> times.log
done
>less times.log
> $ vim times.log
> +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
> times <- read.table("times.log", header=T)
> summary(times)
>       scan               find             binstr
>  Min.   :71195200   Min.   :6351300   Min.   :36811700
>  1st Qu.:74042200   1st Qu.:6358100   1st Qu.:37083800
>  Median :74820400   Median :6374750   Median :37147800
>  Mean   :74308760   Mean   :6427680   Mean   :37176830
>  3rd Qu.:74973900   3rd Qu.:6447100   3rd Qu.:37353150
>  Max.   :75343600   Max.   :6630400   Max.   :37549700

awk '/SCAN COUNT:/ { printf $5 "\t" };/FIND COUNT:/ {printf $5 "\t"} ;/BINSTR COUNT:/ {printf $5 "\n"} ;' times.log

echo "  scan     find     binstr" >> times3.log; awk '/SCAN COUNT:/ { printf substr($5,1,length($5)-1) "\t" };/FIND COUNT:/ {printf substr($5,1,length($5)-1) "\t"} ;/BINSTR COUNT:/ {printf substr($5,1,length($5)-1) "\t"} ; /STRSTR COUNT:/ {printf substr($5,1,length($5)-1) "\n"} ;' times.log >> times3.log

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 >R
 >times<-read.table("times3.log",header=T)

       scan    find   binstr
1  18880000 1397000 12571000
2  31216000 1371000 12057000
3  31792000 1397000 11381000
4  32036000 1402000 11728000
5  30908000 1398000 10811000
6  33672000 1418000 12382000
7  30552000 1316000 11746000
8  31060000 1326000 11765000
9  31628000 1346000 11797000
10 32780000 1401000 12374000
> summary(times)
      scan               find             binstr        
 Min.   :18880000   Min.   :1316000   Min.   :10811000  
 1st Qu.:30946000   1st Qu.:1352250   1st Qu.:11732500  
 Median :31422000   Median :1397000   Median :11781000  
 Mean   :30452400   Mean   :1377200   Mean   :11861200  
 3rd Qu.:31975000   3rd Qu.:1400250   3rd Qu.:12294750  
 Max.   :33672000   Max.   :1418000   Max.   :12571000 

echo "  scan     find     binstr    strstr" >> times.log; 
for i in 1 2 3 4 5 6 7 8 9 10
do 
./tests/string_algos_tests 2>&1 | awk '/SCAN COUNT:/ { printf substr($5,1,length($5)-1) "\t" };/FIND COUNT:/ {printf substr($5,1,length($5)-1) "\t"} ;/BINSTR COUNT:/ {printf substr($5,1,length($5)-1) "\t"} ; /STRSTR COUNT:/ {printf substr($5,1,length($5)-1) "\n"} ;' >> times.log
done


=====FOR output to file in R===========================
sink(file = "summary.txt")
summary(times)
sink(file = NULL)
