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

// 缺页
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

			if (memo.size() == pageSizeLimit) {  // 挑选一个最远没有出现的删掉
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
			printf("第%d次内存中的页面为: ", i + 1);
			for (int p: memo) printf("%d ", p);
			printf("\n");
			
		}

		printf("总共页面置换%d次\n", missPageTime);

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
					printf("当前内存中的页面为: ");
					for (int p: memo) printf("%d ", p); 
					printf("\n");
			}
		}

		printf("总共页面置换%d次\n", missPageTime);
	}

	void LRU() {   // least recently used
		// 找到最久没访问的那个页面
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
			printf("第%d次内存中的页面为: ", i + 1);
				for (auto &el: memo) printf("%d ", el.second);
				printf("\n");
			
		}

		printf("总共页面置换%d次\n", missPageTime);

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
	printf("请输入内存中限定页面的个数: ");
	scanf("%d", &pageSizeLimit);
	printf("请输入需要加载的所有页面: ");

	while (cin >> p) page.push_back(p);

	memory hostMemory{pageSizeLimit, page};
	
	printf("\n*               页面置换算法               *");
	printf("\n********************************************");
	printf("\n     1.最佳置换算法      2.先进先出页面置换     ");
	printf("\n     3.LRU页面置换算法     ");
	printf("\n********************************************");
	printf("\n请选择（1～5）: ");
	
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