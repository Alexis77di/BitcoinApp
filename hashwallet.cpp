#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "hashwallet.h"
#include "linkedlist.h"



using namespace std;

char no_nm_yet[10] = "Pinokio";
char no_bitcoin_yet[5] = "****";


//----------------------- Functions for class WalletElement ----------------------------*/



WalletElement::WalletElement(char Wallet[50])  {
    strcpy(this->Wallet, Wallet);
    cout << "                                     " <<endl;
    cout << "A new WalletElement has been created!" << endl;

    bitcoins bc;
    bc.set_bitcoin(no_bitcoin_yet);
    bc.set_price(0);

    details_list = new WalletList(bc, NULL);
}


WalletElement::~WalletElement() {

    if( details_list != NULL){

        WalletList* prev = NULL;
        WalletList* entry_nd = details_list;

        while(entry_nd != NULL){
            prev = entry_nd;
            entry_nd = entry_nd->get_next_wallet();
            delete prev;
        }
    }

    cout << "A wallet element is about to be destroyed!" << endl;
}

char* WalletElement::getKey() {
        return Wallet;
}

void WalletElement::setWalletId(char WalletId[50]) {
    strcpy(this->Wallet , WalletId);           
}

void WalletElement::setCash(int cs){
	this->cash = cs;
}

int WalletElement::getCash(){
	return cash;
}


void WalletElement::insert_wallet_el(char* info[8],int el,int money){

    setWalletId(info[0]); 
    setCash(money);
    cout << "Insert completed! : New user with WalletId : " << getKey() << ", is in this Bucket !" << endl;
	cout << "I am " << info[0] << " and I Have " << cash << " $ in my wallet !                   " << endl;
    cout << "                                                                   				 " << endl;

    if (el != 0){
    	this->get_details_list()->insert_to_wallet(info,money/el,el);
    }
    else{
    	this->get_details_list()->insert_to_wallet(info,0,el);

    }
}


WalletList* WalletElement::get_details_list(){
    return details_list;
}


void WalletElement::add_wallet(char* info[8],int el,int bit_value){               //-- this function is used in order to add a bitcoin for a user that already exist
    this->get_details_list()->insert_to_wallet(info,bit_value,el);
}



int WalletElement::check_bitcoin_el(char* input[8]){         // check if bitcoin already exists

	int result;
    WalletList* entry_list;
    entry_list = details_list;
    while (entry_list!=NULL){

        result = entry_list->checkBitcoin(input);

        if(result == 1){
        	return 1;
        }
        else if(result == 0){
            return 0;
        }
        entry_list=entry_list->getNextListWallet();
    }
    return 0;
}


//---------------------------- Functions for class BuckeWallet -----------------------------------//


BucketWallet::BucketWallet(int bucket_size , BucketWallet* next_bucket) : bucket_size(bucket_size) , next_bucket(next_bucket) {
    
    bucket_elem_table = new WalletElement*[bucket_size];
    cout << "                          " <<endl;
    cout << "A Bucket has been created!" << endl;
    
    for (int i = 0; i < bucket_size; i++) {
        bucket_elem_table[i] = new WalletElement(no_nm_yet);
        
    }
}


BucketWallet::~BucketWallet() {
        
    int size = get_bucket_size();
     
    for (int i = 0; i < size; i++) {
        delete bucket_elem_table[i];
    }
    delete [] bucket_elem_table;
    	cout << "-----------------------------------------------------------------" <<endl;
        cout << "A BucketWallet with " << size << " size is about to be destroyed!" << endl;
        cout << "-----------------------------------------------------------------" <<endl;
    
}


int BucketWallet::get_bucket_size(){
    return bucket_size;        
}


BucketWallet* BucketWallet::getNextBucket() {
   return next_bucket;
}

void BucketWallet::setNextBucket(BucketWallet *next) {
    this->next_bucket = next;
}

WalletElement* BucketWallet::get_bucket_element(int pos){
    return bucket_elem_table[pos];
}


int BucketWallet::is_full(){                   // check if bucket is full
    int counter=0;
    for (int i = 0; i < bucket_size; i++) {
        int state = strcmp(bucket_elem_table[i]->getKey() , no_nm_yet);
        if(state != 0){
            counter++;
        }
    }
    return counter;
}


int BucketWallet::member_exists_b(char* value[8],int el,int bit_value){
    for (int i=0; i < bucket_size; i++){
        int state = strcmp(this->bucket_elem_table[i]->getKey() , value[0]);
        if (state==0){                       // Here we are!!!
            this->bucket_elem_table[i]->add_wallet(value,el,bit_value);
            return i;
        }

    }
    return -1 ;
}


int BucketWallet::has_money(char* info[8]){    // check if i have money for the transaction

	int state;

	for(int k=0; k<bucket_size; k++){
	    state = strcmp(this->bucket_elem_table[k]->getKey() , info[1]);
		if(state == 0){
			if(this->bucket_elem_table[k]->getCash() >= atoi(info[3])){
				cout << "I have enough money in my wallet for this transaction !" << endl;
				return 1;
			}
			else{
				return 0;
			} 
		}
	}
	return -1;
}

int BucketWallet::remove_sender_money_b(char* info[8]){        // for Transactions
	int state;

	for(int k=0; k<bucket_size; k++){
	    state = strcmp(this->bucket_elem_table[k]->getKey() , info[1]);
		if(state == 0){
			int current = (this->bucket_elem_table[k]->getCash() - atoi(info[3]));
			this->bucket_elem_table[k]->setCash(current);
			cout << "I am " << info[1] << endl;
			cout << "After this transaction, I have " << current << " $ in my wallet !" << endl;
			return 1;
		}
	}
	return -1;
}

int BucketWallet::add_receiver_money_b(char* info[8]){             // for Transactions
	int state;

	for(int k=0; k<bucket_size; k++){
	    state = strcmp(this->bucket_elem_table[k]->getKey() , info[2]);
		if(state == 0){
			
			int current = (this->bucket_elem_table[k]->getCash() + atoi(info[3]));
			this->bucket_elem_table[k]->setCash(current);
			cout << "I am " << info[2] << endl;
			cout << "After this transaction, I have " << current << " $ in my wallet !" << endl;
			return 1;
		}
	}
	return -1;
}


int BucketWallet::getAmount_b(char* input[8]){         // for walletStatus
	int state;
	for(int k=0; k<bucket_size; k++){
	    state = strcmp(this->bucket_elem_table[k]->getKey() , input[1]);
		if(state == 0){
			int current = this->bucket_elem_table[k]->getCash();
			cout << "I am " << input[1] << " and I Have " << current << " $ in my wallet ." << endl;
			return 1;
		}
	}

	return 0;
}


void BucketWallet::insert_to_bucket(char* info[8],int el,int bit_value) {            
	int money = el * bit_value;

    if(this->is_full() == bucket_size){
        
            cout <<"My bucket is full,so we need to create a new bucket !" <<endl;

            BucketWallet* new_bct_node = new BucketWallet(bucket_size,NULL);
            setNextBucket(new_bct_node);
            getNextBucket()->insert_to_bucket(info,el,bit_value);
            return;        
    }
    else{ 

        int state2;
        for(int i=0; i < bucket_size; i++){
            
            state2 = strcmp(this->bucket_elem_table[i]->getKey() , no_nm_yet);
            
             if(state2==0){
                this->bucket_elem_table[i]->insert_wallet_el(info,el,money);
                return;
            }
        }       
    }    
}

int BucketWallet::check_bitcoin_b(char* input[8]){            // check if bitcoin already exists
    
    int result;

    for(int i=0; i<get_bucket_size(); i++){       
        result = bucket_elem_table[i]->check_bitcoin_el(input);
        if(result == 1){
        	return result;
        }
    }
    return result;

}


//---------------------- Functions for class HashWallet -------------------------//

HashWallet::HashWallet(const char* hash_name , int hash_size , int bucket_size) : hash_name(hash_name),hash_size(hash_size) {
    
    table = new BucketWallet*[hash_size]; 
    cout << "                                                      " <<endl;
    cout << "A hash table for " << hash_name << " has been created!" << endl;          
    
    for (int i = 0; i < hash_size; i++) {
        table[i] = new BucketWallet(bucket_size,NULL);
    }  
}

HashWallet::~HashWallet() {
        
    int size = get_table_size();

    for (int i = 0; i < size; i++) {
        BucketWallet* prevEntry = NULL;
        BucketWallet* entry = table[i];
        while(entry != NULL){
            prevEntry = entry;
            entry = entry->getNextBucket();
            delete prevEntry;
        }

    }
    delete [] table;
    cout << "-----------------------------------------------------------------" <<endl; 
    cout << "Hash table for " << hash_name << " is about to be destroyed !    " << endl;
    cout << "-----------------------------------------------------------------" <<endl;

}

int HashWallet::get_table_size(){
    return hash_size;
       
}

int HashWallet::hash_function( char* WalletId){         // HashTable function
    int sum = 0;
    int flag = 0;
    for (int k = 0; k < 50; k++){
        if(WalletId[k] == '\0'){
            k = 50;
            flag = 1;
        }
        if(flag == 0){
            sum = sum + int(WalletId[k]);
        }
    }
    return  sum % get_table_size();
}



void HashWallet::insert_wallet(char* info[8],int el,int bit_value){                 // insert a member to our HashTable
      
	    BucketWallet* entry = member_exists(info,el,bit_value);
	    
	    if (entry==NULL){                             // new member to our hashTable
	    	cout << "We didn't find the user with WalletId " << info[0] << " in this Hash Table,  so we need to add him ! " << endl;
	        int position = hash_function(info[0]);
	        entry = table[position];
	        while (entry->getNextBucket() != NULL)
	            entry = entry->getNextBucket();
	            entry->insert_to_bucket(info,el,bit_value);
	    }
	    else{
	        cout << "The user with WalletId :" << info[0] << " already exists!"<<endl;
	    }	

}

BucketWallet* HashWallet::member_exists(char* info[8],int el,int bit_value){                 // check if user with WalletId : WalletId is in our HashTable
    
    int position = hash_function(info[0]);             //now we know exactly where we have to search
    cout << "I have to search for WalletId : " << info[0] << " , in HashTable with name " << hash_name << " , in position with number : " << position << endl;

    BucketWallet* entry = table[position];
    while(entry!= NULL){

        int result = entry->member_exists_b(info,el,bit_value);
        if(result == -1){
            entry = entry->getNextBucket();
        }
        else{
            return entry;
        }

    }

    return NULL;     //we didn't find you

}


int HashWallet::check_money(char* info[8]){	       // check if i have money for the transaction
	int pos = hash_function(info[1]);
	int result ;
	cout << "I am " << info[1] << " and now I'll check if I have enough money for this transaction ." << endl;
	BucketWallet* entry = table[pos];
	while(entry != NULL){

        result = entry->has_money(info);
        if(result == 1 || result == 0){
         	entry = NULL;
        }
        else if(result == -1){
            entry = entry->getNextBucket();
        }
    }
    if(result == -1){
     	cout << "There is no user with name " << info[1] << " in our App , so this transaction can't be accomplished ..." << endl;
    }
    else if(result == 0){
    	cout << "My money isn't enough for this transaction , so this transaction can't be accomplished ..." << endl;
    }
    return result;
}



void HashWallet::add_receiver_money(char* info[8]){             // for Transactions
	int result;
	int pos = hash_function(info[2]);
	BucketWallet* entry = table[pos];
	while(entry != NULL){
		result = entry->add_receiver_money_b(info);
		if(result == 1){
			entry = NULL;
		}
		else{
			entry = entry->getNextBucket();
		}
		
	}
	if(result != 1){
		cout << "There is no user with name " << info[2] << " in our App , so this transaction can't be accomplished ..." << endl;
	}
}

void HashWallet::remove_sender_money(char* info[8]){         // for Transactions
	int result;
    int pos = hash_function(info[1]);
	BucketWallet* entry = table[pos];

	while(entry != NULL){
		result = entry->remove_sender_money_b(info);
		if(result == 1){
			entry = NULL;
		}
		else{
			entry = entry->getNextBucket();
		}
		
	}
}



void HashWallet::getAmount(char* input[8]){     // print the total amount--walletStatus
	int result;
	int pos = hash_function(input[1]);
	BucketWallet* entry = table[pos];
	while(entry != NULL){
		result = entry->getAmount_b(input);
		if(result == 1){
			entry = NULL;
		}
		else{
			entry = entry->getNextBucket();
		}
	}
	if(result != 1){
		cout << "There is no user with name " << input[1] << " in our App ..." << endl;
	}

}

int HashWallet::check_bitcoin(char* input[8]){                  // check if bitcoin already exists

	int result;

	for(int i=0; i< get_table_size(); i++){
		BucketWallet* entry_bct;
        entry_bct = table[i];

        while (entry_bct!=NULL){
            result = entry_bct->check_bitcoin_b(input);
            if(result == 1){
            	return result;
            }
            entry_bct=entry_bct->getNextBucket();
        }

	}

	return result;
}

