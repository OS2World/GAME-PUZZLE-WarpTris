.* Ayuda de WarpTris - Espanol
:userdoc.

:h1 res=001.Ayuda general
:i1 id=Win.Ventanas
:i1 id=HowTo.Como jugar a WarpTris
:i1 id=Menus.Menus
:font facename=Helv size=8x12.
Elija uno de los temas siguientes&colon.
:p.
:ul compact.
:li.:link reftype=hd res=016.Acuerdo de licencia:elink.
:li.:link reftype=hd res=017.Marcas registradas:elink.
:li.:link reftype=hd res=007.Jugando a WarpTris:elink.
:li.:link reftype=hd res=008.Teclas de WarpTris:elink.
:li.:link reftype=hd res=002.Opciones de menu:elink.
:li.:link reftype=hd res=003.Ventana Juego:elink.
:li.:link reftype=hd res=004.Ventana Puntos:elink.
:li.:link reftype=hd res=005.Ventana Siguiente:elink.
:li.:link reftype=hd res=006.Ventana Mejores Puntuaciones:elink.
:li.:link reftype=hd res=023.Informar de errores:elink.
:li.:link reftype=hd res=009.Creditos:elink.
:eul.
:p.

:h1 res=023.Informar de errores
:font facename=Helv size=8x12.
:p.
Si encuentra algun error en este programa, por favor comuniquelo a traves de la comunidad OS2World
(https&colon.//www.os2world.com), con una descripcion del error.
:p.
Gracias de antemano.

:h1 res=002.Opciones de menu
:font facename=Helv size=8x12.
:p.
Elija un enlace de la lista siguiente&colon.
:p.
:ul compact.
:li.:link reftype=hd res=010.Menu Juego:elink.
:li.:link reftype=hd res=011.Menu Impulso:elink.
:li.:link reftype=hd res=012.Menu Sonido:elink.
:li.:link reftype=hd res=013.Menu Opciones:elink.
:li.:link reftype=hd res=014.Menu Ventanas:elink.
:li.:link reftype=hd res=015.Menu Ayuda:elink.
:eul.
:p.

:h1 res=003.Ventana Juego
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Juego
En esta ventana es donde se juega realmente. Las piezas aparecen en el cuadrado gris del
centro y despues empiezan a caer hacia un lado al azar.
:p.
Cuando alguna pieza cubre una parte del cuadrado gris central, el juego termina.
:p.
Esta ventana tiene tambien un menu contextual con las opciones de la barra de menus que la afectan.

:h1 res=004.Ventana Puntos
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Puntos
No hay mucho que decir sobre esta ventana. Muestra su puntuacion actual.

:h1 res=005.Ventana Siguiente
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Siguiente
Esta ventana muestra la pieza siguiente y la direccion de su proximo impulso.
:p.
Si no desea esta ayuda, puede ocultarla con su boton de ocultar.

:h1 res=006.Ventana Mejores Puntuaciones
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Mejores Puntuaciones
En esta ventana el juego guarda las diez mejores puntuaciones y los nombres de sus jugadores.
:p.
Si lo desea, puede borrarlas todas eliminando el archivo Hiscore.bin. La proxima vez que ejecute
el juego, se creara un archivo de puntuaciones vacio.

:h1 res=007.Jugando a WarpTris
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.Jugando a WarpTris
WarpTris es un tipo de Tetris bastante diferente (y original). En lugar de caer desde arriba de la ventana Juego,
las piezas aparecen en el centro y despues empiezan a caer hacia un lado, al azar.
:p.
Este comportamiento tiene una explicacion pseudo-fisica&colon. imagine que esta en el espacio, donde no hay gravedad. Si suelta
algo y le da un impulso en una direccion, esa es la direccion en que empezara a moverse (o caer) y
seguira moviendose asi, a menos que encuentre algo en su camino. En WarpTris las piezas aparecen en el centro de la
ventana Juego, reciben un impulso en una direccion al azar y empiezan a caer enseguida hacia ella (igual que en el espacio).
:p.
La pieza solo puede caer hacia cuatro direcciones (arriba, abajo, izquierda y derecha) y puede hacer
lineas en los cuatro lados de la ventana Juego. Pierde cuando alguna pieza cubre un cuadro del area gris central.
:p.
Hay tres niveles de dificultad, que llamo impulsos (tiene mas sentido). Se diferencian en
la fuerza del impulso y por tanto en la velocidad con que se mueven las piezas.
:p.
Por ultimo, cuando hace una linea en un lado, solo se evalua el area desde ese lado de la ventana hasta el
primer lado paralelo del cuadrado gris central, lo que abre huecos en los lados adyacentes
de la ventana Juego. Por ejemplo, la figura siguiente muestra que area se evalua si hace
una linea en el lado izquierdo de la ventana Juego.
:p.
:artwork name='help\Figure.bmp' align=center.
:p.
:nt.
Solo puede mover la pieza paralelamente al lado hacia el que cae.
:ent.

:h1 res=008.Teclas de WarpTris
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.Teclas de WarpTris
Las teclas validas en este juego son&colon.
:parml compact tsize=20 break=none.
:pt.Espacio
:pd.Dejar caer la pieza
:pt.Teclado numerico Arriba o flecha arriba
:pd.Mover hacia arriba
:pt.Teclado numerico Abajo o flecha abajo
:pd.Mover hacia abajo
:pt.Teclado numerico Izquierda o flecha izquierda
:pd.Mover a la izquierda
:pt.Teclado numerico Derecha o flecha derecha
:pd.Mover a la derecha
:pt.Teclado numerico 5 o Mayus (cualquiera)
:pd.Girar
:pt.P
:pd.Pausa / continuar
:eparml.
:p.
Los atajos siguientes funcionan en toda la ventana de WarpTris&colon.
:parml compact tsize=20 break=none.
:pt.Ctrl+N
:pd.Juego nuevo
:pt.Ctrl+P
:pd.Pausar / continuar el juego
:pt.Ctrl+Q
:pd.Abandonar el juego actual
:pt.Ctrl+X
:pd.Salir de WarpTris
:pt.Ctrl+B
:pd.Fondo Activo si / no
:pt.Ctrl+F
:pd.Controles de Marco si / no
:pt.Ctrl+1, 2, 3
:pd.Impulso Donkey, Formula 1, WARP!
:eparml.
:p.
El juego tambien se detiene cuando la ventana Juego pierde el foco, salvo que Fondo Activo este activado.
:nt.
Para usar las teclas del teclado numerico debe estar activa la tecla BLOQ NUM.
:ent.

:h1 res=009.Creditos
:font facename=Helv size=8x12.
:p.
WarpTris es un juego de 32 bits tipo Tetris para OS/2, escrito por Paulo Gago da Camara en las Azores, Portugal, en 1996.
Hizo este juego con el proposito de aprender programacion PM.
:p.
Agradecimientos especiales a su antiguo profesor de C/C++, el Dr. Gunther Funk, por la idea original, y a su amigo
Jorge Cipriano, por su apoyo moral y tecnico. Tambien fue el probador de las versiones Alfa, Beta y Final.
:p.
La version para Open Watcom, con la interfaz en seis idiomas, fue preparada por la comunidad OS2World en 2026.

:h1 res=010.Menu Juego
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Juego
:dl tsize=20.
:dt.:hp2.Nuevo:ehp2. (Ctrl+N)
:dd.Esta opcion inicia un juego nuevo. No esta disponible mientras hay un juego en marcha.
:dt.:hp2.Pausar Juego:ehp2. (Ctrl+P)
:dd.Detiene el juego. Elijala otra vez para continuar.
:dt.:hp2.Abandonar Juego:ehp2. (Ctrl+Q)
:dd.Detiene el juego actual y muestra la puntuacion. WarpTris sigue abierto.
:dt.:hp2.Salir:ehp2. (Ctrl+X)
:dd.Sale de WarpTris inmediatamente.
:edl.

:h1 res=011.Menu Impulso
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Impulso
Hay tres clases de impulso, que corresponden a tres velocidades de juego. Este menu
representa en realidad el menu de niveles.
:p.
El impulso Donkey es el mas debil (el mas lento) y WARP! es el mas fuerte (el mas rapido).

:h1 res=012.Menu Sonido
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Sonido
Activa o desactiva el sonido.

:h1 res=013.Menu Opciones
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Opciones
:dl tsize=20.
:dt.:hp2.Propiedades:ehp2.
:dd.Muestra el cuaderno de propiedades.
:dt.:hp2.Detalle:ehp2.
:dd.Alto muestra una animacion suave cuando aparece una pieza nueva, Medio es la animacion original
y Bajo la desactiva.
:dt.:hp2.Idioma:ehp2.
:dd.Cambia el idioma de los menus, ventanas, dialogos y de esta ayuda. La eleccion se recuerda.
:dt.:hp2.Fondo Activo:ehp2. (Ctrl+B)
:dd.Si esta activado, el juego sigue en marcha mientras otra ventana tiene el foco.
:dt.:hp2.Controles de Marco:ehp2. (Ctrl+F)
:dd.Oculta o muestra la barra de titulo y el menu de la ventana de WarpTris. Use Ctrl+F otra vez para recuperarlos.
:dt.:hp2.Guardar al salir:ehp2.
:dd.Guarda la configuracion y las posiciones de las ventanas en WarpTris.cfg al salir.
:edl.

:h1 res=014.Menu Ventanas
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Ventanas
:dl tsize=20.
:dt.:hp2.Puntuaciones:ehp2.
:dd.Muestra u oculta la ventana Mejores Puntuaciones.
:dt.:hp2.Siguiente:ehp2.
:dd.Muestra u oculta la ventana Siguiente.
:dt.:hp2.Puntos:ehp2.
:dd.Muestra u oculta la ventana Puntos.
:dt.:hp2.Juego:ehp2.
:dd.Muestra u oculta la ventana Juego.
:dt.:hp2.Ordenar:ehp2.
:dd.Restaura las posiciones predeterminadas de las ventanas Juego, Puntos, Siguiente y Mejores Puntuaciones.
:edl.

:h1 res=015.Menu Ayuda
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Ayuda
:dl tsize=20.
:dt.:hp2.Ayuda general:ehp2.
:dd.Muestra la ventana de ayuda general.
:dt.:hp2.Indice de ayuda:ehp2.
:dd.Muestra la ventana del indice de ayuda.
:dt.:hp2.Ayuda sobre ayuda:ehp2.
:dd.Muestra informacion que explica como usar la ayuda.
:dt.:hp2.About:ehp2.
:dd.Muestra el dialogo Acerca de.
:edl.

:h1 res=016.Acuerdo de licencia
:font facename=Helv size=8x12.
.br
:hp4.Licencia de WarpTris.:ehp4.
:p.
WarpTris es software libre&colon. puede redistribuirlo y/o modificarlo bajo los terminos de la Licencia Publica General de GNU publicada por la Free Software Foundation, ya sea la version 3 de la Licencia o (a su eleccion) cualquier version posterior.
:p.
Este programa se distribuye con la esperanza de que sea util, pero SIN NINGUNA GARANTIA, ni siquiera la garantia implicita de COMERCIABILIDAD o IDONEIDAD PARA UN FIN DETERMINADO. Vea el archivo LICENSE.txt para el texto completo de la licencia.
:p.
(c) Paulo Gago da Camara 1996. (c) 2026 OS2World.
:i1.Acuerdo de licencia

:h1 res=017.Marcas registradas
:font facename=Helv size=8x12.
:i1.Marcas registradas
:p.
Los terminos siguientes son marcas registradas de IBM Corporation en Estados Unidos o en otros paises&colon.
:sl compact.
:li.IBM
:li.OS/2
:li.Presentation Manager (PM)
:esl.
:p.
Cualquier otra marca mencionada pertenece a sus respectivos propietarios.
:p.
No es mi intencion infringir ningun derecho de autor ni marca registrada con este programa.
:p.

:euserdoc.
