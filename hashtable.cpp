#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "hashtable.h"
#include "linkedlist.h"

using namespace std;


char no_name_yet[10] = "Pinokio";
char no_walletId_yet[50];
char no_id_yet[11] = "No id yet!";
char no_amount_yet[6] = "*****";
char no_date_yet[11] = "0000000000";
char no_time_yet[6] = "*****";

//----------------------- Functions for class BucketElement ----------------------------*/



BucketElement::BucketElement(char Wallet[50])  {
    strcpy(this->Wallet, Wallet);
    cout << "                                     " <<endl;
    cout << "A new BucketElement has been created!" << endl;
    cout << "-------------------------------------" <<endl;

    details dtls;
    dtls.set_transaction_id(no_id_yet);
    dtls.set_receiver_walletId(no_walletId_yet);
    dtls.set_amount(no_amount_yet);
    dtls.set_date(no_date_yet);
    dtls.set_time(no_time_yet);

    details_list = new ListNode(dtls, NULL);
}


BucketElement::~BucketElement() {

    if( details_list != NULL){

        ListNode* prev = NULL;
        ListNode* entry_nd = details_list;

        while(entry_nd != NULL){
            prev = entry_nd;
            entry_nd = entry_nd->get_next_node();
            delete prev;
        }
    }
    cout << "A bucket element is about to be destroyed!" << endl;
}

char* BucketElement::getKey() {
        return Wallet;
}

void BucketElement::setWalletId(char WalletId[50]) {
    strcpy(this->Wallet , WalletId);           
}


void BucketElement::insert_element(char* info[8]){
    setWalletId(info[1]); 
    cout << "Insert completed! : New user with WalletId : " << getKey() << ", is in this Bucket!" << endl;
    this->get_details_list()->insert_transaction(info);
}


ListNode* BucketElement::get_details_list(){
    return details_list;
}


void BucketElement::add_transaction(char* info[8]){               //-- this function is used in order to add a transaction for a user that already exist
    this->get_details_list()->insert_transaction(info);
}

void BucketElement::print_receivers_wallet(char* input[8] , int operation){

    ListNode* entry_list;
    entry_list = details_list;

    if(operation ==  0){            // print earnings without dates
        while (entry_list!=NULL){
            entry_list->print_earnings(input);
            entry_list=entry_list->getNextListNode();
        }
    }
    else{                           // print earnings with dates
        while (entry_list!=NULL){
            entry_list->print_earnings_dates(input);
            entry_list=entry_list->getNextListNode();
        }
    }

}

void BucketElement::print_senders_wallet(char* input[8] , int operation){
    ListNode* entry_list;
    entry_list = details_list;

    if(operation == 0){       // print payments without dates
        while (entry_list!=NULL){
        entry_list->print_payments(input);
        entry_list=entry_list->getNextListNode();
        }
    }
    else{                   // print payments with dates

        while (entry_list!=NULL){  
            entry_list->find_print_payments(input);
            entry_list=entry_list->getNextListNode();
        }
    }

}


int BucketElement::check_date_el(char* input[8]){          // checking dates for transactions

    int result;
    ListNode* entry_list;
    entry_list = details_list;
    while (entry_list!=NULL){
        result = entry_list->checkDate(input);

        if(result == 1){
            return 1;
        }
        else if(result == 0){
            return 0;
        }
        entry_list=entry_list->getNextListNode();
    }
}

//---------------------------- Functions for class Bucket -----------------------------------//


Bucket::Bucket(int bucket_size , Bucket* next_bucket) : bucket_size(bucket_size) , next_bucket(next_bucket) {
    
    
    bucket_elem_table = new BucketElement*[bucket_size];
    cout << "                          " <<endl;
    cout << "A Bucket has been created!" << endl;
    cout << "-----------------------------------" <<endl;
    
    for (int i = 0; i < bucket_size; i++) {
        bucket_elem_table[i] = new BucketElement(no_name_yet);
        
    }

}


Bucket::~Bucket() {
        
    int size = get_bucket_size();
     
    for (int i = 0; i < size; i++) {
        delete bucket_elem_table[i];
    }
    delete [] bucket_elem_table;
        cout << "-----------------------------------" <<endl;
        cout << "A bucket is about to be destroyed!" << endl;
        cout << "-----------------------------------" <<endl;
    
}

int Bucket::get_bucket_size(){
    return bucket_size;
        
}


Bucket* Bucket::getNextBucket() {
   return next_bucket;
}

void Bucket::setNextBucket(Bucket *next) {
    this->next_bucket = next;
}

BucketElement* Bucket::get_bucket_element(int pos){
    return bucket_elem_table[pos];
}


int Bucket::is_full(){
    int counter=0;
    for (int i = 0; i < bucket_size; i++) {
        int state = strcmp(bucket_elem_table[i]->getKey() , no_name_yet);
        if(state != 0){
            counter++;
        }
    }
    return counter;
}


int Bucket::member_exists_b(char* value[8]){
    for (int i=0; i < bucket_size; i++){
        int state = strcmp(this->bucket_elem_table[i]->getKey() , value[1]);
        if (state==0){                       // Here we are!!!
            this->bucket_elem_table[i]->add_transaction(value);
            return i;
        }

    }
    return -1 ;
}

int Bucket::user_exists_b(char* input[8]){
    for (int i=0; i < bucket_size; i++){
        int state = strcmp(this->bucket_elem_table[i]->getKey() , input[1]);
        if(state==0){
            return i;
        }
    }
    return -1 ;
}


void Bucket::insert_to_bucket(char* info[8]) {
    
    if(this->is_full() == bucket_size){
        
            cout <<"There is no space in this bucket for this WalletId!!" <<endl;
            cout << "We need a new bucket in this bucket list" <<endl;


            Bucket* new_bct_node = new Bucket(bucket_size,NULL);
            setNextBucket(new_bct_node);
            getNextBucket()->insert_to_bucket(info);
            return;             
    }
    else{
        cout <<"There is space in this bucket!!" <<endl;
             
        int state2;
        for(int i=0; i < bucket_size; i++){
            
            state2 = strcmp(this->bucket_elem_table[i]->getKey() , no_name_yet);
            
             if(state2==0){
                this->bucket_elem_table[i]->insert_element(info);
                return;
            }
        }       
    }  
}


//---------------------- Functions for class HashTable -------------------------//

HashTable::HashTable(const char* hash_name , int hash_size , int bucket_size) : hash_name(hash_name),hash_size(hash_size) {
    
    table = new Bucket*[hash_size]; 
    cout << "                                                      " <<endl;
    cout << "A hash table for " << hash_name << " has been created!" << endl;
    cout << "------------------------------------------------------" <<endl;
               
    for (int i = 0; i < hash_size; i++) {
        table[i] = new Bucket(bucket_size,NULL);
    }   
}

HashTable::~HashTable() {
        
    int size = get_table_size();

    for (int i = 0; i < size; i++) {

        Bucket* prevEntry = NULL;
        Bucket* entry = table[i];
        while(entry != NULL){
            prevEntry = entry;
            entry = entry->getNextBucket();
            delete prevEntry;
        }

    }
    delete [] table;
    cout << "-----------------------------------" <<endl;
    cout << "Hash table for " << hash_name << " is about to be destroyed!" << endl;
    cout << "-----------------------------------" <<endl;

}

int HashTable::get_table_size(){
    return hash_size;       
}


int HashTable::hash_function( char* WalletId){              
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



void HashTable::insert_wallet(char* info[8]){              // insert a new member to our hash
        
    Bucket* entry = member_exists(info);

    if (entry==NULL){                             // new member to our hashTable
        int position = hash_function(info[1]);
        entry = table[position];
        while (entry->getNextBucket() != NULL)
            entry = entry->getNextBucket();
            entry->insert_to_bucket(info);
    }
    else{
        cout << "The user with WalletId :" << info[1] << " already exists!"<<endl;
    }

}

Bucket* HashTable::member_exists(char* info[8]){
    
    int position = hash_function(info[1]);             //now we know exactly where we have to search
    cout << "I have to search for WalletId : " << info[1] << " , in HashTable with name " << hash_name << " , in position with number : " << position << endl;

    Bucket* entry = table[position];
    while(entry!= NULL){
        int result = entry->member_exists_b(info);
        if(result == -1){
            entry = entry->getNextBucket();
        }
        else{
            return entry;
        }

    }

    return NULL;     //we didn't find you

}


Bucket* HashTable::user_exists(char* input[8]){
    int position = hash_function(input[1]);
    cout << "I have to search for WalletId : " << input[1] << " , in HashTable with name " << hash_name << " , in position with number : " << position << endl;
    Bucket* entry = table[position];
    while(entry!= NULL){
        int result = entry->user_exists_b(input);
        if(result == -1){
            entry = entry->getNextBucket();
        }
        else{
            return entry;
        }

    }

    return NULL;     //we didn't find you
}

void HashTable::findEarnings(char* input[8] , int operation){       

    int position = hash_function(input[1]);
    Bucket* entry = user_exists(input);
    if (entry!=NULL){ 
        int bct_elem_position = entry->user_exists_b(input);
        entry->get_bucket_element(bct_elem_position)->print_receivers_wallet(input , operation);
    }
    

}

void HashTable::findPayments(char* input[8] , int operation){
    int position = hash_function(input[1]);
    Bucket* entry = user_exists(input);
    if (entry!=NULL){ 
        int bct_elem_position = entry->user_exists_b(input);
        entry->get_bucket_element(bct_elem_position)->print_senders_wallet(input , operation);
    }
}


int HashTable::check_date(char* input[8]){            // checking dates for transactions

    int result;
    int position = hash_function(input[1]);
    Bucket* entry = user_exists(input);

    if (entry!=NULL){ 
        int bct_elem_position = entry->user_exists_b(input);
        result = entry->get_bucket_element(bct_elem_position)->check_date_el(input);
    }

    return result;

}
