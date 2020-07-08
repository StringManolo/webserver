#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CONFIG_VAR_LENGTH_CONST 12

char *ltrim(char *str, const char *seps);
char *rtrim(char *str, const char *seps);
char *trim(char *str, const char *seps);
int in_array(char **array, int size, char *lookfor );
int index_of(char **array, int size, char *lookfor );

int config_var_length = CONFIG_VAR_LENGTH_CONST;

char *defaults_config[CONFIG_VAR_LENGTH_CONST] = {"localhost","80","./public_html","./access.log","30","1048576","","OFF","ON","443","./cert.pem","./key.pem"};
char *variables_config[CONFIG_VAR_LENGTH_CONST] = {"IP","PORT","PATH","LOGFILE","TIMEOUT","MAXREQUESTSIZE","CACHEFILES","DIRLIST","SSL","SSLPORT","CERTFILE","CERTKEY"};

int found_config[CONFIG_VAR_LENGTH_CONST] ={0,0,0,0,0,0,0,0,0,0,0,0};

int read_config()	{
	FILE *config = NULL;
	config = fopen("page.conf","r");
	if(config == NULL)	{
		/*
			We need to add default values to main config MAP variable.
		*/
		return 0;
	}
	else	{
		int i = 0,line_length = 0,key_length = 0, value_length = 0,index_temp = 0;
		char *line = NULL,*aux,*key = NULL,*value = NULL;
		line = malloc(1024);
		while(fgets(line,1024,config) != NULL && !feof(config))	{
			trim(line,NULL);
			line_length = strlen(line);
			if(line[0] != '#')	{
				aux = strstr(line,"=");
				if(aux != NULL)	{
					key_length = aux -line;
					value_length = line_length-key_length - 1 ;
					printf("Line with value: %s\n",line);
					printf("%i - %i\n",key_length,value_length);
					if(key_length > 0 && value_length > 0)	{
						key = calloc(key_length+1,1);
						value = calloc(value_length+1,1);
						memcpy(key,line,key_length);
						memcpy(value,aux+1,value_length);
						trim(key,NULL);
						trim(value,NULL);
						printf("Key : %s\n",key);
						printf("Value : %s\n",value);
						if((index_temp = index_of(variables_config,CONFIG_VAR_LENGTH_CONST,key)) >= 0){
							printf("Key found [%s] index %i : %s\n",key,index_temp,variables_config[index_temp]);
							found_config[index_temp] = 1;
							
							/*
								We need to add key and value  to a MAP global config
								
							*/
						}
						else	{
							printf("Ignoring line with unexpected key: %s\n",line);	
						}
						free(key);
						free(value);
					}
					else	{
						printf("Ignoring line without value or key: %s\n",line);	
					}
				}
				else	{
					printf("Ignored line without equal sign: %s\n",line);
				}
			}
			else	{
				printf("Ignored comment line: %s\n",line);
			}
			i++;
		}
		free(line);
		fclose(config);
		
		/*
		We need to add default values of not found keys to a Global config MAP
		*/
	}
}

char *ltrim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}

char *rtrim(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}

char *trim(char *str, const char *seps)
{
    return ltrim(rtrim(str, seps), seps);
}

int in_array(char **array, int size, char *lookfor )
{
    int i;
    for (i = 0; i < size; i++)
        if (strcmp(lookfor, array[i]) == 0)
            return 1;
    return 0;
}

int index_of(char **array, int size, char *lookfor )
{
    int i;
    for (i = 0; i < size; i++)
        if (strcmp(lookfor, array[i]) == 0)
            return i;
    return -1;
}


int main()	{
	read_config();
	
}

