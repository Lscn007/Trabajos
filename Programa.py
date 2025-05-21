def texto_a_bloques_base40(mensaje):
    tabla = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .,?"
    base = 40
    if len(mensaje) % 2 != 0:
        mensaje += 'A'
    bloques = []
    for i in range(0, len(mensaje), 2):
        c1 = tabla.index(mensaje[i])
        c2 = tabla.index(mensaje[i + 1])
        bloques.append(c1 * base + c2)
    return mensaje, bloques

def cifrar_bloques(bloques, clave, modulo):
    return [(b + clave) % modulo for b in bloques]

def descifrar_bloques(bloques_cifrados, clave, modulo):
    return [(b - clave) % modulo for b in bloques_cifrados]

def bloques_a_texto(bloques, tabla, limpiar=False):
    base = 40
    texto = ""
    for b in bloques:
        c1 = tabla[b // base]
        c2 = tabla[b % base]
        texto += c1 + c2
    if limpiar:
        texto = texto[:-1]
    return texto

tabla = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .,?"
base = 40
modulo = 1600
clave = 18

mensaje_original = "HOLA?"
tiene_relleno = len(mensaje_original) % 2 != 0

mensaje_corregido, bloques_numericos = texto_a_bloques_base40(mensaje_original)
bloques_cifrados = cifrar_bloques(bloques_numericos, clave, modulo)
bloques_descifrados = descifrar_bloques(bloques_cifrados, clave, modulo)
texto_recuperado = bloques_a_texto(bloques_descifrados, tabla, limpiar=tiene_relleno)

print("Bloques numéricos:", *bloques_numericos)
print("Bloques cifrados:", *bloques_cifrados)
print("Bloques descifrados:", *bloques_descifrados)
print("Texto recuperado:", texto_recuperado)