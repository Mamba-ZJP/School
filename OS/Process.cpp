#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

class memory {
public:
    memory(int _processNumberLimit = 20): processNumberLimit(_processNumberLimit) {}

    void create() {
        if (currentProcessNumber > processNumberLimit) {
            printf("内存已满，请先结束或换出进程\n");
        } else {
            process newProcess;
            printf("请输入新进程的pid: ");
            scanf("%d", &newProcess.pid);
            
            if (readyQueue.count(newProcess.pid)) {
                printf("进程pid重复\n");
                return;
            }

            printf("请输入新进程的优先级: ");
            scanf("%d",&newProcess.priority);

            printf("请输入新进程的大小: ");
            scanf("%d",&newProcess.cputime);
            
            printf("\n");
            currentProcessNumber += 1;
            readyQueue.insert({newProcess.pid, newProcess});
        }
    }

    void run() {
        printf("当前有%d正在运行的进程\n", currentProcessNumber);
        for (const auto el: readyQueue) {
            const auto pro = el.second;
            printf("该进程的pid为%d, 优先级为%d, 大小为%d\n", pro.pid, pro.priority, pro.cputime);
        }
    }
    
    void exchange(int goalPid) {
        if (!readyQueue.count(goalPid)) {
            printf("该进程不在就绪队列中，无法换出");
        } else {
            blockQueue.insert({goalPid, readyQueue[goalPid]});
            readyQueue.erase(goalPid);
        }
    }

    void kill(int goalPid) {
        if (!readyQueue.count(goalPid)) {
            printf("该进程不在就绪队列中，无法杀死");
        } else {
            readyQueue.erase(goalPid);
        }
    }

private:
    struct process {
        int pid;
        int priority;
        int cputime;
    };

    unordered_map<int, process> readyQueue;
    unordered_map<int, process> blockQueue;
    int currentProcessNumber = 0;
    int processNumberLimit;    
};


int main(void) {
    int n, m, i;
    char a;
    n = 1;
    int goalPid;
    
    memory hostMemory(20);
    while (n == 1)
    {
        printf("\n********************************************");
        printf("\n*               进程演示系统               *");
        printf("\n********************************************");
        printf("\n     1.创建新的进程      2.查看运行进程     ");
        printf("\n     3.换出某个进程      4.杀死运行进程     ");
        printf("\n     5.退出系统                             ");
        printf("\n********************************************");
        printf("\n请选择（1～5）: ");
        cin >> a;

        switch (a)
        {
            case '1':
                hostMemory.create();
                break;
            case '2':
                hostMemory.run();
                break;
            case '3':
                printf("请输入换出进程的pid: ");
                scanf("%d", &goalPid);
                hostMemory.exchange(goalPid);
                break;
            case '4':
                printf("请输入杀死进程的pid: ");
                scanf("%d", &goalPid);
                hostMemory.kill(goalPid); /*自定义过程*/
                break;
            case '5':
                exit(0);
            default:
                n = 0;
        }
    }

    return 0;
}



