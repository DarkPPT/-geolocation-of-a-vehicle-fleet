# Géolocation d'une flotte de véhicules
Projet de BTS SNIR (2018-2019)


## I-INTRODUCTION 
 
Dans le cadre de notre seconde année de BTS Système Numérique option Informatique et Réseaux au Lycée Dorian, il nous est proposé un projet de 4 mois nous permettant de mettre en pratique nos connaissances et nos compétences professionnelles au travers d’un cahier des charges ayant pour finalité la conception et le développement d’une application d’entreprise en accord avec nos intérêts professionnels. 

## II-PRÉSENTATION DE L’ENTREPRISE ET DU CONTEXT 
 
TransSecure est une société de transport de marchandises à forte valeur ajoutée. C’est une société autonome et dynamique spécialisée depuis plus de 25 ans dans le transport et les courses à la demande en Express. Elle met à votre service une gamme complète de plus de 50 véhicules répartis sur nos 15 agences et sur tout le territoire national.  
Leurs véhicules sont munis de toutes sortes de moyens de levage et d’équipements.  
 
TransSecure propose une très large palette de prestations et de qualité de service : 
-	Transport de produits à valeur ajoutée et sur mesure (10 m3 à 12m3) 
En qualité de partenaires de leurs clients, ils prennent en charge vos demandes d'enlèvements et de livraisons mais effectuent aussi toutes sortes de prestations annexes liées à votre métier, et ce comme si vous l'aviez fait vous-mêmes. Pour cela ils forment une équipe de conducteurs à vos spécificités. Ils sont ainsi à tout moment disponible sur une simple demande. Il permet ainsi à leur clientèle de s'appuyer sur une entreprise de qualité et de se consacrer totalement à son cœur de métier, et de ne payer que ce qui est réalisé.  
 
-	Transport de produit à valeur ajoutée rapide 
Une équipe de professionnels de la livraison rapide est à même de vous proposer une large palette tarifaire. Idéal pour le transport de marchandises de petite taille type bijoux, parfums…  
Notre expérience et notre ancienneté vous garantissent une livraison sans soucis.  
 
- Location de véhicules industriels avec chauffeur. 
Sur simple appel, dès que vous êtes référencés comme clients, TransSecure met à votre disposition le véhicule de votre souhait ainsi que son chauffeur. 
En louant ainsi un véhicule et son personnel, vous pouvez immédiatement gérer toutes vos expéditions et vos enlèvements à votre convenance. (Dans la limite du bon respect de la réglementation sociale et routière), soit pour une durée d’une demi-journée, d’une journée, d’une semaine, ou plus. 
C’est la solution pour une bonne gestion d’un service transport interne tout en obtenant le maximum de souplesse. 
Ainsi, TransSecure met à votre disposition des véhicules performant tout en respectant l’environnement. TransSecure dispose de deux flottes de véhicules : 50 véhicules utilitaires et 20 motocycles.

## III-Présentation du projet

Aujourd’hui, les clients se plaignent de ne pas pouvoir suivre leurs livraisons en temps réel lors d’un trajet de l’un des véhicules de la société TransSecure. La société de transports de matériels TransSecure ne dispose d’aucun moyen pour localiser ces flottes de véhicules.  
Afin d’améliorer la sécurité et le service rendu aux clients en matière de délai, la société TransSecure souhaite connaitre précisément et régulièrement la position de tous ses véhicules lors d’une livraison. Un centre de commandement centralisé permettra la gestion de la géolocalisation des véhicules. Les positions des véhicules doivent être connues à chaque minute. 
La position d’un véhicule doit être envoyée à un poste de commandement centralisé qui recevra toutes les 5 minutes les 5 dernières positions à chaque minute par SMS. 
Si les positions d’un véhicule ne sont pas reçues toutes les 5 minutes lors d’une livraison, une alarme est déclenchée pour prévenir l’administrateur du centre qu’un véhicule n’a pas envoyé sa position. 
De plus pour des raisons de sécurité, les positions des véhicules doivent être envoyées de façon cryptée au centre de commandement centralisé. 
Cette solution est composée pour les véhicules utilitaires :  
 - d’un module GM862-GPS (contenant un module GPS et un module GSM) de la société 
TELIT  
 - d’une carte SIM (SMS illimité) 
 - d’un module GM862 EVK V3RS-232 
Evaluation Board de la société SparkFun 
Electronics  
 - d’un DK50 de la société BECK  
 ![Stormtroopocat](https://github.com/DarkPPT/geolocation-flotte-de-vehicules/blob/master/images/v%C3%A9hicule.jpg "véhicules")
 
 
 
ou pour les motocycles :  
 - d'un téléphone portable équipé d'un récepteur GPS et d'un système d'exploitation Android
 ![Stormtroopocat](https://github.com/DarkPPT/geolocation-flotte-de-vehicules/blob/master/images/motocycle.png "moto")
  
Elle veut disposer d’un poste de commandement centralisé. Ce poste de commandement est composé : 
 - d’un module GM862-QUAD (contenant un module GSM) de la société TELIT  
 - d’une carte SIM  
 - d’un ordinateur équipé de Windows 
 - d’une connexion internet 
 
![Stormtroopocat](https://github.com/DarkPPT/geolocation-flotte-de-vehicules/blob/master/images/Centre.jpg "center")
 
## III-Matériel utilisés
DK50 et SC13 : 
 
Le DK50 est un produit de la société allemande BECK IPC. BECK est un membre du groupe Festo GmbH qui travaille notamment dans l’automatisation industrielle. Il est spécialisé dans la conception de systèmes embarqués.  
Définissons exactement les termes DK50 et SC13 que nous utiliserons.  
 
Le SC13 est le cœur du système. C’est le microcontrôleur qui va permettre de gérer les périphériques. Ce microcontrôleur intègre un microprocesseur 16 bits du type 80186 cadencé à 40 Mhz, 512 Ko de mémoire Flash, 512 Ko de RAM, des possibilités de communication par RS232 et Ethernet 10 Base-T. 

![Stormtroopocat](https://github.com/DarkPPT/geolocation-flotte-de-vehicules/blob/master/images/sc13.jpg "sc13")
 
 
Mais on ne peut exploiter le SC13 qu’en l’intégrant dans un module qui relie directement les pattes du microcontrôleur aux connectiques normales utilisées. Ce module s’appelle le DK50. C’est un boitier qui intègre entre autres 8 Entrées/Sorties avec leurs LEDs de contrôle, 2 ports séries (COM et EXT), 1 port Ethernet 10 Base-T et 1 LED de trafic Ethernet. 
 
![Stormtroopocat](https://github.com/DarkPPT/geolocation-flotte-de-vehicules/blob/master/images/dk50.jpg "dk50")
 
L'avantage du SC12 réside dans son noyau temps réel multitâche orchestré par son système d’exploitation RTOS. Celui-ci est propre à l’IPC@CHIP qui comporte une API (Application Programmer Interface) complète autorisant à un accès aisé à toutes ses fonctionnalités mais aussi à un accès simplifié aux services TCP/IP. La figure cidessous représente l’architecture du RTOS : 
 
![Stormtroopocat](https://github.com/DarkPPT/geolocation-flotte-de-vehicules/blob/master/images/arch.jpg "arch")
 
GM862-GPS et UberBoard v2 : 
 
Le module GM862-GPS est à la fine pointe de la gamme de produits Telit. Il combine des performances supérieures dans la fonctionnalité modem GSM/GPRS quadri-bande avec le dernier haut de 20 canaux récepteur GPS monopuce SiRFstarIII™ sensibilité. La compatibilité 
Pin-pin au module précédant GM862-GPS améliore et étend les fonctionnalités des nouvelles et existantes applications GPS. Avec sa conception robuste, sa plage de températures étendue, son support de carte SIM intégré et ses connecteurs 
de qualité industrielle, le Telit GM862-GPS est la plate-forme idéale pour les applications mobiles dans des domaines tels que la télématique, la gestion de flotte, suivi, sécurité et navigation du véhicule. 
Le nouveau récepteur GPS présente une faible consommation d'énergie avec une précision de résolution de position inférieure à 2.5 m, SBAS (WAAS et EGNOS) ainsi que haute sensibilité pour les corrections d'intérieur. Ces fonctionnalités combinées avec l'environnement de développement d'applications Python™ disponible se traduit par un coût très élevé et riche en fonctionnalités et une plateforme tout à fait capable de devenir la solution totale pour l'application client complète. Fonctionnalités supplémentaires, y compris la détection de brouillage, pile de protocole tcp/ip intégrée, et Easy Scan® offre des avantages inégalés au développeur d'applications sans ajouter de coût. 
 
 
 
 
UberBoard v2 est la carte de développement de deuxième génération qui regroupe un ensemble de gadgets, tous reliés entre eux par un processeur LPC2148 ARM7.  
 
Les commutateurs étant sur la gauche, la ligne série passe directement à l’UART0 du LPC2148. Lorsque les commutateurs sont dans les bonnes positions, TX, RX, CTS et RTS passent directement au module de cellules GM862.  
 
 
 
 
GM862-QUAD et GM862 Evaluation Board - USB : 
Le module cellulaire à bande quadruple GM862 par Telit permettra de connecter un appareil embarqué n’importe où dans le monde où les téléphones portables sont utilisés. Cette version (GM862-QUAD) est compatible avec les différentes fréquences 
850/900/1800/1900MHz des réseaux cellulaires à travers le monde. 
 
Vous devrez fournir une carte SIM l’insérer dans le module, et vous passez des appels sous votre compte cellulaire et envoyer des SMS. Fonctionne avec tous les fournisseurs supportant actuellement les cartes SIM. 
 
Le module GM862 est contrôlé par des commandes AT. Cela signifie que tout ce que vous avez à faire est d’envoyer une chaîne de caractères de série telle que "ATD 3035551234" et le module va effectuer un appel. Une fois que le module est connecté à un appareil, une connexion série est effectuée et les données peuvent être transférées aussi simplement que l’envoie et la réception de charactères série à travers le module. 
 
 
  
La carte de développement GM862 Evaluation Board - USB de prochaine génération pour le GM862 dispose d’un breakout complet de 50 broches, connecteur USB B, et d’un script Python qui active le commutateur. Cela permet des connexions aux interfaces audio, numérique et caméra du module GM862. 
 
 
Le GM862 Eval USB se fixe à n’importe quel port USB et apparaît comme un port com standard. Allumez la carte, activez le module, et vous pouvez commencer à envoyer et recevoir des commandes AT via un terminal série.  
 
La communication et l’alimentation se font via le câble USB. La puce USB peut être déconnectée pour permettre le contrôle externe des broches TX et RX sur le module GM862. 
 
La carte est entièrement assemblée avec 50 broches Molex pièce de connecteur # : 
53748-0504, 3.8V circuit de régulation de l’alimentation, et les circuits de soutien. Le connecteur Molex est porté à 5 rangées doubles, . 1" en-tête. 3.8V est régulé par un régulateur LDO SPX29302.  
 
 
Téléphone Android : 
 	Le téléphone est équipé du système d’exploitation Android. Android est un OS basé sur le noyau Linux, ce dernier inclut à la fois un système d’exploitation et des applications que tout le monde (ou presque) peut mettre soit en vente ou en utilisation gratuite depuis la boutique Google Play, mais aussi un logiciel qui crée un réseau d’échange d’informations entre différentes applications (intergiciel). 
 
Autrefois, il existait des variantes de cette plateforme pour les téléphones et les tablettes. À partir de la version 4 (Ice Cream Sandwich), toutes les variantes ont été fusionnées pour donner un système plus uniforme, mais plus performant aussi. La dernière version de la plateforme est pour l’heure Android 9. La version 4.1 a comme nom de code Jelly Bean. Google a tenu à conserver le nom, du fait qu’extérieurement, les deux sont plus ou moins similaires. Cependant, d’importantes modifications ont été apportées en interne pour améliorer la version 4.1. 
 
Le tableau suivant présente quelques différentes distributions d’Android : 

![Stormtroopocat](https://github.com/DarkPPT/geolocation-flotte-de-vehicules/blob/master/images/android.jpg "Android")
