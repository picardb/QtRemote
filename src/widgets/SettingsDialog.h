/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QDialog>

#include <QLineEdit>
#include <QPushButton>

/*
 * SettingsDialog class.
 *
 * Dialog containing configuration widgets for the application settings.
 */
class SettingsDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit   *m_pLogDirEdit;
    QPushButton *m_pLogBrowseButton;
    QPushButton *m_pOkButton;
    QPushButton *m_pCancelButton;

public:
    SettingsDialog(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

    QString getLogDir() const { return m_pLogDirEdit->text(); }

private slots:
    void onLogBrowseButtonClicked();
};
