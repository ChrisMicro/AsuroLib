/*! \mainpage Die Asuro Library
 *
 * \image html asuro1.gif "Der Asuro"
 *
 * \section intro_sec Einfuehrung
 * Die Asuro Library ist eine Sammlung von C-Funktionen fuer den Roboter Asuro. 
 * Der Asuro wurde vom DLR (Deutschen Zentrum fuer Luft und Raumfahrt) http://www.dlr.de in Oberpfaffenhofen entwickelt.
 * 
 * Die Ur-Version der Bibliothek wurde von Jan Grewe vom DLR geschrieben. 
 * Einige User vom Roboternetz Forum http://www.roboternetz.de/phpBB2 haben die Lib erweitert. 
 *
 * Die Asuro Lib ist ab Version 2.70 nicht mehr nur eine Quellcode Bibliothek sondern eine
 * Objectcode Bibliothek. D.h. die Bibliothek besteht aus einem Archiv von Objekt Files, 
 * die normalerweise nicht mehr fuer jedes Projekt neu uebersetzt (compiliert) werden muss, sondern nur noch gelinkt wird. 
 * Die Bibliothek selbst muss nur neu uebersetzt werden, wenn an den Bibliotheks Funktionen Änderungen oder Definitionen 
 * in den Header Files vorgenommen wurden.
 *
 * Der Vorteil der Objekt Bibliothek gegenueber der Quellode Bibliothek ist die drastisch reduzierte
 * Groesse der Hex-Files. Im Gegensatz zur Quellcode Bibliothek werden nur die Objekt Files gelinkt, 
 * die vom Benutzer Programm aufgerufen werden. Bei der Quellcode Bibliothek werden immer alle 
 * Files gelinkt, unabhaengig davon ob sie ueberhaupt benoetigt werden.

 * \section links Wichtige Links
 * \li http://sourceforge.net/projects/asuro Hier findet man immer die aktuelle Version der Asuro Bibliothek
 * \li http://www.roboternetz.de/phpBB2/viewforum.php?f=44 Das Asuro Forum im Roboternetz
 * \li http://www.asurowiki.de/pmwiki/pmwiki.php Ein Wiki ueber den Asuro
 *
 * Der Programm Code der Asuro Bibliothek steht unter der General Public License (GPL)
 *
 * \section preparation_sec Voraussetzungen 
 *
 * Um die Asuro Lib zu verwenden wird neben dem Asuro eine Entwicklungsumgebung fuer die Atmel AVR Prozessoren benoetigt.
 * Der Quelllcode der Bibliothek wurde fuer die AVR-GCC Cross-Compiler Suite geschrieben. Den AVR-GCC ist kostenlos fuer diverse Plattformen 
 * (Windows, Linux, Mac) verfuegbar. Es wird die Verwendung der jeweils neuesten Version empfohlen. Die Bibliothek kommt aber auch mit alten Versionen 
 * klar. Auf der Asuro CD befindet sich z.B. eine sehr alte WinAVR Version (20030913) aus dem Jahre 2003. Die aktuelle WinAVR Version (20070525) ist 
 * hier auf jeden Fall vorzuziehen.
 *
 * \section downloads Download Links
 * \li http://sourceforge.net/projects/winavr/ WinAVR. Der AVR Cross-Compiler fuer Windows.
 * \li http://www.avrfreaks.net/wiki/index.php/Documentation:AVR_GCC AVR-GCC Homepage
 *
 * \section install_sec Installation 
 *
 * Es gibt 3 Moeglichkeiten die Asuro Lib zu downzuloaden und zu installieren.
 * \li Download der <tt>AsuroLib-vXXX-Setup.exe</tt> Datei. Die Installation startet man durch Doppelklick auf die <tt>AsuroLib-vX.XX-Setup.exe</tt> Datei.
 * \li Download  <tt>AsuroLib-vXXX.zip</tt> Datei. Das Zip-Files wird in ein beliebiges Verzeichnis ausgepackt.
 * \li Download ueber Subversion (SVN). Dazu wird ein SVN Client z.B. SmartSVN http://www.syntevo.com/smartsvn/ oder 
 * TortoiseSVN http://tortoisesvn.net/ benoetigt. 
 *
   \verbatim
   SVN Einstellungen:
   Hostname: asuro.svn.sourceforge.net
   Port: 443
   Protocol: HTTPS
   Repository Path: /svnroot/asuro
   Username: SourceForge.net username fuer SVN Schreibrechte, keiner fuer Leserechte
   Password: SourceForge.net user password fuer SVN Schreibrechte, keines fuer Leserechte
   \endverbatim
 *
 * \section directory_sec Verzeichnis Struktur
 * Nach der Installation befindet sich folgende Verzeichnis Struktur auf der Festplatte.
 * Das Installationsverzeichnis im folgenden <tt>[INST_DIR]</tt> genannt, koennte z.B. <tt>C:/ASURO_SRC/AsuroLib</tt> lauten.
 *
   \verbatim
   C:\ASURO_SRC\AsuroLib                     Das Installations Verzeichnis
                        \doc                 Dokumentations Verzeichnis. HTML und HTML Help Dateien
                        \lib                 Bibliotheks Quell Dateien und Objekt Bibiothek
                        \lib\inc             Bibliotheks Header Dateien
                        \examples            Beispiel Projekte
                        \examples\FirstTry   Beispiel Projekt FirstTry
                        \examples\SelfTest   Beispiel Projekt SelfTest
   \endverbatim
 *
 * \section makefile_sec Wichtig! Anpassen der Makefiles
 *
 * Die wichtigste Änderung der AsuroLib spielt sich im Hintergrund ab in den Makefiles. Hier wurde aufgeraeumt um die Verwendung 
 * der Bibliothek fuer eigene Projekte zu erleichtern. Es gibt nur noch eine einzige Stelle, die man aendern muss um alle
 * Pfadangaben, die mit der Lib zu tun haben, zu aendern.
 * Das ganze kann natuerlich nur funktionieren wenn nur noch diese neuen Makefiles verwendet werden.
 *
 * Aufgrund der zahlreichen Probleme, die manche Nutzer beimn Installieren der Bibliothek hatten, wurde der Installationsprozess 
 * vereinfacht. Die compilierte Asuro Bibliothek <tt>'libasuro.a'</tt> muss nun nicht mehr in das Lib-Verzeichnis des AVR-GCC bzw. WinAVR Compilers 
 * kopiert werden, sondern verbleibt im Verzeichnis <tt>[INST_DIR]/lib</tt>. Statt dessen wird im Makefile der Pfad zur Bibliothek eingetragen.
 * Der Verzeichnisname sollte mit normalem Slash (/) angegeben sein nicht mit Backslash (\).
 * In den aktuellen Makefiles geschieht dies (siehe Examples Ordner) durch folgende Zeilen:
 * Hinweis: ein # am Anfang in einer Zeile eines Makefiles bedeutet. Dies ist ein Kommentar, kein Kommando zum Ausfuehren
   \verbatim
   # additional Include path for libraries
   LIBPATH = ../../lib
   \endverbatim
 * In vorigen Beipiel wurden relative Pfade verwendet. Das geht solange gut, solange alle Projekte wie die Beispiel Projekte aus der 
 * Asuro Lib in der gleichen Verzeichnisebene (2 Verzeichnisebenen tiefer als die lib) liegen. 
 * Ist dies nicht der Fall, sollte man statt dessen absolute Pfade verwenden, wie z.B.:
   \verbatim
   # additional Include path for libraries
   LIBPATH = C:/ASURO_SRC/AsuroLib/lib
   \endverbatim
 * Falls man die Bibliothek in ein Verzeichnis mit Leerzeichen installiert hat, muss man die Pfadangaben in Hochkommas einfuegen    
   \verbatim
   # additional Include path for libraries
   LIBPATH = "C:/Eigene Dateien/ASURO_SRC/AsuroLib/lib"
   \endverbatim
 *
 * \section project_sec Neue Projekte
 *
 * Will man ein eigenes Programm fuer den Asuro erstellen, welches die Asuro Bibliothek verwendet kopiert man besten den kompletten Ordner 
 * <tt>[INST_DIR]/examples/FirstTry</tt> in einen neuen Ordner. Dann muss man nur noch das Makefile wie oben beschrieben anpassen, seine Programm 
 * schreiben und sollte es dann uebersetzen koennen. In dem Projekt Ordner duerfen sich aber keine Überbleibsel von vorherigen Asuro Libs (asuro.c, asuro.h)
 * befnden. Der Compiler und Linker uebersetzt/bindet sonst naemlich diese alten Dateien ein. Auch sollte die asuro.h immer in Hochkommans eigebunden
 * werden, nicht in spitzen Klammern. Header Dateien in spitzen Klammern werden als System Include Dateien im AVR Include Verzeichnis gesucht.
 *
 * Enthaelt das eigene Projekt zusaetzliche Quelldateien (ausser test.c) muessen diese ebenfalls im Makefile eingetragen werden. Als Beispiel Projekt 
 * bietet sich hier das Makefile aus dem Selbsttest an <tt>[INST_DIR]/examples/SelfTest</tt>. Hier werden noch mehrere Quelldateien dazugefuegt.
   \verbatim
  # If there is more than one source file, append them above, or adjust and
  # uncomment the following:
  SRC += asuro.c \
  Test.c main.c \
  Demo.c LineDemo.c IRDemo.c PCDemo.c RechteckDemo.c 
   \endverbatim
 * Auch der Name der Zieldatei (sonst immer test.hex) wurde hier angepasst. Es muss natuerlich eine Quelldatei geleichen Namens existieren.
   \verbatim
   # Target file name (without extension).
   TARGET = SelfTest
   \endverbatim
 *
 * \section examples_sec Beispiel Projekte
 *
 * Im Ordner <tt>[INST_DIR]/examples</tt> befiden sich einige Beispiel Projekte, die sich fuer eigene Projekte anpassen oder erweitern lassen 
 * bzw. als Vorlage fuere eigene Projekte dienen sollen.
 *
 * \li <b>FirstTry</b>: Ein Dummy Projekt, das nichts tut als die Asuro Hardware zu initialisieren und dann ein Enlosschleife auszufuehren.
 *           Der ideale Einstieg fuer eigene Projekte. Insbesondere das Makefile kann fuer die meissten Projekte verwendet werden.
 * \li <b>SelfTest</b>: Der Asuro Selbsttest, wie er sich auch auf eienm fabrikneuem Asuro befindet. Allerdinmgs angepasst fuer die AsuroLib und mit       *           dem Unterschied, dass nach einmaliger Ausfuehrung des Selbsttests, die versteckten Demo Programme ausgefuehrt werden koennen.
 *           Taste 1 = LineDemo, Taste 2 = RechteckDemo, Taste 3 = PCDemo, Taste 4 = IRDemo (entspricht der RC5Demo). 
 * \li <b>EncoderTest</b>: Testet die Encoder.
 * \li <b>TasterTest</b>: Testet die Tastsensoren und gibt die gedrueckten Tasten auf dem Terminal aus.
 * \li <b>LineTest</b>: Liniensensor Test. Entspricht der LineDemo aus dem Selbsttest
 * \li <b>RC5Test</b>: Den Asuro ueber eine RC5 kompatible Infrarot Fernbedienung steuern. entspricht der IRDemo aus dem Selbsttest.
 *           Alle programmierbaren Universalfernbedienungen beherschen das RC5 Protokoll von Philips. 
 * \li <b>MotorTest</b>: Testet die Motor Steuerfunktionen Go und Turn
 * \li <b>KollisionTest</b>: Kollisionserkennung ueber die Taster. Bei KLollision faehrt der Asuro ein rueckwaerts Kurve und danmn wieder geradeaus.
 * \li <b>IRCollisionTest</b>: Kollisionserkennung ueber die Infrarot Schnittstelle. Benoetigt den Umbau der IR Schnittstelle 
 * \li <b>I2CLCD</b>: Test eines LCD Moduls. Anbindung erfolgt ueber I2C. Auch fuer die LCD Erweiterung aus dem 2. Asuro Buch verwendbar.
 *
 * \section compile_sec Compilieren der Asuro Library
 *
 * Nimmt man Änderungen an der Bibliotheks Funktionen oder den Header Files vor, muss die Bibliothek logischerweise neu uebersetzt werden,
 * damit sich die Änderungen in den Programmen auch auswirken.
 *
 * Um die Lib neu zu uebersetzen startet man den Make Prozess im Verzeichnis <tt>[INST_DIR]/lib</tt> mit:
   \verbatim
   make clean
   make all
   \endverbatim
 * oder man startet die Batch-Datei <tt>lib/make-lib.bat</tt>. 
 * Das kopieren der erzeugten Asuro Objekt Library (wie bei der AsuroLib 2.7.0) in den ACR-GCC Lib Ordner ist nicht mehr notwendig.
 *
 * \section make_doc Erstellen der ASURO Library Dokumentation
 *
 * Zur Erstellung der Asuro Library Dokumentation wird das Tool Doxygen verwendet.
 * Um die Dokumentation selbst zu aktualisieren:
 * \li man laedt sich die aktuelle Doxygen Version von http://www.stack.nl/~dimitri/doxygen/ herunter.
 * \li Installiert Doxygen
 * \li Im Installationsverzeichnis <tt>[INST_DIR]</tt> der Bibliothek startet man die Batchdatei <tt>make_doc.bat</tt>, 
 * um die Dokumentation zu aktualisieren. Dazu muss man eventuell vorher den Pfad auf die Datei <tt>Doxygen.exe</tt> aktualisieren.
 *
 * Die erzeugte HTML Dokumentation befindet sich im Ordner <tt>/doc/html</tt>.
 * Dort kann die Datei index.html in einen Browser geladen werden.
 * 
 * Die Datei <tt>make_doc.log</tt> und <tt>make_doc.err</tt> werden erzeugt um den doxygen-Lauf zu ueberpruefen.

 * \section make_hhdoc Erstellen einer HTML Help Datei
 *
 * Doxygen erzeugt neben der HTML Doku zusaetzlich ein HTML Help Projekt File <tt>/doc/html/index.hhp</tt>. 
 * Daraus kann mit Hilfe des  HTML Help Workshop von Microsoft eine HTML Help Datei erstellt werden. 
 * \li dazu man laedt sich den HTML Help Workshop von
 *     http://www.microsoft.com/downloads/details.aspx?FamilyID=00535334-c8a6-452f-9aa0-d597d16580cc&DisplayLang=en herunter.
 * \li Installiert den HTML Help Workshop durch den Start von <tt>htmlhelp.exe</tt>
 * \li Zum Erzeugen des HTML Help Files startet man die Batchdatei <tt>make_hhdoc.bat</tt>.
 *     Eventuell muss man auch hiervorher den Pfad auf die Datei <tt>hhc.exe</tt> aktualisieren.
 *
 * Das erzeugte HTML Help File befindet sich dann unter <tt>/doc/html/index.chm</tt>   
 *
 * \section tshoot Troubleshooting
 *
 * Falls es doch noch zu Fehlern oder Warnungen beim Übersetzen gibt, hier noch einige Hinweise:
 *
  \verbatim
  warning: pointer targets in passing argument 1 of 'SerWrite' differ in signedness
  \endverbatim
 * Diese Warnung gibt es bei Verwendung des neuesten AVR Compilers. Das bedeutet nur, dass man der Funktion <tt>SerWrite</tt> einen String 
 * als Parameter uebergeben hat. <tt>SerWrite</tt> erwartet aber <tt>unsigned char *</tt> als Parameter. Fuer die Ausgabe von Strings ist die 
 * Funktion <tt>SerPrint</tt> besser geeignet. Man spart sich zudem das Zaehlen der auszugebenden Zeichen.
  \verbatim
  make: *** No rule to make target `test.hex', needed by `all'.  Stop. 
  \endverbatim
 * Dieser Fehler kann viele Ursachen haben. Meistens fehlt eine Header-Datei o.ae. Evtl. steht vor dieser Fehlermeldung noch ein
 * Hinweis warum das Übersetzen nicht funktioniert. Kann der Compiler z.B. die asuro.h nicht finden, stimmt wahrscheinlich 
 * der <tt>LIBPATH</tt> im Makefile nicht. Naeheres siehe unter Anpassen der Makefiles
 * Oft hilft auch ein Make Clean (durch Aufruf von Make-Clean.bat) und ploetzlich geht
 * das Übersetzen wieder ohne Fehler. 
 *
 * \section history  Versions History
 *
 * \verbinclude CHANGELOG
 *
 * \section authors Autoren der Bibliothek
 * 
 * \verbinclude AUTHORS
 *
 * \section authors_doc Autoren dieser Doku:
 *   m.a.r.v.i.n \n
 *   Sternthaler 
*/

