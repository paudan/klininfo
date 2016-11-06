/****************************************************************************
** Form interface generated from reading ui file '/home/Paulius/klininfo_v0.2/klininfo/src/selsavedlg.ui'
**
** Created: An Lie 20 21:13:01 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.1   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SELSAVEDLG_H
#define SELSAVEDLG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QCheckBox;
class QPushButton;

class SelSaveDlg : public QDialog
{
    Q_OBJECT

public:
    SelSaveDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~SelSaveDlg();

    QLabel* textLabel1;
    QCheckBox* checkBox1;
    QCheckBox* checkBox2;
    QCheckBox* checkBox4;
    QCheckBox* checkBox5;
    QCheckBox* checkBox6;
    QCheckBox* checkBox7;
    QCheckBox* checkBox8;
    QCheckBox* checkBox15;
    QPushButton* pushButton2;
    QCheckBox* checkBox9;
    QCheckBox* checkBox3;
    QCheckBox* checkBox11;
    QCheckBox* checkBox12;
    QCheckBox* checkBox10;
    QCheckBox* checkBox13;
    QCheckBox* checkBox14;
    QCheckBox* checkBox16;

signals:
    void apply();

public slots:
    virtual void applySelection();

protected:
    QGridLayout* SelSaveDlgLayout;

protected slots:
    virtual void languageChange();

};

#endif // SELSAVEDLG_H
