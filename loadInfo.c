#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

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

int getNewAdminUid(){
	struct admin ad;
	int fd=open("Admin.txt",O_RDONLY,0744);             // Admin
	lseek(fd,(-1)*sizeof(struct admin),SEEK_END);
	read(fd,&ad,sizeof(struct admin));
	close(fd);
	return ad.userID+1;
}

int getNewNormalUid(){
	struct normalUser nu;
	int fd=open("NormalUser.txt",O_RDONLY,0744);             // Normal User
	lseek(fd,(-1)*sizeof(struct normalUser),SEEK_END);
	read(fd,&nu,sizeof(struct normalUser));
	close(fd);
	return nu.userID+1;
}

int getNewJointUid(){
	struct jointUser ju;
	int fd=open("JointUser.txt",O_RDONLY,0744);             // Joint User
	lseek(fd,(-1)*sizeof(struct jointUser),SEEK_END);
	read(fd,&ju,sizeof(struct jointUser));
	close(fd);
	return ju.userID+1;
}

int main(){
	int fd1=open("Admin.txt",O_RDWR | O_CREAT,0744);
	int choice=0;
	struct admin adminUser,adminUser1;
	printf("Admin name:");
	scanf("%s",adminUser.username);
	printf("Password:");
	scanf("%s",adminUser.password);
	adminUser.userID=100;
	printf("Your userID is : %d\n",adminUser.userID);
	write(fd1,&adminUser,sizeof(struct admin));
	lseek(fd1,0,SEEK_SET);
	read(fd1,&adminUser1,sizeof(adminUser));
	printf("user_name = %s\n", adminUser1.username);
	printf("password = %s\n", adminUser1.password);
	printf("user_id = %d\n", adminUser1.userID);
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Admin name: ");
		scanf(" %[^\n]",adminUser.username);
		printf("Password: ");
		scanf(" %[^\n]",adminUser.password);
		adminUser.userID=getNewAdminUid();
		printf("Your userID is : %d\n",adminUser.userID);
		write(fd1,&adminUser,sizeof(struct admin));
		lseek(fd1,sizeof(adminUser)*(-1),SEEK_CUR);
		read(fd1,&adminUser1,sizeof(adminUser1));
		printf("user_name : %s\n", adminUser1.username);
		printf("password : %s\n", adminUser1.password);
		printf("user_id : %d\n", adminUser1.userID);
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd1);

	int fd2=open("NormalUser.txt",O_RDWR | O_CREAT,0744);
	choice=1;
	struct normalUser normalUser,normalUser1;
	printf("Normal User name: ");
	scanf(" %[^\n]",normalUser.name);
	printf("Password: ");
	scanf(" %[^\n]",normalUser.password);
	normalUser.userID=100;
	normalUser.account_no=(normalUser.userID-1000)+100000;
	normalUser.balance=0;
	normalUser.isActive = 1;
	printf("Your userID is : %d\n",normalUser.userID);
	write(fd2,&normalUser,sizeof(struct normalUser));
	lseek(fd2,0,SEEK_SET);
	read(fd2,&normalUser1,sizeof(normalUser));
	printf("user_id = %s\n", normalUser1.name);
	printf("password = %s\n", normalUser1.password);
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Normal User name: ");
		scanf(" %[^\n]",normalUser.name);
		printf("Password: ");
		scanf(" %[^\n]",normalUser.password);
		normalUser.userID=getNewNormalUid();
		normalUser.balance=0;
		normalUser.account_no=(normalUser.userID-1000)+100000;
		normalUser.isActive = 1;
		printf("Your userID is : %d\n",normalUser.userID);
		write(fd2,&normalUser,sizeof(struct normalUser));
		lseek(fd2,sizeof(normalUser)*(-1),SEEK_CUR);
		read(fd2,&normalUser1,sizeof(normalUser));
		printf("user_id = %s\n", normalUser1.name);
		printf("password = %s\n", normalUser1.password);
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd2);

	int fd3=open("JointUser.txt",O_RDWR | O_CREAT,0744);
	choice=1;
	struct jointUser jointUser,jointUser1;
	printf("Join User1 name: ");
	scanf(" %[^\n]",jointUser.name1);
	printf("Joint User2 name: ");
	scanf(" %[^\n]",jointUser.name2);
	printf("Password: ");
	scanf(" %[^\n]",jointUser.password);
	jointUser.userID=100;
	jointUser.balance=0;
	jointUser.account_no=(jointUser.userID-1000)+100000;
	jointUser.isActive = 1;
	printf("Your userID is : %d\n",jointUser.userID);
	write(fd3,&jointUser,sizeof(struct jointUser));
	lseek(fd3,0,SEEK_SET);
	read(fd3,&jointUser1,sizeof(jointUser));
	printf("user_id1 = %s\n", jointUser1.name1);
	printf("user_id2 = %s\n", jointUser1.name2);
	printf("password = %s\n", jointUser1.password);
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Joint User1 name: ");
		scanf(" %[^\n]",jointUser.name1);
		printf("Joint User2 name: ");
		scanf(" %[^\n]",jointUser.name2);
		printf("Password: ");
		scanf(" %[^\n]",jointUser.password);
		jointUser.userID=getNewJointUid();
		jointUser.balance=0;
		jointUser.account_no=(jointUser.userID-1000)+100000;
		jointUser.isActive = 1;
		printf("Your userID is : %d\n",jointUser.userID);
		write(fd3,&jointUser,sizeof(struct jointUser));
		lseek(fd3,sizeof(jointUser)*(-1),SEEK_CUR);
		read(fd3,&jointUser1,sizeof(jointUser));
		printf("user_id1 = %s\n", jointUser1.name1);
		printf("user_id2 = %s\n", jointUser1.name2);
		printf("password = %s\n", jointUser1.password);
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd3);
	return 0;
}
