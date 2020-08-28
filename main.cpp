#include <iostream>
#include <vector>
#include <unordered_set>


using namespace std;

vector<pair<int, int>> gale_shapely(int n, vector<vector<int>> &malePrefs, vector<vector<int>> &femalePrefs) {
    unordered_set<int> unMatchedMale;
    unordered_set<int> unMatchedFemale;
    
    vector<int> femaleMatches(n, -1); //female index to male match; initialized to -1
    
    //include all people in unmatched sets
    for (int i = 0; i < n; i++) {
        unMatchedMale.insert(i);
        unMatchedFemale.insert(i);
    }

    //create (male -> ranking) array for females; O(n^2) time
    vector<vector<int>> femalePrefsByMale;
    for (int i = 0; i < n; i++) {
        vector<int> currFemalePrefs = femalePrefs[i];
        vector<int> byMaleToInsert(n);
        for (int j = 0; j < n; j++) {
            byMaleToInsert[currFemalePrefs[j]] = j;
        }
        femalePrefsByMale.push_back(byMaleToInsert);
    }

    //main algorithm; O(n^2)
    while (!unMatchedMale.empty()) {
        int currMale = *(unMatchedMale.begin());
        vector<int> currMalePrefs = malePrefs[currMale];
        int currConsidering = currMalePrefs[currMalePrefs[0]];
        cout<<"Male: "<<currMale<<" Considering Female: "<<currConsidering<<endl;

        auto checkIsUnmatched = unMatchedFemale.find(currConsidering);
        if (checkIsUnmatched != unMatchedFemale.end()) {
            cout<<"ACCEPTED"<<endl;
            femaleMatches[currConsidering] = currMale;
            unMatchedFemale.erase(currConsidering);
            unMatchedMale.erase(currMale);
        } else {
            vector<int> currFemalePrefsByMale = femalePrefsByMale[currConsidering];
            int currEngage = femaleMatches[currConsidering];
            //if female prefers her current match to currMale, continue
            if (currFemalePrefsByMale[currEngage] < currFemalePrefsByMale[currMale]) {
                malePrefs[currMale][0]++;
                cout<<"REJECTED"<<endl;
                continue;
            //else female prefers new proposal to current match, replace current match
            } else {
                cout<<"REPLACED"<<endl;
                unMatchedMale.insert(currEngage);
                unMatchedMale.erase(currMale);
                malePrefs[currEngage][0]++;
                femaleMatches[currConsidering] = currMale;
            }
        }
    }

    
    //create pairs to output
    vector<pair<int, int>> output;
    for (int i = 0; i < n; i++) {
        output.push_back({i, femaleMatches[i]});
    }

    return output;
}

int main() {
    //index represents number of person
    //index 0 of each males preferences will represent the current rank they are considering
    
    //preference lists of males
    vector<vector<int>> male_prefs;
    
    //preference lists of each female
    vector<vector<int>> female_prefs;
    
    //number of people in each group
    int num_groups;

    string type;
    cin>>type;
    if (type == "TEST") {
        male_prefs = {
            {1, 0, 1, 2, 3, 4},
            {1, 0, 1, 2, 3, 4},
            {1, 0, 1, 2, 3, 4},
            {1, 0, 1, 2, 3, 4},
            {1, 0, 1, 2, 3, 4}
        };
        
        female_prefs = {
            {0, 1, 2, 3, 4},
            {0, 1, 2, 3, 4},
            {0, 1, 2, 3, 4},
            {0, 1, 2, 3, 4},
            {0, 1, 2, 3, 4}
        };

        num_groups = 5;
    } else {
        cin>>num_groups;
        for (int i = 0; i < num_groups * 2; i++) {
            bool malePref = i < num_groups;
            vector<int> currList;
            if (malePref) currList.push_back(1);
            for (int j = 0; j < num_groups; j++) {
                int k;
                cin>>k;
                currList.push_back(k);
            }
            if (malePref) male_prefs.push_back(currList);
            else female_prefs.push_back(currList);
        }
    }

    vector<pair<int, int>> stable_matches = gale_shapely(num_groups, male_prefs, female_prefs);

    for (int i = 0; i < num_groups; i++) {
        pair<int, int> curr = stable_matches[i];
        cout<<curr.first<<" "<<curr.second<<endl;
    }
    
    return 0;
}
