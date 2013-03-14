#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define reading 0
#define writing 1

void* shared_mem;
int *count;

struct shared{
	int ready;
};

float f(float x){
	return (1.0/(1.0+x));
}

void main(){
	const key_t key = 1234;
	int shmid = shmget(key,sizeof(struct shared), 0666|IPC_CREAT);
	if(shmid == -1) exit(EXIT_FAILURE);
	
	int i;
	int fds1[2];
	int fds2[2];
	int info[2];
	int max_forks = 8;
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

		int k = 0;

	if (fork() == 0){
		// shaired memory
		shared_mem = shmat(shmid,(void*) 0,0);
		if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
		struct shared* shared_data = (struct shared*) shared_mem;
		while (shared_data->ready != 4){
			sleep(0.1);
		}
		sleep(0.4);
		while (1){	
			if (shared_data->ready == 3){
				exit(0);
			}
			if (k == 64){
				exit(0);
			}
			int type;
			float ans;
			if (shared_data->ready == 3){
				exit(0);
			}
			close(fds1[writing]);
			while(shared_data->ready){
				shared_data->ready = 0;
				while(read(fds1[reading], buff, sizeof(string))==-1){
					if (shared_data->ready == 3){
						exit(0);
					}
				}
			}
			if (shared_data->ready == 3){
				exit(0);
			}
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
			if (shared_data->ready == 3){
				if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
				exit(0);
			}
				sprintf(string, "%f\0", ans);
				close(fds2[reading]);
				write(fds2[writing], string, sizeof(string));
			
		}
	}
	else if(fork()==0){
		if (max_forks>1){
			// shaired memory
			shared_mem = shmat(shmid,(void*) 0,0);
			if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
			struct shared* shared_data = (struct shared*) shared_mem;
			while (shared_data->ready != 4){
				sleep(0.1);
			}
			sleep(0.5);
			while (1){	
				k++;
				if (shared_data->ready == 3){
					exit(0);
				}
				int type;
				float ans;
				close(fds1[writing]);


				while(shared_data->ready){
					shared_data->ready = 0;
					while(read(fds1[reading], buff, sizeof(string))==-1){
						if (shared_data->ready == 3){
							exit(0);
						}
					}
				}
				if (shared_data->ready == 3){
					exit(0);
				}
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
					if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
					exit(EXIT_SUCCESS);
					break;
				}
			}
		}
	}
	else if(fork()==0){
		if (max_forks>2){
			// shaired memory
			shared_mem = shmat(shmid,(void*) 0,0);
			if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
			struct shared* shared_data = (struct shared*) shared_mem;
			while (shared_data->ready != 4){
				sleep(0.1);
			}
			sleep(0.5);
			while (1){	
				k++;
				if (shared_data->ready == 3){
					exit(0);
				}
				int type;
				float ans;
				close(fds1[writing]);


				while(shared_data->ready){
					shared_data->ready = 0;
					while(read(fds1[reading], buff, sizeof(string))==-1){
						if (shared_data->ready == 3){
							exit(0);
						}
					}
				}
				if (shared_data->ready == 3){
					exit(0);
				}
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
					if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
					exit(EXIT_SUCCESS);
					break;
				}
			}
		}
	}
	else if(fork()==0){
		if (max_forks>3){
			// shaired memory
			shared_mem = shmat(shmid,(void*) 0,0);
			if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
			struct shared* shared_data = (struct shared*) shared_mem;
			while (shared_data->ready != 4){
				sleep(0.1);
			}
			sleep(0.5);
			while (1){	
				k++;
				if (shared_data->ready == 3){
					exit(0);
				}
				int type;
				float ans;
				close(fds1[writing]);


				while(shared_data->ready){
					shared_data->ready = 0;
					while(read(fds1[reading], buff, sizeof(string))==-1){
						if (shared_data->ready == 3){
							exit(0);
						}
					}
				}
				if (shared_data->ready == 3){
					exit(0);
				}
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
					if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
					exit(EXIT_SUCCESS);
					break;
				}
			}
		}
	}
	else if(fork()==0){
		if (max_forks>4){
			// shaired memory
			shared_mem = shmat(shmid,(void*) 0,0);
			if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
			struct shared* shared_data = (struct shared*) shared_mem;
			while (shared_data->ready != 4){
				sleep(0.1);
			}
			sleep(0.5);
			while (1){	
				k++;
				if (shared_data->ready == 3){
					exit(0);
				}
				int type;
				float ans;
				close(fds1[writing]);


				while(shared_data->ready){
					shared_data->ready = 0;
					while(read(fds1[reading], buff, sizeof(string))==-1){
						if (shared_data->ready == 3){
							exit(0);
						}
					}
				}
				if (shared_data->ready == 3){
					exit(0);
				}
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
					if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
					exit(EXIT_SUCCESS);
					break;
				}
			}
		}
	}
	else if(fork()==0){
		if (max_forks>5){
			// shaired memory
			shared_mem = shmat(shmid,(void*) 0,0);
			if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
			struct shared* shared_data = (struct shared*) shared_mem;
			while (shared_data->ready != 4){
				sleep(0.1);
			}
			sleep(0.5);
			while (1){	
				k++;
				if (shared_data->ready == 3){
					exit(0);
				}
				int type;
				float ans;
				close(fds1[writing]);


				while(shared_data->ready){
					shared_data->ready = 0;
					while(read(fds1[reading], buff, sizeof(string))==-1){
						if (shared_data->ready == 3){
							exit(0);
						}
					}
				}
				if (shared_data->ready == 3){
					exit(0);
				}
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
					if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
					exit(EXIT_SUCCESS);
					break;
				}
			}
		}
	}
	else if(fork()==0){
		if (max_forks>6){
			// shaired memory
			shared_mem = shmat(shmid,(void*) 0,0);
			if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
			struct shared* shared_data = (struct shared*) shared_mem;
			while (shared_data->ready != 4){
				sleep(0.1);
			}
			sleep(0.5);
			while (1){	
				k++;
				if (shared_data->ready == 3){
					exit(0);
				}
				int type;
				float ans;
				close(fds1[writing]);


				while(shared_data->ready){
					shared_data->ready = 0;
					while(read(fds1[reading], buff, sizeof(string))==-1){
						if (shared_data->ready == 3){
							exit(0);
						}
					}
				}
				if (shared_data->ready == 3){
					exit(0);
				}
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
					if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
					exit(EXIT_SUCCESS);
					break;
				}
			}
		}
	}
	else if(fork()==0){
		if (max_forks>7){
			// shaired memory
			shared_mem = shmat(shmid,(void*) 0,0);
			if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
			struct shared* shared_data = (struct shared*) shared_mem;
			while (shared_data->ready != 4){
				sleep(0.1);
			}
			sleep(0.5);
			while (1){	
				k++;
				if (shared_data->ready == 3){
					exit(0);
				}
				int type;
				float ans;
				close(fds1[writing]);


				while(shared_data->ready){
					shared_data->ready = 0;
					while(read(fds1[reading], buff, sizeof(string))==-1){
						if (shared_data->ready == 3){
							exit(0);
						}
					}
				}
				if (shared_data->ready == 3){
					exit(0);
				}
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
					if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
					exit(EXIT_SUCCESS);
					break;
				}
			}
		}
	}
	else{
		count = &i;
	// shaired memory
		shared_mem = shmat(shmid,(void*) 0,0);
		if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
		struct shared* shared_data = (struct shared*) shared_mem;
		count = &i;		

		shared_data->ready = 4;
		sleep(0.2);
		for (i = 0; i <= max_trapizoids; i++){			
			shared_data->ready = 1;

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
			shared_data->ready = 1;
			write(fds1[writing], string, sizeof(string));
			close(fds2[writing]);
			if (i != 64){
				while(read(fds2[reading], buff, sizeof(string))==-1){}
				sscanf(buff,"%f",&temp);
				if (!finished){
					sum += temp;
				}
			}
			if(is_done){
				finished = 1;
				shared_data->ready = 3;
			}

		}
		sum = sum * (0.5*delta_x);
		printf("Answer: %f\n", sum);
	}

	exit(0);
}
