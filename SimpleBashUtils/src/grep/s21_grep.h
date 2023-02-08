int match(char *string, char *pattern, regex_t *re);
int grep(char *text, char *search_str);
int flag_i(char *text, char *search_str);
char Lowercase_translation(char Sym);
typedef struct flags {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_s;
  int flag_h;
  int flag_o;
  int stop;
} flags;
int search_templates(int argc, char **argv, int templates[], flags *fl);
int search_files(int argc, char **argv, int files[], flags *fl);
int sum_flags(flags *fl);
int flag_o(flags *fl, char *string, char *search_string, int count_of_files,
           char *file);
void path(int count_of_files, char string[], flags *fl);
int flag_l(char *string, char *search_string, flags *fl, char files[]);
void get_opt(int argc, char **argv, flags *f);
void flag_c_calc(char *string, char *search_string, flags *fl, int *count);
int flag_n(char *string, char *search_string, flags *fl, int line_number, int,
           char *);
void flag_c(flags *fl, int count_for_c, int count_of_lines);
int flag_i_flag_v(char *string, char *search_string, flags *fl, int, char[]);
int check_flag_i_flag_v(flags *fl, char *string, char *search_string);