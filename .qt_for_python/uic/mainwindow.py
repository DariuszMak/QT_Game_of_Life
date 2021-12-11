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
        self.horizontalLayout_10 = QHBoxLayout()
        self.horizontalLayout_10.setSpacing(6)
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.horizontalLayout_8 = QHBoxLayout()
        self.horizontalLayout_8.setSpacing(6)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.label_7 = QLabel(self.centralWidget)
        self.label_7.setObjectName(u"label_7")
        self.label_7.setMinimumSize(QSize(145, 27))
        self.label_7.setMaximumSize(QSize(145, 27))

        self.horizontalLayout_8.addWidget(self.label_7)

        self.ProjWidth = QSpinBox(self.centralWidget)
        self.ProjWidth.setObjectName(u"ProjWidth")
        self.ProjWidth.setMinimumSize(QSize(100, 27))
        self.ProjWidth.setMaximumSize(QSize(100, 27))
        self.ProjWidth.setMaximum(3840)
        self.ProjWidth.setValue(0)

        self.horizontalLayout_8.addWidget(self.ProjWidth)


        self.horizontalLayout_10.addLayout(self.horizontalLayout_8)

        self.line_10 = QFrame(self.centralWidget)
        self.line_10.setObjectName(u"line_10")
        self.line_10.setFrameShape(QFrame.VLine)
        self.line_10.setFrameShadow(QFrame.Sunken)

        self.horizontalLayout_10.addWidget(self.line_10)

        self.horizontalLayout_9 = QHBoxLayout()
        self.horizontalLayout_9.setSpacing(6)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.label_8 = QLabel(self.centralWidget)
        self.label_8.setObjectName(u"label_8")
        self.label_8.setMinimumSize(QSize(145, 27))
        self.label_8.setMaximumSize(QSize(145, 27))

        self.horizontalLayout_9.addWidget(self.label_8)

        self.ProjHeight = QSpinBox(self.centralWidget)
        self.ProjHeight.setObjectName(u"ProjHeight")
        self.ProjHeight.setMinimumSize(QSize(100, 0))
        self.ProjHeight.setMaximumSize(QSize(100, 27))
        self.ProjHeight.setMaximum(2160)
        self.ProjHeight.setValue(0)

        self.horizontalLayout_9.addWidget(self.ProjHeight)


        self.horizontalLayout_10.addLayout(self.horizontalLayout_9)

        self.line_11 = QFrame(self.centralWidget)
        self.line_11.setObjectName(u"line_11")
        self.line_11.setFrameShape(QFrame.VLine)
        self.line_11.setFrameShadow(QFrame.Sunken)

        self.horizontalLayout_10.addWidget(self.line_11)

        self.MaxSize = QCheckBox(self.centralWidget)
        self.MaxSize.setObjectName(u"MaxSize")
        self.MaxSize.setMinimumSize(QSize(184, 27))
        self.MaxSize.setMaximumSize(QSize(202, 27))
        self.MaxSize.setChecked(True)

        self.horizontalLayout_10.addWidget(self.MaxSize)

        self.horizontalSpacer_3 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_10.addItem(self.horizontalSpacer_3)


        self.verticalLayout_8.addLayout(self.horizontalLayout_10)

        self.line = QFrame(self.centralWidget)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.HLine)
        self.line.setFrameShadow(QFrame.Sunken)

        self.verticalLayout_8.addWidget(self.line)

        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setSpacing(6)
        self.verticalLayout.setObjectName(u"verticalLayout")

        self.verticalLayout_8.addLayout(self.verticalLayout)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setSpacing(6)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.SetWholeScreen = QCheckBox(self.centralWidget)
        self.SetWholeScreen.setObjectName(u"SetWholeScreen")
        sizePolicy1 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.SetWholeScreen.sizePolicy().hasHeightForWidth())
        self.SetWholeScreen.setSizePolicy(sizePolicy1)
        self.SetWholeScreen.setMinimumSize(QSize(205, 27))
        self.SetWholeScreen.setMaximumSize(QSize(150, 27))
        self.SetWholeScreen.setChecked(False)
        self.SetWholeScreen.setAutoRepeat(False)
        self.SetWholeScreen.setAutoExclusive(False)

        self.horizontalLayout_2.addWidget(self.SetWholeScreen)

        self.line_7 = QFrame(self.centralWidget)
        self.line_7.setObjectName(u"line_7")
        self.line_7.setFrameShape(QFrame.VLine)
        self.line_7.setFrameShadow(QFrame.Sunken)

        self.horizontalLayout_2.addWidget(self.line_7)

        self.label = QLabel(self.centralWidget)
        self.label.setObjectName(u"label")
        self.label.setMinimumSize(QSize(116, 27))
        self.label.setMaximumSize(QSize(116, 27))

        self.horizontalLayout_2.addWidget(self.label)

        self.ColumnChanger = QSpinBox(self.centralWidget)
        self.ColumnChanger.setObjectName(u"ColumnChanger")
        self.ColumnChanger.setMinimumSize(QSize(70, 27))
        self.ColumnChanger.setMaximumSize(QSize(70, 27))
        self.ColumnChanger.setMinimum(1)
        self.ColumnChanger.setMaximum(300)
        self.ColumnChanger.setValue(1)

        self.horizontalLayout_2.addWidget(self.ColumnChanger)

        self.line_8 = QFrame(self.centralWidget)
        self.line_8.setObjectName(u"line_8")
        self.line_8.setFrameShape(QFrame.VLine)
        self.line_8.setFrameShadow(QFrame.Sunken)

        self.horizontalLayout_2.addWidget(self.line_8)

        self.label_2 = QLabel(self.centralWidget)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setMinimumSize(QSize(116, 27))
        self.label_2.setMaximumSize(QSize(116, 27))

        self.horizontalLayout_2.addWidget(self.label_2)

        self.RowChanger = QSpinBox(self.centralWidget)
        self.RowChanger.setObjectName(u"RowChanger")
        self.RowChanger.setMinimumSize(QSize(70, 27))
        self.RowChanger.setMaximumSize(QSize(70, 27))
        self.RowChanger.setMinimum(1)
        self.RowChanger.setMaximum(150)
        self.RowChanger.setValue(1)

        self.horizontalLayout_2.addWidget(self.RowChanger)

        self.line_9 = QFrame(self.centralWidget)
        self.line_9.setObjectName(u"line_9")
        self.line_9.setFrameShape(QFrame.VLine)
        self.line_9.setFrameShadow(QFrame.Sunken)

        self.horizontalLayout_2.addWidget(self.line_9)

        self.label_5 = QLabel(self.centralWidget)
        self.label_5.setObjectName(u"label_5")
        self.label_5.setMaximumSize(QSize(65, 16777215))
        self.label_5.setWordWrap(False)

        self.horizontalLayout_2.addWidget(self.label_5)

        self.SizeFieldLcd = QLCDNumber(self.centralWidget)
        self.SizeFieldLcd.setObjectName(u"SizeFieldLcd")
        self.SizeFieldLcd.setMinimumSize(QSize(98, 27))
        self.SizeFieldLcd.setMaximumSize(QSize(98, 27))
        self.SizeFieldLcd.setDigitCount(7)
        self.SizeFieldLcd.setSegmentStyle(QLCDNumber.Flat)

        self.horizontalLayout_2.addWidget(self.SizeFieldLcd)

        self.horizontalSpacer_4 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_2.addItem(self.horizontalSpacer_4)


        self.verticalLayout_8.addLayout(self.horizontalLayout_2)

        self.SizeFieldSlider = QSlider(self.centralWidget)
        self.SizeFieldSlider.setObjectName(u"SizeFieldSlider")
        self.SizeFieldSlider.setMinimumSize(QSize(0, 29))
        self.SizeFieldSlider.setMaximumSize(QSize(16777215, 29))
        self.SizeFieldSlider.setMinimum(3)
        self.SizeFieldSlider.setMaximum(10)
        self.SizeFieldSlider.setValue(10)
        self.SizeFieldSlider.setSliderPosition(10)
        self.SizeFieldSlider.setOrientation(Qt.Horizontal)

        self.verticalLayout_8.addWidget(self.SizeFieldSlider)

        self.line_4 = QFrame(self.centralWidget)
        self.line_4.setObjectName(u"line_4")
        self.line_4.setFrameShape(QFrame.HLine)
        self.line_4.setFrameShadow(QFrame.Sunken)

        self.verticalLayout_8.addWidget(self.line_4)

        self.horizontalLayout_11 = QHBoxLayout()
        self.horizontalLayout_11.setSpacing(6)
        self.horizontalLayout_11.setObjectName(u"horizontalLayout_11")
        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_11.addItem(self.horizontalSpacer_2)

        self.verticalLayout_4 = QVBoxLayout()
        self.verticalLayout_4.setSpacing(6)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_4.addItem(self.verticalSpacer)

        self.stackedWidget = QStackedWidget(self.centralWidget)
        self.stackedWidget.setObjectName(u"stackedWidget")
        sizePolicy2 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.stackedWidget.sizePolicy().hasHeightForWidth())
        self.stackedWidget.setSizePolicy(sizePolicy2)
        self.stackedWidget.setMaximumSize(QSize(16777215, 16777215))
        self.stackedWidget.setFrameShape(QFrame.Box)
        self.stackedWidget.setLineWidth(3)
        self.Page = QWidget()
        self.Page.setObjectName(u"Page")
        sizePolicy1.setHeightForWidth(self.Page.sizePolicy().hasHeightForWidth())
        self.Page.setSizePolicy(sizePolicy1)
        self.LifeField = QTableWidget(self.Page)
        self.LifeField.setObjectName(u"LifeField")
        self.LifeField.setGeometry(QRect(-60, -140, 256, 509))
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
        self.LifeField.horizontalHeader().setDefaultSectionSize(31)
        self.LifeField.verticalHeader().setVisible(False)
        self.LifeField.verticalHeader().setDefaultSectionSize(17)
        self.LifeField.verticalHeader().setHighlightSections(True)
        self.LifeField.verticalHeader().setProperty("showSortIndicator", False)
        self.stackedWidget.addWidget(self.Page)

        self.verticalLayout_4.addWidget(self.stackedWidget)

        self.verticalSpacer_3 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_4.addItem(self.verticalSpacer_3)


        self.horizontalLayout_11.addLayout(self.verticalLayout_4)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_11.addItem(self.horizontalSpacer)


        self.verticalLayout_8.addLayout(self.horizontalLayout_11)


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

        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_2.addItem(self.verticalSpacer_2)


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
        QWidget.setTabOrder(self.ProjWidth, self.ProjHeight)
        QWidget.setTabOrder(self.ProjHeight, self.MaxSize)

        self.menuBar.addAction(self.menuNarz_dzia.menuAction())
        self.menuNarz_dzia.addAction(self.actionOd_wie)
        self.menuNarz_dzia.addAction(self.actionKolor_ywych_kom_rek)
        self.menuNarz_dzia.addAction(self.actionKo_lor_martwych_kom_rek)

        self.retranslateUi(MainWindow)

        self.stackedWidget.setCurrentIndex(0)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Gra w \u017cycie - Dariusz Makarewicz", None))
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
        self.label_7.setText(QCoreApplication.translate("MainWindow", u"Szeroko\u015b\u0107 ramki (px):", None))
        self.label_8.setText(QCoreApplication.translate("MainWindow", u"Wysoko\u015b\u0107 ramki (px):", None))
        self.MaxSize.setText(QCoreApplication.translate("MainWindow", u"Automatyczny rozmiar ", None))
#if QT_CONFIG(shortcut)
        self.MaxSize.setShortcut(QCoreApplication.translate("MainWindow", u"M", None))
#endif // QT_CONFIG(shortcut)
        self.SetWholeScreen.setText(QCoreApplication.translate("MainWindow", u"Zmiana atrybut\u00f3w tabeli", None))
#if QT_CONFIG(shortcut)
        self.SetWholeScreen.setShortcut(QCoreApplication.translate("MainWindow", u"R", None))
#endif // QT_CONFIG(shortcut)
        self.label.setText(QCoreApplication.translate("MainWindow", u"Kolumn: [1 - 300]", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"Wierszy: [1 - 150]", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"Rozmiar:", None))
        self.Cleaner.setText(QCoreApplication.translate("MainWindow", u"Wyczy\u015b\u0107", None))
#if QT_CONFIG(shortcut)
        self.Cleaner.setShortcut(QCoreApplication.translate("MainWindow", u"W", None))
#endif // QT_CONFIG(shortcut)
        self.menuNarz_dzia.setTitle(QCoreApplication.translate("MainWindow", u"&Narz\u0119dzia", None))
    # retranslateUi

