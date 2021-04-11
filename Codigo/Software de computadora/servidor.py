from flask import Flask,render_template

app = Flask(__name__)

@app.route("/")
def index():
    nombre = "Cristian"
    return render_template("index.htm",nombre=nombre)

@app.route("/base")
def base():
    return render_template("base.htm")


if __name__ == "__main__":
    app.run(debug=True)

# import socket

# mi_socket = socket.socket()
# mi_socket.bind(('localhost',8000))
# mi_socket.listen(5)

# while True:
#     conexion,addr = mi_socket.accept()
#     print ("Nueva conexion establecida")
#     print (addr)
#     peticion = conexion.recv(1024)
#     print(peticion)
#     conexion.send("Hola, te saludo desde el servidor")
#     conexion.close()