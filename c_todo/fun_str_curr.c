#include<stdio.h>
void reverse_word(char *str){
	int f,l,k=0;
	int flag,j=0;
	printf("before:%d%d%d",f,l,k);
	l=printf("%s",str);
	l--;
	printf("f%dl%d\n",f,l);
	while(f<l){
		printf("f%dl%d\n",f,l);
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
	printf("\nafter each rev=%s",str);
}

void main(){
	char str[25];
	printf("enter:\n");
	gets(str);
	reverse_word(str);
	//each_word_swapper();
}
