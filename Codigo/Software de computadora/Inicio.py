from tkinter import *
from tkinter import messagebox

root = Tk()

def Informacion():
    messagebox.showinfo("Estacion meteorologica","Estacion meteorologica basica\nVersion 1.0\n Proyecto computacionl II ")

def Contactos():
    messagebox.showinfo("Contactos","Envie correo a BPC2020106@est.univalle.edu")

def Cerrar():
    valor = messagebox.askokcancel("Cerrar","Deseas cerrar la aplicacion")
    if valor:
        root.destroy()

barraMenu = Menu(root)
root.config(menu = barraMenu,width = 1000,height =600)


Inicio = Menu(barraMenu,tearoff=0)
Inicio.add_command(label="Pagina principal")
Inicio.add_command(label="Base de datos")
Inicio.add_separator()
Inicio.add_command(label="Cerrar",command=Cerrar)

Descargas = Menu(barraMenu,tearoff=0)
Descargas.add_command(label="Base de datos")
Descargas.add_command(label="Graficos de prediccion")


Ayuda = Menu(barraMenu,tearoff=0)
Ayuda.add_command(label="Manual de uso")
Ayuda.add_command(label="Informacion",command=Informacion)
Ayuda.add_command(label="Contactos",command=Contactos)

barraMenu.add_cascade(label="Inicio",menu = Inicio)
barraMenu.add_cascade(label="Descargas",menu = Descargas)
barraMenu.add_cascade(label="Ayuda",menu = Ayuda)

root.mainloop()