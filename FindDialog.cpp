#include <QHBoxLayout>
#include <QVBoxLayout>
#include "FindDialog.h"

FindDialog::FindDialog(QWidget* parent)
    :QDialog(parent)
{
    title_Label = new QLabel("查询内容");
    findString_LineEdit = new QLineEdit;
    find_PushButton = new QPushButton("查询");
    close_PushButton = new QPushButton("取消");
    matchCase_CheckBox = new QCheckBox("区分大小写");
    goBack_CheckBox = new QCheckBox("向后查询");

    QHBoxLayout* string_Layout = new QHBoxLayout;
    string_Layout->addWidget(title_Label);
    string_Layout->addWidget(findString_LineEdit);
    QVBoxLayout* case_Layout = new QVBoxLayout;
    case_Layout->addLayout(string_Layout);
    case_Layout->addWidget(matchCase_CheckBox);
    case_Layout->addWidget(goBack_CheckBox);
    QVBoxLayout* pushButton_Layout = new QVBoxLayout;
    pushButton_Layout->addWidget(find_PushButton);
    pushButton_Layout->addWidget(close_PushButton);
    pushButton_Layout->addStretch();
    QHBoxLayout* main_Layout = new QHBoxLayout;
    main_Layout->addLayout(case_Layout);
    main_Layout->addLayout(pushButton_Layout);
    setLayout(main_Layout);
    main_Layout->setSizeConstraint(QLayout::SetFixedSize);

    find_PushButton->setDefault(true);
    find_PushButton->setEnabled(false);

    connect(findString_LineEdit,SIGNAL(textChanged(const QString&)),this,SLOT(findIsEnabled(const QString&)));
    connect(close_PushButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(find_PushButton,SIGNAL(clicked()),this,SLOT(FindWords()));

    setWindowTitle("查询");
}

void FindDialog::findIsEnabled(const QString& str)
{
    find_PushButton->setEnabled(!str.isEmpty());
}

void FindDialog::findWords()
{
    bool caseSensitivity = matchCase_CheckBox->isChecked();
    bool direction = goBack_CheckBox->isChecked();
    QString strs = findString_LineEdit->text();
    emit findWordDetail(strs,direction,caseSensitivity);
}
