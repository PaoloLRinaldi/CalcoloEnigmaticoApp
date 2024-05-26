#ifndef CALC_ENIG_GENERATOR_H
#define CALC_ENIG_GENERATOR_H

//#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
//#include <iterator>
//#include "fast_input.h"
#include "big_lib.h"
#include <ctime>
//#include <cstdlib>
#include <stdexcept>
//#include <cmath>
#include <utility>
#include "ui_mainwindow.h"
//#include "mainwindow.h"

struct complex_type {
  int top1, top2;
  int low1, low2;
};

struct table {
    int num_mat[3][3];
    std::string char_mat[3][3];
    char opers[2][3];
    std::vector<int> n_to_c;
    Ui::MainWindow *u;

private slots:
    void on_pushButton_released();
    void on_pushButton_toggled(bool checked);
    void on_pushButton_2_released();
    void on_elem12_1_4_textEdited(const QString &arg1);
};

std::vector<int> gen_vec(const std::vector<int>&);
bool next(std::vector<int>&, std::vector<int>&);
bool unique (std::vector<int>& not_num);

template <class T> inline void p_vec(const T& v) {
  for (const auto &a : v)
    std::cout << a << " ";
  std::cout << std::endl;
}
int stoint(const std::string& s, const std::vector<int>& vec);
void mat_conv(const std::string (*ms)[3][3], int (*mn)[3][3], const std::vector<int>& v);
inline int oper(const int a, const char op, const int b) {
  return op == '+' ? a + b :
         op == '-' ? a - b :
    op == '/' ? ((a < b || !b || (a && a % b)) ? throw std::domain_error("Divisione non buona") : a / b) : a * b;
}
inline bool check_oper(int a, int b, int c, const char op) {
  try {
    int ret = oper(a, op, b);
    return ret == c;
  } catch (std::domain_error) {
    return false;
  }
}
template<class T, class K>
void p_panel(const T mn, const K op, std::ostream& out);
double difftime(std::clock_t begin, std::clock_t end);
inline unsigned long int fact(unsigned long int n) {
  if (n == 1 || n == 0)
    return 1;
  else
    return n * fact(n - 1);
}
inline unsigned long int coef_bin(unsigned long int a, unsigned long int b) {
  return fact(a) / (fact(a - b) * fact(b));
}
bool no_zero_on_left(const std::string (*ms)[3][3], const std::vector<int>& vec);
std::vector<std::vector<int>> array_to_vec_nums(const int (*mn)[3][3]);
std::vector<std::vector<char>> array_to_vec_ops(const char (*op)[2][3]);
bool solve_it(const std::string (&char_mat)[3][3], const char (&opers)[2][3], table & tab);
//std::string my_dir();
//std::vector<file_info> getls_str(const std::string& dir);
bool next_oper(char (&op)[2][3]);
//int nrand(int n);
complex_type exp_to_complex(const int a, const char op1, const int b, const char op2);
std::pair<int, int> x_finder(complex_type &elem1, complex_type &elem2);
inline int oper_to_num(const char op) {
  return op == '+' ? 0 :
    op == '-' ? 1 :
    op == '*' ? 2 : 3;
}
inline char num_to_oper(const int num) {
  return num == 0 ? '+' :
    num == 1 ? '-' :
    num == 2 ? '*' : '/';
}
bool complete_table(int (&cm)[3][3], const char (&op)[2][3]);
inline bool good_num(const int a) {
  return a > 0 && a <= 9999;
}
std::vector<int> num_to_char_mat(const int (&nm)[3][3], std::string (&cm)[3][3]);
bool table_quality(const int (&nm)[3][3]);
inline int initial_num_gen() {
  int random = nrand(100);
  if (random <= 5)
    return nrand(9) + 1;
  else if (random <= 55)
    return nrand(90) + 10;
  else if (random <= 95)
    return nrand(900) + 100;
  else
    return nrand(9000) + 1000;
}
bool save_table(int (&num_mat)[3][3], std::string (&char_mat)[3][3], const char (&opers)[2][3], table &tab);
//old_main() -> int(&)[3][3];
void old_main(table &);






#endif // CALC_ENIG_GENERATOR_H
