int main() {
    Televisor tv;

    // Puntero a método de Televisor
    void (Televisor::*pa)();
    pa = &Televisor::apagar;  // Asigna el método apagar

    // Llamar al método a través del puntero
    (tv.*pa)();  

    // Asignamos otro puntero al método encender
    void (Televisor::*pe)();
    pe = &Televisor::encender;
    (tv.*pe)();  // Llamar a encender

    // Asignamos otro puntero al método subirVolumen
    void (Televisor::*ps)();
    ps = &Televisor::subirVolumen;
    (tv.*ps)();  // Llamar a subir volumen

    // Podemos cambiar el puntero pa para que apunte a otro método
    pa = &Televisor::subirVolumen;
    (tv.*pa)();  // Llamar a subir volumen (ahora con el puntero pa)

    return 0;
}
