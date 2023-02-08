#include <check.h>

#include "s21_string.h"

START_TEST(test_memchr) {
  const char* buff = "ASDFGHJK1234!@#$";
  char* buff2 = s21_memchr(buff, 'G', 5);
  char* buff3 = memchr(buff, 'G', 5);
  ck_assert_ptr_eq(buff2, buff3);
  ck_assert_str_eq(buff2, buff3);
  buff2 = s21_memchr(buff, 'G', 4);
  ck_assert_ptr_null(buff2);
  buff2 = s21_memchr("", 'G', 5);
  ck_assert_ptr_null(buff2);
  buff2 = s21_memchr(buff, '\0', 25);
  buff3 = memchr(buff, '\0', 25);
  ck_assert_ptr_eq(buff2, buff3);
  ck_assert_str_eq(buff2, buff3);
}
END_TEST

START_TEST(test_memcmp) {
  const char* buff = "ASDFGHJK1234!@#$";
  const char* buff1 = "ASDFGHJK1234!@#$";
  ck_assert_int_eq(memcmp(buff, buff1, 0), s21_memcmp(buff, buff1, 0));
  ck_assert_int_eq(memcmp(buff, buff1, 10), s21_memcmp(buff, buff1, 10));
  buff = " ";
  buff1 = "ASDFGHJK1234!@#$";
  ck_assert_int_eq(memcmp(buff, buff1, 0), s21_memcmp(buff, buff1, 0));
  ck_assert_int_eq(memcmp(buff, buff1, 10), s21_memcmp(buff, buff1, 10));
  buff = "";
  buff1 = "";
  ck_assert_int_eq(memcmp(buff, buff1, 0), s21_memcmp(buff, buff1, 0));
  ck_assert_int_eq(memcmp(buff, buff1, 10), s21_memcmp(buff, buff1, 10));

  buff = "ASDFGHJK1234!@#$/0asd";
  buff1 = "A/0SDFGHJK1234!@#$";
  ck_assert_int_eq(memcmp(buff, buff1, 100), s21_memcmp(buff, buff1, 100));
}
END_TEST

START_TEST(test_memcpy) {
  char str1[20] = "1112151ergergfg515";
  char str2[20] = "                    ";
  char str3[20] = "%hf*-5";
  char str4[20] = "                    ";
  char str5[30] = "";
  char str6[] = "4444";
  char str7[] = "123\0123";
  ck_assert_str_eq(s21_memcpy(str1, str2, 4), memcpy(str1, str2, 4));
  ck_assert_str_eq(s21_memcpy(str3, str4, 5), memcpy(str3, str4, 5));
  ck_assert_str_eq(s21_memcpy(str5, str6, 4), memcpy(str5, str6, 4));
  ck_assert_str_eq(s21_memcpy(str5, str7, 5), memcpy(str5, str7, 5));
}
END_TEST

START_TEST(test_memmove) {
  char str1[] = "11werwer15";
  char str2[s21_strlen(str1)];
  char str3[] = "s_21\n\t";
  char str4[s21_strlen(str3)];
  ck_assert_str_eq(s21_memmove(str2, str1, s21_strlen(str1)),
                   memmove(str2, str1, s21_strlen(str1)));
  ck_assert_str_eq(s21_memmove(str3, str4, s21_strlen(str3)),
                   memmove(str3, str4, s21_strlen(str3)));
}
END_TEST

START_TEST(test_memset) {
  char str[16] = "ASDFGHJK1234";
  ck_assert_str_eq(memset(str, 'a', 1), s21_memset(str, 'a', 1));
  ck_assert_str_eq(memset(str, '\0', 10), s21_memset(str, '\0', 10));
  ck_assert_str_eq(memset(str, 'k', 5), s21_memset(str, 'k', 5));
}
END_TEST

START_TEST(test_strcat) {
  char str1[30] = "what's go";
  char str11[30] = "ing on";
  char str2[30] = "Car";
  char str12[30] = "aaamba";
  ck_assert_str_eq(strcat(str1, str11), s21_strcat(str1, str11));
  ck_assert_str_eq(strcat(str2, str12), s21_strcat(str2, str12));
  char str001[30] = "opa";
  char str0011[30] = "popa";
  ck_assert_str_eq(strcat(str001, str0011), s21_strcat(str001, str0011));
}
END_TEST

START_TEST(test_strncat) {
  char str14[30] = "what's go";
  char str15[30] = "ing on";
  char str16[30] = "Car";
  char str17[30] = "aaamba";
  ck_assert_str_eq(strncat(str14, str15, 5), s21_strncat(str14, str15, 5));
  ck_assert_str_eq(strncat(str16, str17, 3), s21_strncat(str16, str17, 4));
}
END_TEST

START_TEST(test_strchr) {
  char str24[30] = "what's going on";
  ck_assert_str_eq(strchr(str24, 't'), s21_strchr(str24, 't'));
}
END_TEST

START_TEST(test_strcmp) {
  char str25[50] = "1112151515";
  char str26[50] = "11121sdfsdf";
  char str27[50] = "1112dasdasda12312sdas5";
  char str28[50] = "1112dasdasda12312sdas5";
  ck_assert_int_eq(strcmp(str25, str26), s21_strcmp(str25, str26));
  ck_assert_int_eq(strcmp(str27, str28), s21_strcmp(str27, str28));
}
END_TEST

START_TEST(test_strncmp) {
  char str29[50] = "1112151515";
  char str30[50] = "11121sdfsdf";
  char str31[50] = "1112d&*&a12312sdas5";
  char str32[50] = "1112d&*&a12312sdas5";
  char str1[] = "equal";
  char* str2 = "equaly";
  char* str3 = "qwert";
  char* str1oo = "123@##%@";
  char* str2oo = "123@@$??";
  char* num = "123456789";
  char* numd = "123456788";
  char* nums = "123456";
  char* end = "123\n";
  char* eof = "\0";
  char* eof1 = "1\0";
  int n = 4;
  ck_assert_int_eq(strncmp(str1, str1, 6), s21_strncmp(str1, str1, 6));
  ck_assert_int_eq(strncmp(str1, str2, 5), s21_strncmp(str1, str2, 5));
  ck_assert_int_eq(strncmp(str1, str3, 1), s21_strncmp(str1, str3, 1));
  ck_assert_int_eq(strncmp(str1, "equal", 2), s21_strncmp(str1, "equal", 2));
  ck_assert_int_eq(strncmp(str1oo, str2oo, 10),
                   s21_strncmp(str1oo, str2oo, 10));
  ck_assert_int_eq(strncmp(num, nums, n), s21_strncmp(num, nums, n));
  ck_assert_int_eq(strncmp(nums, nums, 6), s21_strncmp(nums, nums, 6));
  ck_assert_int_eq(strncmp(nums, nums, 12), s21_strncmp(nums, nums, 12));
  ck_assert_int_eq(strncmp(num, end, n), s21_strncmp(num, end, n));
  ck_assert_int_eq(strncmp(num, numd, 9), s21_strncmp(num, numd, 9));
  ck_assert_int_eq(strncmp(nums, numd, 10), s21_strncmp(nums, numd, 10));
  ck_assert_int_eq(strncmp(eof, eof, n), s21_strncmp(eof, eof, n));
  ck_assert_int_eq(strncmp(eof, eof, 0), s21_strncmp(eof, eof, 0));
  ck_assert_int_eq(strncmp(eof, eof1, 1), s21_strncmp(eof, eof1, 1));
  ck_assert_int_eq(strncmp(eof, eof1, n), s21_strncmp(eof, eof1, n));
  ck_assert_int_eq(strncmp(str29, str30, 10), s21_strncmp(str29, str30, 10));
  ck_assert_int_eq(strncmp(str29, str30, 3), s21_strncmp(str29, str30, 3));
  ck_assert_int_eq(strncmp(str31, str32, 10), s21_strncmp(str31, str32, 10));
  ck_assert_int_eq(strncmp(str31, str32, 1), s21_strncmp(str31, str32, 1));
  ck_assert_int_eq(strncmp(str31, str31, 10), s21_strncmp(str31, str31, 10));
}
END_TEST

START_TEST(test_strcpy) {
  char str33[50] = "1112151ergergfg515";
  char str34[s21_strlen(str33)];
  ck_assert_str_eq(strcpy(str34, str33), s21_strcpy(str34, str33));
  char str333[50] = "1112151\0";
  char str344[50] = "ssssdddddfffffggggg1231231231231";
  ck_assert_str_eq(strcpy(str344, str333), s21_strcpy(str344, str333));
}
END_TEST

START_TEST(test_strncpy) {
  char str35[50] = "1112151ergergfg515";
  char str36[s21_strlen(str35)];
  ck_assert_str_eq(strncpy(str36, str35, 5), s21_strncpy(str36, str35, 5));
  char str351[50] = "1112151\0";
  char str361[50] = "ssssdddddfffffggggg1231231231231";
  ck_assert_str_eq(strncpy(str361, str351, 4), s21_strncpy(str361, str351, 4));
  char str355[50] = "1112151ergergfg515";
  char str365[s21_strlen(str355)];
  ck_assert_str_eq(strncpy(str365, str355, 49),
                   s21_strncpy(str365, str355, 49));
}
END_TEST

START_TEST(test_strcspn) {
  char str37[50] = "11121s5151s5";
  char str38[50] = "ddds";
  ck_assert_int_eq(strcspn(str37, str38), s21_strcspn(str37, str38));
  char str39[50] = "11121s5151s5";
  char str40[50] = "ddd";
  ck_assert_int_eq(strcspn(str39, str40), s21_strcspn(str39, str40));
}
END_TEST

/*START_TEST(test_strerror) {
  ck_assert_str_eq(strerror(EPERM), s21_strerror(EPERM));
  ck_assert_str_eq(strerror(ENOBUFS), s21_strerror(ENOBUFS));
  ck_assert_str_eq(strerror(ENOTSOCK), s21_strerror(ENOTSOCK));
}
END_TEST*/

START_TEST(test_strerror) {
  for (int i = -123; i < 0; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
  for (int i = 0; i <= 106; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
  for (int i = 107; i <= 234; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}

END_TEST

START_TEST(test_strpbrk) {
  char str41[50] = "11121s5151s5";
  char str42[50] = "ddds";
  ck_assert_ptr_eq(strpbrk(str41, str42), s21_strpbrk(str41, str42));
  char str43[50] = "11121s5151s5";
  char str44[50] = "ddd";
  ck_assert_ptr_eq(strpbrk(str43, str44), s21_strpbrk(str43, str44));
}
END_TEST

START_TEST(test_strrchr) {
  char str45[50] = "what's going on";
  ck_assert_ptr_eq(strrchr(str45, 't'), s21_strrchr(str45, 't'));
  ck_assert_ptr_eq(strrchr(str45, 'c'), s21_strrchr(str45, 'c'));
}
END_TEST

START_TEST(test_strspn) {
  char str46[50] = "11121sssss1111110000111111111111111111111111111111";
  char str47[50] = "11121s";
  ck_assert_int_eq(strspn(str46, str47), s21_strspn(str46, str47));
  char str48[50] = "11121s5151s5";
  char str49[50] = "1dd";
  ck_assert_int_eq(strspn(str48, str49), s21_strspn(str48, str49));
  char str50[50] = "11121s5151s5";
  char str51[50] = "ddd";
  ck_assert_int_eq(strspn(str50, str51), s21_strspn(str50, str51));
}
END_TEST

START_TEST(test_strlen) {
  char str52[50] = "11121s5151s5";
  ck_assert_int_eq(strlen(str52), s21_strlen(str52));
}
END_TEST

START_TEST(test_strstr) {
  char str55[50] = "11121s5151s5";
  char str56[50] = "111";
  ck_assert_ptr_eq(strstr(str55, str56), s21_strstr(str55, str56));
  ck_assert_str_eq(strstr(str55, str56), s21_strstr(str55, str56));
  char* str = "";
  char* str1 = "equal";
  char* str2 = "qual";
  char* str3 = "quf";
  char* str15 = "123";
  char* str25 = "123qwerty123q";
  char* eof = "\0";
  char* null = "\n";
  char* nulls = "12345678\n";
  ck_assert_pstr_eq(strstr("qwerty", "qwe"), s21_strstr("qwerty", "qwe"));
  ck_assert_pstr_eq(strstr(str1, str2), s21_strstr(str1, str2));
  ck_assert_pstr_eq(strstr(str1, str), s21_strstr(str1, str));
  ck_assert_pstr_eq(strstr(str1, str3), s21_strstr(str1, str3));
  ck_assert_pstr_eq(strstr(str15, str25), s21_strstr(str15, str25));
  ck_assert_ptr_eq(strstr(null, str), s21_strstr(null, str));
  ck_assert_ptr_eq(strstr(null, str2), s21_strstr(null, str2));
  ck_assert_ptr_eq(strstr(null, eof), s21_strstr(null, eof));
  ck_assert_ptr_eq(strstr(str1, eof), s21_strstr(str1, eof));
  ck_assert_ptr_eq(strstr(str, eof), s21_strstr(str, eof));
  ck_assert_ptr_eq(strstr(nulls, null), s21_strstr(nulls, null));
}
END_TEST

START_TEST(test_strtok) {
  char str57[100] = "It's       not a     bug, it's a feature.";
  char str58[100] = "It's       not a     bug, it's a feature.";
  char* parser = " ,.";
  char* strOrigin = strtok(str57, parser);
  char* st21 = s21_strtok(str58, parser);
  while (strOrigin != NULL) {
    strOrigin = strtok(NULL, parser);
    st21 = s21_strtok(NULL, parser);
    ck_assert_pstr_eq(strOrigin, st21);
  }
}
END_TEST

Suite* s21_20_functions(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("sprintf_functions");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_memchr);
  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcpy);
  tcase_add_test(tc_core, test_memmove);
  tcase_add_test(tc_core, test_memset);
  tcase_add_test(tc_core, test_strcat);
  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strcmp);
  tcase_add_test(tc_core, test_strncmp);
  tcase_add_test(tc_core, test_strcpy);
  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_strcspn);
  tcase_add_test(tc_core, test_strerror);
  tcase_add_test(tc_core, test_strpbrk);
  tcase_add_test(tc_core, test_strrchr);
  tcase_add_test(tc_core, test_strspn);
  tcase_add_test(tc_core, test_strlen);
  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strtok);

  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_s_sprintf) {
  char str[100];
  char str2[100];

  ck_assert_int_eq((int)s21_sprintf(str, "Hello %s", "medgarha"),
                   (int)sprintf(str2, "Hello %s", "medgarha"));
  ck_assert_int_eq(s21_sprintf(str, "Hello %-s", "medgarha"),
                   sprintf(str2, "Hello %-s", "medgarha"));
  ck_assert_int_eq(s21_sprintf(str, "Hello %-20s", "medgarha"),
                   sprintf(str2, "Hello %-20s", "medgarha"));
  ck_assert_int_eq(s21_sprintf(str, "Hello %-10.20s", "medgarha"),
                   sprintf(str2, "Hello %-10.20s", "medgarha"));
  ck_assert_int_eq(s21_sprintf(str, "Hello %-.20s", "medgarha"),
                   sprintf(str2, "Hello %-.20s", "medgarha"));
  ck_assert_int_eq(s21_sprintf(str, "Hello %21.20s", "medgarha"),
                   sprintf(str2, "Hello %21.20s", "medgarha"));
  ck_assert_int_eq(
      s21_sprintf(str, "Hello %21.20s and %-2.4s", "medgarha", "school"),
      sprintf(str2, "Hello %21.20s and %-2.4s", "medgarha", "school"));
}
END_TEST

START_TEST(test_c_sprintf) {
  char str[100];
  char str2[100];

  ck_assert_int_eq(s21_sprintf(str, "Hello school %c %lc", '2', '&'),
                   sprintf(str2, "Hello school %c %lc", '2', '&'));
  ck_assert_int_eq(s21_sprintf(str, "Hello school %-c %c %%%%", '2', '1'),
                   sprintf(str2, "Hello school %-c %c %%%%", '2', '1'));
}
END_TEST

START_TEST(test_d_sprintf) {
  char str[100];
  char str2[100];

  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = %d ! = %d", +4, -1),
                   sprintf(str2, "2 + 2 = %d ! = %d", +4, -1));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = %-d ! = %+d", 4, 10),
                   sprintf(str2, "2 + 2 = %-d ! = %+d", 4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = % -d ! = %+-d", +4, 10),
                   sprintf(str2, "2 + 2 = % -d ! = %+-d", +4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = % 10d ! = %+-20d", -4, 10),
                   sprintf(str2, "2 + 2 = % 10d ! = %+-20d", -4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = % 10.d ! = %+-20.20d", 0, -182),
                   sprintf(str2, "2 + 2 = % 10.d ! = %+-20.20d", 0, -182));
  ck_assert_int_eq(
      s21_sprintf(str, "2 + 2 = % 10.hd ! = %+-20.20ld", 4, 276892067102856),
      sprintf(str2, "2 + 2 = % 10.hd ! = %+-20.20ld", (short)4,
              276892067102856));

  ////////////////////////////
  char buff[100];
  char buff2[100];

  int f = s21_sprintf(buff2, "blblbblblc%c%+4d%+.d", '$', 10000, 0);
  int s = sprintf(buff, "blblbblblc%c%+4d%+.d", '$', 10000, 0);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "blblbblblc%c%+4d", '$', 10);
  s = sprintf(buff, "blblbblblc%c%+4d", '$', 10);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "blblbblblc%c%+-10d", '$', 10);
  s = sprintf(buff, "blblbblblc%c%+-10d", '$', 10);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "blblbblblc%c%+10d%5d%+5d", '$', 10, 0, -1);
  s = sprintf(buff, "blblbblblc%c%+10d%5d%+5d", '$', 10, 0, -1);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "blblbblblc%c%+2.5d", '$', 10);
  s = sprintf(buff, "blblbblblc%c%+2.5d", '$', 10);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "%+.5d %+6.5d %+.5d %+6.5d %-2d %-2.5d %-4.d", 10, 10,
                  -10, -10, 1, 10, 0);
  s = sprintf(buff, "%+.5d %+6.5d %+.5d %+6.5d %-2d %-2.5d %-4.d", 10, 10, -10,
              -10, 1, 10, 0);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);

  f = s21_sprintf(buff2, "%hd %hd", 32768, -10000000);
  s = sprintf(buff, "%hd %hd", (short)32768, (short)-10000000);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "%d %d", 2147483648, -21474836480);
  s = sprintf(buff, "%d %d", (int)2147483648, (int)-21474836480);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "%d %d", 2147483648, -21474836480);
  s = sprintf(buff, "%d %d", (int)2147483648, (int)-21474836480);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "%hu %hu", 65536, -65536);
  s = sprintf(buff, "%hu %hu", (unsigned short)65536, (unsigned short)-65536);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  /////////////////////////////////////////
}
END_TEST

START_TEST(test_i_sprintf) {
  char str[100];
  char str2[100];

  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = %i ! = %i", 4, 10),
                   sprintf(str2, "2 + 2 = %i ! = %i", 4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = %-i ! = %+i", 4, 10),
                   sprintf(str2, "2 + 2 = %-i ! = %+i", 4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = % -i ! = %+-i", 4, -10),
                   sprintf(str2, "2 + 2 = % -i ! = %+-i", 4, -10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = % 10d ! = %+-20i", 4, 10),
                   sprintf(str2, "2 + 2 = % 10i ! = %+-20i", 4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = % 10.i ! = %+-20.20i", 4, -10),
                   sprintf(str2, "2 + 2 = % 10.i ! = %+-20.20i", 4, -10));
  ck_assert_int_eq(
      s21_sprintf(str, "2 + 2 = % 10.hi ! = %+-20.20li", -4, +276892067102856),
      sprintf(str2, "2 + 2 = % 10.hi ! = %+-20.20li", (short)-4,
              +276892067102856));
}
END_TEST

START_TEST(test_u_sprintf) {
  char str[100];
  char str2[100];

  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = %d ! = %u", -4, 10),
                   sprintf(str2, "2 + 2 = %d ! = %u", -4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = %-d ! = %u", 4, 10),
                   sprintf(str2, "2 + 2 = %-d ! = %u", 4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = % -i ! = %-u", 4, 10),
                   sprintf(str2, "2 + 2 = % -i ! = %-u", 4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = % 10d ! = %-20u", 4, 10),
                   sprintf(str2, "2 + 2 = % 10d ! = %-20u", 4, 10));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = % 10.i ! = %-20.20u", 4, 10),
                   sprintf(str2, "2 + 2 = % 10.i ! = %-20.20u", 4, 10));
  ck_assert_int_eq(
      s21_sprintf(str, "2 + 2 = %10.hu ! = %-20.20lu", 4, 276892067102856),
      sprintf(str2, "2 + 2 = %10.hu ! = %-20.20lu", (unsigned short)4,
              276892067102856));
}
END_TEST

START_TEST(test_f_sprintf) {
  char str[100];
  char str2[100];

  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = %f ! = %f", -4.21, +42.21),
                   sprintf(str2, "2 + 2 = %f ! = %f", -4.21, +42.21));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = %-f ! = %+f", -4.21, +42.21),
                   sprintf(str2, "2 + 2 = %-f ! = %+f", -4.21, +42.21));
  ck_assert_int_eq(s21_sprintf(str, "2 + 2 = %-10f ! = %+12f", -4.21, +42.21),
                   sprintf(str2, "2 + 2 = %-10f ! = %+12f", -4.21, +42.21));
  ck_assert_int_eq(
      s21_sprintf(str, "2 + 2 = %- 10.f ! = %+12.5f", -4.21, +42.21),
      sprintf(str2, "2 + 2 = %- 10.f ! = %+12.5f", -4.21, +42.21));
  ck_assert_int_eq(
      s21_sprintf(str, "2 + 2 = %- 10.f ! = %+12.5lf", -4.21, +42.21),
      sprintf(str2, "2 + 2 = %- 10.f ! = %+12.5lf", -4.21, +42.21));
}
END_TEST

Suite* s21_sprintf_functions(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("sprintf_functions");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s_sprintf);
  tcase_add_test(tc_core, test_c_sprintf);
  tcase_add_test(tc_core, test_d_sprintf);
  tcase_add_test(tc_core, test_i_sprintf);
  tcase_add_test(tc_core, test_u_sprintf);
  tcase_add_test(tc_core, test_f_sprintf);

  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_upper_lower) {
  char* buff = "ASDFGHJK1234!@#$4";
  char* buff2 = "asdfghjk1234!@#$4";
  char* buff3 = s21_to_lower(buff);
  ck_assert_str_eq(buff2, buff3);
  free(buff3);
  buff3 = s21_to_upper(buff2);
  ck_assert_str_eq(buff, buff3);
  free(buff3);
  buff2 = NULL;
  buff3 = s21_to_upper(buff2);
  ck_assert_ptr_null(buff3);
  buff2 = NULL;
  buff3 = s21_to_lower(buff2);
  ck_assert_ptr_null(buff3);
  buff3 = s21_to_upper("");
  ck_assert_str_eq("", buff3);
  free(buff3);
  buff3 = s21_to_lower("");
  ck_assert_str_eq("", buff3);
  free(buff3);

  char* p_buffer1 = NULL;
  char reference1[256] = "1234_ABCDABCD!?.,|\\\"\n\0";
  char test1[256] = "1234_abcdABCD!?.,|\\\"\n\0";

  p_buffer1 = s21_to_upper(test1);
  ck_assert_pstr_eq(p_buffer1, reference1);
  free(p_buffer1);

  char* p_buffer2 = NULL;
  char* test2 = NULL;

  p_buffer2 = s21_to_upper(test2);
  ck_assert_ptr_null(p_buffer2);

  char* p_buffer3 = NULL;
  char* test3 = "";

  p_buffer3 = s21_to_upper(test3);
  ck_assert_pstr_eq(p_buffer3, test3);
  free(p_buffer3);

  p_buffer1 = NULL;
  char test12[256] = "1234_abcdABCD!?.,|\\\n\"\0";
  char reference12[256] = "1234_abcdabcd!?.,|\\\n\"\0";

  p_buffer1 = s21_to_lower(test12);
  ck_assert_pstr_eq(p_buffer1, reference12);
  free(p_buffer1);

  p_buffer2 = NULL;
  test2 = NULL;

  p_buffer2 = s21_to_lower(test2);
  ck_assert_ptr_null(p_buffer2);

  p_buffer3 = NULL;
  test3 = "";

  p_buffer3 = s21_to_upper(test3);
  ck_assert_pstr_eq(p_buffer3, test3);
  free(p_buffer3);
}
END_TEST

// START_TEST(test_inserts) {
//   char* buff = "0123456789";
//   char* buff2 = "9999";
//   char* buff3 = s21_insert(buff, buff2, 0);
//   ck_assert_str_eq("99990123456789", buff3);
//   free(buff3);
//   buff3 = s21_insert(buff, buff2, 2);
//   ck_assert_str_eq("01999923456789", buff3);
//   free(buff3);
//   buff3 = s21_insert(buff, buff2, 25);
//   ck_assert_ptr_null(buff3);

//   char* p_buffer1 = NULL;
//   char src1[256] = "Hello, My name is ILYA\n";
//   char str1[256] = "World! ";
//   size_t start_index = 7;
//   char reference1[256] = "Hello, World! My name is ILYA\n";

//   p_buffer1 = s21_insert(src1, str1, start_index);
//   ck_assert_pstr_eq(p_buffer1, reference1);
//   free(p_buffer1);

//   char* p_buffer2 = NULL;
//   char src2[256] = "Hello. I like school 21\n";
//   char str2[256] = ", World! My name is ILYA";
//   size_t start_index2 = 5;
//   char reference2[256] = "Hello, World! My name is ILYA. I like school 21\n";

//   p_buffer2 = s21_insert(src2, str2, start_index2);
//   ck_assert_pstr_eq(p_buffer2, reference2);
//   free(p_buffer2);

//   // char* p_buffer3 = NULL;
//   // char src3[7] = "Hello ";
//   // char str3[256] = ", World! My name is ILYA";
//   // size_t start_index3 = 10;

//   // p_buffer3 = s21_insert(src3, str3, start_index3);
//   // ck_assert_ptr_null(p_buffer3);
//   // free(p_buffer3);
// }
// END_TEST

START_TEST(test_trims) {
  char* buff = "     '''''asdfADASSA5522 ASasdaspqp112212'''''    ";
  char* buff2 = " '2";
  char* reference = "asdfADASSA5522 ASasdaspqp11221";
  char* buff3 = s21_trim(buff, buff2);
  ck_assert_str_eq(reference, buff3);
  free(buff3);

  buff = "                   ";
  buff2 = " ";
  buff3 = s21_trim(buff, buff2);
  ck_assert_str_eq("", buff3);
  free(buff3);

  buff = NULL;
  buff2 = " ";
  buff3 = s21_trim(buff, buff2);
  ck_assert_ptr_null(buff3);

  char* p_buffer1 = NULL;
  char src1[256] = "***////Hello, My name is D*ck.****////";
  char trim_chars1[256] = "*/";
  char reference1[256] = "Hello, My name is D*ck.";

  p_buffer1 = s21_trim(src1, trim_chars1);
  ck_assert_pstr_eq(p_buffer1, reference1);
  free(p_buffer1);

  char* p_buffer2 = NULL;
  char src2[256] = "            ";
  char trim_chars2[256] = " ";
  char reference2[256] = "";

  p_buffer2 = s21_trim(src2, trim_chars2);
  ck_assert_pstr_eq(p_buffer2, reference2);
  free(p_buffer2);

  char* p_buffer3 = NULL;
  char* src3 = NULL;
  char trim_chars3[256] = " ";

  p_buffer3 = s21_trim(src3, trim_chars3);
  ck_assert_ptr_null(p_buffer3);
  free(p_buffer3);
}
END_TEST

Suite* s21_void_func_suite(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("additional_func");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_upper_lower);
  // tcase_add_test(tc_core, test_inserts);
  tcase_add_test(tc_core, test_trims);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite* suite[] = {s21_20_functions(), s21_sprintf_functions(),
                    s21_void_func_suite(), NULL};
  int failed_count = 0;
  int flag = EXIT_SUCCESS;

  for (int i = 0; suite[i]; ++i) {
    SRunner* suite_runner = srunner_create(suite[i]);
    srunner_set_fork_status(suite_runner, CK_NOFORK);
    srunner_run_all(suite_runner, CK_NORMAL);
    failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }

  if (failed_count != 0) {
    flag = EXIT_FAILURE;
  }
  return flag;
}
