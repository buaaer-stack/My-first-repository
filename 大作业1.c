#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 7983797
struct Node{
    char s[30];
    int num;
    int t;
};
struct Node hash_s[1000000];
struct Node hash_1[M];
struct Node hash_2[M];
struct Node h1[1000000];
struct Node h2[1000000];
inline int read() {
    char ch = getchar(); int x = 0, f = 1;
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    } while('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    } return x * f;
}
long long getkey(char *s){
    long long sum=0;
    for (int i=0;s[i]!='\0';i++){
        sum=sum*26+s[i];
        sum%=M;
    }
    return sum%M;
}
int hash_func1(int key){
    return key%M;
}
int hash_func2(int key){
    return(1+(key%(M-1)));
}
int find(char *s,struct Node H[]){
    long long key=getkey(s),i,h;
    for(i=0;;i++){
        //printf("%d\n",i);
        h=(hash_func1(key)+i*hash_func2(key))%M;
        if(strcmp(H[h].s,s)==0){
            //printf("1\n");
            //H[h].num++;
            return H[h].t+1;
        }
        else if(strlen(H[h].s)==0){
            return 0;
        }
    }
    return 0;
}
int insert(char *s,struct Node H[],int a){
    //printf("%d\n",1);
    long long key,i,h;
    key=getkey(s);
    for(i=0;;i++){
        h=(hash_func1(key)+i*hash_func2(key))%M;
        if(strcmp(H[h].s,s)==0){
            return 1;
        }
        else if(strlen(H[h].s)==0){
            strcpy(H[h].s,s);
            H[h].num=0;
            H[h].t=a;
            return 0;
        }
    }
    return 0;
}
int istrue(char c){
    if((c-'A'>=0&&c-'A'<=25)){
        return 1;
    }
    else if((c-'a'>=0&&c-'a'<=25)){
        return 2;
    }
    return 0;
}
struct Node H1[M];
void merge_sort(struct Node H[],int l,int r){
    if(l==r)return;
    int mid=(l+r)/2;
    merge_sort(H,l,mid);
    merge_sort(H,mid+1,r);
    int i=l,j=mid+1,k=l;
    while(i<=mid&&j<=r){
        if(H[i].num>H[j].num)H1[k++]=H[i++];
        else if(H[i].num==H[j].num){
            if(strcmp(H[i].s,H[j].s)<0){
                H1[k++]=H[i++];
            }
            else{
                H1[k++]=H[j++];
            }
        }
        else{
            H1[k++]=H[j++];
        }
    }
    while(i<=mid)H1[k++]=H[i++];
    while(j<=r)H1[k++]=H[j++];
    for(int t=l;t<=r;++t)H[t]=H1[t];
}
int cmp(const void *a,const void *b){
	struct Node *a1= (struct Node *)a;
	struct Node *b1= (struct Node *)b;
	if((*a1).num!=(*b1).num){
		return (*b1).num-(*a1).num;
	}
	else{
		return strcmp((*a1).s,(*b1).s);
	}
}
int main(){
    FILE *f_d,*f_s;
    char s[30];
    if((f_d=fopen("dictionary.txt","r"))==NULL){
        printf("error!\n");
        return 0;
    }
    if((f_s=fopen("stopwords.txt","r"))==NULL){
        printf("error!\n");
        return 0;
    }
    int a=0,b=0; 
    while(fscanf(f_s,"%s",s)!=EOF){
        insert(s,hash_s,b);
        //printf("%s\n",s);
    }
    while(fscanf(f_d,"%s",s)!=EOF){
        int t1=find(s,hash_s);
        if(t1==0){
        insert(s,hash_1,a);
        insert(s,hash_2,a);
        //printf("%d\n",t);
        strcpy(h1[a].s,s);
        h1[a].num=0;
        h1[a].t=a;
        h2[a]=h1[a];
        a++;
        }
        else {
            continue;
            
        }
    }
    //printf("%d",123);
    FILE *fp1,*fp2;
    if((fp1=fopen("article1.txt","r"))==NULL){
        printf("error!\n");
        return 0;
    }
    if((fp2=fopen("article2.txt","r"))==NULL){
        printf("error!\n");
        return 0;
    }
    char c;
    int num=0;
    //int t=0;
    while((c=fgetc(fp1))!=EOF){
        //printf("")
        if(istrue(c)==2){
            s[num++]=c;
        }
        else if(istrue(c)==1){
            s[num++]=c-'A'+'a';
        }
        else{
            s[num]='\0';
            if(num==0){
                continue;
            }
            else{
                num=0;
                int t=find(s,hash_s);
                if(t==0){
                
                   int t1=find(s,hash_1);
                   //printf("%d\n",t1);
                   h1[t1-1].num++;
                   
                }
            }
        }
    }
    //printf("%d\n",12324);
    s[num]='\0';
    if(num!=0){
        num=0;
        int t=find(s,hash_s);
        if(t==0){
            int t1=find(s,hash_1);
            h1[t1].num++;     
        }        
    }
    while((c=fgetc(fp2))!=EOF){
        if(istrue(c)==2){
            s[num++]=c;
        }
        else if(istrue(c)==1){
            s[num++]=c-'A'+'a';
        }
        else{
            s[num]='\0';
            if(num==0){
                continue;
            }
            else{
                num=0;
                int t=find(s,hash_s);
                if(t==0){
                    int t1=find(s,hash_2);
                    h2[t1-1].num++;
                }   

            }
        }
    }
    //printf("%d\n",124);
    if(num!=0){
        num=0;
        int t=find(s,hash_s);
        if(t==0){
            int t1=find(s,hash_2);
            h2[t1].num++;     
        }        
    }
    qsort(h1,a,sizeof(struct Node),cmp);
    qsort(h2,a,sizeof(struct Node),cmp);
    //printf("%d\n",11111);
    //printf("%d\n",a);
//下面一步应该是写排序函数，归并吧，比较稳定而且快
//然后在根据题意进行计算，实际上这道题比较难的是上面的东西吧，真正的并不是计算吧   
    int N;
    scanf("%d",&N);
    long long sum1=0,sum2=0;
    /*for(int i=0;i<N;i++){
        printf("%s %d\n",hash_1[i].s,hash_1[i].num);
    }*/
    for (int i=0;i<=N-1;i++){
        sum1+=h1[i].num;
        //printf("%d\n",h1[i].num);
    }
    for (int i=0;i<=N-1;i++){
        sum2+=h2[i].num;
    }
    long long sum3=0,sum4=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(strcmp(h1[i].s,h2[j].s)==0){
                sum3+=h1[i].num;
                sum4+=h2[j].num;
                break;
            }
        }
    }
    //printf("%d\n%d\n%d\n%d\n",sum1,sum2,sum3,sum4);
    double s1,s2;
    s1=(double)((double)sum3/(double)sum1);
    s2=(double)((double)sum4/(double)sum2);
    double sim;
    if(s1>s2){
        sim=s2/s1;
    }
    else{
        sim=s1/s2;
    }
    printf("%.5lf",sim);
    FILE *fp3;
    if((fp3=fopen("results.txt","w"))==NULL){
        printf("error\n");
    }
    fprintf(fp3,"%.5lf\n\n",sim);
    for(int i=0;i<=N-1;i++){
        fprintf(fp3,"%s %d\n",h1[i].s,h1[i].num);
    }
    fprintf(fp3,"\n");
    for(int i=0;i<=N-1;i++){
        fprintf(fp3,"%s %d\n",h2[i].s,h2[i].num);
    }
    return 0;
}

