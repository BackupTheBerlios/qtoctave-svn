#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


/**Limpia el repositorio de los ficheros .svn*/


void limpiar_directorio(char *dir_name)
{
	DIR *dir=opendir(dir_name);
	struct dirent *entry;
	char *buffer;
	
	if(dir==NULL) return;
	
	buffer=(char*)malloc(sizeof(char)*(strlen(dir_name)+300));
	
	printf("Abriendo %s\n", dir_name);
	
	while ( (entry=readdir(dir))!=NULL )
	{
		struct stat buf;
		
		sprintf(buffer,"%s/%s", dir_name,entry->d_name);
		
		stat (buffer, &buf);
		
		if(S_ISDIR(buf.st_mode))
		{
			if( !strcmp(".svn",entry->d_name) )
			{
				
				printf("Eliminando svn: %s\n", buffer);
				
				sprintf(buffer, "rm -Rf \"%s/%s\"", dir_name,entry->d_name );
				
				system ( buffer );
				
			}
			else if(strcmp(".",entry->d_name)  &&  strcmp("..",entry->d_name) )
			{
				limpiar_directorio(buffer);
			}
		}
		
		//printf("%s\n",entry->d_name);
	}
	
	closedir(dir);
	
	free(buffer);
}



int main(int argn, char *argv[])
{
	if(argn<2)
		limpiar_directorio(".");
	else
		limpiar_directorio(argv[1]);
}

