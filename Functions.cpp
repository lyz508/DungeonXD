#include "Functions.h"
using namespace std;

string base_search(string tag_name){

    string file_name = "information_base.txt";
    string container;

    fstream input;
    input.open(file_name, ios::in);

    /*if (input.fail()){
        cout << "Can't Find \"information.txt\"" << endl;
        exit(1);
    }*/

    string criti = "*", tmp_input, target_name;
    vector<string> whole_input, desire_content;

    while(getline(input, tmp_input)){
        whole_input.push_back(tmp_input);
    }

    target_name = tag_name;
    //cout << target_name;

    int is_find = 0;
    for(int i=0; i<whole_input.size(); i++){
        if(whole_input[i] == criti){
            if (whole_input[i+1] != target_name){
                continue;
            }
            else if(whole_input[i+1] == target_name){
                for(int iw = i+2; whole_input[iw] != "*"; iw++){
                    desire_content.push_back(whole_input[iw]);
                }
                is_find = 1;
                break;
            }
        }
    }

    for(int i=0; i<desire_content.size(); i++){
        container += desire_content[i] + '\n';
    }

    /*if (is_find == 0){
        cout << "Can't find " + target_name + " in the " << file_name << endl;
    }*/


    input.close();
    return container;
}


void base_search(string tag_name, vector<string> &container){

    string file_name = "information_base.txt";

    fstream input;
    input.open(file_name, ios::in);

    /*if (input.fail()){
        cout << "Can't Find \"information.txt\"" << endl;
        exit(1);
    }*/

    string criti = "*", tmp_input, target_name;
    vector<string> whole_input;

    while(getline(input, tmp_input)){
        whole_input.push_back(tmp_input);
    }

    target_name = tag_name;

    int is_find = 0;
    for(int i=0; i<whole_input.size(); i++){
        if(whole_input[i] == criti){
            if (whole_input[i+1] != target_name){
                continue;
            }
            else if(whole_input[i+1] == target_name){
                for(int iw = i+2; whole_input[iw] != "*"; iw++){
                    container.push_back(whole_input[iw]);
                }
                is_find = 1;
                break;
            }
        }
    }

    /*if (is_find == 0){
        cout << "Can't find " + target_name + " in the " << file_name << endl;
    }*/


    input.close();
}


// use the * to seperate the npcs and build as a vector
vector<string> npc_seperator(ifstream& in){

    vector<string> return_npcs, whole_input;
    string tmp_input, seperated, criti = "*";
    int hit_criti[1000] = {}, ih = 0;

    while(getline(in, tmp_input)){
        whole_input.push_back(tmp_input);
    }

    for(int i=0; i<whole_input.size(); i++){
        if (whole_input[i] == criti && i != whole_input.size()-1){
            string a_npc;
            for(int in_re = i+1; whole_input[in_re] != criti; in_re++){
                a_npc += whole_input[in_re];
                if (whole_input[in_re+1] != criti){
                    a_npc += "\n";
                }
            }
            return_npcs.push_back(a_npc);
        }
    }

    return return_npcs;
}





string rand_name_generator(string tag_name){
    vector<string> container;

    base_search(tag_name, container);

    return container[rand()%container.size()];
}

int rare_generator(){
    int rare_value = (unsigned int)rand()%1000 + 1;

    if (rare_value >= 950){
        rare_value = 4;
    }
    else if(rare_value <= 950 && rare_value >= 850){
        rare_value = 3;
    }
    else if(rare_value <= 850 && rare_value >= 700){
        rare_value = 2;
    }
    else if(rare_value <= 700 && rare_value >= 200){
        rare_value = 1;
    }
    else if(rare_value <= 200 && rare_value >= 0){
        rare_value = 0;
    }

    return rare_value;
}
