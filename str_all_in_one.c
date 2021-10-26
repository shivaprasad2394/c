/*#include<stdio.h> //word reverse code

void reverse_string(char *str){
int first=0;
int len=strlen(str);
len--;
while(first<len){
//a=a+b-(b=a);
str[first]=str[first]+str[len]-(str[len]=str[first]);
first++;
len--;
}
printf("after=%s\n",str);
}

void swap (char * str,int first ,int last);
void swap(char * str,int first ,int last){
	while(first<last){
		str[first]=str[first]+str[last]-(str[last]=str[first]);
		first++;
		last--;
		printf("\nafter swap=%s",str);
	}
}
void reverse_word(char *str){
	int f=0;	//first position
	int l=0;	//last position
	int flag=0;	//indicates to swap word characters within word range/length
	int j=0;	//f+1 position or next position of head
	
	l=printf("%s",str);//dont change it will affect
	l--;
	printf("\nstr len=%d\n",l);
	swap(str,f,l);
	
	l=f=0;					//reset and start with individual word
	
	while(str[l]!='\0'){	//keep swaping until end
		if(str[l]==' '){	//if last is pointing to space dont swap skip
			if(flag>0){		//probably an indication skip and move on
				f=j+1;		//skip and move to next char in word
			}
			swap(str,f,(l-1));
			flag=1;
			j=l;
		}
		l++;//update last position to end of each word
	}
	if(str[l]=='\0'){//probably i am swaping internal char of word 
	f=j+1;
	swap(str,f,(l-1));//k=l-1;
	}
	printf("after each rev=%s\n",str);
}

void main(){
	char str[25];//character array
	printf("enter:\n");
	gets(str);
	reverse_word(str);
	//each_word_swapper();
}*/
/*void remove_duplicate(char *str){ //remove duplicate
	char dup[25];
	char new[25];
	printf("\ndupped begin");
	int l=printf("%s",str);
	l--;
	char table[255]={0};
	int i=0,j=0,k=0;
	while(str[i]!='\0'){
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
}*/
/*int pattern_search(char *str,char *buf){
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
}*/
/*int myatoi(char *str){
	int num=48,total=0,i=0,j=1,n=0,res[25]={0};
	n=printf("%s",str);
	while(str[i]!='\0'){
		if(str[i]=='\0'){
			res[i]='\0';
			printf("\n null breaker");
			break;
		}
		else if(str[i]>=num && str[i] <=(num+10)){
			res[i]=str[i]-num;
			printf("\nr%d i%d",res[i],i);
		}else{
		//here handle non numerics
		}
		i++;
	}
	for(i=0;res[i]!='\0';i++){
		//total += res[i]*(j<<(n-i));
		total*=10;
		total+=res[i];
		printf("\n t%d",total);
	}
	printf("\nanswer=%d",total);
	return total;
}*/
