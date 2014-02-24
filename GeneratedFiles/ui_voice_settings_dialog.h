/********************************************************************************
** Form generated from reading UI file 'voice_settings_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOICE_SETTINGS_DIALOG_H
#define UI_VOICE_SETTINGS_DIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VoiceSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *sourceLabel;
    QComboBox *sourceListBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *moduleLabel;
    QComboBox *moduleListBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *languageLabel;
    QComboBox *languageListBox;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;
    QSpacerItem *spacerItem;
    QPushButton *cancelButton;

    void setupUi(QDialog *VoiceSettingsDialog)
    {
        if (VoiceSettingsDialog->objectName().isEmpty())
            VoiceSettingsDialog->setObjectName(QStringLiteral("VoiceSettingsDialog"));
        VoiceSettingsDialog->resize(281, 150);
        VoiceSettingsDialog->setMinimumSize(QSize(220, 150));
        VoiceSettingsDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(VoiceSettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        sourceLabel = new QLabel(VoiceSettingsDialog);
        sourceLabel->setObjectName(QStringLiteral("sourceLabel"));

        horizontalLayout->addWidget(sourceLabel);

        sourceListBox = new QComboBox(VoiceSettingsDialog);
        sourceListBox->setObjectName(QStringLiteral("sourceListBox"));

        horizontalLayout->addWidget(sourceListBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        moduleLabel = new QLabel(VoiceSettingsDialog);
        moduleLabel->setObjectName(QStringLiteral("moduleLabel"));

        horizontalLayout_2->addWidget(moduleLabel);

        moduleListBox = new QComboBox(VoiceSettingsDialog);
        moduleListBox->setObjectName(QStringLiteral("moduleListBox"));

        horizontalLayout_2->addWidget(moduleListBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        languageLabel = new QLabel(VoiceSettingsDialog);
        languageLabel->setObjectName(QStringLiteral("languageLabel"));

        horizontalLayout_3->addWidget(languageLabel);

        languageListBox = new QComboBox(VoiceSettingsDialog);
        languageListBox->setObjectName(QStringLiteral("languageListBox"));

        horizontalLayout_3->addWidget(languageListBox);


        verticalLayout->addLayout(horizontalLayout_3);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(VoiceSettingsDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        cancelButton = new QPushButton(VoiceSettingsDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(VoiceSettingsDialog);
        QObject::connect(okButton, SIGNAL(clicked()), VoiceSettingsDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), VoiceSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VoiceSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *VoiceSettingsDialog)
    {
        VoiceSettingsDialog->setWindowTitle(QApplication::translate("VoiceSettingsDialog", "VoiceSettings", 0));
        sourceLabel->setText(QApplication::translate("VoiceSettingsDialog", "Source:", 0));
        moduleLabel->setText(QApplication::translate("VoiceSettingsDialog", "Module:", 0));
        languageLabel->setText(QApplication::translate("VoiceSettingsDialog", "Language:", 0));
        okButton->setText(QApplication::translate("VoiceSettingsDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("VoiceSettingsDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class VoiceSettingsDialog: public Ui_VoiceSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOICE_SETTINGS_DIALOG_H
