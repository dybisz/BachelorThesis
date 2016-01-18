//
// Created by jakub on 1/17/16.
//

#include "language/language_relations.h"

namespace language{

    Language* intersection(const Language& language1,
                           const Language& language2){
        if (!equalAlphabets(language1, language2)){
            throw std::invalid_argument("Languages Alphabets must match");
        }

        Language* intersectionLanguage = new Language(language1.getAlphabet());

        for(unsigned int i = 0; i < language1.size(); i++){
            Word* word1 = language1.getWord(i);
            for(unsigned int j = 0; j < language2.size(); j++){
                Word* word2 = language2.getWord(j);
                if(*word1 == *word2){
                    Word* intersectingWord = new Word(word1);
                    intersectionLanguage->addWord(intersectingWord);
                }
            }
        }

        return intersectionLanguage;
    }

    Language* intersectionSum(const std::vector<Language *> *languages) {
        if (!equalAlphabets(languages)){
            throw std::invalid_argument("Alphabets must be of the same size");
        }
        if (languages->size() < 0){
            throw std::invalid_argument("The Language vector must be bigger "
                                                "than 0");
        }

        Language* intersectionSumLanguage = new Language(*(*languages)[0]);
        for(unsigned int i = 1; i < languages->size(); i++){
            Language* language1 = (*languages)[i];

            Language* intersectionLanguage =
                    intersection(*intersectionSumLanguage, *language1);

            delete intersectionSumLanguage;
            intersectionSumLanguage = new Language(*intersectionLanguage);

            delete intersectionLanguage;
        }

        return intersectionSumLanguage;
    }

    bool equalAlphabets(const Language& language1,
                        const Language& language2){
        Alphabet alphabet1 = language1.getAlphabet();
        Alphabet alphabet2 = language2.getAlphabet();

        if (alphabet1.size() != alphabet2.size()){
            throw std::invalid_argument("Alphabets must be of the same size");
        }

        return ((alphabet1 == alphabet2));
    }

    bool equalAlphabets(const std::vector<Language *> *languages){
        unsigned int size = languages->size();

        for(unsigned int i = 0; i < size - 1; i++){
            Language* language1 = (*languages)[i];
            for(unsigned int j = i+1; j < size; j++){
                Language* language2 = (*languages)[j];

                if(!equalAlphabets(*language1, *language2)) {
                    return false;
                }
            }
        }
        return true;
    }
}