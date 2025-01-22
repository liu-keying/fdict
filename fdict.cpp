#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define WORD_SIZE 50
#define COMMENT_SIZE 100

void dict_file(int &word_num, char (*&word)[WORD_SIZE], char (*&comment)[COMMENT_SIZE])
{	
	FILE * fp;	
	int i, j;	
	if((fp = fopen("words.txt", "r")) == NULL)	
	{		
		printf("cannot find the wordlist file\n");		
		return ;	
	}	
	fscanf(fp, "%d", &word_num);	
	word = (char (*)[WORD_SIZE])malloc(sizeof(char) * WORD_SIZE * word_num);	
	comment = (char (*)[COMMENT_SIZE])malloc(sizeof(char) * COMMENT_SIZE * word_num);	
	memset(word, 0, sizeof(char) * WORD_SIZE * word_num);	
	memset(comment, 0, sizeof(char) * COMMENT_SIZE * word_num);	
	for (i = 0; i < word_num; i++)	
	{		
		fscanf(fp, "%s", word[i]);		
		fgets(comment[i], COMMENT_SIZE, fp);		
		j = 0;		
		while(comment[i][j++] == ' ');		
		strcpy(comment[i], comment[i] + j - 1);		
		if(comment[i][strlen(comment[i]) - 1] == '\n')
			comment[i][strlen(comment[i]) - 1] = '\0';		
		//printf("%s\t%s\n",word[i],comment[i]);	
	}	
	
	fclose(fp);
}
int strtcmp(char str1[], char str2[])
{
	char t1, t2;
	char diff = 'a' - 'A';
	int i = 0;

	while(str1[i] && str2[i])
	{
		t1 = str1[i]; t2 = str2[i];
		if(str1[i] > 'A' && str1[i] < 'Z')
			t1 += diff;

		if(str2[i] > 'A' && str2[i] < 'Z')
			t2 += diff;

		if(t1 > t2) return 1;
		if(t1 < t2) return -1;

		++i;
	}

	if(str1[i] == str2[i]) return 0;
	else if(str1[i] == 0) return -1;
	else if(str2[i] == 0) return 1;
}

// key��ʾ�����ѯ�ĵ���
// words[i]��ʾ���ʿ���ĵ�i������
// size��ʾ���ʿⵥ�ʴ�С
// �Ƚϵ��ʵķ���:
//     strtcmp(key, words[i])
// ���key �� words[j]��ͬ��search�������ص������j
// ���������ٸ��ݸ���������Ӧ�ĵ�����˼
// �Ҳ�������key����-1

// ����������ʾ�����ö��ֲ������search����

int search(char key[], char words[][WORD_SIZE], int size)
{
	int lower=0,upper=size,middle;
	if (!strtcmp(key, words[lower])) return 0;
	if (!strtcmp(key, words[upper])) return size;
	while(lower<=upper){
		middle=(upper+lower)/2;
	    if (!strtcmp(key, words[middle])) return middle;
	   	if (!strtcmp(key, words[lower])) return lower;
	    if (!strtcmp(key, words[upper])) return upper;
	    if (strtcmp(key, words[middle])==1) lower=middle+1;
	    if (strtcmp(key, words[middle])==-1) upper=middle-1;
	}
	return -1;
}

// ��ȷ���0
// ���ڷ���1�����ڱ�ʾstr1����ĸ������str2����
// С�ڷ���-1 С�ڱ�ʾstr1����ĸ������str2ǰ��


void help()
{
	printf("A Dictionary by xxxx.\nCopyright (c) 2018 xxxx. All Rights Reserved.\n");
	printf("Type exit to exit.\n");
}

int main()
{	
	int size;	
	char (*words)[WORD_SIZE];	
	char (*comments)[COMMENT_SIZE];	
	dict_file(size, words, comments);

	char key[WORD_SIZE];
	int i;

	help();

	while(1)
	{
		gets(key);
		if(strtcmp(key, "exit") == 0)
			break;

		i = search(key, words, size);

		if(i != -1)
		{
			printf("%s\n", comments[i]);
		}
		else
		{
			printf("No such word\n");
		}
	}

	free(words);	
	free(comments);
	
	return 0;
}
