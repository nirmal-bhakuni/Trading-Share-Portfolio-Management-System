#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCKS 100

typedef struct {
    char name[20];
    float buy_price;
    float current_price;
    int quantity;
} Stock;

Stock portfolio[MAX_STOCKS];
int stock_count = 0;

void addStock() {
    if (stock_count >= MAX_STOCKS) {
        printf("Portfolio is full!\n");
        return;
    }
    printf("Enter stock name: ");
    scanf("%s", portfolio[stock_count].name);
    printf("Enter buy price: ");
    scanf("%f", &portfolio[stock_count].buy_price);
    printf("Enter current price: ");
    scanf("%f", &portfolio[stock_count].current_price);
    printf("Enter quantity: ");
    scanf("%d", &portfolio[stock_count].quantity);
    stock_count++;
    printf("Stock added successfully!\n\n");
}

void removeStock() {
    char name[20];
    printf("Enter stock name to remove: ");
    scanf("%s", name);
    for (int i = 0; i < stock_count; i++) {
        if (strcmp(portfolio[i].name, name) == 0) {
            for (int j = i; j < stock_count - 1; j++) {
                portfolio[j] = portfolio[j + 1];
            }
            stock_count--;
            printf("Stock removed successfully!\n\n");
            return;
        }
    }
    printf("Stock not found!\n\n");
}

void savePortfolio() {
    FILE *file = fopen("portfolio.dat", "wb");
    if (!file) {
        printf("Error saving portfolio!\n");
        return;
    }
    fwrite(&stock_count, sizeof(int), 1, file);
    fwrite(portfolio, sizeof(Stock), stock_count, file);
    fclose(file);
    printf("Portfolio saved successfully!\n\n");
}

void loadPortfolio() {
    FILE *file = fopen("portfolio.dat", "rb");
    if (!file) {
        printf("No saved portfolio found. Starting fresh.\n\n");
        return;
    }
    fread(&stock_count, sizeof(int), 1, file);
    fread(portfolio, sizeof(Stock), stock_count, file);
    fclose(file);
    printf("Portfolio loaded successfully!\n\n");
}

void analyzePortfolio() {
    float totalInvestment = 0, totalCurrentValue = 0, netProfitLoss = 0;
    printf("\nStock Portfolio Analysis:\n");
    printf("-------------------------------------------\n");
    printf("%-10s %-10s %-10s %-10s %-10s\n", "Stock", "Buy Price", "Cur. Price", "Qty", "Profit/Loss");
    printf("-------------------------------------------\n");
    for (int i = 0; i < stock_count; i++) {
        float investment = portfolio[i].buy_price * portfolio[i].quantity;
        float currentValue = portfolio[i].current_price * portfolio[i].quantity;
        float profitLoss = currentValue - investment;
        totalInvestment += investment;
        totalCurrentValue += currentValue;
        netProfitLoss += profitLoss;
        printf("%-10s %-10.2f %-10.2f %-10d %-10.2f\n", portfolio[i].name, portfolio[i].buy_price, portfolio[i].current_price, portfolio[i].quantity, profitLoss);
    }
    printf("-------------------------------------------\n");
    printf("Total Investment: %.2f\n", totalInvestment);
    printf("Current Value: %.2f\n", totalCurrentValue);
    printf("Net Profit/Loss: %.2f\n\n", netProfitLoss);
}

void exportToCSV() {
    FILE *file = fopen("stocks.csv", "w");
    if (!file) {
        printf("Error exporting to CSV!\n");
        return;
    }
    fprintf(file, "Stock,Buy Price,Current Price,Quantity\n");
    for (int i = 0; i < stock_count; i++) {
        fprintf(file, "%s,%.2f,%.2f,%d\n", portfolio[i].name, portfolio[i].buy_price, portfolio[i].current_price, portfolio[i].quantity);
    }
    fclose(file);
}

void displayGraph() {
    exportToCSV();
    printf("Generating stock performance graph...\n");
    system("start pythonw graph.py");


}

int main() {
    int choice;
    loadPortfolio();
    do {
        printf("\n====================================\n");
        printf("Stock Portfolio Tracker\n");
        printf("====================================\n");
        printf("1. Add Stock\n2. Remove Stock\n3. Analyze Portfolio\n4. Display Graph\n5. Save & Exit\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1: addStock(); break;
            case 2: removeStock(); break;
            case 3: analyzePortfolio(); break;
            case 4: displayGraph(); break;
            case 5: savePortfolio(); printf("Exiting...\n\n"); break;
            default: printf("Invalid choice! Please try again.\n\n");
        }
    } while (choice != 5);
    return 0;
}
