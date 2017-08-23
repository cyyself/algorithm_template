#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
int main(){
	string str = "I love you";
	string separator = " ";
	vector <string> result;
	int i=0;
	string temp = "";
	while(i != str.length()){
		if (str[i] == separator[0]){
			if (str.substr(i,separator.size()) == separator){
				//matched
				i += separator.length();
				result.push_back(temp);
				temp = "";
				continue;
			}
		}
		temp += str[i];
		i++;
	}
	if (temp != ""){
		result.push_back(temp);
	}
	for (int i=0;i<result.size();i++){
		cout << result[i] << endl;
	}
	return 0;
}
