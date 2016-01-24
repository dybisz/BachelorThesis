//
// Created by dybisz on 20.12.15.
//

#include <language/language.h>
#include <language/language_algorithms.h>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

Language::Language(Alphabet alphabet) : _alphabet(alphabet) {

}

Language::Language(const Language &language) :
        _alphabet(language.getAlphabet()){
    for(unsigned int i = 0; i < language.size(); i++){
        Word* otherWord = language.getWord(i);
        Word *word = new Word(*otherWord);

        this->addWord(word);
    }
}

Language::Language(vector<Word *> &words, Alphabet pAlphabet,
                   vector<State *> pStates) : _words(words),
                                              _alphabet(pAlphabet),
                                              _states(pStates) {
}

Language::Language(vector<Word *> &words, Alphabet pAlphabet)
        : _words(words),
          _alphabet(pAlphabet) {
}

Language::Language(vector<Word *> words, Language *lang) :
        _alphabet(lang->getAlphabet()) {

    // Create new pointers to words
    for (auto w = words.begin(); w != words.end(); ++w) {
        Word *word = new Word((*w));
        _words.push_back(word);
    }

    // Copy states values
    const vector<State *> *lStates = lang->getStates();

    for (auto pState = lStates->begin(); pState != lStates->end(); ++pState) {
        State *s = new State(**pState);
        _states.push_back(s);
    }
}

Language::~Language() {
    freeWordsMemory();
    freeStatesMemory();
}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

vector<State *> *Language::getStates() {
    return &_states;
}

vector<Word *> *Language::getWords() {
    return &_words;
}

Alphabet Language::getAlphabet() const {
    return _alphabet;
}

int Language::size() const {
    return _words.size();
}

void Language::setStates(std::vector<State *> states) {
    _safeDeleteContent(this->_states);
    this->_states = states;
}

bool Language::isCorrespondingState(State *state) const {
    for (unsigned int i = 0; i < _states.size(); i++) {
        if (*(_states[i]) == *state)
            return true;
    }
    return false;
}

void Language::addWord(Word *word) {
    this->_words.push_back(word);
}

void Language::append(const Language &language) {
    for(unsigned int i = 0; i < language.size(); i++){
        Word* word = language.getWord(i);

        this->addWord(new Word(word));
    }
}

void Language::removeDuplicates() {
    vector<Word*> wordsWithNoDuplicates
                    = getWordsWithoutDuplicates(this->_words);

    this->freeWordsMemory();
    _words = wordsWithNoDuplicates;
}

int Language::numberOfOccurrences(const Word& word) {
    return language::numberOfOccurrences(this->_words, word);
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

void Language::setNewWords(const vector<Word *> &words) {
    this->freeWordsMemory();

    for(unsigned int i = 0; i < words.size(); i++){
        Word* word = new Word(words[i]);
        this->addWord(word);
    }
}


vector<Word*> Language::getWordsWithoutDuplicates(
                                    const vector<Word *> &words){
    vector<Word*> wordsWithoutDuplicates;

    for(unsigned int i = 0; i < this->size(); i++){
        Word* word = _words[i];
        if (language::numberOfOccurrences(wordsWithoutDuplicates, *word) == 0){
            Word* nonDuplicatingWord = new Word(*word);
            wordsWithoutDuplicates.push_back(nonDuplicatingWord);
        }
    }
    return wordsWithoutDuplicates;
}

string Language::toString() {
    string out = "<< LANGUAGE SUMMARY >>\n";
    out += statesToString();
    out += "\n";
    out += alphabetToString();
    out += "\n";
    out += wordsToString();
    out += "\n";
    return out;
}

string Language::statesToString() {
// string out = "[States]: \n";
    string out = "";
    for (auto iter = _states.begin(); iter != _states.end(); ++iter) {
        out += (*iter)->toString();
        out += " ";
    }
// out += "\n";
    return out;
}

string Language::wordsToString() {
    string out = "[Words]: \n";
    for (auto iter = _words.begin(); iter != _words.end(); ++iter) {
        out += (*iter)->toString();
        out += "\n";
    }

    return out;
}

string Language::alphabetToString() {
    string out = "[Alphabet]: \n";
    out += _alphabet.toString();
    out += "\n";
    return out;
}

Word *Language::getWord(int i) const{
    return _words[i];
}

Word *Language::stealLastWord() {
    Word *word = _words.back();
    _words.pop_back();
    return word;
}

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */

void Language::_safeDeleteContent(vector<State *> vec) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        delete (*it);
    }
    vec.clear();
}

void Language::freeWordsMemory() {
    for (unsigned int i = 0; i < _words.size(); i++) {
        delete (_words)[i];
    }
    _words.clear();
}


void Language::freeStatesMemory() {
    for (unsigned int i = 0; i < _states.size(); i++) {
        delete (_states)[i];
    }
    _states.clear();
}
