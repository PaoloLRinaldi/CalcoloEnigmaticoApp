#ifndef GUARD_fast_input
#define GUARD_fast_input

typedef struct f_info {
  char* name;
  bool is_dir;
} file_info;

void rmEcho();
void setEcho();

int kbhit();
int getch();

int getls (file_info **list, const char *dir);
void free_str_ltrl_array(file_info *list, int size);

int users_choice(const int a, const int b);


#endif