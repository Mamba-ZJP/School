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

// ȱҳ
class memory {
public:
	memory(int _pageSizeLimit = 3, vector<int> _page = {}): 
	pageSizeLimit(_pageSizeLimit), page(_page){}

	void optimal() {
		unordered_map<int, list<int>> rec;
		unordered_set<int> memo;
		for (int i = 0; i < page.size(); i++) 
			rec[page[i]].push_back(i);

		for (auto &el: rec) el.second.push_back(INT_MAX);
		
		int missPageTime = 0;
		for (int i = 0; i < page.size(); i++) {
			if (memo.count(page[i])) continue;

			if (memo.size() == pageSizeLimit) {  // ��ѡһ����Զû�г��ֵ�ɾ��
				missPageTime += 1;

				int time = 0, deletedPage = -1;
				for (int p: memo) {
					while (rec[p].front() <= i) rec[p].pop_front();

					int nextOccurTime = rec[p].front();
					if (nextOccurTime > time) deletedPage = p, time = nextOccurTime;
				}
				memo.erase(deletedPage);
				// if (time != INT_MAX) rec[deletedPage].pop_front();

			}

			memo.insert(page[i]);
			printf("��%d���ڴ��е�ҳ��Ϊ: ", i + 1);
			for (int p: memo) printf("%d ", p);
			printf("\n");
			
		}

		printf("�ܹ�ҳ���û�%d��\n", missPageTime);

	}

	void FIFO() {
		vector<int> memo;
		unordered_set<int> rec;
		int missPageTime = 0;
		for (int p: page) {
			if (rec.count(p)) continue;

			if (memo.size() == pageSizeLimit) {
				rec.erase(memo[0]);
				memo.erase(memo.begin());
				missPageTime += 1;
				
			}
				
			memo.push_back(p);
			rec.insert(p);
			
			{
					printf("��ǰ�ڴ��е�ҳ��Ϊ: ");
					for (int p: memo) printf("%d ", p); 
					printf("\n");
			}
		}

		printf("�ܹ�ҳ���û�%d��\n", missPageTime);
	}

	void LRU() {   // least recently used
		// �ҵ����û���ʵ��Ǹ�ҳ��
		map<int, int> memo;  // {time, page}
		unordered_set<int> rec;
		int currentTime = 0;
		int missPageTime = 0;

		for (int i = 0; i < page.size(); i++) {
			int p = page[i];

			if (rec.count(p)) {
				for (auto pos = memo.begin(); pos != memo.end(); pos++) {
					if ((*pos).second == p) {
						pair<int, int> newPage = (*pos);
						memo.erase(pos);
						newPage.first = i;
						memo.insert(newPage);
						break;
					}
				}
			} else {
				rec.insert(p);
				if (memo.size() == pageSizeLimit) {
					missPageTime += 1;
					rec.erase( (*memo.begin()).second );
					memo.erase(memo.begin());
				}
				
				memo.insert({i, p});
				
			}
			printf("��%d���ڴ��е�ҳ��Ϊ: ", i + 1);
				for (auto &el: memo) printf("%d ", el.second);
				printf("\n");
			
		}

		printf("�ܹ�ҳ���û�%d��\n", missPageTime);

	}
private:
	int pageSizeLimit;
	vector<int> page;
};

int main(void) {
	int pageSizeLimit;
	int p; 
	vector<int> page;

	printf("\n********************************************\n");
	printf("�������ڴ����޶�ҳ��ĸ���: ");
	scanf("%d", &pageSizeLimit);
	printf("��������Ҫ���ص�����ҳ��: ");

	while (cin >> p) page.push_back(p);

	memory hostMemory{pageSizeLimit, page};
	
	printf("\n*               ҳ���û��㷨               *");
	printf("\n********************************************");
	printf("\n     1.����û��㷨      2.�Ƚ��ȳ�ҳ���û�     ");
	printf("\n     3.LRUҳ���û��㷨     ");
	printf("\n********************************************");
	printf("\n��ѡ��1��5��: ");
	
	int option;
	scanf("%d", &option);
	switch (option)
	{
	case 1/* constant-expression */:
		hostMemory.optimal();
		break;
	case 2:
		hostMemory.FIFO();
		break;
	case 3:
		hostMemory.LRU();
	default:
		break;
	}
	return 0;
}

/*

7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

*/