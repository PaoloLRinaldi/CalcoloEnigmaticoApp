#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QProgressBar>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QScreen>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTextEdit>
#include "calc_enig_generator.h"
#include "lab_tab.h"


class lab_tab;
class Schermata;
class SchermataConferma;
class SchermataPrincipale;
class SchermataSoloLettere;
class SchermataSoloNumeri;
class SchermataGioco;
class SchermataLoading;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

//friend class lab_tab;

    friend class Schermata;
    friend class SchermataConferma;
    friend class SchermataPrincipale;
    friend class SchermataSoloLettere;
    friend class SchermataSoloNumeri;
    friend class SchermataGioco;
    friend class SchermataLoading;
public:
    explicit MainWindow(QWidget *parent = 0);
    bool already_inserted (int n, const QString &arg1);
    void lets_play();
    table tab;
    ~MainWindow();

private slots:

    void on_OOH_pressed();

    void on_OOH_released();

//    void on_elem00_2_textChanged(const QString &arg1);

//    void on_OOH_2_pressed();

//    void on_OOH_3_pressed();

    void on_check_pressed();

    void on_check_a_pressed();

    void on_check_b_pressed();

    void on_check_c_pressed();

    void on_check_d_pressed();

    void on_check_e_pressed();

    void on_check_f_pressed();

    void on_check_g_pressed();

    void on_check_h_pressed();

    void on_check_i_pressed();

    void on_check_j_pressed();

    void on_set_a_textEdited(const QString &arg1);

    void on_set_b_textEdited(const QString &arg1);

    void on_set_c_textEdited(const QString &arg1);

    void on_set_d_textEdited(const QString &arg1);

    void on_set_e_textEdited(const QString &arg1);

    void on_set_f_textEdited(const QString &arg1);

    void on_set_g_textEdited(const QString &arg1);

    void on_set_h_textEdited(const QString &arg1);

    void on_set_i_textEdited(const QString &arg1);

    void on_set_j_textEdited(const QString &arg1);

    void on_note_a_textEdited(const QString &);

    void on_note_b_textEdited(const QString &);

    void on_note_c_textEdited(const QString &);

    void on_note_d_textEdited(const QString &);

    void on_note_e_textEdited(const QString &);

    void on_note_f_textEdited(const QString &);

    void on_note_g_textEdited(const QString &);

    void on_note_h_textEdited(const QString &);

    void on_note_i_textEdited(const QString &);

    void on_note_j_textEdited(const QString &);

    void record_table();  //Aggiunto io

    void about_gce();  //Aggiunto io

    void clear_set_a();

    void clear_set_b();

    void clear_set_c();

    void clear_set_d();

    void clear_set_e();

    void clear_set_f();

    void clear_set_g();

    void clear_set_h();

    void clear_set_i();

    void clear_set_j();

    //Da qui aggiungo io le SLOT

    //void hide_conf_show_table_again();
    //void sure_new_game();
    //void new_game_after_conf();
    void orientationChanged(Qt::ScreenOrientation orientation);

private:
    const int false_old_height = 1092;  //Sarebbe l'altezza del rettangolone che si chiama tableView, in ui.
    const int true_old_height = 1198;  //Sarebbe l'altezza del mio cellulare
    const int old_width = 720;  //La larghezza del mio cellulare e quella di tableview coincidono
    Ui::MainWindow *ui;
    QMenu *menu;
    QMenu *menu2;
    QAction *newgame;
    QAction *save;
    QAction *back_to_menu;
    QAction *about;
    QPushButton *remove_a;
    QPushButton *remove_b;
    QPushButton *remove_c;
    QPushButton *remove_d;
    QPushButton *remove_e;
    QPushButton *remove_f;
    QPushButton *remove_g;
    QPushButton *remove_h;
    QPushButton *remove_i;
    QPushButton *remove_j;
    QScreen *s;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;


    void hide_letter_from(int l);
    void show_letter_from(int l);
    void update_remaining_nums();
    void resize_everything(double scale_w, double scale_h);
    void colour_everything();
    bool all_nums_inserted();
    void on_set_n_textEdited(const QString &arg1, int n);
    void clear_set_n(QLineEdit* set_n, int n);
    template<class T, class K> bool lock_or_not(T* set_thing, K* remove_thing);
    //void setfocus(int, int, int pos);
public:
    lab_tab grt;

private:
    SchermataPrincipale *princ;
    SchermataSoloLettere *lettere;
    SchermataSoloNumeri *numeri;
    SchermataGioco *gioco;
    SchermataLoading *loading;
};


template<class T> void resizer(T* thing, double scale_w, double scale_h);
template<class T> void colourer (T* thing, int r, int g, int b);
template <typename T>
std::string to_string(T value);
/**************************************************************************************/

class Schermata : public QMainWindow {
    Q_OBJECT
public:
    Schermata(MainWindow* p): parent(p) {
        QRect rec = QApplication::desktop()->availableGeometry();
        height = rec.height();
        width = rec.width();
        //old_height = parent->true_old_height;
        old_height = parent->false_old_height;
        old_width = parent->old_width;
    }
    
    

    MainWindow *parent;

    virtual void show() = 0;
    virtual void hide() = 0;
    // Per risolvere il fatto che dopo un po' di volte che ruoti lo schermo
    // gli oggetti cominciano a restringersi, la soluzione sarebbe mettere
    // in "resize" ogni volta il posizionamento degli oggetti da capo, solo
    // che molti non si possono mettere perché sono stati posizionati
    // graficamente in mainwindow.ui, per cui dovrei trovare un modo di
    // riposizionarli a mano tramite codice e non mi va.
    virtual void resize(double scale_w, double scale_h) = 0;
    virtual void late_initializer() = 0;

    bool modified = false;

    int height;
    int width;
    int old_height;
    int old_width;

};

class SchermataConferma : public Schermata {
    Q_OBJECT
public:
    template <class T, class K>
    SchermataConferma(MainWindow* p, T *p1, const char* c_back, K *p2, const char* c_on, const char* what_to_ask);

    QTextEdit *message;
    QPushButton *go_back;
    QPushButton *go_on;


    void show() override;
    void hide() override;
    void resize(double scale_w, double scale_h) override;
    void late_initializer() override {}
};

class SchermataPrincipale : public Schermata {
    Q_OBJECT
public:

    SchermataPrincipale(MainWindow* p);

    QPushButton *continue_new_game;
    QPushButton *settings;
    QPushButton *load_table;
    QPushButton *about;
    SchermataConferma load_game;

    void show() override;
    void hide() override;
    void resize(double scale_w, double scale_h) override;
    void late_initializer() override;

private slots:
    void hide_conf_show_menu_again() { load_game.hide(); show(); }
    void load_game_after_conf() { hide(); QMessageBox::about(parent, MainWindow::tr("Still nothing"), MainWindow::tr("Coming soon...")); load_game.hide(); show(); }
    void hide_menu_show_table();
    void hide_menu_show_settings() { hide(); QMessageBox::about(parent, MainWindow::tr("Still nothing"), MainWindow::tr("Coming soon...")); show(); }
    void hide_menu_show_conf_load() { hide(); load_game.show(); }
};

class SchermataSoloLettere : public Schermata {
    Q_OBJECT
public:

    SchermataSoloLettere(MainWindow* p);

    decltype(parent->ui->elem00_1_1) letts[3][3][4];
    decltype(parent->ui->oper00) opers[2][3];
    decltype(parent->ui->euqal_1) equals[6];

    void show() override;
    void hide() override;
    void resize(double scale_w, double scale_h) override;
    void late_initializer() override;
};

class SchermataSoloNumeri : public Schermata {
    Q_OBJECT
public:

    SchermataSoloNumeri(MainWindow* p);

    decltype(parent->ui->elem00_1_1) nums[3][3][4];

    void show() override;
    void hide() override;
    void resize(double scale_w, double scale_h) override;
    void late_initializer() override;

    bool isVisible() { return nums[0][0][0]->isVisible(); }
};


class SchermataLoading : public Schermata {
  Q_OBJECT
public:

    SchermataLoading(MainWindow *p);

    QProgressBar *gen_bar;
    QProgressBar *solve_bar;

    void show() override;
    void hide() override;
    void resize(double scale_w, double scale_h) override;
    void late_initializer() override;
};

class SchermataGioco : public Schermata {
    Q_OBJECT
public:

    SchermataGioco(MainWindow *p);

    SchermataSoloLettere &slett;
    SchermataSoloNumeri &snums;
    bool nums_visible;

    QMenu *menu;
    QLineEdit *missing_numbers;
    bool miss_nums_visible = false;
    QLineEdit *completed;
    QPushButton *check;
    bool check_visible = true;
    QTableView *table;
    std::vector<QLineEdit*> notes;
    bool notes_visible = false;
    std::vector<QLineEdit*> sets;
    std::vector<QPushButton*> locks;
    std::vector<QPushButton*> removes;
    std::vector<bool> removes_visible = std::vector<bool>(10, true);

    SchermataConferma conf_newgame;
    SchermataConferma conf_savetable;


    void show() override;
    void hide() override;
    void resize(double scale_w, double scale_h) override;
    void late_initializer() override;

private slots:
    void sure_new_game() { hide(); conf_newgame.show(); }
    void sure_save_table() { hide(); conf_savetable.show();}
    void hide_conf_newgame_show_table_again() { conf_newgame.hide(); show(); }
    void hide_conf_savetable_show_table_again() { conf_savetable.hide(); show(); }
    void new_game_after_conf_newgame() {
        conf_newgame.hide();
        parent->loading->show();
        parent->on_OOH_released();
        parent->loading->hide();
        show();

    }
    void save_table_after_conf_savetable() {
        conf_savetable.hide();
        show();
        parent->record_table();
    }
    void hide_table_show_menu() { hide(); parent->princ->show(); }
};


#endif // MAINWINDOW_H
