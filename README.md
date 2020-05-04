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
 
ou pour les motocycles :  
 - d'un téléphone portable équipé d'un récepteur GPS et d'un système d'exploitation Android  
  
Elle veut disposer d’un poste de commandement centralisé. Ce poste de commandement est composé : 
 - d’un module GM862-QUAD (contenant un module GSM) de la société TELIT  
 - d’une carte SIM  
 - d’un ordinateur équipé de Windows 
 - d’une connexion internet 
 
