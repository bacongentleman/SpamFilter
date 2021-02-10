#include <iostream>
#include <string>
#include <cctype>
#define NDEBUG
#include <cassert>

using namespace std;

void doUnitTest();
string getFirstWord(string text);
string getLastWord(string text);
string extractWord(string& text);
bool isUppercase(string text);
string makeUppercase(string text);
bool hasManyExclamations(string text);
bool isNonsenseWord(string text);
string makeUppercaseREF(string& text);
bool noWords(string text);

const bool unittest = false;

int main(){
    
    if (unittest == true)
        doUnitTest();
   
    int spamEmails{};
    int legitEmails{};
    for (;;)
    {
   
    string specWords[13]{"BUY", "CHEAP", "CLICK", "DIPLOMA", "ENLARGE", "FREE", "LONEY", "MONEY", "NOW", "OFFER", "ONLY",                                         "PILLS", "SEX"};
    string newEmail;
    int spamscore{};
    string subject;
    string subjectCopy; // used for testing after subject variable is changed within functions that reference it
    string body;
    string bodyCopy;
    string bodyResult; // used to hold value of email body from for loop
    double wordCount{};
    double upperCount{};
    double wordcountBod{};
    double uppercountBod{};

    
    cout << "Enter the subject line of the email:";
    getline(cin,subject);
    subjectCopy = subject;
        
    if (isNonsenseWord(getLastWord(subject)))
        spamscore += 40;
    
    if(hasManyExclamations(subject))
        spamscore += 20;

    
    if(!noWords(subjectCopy))
    {
        for (int i = 0; subjectCopy != ""; ++i)
        {
           if(isUppercase(extractWord(subjectCopy))) // used subjectCopy so subject is not tampered with by extractWord passing by ref
           {
               upperCount++; // counts uppercase words in subject
           }
        wordCount++;
        }
    
        double upPercent = upperCount / wordCount;
    
        if (upPercent > 0.90)
          spamscore += 30;
    }
   
  
    
    cout << " Enter the body of the email.  Press Enter on an empty line to finish.";
    do {
        getline(cin,body);
        bodyResult += body + " ";
    } while(body != ""); // loop will continue to getline until press enter on empty line
        
    bodyCopy = bodyResult;
    makeUppercaseREF(bodyResult); // used for spam rule #5. makes everything uppercase as spam words are case insensitive
    cout << endl;
 

    
    
    if (!noWords(bodyCopy))
    {
       for (int i = 0; bodyCopy != ""; ++i)
          {
              if(isUppercase(extractWord(bodyCopy)))
              {
                  uppercountBod++;
              }
          wordcountBod++;
          }
    }
    
    
       double upPercentBod = uppercountBod / wordcountBod;
       
         if (upPercentBod > 0.50)
         {
           spamscore += 40;
         }
   

    
    for (int i = 0; bodyResult != ""; ++i)
    {
        string temp;
        temp = extractWord(bodyResult);
        for (int k = 0; k < 13; ++k)
       {
            if (temp == specWords[k])
            {
                spamscore += 5;
                break;
            }
       }
    }

    
  if (spamscore > 100)
  {
      cout << "This email is classified as spam, because its spam score is " << spamscore << "." << endl;
    spamEmails++;
  }
  else if (spamscore <= 100)
  {
      cout << "This email is classified as legitimate, because its spam score is " << spamscore << "." << endl;
      legitEmails++;
  }
    
        
       
        cout << "Would you like to classify another email (y or n)? ";
    getline(cin,newEmail);
         
        
        
  while (newEmail != "y" && newEmail != "n")
  {
      cout << "Please enter y or n." << endl;
      cout << "Would you like to classify another email (y or n)? ";
      getline(cin,newEmail);
      
  }
    
     
    if (newEmail == "n")
        break;
} // end of infinite loop
    cout << "Number of spam messages: " << spamEmails << endl;
    cout << "Number of legitimate messages: " << legitEmails << endl;
    
}




string getFirstWord(string text)
{
    string answer{};
   
            for (int i = 0; i < text.size(); i++)
                {
                    if (isalpha(text[i]))
                    {
                        while (text[i] != ' ' && isalpha(text[i]) && i < text.size())
                        {
                            answer += text[i];
                            i++;
                        }
                        break;
                    }
   
                }
    return answer;
}




string getLastWord(string text)
{
    string answer{};
    long count{};
    long start{};
    long startIdex = text.size() - 1;

    for (long i = startIdex; i >= 0; i--) // starts at end of string -> beginning
    {
        if (isalpha(text[i]))
        {
            while (isalpha(text[i]) && i != -1)
            {
                count += 1;
                start = i;
                i--;
            }
            answer = text.substr(start,count);
            break;
        }
    }
    
    if (count == 0)
    {
        answer = "";
    return answer;
    }
    
    return answer;
}



string extractWord(string& text)
{
    string extWord = ""; // will hold value of removed word
    bool removed = false; // condition used after first word is removed
    string newText{}; // variable will hold the new string after first word is removed
    
    for (int i = 0; i < text.size(); ++i )
    {
        if(removed)
        {
            newText += text[i];
        }
            
        if (isalpha(text[i]) && !removed)
        {
            while(isalpha(text[i]) && i < text.size())
            {
                extWord += text[i];
                i++;
            }
            removed = true; // lets us continue with one loop and set new value for text string
            --i; // makes sure we don't double increment since the while loop already incremented
        }
    }
   
    text = newText; // sets text to the new string after word is removed
    return extWord;
}



bool isUppercase(string text)
{
    bool answer = true;
    
    for (int i = 0; i < text.size(); ++i)
    {
        if (isalpha(text[i]) && !isupper(text[i]))
            return false;
    }
    return answer;
}



string makeUppercase(string text)

{
    for (int i = 0; i < text.size(); ++i)
    {
        if(isalpha(text[i]))
        text[i] = toupper(text[i]);
    }
  
    return text;
}




string makeUppercaseREF(string& text)

{
    for (int i = 0; i < text.size(); ++i)
    {
        if(isalpha(text[i]))
        text[i] = toupper(text[i]);
    }
  
    return text;
}




bool hasManyExclamations(string text)
{
    for (int i = 0; i < text.size(); ++i)
    {
        int count = 0;
        while (text[i] == '!')
        {
            count+=1;
            if (count == 3)
            {
                return true;
            }
            i++;
        }
            
    }
    return false;
}



bool isNonsenseWord(string text)
{
int countVow{};
int nonSense{};
char vowels[10]{'a','e','i','o','u','A','E','I','O','U'};
    for (int i = 0; i < text.size(); ++i)
    {
        countVow = 0;
            for (int k = 0; k < 10; ++k)
            {
                if (text[i] == vowels[k] && isalpha(text[i]))
                {
                    countVow = 1;;
                    nonSense = 0;
                    break;
                }
               
            }
        if (countVow == 0 && isalpha(text[i]))
            nonSense += 1;
            if (nonSense == 3)
                return true;
    }
    return false;
}



bool noWords(string text)
{
    for (int i = 0; i < text.size(); ++i)
    {
        if (isalpha(text[i]))
            return false;
    }
    return true;
}

void doUnitTest()
{
    
    string test;
    cout << "enter text: ";
    getline(cin,test);
    
    cout << getFirstWord(test) << endl;
    
    cout << getLastWord(test) << endl;
    
    string removeWord;
    cout << "Enter text for removeWord: ";
    getline(cin, removeWord);
    cout << extractWord(removeWord);
 
    string isitUpper;
    cout << "Enter text for isUpper: ";
    getline(cin, isitUpper);
    cout << makeUppercase(isitUpper);
    
    string manyExclam;
    cout << "Enter text for manyExclam: ";
    getline(cin, manyExclam);
    cout << hasManyExclamations(manyExclam);
    
    
    string nonSense;
    cout << "Enter text for nonSense: ";
    getline(cin, nonSense);
    cout << isNonsenseWord(nonSense);
    
    
    string extractTest = "Extract this word765";
       assert(getFirstWord("!!hello!! this is a sentence") == "hello");
       assert(getFirstWord("!!0569") == "");
       assert(getLastWord("badabing badaBOOOM") == "badaBOOOM");
       assert(getLastWord("!! hello &^!") == "hello");
       assert(getLastWord("6753") == "");
       assert(extractWord(extractTest) == "Extract");
       assert(extractWord(extractTest) == "this");
       assert(extractWord(extractTest) == "word");
       assert(extractWord(extractTest) == "");
       assert(isUppercase("IM UPPERCAASE") == 1);
       assert(isUppercase("IM UPPERaAASE") == 0);
       assert(isUppercase("1676&") == 1);
       assert(makeUppercase("make me uppercase") == "MAKE ME UPPERCASE");
       assert(hasManyExclamations("!!hello!") == 0);
       assert(hasManyExclamations("!!hello!!!") == 1);
       assert(isNonsenseWord("hellonn") == 0);
       assert(isNonsenseWord("hellonnnp") == 1);
       assert(isNonsenseWord("!!hdi&") == 0);
       assert(noWords("!!hdi&") == 0);
       assert(noWords("!!4&") == 1);
}
