/* Auto-generated code from Toy Compiler */
#include<stdio.h>
#include<stdlib.h>

int op = 1;


float f_expr(float left, float right);
int i_expr(int left, int right);

int main(){ 
int i_left, i_right, i_result, opType;
float f_left, f_right, f_result;
	printf("Premere 0 per chiudere il programma oppure scegli l'operazione da effettuare:\n");
	printf("2 = somma, 3 = sottrazione, 4 = moltiplicazione, 5 = divisione\nScelta: ");
	scanf("%d",&op);

while(op != 0){
	printf("Tipo di operazione: 0 = operazione tra int, 1 = operazione tra float\nScelta: ");
	scanf("%d",&opType);
	printf("Scegli il primo valore: ");
	if(opType == 0){
	scanf("%d",&i_left);
	printf("Scegli il secondo valore: ");
	scanf("%d",&i_right);
	i_result = i_expr(i_left, i_right);
	printf("Il risultato e' %d\n", i_result);
}
else{
	scanf("%f",&f_left);
	printf("Scegli il secondo valore: ");
	scanf("%f",&f_right);
	f_result = f_expr(f_left, f_right);
	printf("Il risultato e' %f\n", f_result);
}
	printf("Premere 0 per chiudere il programma oppure scegli l'operazione da effettuare:\n");
	printf("2 = somma, 3 = sottrazione, 4 = moltiplicazione, 5 = divisione\nScelta: ");
	scanf("%d",&op);

}
return 0;
}
float f_expr(float left, float right){ 
float result;
if(op == 2){
	result = left + right;
}
	else if(op == 3){
	result = left - right;
}
	else if(op == 4){
	result = left * right;
}
	else if(op == 5){
	result = left / right;
}
return result;
}
int i_expr(int left, int right){ 
int result;
if(op == 2){
	result = left + right;
}
	else if(op == 3){
	result = left - right;
}
	else if(op == 4){
	result = left * right;
}
	else if(op == 5){
	result = left / right;
}
return result;
}

