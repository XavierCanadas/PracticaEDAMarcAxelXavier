# Practica EDA




DATA STRUCTURES AND ALGORITHMS II, 2022-2023
PROJECT TITLE









STUDENT NAMES: Marc Guiu, Xavier Cañadas i Axel Del Val
STUDENT NUMBERS: U , U , U215091
11/06/2022

INTRODUCCIÓ
El present informe té com a objectiu proporcionar una visió del procés de desenvolupament d'una xarxa social, amb les funcions principals que ha de tenir, centrat en la creació de perfils, establiment d'amistats, publicació de contingut i compartició d'interessos de l'usuari.

La creació d'una xarxa social implica una sèrie de reptes tant tècnics com creatius. En primer lloc, és fonamental dissenyar una interfície fàcil d'utilitzar, que permeti als usuaris navegar i accedir a les diferents funcionalitats de manera intuïtiva i sense confusió. Per aconseguir tal objectiu, s'ha creat un menú principal senzill, amb les funcions principals i alguns menús secundaris per gestionar funcionalitats més concretes.

Aquest informe abordarà els aspectes clau del projecte de desenvolupament de la xarxa social, incloent-hi l'estructura de la base de dades, les funcionalitats implementades i els algoritmes emprats per optimitzar el rendiment del sistema. A més, es donarà especial atenció a les mesures de seguretat implementades, així com a les proves realitzades per garantir la qualitat del codi desenvolupat.

A més de destacar els assoliments aconseguits durant el procés de desenvolupament, s'identificaran els reptes enfrontats i les lliçons apreses al llarg del projecte. Finalment, s'oferiran recomanacions per a possibles millores i expansions futures, amb l'objectiu de continuar millorant l'experiència dels usuaris i adaptant-se a les necessitats canviant de la comunitat.





OBJECTIUS DEL PROJECTE 

OBJECTIUS OBLIGATORIS

Objectiu: Implementar una Llista (List) funcional com a part de les funcionalitats del projecte.
Resum: Es va implementar una Llista per a guardar les publicacions de cada usuari.
Estructures de dades utilitzades i el seu ús esperat: Es va crear la llista com a variable dins l’estructura de dades usuari, i en altres funcions es va usar per guardar les publicacions d’aquest.
Algorisme escollit i el seu comportament esperat: Es va utilitzar un algorisme d'inserció per a afegir elements a la Llista.
Limitacions de l'algorisme i la seva implementació: L'algorisme d'inserció té una complexitat de temps de O(1) per a la inserció en la Llista. No obstant això, una limitació d'aquesta implementació és que l'accés als elements no és tan eficient com en altres estructures de dades, ja que s’ha de recórrer sencer si no es coneix la posició de l’element.
Temps requerit per desenvolupar aquest objectiu: Aproximadament 5 minuts.
Ubicació: Fitxer "structs.h" línia 30
 
Objectiu: Implementar una Cua (Queue) funcional com a part de les funcionalitats del projecte i per gestionar les sol·licituds d’amistat
Resum: Es va implementar una Cua funcional per a gestionar les sol·licituds d’amistat de cada usuari.
Variables utilitzades i la seva finalitat: Es van fer servir variables com "frente" i "final" per a fer referència al primer i últim element de la Cua, respectivament. També es van fer ús d’altres variables auxiliars per a fer operacions d'encolament, desencolament.
Estructures de dades utilitzades i el seu ús esperat: Es va utilitzar un array dinàmic per a representar la Cua. Es van fer servir dos índexs "frente" i "final" per a indicar les posicions del primer i últim element de la Cua dins de l’array.
Algorisme escollit i el seu comportament esperat: Es va usar un algorisme d'encolament i desencolament per a gestionar els elements de la Cua. L'encolament consistia en afegir un element al final de la Cua, mentre que el desencolament eliminava l'element del davant i actualitzava l'índex "frente", en ambdós casos, actualitzant les variables “frente” i “final” amb els nous elements introduïts a la cua.
Limitacions de l'algorisme i la seva implementació: Una limitació d'aquesta implementació és que no es poden ignorar sol·licituds d’amistat, un cop t’apareix l’has d’acceptar o rebutjar, ja que sinó, la sol·licitud es queda a la variable “frente” i impossibilita accedir a les altres sol·licituds.
Possibles millores: Es podria implementar una funció “ignorar”, que desencoles el primer element i l’encoles novament a la última posició, per tal de poder postergar la decisió sobre si acceptar o no la sol·licitud.
Temps requerit per desenvolupar aquest objectiu: Aproximadament 2 hores.
Ubicació: Fitxer "cola.c", “cola.h”.
 
Objectiu: Implementar l'algorisme de cerca (hashing)
Resum: Es va implementar funcionalment l'algorisme de hashing per realitzar cerques dins d’una taula hash.
Variables utilitzades i la seva finalitat: Es va utilitzar la variable “clau” per implementar la funció.
Estructures de dades utilitzades i el seu ús esperat: Es va fer servir una taula hash que conté un valor que serveix com a clau, calculat a partir del contingut d’aquella posició.
Algorisme escollit i el seu comportament esperat: Es va utilitzar l'algorisme de cerca a partir de la clau, es busca dins de la taula hash i un cop trobat es retorna el valor que té associat, en el cas  present, un usuari.
Limitacions de l'algorisme i la seva implementació: Una limitació de l'algorisme són les col·lisions, ja que dos claus diferents poden generar el mateix índex en aplicar la funció de hashing, donant lloc a un conflicte. És per això, va ser necessari implementar una tècnica de solució de conflictes, en aquest cas s’ha usat “linear proving” que busca la següent posició per mirar si està lliure. També si s’intenta afegir un nou objecte amb una clau igual a una que ja està a la taula la funció de hashing() ho té en compte i retorna un error. 
Temps requerit per desenvolupar aquest objectiu: Aproximadament 3 hores.
Ubicació: Fitxer "taulaHash.c", funció: hashing()

Objectiu: Implementar l'algorisme de cerca (linear search)
Resum: Es va implementar funcionalment l'algorisme de cerca lineal per a buscar elements dintre d’una string, la cadena conté un array de JsonObjects. La string s’extreu del fitxer .json que conté totes les dades
Variables utilitzades i la seva finalitat: Com a variables, a part d’un índex per iterar i recórrer la llista per tal de buscar els valors desitjats, es van fer servir una sèrie de comptadors, ja que per poder llegir correctament la string i interpretar el format .json s’ha portat un recompte dels caràcters de la string. Una vegada trobat l’objecte que correspon a l’índex que es volia, s’extreu l’objecte.
Estructures de dades utilitzades i el seu ús esperat: Es va utilitzar una estructura JsonObject, que definia el tipus de dades que podem trobar dins l’arxiu .json.
Algorisme escollit i el seu comportament esperat: Es va utilitzar l'algorisme de cerca lineal, que recorre l’array en cerca del valor desitjat.
Limitacions de l'algorisme i la seva implementació: L'algorisme de cerca lineal requereix que es recorre la llista per “força bruta”, la qual cosa no és massa eficient; tot i això, en alguns casos on les dades estan desordenades és la millor opció.

Objectiu: implementar algoritme de sorting (insertion sort)
Resum: Es va implementar funcionalment l'algorisme de sorting per ordenar la llista de tendències (paraules més usades a les publicacions) de major a menor. Per ordenar-les hem usat l’algoritme InsertionSort.
Variables utilitzades i la seva finalitat: s’ha fet servir dos nombres enters que s’utilitza com a comptadors que s’actualitzaran dintre dels bucles que hi ha. també punter de Tendència auxiliar per fer els canvis de posició.
Estructures de dades utilitzades i implementació de l’algoritme: l’algoritme recorre un array de punters de tendències per fer les comparacions. Primer hi ha un bucle for que recorre tot l’array i dintre hi ha un bucle while que comprovarà si un valor és més gran que l’altre i si ho és fa el canvi de posició.
Limitacions de l'algorisme i la seva implementació: L’algoritme d'insertionsort és simple d’implementar però, per contra, té que en el pitjor dels casos el temps de complexitat és O(n^2)

Objectiu: Implementar un Diccionari (Dictionary) funcional com a part de les funcionalitats del projecte.
Resum: Es va implementar un Diccionari funcional en forma de taula hash, per guardar els usuaris i les seves dades, generant la clau a partir del nom d’usuari.
Variables utilitzades i la seva finalitat: Es van utilitzar variables com "clau" i "valor" per a emmagatzemar els usuaris amb la seva corresponent clau. Es van fer servir altres variables auxiliars per a efectuar operacions com la cerca, l'afegit i l'eliminació d'elements del Diccionari.
Estructures de dades utilitzades i el seu ús esperat: Es va fer ús d’un array dinàmic per a emmagatzemar les parelles clau-valor, per tal de no malbaratar memòria, així, quan és necessari es reserva més memòria per als nous usuaris.
Algorisme escollit i el seu comportament esperat: Es va utilitzar una sèrie de funcions per crear, ampliar, buscar i diverses funcionalitats més dins la taula hash.
Limitacions de l'algorisme i la seva implementació: Les taules de dispersió poden requerir una quantitat significativa de memòria per a emmagatzemar les dades i les estructures auxiliars, com ara l'array de dispersió o les llistes enllaçades per a la resolució de col·lisions. A mesura que la quantitat de dades augmenta, és possible que sigui necessari allotjar més memòria per a mantenir un rendiment acceptable..
Temps requerit per desenvolupar aquest objectiu: Aproximadament 5 hores.
Ubicació: Fitxer "taulaHash.c" i “taulaHash.h”.

A més, s’ha aconseguit crear un entorn de treball amb GitHub per tal de treballar totes les persones involucrades en el projecte d’una manera molt més còmoda i senzilla. Actualitzant el codi al repositori cada cop que s’actualitzava, creant diferents branques quan era pertinent per tal d’evitar conflictes i de no implementar funcions al codi principal fins que no fossin plenament operatives i llistant les tasques que quedaven pendents per tal d’una millor organització.
També, tal com es manava en els objectius obligatoris, tot el codi està comentat amb explicacions dels fragments més importants o difícils d’entendre, així com explicacions de les funcions principals i del seu comportament general.



OBJECTIUS DESITJABLES
Objectiu: Llegir dades d'una font externa com un fitxer de text .JSON (No implica l'emmagatzematge de dades).
Resum: Es va implementar una sèrie de funcions per a llegir i guardar dades des d'un fitxer de text en format .JSON i processar-les en el programa per tal de crear una memòria dels usuaris.
Variables utilitzades i la seva finalitat: S’han utilitzat diverses variables, per classificar els tipus diferents de dades que pot contenir l’arxiu i en la manera en la que aquestes poden estar guardades (enters, arrays, strings...).
Estructures de dades utilitzades i el seu ús esperat: Es va utilitzar una estructura de dades per classificar les diferents variables mencionades prèviament. Es va fer per poder llegir correctament les dades i poder-les usar adequadament al programa.
Algorisme escollit i el seu comportament esperat: Es va utilitzar un algorisme per a llegir i analitzar el fitxer .JSON, classificant les dades segons el seu tipus i implementant-les en el seu espai del codi. L'algorisme esperat era una lectura eficient i una conversió precisa de les dades.
Limitacions de l'algorisme i la seva implementació: L'algorisme de lectura de fitxers .JSON podia ser susceptible a errors si el format del fitxer no era vàlid o si les dades no es corresponien amb l'estructura esperada. 
Possibles millores: Es podria millorar l'algorisme de lectura de fitxers .JSON implementant mecanismes de validació de format, gestió d'excepcions…
Temps requerit per desenvolupar aquest objectiu: Aproximadament 10 hores.
Ubicació: Fitxer "json.c”, “json.h”, “dadesJson.c” i “dadesJson.h”.



OBJECTIUS D’EXPLORACIÓ
Objectiu: Implementar les funcionalitats de lectura i emmagatzematge de dades (informació dels usuaris i els seus contactes, i qualsevol altra informació addicional) des d'un fitxer extern (.json).
Resum: Es va implementar la funcionalitat per a llegir i emmagatzemar les dades des d'un fitxer .json, incloent la informació dels usuaris i els seus contactes. Les dades es van processar i utilitzar en el programa.
Variables utilitzades i la seva finalitat: S’han utilitzat diverses variables, per classificar els tipus diferents de dades que pot contenir l’arxiu i en la manera en la que aquestes poden estar guardades (enters, arrays, strings...).
Estructures de dades utilitzades i el seu ús esperat: Es va utilitzar una estructura de dades per classificar els diferents tipus de dades que hi pot haver i guardar-les de la forma pertinent.
Algorisme escollit i el seu comportament esperat: Es va utilitzar un algorisme per a llegir i processar les dades del fitxer .json, convertint-les en estructures de dades utilitzables i llegibles dins del codi. A l'hora d'emmagatzemar les dades, es va utilitzar l'algorisme per guardar les dades actualitzades en el fitxer. L'algorisme esperat era una lectura i un emmagatzematge eficients amb una conversió precisa de les dades.
Limitacions de l'algorisme i la seva implementació: L'algorisme de lectura i emmagatzematge de fitxers .json podia ser susceptible a errors si el format del fitxer no era vàlid o si les dades no es corresponien amb l'estructura esperada. 
Possibles millores: Es podria millorar l'algorisme de lectura i emmagatzematge de fitxers .json implementant mecanismes de validació de format, gestió de conflictes de dades i una millor manipulació de les estructures de dades. També es podria fer ús de llibreries externes per a la manipulació de fitxers .json.
Temps requerit per desenvolupar aquest objectiu: Aproximadament 13 hores.
Ubicació: Fitxer "json.c”, “json.h”, “dadesJson.c” i “dadesJson.h”.





SOLUCIÓ

Arquitectura del sistema
A continuació veurem el diagrama de com funciona la nostra aplicació i les seves funcionalitats principals. Diagrama:
![D1](https://github.com/XavierCanadas/PracticaEDAMarcAxelXavier/assets/32838581/271a69db-d887-4b43-b4c1-a9eadfaaa1e8)

Tot el diagrama esta  en torn al menú el qual disposa de 4 funcionalitats principals i dues extres. Aquest menú es troba dins un bucle while el qual permet accedir a diferents funcionalitats i treballar dins d’ell el temps necessari fins que l’usuari desitgi marxar. Extern al Menú troben dos blocs Json i Filtres.
Json: Per a poder treballar sobre la xarxa necessita un sistema que guardi la informació un cop el codi ha finalitzat. A l'iniciar el menú agafarem tota la informació corresponent al json i la guardem en la memòria en una taula Hash. Aquests json està enllaçat amb un bloc d'errors.
Errors(Json): Són diverses funciona que verifiquen que tota informació es copia i es guarda correctament sense solapar altres “slots” d’informació o guardar caràcters no vàlids, entre d’altres, d’aquesta manera ens assegurem que el .json copiï la informació el millor possible i en cas d'error sens informarà.
Filtres(Menú): El meu és un dels punts més crítics del codi doncs és on l’usuari interactua directament amb les diferents funcions per a poder evitar possibles errors per part de l'usuari en introduir dades no desitjades els filtres s’asseguren de reclamar la informació més específicament en cas que la d’entrada no sigui la correcta.
Un cop tenim clars aquests conceptes explorarem cada funcionalitat del menú.
Nou Usuari: Dins aquest bloc volem afegir un usuari a la nostra memòria el qual, igual que en el cas del menú, el bloc es relaciona amb “Noves funcions” per a ingressar els valors.
Noves Funcions: Aquí situem totes les funcions que interactuen amb la memòria per a poder guardar corresponentment els valors de l'usuari sense crear cap conflicte, per a poder evitar error usem un sistema de filtres similar al del menú.
Filtres (Nou Usuari): Similar al cas del Menú aquest bloc filtra la informació que s’ha de guardar a l'estructura de l'usuari per evitar faltes. 
Llista Usuaris: En aquest bloc se situen les funcions que recorren tota la memòria actual en cerca de tots els usuaris que hi ha per a poder mostrar el seu nom per pantalla.
Èxit: Per a poder guardar d’informació correctament dins el codi disposem d’un sistema que abans de finalitzar el programa agafa tota la informació guarda en la taula hash i la traspassa al .json on des d'allà es guardarà (així no es perd un cop ha finalitzat el codi). 
Escollir Usuaris: Com a opció més completa del menú principal situem la possibilitat d’accedir a informació més específica d’un usuari, per això se n'obre un altre menú complet amb diverses possibilitats com: Gestionar Sol·licituds, fer publicació, veure publicacions i eliminar usuari, per a poder guardar la informació corresponent a les sol·licituds es fa mitjançant una Cua, igual que en l'apartat del menú aquest també compta amb el seu sistema de filtres
Filtres (Escollir Usuaris): Filtra la informació donada per l'usuari per no tindre conflictes a l'hora d'introduir dades tant en el submenú com als seus blocs adjacents
Cua: Per a poder gestionar les sol·licituds d’amistat disposem d’una cua que controla les sol·licituds rebudes de cada usuari.
Errors (Cua): per tal de no crear conflictes en la cua amb la gestió de sol·licituds tenim una sèrie de funcions que verifiquen l’estat de la cua.
Gestionar Sol·licituds: S'obre un llistat amb totes les sol·licituds de la cua i se’t pregunta si es volen acceptar o eliminar individualment.
Fer Publicació: L'usuari té permès realitzar una publicació de 120 caràcters que es guarda en un array dinàmic així com el número de “m’agrades” que aquesta te i la seva data de publicació.
Veure Publicacions: Es llisten les publicacions guardades amb el nom del publicant, la data de publicació i el nombre de m’agrades, això sorgeix del bloc: Array Publicació, també disposem d’una secció de tendències per veure les paraules més freqüents.
Array Publicació: Usa una array per guardar totes les publicacions de cada usuari per després poder ser mostrades en l’ordre corresponent.
Tendència: Usa una taula hash per filtrar les paraules més freqüents de les publicacions mostrant en ordre les més  citades.
Per veure totes o les teves publicacions pròpies, aquestes es mostren amb un nombre de m’agrada, la data de publicació i qui l’ha publicat. 
Eliminar Usuari: Dona l'opció d'eliminar tot un usuari amb les seves dades corresponents com: publicacions, correu de contacte, edat, amics, etc.
Amb aquest diagrama podem donar per finalitzat els principals blocs del codi que expliquen i justifiquen el seu funcionament.



Gestió d’Errors
Com hem vist anteriorment, la nostra xarxa social es basa en un sistema dins d'un menú en bucle. La principal causa d’errors és degut a no ingressar correctament valors al menú o a l’hora d'introduir alguna string o nombre enter. Per això, una de les nostres principals maneres de facilitar la solució dels errors, és mitjançant filtres,  els quals, a l’hora de reclamar un input a l’usuari s'assegura que el que introdueix és correcte. Algun exemple d'això seria el fet d'escriure un mail que contingui una @ o que en introduir un número no permet introduir una lletra i el valor ha de ser un enter. Això provoca que la gran majoria d'errors que es poden produir per l'usuari quedin reduïts a casos molt excepcionals . Algun altre punt important es dona a l’hora de carregar, afegir i treure informació de: taules hash, cues, arrays, etc. Per a poder solucionar això ens ajudem de valors predeterminats (amb #define) per a poder saber de quin tipus d'error es tracta, algun exemple d'aquest pot ser ERROR_JSON CONFIRMAR o CANCELAR. Amb això, ens assegurem que el sistema no retorna un error desconegut. L'ús del nul també és bastant recurrent per provar que no hi ha cap error en trobar una taula buida o plena, des d'aquí ens ajudem amb prints per indicar a l'usuari el possible error. En el nostre cas usem l'estructura de control switch amb case/default i també ens ajudem del default en cas de no accedir a cap opció valida.



Disseny del model de dades
El mètode per a guardar la informació de l'usuari és la següent:
![D2](https://github.com/XavierCanadas/PracticaEDAMarcAxelXavier/assets/32838581/743c1f80-f631-4f4c-99e4-81357300eb92)

Inicialitzar Taula Hash: S’inicia la taula hash amb els valors del Json o sinó amb una taula buida
Guardar Usuari: Per a guardar un nou usuari es necessita el seu nom i una clau corresponent (que es l’objecte)
Funció NouUsuari: Per afegir els usuaris a la taula s’usa aquesta funció  que conté totes les funcionalitats següents
Càlcul Hash: Calcula el valor del hash del usuari
Càlcul índex: Un cop el valor de hash de usuari està calculat s’usa per a trobar un índex disponible dins la memòria
Linear Proving: En cas de col·lisió s’usa el linear proving per trobar un altre espai en memòria disponible
Inserta Objecte Usuari: Guarda la informació de l'usuari en l’espia corresponent de memòria
Fi: Aquí finalitzen les funcions i l’usuari ha sigut guardat correctament a memòria
Aquest és el mètode per registrar i guardar un nou usuari. Per a mantenir aquests canvis al final del codi, s’ha de tindre en compte el comentat en els punts anteriors sobre la informació retornada al json. 



Descripció i tractament del conjunt de dades
Abans d’inicialitzar el menú es crida a la funció llegirFitxer() la qual es basa en cerca tota la informació dins l’arxiu json i guardar-la en una llista dinàmica, aquesta llista la podem situar en el nostre codi dins un objecte (JsonObject)  tipus root. Un cop hem extret les dades de l'arxiu json i estan a la llista cridem la funció usuarisJson() per agafar tota la informació de la llista i passar-la a una taula hash, que ha estat prèviament inicialitzada. Dins la taula es guardaran els usuaris, el JsonObject i l’array amb les publicacions corresponent a cada usuari. Per a tots els usuaris del fitxer json hi ha una sèrie de funcions internes que serveixen desserialitzar les dades del json i per guardar certa informació a la taula hash. Les funcions convertirJsonUsuari() i guardarUsuari() son les encarregades d’aquest procés. A més la funció convertirJsonUsuari() es trunca amb la funció convertirPublicacioJson() que guarda la informació de les publicacions de cada usuari als arrays que contenen totes les publicacions i les publicacions d’un mateix usuari. Aquest és el sistema que usem per a poder guardar i moure les dades dels usuaris al llarg de tot el codi. 





Referències
En aquesta secció troben algunes de les referències que hem usat per desenvolupar el projecte, podem veure pàgines web com w3schools, fòrums d’interacció com stack overflow i vídeos de youtube entre d’altres, el principal ús d'aquestes referències ha sigut per la implementació de: la taula hash, la lectura de arxius json, algún mètode per corregir possibles errors i alguna llibreria puntual. També, per gestió de problemes més concrets o menys comuns, hem fet servir eines com chat gpt o Bing Chat per a concretar el nostre error i poder-lo adaptar  el màxim possible al nostre problema.
https://www.w3schools.com/whatis/whatis_json.asp
https://www.w3schools.com/c/index.php
https://stackoverflow.com/
https://stackoverflow.com/questions/56531372/what-is-error-0xc0000005-and-how-do-i-fix-it
https://blog.jetbrains.com/clion/2023/01/support-for-vcpkg-in-clion/
https://www.youtube.com/watch?v=wg8hZxMRwcw
https://www.youtube.com/watch?v=hJbDwpSdGkM
https://www.youtube.com/watch?v=1_mnhZ20Vus
https://stackoverflow.com/questions/6844739/implement-a-hash-table
https://github.com/jamesroutley/write-a-hash-table
https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects/JSON
https://www.youtube.com/watch?v=mnIvV-IBI7Y
https://www.geeksforgeeks.org/cjson-json-file-write-read-modify-in-c/
https://www.youtube.com/watch?v=b45tE0kkuAA
https://stackoverflow.com/questions/6673936/parsing-json-using-c
https://github.com/rbtylee/tutorial-jsonc/blob/master/tutorial/index.md
https://www.youtube.com/watch?v=U8JBoZmxH_o
https://www.tutorialspoint.com/c_standard_library/time_h.htm
https://www.youtube.com/watch?v=_i2faEmp2lo
https://www.youtube.com/watch?v=rH1BVWFmahY
https://www.youtube.com/watch?v=Ra6p-Bmajlw
https://www.digitalocean.com/community/tutorials/queue-in-c
https://stackoverflow.com/questions/4184954/are-there-standard-queue-implementations-for-c
https://openai.com/blog/chatgpt
https://www.microsoft.com/en-us/edge/features/bing-chat?form=MT00D8



