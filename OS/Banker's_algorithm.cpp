#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <list>
#include <climits>
using namespace std;
//                  总共需求   已经分配    还需要
vector<vector<int>> maxNeed, allocation, need;  //need(i, j) = maxNeed(i, j) - alloc(i, j)
vector<int> available;

int resourceNumber, processNumber;

bool checkIsSafety(vector<int> request) {
    vector<int> finish(processNumber, 0);
    vector<int> work = available;
    int count = 0;

    while (count < processNumber) {
        bool exist = false;

        for (int i = 0; i < processNumber; i++) {
            if (finish[i]) continue;
            bool allFit = true;
            for (int j = 0; j < resourceNumber; j++) {
                if (need[i][j] > work[j]) {
                    allFit = false; break;
                }
            }

            if (allFit) {
                finish[i] = exist = true;
                for (int j = 0; j < resourceNumber; j++) 
                    work[j] += allocation[i][j];
                break;
            }
        }

        if (!exist) return false;
        count += 1;
    }

    return true;
}

bool bankerAlgorithm(vector<int> request, int pro) {
    for (int i = 0; i < resourceNumber; i++) 
        if (request[i] > need[pro][i]) return false;
    
    for (int i = 0; i < resourceNumber; i++) 
        if (request[i] > available[i]) return false;
    
    for (int i = 0; i < resourceNumber; i++) {
        available[i] -= request[i];
        allocation[pro][i] += request[i];
        need[i][j] -= request[i];
    }

    if (!checkIsSafety(request)) {
        for (int i = 0; i < resourceNumber; i++) {
            available[i] += request[i];
            allocation[pro][i] -= request[i];
            need[i][j] += request[i];
        }
        return false;
    }

    return true;
}

int main(void) {
    printf("请输入计算机资源数：");     
    scanf("%d", &resourceNumber);

    printf("请输入进程数：");          
    scanf("%d", &processNumber);

    maxNeed.resize(processNumber + 1, vector<int>(resourceNumber));
    allocation.resize(processNumber + 1, vector<int>(resourceNumber));
    need.resize(processNumber + 1, vector<int>(resourceNumber));
    return 0;
}