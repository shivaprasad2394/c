#include<stdio.h>
void reverse_word(char *str){
	int f=0;
	int l=0;
	int k=0;
	int flag=0;
	int j=0;
	printf("\nbefore:%d%d%d",f,l,k);
	l=printf("%s",str);
	l--;
	printf("\nl%d\n",l);
	while(f<l){
		str[f]=str[f]+str[l]-(str[l]=str[f]);
		f++;
		l--;
		printf("\n%d%d\n",f,l);
	}
	printf("\nafter rev=%s",str);
	l=f=0;
	while(str[l]!='\0'){
		if(str[l]==' '){
			if(flag>0){
				f=j+1;
				printf("\nthe value of f%d flag%d l%d",f,flag,l);
			}
			k=l-1;
			while(f<k){
				str[f]=str[f]+str[k]-(str[k]=str[f]);
				f++;
				k--;
				flag=1;
				printf("\n%d%d%d%s\n",f,l,k,str);
				j=l;
			}
		}
		l++;
	}
	if(str[l]=='\0'){
		k=l-1;
		f=j+1;
		while(f<k){
			str[f]=str[f]+str[k]-(str[k]=str[f]);
			f++;
			k--;
		}
	}
	printf("\nafter each rev=%s",str);
}

void remove_duplicate(char *str){
	char dup[25];
	char new[25];
	printf("\ndupped begin");
	int l=printf("%s",str);
	l--;
	char table[255]={0};
	int i=0,j=0,k=0;
	while(str[i]!='\0'){//todo modification
		dup[i++]=str[l--];
		printf("\n%d%d",i,l);
	}
	dup[i]='\0';
	printf("ops=%s",dup);
	i=0;
	while(dup[i]!='\0'){
		if(table[(dup[i])]==0){
			table[(dup[i])]=1;
			new[k]=dup[i];
			k++;
		}else{
			printf("\n skipped %c",dup[i]);
		}
		i++;
	}
	printf("\ndupped str=%s",new);
}

int pattern_search(char *str,char *buf){
int a=0,b=0,c=0;
while(str[a]!='\0'){
if((buf[b]==str[c]) && (buf[b]!='\0')){
	c++;
	b++;
}
else{
	if(buf[b]=='\0')
		return 1;
a++;
c=a;
b=0;
}
}
return -1;
}

void main(){
	char str[25],buf[25];
	int flag=0;
	printf("enter:\n");
	gets(str);
	//reverse_word(str);
	//printf("\nnext%s",str);
	//remove_duplicate(str);
	printf("enter the pattern:\n");
	gets(buf); 
	flag=pattern_search(str,buf);
	(flag>0)?printf("patty\n"):printf("nope\n");
}
