/* *************
   PLR
   
   ************* */

//SPAZIO DISPONIBILE CELL ZENFONE 3 MAX = 720 x 1092

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <fstream>
#include <iterator>
//#include "fast_input.h"
#include "calc_enig_generator.h"
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include <utility>
#include <QApplication>
#include <cassert>


using std::binary_search;
using std::copy;
using std::equal;
using std::find;
using std::find_if;
using std::max;
using std::min;
using std::partition;
using std::remove;
using std::remove_copy;
using std::remove_copy_if;
using std::remove_if;
using std::replace;
using std::reverse;
using std::search;
using std::sort;
using std::stable_partition;
using std::swap;
using std::transform;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;
using std::next_permutation;
using std::domain_error;
using std::clock;
using std::clock_t;
using std::ifstream;
using std::ofstream;
using std::rand;
using std::srand;
using std::sqrt;
using std::pair;


/**********************************************************/
/*
template <typename T>
inline std::ostream &bin_write(T elem, std::ostream &fos) {
    fos.write(reinterpret_cast<char*>(&elem), sizeof(elem));
    return fos;
}

template <typename T>
inline T get_binary_integer(std::istream &fis, bool is_little_endian = true) {
  char buf[sizeof(T)];
  fis.read(buf, sizeof(T));
  if (!is_little_endian)
    std::reverse(&buf[0], &buf[sizeof(T)]);
  T *d = reinterpret_cast<T*>(buf);
  return *d;
}

inline void update_bin_file(int num1, int num2, int num3, int sol, int n_th_inp, std::ofstream &fout) {
    fout.seekp(4);
    bin_write<int>(n_th_inp + 1, fout);
    // Li ho divisi in gruppi inglobati da parentesi
    fout.seekp((4) + (2 * sizeof(int)) + (4 * sizeof(int) * n_th_inp));
    bin_write<int>(num1, fout);
    bin_write<int>(num2, fout);
    bin_write<int>(num3, fout);
    bin_write<int>(sol, fout);
}
*/

void old_main(table & tab) {

    /*
    int inp_inserted = 0;
    ifstream fis_train("trainer.txt", std::ios::binary);
    if (fis_train.is_open()) {
        unsigned char c;
        c = get_binary_integer<unsigned char>(fis_train);
        if (c)
            throw std::domain_error("First byte not null!");
        c = get_binary_integer<unsigned char>(fis_train);
        if (c)
            throw std::domain_error("Second byte not null!");
        get_binary_integer<unsigned char>(fis_train);
        get_binary_integer<unsigned char>(fis_train);
        inp_inserted = get_binary_integer<int>(fis_train);
        fis_train.close();
    } else {
        ofstream fos_train("trainer.txt", std::ios::binary);
        bin_write<unsigned char>(0, fos_train);
        bin_write<unsigned char>(0, fos_train);
        unsigned char data_type = 0x0C;
        bin_write(data_type, fos_train);
        unsigned char n_dims = 2;
        bin_write(n_dims, fos_train);
        bin_write<int>(inp_inserted, fos_train);
        bin_write<int>(4, fos_train);  // 3 numeri + 1 soluzion
    }

    ofstream ftrain("trainer.txt", std::ios::binary | std::ios::in | std::ios::out);
    */


  char opers[2][3] = {{'+', '+', '+'}, {'+', '+', '+'}};  //riga, poi colonna
  //char opers[2][3] = {{'-', '+', '+'}, {'-', '+', '+'}};
  //char opers[2][3] = {{'-', '+', '*'}, {'-', '+', '*'}};
  //char opers[2][3] = {{'+', '/', '-'}, {'*', '*', '-'}};
  //char opers[2][3] = {{'*', '/', '-'}, {'+', '/', '/'}};
  //char opers[2][3] = {{'+', '*', '+'}, {'-', '*', '+'}};
  //char opers[2][3] = {{'-', '*', '+'}, {'/', '-', '-'}};  //DEBUGGARE QUESTO CASO (GIU' CI SONO I 3 NUNERI RELATIVI ALLO STESSO CASO (1))
  //char opers[2][3] = {{'-', '*', '+'}, {'/', '+', '-'}};  //DEBUGGARE QUESTO CASO (GIU' CI SONO I 3 NUNERI RELATIVI ALLO STESSO CASO (2))
  int num_mat[3][3];
  srand(time(NULL));

  do {

    num_mat[0][0] = initial_num_gen();
    num_mat[0][1] = initial_num_gen();
    num_mat[1][0] = initial_num_gen();


    //num_mat[0][0] = 7936;;
    //num_mat[0][1] = 7385;
    //num_mat[1][0] = 6403;

      //num_mat[0][0] = 85;
      //num_mat[0][1] = 102;
      //num_mat[1][0] = 66;

      //num_mat[0][0] = 57;
      //num_mat[0][1] = 30;
      //num_mat[1][0] = 60;

    //num_mat[0][0] = 345; //DEBUGGARE QUESTO CASO (1) (CON LE OPERAZIONI SOPRA)
    //num_mat[0][1] = 3;   //ASSIEME A QUESTO (1)
    //num_mat[1][0] = 77;  //ASSIEME A QUESTO (1)

    //num_mat[0][0] = 345; //DEBUGGARE QUESTO CASO (2) (CON LE OPERAZIONI SOPRA)
    //num_mat[0][1] = 3;   //ASSIEME A QUESTO (2)
    //num_mat[1][0] = 77;  //ASSIEME A QUESTO (2)
    
    bool a_good_one ;
    tab.u->genprogress->setValue(0);
    //tab.u->processEvents();
    QApplication::processEvents();
    int opers_tried = 0;

    do {
        ++opers_tried;
      
      a_good_one = false;
      
      if (find(&opers[0][0], &opers[1][2] + 1, '*') == &opers[1][2] + 1 &&
	  find(&opers[0][0], &opers[1][2] + 1, '/') == &opers[1][2] + 1)
	continue;
      
      for (int i = 0; i != 2; ++i)
	for (int j = 0; j != 3; ++j)
     // cout << opers[i][j] << " ";
    //  cout << endl;
        ;
      
      try {
          int tmp = oper(num_mat[0][0], opers[1][0], num_mat[0][1]);
    num_mat[0][2] = tmp;
        tmp = oper(num_mat[0][0], opers[0][0], num_mat[1][0]);
    num_mat[2][0] = tmp;
      } catch (std::domain_error e) {
//	cout << e.what() << endl;
          continue;
      }
      
      
      if (!good_num(num_mat[0][2]) ||
	  !good_num(num_mat[2][0])) {
//	cout << "Numeri troppo alti" << endl;
	continue;
      }

      
      complex_type comp1 = exp_to_complex(num_mat[0][2], opers[0][2], num_mat[1][0], opers[1][1]),
	comp2 = exp_to_complex(num_mat[2][0], opers[1][2], num_mat[0][1], opers[0][1]);

      pair<int, int> x;
      try {
	x = x_finder(comp1, comp2);
      } catch (std::domain_error e) {
    //cout << e.what() << endl;
	continue;
      } catch (std::logic_error) {
    //cout << "LOOOOOL" << endl;
      }

      string char_mat[3][3];

      if (x.first) {
    num_mat[1][1] = x.first;
    a_good_one = save_table(num_mat, char_mat, opers, tab);
    if (a_good_one) {

        copy(&(num_mat[0][0]), &(num_mat[2][3]), &(tab.num_mat[0][0]));
        copy(&(opers[0][0]), &(opers[1][3]), &(tab.opers[0][0]));
        // Lo so che è inutile fare inp_inserted++, ma fa capire.
        //update_bin_file(num_mat[0][0], num_mat[0][1], num_mat[1][0], 1, inp_inserted++, ftrain);
        return;
        //MainWindow::ui->LeditSayHello->setText(tr("YELLOW"));
    }
      }
      if (x.second && x.second != x.first) {
    //num_mat[1][1] = x.second;
    //a_good_one = save_table(num_mat, char_mat, opers);
      }
      tab.u->genprogress->setValue(opers_tried * 100 / 4096);
      QApplication::processEvents();
      //tab.u->processEvents();
      
    } while ((!a_good_one/* || cin.get()*/) && next_oper(opers));
    //update_bin_file(num_mat[0][0], num_mat[0][1], num_mat[1][0], 0, inp_inserted++, ftrain);
 //   cout << "YOLOOOO?" << endl;
  } while (1/* || cin.get()*/);

}
/**********************************************************/

bool solve_it(const string (&char_mat)[3][3], const char (&opers)[2][3], table &tab) {
  int int_mat[3][3];
  
  //clock_t begin = clock();  //Si fa partire il cronometro per sapere quanto ci metterà
  
  //Numero di simboli diversi, ovvero la lettera più alta
  char ch = 'a';
  for (int i = 0; i != 3; ++i) {
    for (int j = 0; j != 3; ++j) {
      for(string::const_iterator it = char_mat[i][j].begin(); it != char_mat[i][j].end(); ++it)
        if (*it > ch)
          ch = *it;
    }
  }
  
  const size_t sz = 9 - (ch - 'a'); //sz sarà il numero di simboli diversi
  auto max_combins = fact(10 - sz) * coef_bin(10, sz);  //Numero massimo di combinazioni possibili
  unsigned long int combins = 0;  //Combinazioni provate
    vector<int> not_num;   //Il numero che, visto come più cifre messe in fila, contiene le cifre non presenti nella tavola
    for (unsigned int i = 0; i != sz; ++i) not_num.push_back(i);
  
  vector<int> symbs(gen_vec(not_num));
  
  bool check_ok;
  
  vector<vector<vector<int>>> solutions;
  vector<vector<vector<char>>> opers_solutions;


  //DA QUI SI COMINCIANO A PROVARE TUTTE LE COMBINAZIONI
  int perc = -1;
  Difftime time_check;
  time_check.set_begin();
  int times_too_slow = 0;
  do {
    check_ok = false;
    ++combins;
    if (no_zero_on_left(&char_mat, symbs)) {
      mat_conv(&char_mat, &int_mat, symbs);
      /*
      for (int i = 0; i != 3; ++i) {
          for (int j = 0; j != 3; ++j)
              assert(int_mat[i][j] > 0 && int_mat[i][j] < 10000);
      }
      */
      for (int i = 0; i != 3; ++i) {
        if (!check_oper(int_mat[i][0], int_mat[i][1], int_mat[i][2], opers[1][i]))
          break;
        if (i == 2)
          check_ok = true;
      }
            
      if (check_ok) {
        for (int i = 0; i != 3; ++i) {
          if (!check_oper(int_mat[0][i], int_mat[1][i], int_mat[2][i], opers[0][i])) {
            check_ok = false;
            break;
          }
        }
      }
    }

    
    if (check_ok) {
      if (!solutions.empty()) return false;
      solutions.push_back(array_to_vec_nums(&int_mat));
      opers_solutions.push_back(array_to_vec_ops(&opers));
    }
    
    //L'if a seguire serve solo a printare il completamento
    if (perc != (int)((double)combins * 100 / max_combins)) {
      perc = (int)((double)combins * 100 / max_combins);
      //cout << not_num << endl;
      //cout << combins << "/" << max_combins << "   (" << (double)combins * 100 / max_combins << "%)" << endl;
      tab.u->solveprogress->setValue(perc);
      QApplication::processEvents();

      //Verifico che non ci stia mettendo troppo tempo
      if (time_check.ms_till_now() > 200) {
          ++times_too_slow;
      }
      if (time_check.ms_till_now() > 5000) {
        ofstream long_tabs(my_dir() + "gce2_proj/" + "long_tables.txt", std::ios::app);
        p_panel(int_mat, opers, long_tabs);
        p_panel(char_mat, opers, long_tabs);
        times_too_slow = 6; //così passa subito alla tabella dopo senza farti aspettare per 6 volte più di 5 secondi
        tab.u->solveprogress->setValue(0);
        return false;
      }
      if (times_too_slow > 5) {
        tab.u->solveprogress->setValue(0);
        return false;
      }
      time_check.set_begin();
    } //else if (time_check.ms_till_now() > 1000) return false;

    //assert(perc <= 100);

  } while (next(symbs, not_num));
  //QUI SI E' APPENA FINITO DI PROVARE TUTTE LE COMBINAZIONI

  tab.u->solveprogress->setValue(0);
  QApplication::processEvents();
  //tab.u->processEvents();
  
  //clock_t end = clock();
  
  //cout << endl << endl;
  
  int num_soluz = solutions.size();
  if (num_soluz) {
    
    /*ofstream fout(string(my_dir() + "calc_enig_generator_proj/" + string("solut") + (char)('0' + num_soluz) + ".txt").c_str(), std::ios::app);
    fout << endl << endl;
    fout << string(15, '*') << endl << endl;
    for (int i = 0; i != num_soluz; ++i) {
      p_panel(solutions[i], opers_solutions[i], fout);
      fout << endl << endl;
    }
    */
    //cout << "Tempo impiegato: " << difftime(begin, end) / 1000 << endl;
    if (num_soluz == 1) {
      //cout << "Trovata 1 soluzione!" << endl;
      return true;
    }
   /* else
      cout << "Trovate " << solutions.size() << " soluzioni!" << endl; */
  }
  /*else {
    cout << "Nessuna soluzione trovata." << endl;
  }*/


  return false;
}


/**********************************************************/
  
bool next(vector<int>& nums, vector<int>& not_nums) {
  
  if (next_permutation(nums.begin(), nums.end())) {}  //voglio la nuova permutazione e voglio anche sapere se va bene. Non serve il corpo dell'if
  else
    try {
      unique(not_nums);
      if (not_nums.empty()) throw domain_error("Non esiste soluzione");
      nums = gen_vec(not_nums);
    }
    catch (domain_error e) {
      cout << e.what() << endl;
      return false;
    }
  return true;
    
}

/**********************************************************/

vector<int> gen_vec(const vector<int>& num) {
  vector<int> ret;
  
    
  vector<int>::const_iterator it = num.begin(), end = num.end();
    
  for (int i = 0; i != 10; ++i) {
    if (it != end && i == *it)
      ++it;
    else
      ret.push_back(i);
  }
  return ret;
}
/**********************************************************/

inline
bool unique (vector<int>& not_num) {
  auto sz = not_num.size();
  if (not_num.empty()) return true;
  auto it = not_num.end();
  do {--it;}
  while (it != not_num.begin() - 1 && (*it)++ >= 10 - (not_num.end() - it));
  if (it == not_num.begin() - 1) throw domain_error("Non esiste soluzione");
  for (; it != not_num.end() - 1; ++it) *(it + 1) = *it + 1;
  return true;
  
}


/**********************************************************/

int stoint(const string& s, const vector<int>& vec) {
  int ret = 0, pow = 1;
  for (string::const_reverse_iterator it = s.rbegin(); it != s.rend(); ++it, pow *= 10)
    ret += vec[*it - 'a'] * pow;
  return ret;
}


/**********************************************************/

void mat_conv(const string (*ms)[3][3], int (*mn)[3][3], const vector<int>& v) {
  
  for (int i = 0; i != 3; ++i)
    for (int j = 0; j != 3; ++j)
      (*mn)[i][j] = stoint((*ms)[i][j], v);
}

/**********************************************************/
template<class T, class K>
void p_panel(const T mn, const K op, std::ostream& out) {
  out << mn[0][0] << '\t' << op[1][0] << '\t' << mn[0][1] << '\t' << "=" << '\t' << mn[0][2] << endl;
  out << op[0][0] << '\t' << '\t' << op[0][1] << '\t' << '\t' << op[0][2] << endl;
  out << mn[1][0] << '\t' << op[1][1] << '\t' << mn[1][1] << '\t' << "=" << '\t' << mn[1][2] << endl;
  out << "=" << '\t' << '\t' << "=" << '\t' << '\t' << "=" << endl;
  out << mn[2][0] << '\t' << op[1][2] << '\t' << mn[2][1] << '\t' << "=" << '\t' << mn[2][2] << endl;
  
}

/**********************************************************/



double difftime(std::clock_t begin, std::clock_t end) {
  //I due tempi sono di tipo clock_t e la funione è clock()
  //bisogna aggiungere using std::clock_t e using std::clock
  double diffticks = end - begin;
  double diffms = (diffticks) / (CLOCKS_PER_SEC/1000);
  return diffms;
}

/**********************************************************/

bool no_zero_on_left(const string (*ms)[3][3], const vector<int>& vec) {
  for (int i = 0; i != 3; ++i) {
    for (int j = 0; j != 3; ++j) {
      if (vec[(*ms)[i][j][0] - 'a'] == 0)
        return false;
    }
  }
  return true;
}

/**********************************************************/

vector<vector<int>> array_to_vec_nums(const int (*mn)[3][3]) {
  vector<vector<int>> ret;
  for (int i = 0;  i != 3; ++i)
    ret.push_back(vector<int>(std::begin((*mn)[i]), std::end((*mn)[i])));
  return ret;
}

/**********************************************************/

vector<vector<char>> array_to_vec_ops(const char (*op)[2][3]) {
  vector<vector<char>> ret;
  for (int i = 0;  i != 2; ++i)
    ret.push_back(vector<char>(std::begin((*op)[i]), std::end((*op)[i])));
  return ret;  
}

/**********************************************************/
/*

std::string my_dir() {
  static std::string directory;
  if (directory.empty()) {
    std::vector<file_info> this_dir_ls = getls_str("");
    std::vector<std::string> is_ubuntu;
    for (const auto& a : this_dir_ls) {
      is_ubuntu.push_back(a.name);
      free(a.name);
    }
    if (std::find(is_ubuntu.begin(), is_ubuntu.end(), "ubuntu.txt") == is_ubuntu.end()) {
      directory = "../../../../../../../../../../../../sdcard/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/";
    } else {
      directory = "../";
    }
  }
  return directory;
}
*/
/**********************************************************/
/*
std::vector<file_info> getls_str(const std::string& dir) {
  std::vector<file_info> ret;
  file_info *ls;
  
  int sz = getls(&ls, dir.c_str());
  std::copy(ls, ls + sz, std::back_inserter(ret));
  free(ls);
  
  return ret;
  
}
*/
/**********************************************************/

/*
int nrand(int n) {
  if (n <= 0 || n > RAND_MAX)
    throw std::domain_error("Argument to nrand is out of range");

  const int bucket_size = RAND_MAX / n;
  int r;

  do r = std::rand() / bucket_size;
  while (r >= n);

  return r;
}
*/
/**********************************************************/

complex_type exp_to_complex(const int a, const char op1, const int b, const char op2) {
  complex_type ret;

  if (op1 == '+' || op1 == '-') {
    if (op2 == '+' || op2 == '-') {
      ret.top1 = oper(a, op1, b);
      ret.top2 = op1 == op2 ? 1 : -1;
      ret.low1 = 1;
      ret.low2 = 0;
    } else if (op2 == '/') {
      ret.top1 = oper(0, op1, b);
      ret.top2 = a;
      ret.low1 = 0;
      ret.low2 = 1;
    } else {
      ret.top1 = a;
      ret.top2 = oper(0, op1, b);
      ret.low1 = 1;
      ret.low2 = 0;
    }
  } else if (op1 == '/') {
    if (op2 == '+' || op2 == '-') {
      ret.top1 = a;
      ret.top2 = 0;
      ret.low1 = b;
      ret.low2 = oper(0, op2, 1);
    } else if (op2 == '/') {
      ret.top1 = 0;
      ret.top2 = a;
      ret.low1 = b;
      ret.low2 = 0;
    } else {
      ret.top1 = a;
      ret.top2 = 0;
      ret.low1 = 0;
      ret.low2 = b;
    }
  } else {
    if (op2 == '+' || op2 == '-') {
      ret.top1 = a * b;
      ret.top2 = oper(0, op2, a);
      ret.low1 = 1;
      ret.low2 = 0;
    } else if (op2 == '/') {
      ret.top1 = a * b;
      ret.top2 = 0;
      ret.low1 = 0;
      ret.low2 = 1;
    } else {
      ret.top1 = 0;
      ret.top2 = a * b;
      ret.low1 = 1;
      ret.low2 = 0;
    }
  }
  
  return ret;
}

/**********************************************************/


pair<int, int> x_finder(complex_type &elem1, complex_type &elem2) {
  int a1, b1, c1, a2, b2, c2; //coefficienti equazione 2^ grado
  pair<int, int> ret;
  //Prodotto binomiale tra numeratore del primo e denominatore del secondo
  c1 = elem1.top1 * elem2.low1;
  b1 = elem1.top1 * elem2.low2 + elem1.top2 * elem2.low1;
  a1 = elem1.top2 * elem2.low2;
  //Prodotto binomiale tra numeratore del secondo e denominatore del primo
  c2 = elem2.top1 * elem1.low1;
  b2 = elem2.top1 * elem1.low2 + elem2.top2 * elem1.low1;
  a2 = elem2.top2 * elem1.low2;

  c1 -= c2;
  b1 -= b2;
  a1 -= a2;

  if (!a1) {
    if (!b1) {
      if (!c1)
	throw std::logic_error("Qualsiasi numero!");
      else
	throw std::domain_error("Impossibile");
    }
    if (!c1)
      throw std::domain_error("La x è 0");

    if ((long)b1 * c1 > 0) //Perché poi la c va a destra e cambia segno
      throw std::domain_error("La x è negativa");

    if (c1 % b1)
      throw std::domain_error("Numero razionale");

    ret.first = ret.second = -c1 / b1;
    return ret;
  }
  
  int discr = b1 * b1 - 4 * a1 * c1;
  
  if (discr < 0)
    throw std::domain_error("Numero complesso");

  int sqrt_discr = sqrt(discr);

  if (discr != sqrt_discr * sqrt_discr)
    throw std::domain_error("Numero reale");
  
  int numeratore1 = -b1 + sqrt_discr;
  int numeratore2 = -b1 - sqrt_discr;


  if (numeratore1 && numeratore1 % (2 * a1))
    ret.first = 0;
  else {
    ret.first = numeratore1 / (2 * a1);
    if (ret.first < 0 || ret.first > 9999)
      ret.first = 0;
  }
  
  
  if (numeratore2 && numeratore2 % (2 * a1))
    ret.second = 0;
  else {
    ret.second = numeratore2 / (2 * a1);
    if (ret.second < 0 || ret.second > 9999)
      ret.second = 0;
  }

  return ret;
}

/**********************************************************/


bool next_oper(char (&op)[2][3]) {
  int num = 0;

  for (int i = 0; i != 2; ++i) {
    for (int j = 0; j != 3; ++j) {
      num <<= 2;
      num += oper_to_num(op[i][j]);
    }
  }
    int check_num = num;
  //++num;
  --num;
    
  
  for (int i = 0; i != 2; ++i) {
    for (int j = 0; j != 3; ++j) {
      op[1 - i][2 - j] = num_to_oper(num & 3);
      num >>= 2;
    }
  }
  
  //if (num == 1) {
  //if (!(num & 1)) {  //ovvero finite le combinazioni di operazioni (4^6), prima era 4096 e spostato di 12 a destra mo è 1
  if (check_num == 1) {  //ovvero l'ultima combinazione è stata "+++++-" ovvero la prossima sarebbe "++++++" e quindi si ricomincerebbe
    /*
    for (int i = 0; i != 2; ++i)
      for (int j = 0; j != 3; ++j)
	cout << op[i][j] << " ";
	cout << endl;*/
    return false;
  }

  return true;
}

/**********************************************************/

bool complete_table(int (&nm)[3][3], const char (&op)[2][3]) {
  try { //nel caso ci sia una divisione
    nm[1][2] = oper(nm[1][0], op[1][1], nm[1][1]);
    nm[2][1] = oper(nm[0][1], op[0][1], nm[1][1]);
  } catch (std::domain_error) {
    return false;
  }

  if (!good_num(nm[1][2]) ||
      !good_num(nm[2][1]))
    return false;

  try {
    nm[2][2] = oper(nm[0][2], op[0][2], nm[1][2]);
  } catch (std::domain_error) {
    return false;
  }

  if (!good_num(nm[2][2]))
    return false;

  return true;
}

/**********************************************************/

vector<int> num_to_char_mat(const int (&nm)[3][3], string (&cm)[3][3]) {
  vector<int> digit_met; //le cifre che già hanno una relativa lettera
  for (int i = 0; i != 3; ++i) {
    for (int j = 0; j != 3; ++j) {
      vector<int>::const_iterator it;
      int tmp = nm[i][j];
      //ora trasformo ik numero in un vettore di cifre
      vector<int> digits;
      while (tmp) {
        digits.push_back(tmp % 10);
        tmp /= 10;
      }
      std::reverse(digits.begin(), digits.end());
      
      for (unsigned int pos = 0; pos != digits.size(); ++pos) {
      	if ((it = find(digit_met.begin(), digit_met.end(), digits[pos])) == digit_met.end()) {
      	  cm[i][j].insert(pos, 1, ('a' + digit_met.size()));
      	  digit_met.push_back(digits[pos]);
      	}
      	else
      	  cm[i][j].insert(pos, 1, ('a' + (it - digit_met.begin())));
      }
    }
  }
  return digit_met;
}

/**********************************************************/

bool table_quality(const int (&nm)[3][3]) {
  int four_digit_counter = 0;
  for (int i = 0; i != 3; ++i) {
    for (int j = 0; j != 3; ++j) {
      /*for (int k = i; k != 3; ++k) {
	for (int l = 0; l != 3; ++l) {
	  if(nm[i][j] == nm[k][l])
	    return false;
	}
	}*/
      if (find(*(nm + i) + j + 1, *(nm + 3) + 4, nm[i][j]) != *(nm + 3) + 4)  //controlla che dal prossimo elemento della tabella fino alla fine non ricapiti il numero nella casella attuale (ovvero [i][j])
	return false;
      if (nm[i][j] == 1)
	return false;
      if (nm[i][j] > 999)
	if (++four_digit_counter > 2)
	  return false;
      
    } 
  }
  return true;
}

/**********************************************************/

bool save_table(int (&num_mat)[3][3], string (&char_mat)[3][3], const char (&opers)[2][3], table &tab) {
  if (complete_table(num_mat, opers)) {
    //tradurre in char e risolvere
//    p_panel(num_mat, opers, cout);
    num_to_char_mat(num_mat, char_mat);
 //   p_panel(char_mat, opers, cout);
    if (table_quality(num_mat)) {
      if (solve_it(char_mat, opers, tab)) {
//	ofstream fcout(my_dir() + "calc_enig_generator_proj/solv_em.txt", std::ios::app);
//	fcout << endl << endl;
//	fcout << string(15, '*') << endl << endl;
//	p_panel(char_mat, opers, fcout);
          return true;
      }
  //    p_panel(char_mat, opers, cout);
  //    return true;           //non so perché prima il return true fosse qui
    }
    /*else
      cout << "Funziona, ma non mi piace." << endl;*/
  }
  return false;
}

/**********************************************************/