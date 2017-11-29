#!/usr/bin/env python

from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
import subprocess
import sys
import time

class BenchMark(QWidget):
    """Widget for creating and answering the questions that are needed in the reasoning"""
    def __init__(self, parent = None):
        super(BenchMark, self).__init__(parent)
        
        self.testDataList = [
            [   100000,   110000 ],
            [  1100000,  1110000 ],
            [  1200000,  1210000 ],
            [ 10000000, 10100000 ]
        ]
        
        self.timeTemplate = "Elapsed: {0}"

        self.main_layout = QGridLayout()
        self.setLayout(self.main_layout)

        #
        # Sequential tests
        #
        self.seqTestLabels = []
        self.seqTestResults = []
        
        self.main_layout.addWidget( QLabel("Test range"), 0, 0)
        self.main_layout.addWidget( QLabel("Test results"), 1, 0)
            
        i = 1
        for testData in self.testDataList:
            newlbl = QLabel("{0} - {1}".format(testData[0], testData[1]))
            newres = QLabel(self.timeTemplate.format(""))
            
            self.seqTestLabels.append(newlbl)
            self.seqTestResults.append(newres)
            
            self.main_layout.addWidget(newlbl, 0, i)
            self.main_layout.addWidget(newres, 1, i)
            
            i+=1
        
        # Action Button
        self.seqBtn = QPushButton("Calculate!")
        self.seqBtn.clicked.connect(self.RunSequentialTests)
        self.main_layout.addWidget( self.seqBtn, 0, i)
        
        
        # Separator
        self.main_layout.addWidget( QLabel("----"), 2, 0)
        
        
        #
        # Concurrent tests
        #
        self.conTestLabels = []
        self.conTestResults = []
        
        self.main_layout.addWidget( QLabel("Test number"), 3, 0)
        self.main_layout.addWidget( QLabel("Test results"), 4, 0)
            
        i = 1
        for testData in self.testDataList:
            newlbl = QLabel("Test: {0} - {1}".format(testData[0], testData[1]))
            newres = QLabel(self.timeTemplate.format(""))
            
            self.conTestLabels.append(newlbl)
            self.conTestResults.append(newres)
            
            self.main_layout.addWidget(newlbl, 3, i)
            self.main_layout.addWidget(newres, 4, i)
            
            i+=1
        
        # Action Button
        self.conBtn = QPushButton("Calculate!")
        self.conBtn.clicked.connect(self.RunConcurrentTests)
        self.main_layout.addWidget( self.conBtn, 3, i)
        
        # Separator
        self.main_layout.addWidget( QLabel("----"), 5, 0)
        
        
        #
        # Concurrent tests
        #
        self.parTestLabels = []
        self.parTestResults = []
        
        self.main_layout.addWidget( QLabel("Test number"), 6, 0)
        self.main_layout.addWidget( QLabel("Test results"), 7, 0)
            
        i = 1
        for testData in self.testDataList:
            newlbl = QLabel("Test: {0} - {1}".format(testData[0], testData[1]))
            newres = QLabel(self.timeTemplate.format(""))
            
            self.parTestLabels.append(newlbl)
            self.parTestResults.append(newres)
            
            self.main_layout.addWidget(newlbl, 6, i)
            self.main_layout.addWidget(newres, 7, i)
            
            i+=1
        
        # Action Button
        self.parBtn = QPushButton("Calculate!")
        self.parBtn.clicked.connect(self.RunParallelTests)
        self.main_layout.addWidget( self.parBtn, 6, i)

        
        self.setWindowTitle("Parallel Benchmark")
        self.show()
        
    def RunSequentialTests(self):
        i = 0
        for testData in self.testDataList:
            # Get time of process
            start_time = time.time()
            subprocess.run(["../bin/seq", str(testData[0]), str(testData[1]) ] )
            end_time = time.time()
            
            self.seqTestResults[i].setText( self.timeTemplate.format( end_time - start_time ) )
            
            i+=1
    
    def RunConcurrentTests(self):
        i = 0
        for testData in self.testDataList:
            # Get time of process
            start_time = time.time()
            subprocess.run(["../bin/concurrent", str(testData[0]), str(testData[1]) ] )
            end_time = time.time()
            
            self.conTestResults[i].setText( self.timeTemplate.format( end_time - start_time ) )
            
            i+=1
    
    def RunParallelTests(self):
        i = 0
        for testData in self.testDataList:
            # Get time of process
            start_time = time.time()
            subprocess.run(["../bin/client", str(testData[0]), str(testData[1]) ] )
            end_time = time.time()
            
            self.parTestResults[i].setText( self.timeTemplate.format( end_time - start_time ) )
            
            i+=1

app = QApplication(sys.argv)
obj = BenchMark()
obj.show()
sys.exit(app.exec_()) 
