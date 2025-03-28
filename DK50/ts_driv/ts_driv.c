//--------------------------ts_driv.c-------------------------------------------
// PROJET G�olocalisation temps r�el d'une flotte de v�hicules
// Programme pour le module embarqu� pour camionnette
//
// Description: Le programme ci dessous permet l'envoi de la localisation
// par SMS d'un v�hicule toute les 5 minutes avec les 5 derni�res localisation


//------------------------------------------------------------------------------
//---------------------------INCORPORATION DES BIBLIOTHEQUES--------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clib.h"



//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//---------------------------PARAMETRAGE DU PORT RS232--------------------------

unsigned int port=0;     							// PORT EXT  0
unsigned int flow=FOSSIL_FLOWCTRL_RTSCTS;    // CONTROLE DE FLUX LOGICIEL
unsigned long baud=9600; 							// VITESSE 9600 BAUDS
unsigned int bits=8;     							// 8 BITS DE DONNEES
unsigned int parity=FOSSIL_PARITY_NO;   		// PAS DE PARITE
unsigned int stop=1;     							// 1 BIT DE STOP

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//------------------------LES STRUCTURES DE DONNEES-----------------------------

struct GPS{ 					///////////Structure des donn�es GPS//////////
   char dategps[7];        //  Date du jour	ddMMaaaa
   char heuregps[7];       //  Heure du jour UTC	MMmmss
   char longitudegps[12];  //  Longitude en Deg�s Minutes Secondes   dddmm.ssssE/W
   char latitudegps[12];   //  Latitude en Deg�s Minutes Secondes    ddmm.ssssN/S
   char nbsat[3];          //  Nombre de satellites	XX
};                         //////////////////////////////////////////////

struct CONF{              //////////////////////////////////////////////
	char number[13];       //	 Num�ro de t�l�phone du poste de commande +33XXXXXXXXX
	char id[4];            //   Identification du module CXX
	char cpin[5];          //   Code PIN de la carte SIM
};                        //////////////////////////////////////////////



//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//-----------------------------TABLEAU DE CORRESPONDANCE-------------------

int dbm[]={-113,-111,-109,-107,-105,-103,-101,-99,-97,-95,-93,-91,-89,-87,-85,-83,-81,-79,-77,-75,-73,-71,-69,-67,-65,-63,-61,-59,-57,-55,-53,-51}; //correspondance de la qualit� du signal en dbm

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//-----------------------------LES PROTOTYPES-----------------------------------

int opengeo(void);										//fonction d'ouverture du port RS232
void closegeo(void);                            //fonction de fermeture du port RS232

void writegeo(char *string);                    //fonction d'�citure sur le port RS232
char* readgeo(void);                            //fonction de lecture sur le port RS232

int checkconnect(void);                         //fonction de v�rification de l'alumage du module GSM-GPS

struct GPS getgps(void);                            //fonction de r�cup�ration des donn�es de localisation
struct CONF getInfo(void);                          //fonction de r�cup�ration de la configuration de l'appilication
int getpuissance();                               //fonction de r�cup�ration des donn�es de qualit�

void setconfiguration(void);                    //fonction de configuration du module GSM-GPS
void initsim(char *pin);                        //fonction d'initialisation du code PIN
void sendsms(char *sms, char *number);          //fonction d'envoi d'un SMS

void encrypt(char* password,int key);            //fonction de cryptage du message

double convertLatitude(char * latitude);        //fonction de conversion de la latitude en degr� d�imal
double convertLongitude(char * longitude);      //fonction de conversion de la longitude en degr� d�imal

char * message(struct GPS d1, struct GPS d2, struct GPS d3, struct GPS d4, struct GPS d5, struct CONF config);		//fonction de mise en forme de la trame de message
char * str_subgeo (const char *s, unsigned int start, unsigned int end);														//fonction pour avoir une partie d'une chaine de charact�re

//------------------------------------------------------------------------------


void main(void)
{
		struct GPS gps[5];			//Cr�ation d'un tableau de type GPS de taille 5
      struct CONF config;        //Cr�ation d'une varriable de type conf

      int i;                     //Cr�ation d'un compteur
      char msg[120];             //Cr�ation d'une variable pour stocker le message
      int power;


		BIOS_Set_Focus(FOCUS_APPLICATION);  //Permet de d�finir le focus sur l'application

      printf("\r\n------------------------------------------------------------------------------\r\n");
		printf("--------*****--*****---------****---****---*****--*---*--******--****---------\r\n");
		printf("----------*----*-------------*---*--*---*----*----*---*--*-------*---*--------\r\n");
		printf("----------*----*-------------*---*--*---*----*----*---*--*-------*---*--------\r\n");
		printf("----------*----*****---------*---*--****-----*----*---*--*****---****---------\r\n");
		printf("----------*--------*---------*---*--**-------*----*---*--*-------**-----------\r\n");
		printf("----------*--------*---------*---*--*-*------*-----*-*---*-------*-*----------\r\n");
		printf("----------*----*****--*****--****---*--*---*****----*----******--*--*---------\r\n");
		printf("------------------------------------------------------------------------------\r\n");
      printf("----------------------par Aghilas MOUGARI BTS SNIR 2019-----------------------\r\n");

      opengeo();						//initialisation du port RS232
      while(checkconnect()!=1)
      {

         printf(".");            // Tant que le module GSM-GPS n'a pas �t� allum�
         RTX_Sleep_Time(1000);
         printf(".");
         RTX_Sleep_Time(1000);
         printf(".");
         RTX_Sleep_Time(1000);
         printf("\r   \r");
            // on attent qu'il le soit
      }
      printf("\r\nCONNECTION RS232 OK\r\n");

      config=getInfo();		//R�cup�ration de la configuration

      printf("\r\nNumero:\"%s\"\r\n", config.number);
      printf("\r\nID:\"%s\"\r\n", config.id);
      printf("\r\nCPIN:\"%s\"\r\n", config.cpin);

      setconfiguration();		//configuration du module GPS-GSM
      initsim(config.cpin);   //initialisation de la carte SIM

      RTX_Sleep_Long(300000);  //On attent 5 minutes une premi�re fois

      while(1)
      {
      	for(i=0;i<5;i++)
         {
         	RTX_Sleep_Time(60000);	//on attent 1 minute

            gps[i]=getgps();	//R�cup�ration des donn�es de localisation

            while(atoi(gps[i].nbsat)<5)
            {
               printf("\r\nPB DE CONNECTION GPS\r\n");                // Tant que le nombre de satelite est
               printf("Nombre de satelites -%s-\r\n",gps[i].nbsat);   // strictement inf�rieur � 5, on attent
               RTX_Sleep_Time(30000);                                 // 30 secondes
               gps[i]=getgps();

            }

            printf("\r\nNombre de satelites -%s-\r\n",gps[i].nbsat);
            printf("\r\nDate=%s Heure=%s Longitude=%07.4f Latitude=%07.4f\r\n",gps[i].dategps, gps[i].heuregps, convertLongitude(gps[i].longitudegps), convertLatitude(gps[i].latitudegps));



         }



         power=getpuissance();
         while(power<10)
         {
         		printf("\r\nPB DE CONNECTION GSM\r\n");						// Tant que la puissance du signal est
               printf("\r\nQualite %d dBm\r\n",dbm[power]);                 // inf�rieur � 10 (-93dBm), on attent
               RTX_Sleep_Time(30000);                                   // 30 secondes

               power=getpuissance();
         }


         if(power==99)
         	power=0;

         printf("\r\nQualite %d dBm\r\n",dbm[power]);




         //msg=message(gps[0], gps[1], gps[2], gps[3], gps[4], config);	// Mise en forme du message
         memcpy(msg, message(gps[0], gps[1], gps[2], gps[3], gps[4], config), 120);
         printf("\r\nMSG: %s\r\n", msg);

			//memcpy(msg,message(gps[0], gps[1], gps[2], gps[3], gps[4], config),120);

         //sendsms(msg, config.number);                                   // Envoi du message
      }

      closegeo();

   	BIOS_Set_Focus(FOCUS_BOTH);

}

char * str_subgeo (const char *s, unsigned int start, unsigned int end)
{
   char *new_s = NULL;

   if (s != NULL && start < end)
   {
      new_s = (char*)malloc (sizeof (*new_s) * (end - start + 2));
      if (new_s != NULL)
      {
         int i;
         for (i = start; i <= end; i++)
         {
            new_s[i-start] = s[i];
         }
         new_s[i-start] = '\0';
      }
      else
      {
         fprintf (stderr, "Memoire insuffisante\n");

      }
   }
   return new_s;
}


int opengeo(void)
{
	if (fossil_init( port ) != 0x1954)
	{
		printf("\r\nError: fossil_init() failed\r\n");
      return 1;
	}

	fossil_setbaud(port, baud, parity, bits, stop);
	fossil_set_flowcontrol( port, flow );

	fossil_purge_output( port );
	fossil_purge_input( port );

   return 0;
}


void closegeo(void)
{
	fossil_deinit( port );
}

void writegeo(char *string)
{
	fossil_writeblock( port, (unsigned char *)string , strlen( string ) );
   RTX_Sleep_Time(500);
}

char* readgeo(void)
{
	char chr[140];
   int i;
   for(i=-1;i<140;i++) chr[i]=0;
	fossil_readblock( port, (unsigned char *)chr, 140 ) ;
   RTX_Sleep_Time(100);

   return chr;
}


struct GPS getgps()
{
	struct GPS d;
	char buff[50];
   char *dt[20];
   char *token;
   char *tmp;
   int i;

   readgeo();

	writegeo("AT$GPSACP\r");
   memcpy(buff,readgeo(),100);

   token=strtok(buff, ",");
   for(i=0;i<11;i++)
   {
   	dt[i]=token;
   	token=strtok(NULL, ",");
   }

   if(!strcmp(dt[4],0))
   {

   	memcpy(d.dategps,dt[2],6);
   	d.dategps[6]=0;

   	memcpy(d.longitudegps,"0",11);
   	d.longitudegps[11]=0;

      memcpy(d.latitudegps,"0",11);
   	d.latitudegps[11]=0;

   	memcpy(d.nbsat,"0",2);
   	d.nbsat[2]=0;
   }
   else
   {
   	memcpy(d.dategps,dt[9],6);
   	d.dategps[6]=0;

   	memcpy(d.longitudegps,dt[2],11);
   	d.longitudegps[11]=0;

      memcpy(d.latitudegps,dt[1],11);
   	d.latitudegps[11]=0;

      tmp=str_subgeo(dt[10],0,2);
   	memcpy(d.nbsat,tmp,2);
   	d.nbsat[2]=0;
   	free(tmp);
   }

   tmp=str_subgeo(dt[0],21,26);
   memcpy(d.heuregps,tmp,6);
   d.heuregps[6]=0;
   free(tmp);

   return d;
}

int getpuissance()
{

	char buff[30];
   char *tmp;
   char puissance[3];
   int puissanceInt;

   puissance[2]=0;

	memset(buff,0,30);
	writegeo("AT+CSQ\r");
   memcpy(buff,readgeo(),30);

   //printf("\r\n%s\r\n", buff);

   tmp=str_subgeo(buff,15,16);
   memcpy(puissance, tmp, 2);
   free(tmp);

   puissanceInt=atoi(puissance);

  // printf("\r\n%d\r\n", atoi(puissance));

   return puissanceInt;


}

void sendsms(char *sms, char *number)
{
	char buffer[120];
   char cmd[100];

   readgeo();

   memset(buffer,0,100);
   sprintf(cmd,"AT+CMGS=\"%s\"\r", number,25);
   writegeo(cmd);
   //printf("\r\n%s\r\n",readgeo());

   sprintf(buffer,"%s%c\r", sms,26);
   writegeo(buffer);
   RTX_Sleep_Time(3000);
   //readgeo();
   //	printf("\r\n%s\r\n",readgeo());
   printf("\r\nSMS ENVOYE\r\n");
}


void initsim(char *pin)
{
	char cmd[20];
   sprintf(cmd,"AT+CPIN=\"%s\"\r", pin);
 	writegeo(cmd);
   readgeo();
}

int checkconnect()
{
	char buffer[10];
	writegeo("AT\r");
   memcpy(buffer,readgeo(),10);

   if(strstr(buffer, "OK")==NULL)
   	return 0;
	return 1;
}

struct CONF getInfo()
{
	struct CONF config;
	FILE* fp;
   char buffer[80];
   char *tmp;
	fp=fopen("ts_conf.ini","r+");
   memset(buffer,0,80);


   if(fp==0)
   {
    	printf("\r\nERREUR DE CONFIGURATION\r\n");
   }

   printf("\r\nCONFIGURATION OK\r\n");
   fseek(fp,0,SEEK_SET);
   fread(buffer,strlen("[GEO]\r\nID=C01\r\nNUMBER=\"+33768749165\"\r\nPIN=0000")+1,1,fp);

   tmp=str_subgeo(buffer,9,14);
   memcpy(config.id,tmp,3);
   config.id[3]=0;
   free(tmp);

   tmp=str_subgeo(buffer,21,32);
   memcpy(config.number,tmp,12);
   config.number[12]=0;
   free(tmp);

   tmp=str_subgeo(buffer,39,43);
   memcpy(config.cpin,tmp,4);
   config.cpin[4]=0;
   free(tmp);

   fclose(fp);

   return config;
}

char * message(struct GPS d1, struct GPS d2, struct GPS d3, struct GPS d4, struct GPS d5, struct CONF config)
{
	char msg[120];
   sprintf(msg,"$%s$%s$%s$%07.4f$%07.4f$%07.4f$%07.4f$%07.4f$%07.4f$%07.4f$%07.4f$%07.4f$%07.4f$", config.id, d1.dategps, d1.heuregps, convertLongitude(d1.longitudegps), convertLatitude(d1.latitudegps), convertLongitude(d2.longitudegps), convertLatitude(d2.latitudegps), convertLongitude(d3.longitudegps), convertLatitude(d3.latitudegps), convertLongitude(d4.longitudegps), convertLatitude(d4.latitudegps), convertLongitude(d5.longitudegps), convertLatitude(d5.latitudegps));

   printf("\r\nMSG: %s\r\n", msg);

   encrypt(msg, 10);
   return msg;
}

void setconfiguration(void)
{
   writegeo("AT+CMGF=1\r");
   readgeo();
}

double convertLatitude(char * latitude)
{
   char *tmp;
   char DegreLatiChar[3];
   char MinuteLatChar[8];
   char signe[2];

   double DegreLati;
   double MinuteLat;
   double result;
   double signeLati;

   if(!strcmp(latitude,"0"))
       return 0;

   signeLati=1;

   tmp=str_subgeo(latitude,0,2);
   memcpy(DegreLatiChar,tmp,2);
   DegreLatiChar[2]=0;
   free(tmp);

   tmp=str_subgeo(latitude,2,11);
   memcpy(MinuteLatChar,tmp,7);
   MinuteLatChar[7]=0;
   free(tmp);

   tmp=str_subgeo(latitude,9,10);
   memcpy(signe,tmp,1);
   signe[1]=0;
   free(tmp);

   MinuteLat=atof(MinuteLatChar);
   DegreLati=atof(DegreLatiChar);

   if(!strcmp(signe,"N"))
   {
       signeLati=1;
   }

   if(!strcmp(signe,"S"))
   {
       signeLati=-1;
   }

   result=signeLati*(DegreLati+(MinuteLat/60));

   return result;
}

double convertLongitude(char * longitude)
{
   char *tmp;
   char DegreLongiChar[4];
   char MinuteLongiChar[8];
   char signe[2];

   double DegreLongi;
   double MinuteLongi;
   double result;
   double signeLongi;


   if(!strcmp(longitude,"0"))
       return 0;

   signeLongi=1;

   tmp=str_subgeo(longitude,0,2);
   memcpy(DegreLongiChar,tmp,3);
   DegreLongiChar[3]=0;
   free(tmp);
   DegreLongi=atof(DegreLongiChar);

   tmp=str_subgeo(longitude,3,12);
   memcpy(MinuteLongiChar,tmp,7);
   MinuteLongiChar[7]=0;
   free(tmp);

   tmp=str_subgeo(longitude,10,11);
   memcpy(signe,tmp,1);
   signe[1]=0;
   free(tmp);
   MinuteLongi=atof(MinuteLongiChar);

   if(!strcmp(signe,"E"))
   {
       signeLongi=1;
   }

   if(!strcmp(signe,"W"))
   {
       signeLongi=-1;
   }

   result=signeLongi*(DegreLongi+(MinuteLongi/60));

   return result;
}

void encrypt(char* password,int key)
{
    unsigned int i;
    for(i=0;i<strlen(password);++i)
    {
        password[i] = password[i] ^ key;
    }
}
