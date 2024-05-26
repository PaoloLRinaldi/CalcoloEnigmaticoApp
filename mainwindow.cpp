#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <ctime>
#include <map>
#include <string>
#include <set>
#include "calc_enig_generator.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <QDesktopWidget>
#include <QRect>
#include <QPoint>
#include <QPalette>
#include <QScreen>

//#include "lab_tab.h"
//#include <algorithm>

using std::isdigit;
using std::cout;
using std::cin;
using std::endl;
using std::system;

//void lets_play();

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

int stod(const std::string &s) {
    int ret = 0;
    int moltip = 1;
    for (auto it = s.crbegin(); it != s.crend(); ++it, moltip *= 10)
        ret += (*it - '0') * moltip;
    return ret;
}

void MainWindow::show_letter_from(int l) {
    switch (l) {
    case 0:
      ui->check_a->show();
      // ui->note_a->show();
      ui->set_a->show();
      if(!ui->set_a->isReadOnly()) remove_a->show();
    case 1:
        ui->check_b->show();
        // ui->note_b->show();
        ui->set_b->show();
        if(!ui->set_b->isReadOnly()) remove_b->show();
    case 2:
        ui->check_c->show();
        // ui->note_c->show();
        ui->set_c->show();
        if(!ui->set_c->isReadOnly()) remove_c->show();
    case 3:
        ui->check_d->show();
        // ui->note_d->show();
        ui->set_d->show();
        if(!ui->set_d->isReadOnly()) remove_d->show();
    case 4:
        ui->check_e->show();
        // ui->note_e->show();
        ui->set_e->show();
        if(!ui->set_e->isReadOnly()) remove_e->show();
    case 5:
        ui->check_f->show();
        // ui->note_f->show();
        ui->set_f->show();
        if(!ui->set_f->isReadOnly()) remove_f->show();
    case 6:
        ui->check_g->show();
        // ui->note_g->show();
        ui->set_g->show();
        if(!ui->set_g->isReadOnly()) remove_g->show();
    case 7:
        ui->check_h->show();
        // ui->note_h->show();
        ui->set_h->show();
        if(!ui->set_h->isReadOnly()) remove_h->show();
    case 8:
        ui->check_i->show();
        // ui->note_i->show();
        ui->set_i->show();
        if(!ui->set_i->isReadOnly()) remove_i->show();
    case 9:
        ui->check_j->show();
        // ui->note_j->show();
        ui->set_j->show();
        if (!ui->set_j->isReadOnly()) remove_j->show();
    }
}

void MainWindow::update_remaining_nums() {
    std::ostringstream sout;
    std::set<int> missing{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (std::vector<int>::size_type i = 0; i != grt.hold_tab->n_to_c.size(); ++i)
       if ((*grt.sets[i])->text() != tr(""))
           missing.erase(::stod((*grt.sets[i])->text().toStdString()));
    int actually_missing = grt.hold_tab->n_to_c.size() - (10 - missing.size());
    sout << "Missing numbers (" << actually_missing << "/" << missing.size() << "): ";

    auto it = missing.cbegin();
    if (it != missing.cend()) {
        sout << *it++;
        for ( ; it != missing.cend(); ++it)
            sout << "   " << *it;
    }
    ui->my_output_2->setText(tr(sout.str().c_str()));
}

void MainWindow::hide_letter_from(int l) {
    switch (l) {
    case 0:
      ui->check_a->hide();
      ui->note_a->hide();
      ui->set_a->hide();
      remove_a->hide();
    case 1:
        ui->check_b->hide();
        ui->note_b->hide();
        ui->set_b->hide();
        remove_b->hide();
    case 2:
        ui->check_c->hide();
        ui->note_c->hide();
        ui->set_c->hide();
        remove_c->hide();
    case 3:
        ui->check_d->hide();
        ui->note_d->hide();
        ui->set_d->hide();
        remove_d->hide();
    case 4:
        ui->check_e->hide();
        ui->note_e->hide();
        ui->set_e->hide();
        remove_e->hide();
    case 5:
        ui->check_f->hide();
        ui->note_f->hide();
        ui->set_f->hide();
        remove_f->hide();
    case 6:
        ui->check_g->hide();
        ui->note_g->hide();
        ui->set_g->hide();
        remove_g->hide();
    case 7:
        ui->check_h->hide();
        ui->note_h->hide();
        ui->set_h->hide();
        remove_h->hide();
    case 8:
        ui->check_i->hide();
        ui->note_i->hide();
        ui->set_i->hide();
        remove_i->hide();
    case 9:
        ui->check_j->hide();
        ui->note_j->hide();
        ui->set_j->hide();
        remove_j->hide();
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    remove_a(new QPushButton(tr("X"), this)),
    remove_b(new QPushButton(tr("X"), this)),
    remove_c(new QPushButton(tr("X"), this)),
    remove_d(new QPushButton(tr("X"), this)),
    remove_e(new QPushButton(tr("X"), this)),
    remove_f(new QPushButton(tr("X"), this)),
    remove_g(new QPushButton(tr("X"), this)),
    remove_h(new QPushButton(tr("X"), this)),
    remove_i(new QPushButton(tr("X"), this)),
    remove_j(new QPushButton(tr("X"), this)),
    grt(ui, &tab),  //ho fatto un casino qua perché ho creato gli array degli elementi "grafici" ai quali puntava ui, ma non me li copiava bene perché non ho notato che li inizializzava
                   //subito dopo (ui->setupUi(this);) per cui quello che copiavo erano dei puntatore ancora non inizializzati. Alla fine ho risolto prendendomi i puntatori dei puntatori
                  
    
    princ(new SchermataPrincipale(this)),
    lettere(new SchermataSoloLettere(this)),
    numeri(new SchermataSoloNumeri(this)),
    gioco(new SchermataGioco(this)),
    loading(new SchermataLoading(this))
{
    ui->setupUi(this);
    ui->genprogress->setValue(0);
    ui->solveprogress->setValue(0);
    //ui->processEvents();
    //this->setStyleSheet("QPushButton { margin: 0px }");
    //this->setStyleSheet("QPushButton { border-width: 0px }");
    
    /*
    this->setStyleSheet(" QPushButton { "
                        " border-radius: 40px; "
                        " color:rgb(0, 0, 0); "
                        " background-color: rgb(255, 255, 255); } "

                        " QPushButton:focus { "
                        " border:0px outset; "
                        " border-radius: 8px; "
                        " border-color: rgb(41, 237, 215); "
                        " color:rgb(0, 0, 0); "
                        " background-color: rgb(150, 150, 150); }
                         ");
                         */
    this->setStyleSheet(" QLineEdit { "
                        " border-radius: 0px; } "

                        " QLineEdit:focus { "
                        " border:0px outset; "
                        " border-radius: 0px; }"
                        
                        " QPushButton { "
                        " border-radius: 0px; }");
    
                        /*                    
    this->setStyleSheet("Button { "
    "text: \"A button\" "
    "style: ButtonStyle { "
        "background: Rectangle {"
            "implicitWidth: 100 "
            "implicitHeight: 25 "
            "border.width: control.activeFocus ? 2 : 1 "
            "border.color: \"#888\" "
            "radius: 4 "
            "gradient: Gradient { "
                "GradientStop { position: 0 ; color: control.pressed ? \"#ccc\" : \"#eee\" } "
                "GradientStop { position: 1 ; color: control.pressed ? \"#aaa\" : \"#ccc\" } "
            "} "
        "} "
    "} "
 "} ");
 
 */
    
    //remove_a->setIcon(QIcon("/storage/emulated/0/qpython.jpg"));
    //remove_a->setIconSize(QSize(65, 65));
    
    
    //QPushButton { background-color: red; border: none; }
    QApplication::processEvents();
    tab.u = ui;
    ui->set_a->setValidator(new QIntValidator(0, 10, this));
    ui->set_b->setValidator(new QIntValidator(0, 10, this));
    ui->set_c->setValidator(new QIntValidator(0, 10, this));
    ui->set_d->setValidator(new QIntValidator(0, 10, this));
    ui->set_e->setValidator(new QIntValidator(0, 10, this));
    ui->set_f->setValidator(new QIntValidator(0, 10, this));
    ui->set_g->setValidator(new QIntValidator(0, 10, this));
    ui->set_h->setValidator(new QIntValidator(0, 10, this));
    ui->set_i->setValidator(new QIntValidator(0, 10, this));
    ui->set_j->setValidator(new QIntValidator(0, 10, this));

    ui->OOH->hide();
    ui->note_out->hide();
    

    //creo menu
    newgame = new QAction(tr("New Game"), this);
    connect(newgame, SIGNAL(triggered()), gioco, SLOT(sure_new_game()));
    save = new QAction(tr("Save table..."), this);
    connect(save, SIGNAL(triggered()), gioco, SLOT(sure_save_table()));
    back_to_menu = new QAction(tr("Go Back to Menu"), this);
    connect(back_to_menu, SIGNAL(triggered()), gioco, SLOT(hide_table_show_menu()));
    about = new QAction(tr("About"), this);
    connect(about, SIGNAL(triggered()), this, SLOT(about_gce()));
    menu = new QMenu(tr("Menu"));
    menu2 = new QMenu(tr("Menu2"));
    menu->addAction(newgame);
    menu->addAction(save);
    menu->addAction(back_to_menu);
    menu->addAction(about);
    menu2->addAction(about);
    menuBar()->addMenu(menu);

    show();  // Così facendo compare anche il menu (menuBar) e il rettangolo disponibile considerato è quello giusto
    // QMessageBox::about(this, tr("Yo"), tr("Howyadoin'?"));

    princ->late_initializer();
    lettere->late_initializer();
    numeri->late_initializer();
    gioco->late_initializer();
    loading->late_initializer();

    //gioco->show();
    princ->show();


    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height(),
            width = rec.width(),
            old_height = ui->tableView->height(),
            old_width = ui->tableView->width();
    resizer(ui->tableView, (double)width / old_width, (double)height / old_height);



    s = QGuiApplication::primaryScreen();
    connect(s, SIGNAL(orientationChanged(Qt::ScreenOrientation)),
               this, SLOT(orientationChanged(Qt::ScreenOrientation)));

     s->setOrientationUpdateMask(
                Qt::PortraitOrientation
                | Qt::LandscapeOrientation
                | Qt::InvertedPortraitOrientation
                | Qt::InvertedLandscapeOrientation);
                
    
    /*
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("/storage/emulated/0/Notes6.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);


    player = new QMediaPlayer();
    // ...
    //player->setMedia(QUrl::fromLocalFile("/storage/emulated/0/FLM\ User\ Files/My\ Tracks/2_5271693668573512193.mp3"));  //FUNZIONA, SCEGLIERE MUSICA
    //player->setMedia(QUrl::fromLocalFile("/storage/emulated/0/Notes6.mp3"));
    player->setPlaylist(playlist);
    player->setVolume(50);
    player->play();
    */

    
    //Ora inizializzo e lego ogni bottone "X" alla propria lettera
    //Notare che la posizione lungo y di questi bottoni su pc non va
    //bene, ma su cellulare si
    
    /*
    remove_a->resize(41, 41);
    remove_a->move(671, 10);
    remove_a->raise();
    */
    connect(remove_a, SIGNAL(released()), this, SLOT(clear_set_a()));

    /*
    remove_b->resize(41, 41);
    remove_b->move(671, 60);
    remove_b->raise();
    */
    connect(remove_b, SIGNAL(released()), this, SLOT(clear_set_b()));

    /*
    remove_c->resize(41, 41);
    remove_c->move(671, 110);
    remove_c->raise();
    */
    connect(remove_c, SIGNAL(released()), this, SLOT(clear_set_c()));

    /*
    remove_d->resize(41, 41);
    remove_d->move(671, 160);
    remove_d->raise();
    */
    connect(remove_d, SIGNAL(released()), this, SLOT(clear_set_d()));

    /*
    remove_e->resize(41, 41);
    remove_e->move(671, 210);
    remove_e->raise();
    */
    connect(remove_e, SIGNAL(released()), this, SLOT(clear_set_e()));

    /*
    remove_f->resize(41, 41);
    remove_f->move(671, 260);
    remove_f->raise();
    */
    connect(remove_f, SIGNAL(released()), this, SLOT(clear_set_f()));

    /*
    remove_g->resize(41, 41);
    remove_g->move(671, 310);
    remove_g->raise();
    */
    connect(remove_g, SIGNAL(released()), this, SLOT(clear_set_g()));

    /*
    remove_h->resize(41, 41);
    remove_h->move(671, 360);
    remove_h->raise();
    */
    connect(remove_h, SIGNAL(released()), this, SLOT(clear_set_h()));

    /*
    remove_i->resize(41, 41);
    remove_i->move(671, 410);
    remove_i->raise();
    */
    connect(remove_i, SIGNAL(released()), this, SLOT(clear_set_i()));

    /*
    remove_j->resize(41, 41);
    remove_j->move(671, 460);
    remove_j->raise();
    */
    connect(remove_j, SIGNAL(released()), this, SLOT(clear_set_j()));
/*
    //RISCALO TUTTO RENDENDOLO COMPATIBILE IN DIMENSIONE CON OGNI DISPOSITIVO
    //Altezza cellulare   = 1198. Altezza finta   = 1092
    //Larghezza cellulare = 720.  Larghezza finta = 720
    //Il menù nella parte alta dello schermo occupa un certo spazio. old_height
    //non considera quello spazio, ma solo tutto lo spazio che c'è sotto. Aggiorno
    //old_height rendendolo 1198, ovvero la vera altezza dello schermo del mio
    //cellulare, scelto come sistema di riferimento iniziale. Questo sperando che
    //lo spazio occupato dal menù in alto sia occupato in proporzione in maniera
    //uguale su ogni dispositivo
    old_height = 1198;
    resize_everything((double)width / old_width, (double)height / old_height);
    */
}


/*
void MainWindow::setfocus(int a, int b, int pos) {
    switch (tab.char_mat[a][b][pos]) {
    case 'a': ui->set_a->setFocus(); break;
    case 'b': ui->set_b->setFocus(); break;
    case 'c': ui->set_c->setFocus(); break;
    case 'd': ui->set_d->setFocus(); break;
    case 'e': ui->set_e->setFocus(); break;
    case 'f': ui->set_f->setFocus(); break;
    case 'g': ui->set_g->setFocus(); break;
    case 'h': ui->set_h->setFocus(); break;
    case 'i': ui->set_i->setFocus(); break;
    case 'j': ui->set_j->setFocus(); break;
    }
}
*/

void MainWindow::record_table() {

    if(!grt.save_table_on_file()) {
        if(grt.already_saved) QMessageBox::about(this, tr("ERROR"), tr("Table already saved!"));
        else QMessageBox::about(this, tr("ERROR"), tr("No table to save!"));
    }
    else {
        QMessageBox::about(this, tr("Done"), tr("Table saved successfully."));
        grt.update_lastlog(); //Questo per fargli mettere sul last_log.txt che l'ha salvata
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_OOH_pressed()
{
 //   lets_play();
}

void MainWindow::on_OOH_released()
{
    if (!tab.char_mat[0][0].empty()) {
        // Per me
        system("mv /storage/emulated/0/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/gce2_proj/last_log.txt /storage/emulated/0/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/gce2_proj/old_log.txt\n");
        // Per TCO
        system("mv /storage/emulated/0/CalcoloEnigmatico/last_log.txt /storage/emulated/0/CalcoloEnigmatico/old_log.txt");
        // Per l'altri
        system("mv last_log.txt old_log.txt\n");
    }
    //QMessageBox::about(this, tr("Yo?"), tr("YOLO"));
    lets_play();
}


void MainWindow::lets_play() {
    ui->my_output_2->setText(tr(""));
    ui->genprogress->setValue(0);
    ui->solveprogress->setValue(0);
    QApplication::processEvents();
    if (!grt.get_lastlog()) {
        ui->set_a->setReadOnly(false);
        colourer(ui->set_a, 255, 255, 255);
        ui->set_b->setReadOnly(false);
        colourer(ui->set_b, 255, 255, 255);
        ui->set_c->setReadOnly(false);
        colourer(ui->set_c, 255, 255, 255);
        ui->set_d->setReadOnly(false);
        colourer(ui->set_d, 255, 255, 255);
        ui->set_e->setReadOnly(false);
        colourer(ui->set_e, 255, 255, 255);
        ui->set_f->setReadOnly(false);
        colourer(ui->set_f, 255, 255, 255);
        ui->set_g->setReadOnly(false);
        colourer(ui->set_g, 255, 255, 255);
        ui->set_h->setReadOnly(false);
        colourer(ui->set_h, 255, 255, 255);
        ui->set_i->setReadOnly(false);
        colourer(ui->set_i, 255, 255, 255);
        ui->set_j->setReadOnly(false);
        colourer(ui->set_j, 255, 255, 255);

        grt.reset();
        ui->note_out->setText(tr(""));
        ui->note_a->setText(tr(""));
        ui->note_b->setText(tr(""));
        ui->note_c->setText(tr(""));
        ui->note_d->setText(tr(""));
        ui->note_e->setText(tr(""));
        ui->note_f->setText(tr(""));
        ui->note_g->setText(tr(""));
        ui->note_h->setText(tr(""));
        ui->note_i->setText(tr(""));
        ui->note_j->setText(tr(""));
        tab.char_mat[0][0] = "";
        tab.char_mat[0][1] = "";
        tab.char_mat[0][2] = "";
        tab.char_mat[1][0] = "";
        tab.char_mat[1][1] = "";
        tab.char_mat[1][2] = "";
        tab.char_mat[2][0] = "";
        tab.char_mat[2][1] = "";
        tab.char_mat[2][2] = "";
        old_main(tab);
        ui->genprogress->setValue(0);  //non è un errore ripeterle, in "old_main()" vengono aggiornate in continuazione
        ui->solveprogress->setValue(0);
        tab.n_to_c = num_to_char_mat(tab.num_mat, tab.char_mat);
        grt.set_letts();
        ui->oper00->setText(tr(std::string(1, tab.opers[0][0]).c_str()));
        ui->oper01->setText(tr(std::string(1, tab.opers[0][1]).c_str()));
        ui->oper02->setText(tr(std::string(1, tab.opers[0][2]).c_str()));
        ui->oper10->setText(tr(std::string(1, tab.opers[1][0]).c_str()));
        ui->oper11->setText(tr(std::string(1, tab.opers[1][1]).c_str()));
        ui->oper12->setText(tr(std::string(1, tab.opers[1][2]).c_str()));
        grt.already_saved = 0;
        grt.this_is_completed = 0;
        gioco->completed->setText(tr("0"));
        gioco->completed->setAlignment(Qt::AlignCenter);
        gioco->completed->setAlignment(Qt::AlignHCenter);
        colourer(gioco->completed, 255, 255, 255);
        grt.update_lastlog();
    }
    lock_or_not(ui->set_a, remove_a);
    lock_or_not(ui->set_b, remove_b);
    lock_or_not(ui->set_c, remove_c);
    lock_or_not(ui->set_d, remove_d);
    lock_or_not(ui->set_e, remove_e);
    lock_or_not(ui->set_f, remove_f);
    lock_or_not(ui->set_g, remove_g);
    lock_or_not(ui->set_h, remove_h);
    lock_or_not(ui->set_i, remove_i);
    lock_or_not(ui->set_j, remove_j);
    auto sz = tab.n_to_c.size();
    show_letter_from(0);
    hide_letter_from(sz);
    update_remaining_nums();
    colour_everything();
    gioco->completed->setText(tr(to_string(grt.completed_number).c_str()));
    gioco->completed->setAlignment(Qt::AlignCenter);
    gioco->completed->setAlignment(Qt::AlignHCenter);
    if (grt.this_is_completed)
        colourer(gioco->completed, 100, 255, 100);
    else
        colourer(gioco->completed, 255, 255, 255);
    if (all_nums_inserted()) gioco->check_visible = true;
    else gioco->check_visible = false;
}


bool MainWindow::already_inserted (int n, const QString &arg1) {
    for (int i = 0; i != 10; ++i) {
        if (i != n && arg1 != tr("") && arg1 == (*grt.sets[i])->text()) {
            (*grt.sets[n])->setText(tr(""));
            //ui->my_output_2->setText(tr("Number already inserted!"));
            QMessageBox::about(this, tr("Invalid operation"), tr(std::string("Number already inserted (" + arg1.toStdString() + ")").c_str()));
            return true;
        }
    }
    return false;
}


void MainWindow::on_check_pressed()
{
    if (tab.char_mat[0][0].empty()) {
        //ui->my_output_2->setText(tr("No table found!"));
        QMessageBox::about(this, tr("Invalid operation"), tr("No table found!"));
    } else if (!grt.valid_input()) {
        //ui->my_output_2->setText(tr("Incomplete input!"));
        QMessageBox::about(this, tr("Invalid operation"), tr("Incomplete input!"));
    } else if (!grt.right_nums()) {
        //ui->my_output_2->setText(tr("Wrong!"));
        QMessageBox::about(this, tr("WRONG SOLUTION"), tr("Try again"));
    } else {
        if (!grt.this_is_completed) {
            ++grt.completed_number;
            grt.this_is_completed = 1;
            grt.update_lastlog();
            colourer(gioco->completed, 100, 255, 100);
            gioco->completed->setText(tr(to_string(grt.completed_number).c_str()));
        }
        //ui->my_output_2->setText(tr("RIGHT!"));
        QMessageBox::about(this, tr("RIGHT SOLUTION"), tr("You did it!"));
    }
}

void MainWindow::on_check_a_pressed()
{
    if (!lock_or_not(ui->set_a, remove_a)) return;
    grt.update_lastlog();
}

void MainWindow::on_check_b_pressed()
{
    if (!lock_or_not(ui->set_b, remove_b)) return;
    grt.update_lastlog();
}

void MainWindow::on_check_c_pressed()
{
    if (!lock_or_not(ui->set_c, remove_c)) return;
    grt.update_lastlog();
}

void MainWindow::on_check_d_pressed()
{
    if (!lock_or_not(ui->set_d, remove_d)) return;
    grt.update_lastlog();
}

void MainWindow::on_check_e_pressed()
{
    if (!lock_or_not(ui->set_e, remove_e)) return;
    grt.update_lastlog();
}

void MainWindow::on_check_f_pressed()
{
    if (!lock_or_not(ui->set_f, remove_f)) return;
    grt.update_lastlog();
}

void MainWindow::on_check_g_pressed()
{
    if (!lock_or_not(ui->set_g, remove_g)) return;
    grt.update_lastlog();
}

void MainWindow::on_check_h_pressed()
{
    if (!lock_or_not(ui->set_h, remove_h)) return;
    grt.update_lastlog();
}

void MainWindow::on_check_i_pressed()
{
    if (!lock_or_not(ui->set_i, remove_i)) return;
    grt.update_lastlog();
}

void MainWindow::on_check_j_pressed()
{
    if (!lock_or_not(ui->set_j, remove_j)) return;
    grt.update_lastlog();
}

void MainWindow::on_set_a_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 0);
}

void MainWindow::on_set_b_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 1);
}

void MainWindow::on_set_c_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 2);
}

void MainWindow::on_set_d_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 3);
}

void MainWindow::on_set_e_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 4);
}

void MainWindow::on_set_f_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 5);
}

void MainWindow::on_set_g_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 6);
}

void MainWindow::on_set_h_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 7);
}

void MainWindow::on_set_i_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 8);
}

void MainWindow::on_set_j_textEdited(const QString &arg1)
{
    on_set_n_textEdited(arg1, 9);
}

void MainWindow::on_note_a_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::on_note_b_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::on_note_c_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::on_note_d_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::on_note_e_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::on_note_f_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::on_note_g_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::on_note_h_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::on_note_i_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::on_note_j_textEdited(const QString &)
{
    grt.update_lastlog();
}

void MainWindow::clear_set_a() {
    clear_set_n(ui->set_a, 0);
}
void MainWindow::clear_set_b() {
    clear_set_n(ui->set_b, 1);
}
void MainWindow::clear_set_c() {
    clear_set_n(ui->set_c, 2);
}
void MainWindow::clear_set_d() {
    clear_set_n(ui->set_d, 3);
}
void MainWindow::clear_set_e() {
    clear_set_n(ui->set_e, 4);
}
void MainWindow::clear_set_f() {
    clear_set_n(ui->set_f, 5);
}
void MainWindow::clear_set_g() {
    clear_set_n(ui->set_g, 6);
}
void MainWindow::clear_set_h() {
    clear_set_n(ui->set_h, 7);
}
void MainWindow::clear_set_i() {
    clear_set_n(ui->set_i, 8);
}
void MainWindow::clear_set_j() {
    clear_set_n(ui->set_j, 9);
}

void MainWindow::resize_everything(double scale_w, double scale_h) {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j)
            for (int k = 0; k != 4; ++k) {
                resizer(*grt.letts[i][j][k], scale_w, scale_h);
                resizer(*grt.nums[i][j][k], scale_w, scale_h);
            }
    }
    for (int i = 0; i != 10; ++i)
        resizer(*grt.sets[i], scale_w, scale_h);

    resizer(ui->check, scale_w, scale_h);
    resizer(ui->check_a, scale_w, scale_h);
    resizer(ui->check_b, scale_w, scale_h);
    resizer(ui->check_c, scale_w, scale_h);
    resizer(ui->check_d, scale_w, scale_h);
    resizer(ui->check_e, scale_w, scale_h);
    resizer(ui->check_f, scale_w, scale_h);
    resizer(ui->check_g, scale_w, scale_h);
    resizer(ui->check_h, scale_w, scale_h);
    resizer(ui->check_i, scale_w, scale_h);
    resizer(ui->check_j, scale_w, scale_h);

    resizer(ui->euqal_1, scale_w, scale_h);
    resizer(ui->euqal_2, scale_w, scale_h);
    resizer(ui->euqal_3, scale_w, scale_h);
    resizer(ui->euqal_4, scale_w, scale_h);
    resizer(ui->euqal_5, scale_w, scale_h);
    resizer(ui->euqal_6, scale_w, scale_h);

    resizer(ui->genprogress, scale_w, scale_h);

    resizer(ui->my_output_2, scale_w, scale_h);

    resizer(ui->note_a, scale_w, scale_h);
    resizer(ui->note_b, scale_w, scale_h);
    resizer(ui->note_c, scale_w, scale_h);
    resizer(ui->note_d, scale_w, scale_h);
    resizer(ui->note_e, scale_w, scale_h);
    resizer(ui->note_f, scale_w, scale_h);
    resizer(ui->note_g, scale_w, scale_h);
    resizer(ui->note_h, scale_w, scale_h);
    resizer(ui->note_i, scale_w, scale_h);
    resizer(ui->note_j, scale_w, scale_h);
    resizer(ui->note_out, scale_w, scale_h);

    resizer(ui->OOH, scale_w, scale_h);

    resizer(ui->oper00, scale_w, scale_h);
    resizer(ui->oper01, scale_w, scale_h);
    resizer(ui->oper02, scale_w, scale_h);
    resizer(ui->oper10, scale_w, scale_h);
    resizer(ui->oper11, scale_w, scale_h);
    resizer(ui->oper12, scale_w, scale_h);

    resizer(ui->solveprogress, scale_w, scale_h);

    resizer(ui->tableView, scale_w, scale_h);
    resizer(ui->tableView_2, scale_w, scale_h);

    resizer(remove_a, scale_w, scale_h);
    resizer(remove_b, scale_w, scale_h);
    resizer(remove_c, scale_w, scale_h);
    resizer(remove_d, scale_w, scale_h);
    resizer(remove_e, scale_w, scale_h);
    resizer(remove_f, scale_w, scale_h);
    resizer(remove_g, scale_w, scale_h);
    resizer(remove_h, scale_w, scale_h);
    resizer(remove_i, scale_w, scale_h);
    resizer(remove_j, scale_w, scale_h);

}

template<class T> void resizer(T* thing, double scale_w, double scale_h) {
    int thing_w = thing->width(),
            thing_h = thing->height();
    thing->resize(scale_w * thing_w, scale_h * thing_h);
    QPoint pos = thing->pos();
    int thing_posx = pos.x(),
            thing_posy = pos.y();
    thing->move(scale_w * thing_posx, scale_h * thing_posy);
}

template<class T> void colourer (T* thing, int r, int g, int b){
  /*
  QPalette p =  thing->palette();
	p.setColor(QPalette::Base, QColor(r, g, b, 255));
	thing->setPalette(p);
	*/
	//thing->setBrush(QColor(0, 0, 255, 127));
	thing->setStyleSheet(("background:rgb(" + to_string(r) + ", " + to_string(g) + ", " + to_string(b) + ");").c_str());
}


void MainWindow::colour_everything() {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            if ((*grt.letts[i][j][0])->text() == tr("")) {
              colourer(*grt.letts[i][j][0], 255, 255, 255);
              colourer(*grt.nums[i][j][0], 255, 255, 255);
            } else {
              colourer(*grt.letts[i][j][0], 255, 255, 51);
              colourer(*grt.nums[i][j][0], 255, 255, 51);
            }
            
            
            if ((*grt.letts[i][j][1])->text() == tr("")) {
              colourer(*grt.letts[i][j][1], 255, 255, 255);
              colourer(*grt.nums[i][j][1], 255, 255, 255);
            } else {
              colourer(*grt.letts[i][j][1], 180, 180, 255);
              colourer(*grt.nums[i][j][1], 180, 180, 255);
            }
            
            if ((*grt.letts[i][j][2])->text() == tr("")) {
              colourer(*grt.letts[i][j][2], 255, 255, 255);
              colourer(*grt.nums[i][j][2], 255, 255, 255);
            } else {
              colourer(*grt.letts[i][j][2], 255, 150, 150);
              colourer(*grt.nums[i][j][2], 255, 150, 150);
            }
            
            if ((*grt.letts[i][j][3])->text() == tr("")) {
              colourer(*grt.letts[i][j][3], 255, 255, 255);
              colourer(*grt.nums[i][j][3], 255, 255, 255);
            } else {
              colourer(*grt.letts[i][j][3], 255, 200, 150);
              colourer(*grt.nums[i][j][3], 255, 200, 150);
            }
        }
    }

    colourer(ui->tableView, 200, 255, 255);
    colourer(ui->tableView_2, 153, 255, 255);

    remove_a->setStyleSheet("background-color: red");
    remove_b->setStyleSheet("background-color: red");
    remove_c->setStyleSheet("background-color: red");
    remove_d->setStyleSheet("background-color: red");
    remove_e->setStyleSheet("background-color: red");
    remove_f->setStyleSheet("background-color: red");
    remove_g->setStyleSheet("background-color: red");
    remove_h->setStyleSheet("background-color: red");
    remove_i->setStyleSheet("background-color: red");
    remove_j->setStyleSheet("background-color: red");

}

bool MainWindow::all_nums_inserted() {
  auto sz = tab.n_to_c.size();
  
  if (sz > 0 && ui->set_a->text() == tr("")) return false;
  else if (sz == 1) return true;
  if (sz > 1 && ui->set_b->text() == tr("")) return false;
  else if (sz == 2) return true;
  if (sz > 2 && ui->set_c->text() == tr("")) return false;
  else if (sz == 3) return true;
  if (sz > 3 && ui->set_d->text() == tr("")) return false;
  else if (sz == 4) return true;
  if (sz > 4 && ui->set_e->text() == tr("")) return false;
  else if (sz == 5) return true;
  if (sz > 5 && ui->set_f->text() == tr("")) return false;
  else if (sz == 6) return true;
  if (sz > 6 && ui->set_g->text() == tr("")) return false;
  else if (sz == 7) return true;
  if (sz > 7 && ui->set_h->text() == tr("")) return false;
  else if (sz == 8) return true;
  if (sz > 8 && ui->set_i->text() == tr("")) return false;
  else if (sz == 9) return true;
  if (sz > 9 && ui->set_j->text() == tr("")) return false;
  
  return true;
}


void MainWindow::about_gce() {
    QMessageBox::about(this, tr("About"), tr("Assign a value between 0 and 9 to every letter in the table.\n"
                                             "You win when all the right number are inserted.\n"
                                             "To insert a number just tap in the little white square on the very right.\n"
                                             "Each little square corrispond to the letter on the left.\n"
                                             "To take notes you can use the rectangle on the right of every letter.\n"
                                             "To lock a letter tap on it in the list on the right.\n"
                                             "To unlock it tap again.\n"
                                             "To erase a number you can do it both by clicking on the white square on the right and delete it manually or you can simply tap on the red \"X\" on the right.\n"
                                             "The numbers written at the bottom are those which are not inserted yet."));

}


template<class T, class K> bool MainWindow::lock_or_not(T* set_thing, K *remove_thing) {

    if (set_thing->text() == tr("")) {
        set_thing->setReadOnly(false);
        return false;
    }
    bool is_RO = set_thing->isReadOnly();
    if (!is_RO) {  //se non lo è lo sta per diventare
        remove_thing->hide();
        colourer(set_thing, 100, 255, 100);  // Verde
    }
    else {
        remove_thing->show();
        colourer(set_thing, 255, 255, 255);  // Bianco
    }
    set_thing->setReadOnly(!is_RO);
    return true;
}

void MainWindow::on_set_n_textEdited(const QString &arg1, int n) {
    if (!already_inserted(n, arg1)) {
    grt.set_num(arg1.toStdString(), n);
    grt.update_lastlog();
    }
    update_remaining_nums();
    if (all_nums_inserted()) ui->check->show();
    else ui->check->hide();
}


void MainWindow::clear_set_n(QLineEdit* set_n, int n) {
    set_n->setText(tr(""));
    grt.set_num("", n);
    grt.update_lastlog();
    update_remaining_nums();
    ui->check->hide();
}

void MainWindow::orientationChanged(Qt::ScreenOrientation orientation)
{
    if (orientation == Qt::LandscapeOrientation || orientation == Qt::InvertedLandscapeOrientation)
        QMessageBox::about(this, tr("Orientation updated"), tr("Landscape (horizontal)"));  // Orizzontale
    else
        QMessageBox::about(this, tr("Orientation updated"), tr("Portrait (vertical)"));  // Orizzontale
    QRect rec = QApplication::desktop()->availableGeometry();
    // QRect rec = QApplication::desktop()->screenGeometry();
    int width = rec.width(),
            height = rec.height(),
            old_height = ui->tableView->height(),
            old_width = ui->tableView->width();
    resizer(ui->tableView, (double)width / old_width, (double)height / old_height);

    /*
    QRect rec = QApplication::desktop()->availableGeometry();
    int old_width = rec.width(),
            old_height = rec.height();
    */
    princ->resize((double)width / old_width, (double)height / old_height);
    lettere->resize((double)width / old_width, (double)height / old_height);
    numeri->resize((double)width / old_width, (double)height / old_height);
    gioco->resize((double)width / old_width, (double)height / old_height);
    loading->resize((double)width / old_width, (double)height / old_height);

    /*
    QMessageBox::about(this, tr("Let's"), tr("See"));  // Se io ci metto un messaggio prima, come questo, lui ha il tempo di girarsi e,
                                                       // nella riga successiva, prendere il rettangolo girato, non quello precedente
    QRect rec2 = QApplication::desktop()->availableGeometry();
    if (rec2.height() < rec2.width())
        QMessageBox::about(this, tr("Orientation"), tr("Landscape (Orizzontale)"));  // Orizzontale
    else
        QMessageBox::about(this, tr("Orientation"), tr("Portrait (Verticale)"));  // Verticale
    QMessageBox::about(this, tr("Available geometry"), tr((to_string(rec2.height()) + ", " + to_string(rec2.width())).c_str()));       // Dà 1157 720, 679 1198, 1075 720, 611 1198
    QMessageBox::about(this, tr("Screen geometry"), tr((to_string(rec.height()) + ", " + to_string(rec.width())).c_str()));            // Dà 1198 720, 720 1198, 1198 720, 720 1198
    QMessageBox::about(this, tr("Menu height"), tr(to_string(menu->sizeHint().height()).c_str()));        // Dà 128, 128
    QMessageBox::about(this, tr("Menu width"), tr(to_string(menu->sizeHint().width()).c_str()));          // Dà 225, 225

    QMessageBox::about(this, tr("Frame geometry height"), tr(to_string(frameGeometry().height()).c_str()));  // Dà 1252, 1252, 611, 1075
    QMessageBox::about(this, tr("Frame geometry width"), tr(to_string(frameGeometry().width()).c_str()));    // Dà 994,  994,  1198, 720
    QMessageBox::about(this, tr("Geometry height"), tr(to_string(geometry().height()).c_str()));             // Dà 1252, 1252, 611, 1075
    QMessageBox::about(this, tr("Geometry width"), tr(to_string(geometry().width()).c_str()));               // Dà 1252, 1252, 1198, 720
    // ALLA FINE I VALORI GIUSTI GIUSTI A PARTIRE DAL BORDO IN BASSO DEL MENU SONO:
    // IN VERTICALE   1075 720
    // IN ORIZZONTALE 611 1198
    // IN PRATICA SEMPRA CHE LA FUNZIONE GIUSTA SIA availableGeometry, MA SE FATTA
    // NEL CONSTRUCTOR DA' VALORI UN PO' SBALLATI PERCHE' IL MENU ANCORA NON ESISTE
    // IN VERTICALE IL MENU E' ALTO 82, IN ORIZZONTALE 68
    */
}


/***************************************************************************************/
template <class T, class K>
SchermataConferma::SchermataConferma(MainWindow* p, T* p1, const char* c_back, K *p2, const char* c_on, const char* what_to_ask) : Schermata(p),
message(new QTextEdit(parent)),
go_back(new QPushButton(parent)),
go_on(new QPushButton(parent)) {
    // Posiziono tutte le cose nella vecchia posizione
    message->resize(parent->old_width / 2, parent->false_old_height / 10);
    message->move(parent->old_width / 4, parent->false_old_height * 3 / 10);
    message->setAlignment(Qt::AlignCenter);
    message->setAlignment(Qt::AlignHCenter);
    message->setText(QMainWindow::tr(what_to_ask));
    message->setAlignment(Qt::AlignCenter);
    message->setAlignment(Qt::AlignHCenter);
    message->setReadOnly(true);
    message->setFontPointSize(go_back->font().pointSize());
    go_back->resize(parent->old_width /3, parent->false_old_height / 10);
    go_back->move(parent->old_width / 6, parent->false_old_height * 5 / 10);
    go_back->setText(QMainWindow::tr("Wha... no!\nGo back!"));
    go_on->resize(parent->old_width / 3, parent->false_old_height / 10);
    go_on->move(parent->old_width * 3 / 6, parent->false_old_height * 5 / 10);
    go_on->setText(QMainWindow::tr("That's what i want!\nContinue"));
    QMainWindow::connect(go_back, SIGNAL(released()), p1, c_back);
    QMainWindow::connect(go_on, SIGNAL(released()), p2, c_on);
    //QMessageBox::about(parent, to_string(go_back->pos().x()).c_str(), to_string(go_back->pos().y()).c_str());
    //QMessageBox::about(parent, to_string(parent->old_width).c_str(), to_string(parent->old_height).c_str());

    resize((double)width / old_width, (double)height / old_height);
    hide();

}

void SchermataConferma::show() {
    message->show();
    message->raise();
    go_back->show();
    go_back->raise();
    go_on->show();
    go_on->raise();

}
void SchermataConferma::hide() {
    message->hide();
    go_back->hide();
    go_on->hide();
}
void SchermataConferma::resize(double scale_w, double scale_h) {
    resizer(message, scale_w, scale_h);
    resizer(go_back, scale_w, scale_h);
    resizer(go_on, scale_w, scale_h);
}


SchermataSoloLettere::SchermataSoloLettere(MainWindow* p) : Schermata(p) { }
void SchermataSoloLettere::late_initializer() {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            for (int k = 0; k != 4; ++k)
                letts[i][j][k] = *(parent->grt.letts[i][j][k]);
        }
    }
    opers[0][0] = parent->ui->oper00;
    opers[0][1] = parent->ui->oper01;
    opers[0][2] = parent->ui->oper02;
    opers[1][0] = parent->ui->oper10;
    opers[1][1] = parent->ui->oper11;
    opers[1][2] = parent->ui->oper12;

    equals[0] = parent->ui->euqal_1;
    equals[1] = parent->ui->euqal_2;
    equals[2] = parent->ui->euqal_3;
    equals[3] = parent->ui->euqal_4;
    equals[4] = parent->ui->euqal_5;
    equals[5] = parent->ui->euqal_6;
    resize((double)width / old_width, (double)height / old_height);
    hide();
}

void SchermataSoloLettere::show() {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            for (int k = 0; k != 4; ++k) {
                letts[i][j][k]->show();
                letts[i][j][k]->raise();
            }
        }
    }
    for (int i = 0; i != 2; ++i)
        for (int j = 0; j != 3; ++j)
            opers[i][j]->show();
    for (int i = 0; i != 6; ++i)
        equals[i]->show();
}
void SchermataSoloLettere::hide() {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            for (int k = 0; k != 4; ++k) {
                letts[i][j][k]->hide();
            }
        }
    }
    for (int i = 0; i != 2; ++i)
        for (int j = 0; j != 3; ++j)
            opers[i][j]->hide();
    for (int i = 0; i != 6; ++i)
        equals[i]->hide();
}

void SchermataSoloLettere::resize(double scale_w, double scale_h) {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j)
            for (int k = 0; k != 4; ++k) {
                resizer(letts[i][j][k], scale_w, scale_h);
            }
    }
    for (int i = 0; i != 2; ++i)
        for (int j = 0; j != 3; ++j)
            resizer(opers[i][j], scale_w, scale_h);
    for (int i = 0; i != 6; ++i)
        resizer(equals[i], scale_w, scale_h);
}

SchermataSoloNumeri::SchermataSoloNumeri(MainWindow* p) : Schermata(p) {}
void SchermataSoloNumeri::late_initializer() {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            for (int k = 0; k != 4; ++k)
                nums[i][j][k] = *(parent->grt.nums[i][j][k]);
        }
    }


    resize((double)width / old_width, (double)height / old_height);
    hide();
}

void SchermataSoloNumeri::show() {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            for (int k = 0; k != 4; ++k) {
                nums[i][j][k]->show();
                nums[i][j][k]->raise();
            }
        }
    }
}
void SchermataSoloNumeri::hide() {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            for (int k = 0; k != 4; ++k) {
                nums[i][j][k]->hide();
            }
        }
    }
}

void SchermataSoloNumeri::resize(double scale_w, double scale_h) {
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j)
            for (int k = 0; k != 4; ++k) {
                resizer(nums[i][j][k], scale_w, scale_h);
            }
    }
}

SchermataGioco::SchermataGioco(MainWindow *p) :
    Schermata(p),
    slett(*parent->lettere),
    snums(*parent->numeri),
    completed(new QLineEdit(parent)),
    removes_visible(10),
    conf_newgame(p, this, SLOT(hide_conf_newgame_show_table_again()), this, SLOT(new_game_after_conf_newgame()), "Are you sure you want to begin a new game?"),
    conf_savetable(p, this, SLOT(hide_conf_savetable_show_table_again()), this, SLOT(save_table_after_conf_savetable()), "Are you sure you want to save the table?") {}

void SchermataGioco::late_initializer() {
    menu = parent->menu;
    missing_numbers = parent->ui->my_output_2;
    //completed = parent->ui->note_out;
    //completed->resize(parent->ui->note_out->width(), parent->ui->note_out->height());
    completed->resize(parent->old_width / 3, parent->false_old_height * 1 / 10);
    completed->move(parent->old_width * 1 / 10, parent->false_old_height * 9 / 20);
    completed->setAlignment(Qt::AlignCenter);
    completed->setAlignment(Qt::AlignHCenter);
    completed->setReadOnly(true);
    
    check = parent->ui->check;
    table = parent->ui->tableView_2;
    notes.push_back(parent->ui->note_a);
    notes.push_back(parent->ui->note_b);
    notes.push_back(parent->ui->note_c);
    notes.push_back(parent->ui->note_d);
    notes.push_back(parent->ui->note_e);
    notes.push_back(parent->ui->note_f);
    notes.push_back(parent->ui->note_g);
    notes.push_back(parent->ui->note_h);
    notes.push_back(parent->ui->note_i);
    notes.push_back(parent->ui->note_j);

    sets.push_back(parent->ui->set_a);
    sets.push_back(parent->ui->set_b);
    sets.push_back(parent->ui->set_c);
    sets.push_back(parent->ui->set_d);
    sets.push_back(parent->ui->set_e);
    sets.push_back(parent->ui->set_f);
    sets.push_back(parent->ui->set_g);
    sets.push_back(parent->ui->set_h);
    sets.push_back(parent->ui->set_i);
    sets.push_back(parent->ui->set_j);

    locks.push_back(parent->ui->check_a);
    locks.push_back(parent->ui->check_b);
    locks.push_back(parent->ui->check_c);
    locks.push_back(parent->ui->check_d);
    locks.push_back(parent->ui->check_e);
    locks.push_back(parent->ui->check_f);
    locks.push_back(parent->ui->check_g);
    locks.push_back(parent->ui->check_h);
    locks.push_back(parent->ui->check_i);
    locks.push_back(parent->ui->check_j);

    removes.push_back(parent->remove_a);
    removes.push_back(parent->remove_b);
    removes.push_back(parent->remove_c);
    removes.push_back(parent->remove_d);
    removes.push_back(parent->remove_e);
    removes.push_back(parent->remove_f);
    removes.push_back(parent->remove_g);
    removes.push_back(parent->remove_h);
    removes.push_back(parent->remove_i);
    removes.push_back(parent->remove_j);

    for (int i = 0; i != 10; ++i) {
        removes[i]->resize(41, 41);
        removes[i]->move(671, 10 + i * 50);
        removes[i]->raise();
    }

    resize((double)width / old_width, (double)height / old_height);
    hide();
}

void SchermataGioco::show() {

    // parent->menuBar()->setEnabled(true);
    // parent->menuBar()->addMenu(parent->menu);
    // parent->menu->setVisible(true);
    // parent->menu->menuAction()->setVisible(true);
    // parent->menuBar()->setVisible(true);
    // parent->menuWidget()->setVisible(true);
    // parent->menuBar()->show();
    // parent->menuWidget()->show();

    /*
    parent->newgame->setEnabled(true);
    parent->save->setEnabled(true);
    parent->back_to_menu->setEnabled(true);
    parent->about->setEnabled(true);
    */
    /*
    parent->menuBar()->update();
    parent->show();
    */
    // parent->menuBar()->addMenu(parent->menu);

    slett.show();
    /*if (nums_visible)*/ snums.show();
    
    completed->raise();
    completed->show();

    if (miss_nums_visible) missing_numbers->show();

    if (check_visible) check->show();

    table->show();

    int n_max = parent->tab.n_to_c.size();
    if (notes_visible)
        for (int i = 0; i != n_max; ++i)
            notes[i]->show();

    for (int i = 0; i != n_max; ++i) {
        sets[i]->show();
        locks[i]->show();
        //if (removes_visible[i]) removes[i]->show();
        if (!sets[i]->isReadOnly()) removes[i]->show();
    }

}

void SchermataGioco::hide() {

    // parent->menu->setVisible(false);
    // parent->menuBar()->setEnabled(false);


    // parent->menu->menuAction()->setVisible(false);
    // parent->menuBar()->setVisible(false);
    // parent->menuWidget()->setVisible(false);
    // parent->menuBar()->hide();
    // parent->menuWidget()->hide();

    /*
    parent->newgame->setEnabled(false);
    parent->save->setEnabled(false);
    parent->back_to_menu->setEnabled(false);
    parent->about->setEnabled(false);
    */
    /*
    parent->menuBar()->update();
    parent->show();
    */

    // parent->menuBar()->addMenu(parent->menu2);

    slett.hide();
    //nums_visible = snums.isVisible();
    snums.hide();
    //miss_nums_visible = missing_numbers->isVisible();
    missing_numbers->hide();
    completed->hide();
    check_visible = check->isVisible();
    check->hide();
    table->hide();
    notes_visible = notes[0]->isVisible();
    notes_visible = false;  // MOMENTANEO
    for (int i = 0; i != 10; ++i) notes[i]->hide();
    for (int i = 0; i != 10; ++i) {
        sets[i]->hide();
        locks[i]->hide();
        removes_visible[i] = removes[i]->isVisible();
        removes[i]->hide();
    }
}

void SchermataGioco::resize(double scale_w, double scale_h) {
    resizer(missing_numbers, scale_w, scale_h);
    resizer(completed, scale_w, scale_h);
    resizer(check, scale_w, scale_h);
    resizer(table, scale_w, scale_h);
    for (int i = 0; i != 10; ++i) {
        resizer(notes[i], scale_w, scale_h);
        resizer(sets[i], scale_w, scale_h);
        resizer(locks[i], scale_w, scale_h);
        resizer(removes[i], scale_w, scale_h);
    }
    // conf.resize(scale_w, scale_h);
}

SchermataLoading::SchermataLoading(MainWindow *p) : Schermata(p) {}
void SchermataLoading::late_initializer() {
    gen_bar = parent->ui->genprogress;
    solve_bar = parent->ui->solveprogress;
    gen_bar->resize(parent->old_width / 3, parent->false_old_height / 15);
    gen_bar->move(parent->old_width / 3, parent->false_old_height * 4 / 15);
    solve_bar->resize(parent->old_width / 3, parent->false_old_height / 15);
    solve_bar->move(parent->old_width / 3, parent->false_old_height * 9 / 15);
    resize((double)width / old_width, (double)height / old_height);
    hide();
}

void SchermataLoading::show() {
    gen_bar->show();
    solve_bar->show();
}

void SchermataLoading::hide() {
    gen_bar->hide();
    solve_bar->hide();
}

void SchermataLoading::resize(double scale_w, double scale_h) {
    resizer(gen_bar, scale_w, scale_h);
    resizer(solve_bar, scale_w, scale_h);
}


SchermataPrincipale::SchermataPrincipale(MainWindow *p) :
    Schermata(p),
    continue_new_game(new QPushButton(parent)),
    settings(new QPushButton(parent)),
    load_table(new QPushButton(parent)),
    about(new QPushButton(parent)),
    load_game(parent, this, SLOT(hide_conf_show_menu_again()), this, SLOT(load_game_after_conf()), "Are you sure you want to load a game?") {}

void SchermataPrincipale::late_initializer() {
    continue_new_game->resize(parent->old_width / 2, parent->false_old_height / 8);
    continue_new_game->move(parent->old_width / 4, parent->false_old_height * 2 / 8);
    continue_new_game->setText(QMainWindow::tr("Continue"));
    settings->resize(parent->old_width / 2, parent->false_old_height / 8);
    settings->move(parent->old_width / 4, parent->false_old_height * 3 / 8);
    settings->setText(QMainWindow::tr("Settings"));
    load_table->resize(parent->old_width / 2, parent->false_old_height / 8);
    load_table->move(parent->old_width / 4, parent->false_old_height * 4 / 8);
    load_table->setText(QMainWindow::tr("Load Table"));
    about->resize(parent->old_width / 2, parent->false_old_height / 8);
    about->move(parent->old_width / 4, parent->false_old_height * 5 / 8);
    about->setText(QMainWindow::tr("About"));

    QMainWindow::connect(continue_new_game, SIGNAL(released()), this, SLOT(hide_menu_show_table()));
    QMainWindow::connect(settings, SIGNAL(released()), this, SLOT(hide_menu_show_settings()));
    QMainWindow::connect(load_table, SIGNAL(released()), this, SLOT(hide_menu_show_conf_load()));
    QMainWindow::connect(about, SIGNAL(released()), parent, SLOT(about_gce()));

    resize((double)width / old_width, (double)height / old_height);
    hide();
    // continue_new_game->move(0, 1198 - parent->menu->sizeHint().height() + 4);  // a "+ 3" si vede, a "+ 4" no
    // continue_new_game->move(0, 610);
}

void SchermataPrincipale::show() {
    std::ifstream log("/storage/emulated/0/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/gce2_proj/last_log.txt");
    if (!log.is_open())
      log.open("/storage/emulated/0/CalcoloEnigmatico/last_log.txt");
    if (!log.is_open())
      log.open("last_log.txt");
    else if (!log.is_open())
        continue_new_game->setText(QMainWindow::tr("New Game"));
    else
        continue_new_game->setText(QMainWindow::tr("Continue"));
    continue_new_game->show();
    continue_new_game->raise();
    settings->show();
    settings->raise();
    load_table->show();
    load_table->raise();
    about->show();
    about->raise();
}
void SchermataPrincipale::hide() {
    continue_new_game->hide();
    settings->hide();
    load_table->hide();
    about->hide();
}
void SchermataPrincipale::resize(double scale_w, double scale_h) {
    resizer(continue_new_game, scale_w, scale_h);
    resizer(settings, scale_w, scale_h);
    resizer(load_table, scale_w, scale_h);
    resizer(about, scale_w, scale_h);
    // load_game.resize(scale_w, scale_h);
}

void SchermataPrincipale::hide_menu_show_table() {
    hide();
    if (parent->gioco->slett.letts[0][0][3]->text() == QMainWindow::tr("")) {
        parent->loading->show();
        parent->on_OOH_released();
        parent->loading->hide();
    }
    parent->gioco->show();
}
