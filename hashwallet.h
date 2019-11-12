#include <iostream>
#include <stdlib.h>
#include "linkedlist.h"

#ifndef HASHWALLET_H
#define HASHWALLET_H

using namespace std;



// ---------------  WalletElement   ------------------//


class WalletElement {
	private:
		char Wallet[50]; 
		int cash;
		WalletList* details_list;	
	public:
		WalletElement(char Wallet[50]);
		~WalletElement();
		char* getKey();
		int getCash();
		void setWalletId(char WalletId[50]);
		void setCash(int cs);
		void insert_wallet_el(char* info[8],int elements,int money); 
		WalletList* get_details_list();
		void add_wallet(char* info[8],int el,int bit_value);
		int check_bitcoin_el(char* input[8]);
};




/* ---------------   Bucket for Wallets    ------------------*/


class BucketWallet {
	private:
    	int bucket_size;      						//user's choice
    	BucketWallet* next_bucket;
    	WalletElement** bucket_elem_table;   	
	public:
    	BucketWallet(int bucket_size , BucketWallet* next_bucket);
    	~BucketWallet();
    	int get_bucket_size();
    	BucketWallet *getNextBucket();
    	void setNextBucket(BucketWallet *next);
    	void insert_to_bucket(char* info[8],int elements,int bit_value);
    	int is_full();
    	int member_exists_b(char* value[8],int el,int bit_value);
    	WalletElement* get_bucket_element(int pos);
    	int has_money(char* info[8]);
    	int add_receiver_money_b(char* info[8]);
    	int remove_sender_money_b(char* info[8]);
    	int getAmount_b(char* input[8]);
    	int check_bitcoin_b(char* input[8]);
};




// ---------------    Hash Table for Wallets    ------------------//



class HashWallet {
	private:
		BucketWallet** table;   			//a hash table is a table of pointers to BucketWallets
		const char* hash_name;
		int hash_size; 					  //user's choice
	public:
		HashWallet(const char* hash_name , int hash_size , int bucket_size);
		~HashWallet();
		int get_table_size();
		int hash_function( char* WalletId);
		void insert_wallet(char* info[8],int elements,int bit_value);
		BucketWallet* member_exists(char* info[8],int el,int bit_value);
		int check_money(char* info[8]);
		void getAmount(char* input[8]);
		void add_receiver_money(char* info[8]);	
		void remove_sender_money(char* info[8]);
		int check_bitcoin(char* input[8]);

};






































#endif 