#include "lab_tab.h"
//#include <algorithm>
#include <cctype>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
// #include <iomanip>

using std::istringstream;
using std::string;
using std::isdigit;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

int stod(std::string s) {
    int ret = 0, mult = 1;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        ret += (*it - '0') * mult;
        mult *= 10;
    }
    return ret;
}

string date_time_format(int dt) {
    if (dt < 10)
        return "0";
    else
        return "";
}

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

void lab_tab::set_letts() {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            for (unsigned int k = 0; k != (hold_tab->char_mat[i][j]).size(); ++k) {
                //A partire da destra metto una lettera alla volta nella rispettiva sottocasella, sottoforma di stringa
               (*letts[i][j][3 - k])->setText(MainWindow::tr(hold_tab->char_mat[i][j].substr(hold_tab->char_mat[i][j].size() - k - 1, 1).c_str()));
            }
        }
    }
}

void lab_tab::set_num(const string& n, unsigned int m) {
  if (!n.size() || (n.size() == 1 && isdigit(n[0])))
   for (int i = 0; i != 3; ++i) {
       for (int j = 0; j != 3; ++j) {
           for (unsigned int k = 0; k != hold_tab->char_mat[i][j].size(); ++k) {
               if (hold_tab->char_mat[i][j][(hold_tab->char_mat[i][j]).size() - k - 1] == char(m + 'a'))
                   (*nums[i][j][3-k])->setText(MainWindow::tr(n.c_str()));
           }
       }
   }

}

void lab_tab::reset() {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j)
            for (int k = 0; k != 4; ++k) {
                /*cout << "Fin qui ci arrivi?" << endl;
                cout << &(*letts[0][0][0]) << endl;
                cout << (*letts[0][0][0]) << endl;
                cout << sizeof((*letts[0][0][0])) << endl;
                cout << sizeof(&(*letts[0][0][0])) << endl;
                cout << sizeof(letts) / sizeof((*letts[0][0][0])) << endl;*/
                (*letts[i][j][k])->setText(MainWindow::tr(""));
                (*nums[i][j][k])->setText(MainWindow::tr(""));
            }
    }
    for (int i = 0; i != 10; ++i)
        (*sets[i])->setText(MainWindow::tr(""));
}


bool lab_tab::valid_input() const {
    int max = hold_tab->n_to_c.size();
    for (int i = 0; i != max; ++i)
        if ((*sets[i])->text().toStdString().size() == 0 ||
            (*sets[i])->text().toStdString().size() >1 ||
            !std::isdigit((*sets[i])->text().toStdString()[0]))
           return false;

    for (int i = 0; i != max - 1; ++i) {
        for (int j = i + 1; j != max; ++j) {
            if ((*sets[i])->text() == (*sets[j])->text())
                return false;
        }
    }
    return true;
}


bool lab_tab::right_nums() const {
    for (unsigned int i = 0; i != hold_tab->n_to_c.size(); ++i)
        if (::stod((*sets[i])->text().toStdString()) != hold_tab->n_to_c[i])
            return false;
    return true;
}

bool lab_tab::get_lastlog() {
    ifstream log("/storage/emulated/0/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/gce2_proj/last_log.txt");
    if (!log.is_open())
      log.open("/storage/emulated/0/CalcoloEnigmatico/last_log.txt");
    if (!log.is_open())
      log.open("last_log.txt");
    if (!log.is_open())
        return false;
        
        
    //QMessageBox::about(u, MainWindow::tr("Yo?"), MainWindow::tr("YOLO"));
    //u->my_output_2->setText(MainWindow::tr("YOULOU?!?"));

    //Leggo e scrivo su grafica le lettere della tabella e il valore intero corrispondente a ogni set di lettere
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            string s;
            std::getline(log, s);
            istringstream oss(s);
            char c;
            //hold_tab->char_mat[i][j] = string();
            while (oss >> c)
                hold_tab->char_mat[i][j].push_back(c);
            log >> hold_tab->num_mat[i][j];
            log.get();  //prende lo spazio, il successivo getline prenderà la riga successiva
        }
    }
    set_letts();
    
    string s;

    //Leggo e scrivo su grafica le operazioni
    std::getline(log, s);
    {
        istringstream oss(s);
		    char op;
  		  char *it = &(hold_tab->opers)[0][0];
    		while (oss >> op)
        *it++ = op;
    }
    u->oper00->setText(MainWindow::tr(std::string(1, hold_tab->opers[0][0]).c_str()));
    u->oper01->setText(MainWindow::tr(std::string(1, hold_tab->opers[0][1]).c_str()));
    u->oper02->setText(MainWindow::tr(std::string(1, hold_tab->opers[0][2]).c_str()));
    u->oper10->setText(MainWindow::tr(std::string(1, hold_tab->opers[1][0]).c_str()));
    u->oper11->setText(MainWindow::tr(std::string(1, hold_tab->opers[1][1]).c_str()));
    u->oper12->setText(MainWindow::tr(std::string(1, hold_tab->opers[1][2]).c_str()));

    //Leggo la cifra corrispondente a ogni carattere e metto nel relativo vettore
    std::getline(log, s);
    {
        istringstream oss(s);
		    int n;
  		  while (oss >> n)
        hold_tab->n_to_c.push_back(n);
    }

    //Leggo e imposto i numeri inseriti dall'utente
    std::getline(log, s);
    {
        istringstream oss(s);
        int n;
        int input_counter = 0;
        while (oss >> n) {
          if (n >= 0) {
            set_num(to_string(n), input_counter);
            (*sets[input_counter])->setText(MainWindow::tr(to_string(n).c_str()));
           }
          ++input_counter;
        }
    }

    //Leggo e imposto tutte le annotazioni fatte
    std::getline(log, s);
	  u->note_a->setText(MainWindow::tr(s.c_str()));
    std::getline(log, s);
	  u->note_b->setText(MainWindow::tr(s.c_str()));
    std::getline(log, s);
    u->note_c->setText(MainWindow::tr(s.c_str()));
    std::getline(log, s);
	  u->note_d->setText(MainWindow::tr(s.c_str()));
    std::getline(log, s);
	  u->note_e->setText(MainWindow::tr(s.c_str()));
    std::getline(log, s);
	  u->note_f->setText(MainWindow::tr(s.c_str()));
    std::getline(log, s);
	  u->note_g->setText(MainWindow::tr(s.c_str()));
    std::getline(log, s);
	  u->note_h->setText(MainWindow::tr(s.c_str()));
    std::getline(log, s);
	  u->note_i->setText(MainWindow::tr(s.c_str()));
    std::getline(log, s);
	  u->note_j->setText(MainWindow::tr(s.c_str()));


    std::getline(log, s);
    if (s.empty()) return true;

    //Scrivo quali lettere vanno lockate e quali no
    istringstream oss(s);
    int lock_it;
    for (int i = 0; i != 10; ++i) {
        oss >> lock_it;
        if (!lock_it) (*sets[i])->setReadOnly(true);
        else (*sets[i])->setReadOnly(false);
    }

    //Leggo se è già salvata o meno
    std::getline(log, s);
    oss.str(s);
    oss >> already_saved;

    //Leggo la data
    {
        std::getline(log,s);
        table_date = s;
    }

    //Leggo il numero di tabelle completate
    {
        std::getline(log, s);
        if (!s.empty()) {
            istringstream oss(s);
            oss >> completed_number >> this_is_completed;
        } else {
            completed_number = 0;
            this_is_completed = 0;
        }
    }

    return true;
}

void lab_tab::update_lastlog() {
	if (hold_tab->char_mat[0][0].empty())
		return;
	
    ofstream log("/storage/emulated/0/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/gce2_proj/last_log.txt");
    if (!log.is_open())
      log.open("/storage/emulated/0/CalcoloEnigmatico/last_log.txt");
    if (!log.is_open())
      log.open("last_log.txt");
    save_log(log);
}

void lab_tab::save_log(std::ostream& log) {
    //Scrivo i caratteri del numero cifrato e in seguito ad ogni set il relativo numero
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            for (auto c : hold_tab->char_mat[i][j])
                log << c << " ";
            log << endl;
          log << hold_tab->num_mat[i][j] << endl;
        }
    }

    //Scrivo le operazioni
    for (int i = 0; i != 2; ++i)
        for (int j = 0; j != 3; ++j)
            log << hold_tab->opers[i][j] << " ";
    log << endl;

    //Scrivo i valori dei rispettivi caratteri in ordine alfabetico
    for (auto n : hold_tab->n_to_c)
        log << n << " ";
    log << endl;

    //Scrivo i numeri inseriti dall'utente
    for (unsigned int i = 0; i != hold_tab->n_to_c.size(); ++i) {
        if (!(*sets[i])->text().toStdString().empty() && isdigit((*sets[i])->text().toStdString()[0]))
            log << (*sets[i])->text().toStdString()[0] << " ";
        else
            log << -1 << " ";
    }
    log << endl;

    //Scrivo le annotazioni fatte dall'utente
    log << u->note_a->text().toStdString() << endl;
    log << u->note_b->text().toStdString() << endl;
    log << u->note_c->text().toStdString() << endl;
    log << u->note_d->text().toStdString() << endl;
    log << u->note_e->text().toStdString() << endl;
    log << u->note_f->text().toStdString() << endl;
    log << u->note_g->text().toStdString() << endl;
    log << u->note_h->text().toStdString() << endl;
    log << u->note_i->text().toStdString() << endl;
    log << u->note_j->text().toStdString() << endl;


    //Scrivo quali numeri sono lockati
    for (int i = 0; i != 10; ++i) {
        if ((*sets[i])->isReadOnly())
            log << 1;
        else
            log << 0;
        log << " ";
    }
    log << endl;

    //Dico se la tavola è già salvata o meno
    log << already_saved << endl;

    //Metto la data
    //log << __DATE__ << endl;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    log << date_time_format(tm.tm_mday) << tm.tm_mday << "/"
        << date_time_format(tm.tm_mon) << tm.tm_mon + 1 << "/"
        << tm.tm_year + 1900 << " "
        << date_time_format(tm.tm_hour) << tm.tm_hour << ":"
        << date_time_format(tm.tm_min) << tm.tm_min << ":"
        << date_time_format(tm.tm_sec) << tm.tm_sec << endl;
    // log << std::put_time(&tm, "%d/%m/%Y %H:%M:%S") << endl;

    //Metto il numero di tabelle completate
    log << completed_number << " " << this_is_completed << endl;

}


bool lab_tab::save_table_on_file() {
    if (hold_tab->char_mat[0][0].empty() || already_saved) {
        //u->my_output_2->setText(MainWindow::tr("No table to save!"));
        return false;
    }
    already_saved = 1;

    ofstream log("/storage/emulated/0/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/gce2_proj/saved_tables.txt", std::ios::app);
    if (!log.is_open())
      log.open("/storage/emulated/0/CalcoloEnigmatico/saved_tables.txt", std::ios::app);
    if (!log.is_open())
      log.open("saved_tables.txt", std::ios::app);
    save_log(log);
    log << endl << string(10, '*') << endl;

    return true;
}
