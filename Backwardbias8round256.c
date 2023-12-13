#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define myrand32 ((ul)(4294967296.0*drand48()))

#define ul unsigned int
#define ull unsigned long long
#define rotateleft(x, n) (((x) << (n)) ^ ((x) >> (32-n)))
#define rotateright(x, n) (((x) >> (n)) ^ ((x) << (32-n)))
#define Add(a,b,n)((rotateleft(a+b,n)))


void print(ul *x)
{
int i;
for (i = 0; i < 16; i++)
{
printf("%8x ", x[i]);
if (i > 0 && i % 4 == 3)
printf("\n");
}
printf("\n");
}

void printk(ul *x)
{
int i;
for (i = 0; i < 8; i++)
{
printf("%8x ", x[i]);
if (i > 0 && i % 4 == 3)
printf("\n");
}
printf("\n");
}


void initial(ul *x){
int i;

for (i=0;i<16;i++)

x[i]= myrand32;

x[0] =0x61707865;
x[5] =0x3320646e;
x[10]=0x79622d32;
x[15]=0x6b206574;
}

void initialkey(ul *k){
int i;

for (i=0;i<8;i++)

k[i]= myrand32;


}

void merge(ul *x,ul *k){

int i;

for (i=1;i<5;i++){

x[i]=k[i-1];
}

for (i=11;i<15;i++){

x[i]=k[i-7];
}

}


void alterkey(ul*k,int word, int bit){

int i;

ul pat= 0x1<<bit;

k[word]=k[word]^pat;

}


void same(ul*x, ul*y){
int i;

 for (i=0;i<16;i++)

 y[i]=x[i];  

}


ul *sum(ul*x,ul*y, ul*z){

int i;

for(i=0;i<16;i++)
{
z[i]=(x[i]+y[i])%4294967296;
}
return z;
}


ul *subt(ul*x,ul*y,ul*z){

int i;

for(i=0;i<16;i++)
{

z[i]=(x[i]-y[i])%4294967296;

}
return z;
}


ul *add(ul*x,ul*y,ul*f){

int i;
for(i=0;i<16;i++)
{

f[i]=(x[i]^y[i]);
}
return f;
}

void swap(double *a, double *b)
{
    double temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap_int(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    }

void sort(double *array, int *array1, int n)
{
    int ctr=0;
    for (int l = n - 1; l >= 0; --l)
    {
        ctr = 0;
        for (int j = 0; j < l; ++j)
        {
            if (array[j] > array[j + 1])
            {
                swap(&array[j], &array[j + 1]);
                swap_int(&array1[j], &array1[j + 1]);
                ctr = 1;
            }
        }
        if (ctr == 0)
        {
            break;
        }
    }
    printf("|   Bias  |  BIT  | Word | Bit | \n");
    for (int k = 0; k < n; ++k)
    {
        
        if (k == 0)
        {
            printf("|------------------------------|\n");
        }
        printf("| %.5lf | %d th | %d |  %d  | \n", array[k], array1[k], array1[k] / 32, array1[k] % 32);
        if (k == n - 1)
        {
            printf("|------------------------------|");
            
        }
    }

    
}



void fn(ul *a, ul*b,ul *c, ul*d){

ul a1,b1,c1,d1;

b1=(*b^Add(*a,*d,7));
c1=(*c^Add(b1,*a,9));
d1=(*d^Add(c1,b1,13));
a1=(*a^Add(c1,d1,18)); 

*a=a1;
*b=b1;
*c=c1;
*d=d1;
}

void column(ul*x){

fn((&x[0]), &(x[4]), &(x[8]), &(x[12]));
fn((&x[5]), &(x[9]), &(x[13]),&(x[1]));                  
fn((&x[10]),&(x[14]),&(x[2]), &(x[6]));
fn((&x[15]),&(x[3]), &(x[7]), &(x[11]));
 }

void row(ul*x){

fn((&x[0]), &(x[1]), &(x[2]), &(x[3]));
fn((&x[5]), &(x[6]), &(x[7]), &(x[4]));                  
fn((&x[10]),&(x[11]),&(x[8]), &(x[9]));
fn((&x[15]),&(x[12]),&(x[13]),&(x[14]));
 }


void refn(ul *a, ul*b,ul *c, ul*d){

ul a1,b1,c1,d1;

a1=(*a^Add(*c,*d,18));
d1=(*d^Add(*c,*b,13));
c1=(*c^Add(*b,a1,9));
b1=(*b^Add(a1,d1,7));

*a=a1;
*b=b1;
*c=c1;
*d=d1;

}


void recolumn(ul*x){

refn((&x[0]), &(x[4]), &(x[8]), &(x[12]));
refn((&x[5]), &(x[9]), &(x[13]),&(x[1]));                  
refn((&x[10]),&(x[14]),&(x[2]), &(x[6]));
refn((&x[15]),&(x[3]), &(x[7]), &(x[11]));
 }

void rerow(ul*x){

refn((&x[0]), &(x[1]), &(x[2]), &(x[3]));
refn((&x[5]), &(x[6]), &(x[7]), &(x[4]));                  
refn((&x[10]),&(x[11]),&(x[8]), &(x[9]));
refn((&x[15]),&(x[12]),&(x[13]),&(x[14]));
 }


    /********************FIrst half************/

void halffn(ul *a, ul*b,ul *c, ul*d){

ul a1,b1,c1,d1;

b1=(*b^Add(*a,*d,7));
c1=(*c^Add(b1,*a,9));
 

*a=*a;
*b=b1;
*c=c1;
*d=*d;
}




 void halfcolumn(ul*x){

halffn((&x[0]), &(x[4]), &(x[8]), &(x[12]));
halffn((&x[5]), &(x[9]), &(x[13]),&(x[1]));                  
halffn((&x[10]),&(x[14]),&(x[2]), &(x[6]));
halffn((&x[15]),&(x[3]), &(x[7]), &(x[11]));
 }

void halfrow(ul*x){

halffn((&x[0]), &(x[1]), &(x[2]), &(x[3]));
halffn((&x[5]), &(x[6]), &(x[7]), &(x[4]));                  
halffn((&x[10]),&(x[11]),&(x[8]), &(x[9]));
halffn((&x[15]),&(x[12]),&(x[13]),&(x[14]));
 }

/*reverse half*/

void rehalffn(ul *a, ul*b,ul *c, ul*d){

ul a1,b1,c1,d1;


c1=(*c^Add(*b,*a,9));
b1=(*b^Add(*a,*d,7));

*a=*a;
*b=b1;
*c=c1;
*d=*d;

}
 void rehalfcolumn(ul*x){

rehalffn((&x[0]), &(x[4]), &(x[8]), &(x[12]));
rehalffn((&x[5]), &(x[9]), &(x[13]),&(x[1]));                  
rehalffn((&x[10]),&(x[14]),&(x[2]), &(x[6]));
rehalffn((&x[15]),&(x[3]), &(x[7]), &(x[11]));
 }

void rehalfrow(ul*x){

rehalffn((&x[0]), &(x[1]), &(x[2]), &(x[3]));
rehalffn((&x[5]), &(x[6]), &(x[7]), &(x[4]));                  
rehalffn((&x[10]),&(x[11]),&(x[8]), &(x[9]));
rehalffn((&x[15]),&(x[12]),&(x[13]),&(x[14]));
 }

    /********************************************************/



int main(){

printf("----------------The PNB backward bias---------------\n");
 
ul x[16],x1[16],y[16],y1[16],z[16],z1[16],f[16],b[16],k[8],pattern,pt, pat,forward,backward;
 

int i,j,p,diff,p1,p2;

// int A[]={93, 94, 95, 139, 140, 141, 50, 142, 51, 52, 143, 53, 64, 144, 65, 54, 145, 66, 55, 146, 67, 56, 160, 147, 68, 57, 161, 17, 148, 58, 69, 18, 162, 59, 149, 36, 19, 70, 159, 60, 163, 174, 37, 150, 20, 61, 204, 71, 62, 175, 21, 164, 38, 151, 205, 192, 115, 237, 4, 63, 72, 176, 22, 255, 206, 116, 152, 193, 39, 5, 165, 238, 23, 73, 31, 177, 117, 128, 194, 207, 153, 199, 239, 40, 166};

// int ll=85;

// int array1[]={4,17,18,19,20,21,22,36,37,38,39,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,93,94,115,116,139,140,141,142,143,144,145,146,147,148,149,150,151,152,159,160,161,162,163,164,165,174,175,176,192,193,204,205,206,237,238};

// int array2[]={5,23,40,73,95,117,153,166,177,194,207,239};

// int array3[]={31,128,199,255};

// int a1=69,a2=12,a3=4;

int A[]={4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 36, 37, 38, 39, 40, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,100,103,104,105,106,107,108,109,110,115,116,117,118,119,120,121,122,128,129,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,159,160,161,162,163,164,165,166,167,168,174,175,176,177,178,179,180,181,182,186,187,188,192,193,194,195,199,200,204,205,206,207,208,209,213,218,224,225,226,231,232,233,237,238,239,240,245,249,250,251,255};

int ll=159;

int array1[]={4,5,6,7,8,9,10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,  36, 37, 38, 39,  50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,  82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 103,104,105,106,107,108,109,115,116,117,118,119,120,121,128,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,159,160,161,162,163,164,165,166,167,174,175,176,177,178,179,180,181,186,187,192,193,194,199,204,205,206,207,208,224,225,231,232,237,238,239,249,250,251};

int array2[]={31,40,75,95,110,122,129,154,168,182,188,195,200,209,226,233,240};

int array3[]={100,213,218,245,255};

int a1=137,a2=17,a3=5;

ul loop=0;

double cnt=0;

int word, bit;

srand48(time(NULL));


while(loop<1024*1024*1024){

while(1){

initial(x);

same(x,x1);

same(x,y);


pt=0x1<<31;

x1[7]=x1[7]^pt;

same(x1,y1);

column(x);
column(x1);

int count=0;

for(i=0;i<16;i++){

for(j=0;j<32;j++){

pattern=0x1<<j;

if(((x[i]^x1[i])&pattern)!=0) 

 count++;
}
}

if(count<=4)
break;

}

row(x);
row(x1);

column(x);
column(x1);

row(x);
row(x1);

column(x);
column(x1);

add(x,x1,f);

// pat=0x1<<14;

// if(((f[1])&pat)==0)

 forward=(f[4]);


row(x);
row(x1);

column(x);
column(x1);

row(x);
row(x1);


sum(x,y,z);
sum(x1,y1,z1);


// for (p=0;p<ll;p++){

// if((A[p]/32)<4){

// p1=(A[p]/32)+1;
// p2=A[p]%32;
// // printf("%d\n",p1);
// }

// else{
// p1=(A[p]/32)+7;
// p2=A[p]%32;
// // printf("%d\n",p1);
// }


// if(drand48()<0.5)
// {
//     y[p1]=y[p1]^(0x1<<p2);
//     y1[p1]=y1[p1]^(0x1<<p2);
    
// }

// }


for (p=0;p<a1;p++){

if((array1[p]/32)<4){

p1=(array1[p]/32)+1;
p2=array1[p]%32;

}
else{
p1=(array1[p]/32)+7;
p2=array1[p]%32;

}

if(((y[p1]>>p2)%2)!=0)

{
   y[p1]=y[p1]^(0x1<<p2);
   y1[p1]=y1[p1]^(0x1<<p2);

   
    
}
}
/*2nd Set*/
for (p=0;p<a2;p++){

if((array2[p]/32)<4){
p1=(array2[p]/32)+1;
p2=array2[p]%32;

}

else{
p1=(array2[p]/32)+7;
p2=array2[p]%32;

}

if(((y[p1]>>p2)%2)==0)
// if(drand48() < 0.5)

{

    y[p1]=y[p1]^(0x1<<p2);
   y1[p1]=y1[p1]^(0x1<<p2);
  
}

}

/*3rd Set*/
for (p=0;p<a3;p++){

if((array3[p]/32)<4){
p1=(array3[p]/32)+1;
p2=array3[p]%32;

}
else{
p1=(array3[p]/32)+7;
p2=array3[p]%32;

}

if(drand48() < 0.5)
{
//     printf("The number %x\n",(y[p1]));
// printf("The bit %x ,%d, %d\n",((y[p1]>>p2)%2),p1,p2);
    y[p1]=y[p1]^(0x1<<p2);
   y1[p1]=y1[p1]^(0x1<<p2);
//    printf("The new number %x\n",(y[p1]));  
   
}

}

subt(z,y,x);
subt(z1,y1,x1);

 
/*reverse round start*/

rerow(x);
rerow(x1);

recolumn(x);
recolumn(x1);

rerow(x);
rerow(x1);


add(x,x1,b);

backward=((b[4]));

pattern=0x1<<7;

if(((forward^backward)& pattern)==0)

 cnt=cnt+1.0;
 loop++;

if (loop>0 && loop%(1024*128)==0)

printf("%u   %0.10f \n", loop/(1024*256),2*(cnt/loop)-1.0);
}

}
  
