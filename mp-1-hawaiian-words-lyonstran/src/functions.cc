#include "functions.hpp"

#include <cctype>
#include <iostream>

/**
 * TODO: Implement this function
 * @param word word to change to lowercase
 * @return result of changing every character in word to lowercase
 */
std::string StringToLower(const std::string& word) {
  
  std::string result;
  for (char c : word) {
    result += (char)tolower(c);
  }
  return result;
}

/**
 * TODO: Implement this function
 * @param v1 first character in potential vowel group
 * @param v2 second character in potential vowel group
 * @return true if v1 and v2 form a valid vowel group
 */
bool IsVowelGroup(const char& v1, const char& v2) {
 
  return (v1 == 'a' && v2 == 'i') || (v1 == 'a' && v2 == 'e') || (v1 == 'a' && v2 == 'o')
  || (v1 == 'a' && v2 == 'u') || (v1 == 'e' && v2 == 'i') || (v1 == 'e' && v2 == 'u')
  || (v1 == 'i' && v2 == 'u') || (v1 == 'o' && v2 == 'i') || (v1 == 'o' && v2 == 'u')
  || (v1 == 'u' && v2 == 'i');
}

/**
 * TODO: Complete this function
 * @param v potential vowel character
 * @return true if v is a vowel
 */
bool IsVowel(const char& v) {
  
  return v == 'a' || v == 'e' || v == 'i' || v == 'o' || v == 'u';
}

/**
 * TODO: Complete this function
 * @param c potential consonant character
 * @return true if c is a consonant
 */
bool IsConsonant(const char& c) {
 
  return c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' || c == 'n' || c == 'w';
}

/**
 * TODO: Implement this function
 * @param c character to check validity of
 * @return true if input c is a valid character in the Hawaiian language, false
 * otherwise
 */
bool IsValidCharacter(const char& c) {
  
  return IsConsonant(c) || IsVowel(c) || c == '\''|| c == ' ';
}

/**
 * TODO: Implement this function
 * @param word word to check validity of
 * @return true if every character in word is a valid character in the Hawaiian
 * language, false otherwise
 */
bool IsValidWord(const std::string& word) {
  
  for (char c : word) {
    if (!IsValidCharacter(c)) {
      return false;
    }
  }
  return true;
}

/**
 * TODO: Implement this function
 * @param c consonant to get pronunciation of
 * @param prev character before c, used for determining w translation
 *    set to null character as default if no value is passed in
 * @return pronunciation of the consonant c as a char
 */
char ConsonantPronunciation(const char& c, const char& prev) {
  
  if (IsConsonant(c)) {
    if ((c == 'w' && prev == 'i') || (c == 'w' && prev == 'e')) {
      return 'v';
    }
    if (c == 'p') {
      return 'p';
    }
    if (c == 'k') {
      return 'k';
    }
    if (c == 'h') {
      return 'h';
    }
    if (c == 'l') {
      return 'l';
    }
    if (c == 'm') {
      return 'm';
    }
    if (c == 'n') {
      return 'n';
    }
    if (c == 'w') {
      return 'w';
    }
  }
  return '\0';
}

/**
 * TODO: Implement this function
 * @param v1 first vowel in a vowel grouping
 * @param v2 second vowel in a vowel grouping
 * @return the pronunciation of the vowel grouping made up of v1 and v2
 * as a string
 */
std::string VowelGroupPronunciation(const char& v1, const char& v2) {
  if (v1 == 'i' && v2 == 'u') {
    return "ew";
  }
  if (v1 == 'u' && v2 == 'i') {
    return "ooey";
  }
  if (v1 == 'o') {
    if (v2 == 'i') { 
      return "oy"; 
    }
    if (v2 == 'u') { 
      return "ow"; 
    }
  }
  if (v1 == 'e') {
    if (v2 == 'i') { 
      return "ay"; 
    }
    if (v2 == 'u') { 
      return "eh-oo"; 
    }
  }
  if (v1 == 'a') {
    if (v2 == 'o' || v2 == 'u') { 
      return "ow"; 
    }
    if (v2 == 'e' || v2 == 'i') { 
      return "eye"; 
    }
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param v single vowel to get pronunciation of
 * @return the pronunciation of v as a string
 */
std::string SingleVowelPronunciation(const char& v) {
  
  if (IsVowel(v)) {
    if (v == 'a') {
      return "ah";
    }
    if (v == 'e') {
      return "eh";
    }
    if (v == 'i') {
      return "ee";
    }
    if (v == 'o') {
      return "oh";
    }
    if (v == 'u') {
      return "oo";
    }
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param prev first character in set of three passed to function
 * @param curr second character in set of three passed to function
 * @param next third character in set of three passed to function
 * @return pronunciation of curr using next and prev as needed to determine
 * result
 */
std::string ProcessCharacter(const char& prev, const char& curr, const char& next) {
  
  std::string proccessed_pronun;
  if (IsVowelGroup(curr, next)) {
    proccessed_pronun += VowelGroupPronunciation(curr, next);
  } else if (IsVowel(curr)) {
    proccessed_pronun += SingleVowelPronunciation(curr);
  } else if (IsConsonant(curr)) {
    proccessed_pronun += ConsonantPronunciation(curr, prev);
  } else {
    proccessed_pronun = curr;
  }
  std::cout << proccessed_pronun << std::endl;
  return proccessed_pronun;
}

/**
 * TODO: Implement this function
 * @param word string to get pronunciation of
 * @return pronunciation of word
 */
// You will likely want to examine each character in the input std::string and build up the pronunciation 
//guide from an empty std::string as you go. However, for this to work, some rules need access to the 
//previous character (like 'w') and others to the next character (vowel groups), so you will need to record 
//the current character as well as the previous and next characters inside your loop. Doing this safely requires 
//some care, given that the previous and next characters are not always valid depending on where you are in the std::string.

// Usually you'll want to consume one character at a time. But when you find a vowel group, 
//you'll need to make sure you skip the next character. For example, given the input "ai", you'll
// need to make sure you output only "eye" and not "eye-ee" or "ah-ee".

// Finally, take care to insert dashes in the correct places. A pronunciation should never end in a dash, and there 
//should not be dashes before spaces or apostrophes. The dashes should be handled in the Pronunciation function
// there should be a hyphen (dash) after every vowel group or vowel unless it is at the end of a word or before an apostrophe
std::string Pronunciation(const std::string& word) {
  std::cout << "Input to Pronunciation() : " << word << std::endl;
  std::string word_pronounced;
  for (unsigned int i = 0; i < word.size(); ++i) {
    char p = ' ';
    char n = ' ';
    char current = word.at(i);
    if (i != 0) {
      p = word.at(i - 1);
    }
    if (i != word.size() - 1) {
      n = word.at(i + 1);
    }
    if (IsVowelGroup(current, n)) {
      i++;
    }
    word_pronounced += ProcessCharacter(p, current, n);
    if ((IsVowel(current) || IsVowelGroup(current, n)) && (n != '\'') && (n != ' ')) {
      word_pronounced += "-";
    }
  }
  if (word_pronounced.at(word_pronounced.size() - 1) == '-') {
    word_pronounced = word_pronounced.substr(0, word_pronounced.size() - 1);
  }
  std::cout << word_pronounced << std::endl;
  
  return word_pronounced;
}

/**
 * TODO: Implement this function
 * @param hawaiian_word word to get pronunciation of
 * @return the pronunciation of hawaiian_word as a string if valid
 *  and throws an invalid_argument error if not valid
 */
std::string GetPronunciation(const std::string& hawaiian_word) {
  std::string wordlowered = StringToLower(hawaiian_word);
  if (!(IsValidWord(wordlowered))) {
    throw std::invalid_argument("THIS WORD IS NOT VALID!!!!");
  }
  return Pronunciation(wordlowered);
}