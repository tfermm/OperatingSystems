#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define reading 0
#define writing 1

float f(float x){
	return (1.0/(1.0+x));
}

void main(){
	int i;
	int fds1[2];
	int fds2[2];
	int info[2];
	int max_forks = 2;
	int max_trapizoids = 64;
	int type;
	float sum=0;
	float temp;
	float delta_x;
	int upper_limit = 2;
	int lower_limit = 0;
	int finished = 0;

	int is_done = 0;

	char string[20] = {0};

	char buff[1024] = {0};

	float value;

	delta_x = ((upper_limit*1.0 - lower_limit*1.0)/ max_trapizoids*1.0);

	pipe(fds1);
	pipe(fds2);

	if (fork() == 0){
		while (1){	
			int type;
			float ans;
			close(fds1[writing]);
			read(fds1[reading], buff, sizeof(string));
			sscanf(buff,"%d %f %d",&type, &value, &is_done);
			switch(type){
				case 0:
					ans = f(value);
					break;
				case 1:
					ans = 2.0 * f(value);
					break;
			}
			memset(string, '\0', sizeof(string));
			if (!is_done){
				sprintf(string, "%f\0", ans);
				close(fds2[reading]);
				write(fds2[writing], string, sizeof(string));
			}
			else{
				break;
			}
		}
	}
	else if(max_forks > 1){
		if (fork() == 0){
			
			while (1){	
				int type;
				float ans;
				close(fds1[writing]);
				read(fds1[reading], buff, sizeof(string));
				sscanf(buff,"%d %f %d",&type, &value, &is_done);
				switch(type){
					case 0:
						ans = f(value);
						break;
					case 1:
						ans = 2.0 * f(value);
						break;
				}
				memset(string, '\0', sizeof(string));
				if (!is_done){
					sprintf(string, "%f\0", ans);
					close(fds2[reading]);
					write(fds2[writing], string, sizeof(string));
				}
				else{
					break;
				}
			}
		}
	}
	else if(max_forks > 2 && fork()==0){
		while (1){	
			int type;
			float ans;
			close(fds1[writing]);
			read(fds1[reading], buff, sizeof(string));
			sscanf(buff,"%d %f %d",&type, &value, &is_done);
			switch(type){
				case 0:
					ans = f(value);
					break;
				case 1:
					ans = 2.0 * f(value);
					break;
			}
			memset(string, '\0', sizeof(string));
			if (!is_done){
				sprintf(string, "%f\0", ans);
				close(fds2[reading]);
				write(fds2[writing], string, sizeof(string));
			}
			else{
				break;
			}
		}

	}
	else if(max_forks > 3 && fork()==0){
		while (1){	
			int type;
			float ans;
			close(fds1[writing]);
			read(fds1[reading], buff, sizeof(string));
			sscanf(buff,"%d %f %d",&type, &value, &is_done);
			switch(type){
				case 0:
					ans = f(value);
					break;
				case 1:
					ans = 2.0 * f(value);
					break;
			}
			memset(string, '\0', sizeof(string));
			if (!is_done){
				sprintf(string, "%f\0", ans);
				close(fds2[reading]);
				write(fds2[writing], string, sizeof(string));
			}
			else{
				break;
			}
		}

	}
	else if(max_forks > 4 && fork()==0){
		while (1){	
			int type;
			float ans;
			close(fds1[writing]);
			read(fds1[reading], buff, sizeof(string));
			sscanf(buff,"%d %f %d",&type, &value, &is_done);
			switch(type){
				case 0:
					ans = f(value);
					break;
				case 1:
					ans = 2.0 * f(value);
					break;
			}
			memset(string, '\0', sizeof(string));
			if (!is_done){
				sprintf(string, "%f\0", ans);
				close(fds2[reading]);
				write(fds2[writing], string, sizeof(string));
			}
			else{
				break;
			}
		}

	}
	else if(max_forks > 5 && fork()==0){
		while (1){	
			int type;
			float ans;
			close(fds1[writing]);
			read(fds1[reading], buff, sizeof(string));
			sscanf(buff,"%d %f %d",&type, &value, &is_done);
			switch(type){
				case 0:
					ans = f(value);
					break;
				case 1:
					ans = 2.0 * f(value);
					break;
			}
			memset(string, '\0', sizeof(string));
			if (!is_done){
				sprintf(string, "%f\0", ans);
				close(fds2[reading]);
				write(fds2[writing], string, sizeof(string));
			}
			else{
				break;
			}
		}

	}
	else if(max_forks > 6 && fork()==0){
		while (1){	
			int type;
			float ans;
			close(fds1[writing]);
			read(fds1[reading], buff, sizeof(string));
			sscanf(buff,"%d %f %d",&type, &value, &is_done);
			switch(type){
				case 0:
					ans = f(value);
					break;
				case 1:
					ans = 2.0 * f(value);
					break;
			}
			memset(string, '\0', sizeof(string));
			if (!is_done){
				sprintf(string, "%f\0", ans);
				close(fds2[reading]);
				write(fds2[writing], string, sizeof(string));
			}
			else{
				break;
			}
		}

	}
	else if(max_forks > 7 && fork()==0){
		while (1){	
			int type;
			float ans;
			close(fds1[writing]);
			read(fds1[reading], buff, sizeof(string));
			sscanf(buff,"%d %f %d",&type, &value, &is_done);
			switch(type){
				case 0:
					ans = f(value);
					break;
				case 1:
					ans = 2.0 * f(value);
					break;
			}
			memset(string, '\0', sizeof(string));
			if (!is_done){
				sprintf(string, "%f\0", ans);
				close(fds2[reading]);
				write(fds2[writing], string, sizeof(string));
			}
			else{
				break;
			}
		}

	}

	else{
		printf("hi");
		for (i = 0; i < max_trapizoids; i++){
			if (i == 0 || i == max_trapizoids-1){
				type = 0;
			}
			else{
				type = 1;
			}
			if (i == max_trapizoids-1){
				is_done = 1;
			}
			sprintf(string, "%d %f %d\0", type, ((i*1.0)*delta_x), is_done);
			close(fds1[reading]);
			write(fds1[writing], string, sizeof(string));

			close(fds2[writing]);
			while(read(fds2[reading], buff, sizeof(string))==-1){}
			sscanf(buff,"%f",&temp);
			if (!finished){
				sum += temp;
			}
			if(is_done){
				finished = 1;
			}

		}
		sum = sum * (0.5*delta_x);
		printf("Answer: %f\n", sum);
	}

	exit(0);
}
