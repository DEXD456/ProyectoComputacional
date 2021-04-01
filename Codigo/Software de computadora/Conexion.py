from firebase import firebase

# put the name of your database where the ***** are
address = "https://estacion-meteorologica-6a5e1-default-rtdb.firebaseio.com/"
fb = firebase.FirebaseApplication(address)


def TemperaturaActual():
    temperatura =fb.get("/Estacion/Fijos/Temperatura","")
    return temperatura

def HumedadActual():
    humedad =fb.get("/Estacion/Fijos/Humedad","")
    return humedad

def LuxActual():
    lux = fb.get("/Estacion/Fijos/LUX","")
    return lux
