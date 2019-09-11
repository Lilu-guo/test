//guomutian911
//2019.09.11@XDU

/**Que
1.build SA is too slow
2.storage of SA is too large
**/

// 朴素的后缀树组构造算法
#include <iostream> //输入输出头文件
#include <cstring> //字符串操作头文件
#include <algorithm> //算法库头文件，涉及sort
using namespace std; //命名空间

// 表示一个后缀，index是后缀的开始下标位置
struct suffix //数据结构：后缀
{
	int index; //后缀在文本开始的位置
	char *suff; //后缀串字符数组
};

// 字典序比较后缀
int cmp(struct suffix a, struct suffix b) //两个字串字典比较
{
	return strcmp(a.suff, b.suff) < 0 ? 1 : 0; //strcmp字串比较函数
}

// 构造txt的后缀数组
int *buildSuffixArray(char *txt, int n) //返回int型数组，参数：字串文本，字串长度
{
	//结果
	struct suffix *suffixes = new suffix[n]; //创建后缀串数据结构数组

	for (int i = 0; i < n; i++) //循环构建
	{
		suffixes[i].index = i; //记录该后缀在文本的起点下标
		suffixes[i].suff = (txt + i); //txt是字符数组指针，加i是移动，得到新字符数组首地址
	}

	// 排序
	sort(suffixes, suffixes + n, cmp); //对后缀串结构体数组进行排序

	// 排在第几的是谁
	int *suffixArr = new int[n]; //后缀数组SA，存放int
	for (int i = 0; i < n; i++)
		suffixArr[i] = suffixes[i].index; //把结构体中的index存到SA中

	return  suffixArr; //返回后缀数组SA
}

//打印
void printArr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

//搜索
void search(char *pat, char *txt, int *suffArr, int n) //参数：模式串，原文本，SA数组，原文本长度
{
	int m = strlen(pat); //模式串长度

	int l = 0, r = n - 1; //初始化搜索边界
	while (l <= r) //循环查找，保证右边界大于左边界
	{
		// 查看 'pat'是否是中间的那个后缀的前缀字串
		int mid = l + (r - l) / 2; //二分搜索，找边界中间
		int res = strncmp(pat, txt + suffArr[mid], m); //两者比较，通过txt首指针的移动拿到后缀字串

		if (res == 0) //找到目标
		{
			cout << "Pattern found at index " << suffArr[mid];
			return;
		}
		if (res < 0) r = mid - 1; //缩小范围，向左边找
		else l = mid + 1; //缩小范围，向右边找
	}
	cout << "Pattern not found"; //循环结束仍然找不到目标
}

int main()
{
	char txt[] = "ilovemybaby";  // 文本串
	int n = strlen(txt);
	int *suffixArr = buildSuffixArray(txt, n); //构建SA数组
	cout << "Following is suffix array for " << txt << endl; 
	printArr(suffixArr, n);

	char pat[] = "emy";     // 模式串
    // 构造后缀数组
	int *suffArr = buildSuffixArray(txt, n); //构建SA数组
	// 在txt中搜索pat是否出现
	search(pat, txt, suffArr, n);
	
	getchar(); //为了暂停屏幕
	return 0;
}