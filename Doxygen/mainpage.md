Hoofdpagina {#mainpage}
----------- 
<span style="font-family:'Corbel'; font-size:10pt; color:green">**Over deze pagina.** Deze pagina (..\Doxygen\\<b>mainpage.md</b>) is een .md markdown-bestand, gemaakt met Typora (gratis download: https://typora.en.uptodown.com/windows/download), aangevuld met html (markdown kun je mixen met html). Zo kun je redelijk simpel zelf een hoofdpagina maken, die Doxygen dan gebruikt (ipv de standaard Doxygen-mainpage); dit wordt dan deze **index.html**.<br>
Het is geïnstalleerd via de Doxygen Wizard, tab [Expert mode]:<br>
&nbsp;&nbsp;&nbsp; INPUT                  = mainpage.md<br>
&nbsp;&nbsp;&nbsp; USE_MDFILE_AS_MAINPAGE = mainpage.md<br>   Bestand <b>..\Doxyfile</b> is de doxygen projectfile. De outputmap van doxygen is <b>..\Doxygen\html</b><br>NB. Als je deze pagina verandert, moet je uiteraard wel eerst doxygen runnen (via tab [Run]) om aanpassingen te zien.
</span>



<span style="font-family:'Corbel'; font-size:12pt;"> 
<!-- 
*(Corbel 12pt is nu het standaard font)* 
</span>

-->

<br>

<h1 style="font-family:'Corbel';">
FreeRTOS documentatie</h1>

Het realtime OS FreeRTOS hebben we gekozen omdat het gratis is, open source is, veel gebruikt wordt, relatief eenvoudig is én... omdat het uitgebreid gedocumenteerd is. Dat betekent dat het lesmateriaal grotendeels online te vinden is (en niet op powerpoints herhaald hoeft te worden).  De belangrijkste bronnen zijn: 

<ul style="font-family:'Corbel';">

<li>**FREERTOS hoofddocumentatie**: de [API-Reference](https://www.freertos.org/a00106.html). <u>Bij het ontwikkelen en de lessen moet je die er constant bij houden.</u> </li>
<li>[FreeRTOS boeken en pdf's](https://www.freertos.org/Documentation/RTOS_book.html)</li>
</ul>

<br>
<h1 style="font-family:'Corbel';">
Installatie: hoe krijg je de applicatie aan de praat?</h1>
<ul style="font-family:'Corbel';">
<li>Installeer het project FreeRTOS_GPS_407 in [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).
<ul style="font-family:'Corbel';font-size:11pt;">
    <li>zip-bestand downloaden en uitpakken in map</li>
    <li>STMCubeIDE starten</li>
    <li>Nieuwe Workspace</li>
    <li>File -> Import -> General -> Atollic TrueSTUDIO Project</li>
    </ul>
    </li> 
<li>Sluit het ARM-bordje aan via USB.</li>
<li>Flash de applicatie naar het ARM-bordje (bv. via debug).</li>
<li>Download en installeer op je laptop een terminal-rs232-programma, bv. terminal.exe, of TeraTerm of iets anders. Zet de comport op 115200,n,8,1. Zet bij Transmit [CR]=[CR]+[LF] (dan wordt na <Enter> automatisch een Linefeed-character toegevoegd. </li>
<li>Reset het ARM-bordje en als het goed is zie je nu tekst verschijnen op het terminalprogramma. </li>
</ul>
<br>

<h1 style="font-family:'Corbel';">
Werking: wat doet de applicatie?</h1>
De applicatie freeRTOS_GPS_407 (geschikt voor ARM Cortex 407) is een werkende freeRTOS-applicatie, met de volgende doelen:

<ul style="font-family:'Corbel';">
<li>**didactisch**. Het toont de opzet en werking van verschillende freeRTOS-mechanismen. Soms is in de code op didactische gronden gekozen voor een of ander mechanisme, terwijl dit ook anders opgelost had kunnen worden.</li>
<li>**als basis (skeleton) om verder uit te werken voor het project**. Nu hoef je als student niet alles from scratch zelf te bouwen. Het is wel aan jou om goed te kijken welke onderdelen van de code je voor jouw applicatie kunt gebruiken en welke je kunt verwijderen.</li>
</ul> 

Als de de installatie gelukt is (zie boven), en het ARM-bordje communiceert met je laptop via een terminalprogramma, dan zie je dit:

<ul style="font-family:'Corbel';">
<li>Het display toont het versienummer (main.c, admin.c)</li>
<li>De applicatie stuurt de rij ledjes aan (ledjes.c).</li>
<li>Het blauwe ledje wordt elke halve seconde aan- en uitgezet (admin.c).</li>
<li>De applicatie leest de ARM-keys in (ARM_keys.c, en stm32f4xx_it.c). Na elke toets zie je de ledjes rood, oranje en groen oplichten.</li>
<li>De applicatie heeft een user interface via de UART (main.c). Het menu geeft keurig aan welke toetsen gebruikt kunnen worden (UART_keys.c). </li>
<ul  style="list-style-type:none;">
<li>**MENU:**</li>
<li>**0**:  *On/Off ALL test output.* Bij '0'\<enter\> krijg je of ALLE of GEEN testoutput te zien.</li>
<li>**1**:  *On/Off LEDS output.* Bij '1'\<enter\> gaan de LED-tasken WEL of GEEN output genereren.'</li>
<li>**2**:  *On/Off ARM_keys output.* Bij '2'\<enter\> gaan de ARM-keys-tasken WEL of GEEN output genereren.'</li>
<li>**3**:  *On/Off UART_keys output.* Bij '3'\<enter\> gaan de UART-keys-tasken WEL of GEEN output genereren.'</li>
<li>**4**:  *On/Off STUDENT output.* </li> Toets '4'\<enter\> kun je gebruiken voor je eigen testoutput. 
<li>**5**:  On/Off GPS-data output (mits een GPS-receiver aangesloten is).</li>
<li>**d**:  *change Delay time.* De LED-tasks werken met een delay time van default 200 MSecs tussen elke LED-setting. Zo kun je zien wat er gebeurt. 
Voorbeeld: 'd,50'\<enter\> verkleint de default delay time naar 50 MSecs, dus de ledjes gaan 4x zo snel.</li>
<li>**m**:  *show Menu*. Dit menu wordt getoond.</li> 
<li>**p**:  *change Priority of task*. Met 'p'[,tasknummer, prioriteit]\<enter\> kun je de prioriteit van een task aanpassen en zien wat er gebeurt. 
Voorbeeld: 'p,7,20' verandert de prioriteit van task 7 naar 20.</li>
<li>**t**:  *display Task-data.* Na 't'\<enter\> krijg je de gegevens per task te zien, zoals: nummer, prioriteit en geheugen (stack) gebruik. Zo kun je code optimaliseren en zien of een taak dreigt te weinig geheugen te krijgen...</li>
</ul>
</ul>

<br>
<h1 style="font-family:'Corbel';">
Design: overview van de applicatie</h1>

Hieronder zie je het *graphical design* van de applicatie (gemaakt in Powerpoint).<br> 
Het doel van het graphisch design is om snel inzicht te krijgen in de samenhang en werking van de applicatie. Daarom zijn alleen de belangrijkste zaken weergegeven. (Er is bijvoorbeeld ook een software-timer (timer.c), maar die is in het design niet weergegeven.)

<img src="../freeRTOS_GPS_407_design.png" alt="FreeRTOS_GPS design" width="100%"/>

De verschillende elementen:
<ul style="font-family:'Corbel';">
<li>*I/O-laag.* Links zie je de ARM-inputs (UART en ARM-toetsen), rechts de ARM-outputs (UART, LCD, Buzzer, RGBY-leds en de LED-rij). De applicatie gebruikt deze I/O's om te laten zien hoe multitasking werkt met de FreeRTOS-mechanismen. </li>
<li>*Tasks.* Elke task bestaat uit een gekleurd blokje met titel en 'sourcecode'. Bijbehorende tasks zijn per kleur gegroepeerd. Zoals je ziet zijn er 3 task-groepen:</li>
<ul>
<li>*Blauw.* Eigenlijk is dit de User Interface via de UART. Het leest en interpreteert de commando's die de gebruiker via een terminalprogramma intikt. Daarnaast schrijft het naar de gebruiker het menu en het programmaverloop.</li>
<li>*Oranje.* Deze groep leest en interpreteert de ARM-toetsen. </li>
<li>*Groen.* Deze groep behandelt de led-rij. </li>
</ul>
<li>*FreeRTOS-mechanismen.* De inter-proces-communicatie (tussen de tasks dus) met FreeRTOS-functies is ook in kleur weergegeven. Zo zie je welke tasks welke data naar elkaar sturen. </li>
<li>*Source-files.* De gestippelde blokjes geven aan in welke c-files de tasks gecodeerd zijn. </li>
<li>*IRQ.* Niet alle blokjes zijn tasks, maar functies, in dit geval interrupt handlers. Deze functies worden door STM32 gegenereerd op het moment dat je op de processor (.ios) hardwarematig een interrupt definieert. Die functie is dan nog leeg, en aan de programmeur om verder 'in te vullen'. In deze applicatie zijn de ARM-toetsen en de UART-input aan interrupts gekoppeld.</li>
</ul>

<br>
<h1 style="font-family:'Corbel';">
FreeRTOS en multitasking, de RTOS-basics</h1>

De applicatie is bedoeld om de werking van FreeRTOS te laten zien: het OS en de functionaliteiten daarvan. In het design hierboven zie je ze in de tasks beschreven in hun c-functieprototypes. 

Ze zijn allemaal keurig beschreven op de FreeRTOS-site (de [API-Reference](https://www.freertos.org/a00106.html) en  [boeken en pdf's](https://www.freertos.org/Documentation/RTOS_book.html)). 

Laten we eerst eens kijken wat een multitasking OS is en hoe die werkt. NB. Ik ga hier nu niet deze referenties herhalen, maar ga alleen globaal in op de basis FreeRTOS-zaken als multitasking, synchronisatie- en communicatiemechanismen en bijbehorende functies. 

<ul style="font-family:'Corbel';">
<li>(Terzijde) **FreeRTOS en CMSIS**. <br>ARM heeft, om zo onafhankelijk mogelijk te zijn van RTOS en processorkeuzes, een eigen softwarelaag gemaakt bovenop FreeRTOS: [RTOS2](https://arm-software.github.io/CMSIS-FreeRTOS/General/html/index.html). '*Using this software pack, users can choose between a native FreeRTOS implementation or one that is adhering to the CMSIS-RTOS2 API and using FreeRTOS under the hood.*' In de praktijk betekent dit dat zo'n beetje elke FreeRTOS-functie een RTOS2-variant heeft. RTOS2-functies zijn te herkennen aan het voorvoegsel '*os*', zoals *osThreadNew()* of *osDelay()*. Om verwarring te voorkomen gebruiken we in deze applicatie zoveel mogelijk 'native' FreeRTOS-functies. Hier en daar gebruiken we RTOS2-functies, omdat die door STM32CubeIDE automatisch gegenereerd worden, die houden we dus voor het gemak in stand.<br></li><br>
<li>**[Multitasking](https://www.freertos.org/implementation/a00004.html)**. <br>FreeRTOS is een realtime [multitasking](https://www.freertos.org/implementation/a00004.html) operating system. *Realtime* betekent dat code gegarandeerd binnen een bepaalde tijd, of op een bepaalde tijd, uitgevoerd wordt. *Multitasking* of multithreading betekent dat meerdere taken (tasks of threads genoemd) schijnbaar 'tegelijkertijd' uitgevoerd worden, parallel als het ware. Dat kan natuurlijk niet echt, want er is maar 1 processor. Wat er gebeurt, is dat het OS zo snel tussen tasks swicht, dat het lijkt of taken inderdaad gelijktijdig uitgevoerd worden. Dit heet **context switch**, waar we zo op door gaan.<br>
<img style="margin-left:30px;" src="./../rtos.png" alt="realtime_os" width="50%"/>
<br></li><br>
<li>**Tasks** (of **threads**). <br>Een [task](https://www.freertos.org/taskandcr.html) is qua code niets anders dan een functie met een oneindige while(1)-loop.<br> '*Each task executes within its own context with no coincidental dependency on other tasks within the system or the RTOS scheduler itself. Only one task within the application can be executing at any point in time and the real time RTOS scheduler is responsible for deciding which task this should be. The RTOS scheduler may therefore repeatedly start and stop each task (swap each task in and out) as the application executes. As a task has no knowledge of the RTOS scheduler activity it is the responsibility of the real time RTOS scheduler to ensure that the processor context (register values, stack contents, etc) when a task is swapped in is exactly that as when the same task was swapped out. To achieve this each task is provided with its own stack. When the task is swapped out the execution context is saved to the stack of that task so it can also be exactly restored when the same task is later swapped back in.*' <br>Dus, een task is een functie die zich gedraagt als een aparte applicatie, met zijn eigen geheugenruimte. De **scheduler** van het OS switcht tussen deze tasks, wat [context switch](https://www.freertos.org/implementation/a00006.html) heet. <br>
<img style="margin-left:30px;" src="../context_switch.png" alt="context switch" width="25%"/>
<br>Sommige tasks zullen belangrijker zijn dan ander, dus wil je dat die belangrijke tasks meer processortijd krijgen. Dat wordt gedaan met prioriteiten. Een task met een hogere prioriteit krijgt dan meer processortijd van het OS. </li>
<ul>
<li>Een task kan de volgende status hebben:</li>
<ul>
<li>**Running:** deze tasks is aan de gang. Het OS geeft hem de beurt, en de task heeft de processor tot zijn beschikking.</li>
<li>**Ready:** deze task is klaar om 'te gaan' (hij is niet blocked, noch is hij suspended) maar het OS laat een andere task, bv. met een hogere prioriteit, runnen.</li>
<li>**Blocked / waiting:** een task is blocked als hij wacht op een event (bv. een bericht of mutex) van een andere task. </li>
<li>**Suspended:** deze task is op 'pauze' gezet. Het OS negeert deze tasks, totdat hij weer op *Resume* gezet is.</li>
</ul>
</ul>
<ul>
<li>Code.</li>
<ul>
<li>*Een task aanmaken:* taskhandle = [osThreadNew()](https://arm-software.github.io/CMSIS_5/RTOS2/html/group__CMSIS__RTOS__ThreadMgmt.html#ga48d68b8666d99d28fa646ee1d2182b8f)  (De FreeRTOS-variant is [xTaskCreate()](https://www.freertos.org/a00125.html))<br>Om een task aan te kunnen maken heeft het OS meerdere argumenten nodig, zoals: de naam van de functie, de hoeveelheid geheugen die je de taak meegeeft, de prioriteit die je hem toekent en nog wat zaken. </li>
<li>*Taskpriority bepalen:* [vTaskPrioritySet(handle, prio)](https://www.freertos.org/a00129.html)</li>
<li>*Task vertragen (context switch afdwingen):* [vTaskDelay(clockticks)](https://www.freertos.org/a00127.html). Wij gebruiken meestal: [osDelay(clockticks)](https://arm-software.github.io/CMSIS_5/RTOS2/html/group__CMSIS__RTOS__Wait.html#gaf6055a51390ef65b6b6edc28bf47322e). Wat ook kan: [taskYIELD()](https://www.freertos.org/a00020.html#taskYIELD), hiermee forceer je een context switch.</li>
<li>*Zie:* admin.c, ledjes.c <br></li><br>
</ul>
</ul>

</ul>

<br>
<h1 style="font-family:'Corbel';">
FreeRTOS: de mechanismen in de applicatie</h1>

<ul style="font-family:'Corbel';">

<li>**Algemeen.** Voor de synchronisatie en communicatie *tussen* tasks gebruiken we 4 mechanismen: *mutexes* voor <u>synchronisatie</u>, en *notifications, events* en *queues* voor <u>communicatie</u>.<br></li><br>

<li>**[Mutual Exclusion Semaphores (mutexes)](https://www.freertos.org/a00113.html).** <br>Met een Mutual Exclusion Semaphore, meestal **mutex** genoemd, zorg je ervoor dat een 'shared resource' (denk aan: printer of wc of ledjes) niet tegelijkertijd door meerdere processen gebruikt kan worden (hence: mutual exluded). Bij een printer wil je dat eerst de ene printjob afgehandeld wordt voordat de volgende printjob aan de beurt komt. Bij een wc wil je liever niet dat een ander van het toilet gebruik maakt terwijl jij er net op zit. Anders gezegd: je wil dat dit soort 'gedeelde resources' *gesynchroniseerd* kunnen worden. Bij een wc is dit het slotje op de deur: rood betekent 'bezet', groen betekent: 'vrij'.<br> 
<img style="margin-left:30px;" src="../vrij-bezet.png" alt="mutex" width="15%"/>
<br>In de applicatie wordt een *mutex* gebruikt om te ledjes te synchroniseren. Kijk in het design naar het groene gedeelte. Daar zie je dat meerdere tasks tegelijkertijd naar de ledjes willen schrijven. Om ervoor te zorgen dat ze niet allemaal dwars door elkaar gaan rammen, is er een mutex aangemaakt. Een task kan pas naar de leds schrijven als de 'deur op groen' staat. De task wacht op het OS tot hij erin mag. Zolang de mutex 'bezet' is door een andere task, geeft het OS de beurt aan een andere task. De wachtende task blijft dan [blocked](https://www.freertos.org/RTOS-task-states.html).</li>

<ul>
<li>*Aanmaken:* handle = [xSemaphoreCreateMutex();](https://www.freertos.org/CreateMutex.html)</li>
<li>*Aanvragen (ik wil erin...):* [xSemaphoreTake(handle);](https://www.freertos.org/a00122.html)</li>
<li>*Vrijgeven (ik ben klaar...):* [xSemaphoreGive(handle);](https://www.freertos.org/a00123.html)</li>
<li>*Zie:* admin.c, ledjes.c <br></li><br>
</ul>
<li>**[Notifications.](https://www.freertos.org/RTOS-task-notification-API.html)**<br>Met notifications maak je een virtuele verbinding naar een andere task. De ontvangende task wacht (en is dus *'blocked'*) op het bericht van de versturende taak. Dat bericht kan een signalering zijn (net als 'tikkertje'), of een waarde. Om een notificatie te doen, moet de task die stuurt eerst de taskhandle van de ontvanger verkrijgen. De ontvangende taak wacht gewoon, en aan de code kun je niet zien op welke task hij wacht.<br>
<img style="margin-left:30px;" src="../notify.jfif" alt="notification" width="20%"/>
<br>*Let op. Bij queues en events stuur je niet een bericht naar een task, maar naar een specifieke queue-handle of een event-handle; elke taak kan naar die handle sturen of van die handle ontvangen ('luisteren').*</li>
<ul>
<li>*Aanmaken:* hoeft niet, de handle die nodig is bestaat al: de handle van de task waarnaar verzonden wordt.</li>
<li>*Zenden en ontvangen met een waarde:*  [xTaskNotify(taskhandle)](https://www.freertos.org/xTaskNotify.html) en [xTaskNotifyWait()](https://www.freertos.org/xTaskNotifyWait.html)</li>
<li>*Op elkaar laten wachten:* [xTaskNotifyGive(taskhandle)](https://www.freertos.org/xTaskNotifyGive.html) en [ulTaskNotifyTake()](https://www.freertos.org/ulTaskNotifyTake.html)</li>
<li>*Zie:* handles.c, ledjes.c, ARM_keys.c <br></li><br>
</ul>
<li>**[Eventgroups (flags).](https://www.freertos.org/event-groups-API.html)** <br>Met een event group zet je een waarde - of eigenlijk: een rij bits - op de aangemaakte eventgroup (op de handle dus) - dat doe je met EventGroupSetBits(). Elke bit kun je zien als een event - hence 'event group'.  Bijvoorbeeld, bit 1 staat voor de motorstatus (aan of uit, 1 of 0), bit 2 voor de koplampen (aan of uit) etc. <br>
<img style="margin-left:30px;" src="../event.png" alt="eventgroup" width="20%"/>
<br>
Met EventGroupWaitBits() worden de bits uitgelezen. Je kunt alle bits uitlezen, of alleen op een specifieke bit (event) wachten, bijvoorbeeld: de motortask wacht tot de motor aangezet wordt, dus reageert op bit 1. Je kunt dan aan het OS aangeven of het bit gecleared moet worden of niet. De applicatie doet het simpeler: nadat een ARM-key gepressed is, wordt een interrupt gegeneerd. In de ISR wordt bepaald welke key gedrukt is, en die key-waarde (int) wordt op de eventgroup-handle gezet (met ...SendFromISR). In ARM_keys.c wordt die waarde in zijn geheel uitgelezen. Er wordt dus verder niks met afzonderlijke bits gedaan. </li>
<ul>
<li>*Aanmaken:* handle = [xEventGroupCreate()](https://www.freertos.org/xEventGroupCreate.html)</li>
<li>*Zenden:*  [xEventGroupSetBits(handle)](https://www.freertos.org/xEventGroupSetBits.html) en [xEventGroupSetBitsFromISR(handle)](https://www.freertos.org/xEventGroupSetBitsFromISR.html)</li>
<li>*Ontvangen:* [xEventGroupWaitBits(handle)](https://www.freertos.org/xEventGroupWaitBits.html)</li>
<li>*Zie:* admin.c, stm32f4xx_it.c, ARM_keys.c <br></li><br>
</ul>
<li>**[Queues. ](https://www.freertos.org/a00018.html)** <br>Een queue is een rij/array van elementen. Net als karretjes bij een kassa. Een element kan een char zijn, of een structure, of een pointer, whatever. Bij het aanmaken geef je aan hoeveel elementen de queue moet bevatten (hoeveel karretjes er in de rij kunnen), en hoe groot (hoeveel bytes) elk element is (hoeveel in elk karretje past). Daarmee weet het OS genoeg. Een queue werkt via FIFO (first in, first out: default) of LIFO. Met *send* zet je een element op de queue; het OS zorgt (bij FIFO) dat dat element keurig achter het vorige element terecht komt. 
<img style="margin-left:30px;" src="../queue.png" alt="queue" width="30%"/>
<br>
Bij *receive* wordt het eerst verstuurde element van de queue gehaald (wil je dat niet, dan moet je *peek* gebruiken). In de applicatie wordt een queue gebruikt om de toetsaanslagen op de UART op te vangen; dit wordt gedaan door de ISR (met ...SendFromISR in main.c). Met deze queue wordt een soort buffer gecreëerd, zodat er geen toetsaanslagen verloren gaan. De ontvangende kant (UART_keys.c) leest elke character (toets) direct uit, tot ie een linefeed  '\\n' tegenkomt - dan gaat ie de string naar een andere task versturen met xTaskNotify(). <ul>
<li>*Aanmaken:* handle = [xQueueCreate()](https://www.freertos.org/a00116.html) </li>
<li>*Op queue zetten:* [xQueueSend(handle)](https://www.freertos.org/a00117.html) en [xQueueSendFromISR(handle)](https://www.freertos.org/a00119.html)</li>
<li>*Ontvangen:* [xQueueReceive(handle)](https://www.freertos.org/a00118.html)</li>
<li>*Zie:* admin.c, main.c, UART_keys.c<br></li>
</ul>
</li>
</ul>

<br>
<h1 style="font-family:'Corbel';">
Sourcefiles: samenhang van de applicatie</h1>

Hieronder zie je de voor deze applicatie belangrijkste bestanden. De applicatie bevindt zich 
in de map **Core**, en wel hoofdzakelijk in de map **MyApp**, die weer verdeeld is in App en Ports. Daarnaast zie je in Core nog de map **Src**, die door STM gegenereerde bestanden bevat.
<table  border='1' style="margin-left:30px; font-family:'Corbel'; font-size:11pt; background-color: #f6f8ff; border-style:solid;">
    <tr>
        <td>**[Core/Src]**</td>
        <td>**Bevat de door STM gegenereerde bestanden**</td>
    </tr>
    <tr>
        <td>main.c</td>
        <td>ISR voor UART (UART_keys.c), blijf ik verder zoveel mogelijk uit...</td>
    </tr>
    <tr>
        <td>stm32f4xx_it.c</td>
        <td>ISR voor ARM_keys.c</td>
    </tr>
    <tr>
        <td>&nbsp;</td>
        <td></td>
    </tr>
    <tr>
        <td>**[Core/MyApp/App]**</td>
        <td>**Bevat de applicatie-code (Michiel Scager)**</td>
    </tr>
    <tr>
        <td>admin.c</td>
        <td>versie-beheer<br>kleine algemene functies;<br><b>alle handles en alle taken (tasks, threads) worden hier aangemaakt</b></td>
    </tr>
    <tr>
        <td>admin.h</td>
        <td>\#defines, structs, externals, etc.</td>
    </tr>
    <tr>
        <td>gps.c</td>
        <td>verwerking van de inkomende GPS-data (UART)</td>
    </tr>
    <tr>
        <td>ledjes.c</td>
        <td>hier gaan wat tasks met ledjes spelen</td>
    </tr>
    <tr>
        <td>UART_keys.c</td>
        <td>afhandeling UART-input via ISR in main.c</td>
    </tr>
    <tr>
        <td>ARM_keys.c</td>
        <td>afhandeling ARM-toetsen via ISR in stm32f4xx_it.c</td>
    </tr>
    <tr>
        <td>student.c</td>
        <td>speeltuin voor studenten</td>
    </tr>
    <tr>
        <td>&nbsp;</td>
        <td></td>
    </tr>
    <tr>
        <td>**[Core/Myapp/Ports]**</td>
        <td>**Bevat ARM-port-functies (Franc van der Bent)**</td>
    </tr>
    <tr>
        <td>buzzer.c</td>
        <td></td>
    </tr>
    <tr>
        <td>uart.c</td>
        <td></td>
    </tr>
    <tr>
        <td>leds.c</td>
        <td></td>
    </tr>
    <tr>
        <td>lcd.c</td>
        <td></td>
    </tr>
    <tr>
        <td>keys.c</td>
        <td></td>
    </tr>
</table>

<br>

