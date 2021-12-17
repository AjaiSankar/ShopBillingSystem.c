#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Function to generate Bill header
void billHeader(char name[20],char date[30]){
  printf("\n\n");
  printf("\tABC STORESt");
  printf("\n-----------------------------");
  printf("\n\nDate: %s ",date);
  printf("\nName: %s ",name);
  printf("\n");
  printf("===============================");
  printf("\nItems\t\t");
  printf("Qty\t\t");
  printf("Total\t\t");
  printf("\n------------------------------");
  printf("\n\n");
}//End of function billHeader

//Function to generateBill
void billGenerate(char item[],int qty,float price){
  printf("%s\t\t",item);
  printf("%d\t\t",qty);
  printf("%0.2f\t\t",qty*price);
  printf("\n");
}//End of function billGenerate

struct items{
  char item[20];
  float price;
  int qty;
}; //End of struct Items

struct customer{
  char name[30];
  char date[50];
  int qtyOfItems;
  struct items itm[50];
};//End of struct Customer

//Function to generate bill footer
void billFooter(float total){
  fflush(stdin);
  printf("\n");
  float discount,netTotal,gst,grandTotal;
  discount = 0.1 * total;
  netTotal = total - discount;
  gst = 0.09 * netTotal;
  grandTotal = netTotal + (2*gst);
  printf("\n-----------------------------");
  printf("\nSub total:\t\t\t%0.2f",total);
  printf("\nDiscount@10\t\t\t%0.2f",discount);
  printf("\n\t\t\t\t-------------");
   printf("\nNet total:\t\t\t%0.2f",netTotal);
  printf("\ncgst@9\t\t\t\t%0.2f",gst);
  printf("\nsgst@9\t\t\t\t%0.2f",gst);
  printf("\n----------------------------------");
  printf("\nGrand total:\t\t\t%0.2f",grandTotal);
  printf("\n----------------------------------\n");
}//End of billFooter function

int main(){
  int option,noItems;
  float total;
  char saveBill;
  char nameSearch[50];
  struct customer ord;
  FILE *fp;
  struct customer order;

  //Dashboard
  printf("\n-=-=-=-ABC STORES-=-=-=-\n");
  printf("\n1) Generate Bill");
  printf("\n2) Show all Bills");
  printf("\n3) Search Bill");
  printf("\n4) Exit");
  printf("\n\nEnter your choice:\t ");
  scanf("%d",&option);
  fgetc(stdin);
  switch(option){

    case 1:
            system("clear");
            printf("\n\nName of customer:\t ");
            fgets(ord.name,30,stdin);
            ord.name[strlen(ord.name)-1] = 0;
            strcpy(ord.date,__DATE__);
            printf("No of items:\t ");
            scanf("%d",&noItems);
            ord.qtyOfItems = noItems;

            for(int i=0;i<noItems;i++){
              fgetc(stdin);
              printf("\n\n");
              printf("Item %d\t\t",i+1);
              fgets(ord.itm[i].item,20,stdin);
              ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
              printf("Qty:\t\t ");
              scanf("%d",&ord.itm[i].qty);
              printf("Unit price:\t");
              scanf("%f",&ord.itm[i].price);  
              total += ord.itm[i].qty * ord.itm[i].price;   
            }//End of for loop
            billHeader(ord.name, ord.date);
            for(int i=0;i<ord.qtyOfItems;i++){
              billGenerate(ord.itm[i].item, ord.itm[i].qty,ord.itm[i].price);
            }//End of for loop
            billFooter(total);

            printf("Do you want to save?:(y/n):");
            scanf("%s",&saveBill);
            if(saveBill == 'y'){

              fp = fopen("Bills.dat","a+");
              fwrite(&ord,sizeof(struct customer),1,fp);
              printf("Succesfully Saved");
              fclose(fp);
            }
            break;

            case 2:
                  system("clear");
                  float tot=0;
                  fp = fopen("Bills.dat","r");
                  printf("======Your Bills=======");

                  while(fread(&order,sizeof(struct customer),1,fp)){
                    billHeader(order.name,order.date);
                    for(int i=0;i<order.qtyOfItems;i++){
                      billGenerate(order.itm[i].item, order.itm[i].qty,order.itm[i].price);
                      tot += order.itm[i].qty * order.itm[i].price; 

                    }
                    billFooter(tot);
                                }
                  fclose(fp);
                  break;

                  case 3:
                        system("clear");

                        printf("Enter name of customer to search: ");
                        fgets(nameSearch, 50, stdin);
                        nameSearch[strlen(nameSearch)-1] = 0;


                        float tota=0;
                        fp = fopen("Bills.dat","r");
                        printf("\n\n======Bill of %s=======",nameSearch);

                        while(fread(&order,sizeof(struct customer),1,fp)){
                          if(!strcmp(order.name,nameSearch)){
                            billHeader(order.name,order.date);
                          for(int i=0;i<order.qtyOfItems;i++){
                            billGenerate(order.itm[i].item, order.itm[i].qty,order.itm[i].price);
                            tota += order.itm[i].qty * order.itm[i].price;  }
                    billFooter(tota);
                                }
                            else{
                              printf("Bill for %s not found",nameSearch);
                            }
                                }
                          
                  fclose(fp);
                  break;

                  case 4:
                        printf("\n\nByeee :}");
                        exit(0);
                        break;
                  default:
                        printf("WRONG CHOOICE!!");
                  }//End of switch
    return 0;

}
