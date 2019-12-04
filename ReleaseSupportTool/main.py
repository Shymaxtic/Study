from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QFileDialog, QMessageBox  
from ReleaseSupportToolGUI import Ui_MainWindow
import sys
from ReleaseManager import ReleaseManager

class ApplicationWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(ApplicationWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.SetupConnection()
        self.mReleaseMng = ReleaseManager()

    def SetupConnection(self):
        self.ui.m_btnSvnFolder.clicked.connect(self.SlotGetSvnFolder)
        self.ui.m_btnGetReleaseInfo.clicked.connect(self.SlotGetReleaseInfo)
        self.ui.m_btnMakeRelease.clicked.connect(self.SlotMakeRelease)
        self.ui.m_btnOpenLogFile.clicked.connect(self.SlotOpenLogFile)
        self.ui.m_cbbPhase.currentTextChanged.connect(self.SlotPhaseChanged)

    def SlotGetSvnFolder(self):
        svnDir = str(QFileDialog.getExistingDirectory(self, "Select Release Directory"))
        self.mReleaseMng.UpdateSVNFolder(svnDir)

    def SlotGetReleaseInfo(self):
        #TODO: init default file
        releaseFile = QFileDialog.getOpenFileName(self, 'Select release file', 'c:\\',"Excel file (*.xlsx)")
        print(releaseFile)

    def SlotMakeRelease(self):
        #TODO: init defaut dir
        releaseDir = str(QFileDialog.getExistingDirectory(self, "Select Release Directory"))
        print(releaseDir)
        errorMsg = self.mReleaseMng.MakeRelease(releaseDir)
        if errorMsg:
            QMessageBox.warning(self, "Issue", errorMsg)
            self.DrawIssueView()

    def SlotOpenLogFile(self):
        print("Open log file")

    def SlotPhaseChanged(self):
        phase = self.ui.m_cbbPhase.currentText()
        self.mReleaseMng.UpdateInprogressPath(phase)

    def DrawIssueView(self):
        # Clear current issure view.
        self.ui.m_lstIssueView.clear()
        for pic in self.mReleaseMng.mLogData:
            for funcId in self.mReleaseMng.mLogData[pic]:
                self.ui.m_lstIssueView.addItem(str(funcId))


def main():
    app = QtWidgets.QApplication(sys.argv)
    application = ApplicationWindow()
    application.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()