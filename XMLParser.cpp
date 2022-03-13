// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	tokenized=false;
	parsed=false;
	elementNameBag = new Bag<string>();
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	clear();
	std::size_t s = 0;
	std::size_t i = 0;
	std::vector<std::string> xmlItems;
	bool inTag = false;

	//Turn string into vector of strings cut at < and >
	while(i<inputString.size()){

		if(inputString[i]=='<'){
			xmlItems.push_back(inputString.substr(s, i-s));
			s = i;
			i++;
		}
		else if(inputString[i]=='>'){
			xmlItems.push_back(inputString.substr(s, i-s+1));
			s = i+1;
			i++;
		}
		else{i++;}
	}
	xmlItems.push_back(inputString.substr(s, i-s));

	//Clear null items
	i=0;
	while(i<xmlItems.size()){
		if(xmlItems[i].size()==0){
			xmlItems.erase(xmlItems.begin()+i);
		}
		else{i++;}
	}

	//Make tags and check if valid
	bool valid = true;
	for(std::size_t i=0;i<xmlItems.size();i++){
		TokenStruct *Token = toTag(xmlItems[i]);
		if(Token==nullptr){
			tokenizedInputVector.clear();
			return false;
		}


		tokenizedInputVector.push_back(*Token);
		Token = nullptr;
	}
	tokenized=true;
	return true;
}  // end

// TODO: Implement a helper function to delete attributes from a START_TAG
// or EMPTY_TAG string (you can change this...)
static std::string deleteAttributes(std::string input)
{
	//END TAGS NO ATRIBUTES!!!!! FIX
	return input;
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	if(!(tokenized)){return false;}
	string pullString;
	parseStack->clear();
	for(std::size_t i=0;i<tokenizedInputVector.size();i++){
		if(tokenizedInputVector[i].tokenType==START_TAG){
			elementNameBag->add(tokenizedInputVector[i].tokenString);
			parseStack->push(tokenizedInputVector[i].tokenString);
		}
		else if(tokenizedInputVector[i].tokenType==END_TAG){
			pullString = parseStack->peek();
			parseStack->pop();
			if(pullString!=tokenizedInputVector[i].tokenString){
				elementNameBag->clear();
				parseStack->clear();
				return false;
			}
		}
	}
	parseStack->clear();
	parsed=true;
	return true;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	tokenizedInputVector.clear();
	parseStack->clear();
	elementNameBag->clear();
	tokenized=false;
	parsed=false;
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	return elementNameBag->contains(inputString);
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	return elementNameBag->getFrequencyOf(inputString);
}

TokenStruct *XMLParser::toTag(std::string xmlItem) const{

	StringTokenType TokenType;
	if(xmlItem[0]=='<'){
		//Check if between 2 <>
		if(!(xmlItem[xmlItem.size()-1]=='>'||xmlItem.size()==2||(xmlItem.size()==3&&xmlItem[1]=='/'))){return nullptr;}

		//Check declaraction
		if(xmlItem[1]=='?'){
			if(xmlItem[xmlItem.size()-2]=='?'){
				string s = xmlItem.substr(2, xmlItem.size()-3);
				return genToken(DECLARATION, s);
			}
			return nullptr;
		}

		StringTokenType TokenType;
		string tagContent;
		if(xmlItem[1]=='/'){
			TokenType = END_TAG;
			tagContent = xmlItem.substr(2, xmlItem.size()-3);
		}else if(xmlItem[xmlItem.size()-2]=='/'){
			TokenType = EMPTY_TAG;
			tagContent = xmlItem.substr(1, xmlItem.size()-3);
		}else{
			TokenType = START_TAG;
			tagContent = xmlItem.substr(1, xmlItem.size()-2);
		}

		string tagName = getName(tagContent);

		if(!(checkNameChars(tagName))){
			return nullptr;
		}
		return genToken(TokenType, tagName);



	}
	else{
		for(std::size_t i=0;i<xmlItem.size();i++){
			//Check for <>
			if(xmlItem[i]=='<' || xmlItem[i]=='>'){return nullptr;}

			//Generic return
			return genToken(CONTENT, xmlItem);
		}
	}




	return nullptr;
}


bool XMLParser::checkNameChars(std::string tagName) const{
	string ILLEGAL_TAG_FIRST_CHAR = "-,.";
	string ILLEGAL_TAG_CHAR = "!\"#$%&'()*+,/;<=>?@[\\]^`{|}~";

	//Check illegal first chars
	for(std::size_t compchar=0; compchar<ILLEGAL_TAG_FIRST_CHAR.size();compchar++){
		if(tagName[0]==ILLEGAL_TAG_CHAR[compchar]){
			return false;
		}
	}

	//Check illegal generic chars
	for(std::size_t compchar=0; compchar<ILLEGAL_TAG_CHAR.size();compchar++){
		for(std::size_t checkchar=0; checkchar<tagName.size();checkchar++){
			if(tagName[checkchar]==ILLEGAL_TAG_CHAR[compchar]){
				return false;
			}
		}
	}

	return true;
}

std::string XMLParser::getName(std::string tagContent) const{
	std::string tagName;
	std::size_t i=0;
	while(i<tagContent.size()&&tagContent[i]!=' '){i++;}
	return tagContent.substr(0,i);
}

TokenStruct *XMLParser::genToken(StringTokenType tokenType, std::string tokenString) const{
	TokenStruct *r = new TokenStruct;
	r->tokenString = tokenString;
	r->tokenType = tokenType;
	return r;
}
