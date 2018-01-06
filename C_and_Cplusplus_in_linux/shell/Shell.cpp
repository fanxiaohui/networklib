
#include<cstdio>
#include<cstring>
#include<cstdlib>


int userlogin(struct passwd **);

int main()
{
	int ret,i=0;
	long ret_cwd;
	struct passwd *pw;
	char buf[128],hostname[16],usercwd[128];
	char *ptmp1;

	do{
		ret = userlogin(&pw);
	}while(ret != 1);

	getchar();

	while(1){
//to gethostname
		if(gethostname(buf,128)!=0){
			perror("gethostname()");
			return 0;
		}
//truncate hostname untill '.'
		while(buf[i]!='.'){
			hostname[i++] = buf[i];
		}
		i = 0;
//if the user is 'root' the symbol is '#'
//else '$'
//and the current work path is truncated from the last '/' to the end
		ret_cwd = (long)getcwd(usercwd,128);
		if(strcmp(usercwd,pw->pw_dir)==0){
			ret = sprintf(usercwd,"~\0",NULL);
		}
		else if(strcmp(usercwd,"/")!=0){
			ptmp1 = strrchr(usercwd,'/');
			sprintf(usercwd,"%s",ptmp1+1);
		}
		if(strcmp(pw->pw_name,"root")==0){
			sprintf(buf,"*[%s@%s %s]# ",
					pw->pw_name,hostname,usercwd);
		}
		else{
			sprintf(buf,"*[%s@%s %s]$ ",
					pw->pw_name,hostname,usercwd);
		}
//command
		ssize_t g_ret,len;
		char *line = NULL,*s_ret,*ptr=NULL;
		int con_cd=0;

		fprintf(stderr,"%s",buf);

		g_ret = getline(&line,&len,stdin);

		line[strlen(line)-1] = '\0';
		if(strcmp(line,"exit")==0){
			exit(-1);
		}
		ptr = line;
		s_ret = line;

		system(line);
		while(ptr!=NULL){
			s_ret = (char *)strsep(&ptr," ");

			if(strcmp(s_ret,"cd") == 0){
				con_cd=1;
				continue;
			}
			else if(con_cd == 1){
				chdir(s_ret);
			}
		}
	}
	return 0;
}


//login function
int userlogin(struct passwd **pw)
{
	char name[32],*passwd,*pret;
	struct spwd *sp;

	printf("login:");
	fflush(stdout);
	scanf("%s",name);

	passwd = getpass("password:");

	sp = getspnam(name);
	if(sp == NULL){
		fprintf(stdout,"no is user![%s]\n",name);
		return 0;
	}

	pret = crypt(passwd,sp->sp_pwdp);

	if(pret == NULL){
		fprintf(stdout,"crypt(%s)\n",name);
		return 0;
	}

	if(strcmp(pret,sp->sp_pwdp) == 0){
		printf("login successful!\n");
	}
	else{
		fprintf(stdout,"passwd is error!\n");
		return 0;
	}

	*pw = getpwnam(name);
	if(*pw == NULL){
		printf("getpwnam(%s) error\n",name);
		return 0;
	}

	return 1;

}
