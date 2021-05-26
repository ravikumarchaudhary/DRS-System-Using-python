import tkinter 
import cv2 # pip install opencv-python
import PIL.Image, PIL.ImageTk # pip install pillow
from functools import partial
import threading
import time
import imutils # pip install imutils
from tkinter import*
from tkinter.ttk import*
import numpy as np

SET_WIDTH = 1100
SET_HEIGHT = 830

stream = cv2.VideoCapture("My video six.mp4")
flag = True
def play(speed):
    global flag
    print(f"You clicked on play. Speed is {speed}")
    # Play the video in reverse mode
    frame1 = stream.get(cv2.CAP_PROP_POS_FRAMES)
    stream.set(cv2.CAP_PROP_POS_FRAMES, frame1 + speed)
    grabbed, frame = stream.read()
    if not grabbed:
        exit()
    frame = imutils.resize(frame, width=SET_WIDTH, height=SET_HEIGHT)
    frame = PIL.ImageTk.PhotoImage(image = PIL.Image.fromarray(frame))
    canvas.image = frame
    canvas.create_image(0,0, image=frame, anchor=tkinter.NW)
    if flag:
        canvas.create_text(134, 26, fill="black", font="Times 26 bold", text="Decision Pending")
    flag = not flag

def dec():
    stream = cv2.VideoCapture('tree.mp4')
    if (stream.isOpened()== False):
        print("Error")
    while(stream.isOpened()):
        ret, frame = stream.read()
        if ret == True:
            cv2.imshow('Frame', frame)
            if cv2.waitKey(25) & 0xFF == ord('q'):
                break
        else:
            break
    stream.release()
    cv2.destroyAllWindows()

def pending(decision):
    # 1. Display decision pending image
    frame = cv2.cvtColor(cv2.imread("CricketGround1234.png"), cv2.COLOR_BGR2RGB)
    frame = imutils.resize(frame, width=SET_WIDTH, height=SET_HEIGHT)
    frame = PIL.ImageTk.PhotoImage(image=PIL.Image.fromarray(frame))
    canvas.image = frame
    canvas.create_image(0,0, image=frame, anchor=tkinter.NW)
    # 2. Wait for 1 second
    time.sleep(1.5)

    # 3. Display sponsor image
    frame = cv2.cvtColor(cv2.imread("decison_pending_final.png"), cv2.COLOR_BGR2RGB)
    frame = imutils.resize(frame, width=SET_WIDTH, height=SET_HEIGHT)
    frame = PIL.ImageTk.PhotoImage(image=PIL.Image.fromarray(frame))
    canvas.image = frame
    canvas.create_image(0,0, image=frame, anchor=tkinter.NW)

    # 4. Wait for 1.5 second
    time.sleep(2.5)
    # 5. Display out/notout image
    if decision == 'out':
        dec()
        decisionImg = "Out_final.png"
    else:
        dec()
        decisionImg = "Not_out_final.png"
    frame = cv2.cvtColor(cv2.imread(decisionImg), cv2.COLOR_BGR2RGB)
    frame = imutils.resize(frame, width=SET_WIDTH, height=SET_HEIGHT)
    frame = PIL.ImageTk.PhotoImage(image=PIL.Image.fromarray(frame))
    canvas.image = frame
    canvas.create_image(0,0, image=frame, anchor=tkinter.NW)

def out():
    thread = threading.Thread(target=pending, args=("out",))
    thread.daemon = 1
    thread.start()
    print("Player is out")

def not_out():
    thread = threading.Thread(target=pending, args=("not out",))
    thread.daemon = 1
    thread.start()
    print("Player is not out")

# Tkinter gui starts here
window = tkinter.Tk()
window.title("DRS System by Ravi Kumar")
cv_img = cv2.cvtColor(cv2.imread("CricketGround123456.png"), cv2.COLOR_BGR2RGB)
canvas = tkinter.Canvas(window, width=SET_WIDTH, height=SET_HEIGHT)
photo = PIL.ImageTk.PhotoImage(image=PIL.Image.fromarray(cv_img))
image_on_canvas = canvas.create_image(0, 0, ancho=tkinter.NW, image=photo)
canvas.pack()

btn = tkinter.Button(window, text="<<Prev (fast)",font = ('calibri',20,'bold'),background='black', foreground = 'red',height=2,width=15,command=partial (play,-25))
btn.place(x=0, y=716)
#btn.pack()

btn = tkinter.Button(window, text="<<Prev (slow)",font = ('calibri',20,'bold'),background='blue', foreground = 'black',height=2,width=15,command=partial (play,-2))
btn.place(x=0, y=610)
#btn.pack()

btn = tkinter.Button(window, text="Next (slow)>>",font = ('calibri',20,'bold'),background='light green', foreground = 'black',height=2,width=15,command=partial (play,2))
btn.place(x=1320, y=610)
#btn.pack()

btn = tkinter.Button(window, text="Next (fast)>>",font = ('calibri',20,'bold'),background='yellow', foreground = 'black',height=2,width=15, command=partial (play,25))
btn.place(x=1320, y=716)
#btn.pack()

btn = tkinter.Button(window, text="GO",font = ('calibri',20,'bold'),background='red', foreground = 'black',height=14,width=15, command=out)
btn.place(x=1320, y=0)
#btn.pack()

btn = tkinter.Button(window, text="GNO",font = ('calibri',20,'bold'),background='purple', foreground = 'yellow',height=14,width=15,command=not_out)
btn.place(x=0, y=0)
#btn.pack()

btn = tkinter.Button(window, text="very (D slow)>>",font = ('calibri',20,'bold'),background='pink', foreground = 'black',height=2,width=15, command=partial (play,0.5))
btn.place(x=1320, y=510)
#btn.pack()

btn = tkinter.Button(window, text="<<very v(slow)",font = ('calibri',20,'bold'),background='black', foreground = 'red',height=2,width=15,command=partial (play,-1))
btn.place(x=0, y=510)
#btn.pack()
window.mainloop()
