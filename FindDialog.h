#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class FindDialog : public QDialog
{
    Q_OBJECT
private:
    QLabel* title_Label;
    QLineEdit* findString_LineEdit;
    QPushButton* find_PushButton;
    QPushButton* close_PushButton;
    QCheckBox* matchCase_CheckBox;
    QCheckBox* goBack_CheckBox;
public:
    FindDialog(QWidget* parent = nullptr);
signals:
    void findWordDetail(const QString& str, bool direction, bool caseSensitivity);
private slots:
    void findIsEnabled(const QString& str);
    void findWords();
};


#endif // FINDDIALOG_H
