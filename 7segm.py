import sys
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QMainWindow, QLabel, QGridLayout, QWidget, QTextEdit
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtCore import QSize    

class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        self.stato_bottoni = [0,0,0,0,0,0,0,0]

        self.setMinimumSize(QSize(300, 200))    
        self.setWindowTitle("PyQt 7 segm test")

        self.pybutton1 = QPushButton('1', self)
        self.pybutton1.clicked.connect(self.clickMethod1)
        self.pybutton1.resize(20,100)
        self.pybutton1.move(140, 30)

        self.pybutton2 = QPushButton('2', self)
        self.pybutton2.clicked.connect(self.clickMethod2)
        self.pybutton2.resize(100,20)
        self.pybutton2.move(30, 0)

        self.pybutton3 = QPushButton('3', self)
        self.pybutton3.clicked.connect(self.clickMethod3)
        self.pybutton3.resize(100,20)
        self.pybutton3.move(30, 280)

        self.pybutton4 = QPushButton('4', self)
        self.pybutton4.clicked.connect(self.clickMethod4)
        self.pybutton4.resize(20,100)
        self.pybutton4.move(140, 170)

        self.pybutton5 = QPushButton('5', self)
        self.pybutton5.clicked.connect(self.clickMethod5)
        self.pybutton5.resize(20,100)
        self.pybutton5.move(0, 30)

        self.pybutton6 = QPushButton('6', self)
        self.pybutton6.clicked.connect(self.clickMethod6)
        self.pybutton6.resize(20,100)
        self.pybutton6.move(0, 170)

        self.pybutton7 = QPushButton('7', self)
        self.pybutton7.clicked.connect(self.clickMethod7)
        self.pybutton7.resize(100,20)
        self.pybutton7.move(30, 140)

        self.pybuttonOK = QPushButton('OK', self)
        self.pybuttonOK.clicked.connect(self.clickMethodOK)
        self.pybuttonOK.resize(100,20)
        self.pybuttonOK.move(180, 60)

        self.labelBIN = QTextEdit('Bin', self)
        #self.label.setStyleSheet("border: 1px solid black;")
        #self.label.resize(100,20)
        self.labelBIN.move(180, 120)

        self.labelHEX = QTextEdit('Hex', self)
        #self.label.setStyleSheet("border: 1px solid black;")
        #self.label.resize(100,20)
        self.labelHEX.move(180, 160)

        self.labelDEC = QTextEdit('Dex', self)
        #self.label.setStyleSheet("border: 1px solid black;")
        #self.label.resize(100,20)
        self.labelDEC.move(180, 200)

    def clickMethod1(self):

        self.stato_bottoni[0] = (self.stato_bottoni[0]* -1) +1
        if self.stato_bottoni[0]:
            self.pybutton1.setStyleSheet("background-color: black");
        else:
            self.pybutton1.setStyleSheet("background-color: white");
    def clickMethod2(self):

        self.stato_bottoni[1] = (self.stato_bottoni[1]* -1) +1
        if self.stato_bottoni[1]:
            self.pybutton2.setStyleSheet("background-color: black");
        else:
            self.pybutton2.setStyleSheet("background-color: white");
    def clickMethod3(self):

        self.stato_bottoni[2] = (self.stato_bottoni[2]* -1) +1
        if self.stato_bottoni[2]:
            self.pybutton3.setStyleSheet("background-color: black");
        else:
            self.pybutton3.setStyleSheet("background-color: white");
    def clickMethod4(self):

        self.stato_bottoni[3] = (self.stato_bottoni[3]* -1) +1
        if self.stato_bottoni[3]:
            self.pybutton4.setStyleSheet("background-color: black");
        else:
            self.pybutton4.setStyleSheet("background-color: white");
    def clickMethod5(self):

        self.stato_bottoni[4] = (self.stato_bottoni[4]* -1) +1
        if self.stato_bottoni[4]:
            self.pybutton5.setStyleSheet("background-color: black");
        else:
            self.pybutton5.setStyleSheet("background-color: white");
    def clickMethod6(self):

        self.stato_bottoni[5] = (self.stato_bottoni[5]* -1) +1
        if self.stato_bottoni[5]:
            self.pybutton6.setStyleSheet("background-color: black");
        else:
            self.pybutton6.setStyleSheet("background-color: white");
    def clickMethod7(self):

        self.stato_bottoni[6] = (self.stato_bottoni[6]* -1) +1
        if self.stato_bottoni[6]:
            self.pybutton7.setStyleSheet("background-color: black");
        else:
            self.pybutton7.setStyleSheet("background-color: white");

    def clickMethodOK(self):
        #print(self.stato_bottoni)
        val = ""
        for i in range(0,len(self.stato_bottoni)):
            val += str(self.stato_bottoni[7-i])
        self.labelBIN.setText("B"+val)
        self.labelDEC.setText(str(int(val, 2)))
        #self.labelHEX.setText("{0:0>2X}".format(int(val, 2)))
        self.labelHEX.setText("0x{0:0>2X}".format(int(val, 2)))

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    mainWin = MainWindow()
    mainWin.show()
    sys.exit( app.exec_() )
