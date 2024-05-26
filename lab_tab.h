#ifndef LAB_TAB_H
#define LAB_TAB_H
#include <string>
#include "calc_enig_generator.h"
#include "ui_mainwindow.h"
#include <iostream>
//#include "mainwindow.h"


class lab_tab{
//    friend Ui::MainWindow;
public:
    lab_tab() = default;
    lab_tab(Ui::MainWindow *ptr_ui, table *ptr_t) : u(ptr_ui), hold_tab(ptr_t), letts{
    {
        {
            &u->elem00_2_1, &u->elem00_2_2, &u->elem00_2_3, &u->elem00_2_4
        },
        {
            &u->elem01_2_1, &u->elem01_2_2, &u->elem01_2_3, &u->elem01_2_4
        },
        {
            &u->elem02_2_1, &u->elem02_2_2, &u->elem02_2_3, &u->elem02_2_4
        }
    },
    {
        {
            &u->elem10_2_1, &u->elem10_2_2, &u->elem10_2_3, &u->elem10_2_4
        },
        {
            &u->elem11_2_1, &u->elem11_2_2, &u->elem11_2_3, &u->elem11_2_4
        },
        {
            &u->elem12_2_1, &u->elem12_2_2, &u->elem12_2_3, &u->elem12_2_4
        }
    },
    {
        {
            &u->elem20_2_1, &u->elem20_2_2, &u->elem20_2_3, &u->elem20_2_4
        },
        {
            &u->elem21_2_1, &u->elem21_2_2, &u->elem21_2_3, &u->elem21_2_4
        },
        {
            &u->elem22_2_1, &u->elem22_2_2, &u->elem22_2_3, &u->elem22_2_4
        }
    }
}, nums{

    {
        {
            &u->elem00_1_1, &u->elem00_1_2, &u->elem00_1_3, &u->elem00_1_4
        },
        {
            &u->elem01_1_1, &u->elem01_1_2, &u->elem01_1_3, &u->elem01_1_4
        },
        {
            &u->elem02_1_1, &u->elem02_1_2, &u->elem02_1_3, &u->elem02_1_4
        }
    },
    {
        {
            &u->elem10_1_1, &u->elem10_1_2, &u->elem10_1_3, &u->elem10_1_4
        },
        {
            &u->elem11_1_1, &u->elem11_1_2, &u->elem11_1_3, &u->elem11_1_4
        },
        {
            &u->elem12_1_1, &u->elem12_1_2, &u->elem12_1_3, &u->elem12_1_4
        }
    },
    {
        {
            &u->elem20_1_1, &u->elem20_1_2, &u->elem20_1_3, &u->elem20_1_4
        },
        {
            &u->elem21_1_1, &u->elem21_1_2, &u->elem21_1_3, &u->elem21_1_4
        },
        {
            &u->elem22_1_1, &u->elem22_1_2, &u->elem22_1_3, &u->elem22_1_4
        }
    }
}, sets{ &u->set_a, &u->set_b, &u->set_c, &u->set_d, &u->set_e, &u->set_f, &u->set_g, &u->set_h, &u->set_i, &u->set_j } {
        //Questo è il corpo del constructor
    }
    void set_letts();  //scrive in grafica le lettere contenute nella tabella hold_tab
    void set_num(const std::string &n, unsigned int m);  //scrive il numero n (come stringa) relatvo alla lettera m-esima
    void reset();
    bool valid_input() const;
    bool right_nums() const;
    bool get_lastlog();
    void update_lastlog();
    void save_log(std::ostream&);
    bool save_table_on_file();
//private:  //ho dovuto mettere i data members pubblici perché da MainWindow non riuscivo ad accedere a sets. Ho anche provato a mettere friend MainWindow, ma niente.

public:
    Ui::MainWindow *u = nullptr;
    table *hold_tab;
    int already_saved = 0;
    int completed_number = 0;
    int this_is_completed = 0;
    std::string table_date;
    decltype(u->elem00_1_1)* letts[3][3][4];/* = {
        {
            {
                u->elem00_2_1, u->elem00_2_2, u->elem00_2_3, u->elem00_2_4
            },
            {
                u->elem01_2_1, u->elem01_2_2, u->elem01_2_3, u->elem01_2_4
            },
            {
                u->elem02_2_1, u->elem02_2_2, u->elem02_2_3, u->elem02_2_4
            }
        },
        {
            {
                u->elem10_2_1, u->elem10_2_2, u->elem10_2_3, u->elem10_2_4
            },
            {
                u->elem11_2_1, u->elem11_2_2, u->elem11_2_3, u->elem11_2_4
            },
            {
                u->elem12_2_1, u->elem12_2_2, u->elem12_2_3, u->elem12_2_4
            }
        },
        {
            {
                u->elem20_2_1, u->elem20_2_2, u->elem20_2_3, u->elem20_2_4
            },
            {
                u->elem21_2_1, u->elem21_2_2, u->elem21_2_3, u->elem21_2_4
            },
            {
                u->elem22_2_1, u->elem22_2_2, u->elem22_2_3, u->elem22_2_4
            }
        }
    };
*/
    decltype(u->elem00_1_1)* nums[3][3][4];/* = {

        {
            {
                u->elem00_1_1, u->elem00_1_2, u->elem00_1_3, u->elem00_1_4
            },
            {
                u->elem01_1_1, u->elem01_1_2, u->elem01_1_3, u->elem01_1_4
            },
            {
                u->elem02_1_1, u->elem02_1_2, u->elem02_1_3, u->elem02_1_4
            }
        },
        {
            {
                u->elem10_1_1, u->elem10_1_2, u->elem10_1_3, u->elem10_1_4
            },
            {
                u->elem11_1_1, u->elem11_1_2, u->elem11_1_3, u->elem11_1_4
            },
            {
                u->elem12_1_1, u->elem12_1_2, u->elem12_1_3, u->elem12_1_4
            }
        },
        {
            {
                u->elem20_1_1, u->elem20_1_2, u->elem20_1_3, u->elem20_1_4
            },
            {
                u->elem21_1_1, u->elem21_1_2, u->elem21_1_3, u->elem21_1_4
            },
            {
                u->elem22_1_1, u->elem22_1_2, u->elem22_1_3, u->elem22_1_4
            }
        }
    };
    */ decltype(u->elem00_1_1)* sets[10]; /*= { u->set_a, u->set_b, u->set_c, u->set_d, u->set_e, u->set_f, u->set_g, u->set_h, u->set_i, u->set_j };*/
    //decltype(u->elem00_1_1) ops[2][3]
};

#endif // LAB_TAB_H
