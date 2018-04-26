#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "intal.h"
typedef struct node{
  char c;
  struct node* next;
}NODE;
typedef struct stack{
  NODE* top;
  int len;
}STACK;
static void init_stack(STACK *s){
  s->top=NULL;
  s->len=0;
}
static void push_stack(STACK *s,char c){
  NODE *tmp=(NODE*)malloc(sizeof(NODE));
  tmp->c=c;
  tmp->next=s->top;
  s->top=tmp;
  s->len+=1;
}
static char pop(STACK *s){
  NODE* tmp;
  char c;
  tmp=s->top;
  s->top=s->top->next;
  c=tmp->c;
  free(tmp);
  return(c);
}
static char* intal_in_binary(void *intal){
  /* returns the binary equivalent of intal.
     Uses stack to convert the number from decimal to binary.
     algo:
          check if the number is even or odd
          if(odd)-> push(1)
          else -> push(0)
          divide intal by 2
          repeat until intal is greater than 0
          pop the stack until it is empty,
          return it
  */
  char *result;//the resultant
  char *var1;
  char *tmp,*tmp1;
  int i,j,k;
  int len;//the length of the input
  int lenp;//length of the power
  var1=(char*)intal_create(intal);//get the effective number of intal
  len=strlen(var1);
  STACK s;
  init_stack(&s);//initialize stack
  while(intal_compare(var1,"0")>0){//as long as var1 is greater than 0
    len=strlen(var1);
    if((var1[len-1]-'0')%2==0){//if even
      push_stack(&s,'0');
    }
    else{                      //if odd
      push_stack(&s,'1');
    }
    tmp=intal_divide(var1,"2");//divide the number by 2
    free(var1);
    var1=tmp;
  }
  lenp=s.len;
  result=(char*)malloc(sizeof(char)*(lenp+1));
  result[lenp]='\0';
  i=0;
  while(s.top!=NULL){//pop until the stack is empty
    result[i]=pop(&s);
    i+=1;
  }
  tmp=intal_create(result);//return the effective binary number
  free(result);
  return(tmp);
}

void* intal_create(const char* str){
  /* creates a new object of the effective number of str and returns the object.
     treats the given number as string.
     return after removing leading zeroes and
     if the given string is alpha numeric, consider till the first non-digit index
     ex:
        if str is 0012 return 12
        if str is 12xs return 12
        if str is 0089tp return 89
        if str is hello return 0
  */
  if(str==NULL){
    return(NULL);
  }
  char* ch;//intal in the form of a string
  char* tmp;
  int len;//the length of the str
  int i,j;
  len=strlen(str);
  i=0;
  while((i<len)&&(str[i]=='0')){//remove leading zeroes
    i+=1;
  }
  if(i==len){//if all are zeroes
    ch=(char*)malloc(sizeof(char)*2);
    ch[0]='0';
    ch[1]='\0';
    return(ch);
  }
  ch=(char*)malloc(sizeof(char)*(len-i+1));
  for(j=i;j<len;j++){
    if(((str[j]-'0')<0)||((str[j]-'0')>9)){//take all digits before a non-digit occurs
      if(i==j){
        ch[0]='0';
        j+=1;
      }
      break;
    }
    ch[j-i]=str[j];
  }
  ch[j-i]='\0';//append with '\0', the end of string
  //there might be a possibility that not all the allocated memory is being used.
  //So to free up the extra memory, create a new object of length of ch and copy it
  tmp=(char*)malloc(sizeof(char)*(strlen(ch)+1));
  for(i=0;i<strlen(ch);i++){
    tmp[i]=ch[i];//copy the string
  }
  tmp[i]='\0';//append with '\0' at the end of string
  free(ch);//free the space
  return(tmp);
}
void intal_destroy(void* intal){
  /*
  frees the memory if intal is not null
  */
  if(intal!=NULL){
    free(intal);
  }
}
char* intal2str(void* intal){
  /*
  Returns NaN is intal is NULL. Else it will return the same as intal_create function.
  creates a new object and then returns
  */
  char* ch;
  if(intal==NULL){
    ch=(char*)malloc(sizeof(char)*4);
    strcpy(ch,"NaN");
    ch[3]='\0';
    return(ch);
  }
  return(intal_create(intal));
}
void* intal_increment(void* intal){
  /*
  Creates a new object with value intal+1 and returns the new object.
  returns NULL, if the input is NULL.
  algo:
      move to the last of the intal.
      if the digit is 9, make it zero.
      move to the previous index.
      continue until you find a number less than 9
      if index is out of bound,
         make the first index 1 and copy the same number of zeroes.
      else
         increment the value at index.
  */
  if(intal==NULL){
    return NULL;
  }
  int len;//len of intal
  int i;
  char* result;
  result=(char*)intal_create(intal);
  len=strlen(result);
  i=len-1;//move to the last index
  while((i>-1)&&(result[i]=='9')){//move to the previous number until the digit is 9
    result[i]='0';
    i-=1;
  }
  if(i>-1){//if index is not out of bound, increment the value at i
    result[i]=result[i]+1;
  }
  else{//else prepend with 1
    result=realloc(result,len+2);
    result[len+1]='\0';
    result[0]='1';
    for(i=1;i<=len;i++){
      result[i]='0';
    }
  }
  return(result);
}
void* intal_decrement(void* intal){
  /*
  Creates a new object with the value intal-1 and returns the object.
  returns NULL, if the input is NULL.
  if intal is 0, returns 0.
  algo:
     move to the last index
     if the digit is 0, make it 9 and move to previous index.
     Continue until you find a non-zero digit
     if index out of bound, return 0 (i.e if all the digits are 0)
     Else decrement the value at index
  */
  if(intal==NULL){
    return NULL;
  }
  int len;//len of intal
  int i;
  char* result;
  char* tmp;
  result=(char*)intal_create(intal);
  len=strlen(result);
  i=len-1;

  while((i>-1)&&(result[i]=='0')){//move to previous index until the value is zero
    result[i]='9';
    i-=1;
  }
  if(i>-1){//if index is not out of bound
    result[i]=result[i]-1;
    i+=1;
  }
  else{//if the given number is zero
    result=(char*)malloc(sizeof(char)*2);
    result[0]='0';
    result[1]='\0';
  }
  tmp=intal_create(result);
  free(result);
  return(tmp);
}
void* intal_add(void* intal1, void* intal2){
  /*
  Creates a new object with value intal1+intal2 and returns the new object.
  returns NULL, if any of the inputs are NULL.
  algo:
      The total number of digits can be one more than the maximum number of digits of the two at max.
      move to the unit digit of both the intals (the last index)
      we will get the digit by subtracting the asciz value of '0' from the current asciz.
      take the sum of the digits.
      carry = sum/10;
      sum=sum%10;
      The sum will then go to the current index of the result and carry will be propagated.
  */
  if((intal1==NULL)||(intal2==NULL)){
    return NULL;
  }
  int c;//the carry
  int s;//the sum
  char *sum;
  char *var1;
  char *var2;
  int i,j,k;
  int len,len1,len2;
  var1=(char*)intal1;
  var2=(char*)intal2;
  len1=strlen(intal1);
  len2=strlen(intal2);
  if(len1<1){
    return(var2);
  }
  if(len2<1){
    return(var1);
  }
  len=len1;
  if(len1<len2){
    len=len2;
  }
  sum=(char*)malloc(sizeof(char)*(len+2));
  //make all the digits in the sum as '0' to start with.
  for(i=0;i<len+1;i++){
    sum[i]='0';
  }
  sum[i]='\0';//append the sum with '\0'
  k=len;
  c=0;//carry is initially zero
  for(i=len1-1,j=len2-1;((i>-1)&&(j>-1));i--,j--){
    s=(var1[i]-'0')+(var2[j]-'0')+c;//find the sum
    c=s/10;//get carry
    s=s%10;//the sum
    sum[k]='0'+s;
    k-=1;
  }
  if((i==-1)&&(j==-1)){//when both have the same len
    sum[k]=c+'0';
  }
  while(i>-1){//if intal1 has more digits than intal2
    s=(var1[i]-'0')+c;
    c=s/10;
    s=s%10;
    sum[k]='0'+s;
    k-=1;
    i-=1;
  }
  while(j>-1){//if intal2 has more digits than intal1
    s=(var2[j]-'0')+c;
    c=s/10;
    s=s%10;
    sum[k]='0'+s;
    k-=1;
    j-=1;
  }
  sum[k]=c+'0';//the last carry to be added
  var1=intal_create(sum);//remove the leading zeroes if any
  free(sum);
  return(var1);
}
void* intal_diff(void* intal1, void* intal2){
  /*
  Creates a new object of with the value abs(intal1-intal2) and returns the new object.
  returns NULL, if any of the inputs are NULL.
  algo:
      get the maximum of the two.
      The result will atmost be of the length of the maximum
      set borrow to 0.
      go to the last index of take the difference along with borrow.
      if difference is less than 0:
          set borrow to 1
          add 10 to difference
      else
          set borrow to 0
      continue until the end of intal2.
      now get the difference of current index of intal1 and borrow.
      if difference is less than 0:
          set borrow to 1
          add 10 to difference
      else
          set borrow to 0
      continue until the end of intal1
  */
  if((intal1==NULL)||(intal2==NULL)){
    return NULL;
  }
  int len1;
  int len2;
  int len;
  int d;//the difference
  int b;//the borrow
  char *diff;
  char *var1;
  char *var2;
  int i,j,k;
  var1=intal_create(intal1);
  var2=intal_create(intal2);
  if(intal_compare(var2,var1)==1){
    diff=var2;
    var2=var1;
    var1=diff;
  }
  len1=strlen(var1);
  len2=strlen(var2);
  len=len1;
  diff=(char*)malloc(sizeof(char)*(len+1));
  //set all the digits in the difference to zero
  for(i=0;i<len;i++){
    diff[i]='0';
  }
  diff[len]='\0';//append with '\0' to the diff
  k=len-1;
  b=0;//set borrow to 0
  for(i=len1-1,j=len2-1;i>-1,j>-1;i--,j--){
    d=var1[i]-var2[j]-b;//take the difference along with borrow
    if(d<0){//if difference is less than zero
      d+=10;
      b=1;
    }
    else{
      b=0;
    }
    diff[k]='0'+d;//update the diff with the difference at the appropriate index.
    k-=1;
  }
  while(i>-1){//if intal1(the larger number) has more number of digits than intal2(the smaller number)
    d=var1[i]-b-'0';//get the difference
    if(d<0){//if difference is less than 0
      d+=10;
      b=1;
    }
    else{
      b=0;
    }
    diff[k]='0'+d;
    k-=1;
    i-=1;
  }
  free(var1);
  free(var2);
  var1=intal_create(diff);//remove the leading zeroes
  free(diff);
  return(var1);
}
void* intal_multiply(void* intal1,void* intal2){
  /*
  Creates a new object with the value intal1*intal2 and returns the new object.
  returns NULL if any of the inputs of are NULL.
  algo:
      for two digits
      a1a2*b1b2=(a1*10 + a2)(b1*10 + b2)
               =(a1*b1*100 + a2*b1*10 +a1*b2*10 + a2*b2)
               =term1      + term2    + term3   + term4
      for n digits
      a1a2a3.....an* b1b2b3....bm =
                                    (a1a2....a(n/2)*10000..(ceil(n/2) zeroes + a(n/2)+1.....an)*(b1b2...b(m/2)*1000..(ceil(m/2) zeroes)+ b(m/2)+1....bm)
      This is credited to karatsuba and is known by his name
  */
  if((intal1==NULL)||(intal2==NULL)){
    return NULL;
  }

  char *var1,*var2;
  char *a1,*a2;
  char *b1,*b2;
  char *term1,*term2,*term3,*term4;
  char *mul;
  int len_a1,len_a2;
  int len_b1,len_b2;
  int i,j,k;
  var1=intal_create(intal1);
  len_a1=strlen(var1);
  var2=intal_create(intal2);
  len_b1=strlen(var2);

  if((len_a1==1)&&(len_b1==1)){//if both of the intals are single digit numbers.
    mul=(char*)malloc(sizeof(char)*3);
    i=var1[0]-'0';
    j=var2[0]-'0';
    k=i*j;
    mul[0]='0'+(k/10);
    mul[1]='0'+(k%10);
    mul[2]='\0';
    a1=intal_create(mul);
    free(mul);
    return(a1);
  }
  if((len_a1<1)||(len_b1<1)){
    /*since we are using recursion with half the number of digits every time,
      there might be a case where the length is less than 1.
    */
    //since i am using realloc i need to allocate memory and then return the pointer
    // return "0";->segmentation fault
    mul=(char*)malloc(sizeof(char)*2);
    mul[0]='0';
    mul[1]='\0';
    return(mul);
  }
  len_a2=(len_a1+1)/2;
  len_a1=len_a1-len_a2;
  a1=(char*)malloc(sizeof(char)*(len_a1+1));
  a2=(char*)malloc(sizeof(char)*(len_a2+1));
  for(i=0;i<len_a1;i++){//copy the first half of intal1 to a1
    a1[i]=var1[i];
  }
  a1[i]='\0';
  for(i=0;i<len_a2;i++){//copy the second half of intal1 to a12
    a2[i]=var1[i+len_a1];
  }
  a2[i]='\0';
  len_b2=(len_b1+1)/2;
  len_b1=len_b1-len_b2;
  b1=(char*)malloc(sizeof(char)*(len_b1+1));
  b2=(char*)malloc(sizeof(char)*(len_b2+1));
  for(i=0;i<len_b1;i++){//copy the first half of intal2 to b1
    b1[i]=var2[i];
  }
  b1[i]='\0';
  for(i=0;i<len_b2;i++){//copy the second half of intal2 to b2
    b2[i]=var2[i+len_b1];
  }
  b2[i]='\0';//append the string with '\0'
  term1=intal_multiply(a1,b1);//term1
  term2=intal_multiply(a1,b2);//term2
  term3=intal_multiply(a2,b1);//term3
  term4=intal_multiply(a2,b2);//term4
  free(a1);
  free(a2);
  free(b1);
  free(b2);
  free(var1);
  free(var2);
  i=strlen(term1);
  term1=realloc(term1,(i+len_a2+len_b2+1)*sizeof(char));
  term1[i+len_b2+len_a2]='\0';
  //effectively multiplying by the required power of 10
  //i.e 10 to the power of the sum of the digits of second half of intal1 and intal2
  for(j=i;j<(i+len_b2+len_a2);j++){
    term1[j]='0';
  }
  i=strlen(term2);
  term2=(char*)realloc(term2,sizeof(char)*(i+len_a2+1));
  term2[i+len_a2]='\0';
  //append suitable number of zeroes to term2
  //i.e 10 to the power of the number of digits of the second half of intal1
  for(j=i;j<(i+len_a2);j++){
    term2[j]='0';
  }
  i=strlen(term3);
  term3=realloc(term3,(i+len_b2+1)*sizeof(char));
  term3[i+len_b2]='\0';
  //multiplying term3 with 10 to the power of the number of digits of the second half of intal2
  for(j=i;j<(i+len_b2);j++){
    term3[j]='0';
  }
  //add all the terms i.e term1+term2+term3+term4
  mul=intal_add(term1,term2);
  a1=intal_add(mul,term3);
  free(mul);
  mul=a1;
  a1=intal_add(mul,term4);
  free(mul);
  mul=a1;
  a1=intal_create(mul);
  free(mul);
  //return the product
  return a1;
}
void* intal_divide(void* intal1, void* intal2){
  /*
  Creates a new object with the value floor(intal1/intal2) and returns the object.
  returns NULL if any of the inputs are NULL.
  algo:
      get the number of digits in intal2.
      copy one more than the  number of digits of intal2 from intal1 to a buffer.
      get the value of value of floor(buffer/intal2)
      add the current quotient to the result and append the next number of intal1 to buffer.
      continue until the end of the intal1
      The algorithm works close to the long division method, learnt in elementary classes.
  */
  if((intal1==NULL)||(intal2==NULL)){
    return NULL;
  }
  if(intal_compare(intal2,"0")==0){//check for divisibility by zero
    return NULL;
  }
  char *result;//the quotient
  char *var1;
  char *tmp;
  char *var2;
  char *buffer;//buffer, the minimum divident required for dividing
  char *c;//the quotient of individual division
  int i,j,k;
  int len2;//the length of the divisor
  int len;//the maximum possible length of the quotient
  var1=intal_create(intal1);
  var2=intal_create(intal2);
  len = strlen(var1)-strlen(var2)+1;
  if(len < 1){
    result = (char*)malloc(sizeof(char)*2);
    result[0]='0';
    result[1]='\0';
    return(result);
  }
  result=(char*)malloc(sizeof(char)*(len+1));
  result[len]='\0';
  len2=strlen(var2)+1;
  buffer=(char*)malloc(sizeof(char)*(len2+1));
  c=(char*)malloc(sizeof(char)*2);
  buffer[len2]='\0';
  //copy the necessary contents to the buffer
  for(i=0;i<len2;i++){
    buffer[i]=var1[i];
  }
  k=0;
  result[k]='\0';
  for(i=len2;i<strlen(var1);i++){
    c[0]='0';//initilize the quotient to 0
    c[1]='\0';
    //as long as buffer is greater than or equal to var2, subtract var2 from buffer and increment quotient by 1
    while(intal_compare(buffer,var2)>=0){
      tmp=intal_diff(buffer,var2);
      free(buffer);
      buffer=tmp;
      tmp=intal_add(c,"1");
      free(c);
      c=tmp;
    }
    //append the quotient to the original result.
    for(j=0;j<strlen(c);j++){
      result[k+j]=c[j];
    }
    result[k+j]='\0';
    k+=j;
    len2=strlen(buffer)+1;
    buffer=realloc(buffer,len2+1);// i need to allocate one more memory so that we make space for the next iterattion
    buffer[len2]='\0';
    buffer[len2-1]=var1[i];//append the next digit of intal1
  }
  //the last iteration would still be left since as soon as the last digit is appended, it moves out of the for loop
  c[0]='0';
  c[1]='\0';
  //get the last part of the quotient
  while(intal_compare(buffer,var2)>=0){
    tmp=intal_diff(buffer,var2);
    free(buffer);
    buffer=tmp;
    tmp=intal_add(c,"1");
    free(c);
    c=tmp;
  }
  for(j=0;j<strlen(c);j++){
    result[k+j]=c[j];
  }
  result[k+j]='\0';//append the result with '\0', the end of string
  k+=j;
  free(var1);
  free(var2);
  return(result);
}
int intal_compare(void* intal1, void* intal2){
  /*
  compares the two intals, intal1 and intal2 and returns as follows.
  returns -2 if any one of the inputs are NULL.
  if(intal1>intal2):
      return 1
  if(intal2>intal1):
      return -1
  if(intal2==intal1):
      return 0
  algo:
      check the lengths of the two intals after removing the leading zeroes.
      if length of intal1 is greater than that of intal2:
          return 1
      if length of intal2 is greate than that of intal1:
          return -1
      if both have the same number of digits(i.e lengths):
          let len be that length.
          for i<-- 0 to len-1:
              if(intal1[i]>intal2[i]):
                  return 1;
              if(intal1[i]<intal2[i]):
                  return -1;
          return 0;//i.e when both are equal
  */
  if((intal1==NULL)||(intal2==NULL)){
    return -2;
  }
  char *var1;
  char *var2;
  int len1;
  int len2;
  int i;
  var1=intal_create(intal1);
  var2=intal_create(intal2);
  len1=strlen(var1);
  len2=strlen(var2);
  //if the number of digits of intal1 is greater than that of intal2
  if(len1>len2){
    return(1);
  }
  //if the number of digits of intal2 is greater than that of intal1
  if(len2>len1){
    return(-1);
  }
  //if both the intals have the same number of digits
  for(i=0;i<len1;i++){
    if(var1[i]>var2[i]){//if the digit at intal1 is greater than that of intal2
      return(1);
    }
    if(var2[i]>var1[i]){//if the digit at intal2 is greater than that of intal1
      return(-1);
    }
  }
  //if both the numbers are same.
  return(0);
}
void* intal_pow(void* intal1, void* intal2){
  /*
  Creates a new object with value pow(intal1,intal2) and returns the new object.
  returns NULL if any of the inputs are NULL.
  pow(0,0)=0
  pow(0,1)=0
  pow(1,0)=1
  algo:
      convert the given intal2 into its equivalent binary number.
      set power to 1.
      start from the first digit in its binary equivalent number(the MSB bit)
      do:
          power=power*power
          if the binary digit at this index is 1:
              power = power*intal1
      until the end of the binary equivalent of intal2
      return power.
      This algorithm is called as horner's rule.
  */
  if((intal1==NULL)||(intal2==NULL)){
    return NULL;
  }
  char *power;
  char *var2;
  char *tmp;
  char *var1;
  int i;
  int len;
  var1=intal_create(intal1);
  if(strcmp(var1,"0")==0){//if the base value is zero, return zero
    power=(char*)malloc(sizeof(char)*2);
    power[0]='0';
    power[1]='\0';
    free(var1);
    return(power);
  }
  //convert intal2 to its binary equivalent number.
  var2=intal_in_binary(intal2);
  if(strcmp(var2,"0")==0){//if the power is zero, return 1
    power=(char*)malloc(sizeof(char)*2);
    power[0]='1';
    power[1]='\0';
    free(var2);
    return power;
  }
  //initilize power to 1.
  power=(char*)malloc(sizeof(char)*2);
  power[0]='1';
  power[1]='\0';
  len=strlen(var2);
  //traverse through the binary equivalent number of intal2.
  for(i=0;i<len;i++){
    tmp=intal_multiply(power,power);//take the current square of power and store it in power.
    free(power);
    power=tmp;
    if(var2[i]=='1'){//if the binary number is 1, multiply it by intal1
      tmp=intal_multiply(power,var1);
      free(power);
      power=tmp;
    }
  }
  free(var1);
  free(var2);
  return(power);
}
