/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCIJUDGEDOCK_H
#define KCIJUDGEDOCK_H

#include <QList>
#include <QLabel>
#include <QWidget>
#include <QPalette>
#include <QSplitter>
#include <QTreeView>
#include <QIcon>
#include <QAction>
#include <QPlainTextEdit>
#include <QTabWidget>
#include <QToolButton>
#include <QToolBar>
#include <QMimeData>
#include <QDebug>
#include <QKeySequence>
#include <QVBoxLayout>
#include <QDockWidget>

class kciJudgeFileEdit : public QWidget
{
    Q_OBJECT
public:
    explicit kciJudgeFileEdit(QWidget *parent = 0);
    QString inputFile();
    QString outputFile();

signals:
    void textChange();

private:
    QLabel *lblInput, *lblOutput, *lblUserOutput;
    QPlainTextEdit *InputFileEdit, *OutputFileEdit, *UserOutput;
    QVBoxLayout *EditLayout;
};

class kciJudgeEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit kciJudgeEditWidget(QWidget *parent = 0);

private slots:
    void addNewTab();
    void removeCurrentTab();
    void documentChanged();
    void backupTestData();
    void importTestData();

private:
    int judge_file_count;
    QTabWidget *tabJudgeFiles;
    QToolBar *tlbJudge;
    QVBoxLayout *MainLayout;
    QToolButton *tlbacAdd, *tlbacRemove, *tlbacStartAll, *tlbacStop,
                *tlbacBackup, *tlbacImport;

    QList<QString> strInputFiles, strOutputFiles;

    void resetJudgetEditWidget();
    void removeTabIndex(int TabIndex);
};

class kciJudgeDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit kciJudgeDock(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QTreeView *trevwJudgeList;
    QSplitter *splCombine;
    QList<int> l_sizes;
    QToolButton *addANewTab;
    kciJudgeEditWidget *kjwEditWidget;
};

#endif // KCIJUDGEDOCK_H
