#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define DEVICE "/dev/encdev"
#define DEVICE1 "/dev/decdev"

int main(){

	int f;
	do{
		char input[1024];
		printf("What you wanna do?");
		scanf("%s",input);
		if(strcmp(input,"enc")==0){
			char ch ;
			char writer[100];
			char reader[100]; 
			f = open(DEVICE, O_RDWR);
			if(f != -1){

				scanf("%[^\n]", writer);
				printf("device: %s\n", writer);
				write(f, writer, sizeof(writer));
				read(f, reader, sizeof(reader));
				printf("device: %s\n", reader);

				FILE *fr;
				char * temp = reader[1] ;
			    fr = fopen("encdata.txt", "a+");
			    int i ;
			    for(i=1 ; reader[i]!=NULL ; i++){
			  		printf("here\n");
			    }
			    fwrite (&reader, sizeof(char)*i, 1, fr);
			    fclose(fr);
			}
			else
				printf("Error opening file\n");
			close(f);
		}
		else if(strcmp(input,"dec")==0){
			char ch ;
			char writer[100];
			char reader[100]; 
			f = open(DEVICE1, O_RDWR);
			if(f != -1){

				FILE *fr1;
				fr1 = fopen("encdata.txt", "a+");
				fseek(fr1,0,SEEK_SET);
				char c;
				c = fgetc(fr1);
				int p=0;
				while( c != EOF)
				{
					printf("%c",c);
					writer[p]=c;
					p++;
					c = fgetc(fr1);      
				}
				fclose(fr1);
				p++;
				writer[p]="/n";

				printf("device: %s\n", writer);
				write(f, writer, sizeof(writer));
				read(f, reader, sizeof(reader));
				printf("device: %s\n", reader);

				FILE *fr;
			    fr = fopen("decdata.txt", "a+");
			    if(fr==NULL){
			    	printf("here%d\n",fr);
			    }
			    int i ;
			    for(i=1 ; reader[i]!=NULL ; i++){
			  		printf("here\n");
			    }
			    fwrite (&reader, sizeof(char)*i, 1, fr);
			    fclose(fr);

			}
			else
				printf("Error opening file\n");
			close(f);


		}
		else
			printf("Wrong Command entered\n");
	}while(1);

	return 0;
}






/*int clearHistory()
{
  FILE *fr;
  fr = fopen(location, "w+");
  fclose(fr);
  return 1;
}


int readHistory()
{
  FILE *fr;
  fr = fopen(location, "a+");
  fseek(fr,0,SEEK_SET);
  char c;
  c = fgetc(fr);
  while( c != EOF)
  {
  	printf("%c",c);
    c = fgetc(fr);      
  }
  fclose(fr);
  return 1;
}


void writeHistory(char **args)
{
  FILE *fr;
  fr = fopen(location, "a+");
  for(int i=0 ; args[i]!=NULL ; i++){
  	fprintf(fr, "%s ", args[i]);
  }
  fprintf(fr, "\n");
  fclose(fr);
}*/




