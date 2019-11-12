#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "linkedlist.h"


using namespace std;


char no_walletId_yet2[15] = "No wallet yet!";
char no_id_yet2[50] = "0000000000000000000000000000000000000000000000000";
char no_amount_yet2[6] = "*****";
char no_date_yet2[11] = "0000000000";
char no_time_yet2[6] = "*****";
char no_bitcoin_yet2[5] = "****";


//  This function helps me to compare dates //
// I found it in this link --> https://stackoverflow.com/questions/13787702/comparing-2-dates-in-c

int date_cmp(const char *d1, const char *d2)
{
    int rc;
    // compare years
    rc = strncmp(d1 + 6, d2 + 6, 4);
    if (rc != 0)
        return rc;

    // compare months
    rc = strncmp(d1 + 3, d2 + 3, 2);
    if (rc != 0)
        return rc;

    // compare days
    return strncmp(d1, d2, 2);
}





//------------  Getters and Setters for our details Struct  ----------------//

void details::set_transaction_id(char coin_id[11]){
	strcpy(this->transaction_id , coin_id);

}

void details::set_receiver_walletId(char rec_id[15]){
	strcpy(this->receiver_walletId , rec_id);

}

void details::set_amount(char amnt[3]){
	strcpy(this->amount , amnt);
}

void details::set_date(char dt[11]){
	strcpy(this->date , dt);

}


void details::set_time(char tm[6]){
	strcpy(this->time , tm);

}




char* details::get_transaction_id(){
	return transaction_id;
}

char* details::get_receiver_walletId(){
	return receiver_walletId;
}
    

char* details::get_date(){
	return date;
}
   
char* details::get_amount(){
	return amount;
}

char* details::get_time(){
	return time;
}




//-------------------------  Functions for our ListNode  --------------------------//

ListNode::ListNode( details dtls, ListNode* next_node ) : next_node(next_node)  {
	
	for (int i = 0; i < 30; i++) {
        member_details[i].set_transaction_id(dtls.get_transaction_id());
        member_details[i].set_receiver_walletId(dtls.get_receiver_walletId());
        member_details[i].set_amount(dtls.get_amount());
        member_details[i].set_date(dtls.get_date());
        member_details[i].set_time(dtls.get_time());

    }
    cout << "                                 " <<endl;
    cout << "A new list node has been created!" << endl;
    cout << "-----------------------------------" <<endl;
}


ListNode::~ListNode() {
   cout << "A list node is about to be destroyed!" << endl;
}



ListNode* ListNode::getNextListNode() {
    return next_node;
}


int ListNode::is_list_full(){
	
	int counter2=0;
    for (unsigned i = 0; i < 30 ; i++) {
       int state2 = strcmp(this->member_details[i].get_transaction_id(), "No id yet!");
       if(state2 != 0){
            counter2++;
       }
    }
    return counter2;
       
}



ListNode *ListNode::get_next_node(){
	return next_node;
}




void ListNode::set_next_node(ListNode *next){
	this->next_node = next;
}



void ListNode::insert_transaction(char* info[8]) {

	if(this->is_list_full() == 30){
	 	details dtls;

    	dtls.set_transaction_id(no_id_yet2);
    	dtls.set_receiver_walletId(no_walletId_yet2);
    	dtls.set_amount(no_amount_yet2);
    	dtls.set_date(no_date_yet2);
    	dtls.set_time(no_time_yet2);

		ListNode* new_list_node = new ListNode(dtls , NULL);
		set_next_node(new_list_node);
		get_next_node()->insert_transaction(info);
		return;

	}
	else{

		for(int i=0; i<30; i++){
			int state = strcmp(this->member_details[i].get_transaction_id() ,"No id yet!" );
			if(state == 0){
				//we find a free slot in this table!!
				member_details[i].set_transaction_id(info[0]);
				member_details[i].set_receiver_walletId(info[2]);
				member_details[i].set_amount(info[3]);
				member_details[i].set_date(info[4]);
				member_details[i].set_time(info[5]);

				return;
			}
		}
	}
}

void ListNode::print_earnings(char* input[8]){          // print earnings without dates
	int flag = 1;
	int sum = 0;
	for(int i=0; i<30; i++){

		flag = strcmp(this->member_details[i].get_transaction_id() , "No id yet!" );
		if(flag != 0){
			int amount = atoi(this->member_details[i].get_amount());

			sum = sum + amount;
			cout << " 													 " << endl;
			cout << "------  Transaction Details for this ListNode ------" << endl;
			cout << " 													 " << endl;
			cout << "The TransactionId for this transaction is: "<< this->member_details[i].get_transaction_id() << endl;
			cout << "The sender for this transaction is: "<< this->member_details[i].get_receiver_walletId() << endl;
			cout << "The amount for this transaction is: " << this->member_details[i].get_amount() << endl;
			cout << "The date for this transaction is: "<< this->member_details[i].get_date() << endl;
			cout << "The time for this transaction is: "<< this->member_details[i].get_time() << endl;
		}
	}
	cout << " 													 " << endl;
	cout << "I am " << input[1] << " and I received " << sum << " $ from my friends !" << endl;
}

void ListNode::print_earnings_dates(char* input[8]){        // print earnings with dates
	int flag = 1;
	int sum = 0;
	for(int i=0; i<30; i++){

		flag = strcmp(this->member_details[i].get_transaction_id() , "No id yet!" );
		if(flag != 0){
			int amount = atoi(this->member_details[i].get_amount());
			sum = sum + amount;

			if( date_cmp( input[3] , this->member_details[i].get_date()) < 0  && date_cmp( input[5] , this->member_details[i].get_date()) > 0 ){

				cout << " 													 " << endl;
				cout << "------  Transaction Details for this ListNode ------" << endl;
				cout << " 													 " << endl;
				cout << "The TransactionId for this transaction is: "<< this->member_details[i].get_transaction_id() << endl;
				cout << "The receiver for this transaction is: "<< this->member_details[i].get_receiver_walletId() << endl;
				cout << "The amount for this transaction is: " << this->member_details[i].get_amount() << endl;
				cout << "The date for this transaction is: "<< this->member_details[i].get_date() << endl;
				cout << "The time for this transaction is: "<< this->member_details[i].get_time() << endl;
			}
		}
	}
	cout << " 													 " << endl;
	cout << "I am " << input[1] << " and I received " << sum << " $ from my friends !" << endl;
}

void ListNode::print_payments(char* input[8]){          // print payments without dates
	int flag = 1;
	int sum = 0;
	for(int i=0; i<30; i++){

		flag = strcmp(this->member_details[i].get_transaction_id() , "No id yet!" );
		if(flag != 0){
			int amount = atoi(this->member_details[i].get_amount());

			sum = sum + amount;
			cout << " 													 " << endl;
			cout << "------  Transaction Details for this ListNode ------" << endl;
			cout << " 													 " << endl;
			cout << "The TransactionId for this transaction is: "<< this->member_details[i].get_transaction_id() << endl;
			cout << "The receiver for this transaction is: "<< this->member_details[i].get_receiver_walletId() << endl;
			cout << "The amount for this transaction is: " << this->member_details[i].get_amount() << endl;
			cout << "The date for this transaction is: "<< this->member_details[i].get_date() << endl;
			cout << "The time for this transaction is: "<< this->member_details[i].get_time() << endl;
		}
	}
	cout << " 													 " << endl;
	cout << "I am " << input[1] << " and I sent " << sum << " $ to my friends !" << endl;
}


void ListNode::find_print_payments(char* input[8]){           // print payments with dates
	int flag = 1;
	int sum = 0;

	for(int i=0; i<30; i++){
		flag = strcmp(this->member_details[i].get_date() , "0000000000" );
		if(flag != 0){

			int amount = atoi(this->member_details[i].get_amount());
			sum = sum + amount;

			if( date_cmp( input[3] , this->member_details[i].get_date()) < 0  && date_cmp( input[5] , this->member_details[i].get_date()) > 0 ){

				cout << " 													 " << endl;
				cout << "------  Transaction Details for this ListNode ------" << endl;
				cout << " 													 " << endl;
				cout << "The TransactionId for this transaction is: "<< this->member_details[i].get_transaction_id() << endl;
				cout << "The receiver for this transaction is: "<< this->member_details[i].get_receiver_walletId() << endl;
				cout << "The amount for this transaction is: " << this->member_details[i].get_amount() << endl;
				cout << "The date for this transaction is: "<< this->member_details[i].get_date() << endl;
				cout << "The time for this transaction is: "<< this->member_details[i].get_time() << endl;

			}
		}
	}

	cout << " 													 " << endl;
	cout << "I am " << input[1] << " and I sent " << sum << " $ to my friends !" << endl;
	return ;
} 

int ListNode::checkDate(char* input[8]){         // check which date is earlier
	int flag = 1;
	int flag2 = 0;
	for(int i=0; i<30; i++){

		flag = strcmp(this->member_details[i].get_transaction_id() , "No id yet!" );
		if(flag == 0){
			char* last_date = this->member_details[i-1].get_date();
			cout << "I have to check which transaction is earlier .." << endl;
			cout << "The last transaction in my list has date : " << last_date << endl;
			cout << "The new transaction that I want to add in my list has date : " << input[4] << endl;
			flag2 = date_cmp(input[4] , last_date);
			if(flag2 > 0){
				return 1;
			}
			else{
				return 0;
			}
		}
	}
}


//------------------ Getters and Setters for our bitcoins Struct ------------------------------------------------//


void bitcoins::set_bitcoin(char btcn[5]){
	strcpy(this->bitcoin , btcn);

}


void bitcoins::set_price(int pr){
	this->price =pr;

}




char* bitcoins::get_bitcoin(){
	return bitcoin;
}

int bitcoins::get_price(){
	return price;
}



//-------------------------  Functions for our WalletList  --------------------------//


WalletList::WalletList( bitcoins bc, WalletList* next_wallet ) : next_wallet(next_wallet)  {
	
	for (int i = 0; i < 7; i++) {
        member_bitcoins[i].set_bitcoin(bc.get_bitcoin());
        member_bitcoins[i].set_price(0);
    }
    cout << "                                 " <<endl;
    cout << "A new wallet node has been created!                         " << endl;
    cout << "------------------------------------------------------------" <<endl;
}


WalletList::~WalletList() {
   cout << "A wallet node is about to be destroyed!" << endl;
}



WalletList* WalletList::getNextListWallet() {
    return next_wallet;
}


int WalletList::is_wallet_full(){
	
	int counter2=0;
    for (unsigned i = 0; i < 7 ; i++) {
       int state2 = strcmp(this->member_bitcoins[i].get_bitcoin(), "****");
       if(state2 != 0){
            counter2++;
       }
    }
    return counter2;
       
}


WalletList *WalletList::get_next_wallet(){
	return next_wallet;
}




void WalletList::set_next_wallet(WalletList *next){
	this->next_wallet = next;
}



void WalletList::insert_to_wallet(char* info[8],int price,int el) {

	if(this->is_wallet_full() == 7){
	 	bitcoins bc;

    	bc.set_bitcoin(no_bitcoin_yet2);
    	bc.set_price(0);

		WalletList* new_wallet_node = new WalletList(bc , NULL);
		set_next_wallet(new_wallet_node);
		get_next_wallet()->insert_to_wallet(info,price,el);
		return;
	}

	else{

		for(int i=0; i<el; i++){
			int state = strcmp(this->member_bitcoins[i].get_bitcoin() ,"****" );
			if(state == 0){
				member_bitcoins[i].set_bitcoin(info[i+1]);
				member_bitcoins[i].set_price(price);
			}

		}
		return;
	}
}


void WalletList::print_wallet(){

	int flag = 1;

	for(int i=0; i<7; i++){
	    flag = strcmp(this->member_bitcoins[i].get_bitcoin() ,"****" );

		if(flag != 0){
			cout << "The BitCoin number " << i+1 << "  is: "<< this->member_bitcoins[i].get_bitcoin()  << " and the price for this bitcoin is: " << this->member_bitcoins[i].get_price() << endl;
		}
	}
}


int WalletList::checkBitcoin(char* input[8]){               // check if bitcoin already exists
	int flag = 0;
	int flag2;
	for(int i=0; i<7; i++){
		if(strcmp(this->member_bitcoins[i].get_bitcoin() , "****" ) == 0){
			flag = i;
			i = 7;
		}
	}

	for(int k = 0; k < flag; k++){
		for(int j = 0; j<flag; j++){
			flag2 = strcmp(this->member_bitcoins[k].get_bitcoin() , input[j+1]);
			if(flag2 == 0){
				cout << "BitCoin with id " << this->member_bitcoins[k].get_bitcoin() << "  already exists ." << endl; 
				return 1;
			}
		}
	}
	return 0;
}


