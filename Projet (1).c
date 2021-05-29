#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct DateFinDebut{//date
int dy;
 int mth;
 int yr;
}date;
typedef struct Voiture{//car
int idcar;
 char marque[15];
 char namecar[15];
 char color;
 int nbplace;
 int prixday;
 char *Enlocation;
}car;
typedef struct contratLocation{//Contrat
float numContrat;
 int idcar;
 int idClient;
 date Begin;
 date End;
 int Cost;
}Contrat;
typedef struct Client{//cl
int idClient;
 char nm[20];
 char prnm[20];
 int cin;
 char adrs[15];
 int tlphone;
}cl;
/********************** Struct ******************************/
int rech_cl(int id){//recherche de l'id_client
FILE *f;cl client;
f=fopen("Clients.txt","r");
do{
  fscanf(f,"%d %s %s %d %s %d",&client.idClient,client.nm,client.prnm,&client.cin,client.adrs,&client.tlphone);
  if(id==client.idClient){fclose(f);return 1;}
  }while(!feof(f));
  fclose(f);return -1;
  }
int rech_car(int id){//recherche de l'id_voiture
FILE *F;car Car;
F=fopen("Voiture.txt","r");
do{
  fscanf(F,"%d %s %s %s %d %d %s \n",&Car.idcar,Car.marque,Car.namecar,Car.color,&Car.nbplace,&Car.prixday,Car.Enlocation);
  if(id==Car.idcar){fclose(F);return 1;}
  }while(!feof(F));
  fclose(F);return -1;
  }
int rech_contrat(float n){//recherche de num de contrat
FILE *C;Contrat contrat;
C=fopen("Contrat.txt","r");
do{fscanf(C,"%f %d %d %d/%d/%d %d/%d/%d %d",&contrat.numContrat,&contrat.idcar,&contrat.idClient,&contrat.Begin.dy,&contrat.Begin.mth,&contrat.Begin.yr,&contrat.End.dy,&contrat.End.mth,&contrat.End.yr,&contrat.Cost);
  if(n==contrat.numContrat){fclose(C);return 1;}
  }while(!feof);
  fclose(C);
  return -1;
}
int ordre(date D,date F){
	if(D.yr <= F.yr)
	  if(D.mth <= F.mth)
	    if(D.dy< F.dy)return 0;
	else{return 1;}
}
/********************* Recherche *******************************/
void Menu_prcpl();
void Afchg(){//fonction de la liste des clients
    cl client;
	FILE *F;
	F=fopen("Client.txt","r");
	printf("ID_Client\tNom\tPrenom\tCIN\tAdresse\tTelephone\n");
	do{
		fscanf(F,"%d %s %s %d %s %d \n",&client.idClient,client.nm,client.prnm,&client.cin,client.adrs,&client.tlphone);
		printf("%d\t",client.idClient);printf("%s\t",client.nm);printf("%s\t",client.prnm);
		printf("%d\t",client.cin);printf("%s\t",client.adrs);printf("%d\t\n",client.tlphone);
		printf("\n");
	}while(!feof(F));
	fclose(F);
	}
void Add(){// function de l'ajout
FILE *F;cl client;
F=fopen("Clients.txt","a");
printf("Saisir l'id du client:");
scanf("%d",&client.idClient);
if(rech_cl(client.idClient)==1){printf("Client exist déja !!\n");fclose(F);Menu_prcpl();}
else{printf("Saisir nom ff du client:\n");
  gets(client.nm);
  printf("Saisir prenom du client:\n");
  gets(client.prnm);
  printf("Saisir CIN du client:\n");
  scanf("%d",&client.cin);
  printf("Saisir adresse du client:\n");
  gets(client.adrs);
  printf("Saisir numéro de téléphone du client:\n");
  scanf("%d",&client.tlphone);
  fprintf(F,"%d %s %s %d %s %d \n",client.idClient,client.nm,client.prnm,client.cin,client.adrs,client.tlphone);
  fclose(F);
  }
printf("Ajout du client s'est fait par succée!\n");
}
void Modifie(){//function de modifier
FILE *F,*f;int num;cl client;
F=fopen("Client.txt","r");
printf("Saisir l'id du client:");
scanf("%d",&num);
if(rech_cl(num)==-1)
  {fclose(F);
  printf("\nCe client n'existait pas!!");
  printf("Si vous voulez l'ajoutez, revenez au menu de gestion du client et choisissez\"Ajout Client\" ...\n");
  exit(0);}
else{
  f=fopen("change.txt","a");
  do{fscanf(F,"%d %s %s %d %s %d \n",&client.idClient,client.nm,client.prnm,&client.cin,client.adrs,&client.tlphone);
	if(num==client.idClient)
	  {
	  client.idClient=num;
	  printf("Saisir nom du client:");
      gets(client.nm);
      printf("Saisir prénom du client:");
      gets(client.prnm);
      printf("Saisir CIN du client:");
      scanf("%d",&client.cin);
      printf("Saisir adresse du client:");
      gets(client.adrs);
      printf("Saisir numéro de téléphone du client:");
      scanf("%d",&client.tlphone);
	  }
    fprintf(f,"%d %s %s %d %s %d \n",client.idClient,client.nm,client.prnm,client.cin,client.adrs,client.tlphone);
    }while(!feof(F));
  fclose(f);
	}
  fclose(F);
  remove("Client.txt");rename("change.txt","Client.txt");
}
void Sup(){//function for deleting
	FILE* file,*fichier;int num;cl client;
	file=fopen("Client.txt","r");
	printf("Saisir l'id du client:");
    scanf("%d",&num);
    if(rech_cl(num)==-1)
      {fclose(file); printf("Ce client n'existait pas!!");exit(0);}
    else{fichier=fopen("change.txt","a");
      while(!feof(file))
        {fscanf(file,"%d %s %s %d %s %d\n",&client.idClient,client.nm,client.prnm,&client.cin,client.adrs,&client.tlphone);
        if(num!=client.idClient)
          fprintf(fichier,"%d %s %s %d %s %d\n",&client.idClient,client.nm,client.prnm,&client.cin,client.adrs,&client.tlphone);
		}fclose(fichier);
	  }fclose(file);
	remove("Client.txt");
	rename("change.txt","Client.txt");
}
/************************/             /***************************/
void Afchg_car(){//fct de Car list
FILE *F;car Car;
F=fopen("Voiture.txt","r");
printf("ID Voiture\tLa Marque\tNom \tCouleur\tNombre de place\tPrix/jour\tEn Location\n");
do{fscanf(F,"%d %s %s %s %d %d %s \n",&Car.idcar,Car.marque,Car.namecar,Car.color,&Car.nbplace,&Car.prixday,Car.Enlocation);
  printf("%d\t%s\t%s\t%s\t%d\t%d\t%s \n",Car.idcar,Car.marque,Car.namecar,Car.color,Car.nbplace,Car.prixday,Car.Enlocation);
  }while(!feof(F));
  fclose(F);
}
void Add_car(){//function de l'ajout de car
FILE *F;car Car;
F=fopen("Voiture.txt","a");	
printf("Saisir l'id de la voiture:");
scanf("%d",&Car.idcar);
if(rech_car(Car.idcar)==1){printf("Voiture exist déja !!\n");fclose(F);exit(0);}
else{printf("\nSaisir marque de la voiture:");
  gets(Car.marque);
  printf("\nSaisir nom de la voiture:");
  gets(Car.namecar);
  printf("\nSaisir la couleur de la voiture:");
  scanf("%s",Car.color);
  printf("\nSaisir nombre de place de la voiture:");
  scanf("%d",&Car.nbplace);
  printf("\nSaisir le prix par jour:");
  scanf("%d",&Car.prixday);
  do{
    printf("Indiquez si la voiture est en location ou non par OUI/NON:");
    scanf("%s",Car.Enlocation);
	}while(Car.Enlocation !="OUI"||Car.Enlocation !="NON");
  fprintf(F,"%d %s %s %s %d %d %s \n",Car.idcar,Car.marque,Car.namecar,Car.color,Car.nbplace,Car.prixday,Car.Enlocation);
  fclose(F);
  }
printf("\nAjout de la voitures s'est fait par succée!");
fclose(F);
}
void Modifie_car(){//function of modify car
FILE *file,*fichier; int num;car Car;
file=fopen("Voiture.txt","r");
printf("Saisir l'id de la voiture à modifier:");
scanf("%d",&num);
if(rech_car(num)==-1){fclose(file);printf("\nVoiture n'existait pas!!");exit(0);}
else{
  fichier=fopen("change.txt","a");
  do{fscanf(file,"%d %s %s %s %d %d %s \n",&Car.idcar,Car.marque,Car.namecar,Car.color,&Car.nbplace,&Car.prixday,Car.Enlocation);
    if(num==Car.idcar){
	  printf("\nSaisir marque de la voiture:");
      gets(Car.marque);
      printf("\nSaisir nom de la voiture:");
      gets(Car.namecar);
      printf("\nSaisir la couleur de la voiture:");
      scanf("%s",Car.color);
      printf("\nSaisir nombre de place de la voiture:");
      scanf("%d",&Car.nbplace);
      printf("\nSaisir le prix par jour:");
      scanf("%d",&Car.prixday);
      do{printf("\nIndiquez si la voiture est en location ou non par OUI/NON:");scanf("%s",Car.Enlocation);
	    }while(Car.Enlocation!="OUI"||Car.Enlocation !="NON");
	  }
	fprintf(fichier,"%d %s %s %s %d %d %s \n",Car.idcar,Car.marque,Car.namecar,Car.color,Car.nbplace,Car.prixday,Car.Enlocation);
	}while(!feof(file));
	fclose(fichier);
  }fclose(file);remove("Voiture.txt");rename("change.txt","Voiture.txt");
}
void Sup_car(){//function suprimé car
FILE *f,*F;int num;car Car;
f=fopen("Voiture.txt","r");
printf("\nSaisir l'id de la voiture à supprimer:");
scanf("%d",&num);
if(rech_car(num)==-1){fclose(f);printf("\nVoiture n'existait pas!!");exit(0);}
else{F=fopen("change.txt","a");
  do{fscanf(f,"%d %s %s %s %d %d %s \n",&Car.idcar,Car.marque,Car.namecar,Car.color,&Car.nbplace,&Car.prixday,Car.Enlocation);
    if(num!=Car.idcar)
    fprintf(F,"%d %s %s %s %d %d %s \n",Car.idcar,Car.marque,Car.namecar,Car.color,Car.nbplace,Car.prixday,Car.Enlocation);
	}while(!feof(f));
	fclose(F);
  }fclose(f);remove("Voiture.txt");rename("change.txt","Voiture.txt");
}
/************************/             /***************************/
void Afchg_ctrat(){//fct show contrat by num
float num;FILE *F;	Contrat contrat;  date Begin,End;
F=fopen("Contrat.txt","r");
printf("Saisir le numéro de contrat à visualiser:");
scanf("%f",&num);
if(rech_contrat(num)==-1){fclose(F);printf("Contrat n'existait pas!!\n");Menu_prcpl();}
else{
	do{
	  fscanf(F,"%f %d %d %d/%d/%d %d/%d/%d %d \n",&contrat.numContrat,&contrat.idcar,&contrat.idClient,&contrat.Begin.dy,&contrat.Begin.mth,&contrat.Begin.yr,&contrat.End.dy,&contrat.End.mth,&contrat.End.yr,&contrat.Cost);
	  if(num==contrat.numContrat)
	  {printf(" \nNuméro de contrat:     %f",contrat.numContrat);
	   printf(" \nL'ID de la voiture:    %d",contrat.idcar);
	   printf(" \nL'ID du client:        %d",contrat.idClient);
	   printf(" \nDate début de contrat: %d/%2.d/%4.d",contrat.Begin.dy,contrat.Begin.mth,contrat.Begin.yr);
	   printf(" \nDate fin de contrat:   %d/%2.d/%4.d",contrat.End.dy,contrat.End.mth,contrat.End.yr);
	   printf(" \nLe Cout:               %d",contrat.Cost);
	  }
	}while(!feof(F));fclose(F);
  }
}
void Sup_ctrat(float n){//Suprimer le contrat
FILE *file,*F;Contrat contrat;
file=fopen("Contrat.txt","r");
F=fopen("change.txt","a");
do{fscanf(file,"%f %d %d %d/%d/%d %d/%d/%d %d",&contrat.numContrat,&contrat.idcar,&contrat.idClient,&contrat.Begin.dy,&contrat.Begin.mth,&contrat.Begin.yr,&contrat.End.dy,&contrat.End.mth,&contrat.End.yr,&contrat.Cost);
  if(n!=contrat.numContrat)
  fprintf(F,"%f %d %d %d/%d/%d %d/%d/%d %d",contrat.numContrat,contrat.idcar,contrat.idClient,contrat.Begin.dy,contrat.Begin.mth,contrat.Begin.yr,contrat.End.dy,contrat.End.mth,contrat.End.yr,contrat.Cost);
  }while(!feof(file));
  fclose(file);fclose(F);
  remove("Contrat.txt");rename("change.txt","Contrat.txt");
}
void Return_ctrat(){//fct give back the car
	FILE *F,*file;  float num;  int n;  car Car;
	printf(" \nSaisir l'id de la voiture à retourner:");
	scanf("%d",&n);
	if(rech_car(n)==1)
	{file=fopen("Voiture.txt","r");
	 F=fopen("change.txt","a");
	 do{fscanf(file,"%d %s %s %s %d %d %s \n",&Car.idcar,Car.marque,Car.namecar,Car.color,&Car.nbplace,&Car.prixday,Car.Enlocation);
     if(n==Car.idcar)
	   {Car.Enlocation="NON";  
	   printf("\nSaisir numéro de contrat:");  scanf("%f",&num);  
		Sup_ctrat(num);}
	 fprintf(F,"%d %s %s %s %d %d %s \n",Car.idcar,Car.marque,Car.namecar,Car.color,Car.nbplace,Car.prixday,Car.Enlocation);
	   }while(!feof(file));
	 fclose(file);fclose(F);
	 remove("Voiture.txt");rename("change.txt","Voiture.txt");
     }
}
void Modifie_ctrat(){//fct modify contrat
FILE *f,*file;  float num;  Contrat contrat;  date Begin,Fin;
f=fopen("Contrat.txt","r");
printf(" \nSaisr numéro de contrat:");
scanf("%f",&num);
if(rech_contrat(num)==-1){fclose(f);printf("\n Contrat n'existait pas!!");exit(0);}
else{file=fopen("change.txt","a");
  do{
    fscanf(f,"%f %d %d %d/%d/%d %d/%d/%d %d",&contrat.numContrat,&contrat.idcar,&contrat.idClient,&contrat.Begin.dy,&contrat.Begin.mth,&contrat.Begin.yr,&contrat.End.dy,&contrat.End.mth,&contrat.End.yr,&contrat.Cost);
	if(num==contrat.numContrat)
	  {printf("\nNuméro de contrat:");scanf("%f",contrat.numContrat);
	  printf(" \nL'ID de la voiture:");scanf("%d",contrat.idcar);
	  printf(" \nL'ID du client:");scanf("%d",contrat.idClient);
	  printf(" \nDate début de contrat: ");
	  printf(" \nJour:");   scanf("%d",contrat.Begin.dy);
	  printf(" \nMois:");   scanf("%d",contrat.Begin.mth);
	  printf(" \nAnnée:");  scanf("%d",contrat.Begin.yr);
	  printf(" \nDate fin de contrat:");
	  do{printf(" \nJour de retour:");   scanf("%d",contrat.End.dy);
	    printf(" \nMois de retour:");   scanf("%d",contrat.End.mth);
	    printf(" \nAnnée de retour:");   scanf("%d",contrat.End.yr);
		}while(ordre(Begin,Fin)==1);
	  printf(" \nLe Cout:");  scanf("%d",contrat.Cost);
	  }
	 fprintf(file,"%f %d %d %d/%d/%d %d/%d/%d %d",contrat.numContrat,contrat.idcar,contrat.idClient,contrat.Begin.dy,contrat.Begin.mth,contrat.Begin.yr,contrat.End.dy,contrat.End.mth,contrat.End.yr,contrat.Cost);
	}while(!feof(f));fclose(file);
	}fclose(f);remove("Contrat.txt");rename("change.txt","Contrat.txt");
}
void Ajout_ctrat(){//ajout new contrat
FILE *file; Contrat contrat;  date Begin,Fin;
file=fopen("Contrat.txt","a");
printf(" \nNuméro de contrat:");scanf("%f",contrat.numContrat);
printf(" \nL'ID de la voiture:");scanf("%d",contrat.idcar);
printf(" \nL'ID du client:");scanf("%d",contrat.idClient);
printf(" \n Date début de contrat: ");
printf(" \n Jour:");   scanf("%d",contrat.Begin.dy);
printf(" \n Mois:");   scanf("%d",contrat.Begin.mth);
printf(" \n Année:");  scanf("%d",contrat.Begin.yr);
printf(" \n Date fin de contrat:");
do{printf(" \n Jour de retour:");   scanf("%d",contrat.End.dy);
  printf(" \n Mois de retour:");   scanf("%d",contrat.End.mth);
  printf(" \n Année de retour:");   scanf("%d",contrat.End.yr);
}while(ordre(Begin,Fin)==1);
printf(" \n Le Cout:");  scanf("%d",contrat.Cost);
fprintf(file,"%f %d %d %d /%d /%d %d /%d /%d %d \n",contrat.numContrat,contrat.idcar,contrat.idClient,contrat.Begin.dy,contrat.Begin.mth,contrat.Begin.yr,contrat.End.dy,contrat.End.mth,contrat.End.yr,contrat.Cost);
}
void Louer(){//fct Rent
FILE*f,*file; int n,num;car Car;
printf(" \nSaisir l'id du client:\n");
scanf("%d",n);
printf(" \nSaisir l'id de la voiture:\n");
scanf("%d",&num);
if(rech_car(num)==-1)printf(" \nCette voiture n'existait pas!!\n");
else if(rech_cl(n)==-1)
    {printf(" \nCe client n'existait pas!!\n Veuillez enregistrer les informations du client dans Gestion_Client ...\n");}
else{
  file=fopen("Voiture.txt","r");   f=fopen("change.txt","a");
  do{fscanf(file,"%d %s %s %s %d %d %s \n",&Car.idcar,Car.marque,Car.namecar,Car.color,&Car.nbplace,&Car.prixday,Car.Enlocation);
    if(num==Car.idcar){
	  if(Car.Enlocation=="OUI"){printf(" \n La voiture n'est pas disponible!!\n");}
      else{
	    printf(" \nLa voiture est disponible...\n");
	    Car.Enlocation="OUI";}
	}
	 fprintf(f,"%d %s %s %s %d %d %s \n",Car.idcar,Car.marque,Car.namecar,Car.color,Car.nbplace,Car.prixday,Car.Enlocation);
    }while(!feof(file));
	fclose(file);  fclose(f);  
	remove("Voiture.txt");  rename("change.txt","Voiture.txt");
   Ajout_ctrat();
   }
}
/**************************************************/
void Gst_Client(){//gestion client
int ch1;
 printf("  ^ Gestion de Client ^\n\n");
 printf(" Liste des clients     1\n");//done
 printf(" Ajout client          2\n");//done
 printf(" Modifier client       3\n");//done
 printf(" Supprimer client      4\n");//done
 printf(" Retour                5\n");//done
  do{
 printf("   \nVotre Choix : \b ");
 scanf("%d",&ch1);}while(ch1<1 || ch1>5);
 switch(ch1)
   {case 1:Afchg();break;
   case 2:Add();break;
   case 3:Modifie();break;
   case 4:Sup();break;
   case 5:Menu_prcpl();break;
   }
 }
void Gst_Car(){//gestion voiture
int ch2;
 printf("  ^Gestion de Voiture ^\n\n");
 printf(" Liste des voitures     1\n");
 printf(" Ajout voiture          2\n");
 printf(" Modifier voiture       3\n");
 printf(" Supprimer voiture      4\n");
 printf(" Retour                 5\n");
  do{
 printf("   \nVotre Choix : \b ");
 scanf("%d",&ch2);}while(ch2<1 || ch2>5);
 switch(ch2)
   {case 1:Afchg_car();break;//done
   case 2:Add_car();break;//done
   case 3:Modifie_car();break;//done
   case 4:Sup_car();break;//done
   case 5:Menu_prcpl();break;
   }
 }
void Location(){//gestion de location de voiture
int ch3;
 printf(" ^ Location d'une Voiture ^\n\n");
 printf(" Visualiser contrat      1\n");
 printf(" Louer voiture           2\n");
 printf(" Retourner voiture       3\n");
 printf(" Modifier voiture        4\n");
 printf(" Retour                  5\n");
  do{
 printf("   \nVotre Choix : \b ");
 scanf("%d",&ch3);}while(ch3<1 || ch3>5);
 switch(ch3)
   {case 1:Afchg_ctrat();break;//done
   case 2:Louer();break;//done
   case 3:Return_ctrat();break;//done
   case 4:Modifie_ctrat();break;//done
   case 5:Menu_prcpl();break;
   }
}
void Menu_prcpl(){
int ch;
printf("     Bienvenu   \n");
printf(" ^ Menu Principal ^ \n\n");
printf(" Location           1\n");
printf(" Gestion Voitures   2\n");
printf(" Gestion Clients    3\n");
printf(" Quitter            4\n");
  do{
printf(" \t  \nVotre Choix: \b ");
scanf("%d",&ch);}while(ch<1 || ch>4);
switch(ch)
 {case 1:
 	Location();
 	break;
  case 2:
  	Gst_Car();
  	break;
  case 3:
  	Gst_Client();
  	break;
  case 4:
  	printf("...Au revoir...");
  	break;
 }
 }
/*************************************************/
int main(){
char rp;
do{Menu_prcpl();
  printf("\n Voulez sortir de l'application(O/N) ?");
  scanf("%s",rp);
 }while(rp=='N'|| rp=='n');
return 0;
 }
