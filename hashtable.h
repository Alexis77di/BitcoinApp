#include <iostream>
#include <stdlib.h>
#include "linkedlist.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H


using namespace std;


// ---------------  BucketElement   ------------------//


class BucketElement {
	private:
		char Wallet[50]; 
		ListNode* details_list;	
	public:
		BucketElement(char Wallet[50]);
		~BucketElement();
		char* getKey();
		void setWalletId(char WalletId[50]);
		void insert_element(char* info[8]); 
		ListNode* get_details_list();
		void print_receivers_wallet(char* input[8] , int operation);
		void print_senders_wallet(char* input[8] , int operation);
		void add_transaction(char* info[8]);
		int check_date_el(char* input[8]);
};




// ---------------   Bucket    ------------------//


class Bucket {
	private:
    	int bucket_size;      						//user's choice
    	Bucket* next_bucket;
    	BucketElement** bucket_elem_table;   		
	public:
    	Bucket(int bucket_size , Bucket* next_bucket);
    	~Bucket();
    	int get_bucket_size();
    	Bucket *getNextBucket();
    	void setNextBucket(Bucket *next);
    	void insert_to_bucket(char* info[8]);
    	int is_full();
    	int member_exists_b(char* value[8]);
    	int user_exists_b(char* input[8]);
    	BucketElement* get_bucket_element(int pos);


};


// ---------------    Hash Table     ------------------//



class HashTable {
	private:
		Bucket** table;   		
		const char* hash_name;
		int hash_size; 				//user's choice
	public:
		HashTable(const char* hash_name , int hash_size , int bucket_size);
		~HashTable();
		int get_table_size();
		int hash_function( char* WalletId);
		void insert_wallet(char* info[8]);
		Bucket* member_exists(char* info[8]);
		Bucket* user_exists(char* input[8]);
		void findEarnings(char* input[8] , int operation );
		void findPayments(char* input[8] , int operation);
		int check_date(char* input[8]);

};









#endif 