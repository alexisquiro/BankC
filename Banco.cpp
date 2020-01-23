#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct transacciones{
int codigope;
char tipoop[8];
char fecha [11];
long int monto;
char descripcion[20];
 transacciones *next;
};
struct cuentas {
int nrocuenta;
int  banco;
int saldo;
cuentas *next;
transacciones *trans;
};

struct personas {
int cedula;
char nombre[10];
char apellido[10];
char direccion[10];
int fecha;
char domicilio[15];
int capitalto;
int deuda;
int efectivo;
personas *next;
cuentas *cuen;
};


int cedula(personas **p,int c) {  
personas *t=*p;
		if(*p){
		
		while (t)
	{  
	    if(c==t->cedula)
		{
			return 1;
		}
			t=t->next;
  }
}
  return 0;
}


int existcuen(int ce,int ci,personas **p){
	personas *t=*p;
	cuentas *c;
	int x=0;
	  
	while (t)
	{ 
	 
		if(ci==t->cedula)
		{	c=t->cuen;

			while(c)
			{
				if(ce==c->nrocuenta)
				{
				    return 1;
				}
				c=c->next;
			}
		}
		t=t->next;
	}
	
	return 0;
}


void archivosper(personas **p){
	FILE *archivo;
	archivo = fopen("personas.txt","r");
	if (!archivo) printf("No se encuentra el archivo de clientes\n");
	else{
		int x;
		char campo[20];
		while (!(feof(archivo))){
			personas *t = new personas;
		//	t->next=NULL;
			fscanf(archivo, "%i", &x);
			t->cedula = x;
			fscanf(archivo, "%s", &campo);
			strcpy(t->nombre,campo);
			fscanf(archivo, "%s", &campo);
			strcpy(t->apellido,campo);
			fscanf(archivo, "%s", &campo);
			strcpy(t->direccion,campo);
			fscanf(archivo, "%i", &x);
		//	strcpy(t->fecha,campo);
			t->fecha=x;
			fscanf(archivo, "%s", &campo);
			strcpy(t->domicilio,campo);
			fscanf(archivo, "%i", &x);
			t->deuda = x;
			fscanf(archivo, "%i", &x);
			t->efectivo = x;
			t->capitalto = x;
			t->cuen = NULL;
		
				t->next = NULL;
				t->next=*p;
				*p = t;
		
			
		}
	}	
	fclose(archivo);
}
void archivoscu(personas **p){
	FILE *archivo;
	archivo = fopen("cuentas.txt","r");
	if (!archivo) printf("No se encuentra el archivo de cuentas\n");
	else{
		int x;
		personas *y = *p;
		char campo[20];
		while (!(feof(archivo))){
			y = *p;
			fscanf(archivo, "%i", &x);
			while ((y)&&(y->cedula != x)) y = y->next;
			if (y){
				cuentas *t = new cuentas;
				fscanf(archivo, "%i", &x);
				t->banco=x;
				fscanf(archivo, "%i", &x);
				t->nrocuenta = x;
				fscanf(archivo, "%i", &x);
				t->saldo = x;
				y->capitalto += x;
				t->trans = NULL;
				if (!y->cuen){
					t->next = NULL;
					y->cuen = t;
				}
				else {
					t->next = y->cuen;
					y->cuen = t;
				}
		
			}
		}
	}
	fclose(archivo);
}

void escribirtran(personas **p){
	FILE *archivo;
	archivo = fopen("transacciones.txt","w");
	personas *t = *p;
	while (t){
		if (t->cuen){
			cuentas *q = t->cuen;
			while (q){
				if (q->trans){
					transacciones *y = q->trans;
					while (y){
						if ((t->next)||(q->next)||(y->next)) fprintf(archivo, "%i\n%i\n%s\n%s\n%i\n%s\n",q->nrocuenta,y->codigope,y->tipoop,y->fecha,y->monto,y->descripcion);
						else fprintf(archivo, "%i\n%i\n%s\n%s\n%i\n%s",q->nrocuenta,y->codigope,y->tipoop,y->fecha,y->monto,y->descripcion);
						y = y->next;
					}
				}
				q = q->next;
			}	
		}
		t = t->next;
	}
	fclose(archivo);
}

void escribircuen (personas **p){
	FILE *archivo;
	archivo = fopen("cuentas.txt","w");
	personas *t = *p;
	while (t){
		if (t->cuen){
			cuentas *q = t->cuen;
			while (q){
				if ((t->next)||(q->next)) fprintf(archivo, "%i\n%i\n%i\n%i\n",t->cedula,q->banco,q->nrocuenta,q->saldo);
				else fprintf(archivo, "%i\n%i\n%i\n%i",t->cedula,q->banco,q->nrocuenta,q->saldo);
				q = q->next;
			}	
		}
		t = t->next;
	}
	fclose(archivo);
}



personas *personaporcuenta (personas *p, int nrocuenta){
	personas *t = p;
	while (t){
		if (t->cuen){
			cuentas *y = t->cuen;
			while ((y)&&(y->nrocuenta != nrocuenta)) y = y->next;
			if (y) return t;
		}	
		t = t->next;
	}
	return NULL;
}

void archivostran(personas **p){
	FILE *archivo;
	archivo = fopen("transacciones.txt","r");
	if (!archivo) printf("No se encuentra el archivo de transacciones\n");
	else{
		int x;
		personas *y = *p;
		cuentas *q;
		char campo[20];
		while (!(feof(archivo))){
			fscanf(archivo, "%i", &x);
			y = personaporcuenta(*p,x);
			q = y->cuen;
			while ((q)&&(q->nrocuenta != x)) q = q->next;
			if (q){
				transacciones *t = new transacciones;
				fscanf(archivo, "%i", &x);
				t->codigope = x;
				fscanf(archivo, "%s", &campo);
				strcpy(t->tipoop,campo);
				fscanf(archivo, "%s", &campo);
				strcpy(t->fecha,campo);
				fscanf(archivo, "%i", &x);
				t->monto = x;
				fscanf(archivo, "%s", &campo);
				strcpy(t->descripcion,campo);
				if (!y->cuen){
					t->next = NULL;
					q->trans = t;
				}
				else {
					t->next = q->trans;
					q->trans = t;
				}
		
			}
		}
	}
	fclose(archivo);
}

void escribirarper (personas **p){
	FILE *archivo;
	archivo = fopen("personas.txt","w");
	personas *t = *p;
	while (t){
		if (t->next) fprintf(archivo,"%i\n%s\n%s\n%s\n%i\n%s\n%i\n%i\n",t->cedula,t->nombre,t->apellido,t->direccion,t->fecha,t->domicilio,t->deuda,t->efectivo);
		else fprintf(archivo,"%i\n%s\n%s\n%s\n%i\n%s\n%i\n%i\n",t->cedula,t->nombre,t->apellido,t->direccion,t->fecha,t->domicilio,t->deuda,t->efectivo);
		t = t->next;
	}
	fclose(archivo);
}

void swapcuentas(cuentas **p,cuentas **temp){
	
	int nrocuenta=(*p)->nrocuenta;
	int saldo=(*p)->saldo;
	int banco=(*p)->banco;
	transacciones *q = (*p)->trans;
	(*p)->nrocuenta=(*temp)->nrocuenta;
	(*p)->saldo=(*temp)->saldo;
	(*p)->banco=(*temp)->banco;
	(*p)->trans = (*temp)->trans;
	(*temp)->nrocuenta=nrocuenta;
	(*temp)->saldo=saldo;
	(*temp)->banco=banco;
	(*temp)->trans=q;
	
}
void ordenarpornrocuentacreci(cuentas **cab){
cuentas *ax=*cab,*temp=*cab,*aux,*t;
while(ax->next){
     while(temp->next){
       temp=temp->next;
        if(temp->nrocuenta<ax->nrocuenta){
           swapcuentas(&(ax),&(temp));
        }
     }
     
ax=ax->next;
temp=ax;
}
aux=*cab;
            while(aux->next){

	            printf("Nro cuenta: [%i]   ", aux->nrocuenta);
				printf("banco : %i \n", aux->banco);
				printf("saldo: [%i] \n\n", aux->saldo);
				aux=aux->next;
			
			}
			system("PAUSE");
			
}
void ordenarporsaldodecre(cuentas **cab){
cuentas *ax=*cab,*temp=*cab,*aux,*t;
while(ax->next){
     while(temp->next){
       temp=temp->next;
        if(temp->saldo>ax->saldo){
           swapcuentas(&(ax),&(temp));
        }
     }
     
ax=ax->next;
temp=ax;
}
aux=*cab;
            while(aux->next){

	            printf("Nro cuenta: [%i]   ", aux->nrocuenta);
				printf("banco : %i \n", aux->banco);
				printf("saldo: [%i] \n\n", aux->saldo);
				aux=aux->next;
			
			}
			system("PAUSE");
			
}
void crear(cuentas **p,int banco,int nrocuenta,int saldo){
cuentas *ax,*t;
if(p==NULL){
	 t=new cuentas;
     t->banco=banco;
     t->nrocuenta=nrocuenta;
     t->saldo=saldo;
     t->next=*p;
     t->trans=NULL;
     *p=t;
      
}
else
{
		t = new cuentas;
		t->nrocuenta = nrocuenta;
		t->saldo = saldo;
	    t->banco=banco;
		t->trans = NULL;
		t->next = *p;
		*p = t;
}
}
void eliminarauxiliar (cuentas **p){
	cuentas *t = *p;
	while (*p){
		t = *p;
		*p = (*p)->next;
		delete(t);
	}
}
void consultasATM(personas*A){//-----------------------------CONSULTAR POR BANCO--------------------------------------
 personas *ax=A;
 cuentas *temp,*cab,*p=NULL,*j=NULL;
 int y;
 int x=0;
 if(A){
 		while((x!=1)&&(x!=2)&&(x!=3)){   
				printf("\tIntroduzca su banco\n");
					printf("\t1.banesco \n");
					printf("\t2.mercantil\n ");		
					printf("\t3.probincial \n");
		        	scanf("%i",&x);
			}
		while(ax){
			temp=ax->cuen;
		while(temp){
			
			if(temp->banco==x)
			 
			{
				crear(&p,x,temp->nrocuenta,temp->saldo);
				printf("\nCedula : [%i]   ", ax->cedula);
				printf("Nombre : [%s  %s]   ", ax->nombre,ax->apellido);
				printf("Direccion : %s \n", ax->direccion);
				printf("capital total total: [%i] \n", ax->capitalto);
				printf("efectivo total: [%i] \n", ax->efectivo);
				printf("Deuda : %i \n", ax->deuda);	
				printf("\nCedula : [%i]   ", ax->cedula);
				printf("Nro cuenta: [%i]   ", temp->nrocuenta);
				printf("banco : %i \n", temp->banco);
				printf("saldo: [%i] \n\n", temp->saldo);
		
			}
			temp=temp->next;
		}
		ax=ax->next;
		
	}
	printf("1.Ordenadas por saldo decreciente\n");
	printf("2.Ordenadas por cuenta creciente\n");
	scanf("%i",&y);
	if(y==1){
	ordenarporsaldodecre(&p);
	eliminarauxiliar(&p); 
     }
	else
	 if(y==2){
	 ordenarpornrocuentacreci(&p);
	 eliminarauxiliar(&p); 	
     } 
 	
 }
 
 	
}

void swap(personas **p,personas **temp){
	int cedula=(*p)->cedula;
	int capitalto=(*p)->capitalto;
	int deuda=(*p)->deuda;
	int efectivo=(*p)->efectivo;
	char apellido[10];
	strcpy(apellido,(*p)->apellido);
	char nombre[10];
	strcpy(nombre,(*p)->nombre);
	char direccion[10];
	strcpy(direccion,(*p)->direccion);
	char domicilio[10];
	strcpy(domicilio,(*p)->domicilio);
	int fecha=(*p)->fecha;
	cuentas (*q)=(*p)->cuen;
	(*p)->cedula=(*temp)->cedula;
	(*p)->capitalto=(*temp)->capitalto;
	(*p)->deuda=(*temp)->deuda;
	(*p)->efectivo=(*temp)->efectivo;	
	strcpy((*p)->apellido,(*temp)->apellido);
	strcpy((*p)->nombre,(*temp)->nombre);
	strcpy((*p)->direccion,(*temp)->direccion);
    strcpy((*p)->domicilio,(*temp)->domicilio);

	(*p)->cuen=(*temp)->cuen;
	(*temp)->cedula=cedula;
	(*temp)->capitalto=capitalto;
	(*temp)->deuda=deuda;
	(*temp)->efectivo=efectivo;
	(*temp)->fecha=fecha;
	strcpy((*temp)->apellido,apellido);
	strcpy((*temp)->nombre,nombre);
	strcpy((*temp)->direccion,direccion);
    strcpy((*temp)->domicilio,domicilio);
	(*temp)->cuen=q;
	
}


void consultacedula(personas**A){
personas *ax=*A,*temp=*A,*aux=*A,*t=*A;
while(ax->next){
     while(temp->next){
       temp=temp->next;
        if(temp->cedula<ax->cedula){
           swap(&(ax),&(temp));
        }
     }
     
ax=ax->next;
temp=ax;
}
}
void consultapellido(personas**A){
personas *ax=*A,*temp=*A,*aux=*A,*t=*A;
char x[10];
while(ax->next){
     while(temp->next){
       temp=temp->next;
        if(strcmp(ax->apellido,temp->apellido)>0){
           swap(&(ax),&(temp));
        }
     }
     
ax=ax->next;
temp=ax;
}
}

void consultanomb (personas **p){
	personas *temp=*p,*aux1=*p;
	int x,ci;
	char n[10],c[10];
    printf("1.Ordenado por apellido\n 2.Ordenado por cedula\n'");
    scanf("%i",&x);

if (x==1){	
	printf("introduzca el nombre:");
		/*fflush(stdin);
     	fgets(n,10,stdin);*/
     	scanf("%s",n);
	consultapellido(p);	
			
		 while (temp) 
		{ 
			if (strcmp(n,temp->nombre)==0) 
			{	
				printf("Nombre : [%s  %s]  ", temp->nombre,temp->apellido);
				printf("\n Cedula : [%i]   ", temp->cedula);
				printf("Direccion : %s \n", temp->direccion);
				printf("efectivo total: [%i] \n", temp->efectivo);
				printf("Deuda : %i \n\n", temp->deuda);
		
 		}
 		temp=temp->next;
	}
}else if(x==2){
        printf("introduzca el nombre:");
	/*	fflush(stdin);
     	fgets(c,10,stdin);*/
     	scanf("%s",c);
	    consultacedula(p);	
			
			  while (aux1) 
		{
			if (strcmp(c,aux1->nombre)==0) 
			{	
				printf("Nombre : [%s  %s]  ", aux1->nombre,aux1->apellido);
				printf("\n Cedula : [%i]   ", aux1->cedula);
				printf("Direccion : %s \n", aux1->direccion);
				printf("efectivo total: [%i] \n", aux1->efectivo);
				printf("Deuda : %i \n\n", aux1->deuda);
		
 		}
 		aux1=aux1->next;
	
}

}
}




void consultarpe(personas **p) { // para consultar personas en el sistema
	personas *temp = *p;
	cuentas *c=NULL;
	int op,x;
	int c1,cont=0;
	int sumaba=0,sumame=0,sumave=0;
	char n[10];
	if (p)	
{  	
     printf("por cedula 1\n por nombre  2\n");
     scanf("%i",&x);


  if(x==1){
		printf("\nIntroduce el numero de cedula:  ");
		scanf("%i",&c1);
	
		while (temp) 
		{
			if (temp->cedula == c1) 
			{	
				printf("\nCedula : [%i]   ", temp->cedula);
				printf("Nombre : [%s  %s]   ", temp->nombre,temp->apellido);
				printf("Direccion : %s \n", temp->direccion);
				printf("capital total total: [%i] \n", temp->capitalto);
				printf("efectivo total: [%i] \n", temp->efectivo);
				printf("Deuda : %i \n", temp->deuda);
			    c=temp->cuen;
				while(c)
				{	if(c->banco==1){
					sumaba+=c->saldo;				
				}
			   else if(c->banco==2){
					sumame+=c->saldo;				
				}else if (c->banco==3){
					sumave+=c->saldo;
					
				}
			   	 	printf("banco [%i] numero de cuenta : [%i]  saldo: [%i]\n\n ",c->banco,c->nrocuenta,c->saldo);
					
				 c=c->next;
				}
				printf("saldo en banesco [%i]\n",sumaba);
				printf("saldo en mercantil [%i]\n",sumame);
				printf("saldo en provincial [%i]\n",sumave);
			}
	 	temp = temp->next;
		    
			}

		}else if(x==2){
			
			consultanomb(p);
}
	
}else printf("NO HAY PERSONAS EN EL SISTEMA");  
system("pause");
}
	
void agregarper(personas **p) {
personas *tempo = *p; //Agregar Personas
int ci;
	if (!(*p))
	{
		tempo = new personas;
	printf("Introduzca su cedula de identidad: ");
	scanf("%i",&tempo->cedula);
	printf("Introduza su nombre: ");
	fflush(stdin);
    fgets(tempo->nombre,10,stdin);
	printf("Introduza su apellido: ");
    fflush(stdin);
	fgets(tempo->apellido,10,stdin);
	printf("Introduzca su direccion : ");
	scanf("%s", tempo->direccion);
	printf("Introduza la fecha: ");
	scanf("%i", &tempo->fecha);
	printf("Introduza su domicilio: ");
	scanf("%s", tempo->domicilio);
	printf("introduzca su efectivo ");
	scanf("%i",&tempo->efectivo);
	printf("introduzca su deuda inicial ");
	scanf("%i",&tempo->deuda);
	tempo->capitalto=0;
	tempo->capitalto+=tempo->efectivo;	
	tempo->next = NULL;
	tempo->cuen=NULL;
	*p =tempo;

	}
else
{    while (tempo->next )
	tempo = tempo->next;
	tempo->next = new personas;
		printf("Introduzca su cedula de identidad: ");
		scanf("%i",&ci);
	//	printf("%i",cedula(p,ci));
	  	//if(!(cedula(p,ci))){
         tempo->next->cedula=ci;
		printf("Introduza su nombre: ");
		fflush(stdin);
     	fgets(tempo->next->nombre,10,stdin);
		printf("Introduza su apellido: ");
        fflush(stdin);
	    fgets(tempo->next->apellido,10,stdin);
		printf("Introduzca su direccion: ");
		scanf("%s",tempo->next->direccion);
		printf("Introduza la fecha: ");
		scanf("%i",&tempo->next->fecha);
		printf("Introduza su domicilio: ");
		scanf("%s",tempo->next->domicilio);
		printf("introduzca su efectivo ");
		scanf("%i",&(tempo->next->efectivo));
		printf("introduzca su deuda inicial ");
		scanf("%i",&tempo->next->deuda);
		tempo->next->capitalto=0;
		tempo->next->capitalto+=tempo->next->efectivo;	
		tempo->next->next = NULL;
		tempo->next->cuen=NULL;
	}

}





void crearcuenta(personas **p){
int ci,x=0;
int r=1;
personas *t=*p;
cuentas *ax,*cu;//cu es para agregar cuentas nuevas despues que ax llegue al final
  if (*p==NULL)
      printf("no hay personas en el sistema\n");
      else
     {
         	printf("introduzca su numero de cedula");
         	scanf("%i", &ci);
 	if ((cedula(p,ci))== 1)
	{ //este while es para buscar a la persona que se le desea agregar la cuenta
	
	 while (t){
	 	
	 	  if(t->cedula==ci){
		  if (t->cuen==NULL){ 
		     	          //------------------------------------cu apunta a la primera para que no se pierda
	         	ax=new cuentas;             	//---------------------------t cuen se crea 
	               while((x!=1)&&(x!=2)&&(x!=3)){   //--------------------------------------ax es donde se va a llenar
		        	printf("\tIntroduzca su banco\n");
					printf("\t1.banesco \n");
					printf("\t2.mercantil\n ");		
					printf("\t3.provincial\n");
		        	scanf("%i",&x);
			}
	        ax->banco=x;
			printf("\tIntroduzca numero de cuenta ");
			scanf("%i",&ax->nrocuenta);
			printf("\tIntroduzca el saldo de la cuenta inicial: ");
			scanf("%i",&ax->saldo);
			t->capitalto+=ax->saldo;
			ax->trans=NULL;
			ax->next=t->cuen;
			t->cuen=ax;
		
			}else{ 
			cu=t->cuen;
			    ax=new cuentas;//--------------------------------------ax es donde se va a llenar
	   	        while((x!=1)&&(x!=2)&&(x!=3)){   //--------------------------------------ax es donde se va a llenar
				printf("\tIntroduzca su banco\n");
					printf("\t1.banesco \n");
					printf("\t2.mercantil\n ");		
					printf("\t3.Provincial \n");
		        	scanf("%i",&x);
			}
	        ax->banco=x;
			printf("\tIntroduzca numero de cuenta ");
			scanf("%i",&ax->nrocuenta);
			if(!(existcuen(ax->nrocuenta,ci,p))){
				printf("\tIntroduzca el saldo de la cuenta inicial: ");
				scanf("%i",&ax->saldo);
				t->capitalto+=ax->saldo;
				ax->trans=NULL;
		        t->cuen=ax;	
			    ax->next=cu;	
			    
				
			}else
			{
				printf("\n\t\t\tESTE NUMERO DE CUENTA YA ESTA ASOCIADO A ESTA PERSONA\n\n");
				system("pause");
			}
		}
      	}
	 t=t->next;
		} 
			
	} 
     
 } 
}

void modificarper(personas **p){
	personas *t=*p;
	int ci;
printf("introduzca la cedulaque va a modificar");
scanf("%i",&ci);
if (*p==NULL)
      printf("no hay personas en el sistema\n");
      else{
	  	 
	  	 if (t->cedula==ci)
	{	    
	
		    printf("Introduza su nombre: ");
			scanf("%s", &t->nombre);
			printf("Introduza su apellido: ");
			scanf("%s", &t->apellido);
			printf("Introduzca su direccion : ");
			scanf("%s", &t->direccion);
			printf("Introduza la fecha: ");
			scanf("%i", &t->fecha);
			printf("Introduza su domicilio: ");
			scanf("%s", &t->domicilio);
			
	  }else{
	
	  	while((t)&&(t->next)){
	
		if(t->next->cedula==ci){
		
			printf("Introduza su nombre: ");
			scanf("%s", &t->next->nombre);
			printf("Introduza su apellido: ");
			scanf("%s", &t->next->apellido);
			printf("Introduzca su direccion : ");
			scanf("%s", &t->next->direccion);
			printf("Introduza la fecha: ");
			scanf("%i", &t->next->fecha);
			printf("Introduza su domicilio: ");
			scanf("%s", &t->next->domicilio);
			
     }
      	 t=t->next;
	  }	
}

}

}
void eliminartrans(transacciones **p){
		transacciones *aux;
while ((*p)){
		aux = (*p);
		(*p)= (*p)->next;
		delete (aux);
	}
}

void eliminarcuentas(cuentas **p){
	cuentas *aux;
	if(*p){	
	
	while ((*p)){
		eliminartrans(&(*p)->trans);
		aux = (*p);
		(*p)= (*p)->next;
		delete (aux);
	}
}
}


void eliminarper(personas **p){
	personas *t=*p;
	int ci;
	printf("introduzca la cedula del usuario que desea eliminar: ");
	  scanf("%i",&ci);
	  if(*p){
	  	    if((*p)->cedula==ci){
			  	eliminarcuentas(&(*p)->cuen);
	  	    	(*p)=(*p)->next;
	  	    	 delete(t);
	  	    	 t=(*p);
	  	    	
	  	      }else{ 
				while ((t)&&(t->next))
				{   
					if (t->next->cedula==ci){
	  	      	    	personas *ax=t->next;
						eliminarcuentas(&ax->cuen);
	  	      	    	t->next=t->next->next;
	  	      	    	delete(ax);
						}
	  	      	    t=t->next;
				}
 			
			}
	  	
	  }else {
	 			 printf("no hay usuarios en el sistema "); 
	  			system("pause");
 			}
	
}

void eliminarcuen(personas **p){
	personas *t=*p;
	 int x,ci;
	 printf(" introduzca el numero de cedula");
	  scanf("%i",&ci);
	     while(t){
	     	if(t->cedula==ci){
	     		cuentas *cu=t->cuen;
	     		if(cu){
	     		 printf("introduzca el numero de cuenta a eliminar");
	     		  scanf("%i",&x);
	     		  if(existcuen(x,ci,p)){
	     		  	if(cu->nrocuenta==x)
	     		  	{   cuentas *ax=cu;
	     		  	    t->capitalto-=ax->saldo;//-------------------------------------error al eliminar la primera cuenta
	     		  		eliminartrans(&ax->trans);
	     		  	    cu=cu->next;
	     		  	    delete(ax);
	     		  	    ax=cu;
					   }
			       else{
	     		    while((cu)&&(cu->next)){
	     		    	 if(cu->next->nrocuenta==x)
						  {
	     		   	 	   cuentas *ax=cu->next;
	     		   	 	   t->capitalto-=ax->saldo;
	     		   	 	   eliminartrans(&ax->trans);
	     		   	 	   cu->next=ax->next;
	     		   	 	   delete(ax);
	     		   	 	   ax=cu;
					   		}	     		   	
	     		    	cu=cu->next;
				    	 } 
	     	       }
	     		
	     	}else{
	     		printf("no esiste este numero de cuenta");
				 }
			 }
	     	}
	     	t=t->next;
	     	
		 }
	   
	
}

void consultcuen(personas **p){
	personas *t=*p;
	int ci,x;
	  printf("introduzca el numero de cedula\n");
	   scanf("%i",&ci);
	  while(t){
            if(t->cedula==ci){
            	cuentas *c=t->cuen;
			   printf("introduzca el numero de cuenta\n\n");
			   scanf("%i",&x);
			     while(c){
				     if(c->nrocuenta==x){
					 printf("banco [%i] numero de cuenta : [%i]  saldo: [%i]\n\n ",c->banco,c->nrocuenta,c->saldo);
				     	transacciones *tran=c->trans;
				     	  while(tran){
				     	  	
				  printf("codigo operacion:[%i] monto :[%i] fecha:[%s]  tipo:[%s] descripcion[%s]\n",tran->codigope,tran->monto,tran->fecha,tran->tipoop,tran->descripcion);
				     	  	tran=tran->next;	
						   }				     	
					 }
				  c=c->next;
				 } 
			   
			}	  
	  t=t->next;
	  }
system("pause");

}
void Depositar(personas **p){
	personas *t=*p;
	 int ci,x,monto,n;
	   printf("introduzca su cedula de identidad");
	    scanf("%i",&ci);
	      while(t){
	      	 if(t->cedula==ci){
	      	 	cuentas *c=t->cuen;
	      	 	  printf("introduzca el numero de cuenta que quiere depositar");
	      	 	   scanf("%i",&x);
	      	 	    while(c){
	      	 	    	if(c->nrocuenta==x)
						   
	      	 	    	printf("ingrese la cantidad de efectivo que desea depositar");
	      	 	    	scanf("%i",&monto);
	      	 	    	
						 if(monto<=t->efectivo){
						 transacciones *tra=new transacciones;
						 tra->next=NULL;
						 	c->saldo+=monto;
							 t->efectivo-=monto;
							 printf("ingrese el numero de la transferencia");
	      	 	                	scanf("%i",&tra->codigope);
									 printf("confirme el monto");
									 scanf("%i",&tra->monto);
									 printf("ingrese el motivo");
									scanf("%i",&tra->tipoop);
									printf("ingrese la fecha");
									scanf("%s",tra->fecha);	
												
							 	tra->next=c->trans;
							 	c->trans=tra;
							 
						 }else{
						 	printf("el monto excedio su limite de efcetivo");
						 	system("pasue");	
						 }   
	      	 	    c=c->next;	
					   }
	      	 	
			   }
	      
	      t=t->next;	
		  }
	
}


void pagardeudas(personas **p){
  personas *t=*p;
      int e,ci,x,monto,n;
      printf("pagar por:\n 1.efectivo\n 2.una cuenta de banco\n");
      scanf("%i",&e);
      
      
	   printf("introduzca su cedula de identidad\n");
	    scanf("%i",&ci);
	    
	    
	    if(e==2){
		
	     while(t){
	     	if(t->cedula==ci){
	     		cuentas *c=t->cuen;
	     		   printf("introduzca el numero de cuenta con la cual desea pagar\n");
	      	 	   scanf("%i",&x);
	     		    while(c){
	     		    	  if(c->nrocuenta==x){
	     		    	  		printf("ingrese la el monto que desea pagar");
	      	 	            	scanf("%i",&monto);
	      	 	            		
	     		    	  	 if((monto<=c->saldo)&&(monto<=t->deuda)){
	     		    	  	 	  c->saldo-=monto;
	     		    	  	 	  t->deuda-=monto;
	     		    	  	 	  	transacciones *tra=new transacciones;
	     		    	  	 	  	tra->next=NULL;
									 printf("ingrese el numero de la transferencia");
	      	 	                	scanf("%i",&tra->codigope);
									 printf("confirme el monto");
									 scanf("%i",&tra->monto);
									 printf("ingrese el motivo");
									scanf("%i",&tra->tipoop);
									printf("ingrese la fecha");
									scanf("%s",tra->fecha);
							
									 tra->next=c->trans;
									 c->trans=tra;	     		    	  	 	  
	     		    	  	 	  
								}else{
									printf("el monto no esta dentro de los limites del saldo o sobrepasa su deuda");
									system("pause");
								}
	     	
	     		    	  	
						   }
	     		    	  c=c->next;
	     		    
					 }

			 }
			 t=t->next;
	     	
		 }
	}else if(e==1){
		while (t){
			if(t->cedula==ci){
			printf("ingrese la el monto que desea pagar");
	      	scanf("%i",&monto);
	      	  if((monto<=t->efectivo)&&(monto<=t->deuda)){
			     t->efectivo-=monto;
			     t->deuda-=monto;
			  }else{
			  	printf("el monto no esta dentro de los limites del saldo o sobrepasa su deuda");
				system("pause");
			  }
	
			}
			t=t->next;
		}
	}
	
}

void Retirar(personas **p){
	personas *t=*p;
	int ci,x,monto;
	
	printf("introduzca su cedula");
	scanf("%i",&ci);
	while(t){
		if(ci==t->cedula){
			cuentas *c=t->cuen;
		printf("introduzca el numero de cuenta en el que desea retirar");
		scanf("%i",&x);
		 while(c){
		  if (x==c->nrocuenta){ 
		   printf("introduzca el monto");
		   scanf("%i",&monto);
		    if((monto<=c->saldo)&&(monto>0)){
		    	transacciones *tra=new transacciones;
	     		    	  	 	  	tra->next=NULL;
									 printf("ingrese el numero de la transferencia");
	      	 	                	scanf("%i",&tra->codigope);
									 printf("confirme el monto");
									 scanf("%i",&tra->monto);
									 printf("ingrese el motivo");
									scanf("%i",&tra->tipoop);
									printf("ingrese la fecha");
									scanf("%s",tra->fecha);
		    	t->efectivo+=monto;
		        c->saldo-=monto;
		        tra->next=c->trans;
		        c->trans=tra;
		    	
			}else printf("el monto pasa los limites del saldo");
		 
		 }	
		 
		  c=c->next;
		 }
	}
	t=t->next;	
		
	}
	
	
}











void modificarcuen(personas **p){
personas *t=*p;
   int ci,x;
   cuentas *c;
   
   
   printf("introduzca la cedulaque va a modificar");
scanf("%i",&ci);
if (*p==NULL)
      printf("no hay personas en el sistema\n");
      else{
	  	 while(t){
		   
	  	 if (t->cedula==ci)
       	{	    c=t->cuen;
	       printf("introduzca el nomero de cuenta que va a modificar");
	        scanf("%i",&x);
	       while(c){
		   
	       if (c->nrocuenta==x)
           {
	            printf("introduzca el numero de cuenta");
				scanf("%i",&c->nrocuenta);	   
			    printf("introduzca el monto \n");
			    scanf("%i",&c->saldo);   
			}
		c=c->next;
           }
      	 
	  }
	  	t=t->next;
}

}

}
   
int rangomonto(cuentas **c,int x,int y){
	cuentas *cu=*c;
	  while(cu){
	  	  if((cu->saldo>=x)&&(cu->saldo<=y))
	  	   return 1;
	  	   cu=cu->next;
	  }
	return 0;		
}


void consultamonto(personas **p){
   	 personas *t=*p;
   	   int x,y;
		  printf("introduzca el rango\n ");
		  printf("desde:");
		  scanf("%i",&x);
		  printf("\nhasta:");
		  scanf("%i",&y);
		  
		  while(t){
		  	if(rangomonto(&t->cuen,x,y)){
		  		printf("Nombre : [%s  %s]  ", t->nombre,t->apellido);
				printf("\n Cedula : [%i]   ", t->cedula);
				printf("Direccion : %s \n", t->direccion);
				printf("efectivo total: [%i] \n", t->efectivo);
				printf("Deuda : %i \n\n", t->deuda);
		  	
			  }
		  	t=t->next;
		
		  }
		  
		  system("pause");
   	
}

int capitaltocuen(cuentas *c){
	
	int x=0;
	while(c){
		x+=c->saldo;
		c=c->next;	
	}
	return x;
	
}



void consultadeuda(personas **p){
	personas *temp=*p; 
	  int x,y;
		  printf("introduzca el rango\n ");
		  printf("desde:");
		  scanf("%i",&x);
		  printf("\nhasta:");
		  scanf("%i",&y);
		  
		   while(temp){
		  	if((temp->deuda>=x)&&(temp->deuda<=y)){
		  		printf("Nombre : [%s  %s]  ", temp->nombre,temp->apellido);
				printf("\n Cedula : [%i]   ", temp->cedula);
				printf("Direccion : %s \n", temp->direccion);
				printf("efectivo total: [%i] \n", temp->efectivo);
				printf("Deuda : [%i] \n", temp->deuda);
				printf("capital total[%i]\n\n",capitaltocuen(temp->cuen));
		  	
			  }
		  	temp=temp->next;
		
		  }
	  system("pause");
	
}






//---------------------------------------------------------menu------------------------------------------------------------------------

void consultas(personas **p){
	int op = -1, x=0;
	char k='\0';
	
	while ( op ){
		system("cls");	
		printf( "\n\n\t\t MENU DE MANTENIMIENTO USUARIOS\n ");
	
		printf("1.\tConsultar usuario\n");
		printf("2.\tconsultar cuentas\n");	
		printf("3.\tConsultar Bancos\n");
		printf("4.\tConsultar por montos\n");
		printf("5.\tConsultar por deudas\n\n");
		printf("0.\tSALIR Del MENU\n\n ");
		
		 k=_getch();	
		switch (k){
			case '0': op=0;
		
		   		 break;
			case '1':
				      consultarpe(p);
		        break;
		        
			case '2': 
			            consultcuen(p);
		        break;   
				
				
			case '3': 
			           consultasATM(*p);
		        break;   
		    case '4':   
			            consultamonto(p);
			  break; 
		  case '5':
		  	   			consultadeuda(p);
		   break;	  
			  
			  
			     
		        
    }


};
	
}


void manucuenta(personas **p){
	int op = -1, x=0;
	char k='\0';
	
	while ( op ){
		system("cls");	
		printf( "\n\n\t\t MENU DE MANTENIMIENTO CUENTAS\n ");
		printf( "1.\tNuevo cuenta\n ");
		printf( "2.\tModificar cuenta\n ");
		printf( "3.\tEliminar cuenta\n\n");
		printf( "0.\tSALIR DEL MENU \n");
		
		 k=_getch();	
		switch (k){
			case '0': op=0;
		    
		   		 break;
			case '1':
				        crearcuenta(p); 
		        break;
			case '2': 
			          
		        break;
			case '3': 
			         eliminarcuen(p);
				break;		        	        
    }
};

}


void manusuario(personas **p){
	int op = -1, x=0;
	char k='\0';
	
	while ( op ){
		system("cls");	
		printf( "\n\n\t\t MENU DE MANTENIMIENTO USUARIOS\n ");
		printf( "1.\tNuevo usuario\n ");
		printf( "2.\tModificar usuario\n ");
		printf( "3.\tEliminar usuario\n\n");
		printf( "0.\tSALIR Del MENU\n ");
		
		 k=_getch();	
		switch (k){
			case '0': op=0;
		
		   		 break;
			case '1':
				        agregarper(p);
		        break;
			case '2': 
			            modificarper(p);
		        break;
			case '3': 
				        eliminarper(p);
				break;		        
		        
    }


};
	
}

void menu2(personas **p) {
	int op = -1, x=0;
	char k='\0';
		while ( op ){
			system("cls");	
			printf( "\n\n\t\tUSUARIOS Y CUENTAS\n ");
			printf( "1.\tUsuarios\n ");
			printf( "2.\tCuentas\n ");
			
			printf( "0.\tSALIR del sistema\n\n ");
		
		   k=_getch();	
			switch (k){
			case '0': 
				op=0;
			 break;
			case '1':
		           manusuario(p);
		        break;
			case '2': 
			    	manucuenta(p);
		        break;
			case '3': 
				break;		        
		        
    }


};
	
}
void operaciones(personas **p){
	int op = -1, x=0;
	 char k='\0';
		while ( op ){
			system("cls");	
			printf( "\n\n\t\tCONTROL DE OPERACIONES\n ");
			printf( "1.\tDepositar desde el efectivo\n ");
			printf( "2.\tRetirar\n ");
			printf( "3.\tPagar deudas\n\n");
			printf( "0.\tSALIR del sistema\n\n ");
		
		   k=_getch();	
			switch (k){
			case '0': op=0;
		
		   		 break;
			case '1':
		            Depositar(p);
		        break;
			case '2': 
					Retirar(p);
		        break;
			case '3': 
		        	pagardeudas(p);
				break;		        
		        
    }
	
	
}
}

int main() {
	int op = -1, x=0;
	char k='\0';
	personas *p=NULL;
	archivosper(&p);
	archivoscu(&p);
	archivostran(&p);
		while ( op ){
		system("cls");	
			printf( "\n\n\t\tCONTROL DE CUENTAS\n ");
			printf( "1.\tMantenimiesto\n ");
			printf( "2.\tOperaciones\n ");
			printf( "3.\tConsultas\n\n");
			printf( "0.\tSALIR del sistema\n\n ");
		
		   k=_getch();	
			switch (k){
			case '0': op=0;
		
		   		 break;
			case '1':
		          menu2(&p);
		        break;
			case '2': operaciones(&p);
		        break;
			case '3': 
		        	consultas(&p);
				break;		        
		        
    }

	
};
	escribirtran(&p);
    escribircuen(&p);
	escribirarper(&p);
	return 0;

}

