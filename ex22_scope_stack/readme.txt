1) Включаем в файл хедер прототипы для переменных и функций,
 #define, a так же библиотеки #include
 
 2) в .с файлы включаем #include "*.h" и определяем декларацию функций
 
 3) Сборку заспускаем либо одной командой
 gcc -Wall -g *.c -o ex22_main
 либо собираем объектные файлы .о(с кодом ассемблера) и затем 
 gcc -Wall -g  ex22_yr.c ex22_yr.o -o ex22_main
 
