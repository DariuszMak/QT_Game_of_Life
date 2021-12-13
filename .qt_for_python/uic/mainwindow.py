# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'mainwindow.ui'
##
## Created by: Qt User Interface Compiler version 6.1.3
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import *  # type: ignore
from PySide6.QtGui import *  # type: ignore
from PySide6.QtWidgets import *  # type: ignore


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.setEnabled(True)
        MainWindow.resize(1113, 634)
        sizePolicy = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MainWindow.sizePolicy().hasHeightForWidth())
        MainWindow.setSizePolicy(sizePolicy)
        MainWindow.setMinimumSize(QSize(0, 0))
        MainWindow.setMaximumSize(QSize(16777215, 16777215))
        MainWindow.setLayoutDirection(Qt.LeftToRight)
        self.actionWczytaj_jako = QAction(MainWindow)
        self.actionWczytaj_jako.setObjectName(u"actionWczytaj_jako")
        self.action_Zapisz = QAction(MainWindow)
        self.action_Zapisz.setObjectName(u"action_Zapisz")
        self.actionZapisz_jako = QAction(MainWindow)
        self.actionZapisz_jako.setObjectName(u"actionZapisz_jako")
        self.actionWczytaj = QAction(MainWindow)
        self.actionWczytaj.setObjectName(u"actionWczytaj")
        self.action_Nowy = QAction(MainWindow)
        self.action_Nowy.setObjectName(u"action_Nowy")
        self.actionOd_wie = QAction(MainWindow)
        self.actionOd_wie.setObjectName(u"actionOd_wie")
        self.actionKolor_ywych_kom_rek = QAction(MainWindow)
        self.actionKolor_ywych_kom_rek.setObjectName(u"actionKolor_ywych_kom_rek")
        self.actionKo_lor_martwych_kom_rek = QAction(MainWindow)
        self.actionKo_lor_martwych_kom_rek.setObjectName(u"actionKo_lor_martwych_kom_rek")
        self.actionO_programie = QAction(MainWindow)
        self.actionO_programie.setObjectName(u"actionO_programie")
        self.action_Ustawienia_zasad = QAction(MainWindow)
        self.action_Ustawienia_zasad.setObjectName(u"action_Ustawienia_zasad")
        self.centralWidget = QWidget(MainWindow)
        self.centralWidget.setObjectName(u"centralWidget")
        self.gridLayout = QGridLayout(self.centralWidget)
        self.gridLayout.setSpacing(6)
        self.gridLayout.setContentsMargins(11, 11, 11, 11)
        self.gridLayout.setObjectName(u"gridLayout")
        self.horizontalLayout_5 = QHBoxLayout()
        self.horizontalLayout_5.setSpacing(6)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.verticalLayout_8 = QVBoxLayout()
        self.verticalLayout_8.setSpacing(6)
        self.verticalLayout_8.setObjectName(u"verticalLayout_8")
        self.LifeField = QTableWidget(self.centralWidget)
        self.LifeField.setObjectName(u"LifeField")
        sizePolicy1 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.LifeField.sizePolicy().hasHeightForWidth())
        self.LifeField.setSizePolicy(sizePolicy1)
        self.LifeField.setAutoFillBackground(False)
        self.LifeField.setFrameShape(QFrame.NoFrame)
        self.LifeField.setFrameShadow(QFrame.Sunken)
        self.LifeField.setLineWidth(1)
        self.LifeField.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.LifeField.setSelectionMode(QAbstractItemView.NoSelection)
        self.LifeField.setShowGrid(True)
        self.LifeField.setSortingEnabled(False)
        self.LifeField.setWordWrap(True)
        self.LifeField.setCornerButtonEnabled(True)
        self.LifeField.setRowCount(0)
        self.LifeField.setColumnCount(0)
        self.LifeField.horizontalHeader().setVisible(False)
        self.LifeField.horizontalHeader().setDefaultSectionSize(35)
        self.LifeField.verticalHeader().setVisible(False)
        self.LifeField.verticalHeader().setDefaultSectionSize(21)
        self.LifeField.verticalHeader().setHighlightSections(True)
        self.LifeField.verticalHeader().setProperty("showSortIndicator", False)

        self.verticalLayout_8.addWidget(self.LifeField)


        self.horizontalLayout_5.addLayout(self.verticalLayout_8)

        self.line_5 = QFrame(self.centralWidget)
        self.line_5.setObjectName(u"line_5")
        self.line_5.setFrameShape(QFrame.VLine)
        self.line_5.setFrameShadow(QFrame.Sunken)

        self.horizontalLayout_5.addWidget(self.line_5)

        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setSpacing(6)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.verticalLayout_3.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setSpacing(6)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.Cleaner = QPushButton(self.centralWidget)
        self.Cleaner.setObjectName(u"Cleaner")

        self.verticalLayout_2.addWidget(self.Cleaner)


        self.verticalLayout_3.addLayout(self.verticalLayout_2)


        self.horizontalLayout_5.addLayout(self.verticalLayout_3)


        self.gridLayout.addLayout(self.horizontalLayout_5, 1, 0, 1, 1)

        self.line_6 = QFrame(self.centralWidget)
        self.line_6.setObjectName(u"line_6")
        self.line_6.setFrameShape(QFrame.HLine)
        self.line_6.setFrameShadow(QFrame.Sunken)

        self.gridLayout.addWidget(self.line_6, 0, 0, 1, 1)

        MainWindow.setCentralWidget(self.centralWidget)
        self.menuBar = QMenuBar(MainWindow)
        self.menuBar.setObjectName(u"menuBar")
        self.menuBar.setGeometry(QRect(0, 0, 1113, 20))
        self.menuNarz_dzia = QMenu(self.menuBar)
        self.menuNarz_dzia.setObjectName(u"menuNarz_dzia")
        MainWindow.setMenuBar(self.menuBar)
        self.statusBar = QStatusBar(MainWindow)
        self.statusBar.setObjectName(u"statusBar")
        MainWindow.setStatusBar(self.statusBar)

        self.menuBar.addAction(self.menuNarz_dzia.menuAction())
        self.menuNarz_dzia.addAction(self.actionOd_wie)
        self.menuNarz_dzia.addAction(self.actionKolor_ywych_kom_rek)
        self.menuNarz_dzia.addAction(self.actionKo_lor_martwych_kom_rek)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"LCD Simulator", None))
        self.actionWczytaj_jako.setText(QCoreApplication.translate("MainWindow", u"Wczyt&aj jako...", None))
#if QT_CONFIG(shortcut)
        self.actionWczytaj_jako.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+Shift+O", None))
#endif // QT_CONFIG(shortcut)
        self.action_Zapisz.setText(QCoreApplication.translate("MainWindow", u"&Zapisz", None))
#if QT_CONFIG(shortcut)
        self.action_Zapisz.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+S", None))
#endif // QT_CONFIG(shortcut)
        self.actionZapisz_jako.setText(QCoreApplication.translate("MainWindow", u"Zapi&sz jako...", None))
#if QT_CONFIG(shortcut)
        self.actionZapisz_jako.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+Shift+S", None))
#endif // QT_CONFIG(shortcut)
        self.actionWczytaj.setText(QCoreApplication.translate("MainWindow", u"&Wczytaj", None))
#if QT_CONFIG(shortcut)
        self.actionWczytaj.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+O", None))
#endif // QT_CONFIG(shortcut)
        self.action_Nowy.setText(QCoreApplication.translate("MainWindow", u"&Nowy", None))
#if QT_CONFIG(shortcut)
        self.action_Nowy.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+N", None))
#endif // QT_CONFIG(shortcut)
        self.actionOd_wie.setText(QCoreApplication.translate("MainWindow", u"Od\u015bwie\u017c", None))
#if QT_CONFIG(shortcut)
        self.actionOd_wie.setShortcut(QCoreApplication.translate("MainWindow", u"F5", None))
#endif // QT_CONFIG(shortcut)
        self.actionKolor_ywych_kom_rek.setText(QCoreApplication.translate("MainWindow", u"&Kolor \u017cywych kom\u00f3rek", None))
#if QT_CONFIG(shortcut)
        self.actionKolor_ywych_kom_rek.setShortcut(QCoreApplication.translate("MainWindow", u"[", None))
#endif // QT_CONFIG(shortcut)
        self.actionKo_lor_martwych_kom_rek.setText(QCoreApplication.translate("MainWindow", u"Ko&lor martwych kom\u00f3rek", None))
#if QT_CONFIG(shortcut)
        self.actionKo_lor_martwych_kom_rek.setShortcut(QCoreApplication.translate("MainWindow", u"]", None))
#endif // QT_CONFIG(shortcut)
        self.actionO_programie.setText(QCoreApplication.translate("MainWindow", u"O &programie", None))
#if QT_CONFIG(shortcut)
        self.actionO_programie.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+H", None))
#endif // QT_CONFIG(shortcut)
        self.action_Ustawienia_zasad.setText(QCoreApplication.translate("MainWindow", u"&Ustawienia zasad", None))
#if QT_CONFIG(shortcut)
        self.action_Ustawienia_zasad.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+U", None))
#endif // QT_CONFIG(shortcut)
        self.Cleaner.setText(QCoreApplication.translate("MainWindow", u"Wyczy\u015b\u0107", None))
#if QT_CONFIG(shortcut)
        self.Cleaner.setShortcut(QCoreApplication.translate("MainWindow", u"W", None))
#endif // QT_CONFIG(shortcut)
        self.menuNarz_dzia.setTitle(QCoreApplication.translate("MainWindow", u"&Narz\u0119dzia", None))
    # retranslateUi

