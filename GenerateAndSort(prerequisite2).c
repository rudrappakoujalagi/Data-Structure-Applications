#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_array(int a[10],int n);
void read_array(int a[10],int n);
void bubble_sort(int a[10],int n);
void selection_sort(int a[10],int n);
void rand_numbers(int n,int lower,int upper,FILE *fp);
void read_array_file(int *a,FILE *fp,int n);
void print_num_file(int n,int *a,FILE *fp);
void main()
{
 FILE *fp;
 FILE *fp1;
 FILE *fp2;
 int a[10];
 char str[10];
 fp=fopen("input.txt","w");
 rand_numbers(10,40,100,fp);
 fclose(fp);
 fp1=fopen("input.txt","r");
 read_array_file(&a[0],fp1,10);
 fclose(fp1);
 print_array(a,10);
 bubble_sort(a,10);
 selection_sort(a,10);
 printf("\n");
 print_array(a,10);
 fp2=fopen("output.txt","w");
 print_num_file(10,&a[0],fp2);



}
void bubble_sort(int a[10],int n)
{
    int i;
    int j;
    int temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
             temp=a[j];
             a[j]=a[j+1];
             a[j+1]=temp;
            }
        }
    }
}
void read_array(int a[10],int n)
{
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
}
void print_array(int a[10],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
}
void selection_sort(int a[10],int n)
{
    int i;
    int j;
    int temp;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(a[i]>a[j])
            {
               temp=a[j];
               a[j]=a[i];
               a[i]=temp;
            }
        }
    }
}
void rand_numbers(int n,int lower,int upper,FILE *fp)
{
    int num;
for(int i=0;i<n;i++)
{
    num=lower+rand()%(upper-lower+1);
    fprintf(fp,"%d ",num);

}
}
void read_array_file(int *a,FILE *fp,int n)
{
    int num;
for(int i=0;i<n;i++)
{
    fscanf(fp,"%d",&num);
    *(a+i)=num;
}


}
void print_num_file(int n,int *a,FILE *fp)
{
int i;
for(i=0;i<n;i++)
{
    fprintf(fp,"%d ",*(a+i));

}

}
