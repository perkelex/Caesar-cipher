#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

void showUsage(){
    cout << "Usage: ./runner [MODE] [MESSAGE] [SHIFT]\n";
    cout << "[MODE]: e = encipher, d = decipher.\n";
    cout << "[MESSAGE]: a string of characters; maximum length is 255";
    cout << "[SHIFT]: shift value; for enchiphering, only shifting right; for deciphering, only shifting left\n";
    cout << "Example: ./runnel e abc 3. Wrap the message in double quotes if it contains whitespaces.";
}

int findChar(const char character, const char *source){
    for(int i = 0; i < strlen(source); i++){
        if(character == source[i]){
            return i;
        }
    }
    return 42;
}

char *encipher(const char *message, int shift, const char *alphabet){
    char *encipheredMessage = (char *)malloc(strlen(message));
    int posInAlphabet = 0;
    for(int i = 0; i < (strlen(message)); i++){
        // Skip processing spaces
        if(message[i] == 32){
            encipheredMessage[i] = 32;
            continue;
        }

        posInAlphabet = findChar(message[i], alphabet);

        // Should not happen
        if(posInAlphabet == 42){
            cout << "Something went very wrong, exiting...\n";
            exit(EXIT_FAILURE);
        }

        // Stay within the alphabet
        if(posInAlphabet + shift >= 26){
            shift = shift + posInAlphabet - 26;
            encipheredMessage[i] = alphabet[shift];
        } else{
            encipheredMessage[i] = alphabet[posInAlphabet + shift];
        }
    }
    return encipheredMessage;
}

char *decipher(char *encipheredMessage, int shift, char *alphabet){
    int posInAlphabet = 0;
    char *originalMessage = (char *)malloc(strlen(encipheredMessage));
    for(int i = 0; i < (strlen(encipheredMessage)); i++){
        // Skip processing spaces
        if(encipheredMessage[i] == 32){
            originalMessage[i] = 32;
            continue;
        }

        posInAlphabet = findChar(encipheredMessage[i], alphabet);

        // Should not happen
        if(posInAlphabet == 42){
            cout << "Something went very wrong, exiting...\n";
            exit(EXIT_FAILURE);
        }

        // Stay within the alphabet
        if(posInAlphabet - shift <= 0){
            shift = - shift - posInAlphabet + 26;
            originalMessage[i] = alphabet[shift];
        } else{
            originalMessage[i] = alphabet[posInAlphabet - shift];
        }
    }
    return originalMessage;
}

int main(int argc, char **argv){
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    char *message = NULL;
    char *enciphered = NULL;
    char *deciphered = NULL;
    char mode = 0; // e = encipher, d = decipher
    int shift = 0;
    
    if(argc == 4){
        mode = argv[1][0];
        message = argv[2];
        if(argv[3] < 0){
            cout << "Negative shift value not allowed, exiting...\n";
            exit(EXIT_FAILURE);
        }
        shift = atoi(argv[3]);
    } else{
        cout << "Invalid number of parameters, exiting...\n";
        exit(EXIT_FAILURE);
    }

    switch(toupper(mode)){
        case 'E': 
            enciphered = encipher(message, shift, alphabet);
            cout << "Enciphered message is: " << enciphered << "\n";
            free(enciphered);
            break;
        case 'D':
            deciphered = decipher(message, shift, alphabet);
            cout << "Deciphered message is: " << deciphered << "\n";
            free(deciphered);
            break;
    }

    return EXIT_SUCCESS;
}
