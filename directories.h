#pragma once
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <string>

struct DIRECTORIES {
  std::string pwd = realpath("./", NULL);
  /*std::string pwd2 = getenv("PWD"); */

std::vector<std::string> getFileList(const char *path)	{
	std::vector<std::string> files,aux;
	DIR *dir_temp;
	struct dirent *file_dir;
	char *temp;
	char *directorio_path;
	int len_directorio_path;
	int len_file_path;
	char *archivo_dir;
	int i = 0;
	
	dir_temp = opendir(path);
	if(dir_temp != NULL)	{
		len_directorio_path = strlen(path);
		directorio_path = (char*)malloc(len_directorio_path+2);
		memcpy(directorio_path,path,len_directorio_path);
		if(directorio_path[len_directorio_path - 1] == '\\' || directorio_path[len_directorio_path - 1] == '/' ){
			directorio_path[len_directorio_path] = '\0';
		}
		else	{
			directorio_path[len_directorio_path] = '/';
			directorio_path[len_directorio_path+1] = '\0';
		}
		//printf("Directorio: %s\n",directorio_path);
		while((file_dir = readdir(dir_temp))){
			archivo_dir = NULL;
			if(strcmp(file_dir->d_name,".") != 0 && strcmp(file_dir->d_name,"..") != 0){
				///printf("examinando %s\n",file_dir->d_name);
				len_file_path = strlen(file_dir->d_name);
				archivo_dir = (char*) calloc(len_directorio_path+len_file_path+4,1);
				if(archivo_dir != NULL){
					sprintf(archivo_dir,"%s%s",directorio_path,file_dir->d_name);
					if(is_regular_file(archivo_dir))	{
						files.push_back(archivo_dir);
					}
					else	{
						if(isDirectory(archivo_dir))	{
							//printf("Es directorio: %s\n",archivo_dir);
							aux = getFileList(archivo_dir);
							i = 0;
							while(i < aux.size())	{
								files.push_back(aux[i]);
								i++;
							}
						}
						else	{
							//another file type, device, unix special file etc...
						}
					}

				}
				else	{
		
				}
			}
		}
		closedir(dir_temp);
	}
	else	{
		printf("El parametro \"%s\" no es un directorio valido",path);
	}
	return files;
}


int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

off_t fsize(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}


int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

char *file_get_contents(const char* path, int*  r_length){
	FILE *fd = NULL;
	char *buffer = NULL;
	char temp[64];
	int length = 0,leido = 0,offset = 0;
	length = fsize(path);
	buffer =  (char*) calloc(length,1);
	if(buffer  != NULL)	{
		fd= fopen(path,"rb+");
		if(fd != NULL)	{
			while(!feof(fd))	{
				memset(temp,0,64);
				leido = fread(temp,1,64,fd);
				memcpy(buffer + offset,temp,leido);
				offset+= leido;
			}
			fclose(fd);
		}
		else	{
			perror("fopen()");
		}
	}
	else	{
		perror("calloc()");
	}
	if(r_length != NULL)	{
		r_length[0] = length;
	}
	return buffer;
}
};
