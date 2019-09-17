#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>   // Internet Protocol family
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>

struct admin{
	int userID;         // userID starts from 100
	char username[30];
	char password[15];
};

struct normalUser{
	int userID;         // userID starts from 100
	char name[30];
	char password[15];
	int account_no;     // account_no starts from 100000
	float balance;
	int isActive;       // to check whether the account is deleted or not.  //if isActive = 1 then it's not deleted
};

struct jointUser{
	int userID;         // userID starts from 100
	char name1[30];
	char name2[30];
	char password[15];
	int account_no;     // account_no starts from 100000
	float balance;
	int isActive;       // to check whether the account is deleted or not.  //if isActive = 1 then it's not deleted
};

struct normalUser searchNU(int ID){
	int i=ID-100;
	struct normalUser currUser;
	int fd=open("NormalUser.txt",O_RDONLY,0744);

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct normalUser);    	     //nth record
	lock.l_len=sizeof(struct normalUser);	               //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct normalUser));

	// printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

struct jointUser searchJU(int ID){
	int i=ID-100;
	struct jointUser currUser;
	int fd=open("JointUser.txt",O_RDONLY,0744);

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct jointUser);    	     //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct jointUser));

	// printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

struct admin searchAD(int ID){
	int i=ID-100;
	struct admin currUser;
	int fd=open("Admin.txt",O_RDONLY,0744);
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct admin);    	     //nth record
	lock.l_len=sizeof(struct admin);	               //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	lseek(fd,(i)*sizeof(struct admin),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct admin));
	printf("%d\n", currUser.userID);
	printf("%s\n",currUser.password );

	// printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

bool checkNU(struct normalUser currUser){
	int i=currUser.userID-100;
	int fd=open("NormalUser.txt",O_RDONLY,0744);
	bool result;
	struct normalUser temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct normalUser);    	   // nth record
	lock.l_len=sizeof(struct normalUser);	             // sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(struct normalUser));
	if(!strcmp(temp.password,currUser.password) && temp.isActive == 1)
		result=true;
	else
		result=false;

	printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkJU(struct jointUser currUser){
	int i=currUser.userID-100;
	int fd=open("JointUser.txt",O_RDONLY,0744);
	bool result;
	struct jointUser temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct jointUser);    	     //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(struct jointUser));
	if(!strcmp(temp.password,currUser.password) && temp.isActive == 1)
		result=true;
	else
		result=false;

	printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkAD(struct admin currUser){
	int i=currUser.userID-100;
	int fd=open("Admin.txt",O_RDONLY,0744);
	bool result;
	struct admin temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct admin);    	     //nth record
	lock.l_len=sizeof(struct admin);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	lseek(fd,(i)*sizeof(struct admin),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(struct admin));
	if(!strcmp(temp.password,currUser.password))	result=true;
	else						result=false;

	printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool deposit(int accType,int ID,float amt){
	int i=ID-100;
	if(accType==1){
		int fd=open("NormalUser.txt",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct normalUser);    //nth record
		lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		printf("Inside critical section \n");

		struct normalUser currUser;
		lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct normalUser));

		if(currUser.isActive == 1){
			currUser.balance+=amt;
			lseek(fd,sizeof(struct normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct normalUser));
			result=true;
		}
		else
			result=false;

		printf("Amount deposited = %f\n",amt);
		// getchar();
		sleep(20);
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		printf("Unlocked \n");
		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open("JointUser.txt",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct jointUser);    //nth record
		lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		printf("Inside critical section \n");

		struct jointUser currUser;
		lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct jointUser));

		if(currUser.isActive == 1){
			currUser.balance+=amt;
			lseek(fd,sizeof(struct jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct jointUser));
			result=true;
		}
		else	result=false;

		printf("Amount deposited = %f\n",amt);
		// getchar();
		sleep(20);
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

bool withdraw(int accType,int ID,float amt){
	int i=ID-100;
	if(accType==1){
		int fd=open("NormalUser.txt",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct normalUser);    //nth record
		lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		printf("Inside critical section \n");

		struct normalUser currUser;
		lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct normalUser));

		if(currUser.isActive == 1 && currUser.balance>=amt){
			currUser.balance-=amt;
			lseek(fd,sizeof(struct normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct normalUser));
			result=true;
		}
		else	result=false;

		printf("Press enter to unlock \n");
		// getchar();
		sleep(20);
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open("JointUser.txt",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct jointUser);    //nth record
		lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		printf("Inside critical section \n");

		struct jointUser currUser;
		lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct jointUser));

		if(currUser.isActive == 1 && currUser.balance>=amt){
			currUser.balance-=amt;
			lseek(fd,sizeof(struct jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct jointUser));
			result=true;
		}
		else	result=false;

		printf("Press enter to unlock \n");
		// getchar();
		sleep(20);
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

float checkBalance(int accType,int ID){
	int i=ID-100;
	float result;
	if(accType==1){
		int i=ID-100;
		int fd=open("NormalUser.txt",O_RDONLY,0744);
		struct normalUser temp;

		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct normalUser);    	     //nth record
		lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		printf("Inside critical section \n");

		lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(struct normalUser));
		if(temp.isActive == 1)
			result=temp.balance;
		else
			result=0;

		printf("Press enter to unlock \n");
		// getchar();
		sleep(20);
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int i=ID-100;
		int fd=open("JointUser.txt",O_RDONLY,0744);
		struct jointUser temp;

		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct jointUser);    	     //nth record
		lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		printf("Inside critical section \n");

		lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(struct jointUser));
		if(temp.isActive == 1)	result=temp.balance;
		else					result=0;

		printf("Press enter to unlock \n");
		// getchar();
		sleep(20);
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return 0;
}

bool changePassword(int accType,int ID,char newPwd[10]){
	int i=ID-100;
	if(accType==1){
		int fd=open("NormalUser.txt",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct normalUser);    //nth record
		lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		printf("Inside critical section \n");

		struct normalUser currUser;
		lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct normalUser));

		if(currUser.isActive == 1){
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(struct normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct normalUser));
			result=true;
		}
		else
			result=false;

		printf("Press enter to unlock \n");
		// getchar();
		sleep(20);
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open("JointUser.txt",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct jointUser);    //nth record
		lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		printf("Inside critical section \n");


		struct jointUser currUser;
		lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct jointUser));

		if(currUser.isActive == 1){
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(struct jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct jointUser));
			result=true;
		}
		else	result=false;

		// getchar();
		sleep(20);
		printf("Press enter to unlock \n");
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

bool addNU(struct normalUser record){
	int fd=open("NormalUser.txt",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(struct normalUser);        //nth record
	lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	               //lock the selected record
	printf("Inside critical section \n");

	struct normalUser endUser;
	lseek(fd,(-1)*sizeof(struct normalUser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(struct normalUser));

	record.userID=endUser.userID+1;
	record.account_no=endUser.account_no+1;
	record.isActive = 1;

	int j=write(fd,&record,sizeof(struct normalUser));
	if(j!=0)	result=true;
	else	result=false;

	printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool addJU(struct jointUser record){
	int fd=open("JointUser.txt",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(struct jointUser);    //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	struct jointUser endUser;
	lseek(fd,(-1)*sizeof(struct jointUser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(struct jointUser));

	record.userID=endUser.userID+1;
	record.account_no=endUser.account_no+1;
	record.isActive = 1;

	int j=write(fd,&record,sizeof(struct jointUser));
	if(j!=0)	result=true;
	else	result=false;

	printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool deleteNU(int ID){
	int i=ID-100;
	int fd=open("NormalUser.txt",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct normalUser);    //nth record
	lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	struct normalUser currUser;
	lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct normalUser));

	if(currUser.isActive == 1){
		currUser.isActive = 0;
		currUser.balance=0;

		lseek(fd,(-1)*sizeof(struct normalUser),SEEK_CUR);
		int j=write(fd,&currUser,sizeof(struct normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool deleteJU(int ID){
	int i=ID-100;
	int fd=open("JointUser.txt",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct jointUser);    //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	struct jointUser currUser;
	lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct jointUser));

	if(currUser.isActive == 1){
		currUser.isActive = 0;
		currUser.balance=0;

		lseek(fd,(-1)*sizeof(struct jointUser),SEEK_CUR);
		int j=write(fd,&currUser,sizeof(struct jointUser));
		if(j!=0)	result=true;
		else		result=false;
	}

	printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool modifyNU(struct normalUser modUser){
	int i=modUser.userID-100;
	int fd=open("NormalUser.txt",O_RDWR,0744);
	bool result=false;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct normalUser);    //nth record
	lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	struct normalUser currUser;
	lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct normalUser));

	if(currUser.isActive == 1 && (modUser.account_no==currUser.account_no)){
		modUser.isActive = 1;
		lseek(fd,(-1)*sizeof(struct normalUser),SEEK_CUR);
		int j=write(fd,&modUser,sizeof(struct normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}

	printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool modifyJU(struct jointUser modUser){
	int i=modUser.userID-100;
	int fd=open("JointUser.txt",O_RDWR,0744);
	bool result=false;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct jointUser);        //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	printf("Inside critical section \n");

	struct jointUser currUser;
	lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct jointUser));

	if(currUser.isActive == 1  && (modUser.account_no==currUser.account_no)){
		modUser.isActive = 1;
		lseek(fd,(-1)*sizeof(struct jointUser),SEEK_CUR);
		int j=write(fd,&modUser,sizeof(struct jointUser));
		if(j!=0)	result=true;
		else		result=false;
	}

	printf("Press enter to unlock \n");
	// getchar();
	sleep(20);
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

void serverOption(int nsd){
	int msgLength,select,type,option,accType,currUserID;
	bool result;
	while(1){
		read(nsd,&option,sizeof(option));
		printf("Option : %d\n",option);

		if(option==1){
			struct normalUser currUser1;
			accType=1;
			msgLength=read(nsd,&currUser1,sizeof(struct normalUser));
			printf("Username : %d\n",currUser1.userID);
			printf("Password : %s\n",currUser1.password);
			currUserID=currUser1.userID;
			result=checkNU(currUser1);
			write(nsd,&result,sizeof(result));
		}
		else if(option==2){
			struct jointUser currUser2;
			accType=2;
			msgLength=read(nsd,&currUser2,sizeof(struct jointUser));
			currUserID=currUser2.userID;
			printf("Username : %d\n",currUser2.userID);
			printf("Password : %s\n",currUser2.password);
			result=checkJU(currUser2);
			write(nsd,&result,sizeof(result));
		}
		else if(option==3){
			struct admin currUser3;
			accType=3;
			msgLength=read(nsd,&currUser3,sizeof(struct admin));
			currUserID=currUser3.userID;
			printf("Username : %d\n",currUser3.userID);
			printf("Password : %s\n",currUser3.password);
			result=checkAD(currUser3);
			write(nsd,&result,sizeof(result));
		}
		else{
			result=false;
			write(nsd,&result,sizeof(result));
		}
		if(result)	break;
	}

	while(1){
		read(nsd,&select,sizeof(int));
		if(option==1 || option==2){
			if(select==1){
				float amt;
				read(nsd,&amt,sizeof(float));
				result=deposit(accType,currUserID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==2){
				float amt;
				read(nsd,&amt,sizeof(float));
				result=withdraw(accType,currUserID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==3){
				float amt;
				amt=checkBalance(accType,currUserID);
				write(nsd,&amt,sizeof(float));
			}
			else if(select==4){
				char pwd[10];
				read(nsd,pwd,sizeof(pwd));
				result=changePassword(accType,currUserID,pwd);
				write(nsd,&result,sizeof(result));
			}
			else if(select==5){
				if(option==1){
					struct normalUser user1=searchNU(currUserID);
					write(nsd,&user1,sizeof(struct normalUser));
				}
				else if(option==2){
					struct jointUser user2=searchJU(currUserID);
					write(nsd,&user2,sizeof(struct jointUser));
				}
			}
			else if(select==6)	break;
		}
		else if(option==3){
			read(nsd,&type,sizeof(int));
			if(select==1){
				if(type==1){
					struct normalUser newUser1;
					read(nsd,&newUser1,sizeof(struct normalUser));
					result=addNU(newUser1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					struct jointUser newUser2;
					read(nsd,&newUser2,sizeof(struct jointUser));
					result=addJU(newUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==2){
				if(type==1){
					int delUserID1;
					read(nsd,&delUserID1,sizeof(int));
					result=deleteNU(delUserID1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					int delUserID2;
					read(nsd,&delUserID2,sizeof(int));
					result=deleteJU(delUserID2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==3){
				if(type==1){
					struct normalUser modUser1;
					read(nsd,&modUser1,sizeof(struct normalUser));
					result=modifyNU(modUser1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					struct jointUser modUser2;
					read(nsd,&modUser2,sizeof(struct jointUser));
					result=modifyJU(modUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==4){
				if(type==1){
					struct normalUser searchUser1;
					int userID1;
					read(nsd,&userID1,sizeof(int));
					searchUser1=searchNU(userID1);
					write(nsd,&searchUser1,sizeof(struct normalUser));
				}
				else if(type==2){
					struct jointUser searchUser2;
					int userID2;
					read(nsd,&userID2,sizeof(int));
					searchUser2=searchJU(userID2);
					write(nsd,&searchUser2,sizeof(struct jointUser));
				}
			}
			else if(select==5)	break;
		}
	}
	close(nsd);
	write(1,"Ended client session.....\n",sizeof("Ended client session.....\n"));
	return;
}

int main(){
	struct sockaddr_in ser,cli;         // The <netinet/in.h> header defines the sockaddr_in structure
	int sd,nsd,clilen;
	bool result;
	sd=socket(AF_INET,SOCK_STREAM,0);   // int socket (int family, int type, int protocol);  // returns socket descriptor
																			// type − It specifies the kind of socket you want. // if protocol = 0 then it's systems default
	ser.sin_family=AF_INET;          // family − It specifies the protocol family i.e if family = AF_INET then it's IPv4 protocol
	ser.sin_addr.s_addr=INADDR_ANY;  // INADDR_ANY value for IP address means the server's IP address will be assigned automatically.
	ser.sin_port=htons(5555);        // Host to Network Short
	// bind returns 0 on success and -1 on failure
	bind(sd,(struct sockaddr *)&ser,sizeof(ser));  // The bind function assigns a local protocol address to a socket. With the Internet protocols, the protocol address is the combination of either a 32-bit IPv4 address or a 128-bit IPv6 address, along with a 16-bit TCP or UDP port number. This function is called by TCP server only.
	listen(sd,5);	                      // listen function converts an unconnected socket into a passive socket, indicating that the kernel should accept incoming connection requests directed to this socket. // maximum number of connections the kernel should queue for this socket i.e max queue length :: 5 clients per connection
  // listen returns 0 on success and -1 on error.
	write(1,"Waiting for the client.....\n",sizeof("Waiting for the client.....\n"));
	while(1){
		clilen = sizeof(cli);
		nsd=accept(sd,(struct sockaddr *)&cli,&clilen);  // int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
    // The accept function is called by a TCP server to return the next completed connection from the front of the completed connection queue.
		write(1,"Connected to the client.....\n",sizeof("Connected to the client.....\n"));
		if(!fork()){   // Child
			close(sd);	 // child doesn't require sd
			serverOption(nsd);
			exit(0);
		}
		else{         // Parent
			close(nsd);	// child has nsd and parent doesn't require it
		}
	}
	return 0;
}
