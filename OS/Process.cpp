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
            printf("�ڴ����������Ƚ����򻻳�����\n");
        } else {
            process newProcess;
            printf("�������½��̵�pid: ");
            scanf("%d", &newProcess.pid);
            
            if (readyQueue.count(newProcess.pid)) {
                printf("����pid�ظ�\n");
                return;
            }

            printf("�������½��̵����ȼ�: ");
            scanf("%d",&newProcess.priority);

            printf("�������½��̵Ĵ�С: ");
            scanf("%d",&newProcess.cputime);
            
            printf("\n");
            currentProcessNumber += 1;
            readyQueue.insert({newProcess.pid, newProcess});
        }
    }

    void run() {
        printf("��ǰ��%d�������еĽ���\n", currentProcessNumber);
        for (const auto el: readyQueue) {
            const auto pro = el.second;
            printf("�ý��̵�pidΪ%d, ���ȼ�Ϊ%d, ��СΪ%d\n", pro.pid, pro.priority, pro.cputime);
        }
    }
    
    void exchange(int goalPid) {
        if (!readyQueue.count(goalPid)) {
            printf("�ý��̲��ھ��������У��޷�����");
        } else {
            blockQueue.insert({goalPid, readyQueue[goalPid]});
            readyQueue.erase(goalPid);
        }
    }

    void kill(int goalPid) {
        if (!readyQueue.count(goalPid)) {
            printf("�ý��̲��ھ��������У��޷�ɱ��");
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
        printf("\n*               ������ʾϵͳ               *");
        printf("\n********************************************");
        printf("\n     1.�����µĽ���      2.�鿴���н���     ");
        printf("\n     3.����ĳ������      4.ɱ�����н���     ");
        printf("\n     5.�˳�ϵͳ                             ");
        printf("\n********************************************");
        printf("\n��ѡ��1��5��: ");
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
                printf("�����뻻�����̵�pid: ");
                scanf("%d", &goalPid);
                hostMemory.exchange(goalPid);
                break;
            case '4':
                printf("������ɱ�����̵�pid: ");
                scanf("%d", &goalPid);
                hostMemory.kill(goalPid); /*�Զ������*/
                break;
            case '5':
                exit(0);
            default:
                n = 0;
        }
    }

    return 0;
}



