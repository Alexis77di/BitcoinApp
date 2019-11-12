//-------------1st project Syspro-BitCoin App------------------------//
//---------------------Alexis Chaidos-------------------------------//
//---------------------sdi1300197----------------------------------//


#include "headers.h"
#include "hashtable.h"
#include "hashwallet.h"

using namespace std;

char* transaction[8];                // for transaction file
char* balance[8];                   // for balances file
char* input[8];                    // for queries
char* seperate_transaction[8];    // multiple input till 8 transactions from keyboard
int num_of_elements1;
int num_of_elements2;
char current_time[8];  
char current_date[15];

//-----------------------------Functions that used in main------------------------------------//


//---------This function helps me to Split a string operation by delimiter ' '---------------//
//----------------------------- TransactionFile --------------------------------------------//

int split_transaction(char * ex_line ){
    
    int i=0;
    
    char* chars_array = strtok(ex_line, " ");
    while(chars_array != NULL)
    {   
        transaction[i] = chars_array;
        chars_array = strtok(NULL, " ");
        i++;
        
    }
    return i;
}


//---------This function helps me to Split a string operation by delimiter ' '---------------//
//----------------------------- BalancesFile -----------------------------------------------//

int split_balance(char * ex_line ){
    

    int i=0;
    
    char* chars_array = strtok(ex_line, " ");
    while(chars_array != NULL)
    {
        balance[i] = chars_array;
        chars_array = strtok(NULL, " ");
        i++;

    }
    return i;
}

//---------This function helps me to Split a string operation by delimiter ' '  -------------//
//----------------------------- Input File--------------------------------------------------//

int split_input(int number_of_transaction , char * ex_line ){
    
    int i=0;
    char* chars_array = strtok(ex_line, " ");
    if(number_of_transaction >= 2){
        strcpy(input[0] , " empty ");                   // fill first argument with "empty" cause I didn't generate TransactionID's
        i++;
    }
    while(chars_array != NULL)
    {   

        input[i] = chars_array;

        chars_array = strtok(NULL, " ");
        i++;
        
    }
    return i;
}

//---------This function helps me to Split a string operation by delimiter ';'  -----------------//
//----------------------------- SeperateTransaction---------------------------------------------//
//------- -Used for requestTransactions query --> multiple Transactions from keyboard ---------//

int split_multiple_input(char * ex_line ){
    
    int i=0;
    char* chars_array = strtok(ex_line, ";");
    while(chars_array != NULL)
    {
        seperate_transaction[i] = chars_array;
        chars_array = strtok(NULL, ";");
        i++;
        
    }
    return i;
}



//------------------------------------------------------------------------------------------//
//--------------------------- main Function  ----------------------------------------------//
//----------------------------------------------------------------------------------------//

int main(int argc,char *argv[]){

    int  bitCoinValue , hash1_size , hash2_size , bucketSizeBytes;
    char BalancesFile[30] , TransactionFile[30];
    char input_line[500];
    char temp[500];                   // keep the input line for multiple transactions .

    if(argc > 7){                                // check the number of arguments,must be 7 .
        cout <<"Too many arguments \n"<< endl;
        return -1;
    }

    if(argc < 7){
        cout <<"Too few arguments\n" << endl;
        return -1;
    }


    strcpy(BalancesFile , argv[1]);
    strcpy(TransactionFile , argv[2]);

    bitCoinValue = atoi(argv[3]);
    cout <<"ΒitCoin Value selected as " << bitCoinValue << endl;

    hash1_size = atoi(argv[4]);
    cout <<"Hash Table for Senders has " << hash1_size << " number of entries! " << endl;

    hash2_size = atoi(argv[5]);
    cout <<"Hash Table for Receivers has " << hash2_size << " number of entries! " << endl;

    bucketSizeBytes = atoi(argv[6]);
    cout <<"Bucket Size selected as " << bucketSizeBytes << endl;


//--------------------- HASHTABLE Creation -------------------------------------------------------------------//


    HashTable hashtable1("Senders" , hash1_size , bucketSizeBytes);      // here we create the hashtable for Senders.
    HashTable hashtable2("Receivers" , hash2_size , bucketSizeBytes);    // here we create the hashtable for Receivers.

    HashWallet hash("Wallets" , hash2_size , bucketSizeBytes);           // here we create the hashtable for wallets.



//------  Here we open the " BalancesFile.txt " file  ---------//
    char line_from_balance_file[100];
    std::ifstream myfile(BalancesFile);
        if (myfile.is_open()){
            cout << "                                                              "<< endl;
            cout << "                                                              "<< endl;
            cout << "---------------  We just opened the BalancesFile  ------------"<< endl;
            cout << "                                                              "<< endl;
            cout << "                                                              "<< endl;

            int line = 1; 

            while ( myfile.getline(line_from_balance_file,100) )
            {   
                cout << "Line " << line << " : " << line_from_balance_file << endl;

                num_of_elements1 = split_balance(line_from_balance_file);

                if(hash.check_bitcoin(balance) == 0){                                 // check for same bitcoins
                    hash.insert_wallet(balance,num_of_elements1-1,bitCoinValue);
                }
                else{
                    cout << "Error...Bitcoin already exists ." << endl;
                    return -1;
                }

                for(int k = 0; k<num_of_elements1; k++){        // xreiazetai gia elegxo bitcoin
                    strcpy( balance[k] , "*");      
                }

                line++;
            }
            myfile.close();
        }
        else {
            cout << "Unable to open file";
        }

    cout << "                                                                         "<< endl;
    cout << "                                                                         "<< endl;
    cout << "--------------  We just finished with BalancesFile  -------------"<< endl;
    cout << "                                                                         "<< endl;
    cout << "                                                                         "<< endl;


//------  Here we open the " TransactionFile.txt file " -------- //

    char line_from_transaction_file[100];
    std::ifstream myfile2(TransactionFile);
        if (myfile2.is_open()){
            cout << "---------------  We just opened the TransactionFile  ------------"<< endl;
            cout << "                                                                 "<< endl;
            cout << "                                                                 "<< endl;
            cout << "                                                                 "<< endl;

            int line = 1; 

            while ( myfile2.getline(line_from_transaction_file,100) ){ 

                cout << "Line " << line << " : " << line_from_transaction_file << endl;
                num_of_elements2 = split_transaction(line_from_transaction_file);

                if( strcmp(transaction[1],transaction[2]) != 0 ){                                     //check if sender = receiver

                    if(hash.check_money(transaction) == 1){                                         // chech if i have money for the transaction
                        cout << "                                            "<< endl;
                        hash.add_receiver_money(transaction);                                     //add money to receiver
                        hash.remove_sender_money(transaction);                                   //remove money from sender
                        cout << "                                            "<< endl;
                        hashtable1.insert_wallet(transaction);                                 //insert transaction to sender's hashtable
                        cout << "                                            "<< endl;

                        swap(transaction[1] , transaction[2]);
                        hashtable2.insert_wallet(transaction);                              //insert transaction to receiver's hashtable
                    }

                    cout << "                                                    "<< endl;

                }
                else{
                    cout << "Transaction error --> Sender and receiver is the same user ." << endl;
                    cout << "                                                            " << endl;
                }

                line++;
            }

            myfile.close();

        }
        else {
            cout << "Unable to open file";
        }

    cout << "-------------------  We just finished with TransactionFile  ------------" << endl;
    cout << "                                                                        " << endl;

    //------------------------------ INPUTS FROM USER ------------------------------------------//

    cout << "                                                                               "<< endl;
    cout << "------------------------  It's your turn...User  ------------------------------"<< endl;
  
    int result = strcmp(input_line, "exit");
    while(result != 0){

        cout << "Please, enter the valid operation that you want or 'exit' for Exit ."<< endl;
        cin.getline (input_line,500);
        cout << "                                                     " << endl;
        cout << "The user requested for this query : " << input_line    << endl;
        cout << "                                                     " << endl;

        strcpy(temp , input_line);

        int words = split_input(1,input_line);

        if(strcmp(input[0] , "walletStatus") == 0){                     // walletStatus query

            if(words == 2){

                hash.getAmount(input);
                cout << "                                              "<< endl;
            }
        }
        else if(strcmp(input[0] , "requestTransaction") == 0){         // requestTransaction query

            if(words == 4 || words == 6){

                if(strcmp(input[1],input[2]) != 0){                                // check if sender = receiver

                    if(hash.check_money(input) == 1){                             // check if I have money

                        if(words == 4){                                          // didn't receive date and time so we will generate the current date and time 

                            time_t now = time(NULL);
                            strftime(current_time, 8, "%H:%M", localtime(&now));
                            strftime(current_date , 15,"%d-%m-%Y",localtime(&now));
                            input[4] = current_date;
                            input[5] = current_time;
                            hash.add_receiver_money(input);
                            hash.remove_sender_money(input);
                            cout << "                                  "<< endl;
                            hashtable1.insert_wallet(input);
                            cout << "                                  "<< endl;
                            swap(input[1] , input[2]);
                            hashtable2.insert_wallet(input);
                            cout << "                                  " << endl;

                            
                        }
                        else{

                            if(hashtable1.check_date(input) == 1){

                                cout << "I'm ok with dates ..." << endl;

                                hash.add_receiver_money(input);
                                hash.remove_sender_money(input);
                                cout << "                                   "<< endl;
                                hashtable1.insert_wallet(input);
                                cout << "                                   "<< endl;
                                swap(input[1] , input[2]);
                                hashtable2.insert_wallet(input);
                                cout << "                                   " << endl;
                                      
                            }
                            else{
                                cout << "This transaction can't be accomplished... Date error ." << endl;
                                cout << "                                                      " << endl;

                            }
                        }

                    }
                }
                else{
                    cout << "Transaction error --> Sender and receiver is the same user ." << endl;

                }
            }   
        }
        else if(strcmp(input[0] , "requestTransactions") == 0){                                       // requestTransactions query


            if(words != 2){
                int transaction_number = split_multiple_input(temp);
                cout << "I have to deal with " << transaction_number  << " new transactions ." << endl;
                cout << "                                                                    " << endl;

                for(int i = 0; i<transaction_number; i++){

                    int debug = split_input(i+1 , seperate_transaction[i]);

                    if( strcmp(input[1],input[2]) != 0 ){                   //check if sender = receiver
                        if(hashtable1.check_date(input) == 1){             // check the dates 

                            cout << "I'm ok with dates ..." << endl;

                            if(hash.check_money(input) == 1){              // check if sender has money

                                hash.add_receiver_money(input);

                                hash.remove_sender_money(input);
                                cout << "                                   "<< endl;
                                hashtable1.insert_wallet(input);
                                cout << "                                   "<< endl;
                                swap(input[1] , input[2]);
                                hashtable2.insert_wallet(input);
                                cout << "                                   " << endl;

                            }
                        }
                        else{
                            cout << "This transaction can't be accomplished... Date error ." << endl;
                            cout << "                                                      " << endl;
                        }
                    }
                    else{
                        cout << "Transaction error --> Sender and receiver is the same user ." << endl;
                    }
                }
            }
            else{
                cout << "Transactions from input File ..." << endl;
            }
        }
        else if(strcmp(input[0] , "findEarnings") == 0){                     // findEarnings query

            if(words == 2){
                hashtable2.findEarnings(input , 0);                                    // second argument for date and time
                cout << "                                               "<< endl;
            }
            else if(words == 6){
                hashtable2.findEarnings(input , 1);
                cout << "                                               "<< endl;
                
            }

        } 
        else if(strcmp(input[0] , "findPayments") == 0){                    // findPayments query

            if(words == 2 ){                                                            // second argument for date and time
                hashtable1.findPayments(input,0);
                cout << "                                               "<< endl;
            }
            else if(words == 6){
                hashtable1.findPayments(input,1);
                cout << "                                               "<< endl;     
            }

        }
        else if(strcmp(input[0] , "bitCoinStatus") == 0){

            if(words == 2){
                cout << "Bitcoin with id : " << input[1] << " has " << bitCoinValue << " value ." << endl;
            }
        }

        result = strcmp(input_line, "exit");

    }



    cout << "                                                                        "<< endl;
    cout << "                                                                        "<< endl;
    cout << "                       Goodbye for now !!!                              " << endl;
    cout << "                                                                        "<< endl;
    cout << "                                                                        "<< endl;


}  