#-------------------------------------------------------------------------------
# Name:        модуль1
# Purpose:
#
# Author:      marmyshev_d
#
# Created:     17.09.2013
# Copyright:   (c) marmyshev_d 2013
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/python
# -*- coding: utf-8 -*-

"""
ZetCode PyQt4 tutorial

In this example, we create a simple
window in PyQt4.

author: Jan Bodnar
website: zetcode.com
last edited: October 2011
"""

import sys
from PyQt4 import QtCore, QtGui

class TrayNotificationWidget(QtGui.QWidget):

    def __init__(self):
        super(TrayNotificationWidget, self).__init__()

        self.initUI()

    def initUI(self):

        self.setGeometry(300, 300, 250, 150)
        window_flags = QtCore.Qt.FramelessWindowHint | QtCore.Qt.Window
        self.setWindowFlags(window_flags)
##        self.setWindowTitle('Icon')
##        self.setWindowIcon(QtGui.QIcon('web.png'))
        QtGui.QToolTip.setFont(QtGui.QFont('SansSerif', 10))

        self.setToolTip('This is a <b>QWidget</b> widget')

        btn = QtGui.QPushButton('Button', self)
        btn.setToolTip('This is a <b>QPushButton</b> widget')
        btn.resize(btn.sizeHint())
        btn.move(50, 50)

        cb = QtGui.QCheckBox('Set transparency', self)
        cb.move(20, 20)
        cb.toggle()
        cb.stateChanged.connect(self.changeTransparency)

        self.show()

    def changeTransparency(self, state):

        if state == QtCore.Qt.Checked:
            self.set_transparency(True)
        else:
            self.set_transparency(False)

    def set_transparency(self, enabled):
        """
        Set the transparency of the window
        """
        if enabled:
            self.setAutoFillBackground(False)
        else:
            self.setAttribute(QtCore.Qt.WA_NoSystemBackground, False)
        self.setAttribute(QtCore.Qt.WA_TranslucentBackground, enabled)
        self.repaint()

def main():

    app = QtGui.QApplication(sys.argv)

    w = TrayNotificationWidget()
    w.set_transparency(False)
##    w.resize(250, 150)
##    w.setWindowTitle('Simple')
##    w.move(300, 300)
##
##    w.show()

    sys.exit(app.exec_())


if __name__ == '__main__':
    main()



