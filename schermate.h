#ifndef SCHERMATE_H
#define SCHERMATE_H

#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include "mainwindow.h"

class Schermata {
public:
    Schermata(MainWindow* p): parent(p) {}

    MainWindow *parent;
    static int height;
    static int width;

    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void switch_to(Schermata* s) { hide(); s->show(); }

    bool modified = false;

};

class SchermataConferma : public Schermata {
public:

    SchermataConferma(MainWindow* p, const char* c_back, const char* c_on, const char* what_to_ask);

    QLineEdit *message;
    QPushButton *go_back;
    QPushButton *go_on;


    void show() override;
    void hide() override;
};

class SchermataPrincipale : public Schermata {
public:

    SchermataPrincipale(MainWindow* p);

    QPushButton *continue_new_game;
    QPushButton *settings;
    QPushButton *load_table;
    QPushButton *about;
    SchermataConferma load_game;

    void show() override;
    void hide() override;
};

class SchermataSoloLettere : public Schermata {
public:

    SchermataSoloLettere(MainWindow* p, lab_tab &t);

    //decltype(parent->ui->elem00_1_1) letts[3][3][4];

    void show() override;
    void hide() override;
};

class SchermataSoloNumeri : public Schermata {
public:

    SchermataSoloNumeri(MainWindow* p, lab_tab &t);

    //decltype(parent->ui->elem00_1_1) nums[3][3][4];

    void show() override;
    void hide() override;
};

class SchermataGioco : public Schermata {
public:

    SchermataGioco(MainWindow *p, SchermataSoloLettere &sl, SchermataSoloNumeri &sn) : parent(p), slett(sl), snums(sn) {}

    SchermataSoloLettere &slett;
    SchermataSoloNumeri &snums;
    void show() override;
    void hide() override;
};

#endif // SCHERMATE_H
