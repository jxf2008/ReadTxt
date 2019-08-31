#include <QMessageBox>
#include <QDateTime>
#include <QFontDialog>
#include <QFileDialog>
#include <QTextStream>
#include "ReadTxt.h"

ReadTxt::ReadTxt(QWidget *parent)
    : QMainWindow(parent)
{
    createAction();
    createMenu();
    createMenuBar();
    setActionPix();
    createToolBar();
    createStatusBar();
    setHotKey();
    setActionProperty();
    editor_TextEdit = new QTextEdit;
    setCentralWidget(editor_TextEdit);
    find_Dialog = nullptr;
    setWindowTitle("记事本");
    setWindowIcon(QIcon(":/images/title.png"));
    connectSignalAndSlot();
}

ReadTxt::~ReadTxt()
{

}

void ReadTxt::closeEvent(QCloseEvent* event)
{
    if(editor_TextEdit->document()->isModified() and !(editor_TextEdit->toPlainText().isEmpty()))
    {
        int buttons = QMessageBox::warning(this,tr("文件未保存"),tr("原文件尚未保存，是否需要保存？"),QMessageBox::Yes|QMessageBox::No);
        if(buttons == QMessageBox::Yes)
        {
            if(currentFilePath.isEmpty())
                saveAsCurrentFile();
            else
                saveCurrentFile();
            event->ignore();
        }
        if(buttons == QMessageBox::No)
        {
            event->accept();
            return;
        }
    }
}

void ReadTxt::createAction()
{
    open_Action = new QAction("打开",this);
    new_Action = new QAction("新建",this);
    save_Action = new QAction("保存",this);
    saveAs_Action = new QAction("另存为...",this);
    close_Action = new QAction("关闭",this);

    redo_Action = new QAction("撤销",this);
    undo_Action = new QAction("恢复",this);
    cut_Action = new QAction("剪切",this);
    copy_Action = new QAction("复制",this);
    paste_Action = new QAction("粘帖",this);
    delete_Action = new QAction("删除",this);
    find_Action = new QAction("查询",this);
    findNext_Action = new QAction("查询下一个",this);
    selectAll_Action = new QAction("全选",this);
    dateAndTime_Action = new QAction("日期/时间",this);

    autoChangeLine_Action = new QAction("自动换行",this);
    leftAlignment_Action = new QAction("左对齐",this);
    rightAlignment_Action = new QAction("右对齐",this);
    midAlignment_Action = new QAction("中对齐",this);
    font_Action = new QAction("字体",this);

    findHelp_Action = new QAction("关于帮助",this);
    about_Action = new QAction("关于记事本",this);
}

void ReadTxt::createMenu()
{
    file_Menu = new QMenu("文件");
    file_Menu->addAction(open_Action);
    file_Menu->addAction(new_Action);
    file_Menu->addAction(save_Action);
    file_Menu->addAction(saveAs_Action);
    file_Menu->addSeparator();
    file_Menu->addAction(close_Action);

    edit_Menu = new QMenu("编辑");
    edit_Menu->addAction(redo_Action);
    edit_Menu->addAction(undo_Action);
    edit_Menu->addSeparator();
    edit_Menu->addAction(cut_Action);
    edit_Menu->addAction(copy_Action);
    edit_Menu->addAction(paste_Action);
    edit_Menu->addAction(delete_Action);
    edit_Menu->addSeparator();
    edit_Menu->addAction(find_Action);
    edit_Menu->addAction(findNext_Action);
    edit_Menu->addSeparator();
    edit_Menu->addAction(selectAll_Action);
    edit_Menu->addAction(dateAndTime_Action);

    format_Menu = new QMenu("格式");
    format_Menu->addAction(autoChangeLine_Action);
    format_Menu->addSeparator();
    format_Menu->addAction(leftAlignment_Action);
    format_Menu->addAction(rightAlignment_Action);
    format_Menu->addAction(midAlignment_Action);
    format_Menu->addSeparator();
    format_Menu->addAction(font_Action);

    help_Menu = new QMenu("帮助");
    help_Menu->addAction(findHelp_Action);
    help_Menu->addAction(about_Action);
}

void ReadTxt::createMenuBar()
{
    fileMenu_MenuBar = menuBar();
    fileMenu_MenuBar->addMenu(file_Menu);
    fileMenu_MenuBar->addMenu(edit_Menu);
    fileMenu_MenuBar->addMenu(format_Menu);
    fileMenu_MenuBar->addMenu(help_Menu);
}

void ReadTxt::connectSignalAndSlot()
{
    connect(find_Action,SIGNAL(triggered()),this,SLOT(showFindDialog()));
    connect(redo_Action,SIGNAL(triggered()),editor_TextEdit,SLOT(redo()));
    connect(undo_Action,SIGNAL(triggered()),editor_TextEdit,SLOT(undo()));
    connect(paste_Action,SIGNAL(triggered()),editor_TextEdit,SLOT(paste()));
    connect(cut_Action,SIGNAL(triggered()),editor_TextEdit,SLOT(cut()));
    connect(copy_Action,SIGNAL(triggered()),editor_TextEdit,SLOT(copy()));
    connect(selectAll_Action,SIGNAL(triggered()),editor_TextEdit,SLOT(selectAll()));
    connect(findNext_Action,SIGNAL(triggered()),this,SLOT(showFindDialog()));
    connect(delete_Action,SIGNAL(triggered()),this,SLOT(deleteSelectText()));
    connect(dateAndTime_Action,SIGNAL(triggered()),this,SLOT(dateAndTime()));
    connect(autoChangeLine_Action,SIGNAL(triggered()),this,SLOT(setAutoChangeLine()));
    connect(leftAlignment_Action,SIGNAL(triggered()),this,SLOT(setAlignmentFormat()));
    connect(rightAlignment_Action,SIGNAL(triggered()),this,SLOT(setAlignmentFormat()));
    connect(midAlignment_Action,SIGNAL(triggered()),this,SLOT(setAlignmentFormat()));
    connect(autoChangeLine_Action,SIGNAL(triggered()),this,SLOT(setAutoChangeLine()));
    connect(font_Action,SIGNAL(triggered()),this,SLOT(setTextFont()));
    connect(open_Action,SIGNAL(triggered()),this,SLOT(openExistFile()));
    connect(new_Action,SIGNAL(triggered()),this,SLOT(createNewFile()));
    connect(save_Action,SIGNAL(triggered()),this,SLOT(saveCurrentFile()));
    connect(saveAs_Action,SIGNAL(triggered()),this,SLOT(saveAsCurrentFile()));
    connect(close_Action,SIGNAL(triggered()),this,SLOT(close()));
}

void ReadTxt::setActionPix()
{
    new_Action->setIcon(QIcon(":/images/new.png"));
    open_Action->setIcon(QIcon(":/images/open.png"));
    save_Action->setIcon(QIcon(":/images/save.png"));
    saveAs_Action->setIcon(QIcon(":/images/saveAs.png"));

    redo_Action->setIcon(QIcon(":/images/re.png"));
    undo_Action->setIcon(QIcon(":/images/un.png"));
    cut_Action->setIcon(QIcon(":/images/cut.png"));
    copy_Action->setIcon(QIcon(":/images/copy.png"));
    paste_Action->setIcon(QIcon(":/images/paste.png"));
    delete_Action->setIcon(QIcon(":/images/delete.png"));

    leftAlignment_Action->setIcon(QIcon(":/images/left.png"));
    rightAlignment_Action->setIcon(QIcon(":/images/right.png"));
    midAlignment_Action->setIcon(QIcon(":/images/center.png"));
}

void ReadTxt::createToolBar()
{
    fileTools_ToolBar = addToolBar("文件");
    fileTools_ToolBar->addAction(new_Action);
    fileTools_ToolBar->addAction(open_Action);
    fileTools_ToolBar->addAction(save_Action);
    fileTools_ToolBar->addAction(saveAs_Action);

    editTools_ToolBar = addToolBar("编辑");
    editTools_ToolBar->addAction(redo_Action);
    editTools_ToolBar->addAction(undo_Action);
    editTools_ToolBar->addAction(cut_Action);
    editTools_ToolBar->addAction(copy_Action);
    editTools_ToolBar->addAction(paste_Action);
    editTools_ToolBar->addAction(delete_Action);

    formatTools_ToolBar = addToolBar("格式");
    formatTools_ToolBar->addAction(leftAlignment_Action);
    formatTools_ToolBar->addAction(midAlignment_Action);
    formatTools_ToolBar->addAction(rightAlignment_Action);
}

void ReadTxt::createStatusBar()
{
    statusBar();
    new_Action->setStatusTip(tr("新建一个文件"));
    open_Action->setStatusTip(tr("打开一个文件"));
    save_Action->setStatusTip(tr("保存当前文件"));
}

void ReadTxt::setHotKey()
{
    new_Action->setShortcut(QKeySequence::New);
    copy_Action->setShortcut(QKeySequence::Copy);
    paste_Action->setShortcut(QKeySequence::Paste);
}

void ReadTxt::showFindDialog()
{
    if(find_Dialog == nullptr)
        find_Dialog = new FindDialog(this);
    find_Dialog->show();
    find_Dialog->raise();
    find_Dialog->activateWindow();
}

void ReadTxt::findWordInText(const QString& str , bool direction , bool caseSensitivity)
{
    bool findWord = false;
    if(direction == false and caseSensitivity == false)
        findWord = editor_TextEdit->find(str);
    if(direction == false and caseSensitivity == true)
        findWord = editor_TextEdit->find(str,QTextDocument::FindCaseSensitively);
    if(direction == true and caseSensitivity == false)
        findWord = editor_TextEdit->find(str,QTextDocument::FindBackward);
    if(direction == true and caseSensitivity == true)
        findWord = editor_TextEdit->find(str,QTextDocument::FindCaseSensitively|QTextDocument::FindBackward);
    if(findWord == false)
        QMessageBox::information(this,tr("查询"),tr("无结果"),QMessageBox::Yes);
}

void ReadTxt::deleteSelectText()
{
    editor_TextEdit->textCursor().removeSelectedText();
}

void ReadTxt::dateAndTime()
{
  editor_TextEdit->insertPlainText(QDateTime::currentDateTime().toString());
}

void ReadTxt::setActionProperty()
{
    autoChangeLine_Action->setCheckable(true);
    autoChangeLine_Action->setChecked(true);

    leftAlignment_Action->setCheckable(true);
    rightAlignment_Action->setCheckable(true);
    midAlignment_Action->setCheckable(true);
    alignmentFormat_ActionGroup = new QActionGroup(this);
    alignmentFormat_ActionGroup->addAction(leftAlignment_Action);
    alignmentFormat_ActionGroup->addAction(rightAlignment_Action);
    alignmentFormat_ActionGroup->addAction(midAlignment_Action);
}

void ReadTxt::setAutoChangeLine()
{
    if(autoChangeLine_Action->isChecked())
        editor_TextEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    else
        editor_TextEdit->setLineWrapMode(QTextEdit::NoWrap);
}

void ReadTxt::setAlignmentFormat()
{
    if(leftAlignment_Action->isChecked())
        editor_TextEdit->setAlignment(Qt::AlignLeft);
    if(rightAlignment_Action->isChecked())
        editor_TextEdit->setAlignment(Qt::AlignRight);
    if(midAlignment_Action->isChecked())
        editor_TextEdit->setAlignment(Qt::AlignCenter);
}

void ReadTxt::setTextFont()
{
    bool getFont = true;
    QFont newFont= QFontDialog::getFont(&getFont,editor_TextEdit->currentFont(),this,tr("选择字体"));   //注释5
    if(getFont == true)
        editor_TextEdit->setCurrentFont(newFont);
}

void ReadTxt::openExistFile()
{
    currentFilePath = QFileDialog::getOpenFileName(this,tr("打开文件"),".",tr("Text(*.txt)"));  //注释5
    if(currentFilePath.isEmpty())
    {
        QMessageBox::warning(this,tr("空文件"),tr("该文件为空或不存在"),QMessageBox::Yes);
        return;
    }
    QFile fs(currentFilePath);
    QTextStream fDate(&fs);
    fs.open(QIODevice::ReadWrite|QIODevice::Text);
    editor_TextEdit->setText(fDate.readAll());
}

void ReadTxt::saveCurrentFile()
{
    if(currentFilePath.isEmpty())
        saveAsCurrentFile();
    else
    {
        QFile fs(currentFilePath);
        QTextStream fDate(&fs);
        fs.open(QIODevice::WriteOnly);
        fDate<<(editor_TextEdit->toPlainText());
        editor_TextEdit->document()->setModified(false);
    }
}

void ReadTxt::saveAsCurrentFile()
{
    currentFilePath = QFileDialog::getSaveFileName(this,tr("文件另存为"),".",tr("Text(*.txt)"));//注释11
    if(currentFilePath.isEmpty())
    {
        QMessageBox::warning(this,tr("保存失败"),tr("保存文件失败"),QMessageBox::Yes);
        return;
    }

    QFile fs(currentFilePath);
    QTextStream fDate(&fs);
    fs.open(QIODevice::WriteOnly);
    fDate<<(editor_TextEdit->toPlainText());
    editor_TextEdit->document()->setModified(false);
}

void ReadTxt::createNewFile()
{
    if(editor_TextEdit->document()->isModified() && !(editor_TextEdit->toPlainText().isEmpty()))
    {
        int buttons = QMessageBox::warning(this,tr("文件未保存"),tr("原文件尚未保存，是否需要保存？"),QMessageBox::Yes|QMessageBox::No);
        if(buttons == QMessageBox::Yes)
        {
            if(currentFilePath.isEmpty())
                saveAsCurrentFile();
            else
                saveCurrentFile();
        }
        if(buttons == QMessageBox::No)
            editor_TextEdit->clear();
    }
  if(currentFilePath.isEmpty())
    return;
  editor_TextEdit->clear();
}
