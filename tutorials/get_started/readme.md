Hier erscheinen die ersten Schritte für die Einrichtung einer Entwicklungsumgebung.

# Die Hardware:
* irgendwas braucht man: https://eckstein-shop.de/Starter-Sets
* Es gibt viele unterschiedliche Modelle, C++ Code ist relativ portabel:
   * Abstrakte Datenstrukturen, Programmlogik leicht übertragbar
   * Ansteuerung der einzelnen Hardwarekomponenten direkt von der Hardware abhängig

* seine Hardware kennenlernen:
   * https://i.stack.imgur.com/dVkQU.jpg
   * http://lmgtfy.com/?q=arduino+uno+ports
   * http://www.atmel.com/products/microcontrollers/avr/default.aspx (!!! Das Datenblatt eures Controllers wird nach und nach euer bester Freund)

# Programmierung unter Windows:
* ausdrücklich empfohlen: Verwendung vonAtmel Studio
* Download der Software: http://www.atmel.com/tools/ATMELSTUDIO.aspx
* Download von AVRDude (Tool zum Übertragen vom Compilat auf den Arduino Uno):
http://mirror.rackdc.com/savannah//avrdude/
* Einrichtung und Nutzung von AVRDude:
https://www.youtube.com/watch?v=zEbSQaQJvHI
Argumente: "D:\arduinotest\avrdude.conf" -v -patmega328p -carduino -P\\.\COM6 -b115200 -D -Uflash:w:"$(ProjectDir)Debug\$(TargetName).hex":i

# Programmierung unter Unixumgebungen:
* Nutzung des Compilers "avr-gcc" mittels Konsole und makefile.
* http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/
* 
