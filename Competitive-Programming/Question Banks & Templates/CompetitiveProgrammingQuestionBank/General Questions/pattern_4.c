/*PRINT THE FOLLOWING STAR PATTERN :
*********
 ********
  *******
   ******
    *****
     ****
      ***
       **
        *
*/ 

#include<stdio.h> 

int main(){ 
    int n;
printf("Enter the number of rows:");
scanf("%d",&n);

for(int i =0; i<n;i++){
    for(int j = 0; j<2*n; j++){
        if(j>=i){
            printf("*");
        }
        else
        {
            printf(" ");
        }
        
    }
    printf("\n");
}
return 0;
}