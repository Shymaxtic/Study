# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '.\ReleaseSupportTool.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(803, 621)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout(self.centralwidget)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.m_cbbPhase = QtWidgets.QComboBox(self.centralwidget)
        self.m_cbbPhase.setObjectName("m_cbbPhase")
        self.m_cbbPhase.addItem("")
        self.m_cbbPhase.addItem("")
        self.m_cbbPhase.addItem("")
        self.verticalLayout_2.addWidget(self.m_cbbPhase)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.m_btnMakeRelease = QtWidgets.QPushButton(self.centralwidget)
        self.m_btnMakeRelease.setObjectName("m_btnMakeRelease")
        self.horizontalLayout_3.addWidget(self.m_btnMakeRelease)
        self.m_btnOpenLogFile = QtWidgets.QPushButton(self.centralwidget)
        self.m_btnOpenLogFile.setObjectName("m_btnOpenLogFile")
        self.horizontalLayout_3.addWidget(self.m_btnOpenLogFile)
        self.verticalLayout_2.addLayout(self.horizontalLayout_3)
        spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_2.addItem(spacerItem)
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.lineEdit = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit.setObjectName("lineEdit")
        self.horizontalLayout.addWidget(self.lineEdit)
        self.m_btnSvnFolder = QtWidgets.QPushButton(self.centralwidget)
        self.m_btnSvnFolder.setObjectName("m_btnSvnFolder")
        self.horizontalLayout.addWidget(self.m_btnSvnFolder)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.lineEdit_2 = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_2.setText("")
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.horizontalLayout_2.addWidget(self.lineEdit_2)
        self.m_btnGetReleaseInfo = QtWidgets.QPushButton(self.centralwidget)
        self.m_btnGetReleaseInfo.setObjectName("m_btnGetReleaseInfo")
        self.horizontalLayout_2.addWidget(self.m_btnGetReleaseInfo)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        self.verticalLayout_2.addLayout(self.verticalLayout)
        self.horizontalLayout_4.addLayout(self.verticalLayout_2)
        self.m_lstIssueView = QtWidgets.QListWidget(self.centralwidget)
        self.m_lstIssueView.setObjectName("m_lstIssueView")
        self.horizontalLayout_4.addWidget(self.m_lstIssueView)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 803, 18))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.m_cbbPhase.setItemText(0, _translate("MainWindow", "Trial"))
        self.m_cbbPhase.setItemText(1, _translate("MainWindow", "Phase 01"))
        self.m_cbbPhase.setItemText(2, _translate("MainWindow", "Phase 02"))
        self.m_btnMakeRelease.setText(_translate("MainWindow", "Make Release"))
        self.m_btnOpenLogFile.setText(_translate("MainWindow", "Open Log File"))
        self.m_btnSvnFolder.setText(_translate("MainWindow", "Svn folder"))
        self.m_btnGetReleaseInfo.setText(_translate("MainWindow", "Get Release Info"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
