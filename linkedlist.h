#include <iostream>
#include <stdlib.h>
#ifndef LINKEDLIST_H
#define LINKEDLIST_H


using namespace std;

#define SIZE_OF_LIST 30
#define SIZE_OF_WALLETLIST 7

struct details
{
    char transaction_id[11];
    char receiver_walletId[50];
    char amount[6];
    char date[11];
    char time[6];


// -----------------------  Setters  ----------------------------//
    
    void set_transaction_id(char coin_id[11]);
    void set_receiver_walletId(char rec_id[50]);
    void set_amount(char amnt[3]);
    void set_date(char dt[11]);
    void set_time(char tm[6]);

// ----------------------  Getters  ---------------------------//

    char* get_transaction_id();
    char* get_receiver_walletId();
    char* get_amount();
    char* get_date();
    char* get_time();

};



class ListNode {
	
	private:
		ListNode* next_node;  
		details member_details[SIZE_OF_LIST];


	public:
		ListNode( details dtls, ListNode* next_node );
		~ListNode();
		void insert_transaction(char* info[8]);
		int is_list_full();
		ListNode *get_next_node();
    	void set_next_node(ListNode *next_node);
        ListNode* getNextListNode();
        void print_earnings(char* input[8]);
        void print_payments(char* input[8]);
        int checkDate(char* input[8]);
        void find_print_payments(char* input[8]);
        void print_earnings_dates(char* input[8]);
};


struct bitcoins
{
	char bitcoin[5];
	int price;
	//binary_tree binary;

// --------------------------  Setters  ---------------------------//

	void set_bitcoin(char btcn[5]);
	void set_price(int pr);

// ---------------------------- Getters  -------------------------//

	char* get_bitcoin();
	int get_price();

};


// struct binary_tree {
// 	binary_tree *left;    		// pointer to the left child 
// 	binary_tree *right;   	   // pointer to the right child 
// 	int size;
// 	int height; 	
// 	int value;
// 	char* walletId[50];
// };


class WalletList {

	private:
		WalletList* next_wallet;
		bitcoins member_bitcoins[SIZE_OF_WALLETLIST];

	public:
		WalletList( bitcoins bc, WalletList* next_wallet );
		~WalletList();
		void insert_to_wallet(char* info[8],int price,int el);
		WalletList* getNextListWallet();
		int is_wallet_full();
		WalletList *get_next_wallet();
    	void set_next_wallet(WalletList *next_wallet);
        void print_wallet();
        int checkBitcoin(char* input[8]);
};


#endif 