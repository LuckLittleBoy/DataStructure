#include<iostream>
#include<string>
using namespace std;

#define m 50
#define p 40
typedef struct
{
	string key;     //�ؼ���Ϊstring���洢����ƴ��	
	int times;      //times Ϊ�Ƚϴ���
	int j;
}Hash;

Hash HashTable[m];

typedef struct
{
	string name;
	int num;
}Name;

Name NameTable[30];


int getnum(string s)
{
	int l = s.length();
	int n = 0;
	for(int o = 0;o<l;o++)
	{
		n = n + s[o];
	}

	return n;
}

void CreatHashTable()//����̽�ⷨ�����ͻ
{
	//////////////////////����ĳ�ʼ��
	NameTable[0].name="baojianbo";
NameTable[1].name="chenjiabin";
NameTable[2].name="chenxi";
NameTable[3].name="dinglin";
NameTable[4].name="fangzewei";
NameTable[5].name="fengpan";
NameTable[6].name="guidong";
NameTable[7].name="hanlijuan";
NameTable[8].name="haoxiaoju";
NameTable[9].name="heqing";
NameTable[10].name="jishaomei";
NameTable[11].name="jiyunfeng";
NameTable[12].name="jiangshanshan";
NameTable[13].name="lixuefei";
NameTable[14].name="lixueqin";
NameTable[15].name="liyuanxin";
NameTable[16].name="liangguannan";
NameTable[17].name="liuna";
NameTable[18].name="liupeiyu";
NameTable[19].name="nixiaodong";
NameTable[20].name="peixue";
NameTable[21].name="sunke";
NameTable[22].name="sunying";
NameTable[23].name="wanqishuai";
NameTable[24].name="wangna";
NameTable[25].name="linglei";
NameTable[26].name="xinnaping";
NameTable[27].name="xuyuanfei";
NameTable[28].name="yanlipeng";
NameTable[29].name="yangmengjiao";
	////////////////////////
	int i;
	for(i = 0;i<30;i++)
	{
		NameTable[i].num = getnum(NameTable[i].name);
	}

	for(i = 0;i<m;i++)
	{
		HashTable[i].j = 0;
		HashTable[i].key = "******";
		HashTable[i].times = 0;
	}
	//////////////////////////////

	for(i = 0;i<30;i++)
	{
		int H0 = NameTable[i].num % p; //����H(key)
		if(HashTable[H0].j == 0)
		{
			HashTable[H0].key = NameTable[i].name;
			HashTable[H0].times = 1;
			HashTable[H0].j = 1;
		}
		else 
		{
			int Hi;
			for(int x = 1;x < m;x++)
			{
				Hi = (H0 + x) % m;
				if(HashTable[Hi].j == 0)
				{
					HashTable[Hi].key = NameTable[i].name;
					HashTable[Hi].times = i;
					HashTable[Hi].j = 1;
					break;
				}
				
			}
		}
	}
}

bool judge(string a,string b)
{
	if(a.length() != b.length())
		return false;
	else
	{
		int d = a.length();
		for(int i = 0;i<d;i++)
		{
			if(a[i]-b[i]!=0)
				return false;
		}
	}
	///////////////////////////////////
	return true;
}

void SearchHAshTable(string s)
{
	int k = getnum(s);
	int H1 = k % p;
	if(HashTable[H1].j == 0)//��ַΪ��
		cout<<"\n���޴���!\n"<<endl;/////////////////////////
	else if(HashTable[H1].j == 1)//��ַ��Ϊ��
	{
		if(judge(HashTable[H1].key,s))
		{
			cout<<"\n���ҳɹ�!\n"<<endl;/////////////////////
			cout<<"ɢ�е�ַ    �Ƚϴ���            �ؼ���\n";
			cout<<H1<<"\t\t"<<HashTable[H1].times<<"\t\t"<<HashTable[H1].key<<"\n"<<endl;
		}
		else
		{
			int Hi2;
			for(int i = 1;i<m;i++)
			{
				Hi2 = (H1 + i) % m;
				if(HashTable[H1].j == 0)//��ַΪ��
				{
					cout<<"\n���޴���!\n"<<endl;
					break;
				}
				else if(HashTable[H1].j == 1)
				{
					if(judge(HashTable[H1].key,s))
						cout<<"\n���ҳɹ�!"<<endl;
						cout<<"ɢ�е�ַ    �Ƚϴ���            �ؼ���\n";
						cout<<H1<<"\t\t"<<HashTable[H1].times<<"\t\t"<<HashTable[H1].key<<endl;
						cout<<endl;
					break;
				}
			}
		}
	}
}

void main()
{
	CreatHashTable();
	int choice;
	
	while(1)
	{
		cout<<"1��ʾ�б���Ϣ  2����  3�˳�"<<endl;
		cin>>choice;
		if(choice == 1)
		{
			cout<<"\nɢ�е�ַ    �Ƚϴ���            �ؼ���\n";
			for(int q = 0;q<m;q++)
				cout<<q<<"\t\t"<<HashTable[q].times<<"\t\t"<<HashTable[q].key<<"\n";////////////////////////////////
		}
		else if(choice == 2)
		{
			string s;
			cout<<"������Ҫ��ѯ�����֣�ƴ����:";
			cin>>s;
			SearchHAshTable(s);
		}
		else if(choice == 3)
			break;
		else
			cout<<"�����������������!"<<endl;
	}
}