# HiggsToMuMu

Este repositorio es creado por estudiantes de la UN de Colombia para la clase de Introduccion a la Investigacion Teorica.

Vamos a estudiar la desintegracion del Higgs a dos muones y haremos una simulacion MC para estudiarlo.

Lorena Bucuru,
Laura Caviedes, 
Daniela Daza

# Instalaciones

Para desarrollar este proyecto se debe instalar Madgraph principalmente. Sin embargo, MG5 tiene como requisito instalar ROOT (software libre del CERN). En MG5 se instalará Pythia8 y Delphes como extensiones, pero tambien se hará stand alone ya que de esta forma también se van a utilizar para el proceso de aprendisaje y entendimiento de ambos softwares.

## ROOT

En la página oficial de ROOT se encuentra el paso a paso de la instalación. Para MG5 el que mejor funciona es la [versión 20.08](https://root.cern/releases/release-62008/) y tiene como [requisitos](https://root.cern/install/dependencies) los siguientes paquetes

* *dpkg-dev*
* *cmake*
* *g++*
* *gcc*
* *binutils*
* *libX11-devel*
* *libXpm-devel*
* *libXft-devel*
* *libXext-devel*
* *libjpeg*
* *libpng*
* *python2.7*
* *libssl-dev:*

Despues de verificar, se procede a la [instalación](https://root.cern/install/https://root.cern/install/).
´´´
wget https://root.cern/download/root_v6.20.08.source.tar.gz
tar -xzvf root_v6.20.08.source.tar.gz
´´´
Y hacer un source para ejecutar root
´´´
source root/bin/thisroot.sh
´´´
## Tcl Developer

Tcl es necesario para instalar Delphes, usualmente viene instalado en las versiones de linux y Mac OS y para verificar que se encuentre instalado se ejecuta el siguiente comando
´´´
tclsh
´´´
y escribimos
´´´
info patchlevel
´´´ 
Aparece la versión de tcl instalada y con eso es suficiente, para salir se escribe exit.
Si no se encuentra instalada, en la [página oficial](http://www.tcl.tk/software/tcltk/) se encuentran las nstrucciones. Según el sistema operativo
´´´
sudo apt-get install tcl
´´´
y para verificar se hace lo previamente escrito.

## Pythia

Descarga y descomprime el archivo de la [página oficial](https://pythia.org/)
´´´
wget https://pythia.org/download/pythia83/pythia8306.tgz
tar xvfz pythia8306.tgz
´´´
Dentro de la carpeta de pythia se hace make (ya que no se van a agregar extensiones)
´´´
cd pythia8306
make
´´´
## Delphes
Descargar y descomprimir (instrucciones en la [página oficial](https://github.com/delphes/delphes).
´´´
wget http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.5.0.tar.gz
tar -zxf Delphes-3.5.0.tar.gz
´´´
Dentro de la carpeta de delphes se instala junto con el event display
´´´
cd Delphes-3.5.0
make -jN
make -jN display
´´´
N es el número de núcleos que tiene el computador.
Para verificar que root corra bien se realizan los siguientes comandos y no debe salir nada.
´´´
root -l
gSystem->Load("libDelphes");
´´´
## MadGraph

Para instalar MadGraph hay que tener varias cosas previamente instaladas, ROOT y Python 2.7, la versión 3 de python no es compatible.
