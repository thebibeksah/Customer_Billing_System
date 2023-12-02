#include<stdio.h>
#include<string.h>

#define MAX_ITEMS 100
#define MAX_CUSTOMERS 100
#define MAX_DETAILS 100

typedef struct{
    char itemName[50];
    float itemPrice;
} Item;

typedef struct{
    char customerId[50];
    int isRegular;
} Customer;

typedef struct{
    int index;
    int quantity;
} Details;

int loadItems(Item items[]){
    FILE *item = fopen("items.txt", "r");
    if(!item){
        FILE *createItem = fopen("items.txt", "w");
        fprintf(createItem, "coke 100\ncandy 10\ncookies 250\nbread 50\nmilk 80\n");
        fclose(createItem);
        return 0;
    }

    int count = 0;
    while(fscanf(item, "%s %f", items[count].itemName, &items[count].itemPrice) == 2 && count < MAX_ITEMS){
        count++;
    }
    fclose(item);
    return count;
}

int loadCustomers(Customer customers[]){
    FILE *customer = fopen("customers.txt", "r");
    if(!customer){
        FILE *createCustomer = fopen("customers.txt", "w");
        fprintf(createCustomer, "Bibek 1\n");
        fclose(createCustomer);
        return 0;
    }
    int count = 0;
    while(fscanf(customer, "%s %d", customers[count].customerId, &customers[count].isRegular) == 2 && count < MAX_CUSTOMERS){
        count++;
    }
    fclose(customer);
    return count;
}

float calculateTotal(float price, int isRegular){
    if(isRegular){
        return 0.9 * price;
    }
    else{
        return price;
    }
}

int main(){
    Item items[MAX_ITEMS];
    Customer customers[MAX_CUSTOMERS];
    Details detail[MAX_DETAILS];

    int i;
    char confirmCustomer;
    int numItems = loadItems(items);
    int numCustomers = loadCustomers(customers);

     if (numItems == 0 || numCustomers == 0) {
        printf("\n\nInitializing completed! Run this code again to contine!!\n\n");
        return 1; 
    }

    char customerName[50];
    printf("\n\n-------------------------------------------------------------------------------------------------------------\n\n");
    printf("-------------------------------------------Welcome to Titans Store-------------------------------------------");
    printf("\n\n-------------------------------------------------------------------------------------------------------------\n\n");
    printf("Enter customer name: ");
    scanf("%s", customerName);

    int isRegular = 0;
    for(i=0; i<numCustomers; i++){
        if(strcmp(customers[i].customerId, customerName) == 0){
            isRegular = customers[i].isRegular;
            break;
        }
    }

    if(isRegular){
        printf("\n\n-------------------------------------------------------------------------------------------------------------\n\n");
        printf("%s, You are our regular customer: 10%% discount", customerName);
        printf("\n\n-------------------------------------------------------------------------------------------------------------\n\n");
    } else {
        printf("\n-------------------------------------------------------------------------------------------------------------\n\n");
        printf("%s, You are a new customer. Do you want to be our regular customer(y/n): ", customerName);
        fflush(stdin);
        scanf("%c", &confirmCustomer);
        printf("\n-------------------------------------------------------------------------------------------------------------\n");
        char confirm = tolower(confirmCustomer);
        if(confirm == 'y'){
            FILE *customer = fopen("customers.txt", "a");
            fprintf(customer,"%s %d\n",customerName, 1);
            printf("\n-------------------------------------------------------------------------------------------------------------\n\n");
            printf("Congratulations! %s now you will get 10%% discount from next as being our regular customer.", customerName);
            printf("\n\n-------------------------------------------------------------------------------------------------------------\n\n");
        } else if(confirm == 'n'){
            printf("Alright %s, You can join it later as well!\n", customerName);
        }
        else{
            printf("Invalid Input!! I will take it as no");
        }
    }

    printf("\nAvailable items:\n");
    for(i=0;i<numItems; i++){
        printf("%d. %s - Rs %.2f\n", i+1, items[i].itemName, items[i].itemPrice);
    }

    int numPurchased;
    printf("\nEnter the number of items to purchase: ");
    scanf("%d", &numPurchased);

    float totalAmount = 0;
    int itemIndex, quantity;

    for(i=0; i<numPurchased; i++){

        printf("Enter item %d details (index quantity): ", i+1);
        scanf("%d %d", &detail[i].index, &detail[i].quantity);
        

        if(detail[i].index >=1 && detail[i].quantity > 0){
            float itemTotal = calculateTotal(items[detail[i].index - 1].itemPrice * detail[i].quantity, isRegular);
            totalAmount += itemTotal;
        } else {
            printf("Invalid input, Try Again!\n");
            i--;
        }
    }

    printf("\n\n\t\t\tBILL\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("Item\t\tQuantity\tRate\t\tTotal\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    for(i=0; i<numPurchased;i++){
        printf("%s\t\t%d\t\t$%.2f\t\tRs %.2f\n", items[detail[i].index - 1].itemName, detail[i].quantity, items[detail[i].index - 1].itemPrice, calculateTotal(items[detail[i].index - 1].itemPrice * detail[i].quantity, isRegular));
    }
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tTotal: Rs %.2f\n", totalAmount);
    return 0;
}