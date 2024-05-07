#include "minunit.h"
#include "lcthw/bstrlib.h"

char *test_bfromcstr()
{
	char *word = "hi"; // check cstr
	bstring check1 = bfromcstr(word);
	PRINT_s(check1->data);

	word = word + 2; // check to '\0' ptr
	bstring check2 = bfromcstr(word);
	PRINT_s(check2->data);
	PRINT_int(check2->mlen);
	PRINT_int(check2->slen);

	check2 = bfromcstr("Hello");
	printf("Char is %c\n", bchar(check2, 4));
	PRINT_s(check2->data);
	PRINT_int(check2->mlen);
	PRINT_int(check2->slen);

	char *word2;
	word2 = calloc(15, 1);
	word2 = strcpy(word2, "Hello world");
	check2 = bfromcstr(word2);
	mu_assert(blength(check2) == 11, "Size of check2 incorrect");

	word2[3] = '\0';
	bstring check3 = bfromcstr(word2);
	mu_assert(bchar(check3, 0) == 'H', "First symbol of string incorrect");
	check3->data[3] = 'b';
	PRINT_s(bdata(check3));
	// mu_assert(strcmp(word2, bdata(check3)) == 0, "Both string should be equal to <Hel>");
	mu_assert(check3->mlen == 8, "minimun size must be 8");
	mu_assert(check3->slen == 3, "length pure size is 3");
	mu_assert(blength(check3) == 3, "Presumed 3 length");

	return NULL;
}

char *test_blk2bstr()
{
	char *word = "yuriy";
	bstring b = blk2bstr(word, 3);
	char *bd = bdata(b);
	int rc = strcmp("yur", bd);
	mu_assert(rc == 0, "Both string should be equal to yur");
	PRINT_int(blength(b));

	return NULL;
}

char *test_bstrcpy()
{
	bstring a, b;
	a = blk2bstr("hello world", 5);
	b = bstrcpy(a);
	char *ad = bdata(a);
	char *bd = bdata(b);
	int rc = strcmp(ad, bd);
	mu_assert(rc == 0, "Both string should be equal to hello");
	PRINT_s(bd);
	PRINT_p(a);
	PRINT_p(b);

	return NULL;
}

char *test_bassign()
{
	bstring a, b;
	b = blk2bstr("yes", 3);
	a = blk2bstr("hello world", 10);
	bassign(b, a);
	char *ad = bdata(a);
	char *bd = bdata(b);
	int rc = strcmp(ad, bd);
	mu_assert(rc == 0, "Both string should be equal to hello");
	PRINT_s(bd);
	PRINT_p(a);
	PRINT_p(b);
	PRINT_int(b->mlen);

	return NULL;
}

char *test_bassigncstr()
{
	char *a = NULL;
	a = calloc(12, 1);
	a = strcpy(a, "hello world");
	bstring b = NULL;
	b = blk2bstr("init", 10);
	bassigncstr(b, a);
	char *bd = bdata(b);
	int rc = strcmp(a, bd);
	mu_assert(rc == 0, "string c not assign correctly");
	PRINT_s(a);
	PRINT_s(bd);

	return NULL;
}

char *test_bassignblk()
{
	char *a = NULL;
	a = calloc(12, 1);
	a = strcpy(a, "hello world");
	bstring b = NULL;
	b = blk2bstr("init", 5);
	bassignblk(b, a, 12);
	char *bd = bdata(b);
	int rc = strcmp(a, bd);
	mu_assert(rc == 0, "string c not assign correctly");
	PRINT_s(a);
	PRINT_s(bd);

	return NULL;
}

char *test_bdestroy()
{
	bstring b = NULL;
	b = blk2bstr("init", 5);
	bdestroy(b);
	b = blk2bstr("second", 10);
	bdestroy(b);
	b = NULL;
	mu_assert(b == NULL, "bstring after destroy should be NULL");

	return NULL;
}

char *test_bconcat()
{
	bstring a, b;
	b = blk2bstr("yes ", 3);
	a = blk2bstr("hello world", 10);
	bconcat(b, a);
	char *bd = bdata(b);
	int rc = strcmp(bd, "yes hello world") == 0;
	mu_assert(rc == 0, "Concat doesn't work");

	return NULL;
}

char *test_bstricmp()
{
	bstring a = bfromcstr("AAAAA");
	bstring b = bfromcstr("BBBBB");
	bstring c = bfromcstr("AAAAA");
	mu_assert(bstricmp(a, b) < 0, "a should be greater than b");
	mu_assert(bstricmp(a, c) == 0, "a should be greater than b");

	return NULL;
}

char *test_biseq()
{
	bstring a = bfromcstr("AAAAA");
	bstring b = bfromcstr("BBBBB");
	bstring c = bfromcstr("AAAAA");
	mu_assert(biseq(a, b) == 0, "a should be greater than b");
	mu_assert(biseq(a, c) == 1, "a should be greater than b");

	return NULL;
}

char *test_binstr()
{
	bstring a = bfromcstr("Blabla opa bla");
	bstring b = bfromcstr("opa");
	bstring c = bfromcstr("opra");

	mu_assert(binstr(a, 0, b) == 7, "a should be greater than b");
	mu_assert(binstr(a, 0, c) == -1, "a should be greater than b");

	return NULL;
}

char *test_bfindreplace()
{
	bstring a = bfromcstr("Blabla opa bla");
	bstring b = bfromcstr("opa");
	int size = blength(a);
	bfindreplace(a, b, bfromcstr("focus"), 0);
	mu_assert(blength(a) == size + 2, "control length of str a after replace");
	PRINT_s(bdata(a));

	return NULL;
}

char *test_bsplit()
{
	bstring a = bfromcstr("Bla opa focus bla");

	struct bstrList *new = bsplit(a, ' ');
	UPTO(new->qty)
	PRINT_s(bdata(new->entry[i]));

	return NULL;
}

char *test_bformat()
{
	char *word = "hello";
	int num = 100;
	float fn = 10.5;
	bstring a = bformat("My word is %s with num %d and float %f", word, num, fn);
	char *ab = (char *)bdata(a);
	printf("%s\n", ab);	   // bdata test
	char ch = bchar(a, 1); // bchar test
	printf("CHAR is %c\n", ch);
	int x = blength(a);
	PRINT_int(x); // blength test

	return NULL;
}

char *all_tests()
{
	mu_suite_start();
	mu_run_test(test_bfromcstr);
	mu_run_test(test_blk2bstr);
	mu_run_test(test_bstrcpy);
	mu_run_test(test_bassign);
	mu_run_test(test_bassigncstr);
	mu_run_test(test_bassignblk);
	mu_run_test(test_bassignblk);
	mu_run_test(test_bdestroy);
	mu_run_test(test_bconcat);
	mu_run_test(test_bstricmp);
	mu_run_test(test_biseq);
	mu_run_test(test_binstr);
	mu_run_test(test_bfindreplace);
	mu_run_test(test_bsplit);
	mu_run_test(test_bformat); // + blength +bdata +bchar

	return NULL;
}

RUN_TESTS(all_tests);