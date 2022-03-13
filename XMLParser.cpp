// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	std::size_t s = 0;
	std::size_t i = 0;
	std::vector<std::string> xmlItems;
	bool inTag = false;

	//Turn string into vector of strings cut at < and >
	while(i<inputString.size()){

		if(inputString[i]=='<'){
			xmlItems.push_back(inputString.substr(s, s-i));
			s = i;
			i++;
		}
		else if(inputString[i]=='>'){
			i++;
			xmlItems.push_back(inputString.substr(i, s-i));
			s = i;
		}
		else{i++;}
	}
	xmlItems.push_back(inputString.substr(i, s-i));

	//Clear null items
	for(std::size_t i=0;i<xmlItems.size();i++){
		if(xmlItems[i].size()==0){xmlItems.erase(xmlItems.begin()+i);i--;}
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

	return true;
}  // end

// TODO: Implement a helper function to delete attributes from a START_TAG
// or EMPTY_TAG string (you can change this...)
static std::string deleteAttributes(std::string input)
{
	return input;
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	return false;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	return false;
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	return -1;
}

TokenStruct *XMLParser::toTag(std::string xmlItem) const{

	StringTokenType TokenType;
	if(xmlItem[0]=='<'){
		//Check if between 2 <>
		if(!(xmlItem[xmlItem.size()-1]=='>'||xmlItem.size()==2||(xmlItem.size()==3&&xmlItem[1]=='/'))){return nullptr;}

		StringTokenType TokenType;
		if(xmlItem[1]=='/'){
			TokenType = END_TAG;
			string tagContent = xmlItem.substr(2, xmlItem.size()-2);
			
		}else if(xmlItem[xmlItem.size()-2]=='/'){
			TokenType = EMPTY_TAG;
			string tagContent = xmlItem.substr(1, xmlItem.size()-3);
		}else{
			TokenType = START_TAG;
			string tagContent = xmlItem.substr(1, xmlItem.size()-2);
		}







		string ILLEGAL_TAG_FIRST_CHAR = "-,.";
		string ILLEGAL_TAG_CHAR = "!\"#$%&'()*+,/;<=>?@[\\]^`{|}~";





		for(std::size_t compchar=0; compchar<ILLEGAL_TAG_FIRST_CHAR.size();compchar++){
			//if(tagContent[])
		}


	}
	else{
		for(std::size_t i=0;i<xmlItem.size();i++){
			//Check for <>
			if(xmlItem[i]=='<' || xmlItem[i]=='>'){return nullptr;}

			//Generic return
			TokenStruct *Token = new TokenStruct();
			Token->tokenType = CONTENT;
			Token->tokenString = xmlItem;
			return Token;
		}
	}




	return nullptr;
}
