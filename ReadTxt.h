#ifndef READTXT_H
#define READTXT_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QActionGroup>
#include <QCloseEvent>
#include "FindDialog.h"

class ReadTxt : public QMainWindow
{
    Q_OBJECT
private:
    QAction* open_Action;
    QAction* new_Action;
    QAction* save_Action;
    QAction* saveAs_Action;
    QAction* close_Action;
    QAction* redo_Action;
    QAction* undo_Action;
    QAction* cut_Action;
    QAction* copy_Action;
    QAction* paste_Action;
    QAction* delete_Action;
    QAction* find_Action;
    QAction* findNext_Action;
    QAction* selectAll_Action;
    QAction* dateAndTime_Action;
    QAction* autoChangeLine_Action;
    QAction* leftAlignment_Action;
    QAction* rightAlignment_Action;
    QAction* midAlignment_Action;
    QAction* font_Action;
    QAction* findHelp_Action;
    QAction* about_Action;

    QMenuBar* fileMenu_MenuBar;
    QMenu* file_Menu;
    QMenu* edit_Menu;
    QMenu* format_Menu;
    QMenu* help_Menu;

    QTextEdit* editor_TextEdit;

    QToolBar* fileTools_ToolBar;
    QToolBar* editTools_ToolBar;
    QToolBar* formatTools_ToolBar;

    QActionGroup* alignmentFormat_ActionGroup;

    FindDialog* find_Dialog;

    QString currentFilePath;

    void createAction();
    void createMenu();
    void createMenuBar();
    void connectSignalAndSlot();
    void setActionPix();
    void createToolBar();
    void createStatusBar();
    void setHotKey();
    void setActionProperty();
public:
    ReadTxt(QWidget *parent = nullptr);
    ~ReadTxt();
protected:
    void closeEvent(QCloseEvent* event);
private slots:
    void showFindDialog();
    void findWordInText(const QString& str , bool direction , bool caseSensitivity);
    void deleteSelectText();
    void dateAndTime();
    void setAutoChangeLine();
    void setAlignmentFormat();
    void setTextFont();
    void openExistFile();
    void saveCurrentFile();
    void saveAsCurrentFile();
    void createNewFile();
};

#endif // READTXT_H
