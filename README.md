# HiggsToMuMu

Este repositorio es creado por estudiantes de la UN de Colombia para la clase de Introduccion a la Investigacion Teorica.

Vamos a estudiar la desintegracion del Higgs a dos muones y haremos una simulacion MC para estudiarlo.

Lorena Bucuru,
Laura Caviedes, 
Daniela Daza

# Instalaciones

Para desarrollar este proyecto se debe instalar Madgraph principalmente. Sin embargo, MG5 tiene como requisito instalar ROOT (software libre del CERN). En MG5 se instalará Pythia8 y Delphes como extensiones, pero tambien se hará stand alone ya que de esta forma también se van a utilizar para el proceso de aprendisaje y entendimiento de ambos softwares.

Empezamos instalando Pythia8 stand alone.
## Pythia

Descarga y descomprime el archivo de la [página oficial](https://pythia.org/)
```bash
wget https://pythia.org/download/pythia83/pythia8306.tgz
tar xvfz pythia8306.tgz
```
Dentro de la carpeta de pythia se hace make (ya que no se van a agregar extensiones)
```bash
cd pythia8306
\.configure
make
```
## ROOT

En la página oficial de ROOT se encuentra el paso a paso de la instalación. Para MG5 el que mejor funciona es la [versión 20.08](https://root.cern/releases/release-62008/) y tiene como [requisitos](https://root.cern/install/dependencies) los siguientes paquetes

* *dpkg-dev*
* *cmake*
* *ccmake*
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

```bash
  wget https://root.cern/download/root_v6.20.08.source.tar.gz
  tar -xzvf root_v6.20.08.source.tar.gz
```
Entran y crean una carpeta para instalar root
```
cd root-6.20.08/
mkdir build-root
cd build-root
```
Para instalarlo ejecutamos
```
ccmake ../
```
En la nueva ventana que aparece escribimos ```c``` para configurarlo, se activa "all", "cuda" y "pythia8"dandole enter en frente de cada una y además se escribe la dirección del xmldoc de pythia8 frente a "pythia8-data". Configuran de nuevo con ```c```, salen ```e``` y lo compilan con ```g```.
Por último realizan los siguientes comandos

```bash
cmake --build
sudo make install
source root/bin/thisroot.sh
```
## Tcl Developer

Tcl es necesario para instalar Delphes, usualmente viene instalado en las versiones de linux y Mac OS y para verificar que se encuentre instalado se ejecuta el siguiente comando
```bash
tclsh
```
y escribimos
```bash
info patchlevel
```
Aparece la versión de tcl instalada y con eso es suficiente, para salir se escribe exit.
Si no se encuentra instalada, en la [página oficial](http://www.tcl.tk/software/tcltk/) se encuentran las nstrucciones. Según el sistema operativo
```bash
sudo apt-get install tcl
```
y para verificar se hace lo previamente escrito.


## Delphes
Descargar y descomprimir (instrucciones en la [página oficial](https://github.com/delphes/delphes).
```bash
wget http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.5.0.tar.gz
tar -zxf Delphes-3.5.0.tar.gz
```
Dentro de la carpeta de delphes se instala junto con el event display
```bash
cd Delphes-3.5.0
make -jN
make -jN display
```
N es el número de núcleos que tiene el computador.
Para verificar que root corra bien se realizan los siguientes comandos y no debe salir nada.
```bash
root -l
gSystem->Load("libDelphes");
```
## MadGraph

Para instalar MadGraph hay que tener varias cosas previamente instaladas, ROOT y Python 2.7, la versión 3 de python no es compatible.


Del (launchpad)[https://launchpad.net/mg5amcnlo] de Madgraph descargar la versión 2.9.3 y extraerlo con el comando ```tar -xvf```

Dentro de la carpeta de Madgraph
```cd MG5_aMC_v2_9_3```
esccribir el comando
```./bin/mg5_aMC```
y debería abrirse el terminal de Madgraph. Dentro de Madgraph se necesitan instalar otros paquetes como MadAnalysis, Pythia8 y Delphes. Para ello solo es necesario escribir los siguientes comandos dentro de MadGraph
```
install MadAnalysis
install Pythia8
install Delphes
```
Para salirse del terminal de MadGraph basta con escribir ```exit```.