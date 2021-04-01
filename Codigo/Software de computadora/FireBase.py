
from firebase import firebase

# put the name of your database where the ***** are
address = "https://estacion-meteorologica-6a5e1-default-rtdb.firebaseio.com/"
fb = firebase.FirebaseApplication(address)

import tkinter as tk

root = tk.Tk()


def seedata():
	data2 = data[lbx.get(lbx.curselection())]
	for k in data2:
		lbx2.insert(tk.END, k + ": " + str(data2[k]))
        
def Limpiar ():
    xCntr = 0
    for i in range (0, 9):
        yCntr = int(i) - xCntr
        lbx2.delete(yCntr,yCntr)
        xCntr = xCntr + 1

lbx = tk.Listbox(root)
lbx.grid(row=4,column=0,padx=10)
data = fb.get(address, "/Estacion/BD/Datos")
for k in data:
	lbx.insert(tk.END, k)
lbx2 = tk.Listbox(root)
lbx2.grid(row=4,column=1,padx=10)
lbx.bind("<<ListboxSelect>>", lambda x: seedata())




#-----------------------------Labels--------------------------------------------------
Label1 = tk.Label(root,text="Estacion meteorologica")
Label1.grid(row=0,column=0,padx=10,columnspan=2)

Label2 = tk.Label(root,text="Id de datos guardados")
Label2.grid(row=2,column=0,padx=10)

Label3 = tk.Label(root,text="Datos Obtenidos ")
Label3.grid(row=2,column=1,padx=10)

B = tk.Button (root, text = "Borrar ListBox", command = Limpiar)
B.grid(row= 5 , column = 0, padx =10,columnspan=2)

root.mainloop()