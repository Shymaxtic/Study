D_LOG_FILE = "IssueLog.txt"

class ReleaseManager:
    def __init__(self):
        self.mSvnPath = ""
        self.mInprogressPath = ""
        self.mReleasePath = ""
        self.mReleaseStuffs = []
        self.mLogData = {}
        pass

    def UpdateSVNFolder(self, svnFolder: str):
        #TODO: update mInprogressPath, mReleasePath
        pass
    
    def UpdateInprogressPath(self, phase:str):
        #TODO: update mInprogressPath
        pass

    def LoadConfig(self):
        #TODO: load xml config file 
        pass

    def LoadReleaseInfo(self, file:str):
        # TODO: read release file to get self.mReleaseStuffs
        errorMsg = ""
        return errorMsg

    def CheckRequiredData(self):
        for testSpecMng in self.mReleaseStuffs:
            errorMsg = testSpecMng.CheckRequiredData()
            # if has error. prepare for log file
            if errorMsg:
                if testSpecMng.mPIC not in self.mLogData:
                    self.mLogData[testSpecMng.mPIC] = {}
                if testSpecMng.mId not in self.mLogData[testSpecMng.mPIC]:
                    self.mLogData[testSpecMng.mPIC][testSpecMng.mId] = []
                self.mLogData[testSpecMng.mPIC][testSpecMng.mId] += errorMsg

    def CheckCorrectFormat(self):
        for testSpecMng in self.mReleaseStuffs:
            errorMsg = testSpecMng.CheckCorrectFormat()
            # if has error. prepare for log file
            if errorMsg:
                if testSpecMng.mPIC not in self.mLogData:
                    self.mLogData[testSpecMng.mPIC] = {}
                if testSpecMng.mId not in self.mLogData[testSpecMng.mPIC]:
                    self.mLogData[testSpecMng.mPIC][testSpecMng.mId] = []
                self.mLogData[testSpecMng.mPIC][testSpecMng.mId] += errorMsg

    def CheckExistence(self):
        for testSpecMng in self.mReleaseStuffs:
            errorMsg = testSpecMng.CheckExistence()
            # if has error. prepare for log file
            if errorMsg:
                if testSpecMng.mPIC not in self.mLogData:
                    self.mLogData[testSpecMng.mPIC] = {}
                if testSpecMng.mId not in self.mLogData[testSpecMng.mPIC]:
                    self.mLogData[testSpecMng.mPIC][testSpecMng.mId] = []
                self.mLogData[testSpecMng.mPIC][testSpecMng.mId] += errorMsg

    def CopyStuff(self):
        errorMsg = ""
        return errorMsg

    def LogFile(self):
        errorMsg = ""
        with open(D_LOG_FILE, 'w+') as logfile:
            for pic in self.mLogData:
                logfile.write(pic+'\n')
                for funcId in self.mLogData[pic]:
                    logfile.write('\t- ' + funcId + '\n')
                    for content in self.mLogData[pic][funcId]:
                        logfile.write('\t\t- ' + content + '\n')
        return errorMsg

    def MakeRelease(self, releaseDir:str):
        """TODO:
        1. Clean log data.
        2. Check existence.
        3. Check required data.
        4. Check format.        
        5. Copy stuff or log file.
        """
        self.mLogData = {}
        self.CheckExistence()
        self.CheckRequiredData()
        self.CheckCorrectFormat()
        errorMsg = ""
        #NOTE: dummy for test
        self.mLogData["Peter"] = {}
        self.mLogData['Alley'] = {}
        self.mLogData['Peter']['001'] = ['hello']
        self.mLogData['Peter']['002'] = ['hello']
        self.mLogData['Alley']['003'] = ['hello']
        if self.mLogData:
            self.LogFile()
            errorMsg = "[ERROR] Problem when make release. See log file"
        else:
            errorMsg = self.CopyStuff()
        return errorMsg