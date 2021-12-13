# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'testable_form_widget_ui.ui'
##
## Created by: Qt User Interface Compiler version 6.1.3
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import *  # type: ignore
from PySide6.QtGui import *  # type: ignore
from PySide6.QtWidgets import *  # type: ignore


class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(726, 588)
        self.LifeField = QTableWidget(Form)
        self.LifeField.setObjectName(u"LifeField")
        self.LifeField.setGeometry(QRect(130, 60, 301, 261))
        sizePolicy = QSizePolicy(QSizePolicy.Maximum, QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.LifeField.sizePolicy().hasHeightForWidth())
        self.LifeField.setSizePolicy(sizePolicy)
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

        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
    # retranslateUi

